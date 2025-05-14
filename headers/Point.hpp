#ifndef Point_hpp
#define Point_hpp

class Point {
public:
	float x, y;
	Point()
		: x(0)
		, y(0)
	{ }
	Point(float x, float y)
		: x(x)
		, y(y)
	{ }

	bool operator ==(const Point& other) const {
		return x == other.x && y == other.y;
	}

	bool operator !=(const Point& other) const {
		return x != other.x || y != other.y;
	}

	bool operator <(const Point& other) const {
		return std::tie(x, y) < std::tie(other.x, other.y);
	}
};

#endif