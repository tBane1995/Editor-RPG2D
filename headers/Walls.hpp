#ifndef Walls_hpp
#define Walls_hpp

class Wall : public GameObject {
public:

	Wall(std::wstring name, float width, float length, float height) : GameObject(name, width, length, height, true, ColliderType::Rectangle) {
		type = GameObjectType::Wall;
	}

	Wall(GameObject* object) : GameObject(object) {
		type = GameObjectType::Wall;
	}

	virtual ~Wall() {

	}
};

std::vector < Wall* > walls;

#endif