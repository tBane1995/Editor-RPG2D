#ifndef Renderer_hpp
#define Renderer_hpp



class Renderer {
public:
	const short frames = 3;
	std::vector < sf::RenderTexture* > render_textures;

	sf::Shader* sh;
	sf::Color frame_color = sf::Color(0, 0, 0, 0);
	
	float brightness = 0.0f;	// -0.5f - 0.5f
	float contrast = 1.0f;		// 0.4f - 1.6f
	float gamma = 1.0f;			// TO-DO - must a set the gamma

	bool renderBorders;
	bool renderCoords;
	bool renderTilesBorders;
	bool renderActionRange;
	bool renderViewRange;
	bool renderColliders;
	bool renderMeshes;
	bool renderMonsterBases;
	bool renderBuildingsOutside;

	Renderer() {
		
		for (short i = 0; i < frames; i++) {
			sf::RenderTexture* r = new sf::RenderTexture();
			r->create(screenWidth, screenHeight);
			r->clear(frame_color);
			r->setView(cam->view);
			render_textures.push_back(r);
		}

		sh = getShader("shaders\\renderer")->shader;

		renderBorders = true;
		renderCoords = true;
		renderTilesBorders = false;
		renderActionRange = false;
		renderViewRange = false;
		renderColliders = false;
		renderMeshes = false;
		renderMonsterBases = false;
		renderBuildingsOutside = true;
		
	}

	~Renderer() {
		for (auto& r : render_textures)
			delete r;

		render_textures.clear();
	}

	sf::RenderTexture* getTheCurrentFrame() {
		return render_textures.back();
	}

	void update() {
		// delete the oldest texture
		delete render_textures.front();
		render_textures.erase(render_textures.begin());

		// add the new texure
		sf::RenderTexture* rtex = new sf::RenderTexture();
		rtex->create(screenWidth, screenHeight);
		rtex->clear(frame_color);
		rtex->setView(cam->view);
		render_textures.push_back(rtex);

	}
	
	void draw() {

		getTheCurrentFrame()->display();

		sh->setUniform("render_texture_0", render_textures[0]->getTexture());
		//sh->setUniform("render_texture_1", render_textures[1]->getTexture());
		//sh->setUniform("render_texture_2", render_textures[2]->getTexture());
		
		//(brightness >= 0.5f)? brightness = -0.5f : brightness += 0.001f;
		//(contrast >= 1.6f)? contrast = 0.4f : contrast += 0.001f;
		//(gamma >= 2.4f)? gamma = 0.4f : gamma += 0.005f;

		sh->setUniform("brightness", brightness);
		sh->setUniform("contrast", contrast);
		sh->setUniform("gamma", gamma);

		sf::Sprite renderer;
		renderer.setTexture(getTheCurrentFrame()->getTexture());
		renderer.setOrigin(screenWidth / 2, screenHeight / 2);
		renderer.setPosition(cam->position);

		window->draw(renderer, sh);
	}
};

Renderer* renderer = nullptr;

#endif