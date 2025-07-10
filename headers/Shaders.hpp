#ifndef Shaders_hpp
#define Shaders_hpp

using namespace std;

class Shader {
public:
	std::wstring name;
	sf::Shader* shader;

	Shader(std::wstring pathfile) {

		name = L"";
		
		short i = short(pathfile.size()) - 6;
		while (i >= 0)
			name = pathfile[i--] + name;

		shader = new sf::Shader();
		shader->loadFromFile(ConvertWideToUtf8(L"assets\\" + pathfile), sf::Shader::Fragment);
		std::wcout << L"load shader: " << pathfile << L" as: " << name << endl;
	}

	Shader(std::wstring name, std::wstring vertex_pathfile, std::wstring fragment_pathfile) {

		this->name = name;
		shader = new sf::Shader();
		shader->loadFromFile(ConvertWideToUtf8(L"assets\\" + vertex_pathfile), ConvertWideToUtf8(L"assets\\" + fragment_pathfile));
		//cout << "load shader: " << vertex_pathfile << ", " << fragment_pathfile << " as: " << name << endl;
	}
};

std::vector < Shader* > shaders;

void loadShader(std::wstring name, std::wstring vertex_pathfile, std::wstring fragment_pathfile) {
	shaders.push_back(new Shader(name, vertex_pathfile, fragment_pathfile));
}

void loadShader(std::wstring pathfile) {
	shaders.push_back(new Shader(pathfile));
}

void loadShaders() {

	loadShader(L"shaders\\empty.frag");
	loadShader(L"shaders\\water.frag");
	loadShader(L"shaders\\lake", L"shaders\\vertex.vert", L"shaders\\lake.frag");
	loadShader(L"shaders\\river", L"shaders\\vertex.vert", L"shaders\\river.frag");
	loadShader(L"shaders\\swamp", L"shaders\\vertex.vert", L"shaders\\swamp.frag");
	loadShader(L"shaders\\palette_lake", L"shaders\\vertex.vert", L"shaders\\palette_lake.frag");
	loadShader(L"shaders\\palette_swamp", L"shaders\\vertex.vert", L"shaders\\palette_swamp.frag");
	loadShader(L"shaders\\shadow", L"shaders\\vertex.vert", L"shaders\\shadow.frag");
	loadShader(L"shaders\\renderer.frag");
	loadShader(L"shaders\\highlighted.frag");
	

}

Shader* getShader(std::wstring name) {

	for (auto& s : shaders) {
		if (s->name == name) {
			return s;
		}
	}

	std::wcout << L"error - get Shader - Shader: \"" << name << L"\" not exists\n";
	return nullptr;
}

void updateShaders() {

	sf::Vector2f resolution(screenWidth, screenHeight);

	for(auto & s : shaders)
		s->shader->setUniform("time", currentTime.asSeconds());

	Shader* s;

	// lake shader
	s = getShader(L"shaders\\lake");
	s->shader->setUniform("resolution", resolution);

	// swamp shader
	s = getShader(L"shaders\\swamp");
	s->shader->setUniform("resolution", resolution);

	// river
	s = getShader(L"shaders\\river");
	s->shader->setUniform("resolution", resolution);
	s->shader->setUniform("direction", sf::Vector2f(1.0f, -1.0f));

	// palette_lak
	s = getShader(L"shaders\\palette_lake");
	s->shader->setUniform("resolution", resolution);
	s->shader->setUniform("camPosition", cam->position);

	// palette swamp
	s = getShader(L"shaders\\palette_swamp");
	s->shader->setUniform("resolution", resolution);
	s->shader->setUniform("camPosition", cam->position);
}


#endif // !define Shaders_hpp
