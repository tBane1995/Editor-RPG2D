#ifndef Shaders_hpp
#define Shaders_hpp

using namespace std;

class Shader {
public:
	string name;
	sf::Shader* shader;

	Shader(string pathfile) {

		name = "";
		
		short i = short(pathfile.size()) - 6;
		while (i >= 0)
			name = pathfile[i--] + name;

		shader = new sf::Shader();
		shader->loadFromFile("assets\\" + pathfile, sf::Shader::Fragment);
		cout << "load shader: " << pathfile << " as: " << name << endl;
	}

	Shader(string name, string vertex_pathfile, string fragment_pathfile) {

		this->name = name;
		shader = new sf::Shader();
		shader->loadFromFile("assets\\" + vertex_pathfile, "assets\\" + fragment_pathfile);
		//cout << "load shader: " << vertex_pathfile << ", " << fragment_pathfile << " as: " << name << endl;
	}
};

std::vector < Shader* > shaders;

void loadShader(string name, string vertex_pathfile, string fragment_pathfile) {
	shaders.push_back(new Shader(name, vertex_pathfile, fragment_pathfile));
}

void loadShader(string pathfile) {
	shaders.push_back(new Shader(pathfile));
}

void loadShaders() {

	loadShader("shaders\\empty.frag");
	loadShader("shaders\\water.frag");
	loadShader("shaders\\lake", "shaders\\vertex.vert", "shaders\\lake.frag");
	loadShader("shaders\\river", "shaders\\vertex.vert", "shaders\\river.frag");
	loadShader("shaders\\palette_lake", "shaders\\vertex.vert", "shaders\\palette_lake.frag");
	loadShader("shaders\\shadow", "shaders\\vertex.vert", "shaders\\shadow.frag");
	loadShader("shaders\\circle.frag");
	loadShader("shaders\\jagged_circle.frag");
	loadShader("shaders\\circles.frag");
	loadShader("shaders\\renderer.frag");
	loadShader("shaders\\highlighted.frag");

}

Shader* getShader(string name) {

	for (auto& s : shaders) {
		if (s->name == name) {
			return s;
		}
	}

	std::cout << "error - get Shader - Shader: \"" << name << "\" not exists\n";
	return nullptr;
}

void updateShaders() {

	sf::Vector2f resolution(screenWidth, screenHeight);

	for(auto & s : shaders)
		s->shader->setUniform("time", currentTime.asSeconds());

	// lake shader
	Shader* s = getShader("shaders\\lake");
	s->shader->setUniform("resolution", resolution);

	// palette_lak
	s = getShader("shaders\\palette_lake");
	s->shader->setUniform("resolution", resolution);
	s->shader->setUniform("camPosition", cam->position);

	// river
	s = getShader("shaders\\river");
	s->shader->setUniform("resolution", resolution);
	s->shader->setUniform("direction", sf::Vector2f(1.0f, -1.0f));
}


#endif // !define Shaders_hpp
