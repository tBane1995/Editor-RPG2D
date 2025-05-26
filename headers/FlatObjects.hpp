#ifndef FlatObjects_hpp
#define FlatObjects_hpp

class FlatObject : public GameObject {
public:
	
	FlatObject(string name, float width, float length, float height ) : GameObject(name, width, length, height, false, ColliderType::Elipse) {
		type = GameObjectType::FlatObject;
	}

	FlatObject(GameObject* object) : GameObject(object) {
		type = GameObjectType::FlatObject;
	}

	virtual ~FlatObject() { }

};

std::vector < FlatObject* > flatObjects;


#endif