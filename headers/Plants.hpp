#ifndef Plants_hpp
#define Plants_hpp

enum class animState { stop, anim, end };

class Plant : public GameObject {
public:
	std::vector < SingleTexture* > textures;
	short current_texture;
	sf::Time time_last_frame;

	sf::Sprite sprite;

	animState state;
	sf::Time start_anim;
	sf::Time last_anim;
	short rotate;
	bool growing;

	Plant(string name, float width, float length, float height) : GameObject(name, 0, 0, width, length, height, false, ColliderType::Elipse) {
		textures.push_back(getSingleTexture("plants/grass_0"));
		textures.push_back(getSingleTexture("plants/grass_1"));

		sprite.setTexture(*textures[0]->texture);
		sprite.setOrigin(textures[0]->cx, textures[0]->cy);
		sprite.setPosition(position);

		current_texture = 0;
		time_last_frame = sf::Time::Zero;

		state = animState::stop;
	}

	Plant(GameObject* object, float x, float y) : GameObject(object, x, y) {

		for (auto& t : dynamic_cast<Plant*>(object)->textures) {
			textures.push_back(t);
		}
			
		sprite.setTexture(*textures[0]->texture);
		sprite.setOrigin(textures[0]->cx, textures[0]->cy);
		sprite.setPosition(position);

		current_texture = 0;
		time_last_frame = sf::Time::Zero;

		state = animState::stop;
	}

	virtual ~Plant() {

	}

	virtual void setPosition(sf::Vector2f position) {
		this->position = position;
		sprite.setPosition(position);
	}

	virtual void update(float dt) {
		/*
		if ((currentTime - time_last_frame).asSeconds() > 0.2f) {
			sprite.setTexture(*textures[current_texture]->texture);

			time_last_frame = currentTime;

			current_texture += 1;
			if (current_texture >= textures.size())
				current_texture = 0;
		}
		*/

		if (state == animState::stop && pointInEllipse(worldMousePosition.x, worldMousePosition.y, position.x, position.y, collider->width / 2.0f, collider->height / 2.0f)) {
			
			state = animState::anim;
			start_anim = currentTime;
			last_anim = currentTime;
			(rand() % 2 == 0) ? growing = true : growing = false;
			rotate = 0;
		}
		
		if (state == animState::end && !pointInEllipse(worldMousePosition.x, worldMousePosition.y, position.x, position.y, collider->width / 2.0f, collider->height / 2.0f)) {
			state = animState::stop;
		}
		else if ((currentTime - start_anim).asSeconds() > 0.3f) {
			state = animState::end;
			if ((currentTime - last_anim).asSeconds() > 0.001f) {

				if (rotate < 0) rotate += 1;
				else if (rotate > 0) rotate -= 1;

				last_anim = currentTime;

				sprite.setRotation(rotate);
			}

		}
		else if (state == animState::anim && (currentTime - last_anim).asSeconds() > 0.001f) {

			(growing == true) ? rotate += 1 : rotate -= 1;
				
			if (rotate > 10) growing = false;
			else if (rotate < -10) growing = true;

			last_anim = currentTime;

			sprite.setRotation(rotate);
			
		}

		

	}

	virtual void draw() {
		window->draw(sprite);
	}
};

std::vector < Plant* > plants;

#endif