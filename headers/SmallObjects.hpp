#ifndef SmallObjects_hpp
#define SmallObjects_hpp

class SmallObject : public GameObject {
public:

	SmallObject(string name, float width, float length, float height) : GameObject(name, width, length, height, false, ColliderType::Elipse) {
		type = GameObjectType::SmallObject;
	}

	SmallObject(GameObject* object) : GameObject(object) {
		type = GameObjectType::SmallObject;
	}

	~SmallObject() { }
};

std::vector < SmallObject* > smallObjects;

#endif