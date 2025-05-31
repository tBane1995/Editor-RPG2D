#ifndef Objects_hpp
#define Objects_hpp

class Object : public GameObject {
public:

	Object(std::wstring name, float width, float length, float height, bool collisioning, ColliderType ctype = ColliderType::Rectangle) : GameObject(name, width, length, height, collisioning, ctype) {
		type = GameObjectType::Object;
	}

	Object(GameObject* object) : GameObject(object) {
		type = GameObjectType::Object;
	}

	~Object() { }
	
};

std::vector < Object* > objects;

#endif