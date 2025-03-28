#ifndef SmallObjects_hpp
#define SmallObjects_hpp

class SmallObject : public GameObject {
public:

	sf::Sprite sprite;

	SmallObject(string name, float width, float length, float height) : GameObject(name, 0, 0, width, length, height, false, ColliderType::Elipse) {
		type = GameObjectType::SmallObject;
		this->texture = getSingleTexture(name);
		sprite = sf::Sprite();
		sprite.setTexture(*texture->texture);
		sprite.setOrigin(texture->cx, texture->cy);
	}

	SmallObject(GameObject* object, float x, float y) : GameObject(object, x, y) {
		type = GameObjectType::SmallObject;
		this->texture = getSingleTexture(name);
		sprite = sf::Sprite();
		sprite.setTexture(*getSingleTexture(name)->texture);
		sprite.setOrigin(texture->cx, texture->cy);
		sprite.setPosition(position);

	}

	~SmallObject() { }

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

std::vector < SmallObject* > smallObjects;

#endif