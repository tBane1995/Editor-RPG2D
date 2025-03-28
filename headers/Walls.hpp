#ifndef Walls_hpp
#define Walls_hpp

class Wall : public GameObject {
public:
	sf::Sprite sprite;

	Wall(string name, float width, float length, float height) : GameObject(name, 0, 0, width, length, height, true, ColliderType::Rectangle) {
		type = GameObjectType::Wall;
		this->texture = getSingleTexture(name);
		sprite = sf::Sprite();
		sprite.setTexture(*texture->texture);
		sprite.setOrigin(texture->cx, texture->cy);
	}

	Wall(GameObject* object, float x, float y) : GameObject(object, x, y) {
		type = GameObjectType::Wall;
		this->texture = getSingleTexture(name);
		sprite = sf::Sprite();
		sprite.setTexture(*texture->texture);
		sprite.setOrigin(texture->cx, texture->cy);
		sprite.setPosition(position);
	}

	virtual ~Wall() {

	}

	virtual void setPosition(sf::Vector2f position) {
		GameObject::setPosition(position);
		sprite.setPosition(position);
	}

	virtual void update() {
		
	}

	virtual void drawStatistics() {
		GameObject::drawStatistics();
	}

	virtual void draw() {
		window->draw(sprite);
	}
};

std::vector < Wall* > walls;

#endif