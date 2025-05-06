#ifndef MouseMovedGameObjects_hpp
#define MouseMovedGameObjects_hpp

class Action {

};

class Move : public Action {

};

class History {

};

class MouseMovedGameObject {
public:
	GameObject* _object;
	sf::Vector2f _offset;

	MouseMovedGameObject(GameObject* object) {
		_object = object;
		_offset = sf::Vector2f(0, 0);
	}

	~MouseMovedGameObject() { }


	void setOffset(sf::Vector2f offset) {
		_offset = offset;
	}

	void update() {
		sf::Vector2f pos;
		pos.x = short(worldMousePosition.x + _offset.x) / short(tileSide) * short(tileSide);
		pos.y = short(worldMousePosition.y + _offset.y) / short(tileSide) * short(tileSide);

		_object->setPosition(pos);
		_object->update();
	}

	void draw() {
		_object->draw();
	}
};

#endif