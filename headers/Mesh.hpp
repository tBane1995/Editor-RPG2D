#ifndef Mesh_hpp
#define Mesh_hpp

class GameObject;

class Triangle {
public:
	sf::Vector2f a, b, c;
};

void drawThickLine(sf::Vector2f start, sf::Vector2f end, float thickness, sf::Color color) {
    sf::Vector2f direction = end - start;
    sf::Vector2f unitDirection = direction / std::sqrt(direction.x * direction.x + direction.y * direction.y);
    sf::Vector2f normal(-unitDirection.y, unitDirection.x);
    sf::Vector2f offset = (thickness / 2.f) * normal;

    sf::Vertex vertices[4];
    vertices[0].position = start + offset;
    vertices[1].position = end + offset;
    vertices[2].position = end - offset;
    vertices[3].position = start - offset;

     for (int i = 0; i < 4; ++i) {
        vertices[i].color = color;
    }

    renderer->getTheCurrentFrame()->draw(vertices, 4, sf::Quads);
}

class Mesh {
public:
    const float line_weight = 1.25f;
    const sf::Color line_color = sf::Color(255, 48, 48);
    std::wstring name;
	std::vector <Triangle> triangles;

    Mesh(std::wstring name) {
        this->name = name;
        triangles.clear();
    }

    ~Mesh() {
        triangles.clear();
    }

    bool isEar(const std::vector<sf::Vector2f>& vertices, int i, int prev, int next) {
        sf::Vector2f A = vertices[prev];
        sf::Vector2f B = vertices[i];
        sf::Vector2f C = vertices[next];

        // Sprawdź, czy trójkąt jest wypukły
        float crossProduct = (B.x - A.x) * (C.y - A.y) - (B.y - A.y) * (C.x - A.x);
        if (crossProduct <= 0) return false; // Trójkąt jest wklęsły, nie jest uchem

        // Sprawdź, czy inne wierzchołki leżą wewnątrz trójkąta
        for (size_t j = 0; j < vertices.size(); j++) {
            if (j != i && j != prev && j != next && isPointInTriangle(A, B, C, vertices[j])) {
                return false; // Trójkąt zawiera inne wierzchołki, nie jest uchem
            }
        }
        return true; // Trójkąt jest uchem
    }

    void triangulate(std::vector<sf::Vector2f>& vertices) {

        triangles.clear();

        std::vector<int> indices(vertices.size());
        for (int i = 0; i < vertices.size(); i++) {
            indices[i] = i;
        }

        int n = vertices.size();
        while (n > 3) {
            bool earFound = false;

            for (int i = 0; i < n; i++) {
                int prev = (i + n - 1) % n;
                int next = (i + 1) % n;

                if (isEar(vertices, indices[i], indices[prev], indices[next])) {
                    // Dodaj trójkąt do listy meshu
                    triangles.push_back({ vertices[indices[prev]], vertices[indices[i]], vertices[indices[next]] });

                    // Usuń ucho z listy
                    indices.erase(indices.begin() + i);
                    n--;
                    earFound = true;
                    break;
                }
            }

            // Jeśli nie znaleziono ucha, zakończ (uniknięcie nieskończonej pętli)
            if (!earFound) break;
        }

        // Dodaj ostatni pozostały trójkąt
        if (n == 3) {
            triangles.push_back({ vertices[indices[0]], vertices[indices[1]], vertices[indices[2]] });
        }
    }

    std::vector < sf::Vector2f > getVertices() {

        std::vector< sf::Vector2f> vertices;
        vertices.clear();

        for (auto& tri : triangles) {
            vertices.push_back(tri.a);
            vertices.push_back(tri.b);
            vertices.push_back(tri.c);
        }

        return vertices;

    }

