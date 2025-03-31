#ifndef Objects_hpp
#define Objects_hpp

class Object : public GameObject {
public:

	std::vector < SingleTexture* > textures;
	short frame;
	sf::Time last_action_time;
	sf::Sprite sprite;


	Object(string name, float width, float length, float height, bool collisioning, ColliderType ctype = ColliderType::Rectangle) : GameObject(name, 0, 0, width, length, height, collisioning, ctype) {
		type = GameObjectType::Object;
		
		textures.clear();
		textures = getAnimation(name);
		frame = 0;
		texture = textures[0];
		last_action_time = currentTime;

		sprite = sf::Sprite();
		sprite.setTexture(*texture->texture);
		sprite.setOrigin(texture->cx, texture->cy);

	}

	Object(GameObject* object, float x, float y) : GameObject(object, x, y) {
		type = GameObjectType::Object;
		
		textures.clear();
		textures = getAnimation(name);
		frame = 0;
		texture = textures[0];
		last_action_time = currentTime;

		sprite = sf::Sprite();
		sprite.setTexture(*texture->texture);
		sprite.setOrigin(texture->cx, texture->cy);
		sprite.setPosition(position);

	}

	~Object() { }

	virtual void setPosition(sf::Vector2f position) {
		GameObject::setPosition(position);
		sprite.setPosition(position);
	}

	virtual void update() {

		GameObject::update();

		if ((currentTime - last_action_time).asSeconds() > 0.1f) {
			
			last_action_time = currentTime;
			frame += 1;

			if (frame >= textures.size())
				frame = 0;

			texture = textures[frame];

			sprite.setTexture(*texture->texture);
		}

	}

	virtual void drawStatistics() {
		GameObject::drawStatistics();
	}

	virtual void draw() {

		window->draw(sprite);
	}
};

std::vector < Object* > objects;

#endif