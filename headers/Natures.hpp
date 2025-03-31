#ifndef NatureObjects_hpp
#define NatureObjects_hpp

class Nature : public GameObject {
public:
	sf::Sprite sprite;

	Nature(string name, float width, float length, float height) : GameObject(name, 0, 0, width, length, height, true, ColliderType::Elipse) {
		type = GameObjectType::Nature;
		this->texture = getSingleTexture(name);
		sprite = sf::Sprite();
		sprite.setTexture(*texture->texture);
		sprite.setOrigin(texture->cx, texture->cy);
		sprite.setPosition(position);

	}

	Nature(GameObject* object, float x, float y) : GameObject(object, x, y) {
		type = GameObjectType::Nature;

		this->texture = getSingleTexture(name);

		sprite = sf::Sprite();
		sprite.setTexture(*texture->texture);
		sprite.setOrigin(texture->cx, texture->cy);
		sprite.setPosition(position);

	}

	virtual ~Nature() {
	
	}

	virtual void setPosition(sf::Vector2f position) {
		GameObject::setPosition(position);
		sprite.setPosition(position);
	}

	virtual void update() { 
		GameObject::update();
	}

	virtual void drawStatistics() {
		GameObject::drawStatistics();
	}

	virtual void draw() {

		window->draw(sprite);

		
	}
};

std::vector < Nature* > natures;

#endif