#ifndef Clipboard_hpp
#define Clipboard_hpp

enum class ClipboardState { Idle, Copy, Paste, Cut };

class Clipboard {
public:
	sf::Vector2f _position;
	ClipboardState _state;
	std::vector < MouseMovedGameObject* > _objects;

	Clipboard() {
		clear();
		_state = ClipboardState::Idle;
	}

	~Clipboard() {
		clear();
	}

	void clear() {
		for (auto& object : _objects) {
			delete object->_object;
			delete object;
		}

		_objects.clear();
	}

	void copy() {
		//std::cout << "copy\n";
		_state = ClipboardState::Copy;

		clear();

		// calculate center point
		sf::Vector2f center(0, 0);
		for (auto& so : selectedGameObjects) {
			center.x += so->_object->position.x;
			center.y += so->_object->position.y;
		}

		center.x /= selectedGameObjects.size();
		center.y /= selectedGameObjects.size();

		// copying the Selected GameObjects and set the offset
		for (auto& so : selectedGameObjects) {

			GameObject* object = getNewGameObject(so->_object);
			if (object != nullptr) {
				MouseMovedGameObject* moved_object = new MouseMovedGameObject(getNewGameObject(so->_object));
				sf::Vector2f offset = sf::Vector2f(so->_object->position.x - center.x, so->_object->position.y - center.y);
				moved_object->setOffset(offset);
				_objects.push_back(moved_object);
			}
			
		}

		/*
		std::cout << "zawartosc schowka:\n";
		for (auto& o : _objects) {
			std::cout << o->_object->name << " x=" << o->_object->position.x << " y=" << o->_object->position.y << "\n";
		}\*/
	}

	void cut() {
		//std::cout << "cut\n";
		_state = ClipboardState::Cut;
		copy();

		// TO-DO - remove objects
	}

	void paste() {
		//std::cout << "paste\n";
		_state = ClipboardState::Paste;
		//std::cout << "size: " << _objects.size() << "\n";
		 
		// paste GameObjects
		std::vector < MouseMovedGameObject* > objects_to_paste;
		sf::Vector2f offset;
		for (auto& obj : _objects) {
			MouseMovedGameObject* mv = new MouseMovedGameObject(getNewGameObject(obj->_object));
			mv->setOffset(obj->_offset);
			mv->update();
			objects_to_paste.push_back(mv);
		}

		painter->addGameObjectsToMapAndLists(objects_to_paste, true);
	}

	void update() {
		_state = ClipboardState::Idle;
	}
};

Clipboard* clipboard = nullptr;

#endif