    void save() {
        std::wstring pathfile = L"assets\\" + name + L".msh";

        std::ofstream file(pathfile, std::ios::binary);

        uint32_t triangles_count = triangles.size();;

        file.write(reinterpret_cast <char*>(&triangles_count), sizeof(triangles_count));

        float t1x, t1y, t2x, t2y, t3x, t3y;

        for (auto& t : triangles) {

            t1x = t.a.x;
            t1y = t.a.y;

            t2x = t.b.x;
            t2y = t.b.y;

            t3x = t.c.x;
            t3y = t.c.y;

            file.write(reinterpret_cast <char*>(&t1x), sizeof(t1x));
            file.write(reinterpret_cast <char*>(&t1y), sizeof(t1y));

            file.write(reinterpret_cast <char*>(&t2x), sizeof(t2x));
            file.write(reinterpret_cast <char*>(&t2y), sizeof(t2y));

            file.write(reinterpret_cast <char*>(&t3x), sizeof(t3x));
            file.write(reinterpret_cast <char*>(&t3y), sizeof(t3y));
        }

        file.close();
    }

    void draw(sf::Vector2f position = sf::Vector2f(0,0)) {

        for (auto& tri : triangles) {

            drawThickLine(tri.a + position, tri.b + position, line_weight, line_color);
            drawThickLine(tri.b + position, tri.c + position, line_weight, line_color);
            drawThickLine(tri.c + position, tri.a + position, line_weight, line_color);
        }
    }

    void draw(float scale) {

        for (auto& tri : triangles) {

            drawThickLine(tri.a * scale, tri.b * scale, line_weight * scale, line_color);
            drawThickLine(tri.b * scale, tri.c * scale, line_weight * scale, line_color);
            drawThickLine(tri.c * scale, tri.a * scale, line_weight * scale, line_color);
        }
    }
};

std::vector < Mesh* > meshes;

void loadMeshes(const std::wstring folderPath=L"assets\\") {

    meshes.clear();

    std::wstring pathfile;
    std::wstring mesh_name;
    Mesh* mesh;
    Triangle triangle;

    for (const auto& entry : std::filesystem::recursive_directory_iterator(folderPath)) {
        if (entry.is_regular_file() && entry.path().extension() == ".msh") {

            pathfile = entry.path().wstring();

            mesh_name = pathfile;
            mesh_name.erase(0, folderPath.length());
            mesh_name.erase(mesh_name.length() - 4, string(".msh").length());
            //std::cout << "loaded mesh: " << mesh_name << "\n";

            mesh = new Mesh(mesh_name);

            std::ifstream file(pathfile, std::ios::binary);
            if (!file) {
                std::wcout << L"Nie można otworzyć pliku " << pathfile << L"\n";
                return;
            }

            uint32_t triangles_count;
            file.read(reinterpret_cast <char*>(&triangles_count), sizeof(triangles_count));
            
            float t1x, t1y, t2x, t2y, t3x, t3y;

            for (uint32_t i = 0; i < triangles_count; ++i) {
                file.read(reinterpret_cast <char*>(&t1x), sizeof(t1x));
                file.read(reinterpret_cast <char*>(&t1y), sizeof(t1y));

                file.read(reinterpret_cast <char*>(&t2x), sizeof(t2x));
                file.read(reinterpret_cast <char*>(&t2y), sizeof(t2y));

                file.read(reinterpret_cast <char*>(&t3x), sizeof(t3x));
                file.read(reinterpret_cast <char*>(&t3y), sizeof(t3y));

                triangle = Triangle();
                triangle.a = sf::Vector2f(t1x, t1y);
                triangle.b = sf::Vector2f(t2x, t2y);
                triangle.c = sf::Vector2f(t3x, t3y);

                //std::cout << triangle.a.x << " " << triangle.a.y << " ";
                //std::cout << triangle.b.x << " " << triangle.b.y << " ";
                //std::cout << triangle.c.x << " " << triangle.c.y << "\n\n";

                mesh->triangles.push_back(triangle);
            }

            file.close();
            meshes.push_back(mesh);

            //std::cout << "loaded mesh: " << mesh_name << "\n";
        }
    }
}


Mesh* getMesh(std::wstring name) {
    for (auto& m : meshes) {

        if (m->name == name) {
            return m;
        }
    }

    return nullptr;
}

GameObject* mesh_to_edit_gameobject = nullptr;
Mesh* mesh_to_edit;
std::vector< sf::Vector2f > mesh_to_edit_vertices;

#endif // Mesh_hpp
