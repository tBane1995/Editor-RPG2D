#ifndef Collisions_hpp
#define Collisions_hpp

#define M_PI 3.14159265358979323846f
float angle;
float px, py;
int numPoints = 8;

bool isPointInRectangle(float px, float py, float rx, float ry, float rwidth, float rheight) {

    if (px > rx - rwidth / 2.0f && px < rx + rwidth / 2.0f && py > ry - rheight / 2.0f && py < ry + rheight / 2.0f)
        return true;
    
    return false;
}

bool isPointInEllipse(float px, float py, float cx, float cy, float rx, float ry) {
    // Sprawdza, czy punkt (px, py) znajduje się wewnątrz elipsy o środku (cx, cy) i półosiach rx, ry
    return (std::pow(px - cx, 2) / std::pow(rx, 2)) + (std::pow(py - cy, 2) / std::pow(ry, 2)) <= 1;
}

bool isPointInLine(sf::Vector2f point, sf::Vector2f line_start, sf::Vector2f line_end) {

    const float delta = 1000 * std::numeric_limits<float>::epsilon();

    float line_len = sqrt(pow(line_end.x - line_start.x, 2) + pow(line_end.y - line_start.y, 2));

    float distance_from_start = sqrt(pow(line_start.x - point.x, 2) + pow(line_start.y - point.y, 2));
    float distance_from_end = sqrt(pow(line_end.x - point.x, 2) + pow(line_end.y - point.y, 2));

    return std::abs(line_len - distance_from_start - distance_from_end) <= delta;

}

bool isPointInTriangle(sf::Vector2f A, sf::Vector2f B, sf::Vector2f C, sf::Vector2f P) {
    
    float w1 = (C.x * (A.y - C.y) + (P.y - C.y) * (A.x - C.x) - P.x * (A.y - C.y)) /
        ((B.y - C.y) * (A.x - C.x) - (B.x - C.x) * (A.y - C.y));

    float w2 = (P.y - C.y - w1 * (B.y - C.y)) / (A.y - C.y);

    return w1 >= 0 && w2 >= 0 && (w1 + w2) <= 1;
}



bool intersectionTwoEllipses(float x1, float y1, float rx1, float ry1, float x2, float y2, float rx2, float ry2) {

    // Sprawdzenie punktów na pierwszej elipsie względem drugiej elipsy
    for (short i = 0; i < numPoints; ++i) {

        angle = 2 * M_PI * i / numPoints;
        px = x1 + rx1 * std::cos(angle);
        py = y1 + ry1 * std::sin(angle);

        if (isPointInEllipse(px, py, x2, y2, rx2, ry2)) {
            return true;
        }
    }

    // Sprawdzenie punktów na drugiej elipsie względem pierwszej elipsy
    for (short i = 0; i < numPoints; ++i) {

        angle = 2 * M_PI * i / numPoints;
        px = x2 + rx2 * std::cos(angle);
        py = y2 + ry2 * std::sin(angle);

        if (isPointInEllipse(px, py, x1, y1, rx1, ry1)) {
            return true;
        }
    }

    // Brak przecięcia
    return false;
}

bool intersectionTwoRectangles(float x1, float y1, float width1, float height1, float x2, float y2, float width2, float height2) {

    if ( abs(x1 - x2) < (width1 + width2) / 2.0f && abs(y1-y2) < (height1 + height2) / 2.0f )
        return true;

    return false;

}

bool intersectionRectangleWithElipse(float r_x, float r_y, float r_width, float r_height, float e_x, float e_y, float e_radiusx, float e_radiusy) {

    // Sprawdzenie, czy któryś z rogów prostokąta znajduje się w elipsie
    float half_width = r_width / 2.0f;
    float half_height = r_height / 2.0f;

    float rect_corners[4][2] = {
        {r_x - half_width, r_y - half_height}, // Lewy górny
        {r_x + half_width, r_y - half_height}, // Prawy górny
        {r_x - half_width, r_y + half_height}, // Lewy dolny
        {r_x + half_width, r_y + half_height}  // Prawy dolny
    };

    for (int i = 0; i < 4; i++) {
        float dx = (rect_corners[i][0] - e_x) / e_radiusx;
        float dy = (rect_corners[i][1] - e_y) / e_radiusy;
        if ((dx * dx + dy * dy) <= 1.0f)
            return true;
    }

    // Sprawdzenie punktów leżących na elipsie czy są w prostokącie
    for (short i = 0; i < numPoints; ++i) {

        angle = 2 * M_PI * i / numPoints;
        px = e_x + e_radiusx * std::cos(angle);
        py = e_y + e_radiusy * std::sin(angle);

        if (px > r_x - r_width / 2.0f && px < r_x + r_width / 2.0f && py > r_y - r_height / 2.0f && py < r_y + r_height / 2.0f)
            return true;

    }

    return false;

}

bool onSegment(sf::Vector2f _p, sf::Vector2f _q, sf::Vector2f _r)  {
    return _q.x <= std::max(_p.x, _r.x) && _q.x >= std::min(_p.x, _r.x) &&
        _q.y <= std::max(_p.y, _r.y) && _q.y >= std::min(_p.y, _r.y);
}

int orientation(sf::Vector2f _p, sf::Vector2f _q, sf::Vector2f _r)  {
    float val = (_q.y - _p.y) * (_r.x - _q.x) - (_q.x - _p.x) * (_r.y - _q.y);
    if (val == 0) return 0; // kolinearne

    return(val > 0) ? 1 : 2; // 1 = zgodnie ze wskazówkami zegara, 2 = przeciwnie
}


