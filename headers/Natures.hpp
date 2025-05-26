#ifndef NatureObjects_hpp
#define NatureObjects_hpp

class Nature : public GameObject {
public:

	Nature(string name, float width, float length, float height) : GameObject(name, width, length, height, true, ColliderType::Elipse) {
		type = GameObjectType::Nature;
	}

	Nature(GameObject* object) : GameObject(object) {
		type = GameObjectType::Nature;
	}

	virtual ~Nature() {
	
	}
};

std::vector < Nature* > natures;

#endif