bool intersectionTwoLines( sf::Vector2f _p1, sf::Vector2f _q1, sf::Vector2f _p2, sf::Vector2f _q2) {

    // if line is a point return false
    if (_p1 == _q1 || _p2 == _q2)
        return false;

    int o1 = orientation(_p1, _q1, _p2);
    int o2 = orientation(_p1, _q1, _q2);
    int o3 = orientation(_p2, _q2, _p1);
    int o4 = orientation(_p2, _q2, _q1);

    if (o1 != o2 && o3 != o4) return true;

    if (o1 == 0 && onSegment(_p1, _p2, _q1)) return true;

    if (o2 == 0 && onSegment(_p1, _q2, _q1)) return true;

    if (o3 == 0 && onSegment(_p2, _p1, _q2)) return true;

    if (o4 == 0 && onSegment(_p2, _q1, _q2)) return true;

    return false;
}

bool intersectionRectangleWithTriangle(float r_x, float r_y, float r_width, float r_height, sf::Vector2f a, sf::Vector2f b, sf::Vector2f c) {

    // Points of Triangle in Rect
    if (isPointInRectangle(a.x, a.y, r_x, r_y, r_width, r_height))
        return true;

    if (isPointInRectangle(b.x, b.y, r_x, r_y, r_width, r_height))
        return true;

    if (isPointInRectangle(c.x, c.y, r_x, r_y, r_width, r_height))
        return true;

    // Points of Rectangle in Triangle
    if (isPointInTriangle(a, b, c, sf::Vector2f(r_x - r_width / 2.0f, r_y - r_height / 2.0f)))
        return true;

    if (isPointInTriangle(a, b, c, sf::Vector2f(r_x + r_width / 2.0f, r_y - r_height / 2.0f)))
        return true;

    if (isPointInTriangle(a, b, c, sf::Vector2f(r_x - r_width / 2.0f, r_y + r_height / 2.0f)))
        return true;

    if (isPointInTriangle(a, b, c, sf::Vector2f(r_x + r_width / 2.0f, r_y + r_height / 2.0f)))
        return true;

    // Intersection of lines of Triangle and Rectangle

    // AB and rect lines
    if (intersectionTwoLines(a,b, sf::Vector2f(r_x-r_width/2.0f,r_y-r_height/2.0f),sf::Vector2f(r_x-r_width/2.0f,r_y+r_height/2.0f)))
        return true;

    if (intersectionTwoLines(a, b, sf::Vector2f(r_x + r_width/2.0f,r_y-r_height/2.0f),sf::Vector2f(r_x+r_width/2.0f,r_y+r_height/2.0f)))
        return true;

    if (intersectionTwoLines(a, b, sf::Vector2f(r_x - r_width / 2.0f, r_y - r_height / 2.0f), sf::Vector2f(r_x + r_width / 2.0f, r_y - r_height / 2.0f)))
        return true;

    if (intersectionTwoLines(a, b, sf::Vector2f(r_x - r_width / 2.0f, r_y + r_height / 2.0f), sf::Vector2f(r_x + r_width / 2.0f, r_y + r_height / 2.0f)))
        return true;


    // BC and rect lines
    if (intersectionTwoLines(b, c, sf::Vector2f(r_x - r_width / 2.0f, r_y - r_height / 2.0f), sf::Vector2f(r_x - r_width / 2.0f, r_y + r_height / 2.0f)))
        return true;

    if (intersectionTwoLines(b, c, sf::Vector2f(r_x + r_width / 2.0f, r_y - r_height / 2.0f), sf::Vector2f(r_x + r_width / 2.0f, r_y + r_height / 2.0f)))
        return true;

    if (intersectionTwoLines(b, c, sf::Vector2f(r_x - r_width / 2.0f, r_y - r_height / 2.0f), sf::Vector2f(r_x + r_width / 2.0f, r_y - r_height / 2.0f)))
        return true;

    if (intersectionTwoLines(b, c, sf::Vector2f(r_x - r_width / 2.0f, r_y + r_height / 2.0f), sf::Vector2f(r_x + r_width / 2.0f, r_y + r_height / 2.0f)))
        return true;

    // AB and rect lines
    if (intersectionTwoLines(c, a, sf::Vector2f(r_x - r_width / 2.0f, r_y - r_height / 2.0f), sf::Vector2f(r_x - r_width / 2.0f, r_y + r_height / 2.0f)))
        return true;

    if (intersectionTwoLines(c, a, sf::Vector2f(r_x + r_width / 2.0f, r_y - r_height / 2.0f), sf::Vector2f(r_x + r_width / 2.0f, r_y + r_height / 2.0f)))
        return true;

    if (intersectionTwoLines(c, a, sf::Vector2f(r_x - r_width / 2.0f, r_y - r_height / 2.0f), sf::Vector2f(r_x + r_width / 2.0f, r_y - r_height / 2.0f)))
        return true;

    if (intersectionTwoLines(c, a, sf::Vector2f(r_x - r_width / 2.0f, r_y + r_height / 2.0f), sf::Vector2f(r_x + r_width / 2.0f, r_y + r_height / 2.0f)))
        return true;

    return false;

}

#endif // !Collisions_hpp
