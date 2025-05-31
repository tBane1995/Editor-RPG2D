#ifndef CharacterSideMenu_hpp
#define CharacterSideMenu_hpp

enum class ContextMenuState { Idle, Closing, Close };

class ContextMenu : public ElementGUI {
public:
	ContextMenuState _state;
	sf::Vector2f _position;
	sf::RectangleShape rect;
	std::vector < ButtonWithTextAndIcon* > _buttons;
	
	ContextMenu(GameObject* object) : ElementGUI() {

		_state = ContextMenuState::Idle;

		_position.x = worldMousePosition.x;
		_position.y = worldMousePosition.y;

		if (object == nullptr || selectedGameObjects.size() > 1) {
			loadDefaultMenu();
		}
		else if (object->type == GameObjectType::Character) {
			loadCharacterMenu(object);
		}else if (object->type == GameObjectType::Building) {
			loadBuildingMenu(object);
		}else if (object->type == GameObjectType::Furniture) {
			loadFurnitureMenu(object);
		}
		else if (object->type == GameObjectType::Door) {
			loadDoorMenu(object);
		}
		else {
			loadObjectMenu(object);
		}

		//std::cout << "selected GameObjects: " << selectedGameObjects.size() << "\n";

		// calculate max width of buttons
		short btn_width = 0;
		for (auto& btn : _buttons) {
			if (btn->rect.getSize().x > btn_width)
				btn_width = btn->rect.getSize().x;
		}

		// set the width for buttons
		sf::Vector2f btn_size(btn_width + 20, 30);
		for (auto& btn : _buttons) {
			btn->setRectSize(btn_size);
		}

		// positioning
		sf::Vector2f pos;
		pos.x = _position.x - cam->position.x;
		pos.y = _position.y - cam->position.y;

		for (short i = 0; i < _buttons.size(); i += 1) {
			_buttons[i]->setPosition(sf::Vector2f(pos.x, pos.y + i * 30));
		}


		sf::Vector2f size;
		size.x = _buttons.front()->rect.getSize().x;
		size.y = _buttons.front()->rect.getSize().y * _buttons.size();
		rect = sf::RectangleShape(size);
		rect.setPosition(_position);
	}

	~ContextMenu() {
		
		for (auto& btn : _buttons)
			delete btn;
	}

	void loadDefaultMenu() {

		if (selectedGameObjects.size() > 0) {
			ButtonWithTextAndIcon* btn_copy = new ButtonWithTextAndIcon(L"copy", getSingleTexture(L"GUI\\context_menu\\btn_default"));
			btn_copy->onclick_func = [this]() {
				clipboard->copy();
				};

			ButtonWithTextAndIcon* btn_remove = new ButtonWithTextAndIcon(L"remove", getSingleTexture(L"GUI\\context_menu\\btn_remove"));
			btn_remove->onclick_func = [this]() {

				for (auto& so : selectedGameObjects) {

					deleteGameObjectFromMainLists(so->_object);

					if (editor_state == EditorStates::MapEditor) {
						Chunk* chunk = nullptr;
						(so->_object->type == GameObjectType::Monster) ? chunk = mapa->getChunk(dynamic_cast<Monster*>(so->_object)->base) : chunk = mapa->getChunk(so->_object->position);

						if (chunk != nullptr)
							chunk->deleteGameObject(so->_object);
					}

					if (editor_state == EditorStates::BuildingEditor) {
						building_to_edit->deleteGameObject(so->_object);
					}

					delete so->_object;
					delete so;
				}

				selectedGameObjects.clear();
				};

			_buttons.push_back(btn_copy);
			_buttons.push_back(btn_remove);
		}
		else {
			ButtonWithTextAndIcon* btn_undo = new ButtonWithTextAndIcon(L"undo", getSingleTexture(L"GUI\\context_menu\\btn_default"));


			ButtonWithTextAndIcon* btn_paste = new ButtonWithTextAndIcon(L"paste", getSingleTexture(L"GUI\\context_menu\\btn_default"));
			btn_paste->onclick_func = [this]() {
				clipboard->paste();
				};

			_buttons.push_back(btn_undo);
			_buttons.push_back(btn_paste);
		}

		

		
	}

	void loadCharacterMenu(GameObject* object) {
		Character* character = dynamic_cast <Character*>(object);

		ButtonWithTextAndIcon* btn_edit = new ButtonWithTextAndIcon(L"edit", getSingleTexture(L"GUI\\context_menu\\btn_edit"));
		btn_edit->onclick_func = [this, character]() {
			dialogs.push_back(new CharacterInfoPanel(character));
			};

		ButtonWithTextAndIcon* btn_copy = new ButtonWithTextAndIcon(L"copy", getSingleTexture(L"GUI\\context_menu\\btn_default"));
		btn_copy->onclick_func = [this]() {
			clipboard->copy();
			};

		ButtonWithTextAndIcon* btn_cut = new ButtonWithTextAndIcon(L"cut", getSingleTexture(L"GUI\\context_menu\\btn_default"));
		btn_cut->onclick_func = [this]() {
			clipboard->cut();
			};

		ButtonWithTextAndIcon* btn_remove = new ButtonWithTextAndIcon(L"remove", getSingleTexture(L"GUI\\context_menu\\btn_remove"));
		btn_remove->onclick_func = [this, character]() {
			deleteGameObjectFromMainLists(character);
			if (editor_state == EditorStates::MapEditor) {
				Chunk* chunk = nullptr;
				chunk = mapa->getChunk(character->position);
				if (chunk != nullptr)
					chunk->deleteGameObject(character);
			}
			delete character;
			unselectGameObjects();
			};

		ButtonWithTextAndIcon* btn_cancel = new ButtonWithTextAndIcon(L"cancel", getSingleTexture(L"GUI\\context_menu\\btn_cancel"));

		_buttons.push_back(btn_edit);
		_buttons.push_back(btn_copy);
		_buttons.push_back(btn_cut);
		_buttons.push_back(btn_remove);
		_buttons.push_back(btn_cancel);
	}

	void loadBuildingMenu(GameObject* object) {
		Building* building = dynamic_cast <Building*>(object);

		// TO-DO
		ButtonWithTextAndIcon* btn_edit = new ButtonWithTextAndIcon(L"edit", getSingleTexture(L"GUI\\context_menu\\btn_edit"));
		btn_edit->onclick_func = [this, building]() {
			editor_state = EditorStates::BuildingEditorInit;
			building_to_edit = building;
			};

		ButtonWithTextAndIcon* btn_copy = new ButtonWithTextAndIcon(L"copy", getSingleTexture(L"GUI\\context_menu\\btn_default"));
		btn_copy->onclick_func = [this]() {
			clipboard->copy();
			};

		ButtonWithTextAndIcon* btn_cut = new ButtonWithTextAndIcon(L"cut", getSingleTexture(L"GUI\\context_menu\\btn_default"));
		btn_cut->onclick_func = [this]() {
			clipboard->cut();
			};

		ButtonWithTextAndIcon* btn_remove = new ButtonWithTextAndIcon(L"remove", getSingleTexture(L"GUI\\context_menu\\btn_remove"));
		btn_remove->onclick_func = [this, building]() {
			deleteGameObjectFromMainLists(building);
			Chunk* chunk = nullptr;
			chunk = mapa->getChunk(building->position);
			if (chunk != nullptr) {
				chunk->deleteGameObject(building);
			}
				
			delete building;
			unselectGameObjects();
			};
		
		ButtonWithTextAndIcon* btn_cancel = new ButtonWithTextAndIcon(L"cancel", getSingleTexture(L"GUI\\context_menu\\btn_cancel"));

		_buttons.push_back(btn_edit);
		_buttons.push_back(btn_copy);
		_buttons.push_back(btn_cut);
		_buttons.push_back(btn_remove);
		_buttons.push_back(btn_cancel);

	}

	void loadFurnitureMenu(GameObject* object) {
		ButtonWithTextAndIcon* btn_copy = new ButtonWithTextAndIcon(L"copy", getSingleTexture(L"GUI\\context_menu\\btn_default"));
		btn_copy->onclick_func = [this]() {
			clipboard->copy();
			};

		ButtonWithTextAndIcon* btn_cut = new ButtonWithTextAndIcon(L"cut", getSingleTexture(L"GUI\\context_menu\\btn_default"));
		btn_cut->onclick_func = [this]() {
			clipboard->cut();
			};

		ButtonWithTextAndIcon* btn_remove = new ButtonWithTextAndIcon(L"remove", getSingleTexture(L"GUI\\context_menu\\btn_remove"));
		btn_remove->onclick_func = [this, object]() {
			deleteGameObjectFromMainLists(object);
			building_to_edit->deleteGameObject(object);
			delete object;
			unselectGameObjects();
			};

		ButtonWithTextAndIcon* btn_cancel = new ButtonWithTextAndIcon(L"cancel", getSingleTexture(L"GUI\\context_menu\\btn_cancel"));

		_buttons.push_back(btn_copy);
		_buttons.push_back(btn_cut);
		_buttons.push_back(btn_remove);
		_buttons.push_back(btn_cancel);

	}

	void loadDoorMenu(GameObject* object) {

		Door* door = dynamic_cast<Door*>(object);

		ButtonWithTextAndIcon* btn_open_close;
		if (door->state == DoorState::Open || door->state == DoorState::Opening) {
			btn_open_close = new ButtonWithTextAndIcon(L"close", getSingleTexture(L"GUI\\context_menu\\btn_default"));

			btn_open_close->onclick_func = [this, door]() {
				door->close();
				};
		}
		else {

			btn_open_close = new ButtonWithTextAndIcon(L"open", getSingleTexture(L"GUI\\context_menu\\btn_default"));

			btn_open_close->onclick_func = [this, door]() {
				door->open();
				};
		}
			

		
		ButtonWithTextAndIcon* btn_copy = new ButtonWithTextAndIcon(L"copy", getSingleTexture(L"GUI\\context_menu\\btn_default"));
		btn_copy->onclick_func = [this]() {
			clipboard->copy();
			};

		ButtonWithTextAndIcon* btn_cut = new ButtonWithTextAndIcon(L"cut", getSingleTexture(L"GUI\\context_menu\\btn_default"));
		btn_cut->onclick_func = [this]() {
			clipboard->cut();
			};

		ButtonWithTextAndIcon* btn_remove = new ButtonWithTextAndIcon(L"remove", getSingleTexture(L"GUI\\context_menu\\btn_remove"));
		btn_remove->onclick_func = [this, object]() {

			deleteGameObjectFromMainLists(object);

			if (editor_state == EditorStates::MapEditor) {
				Chunk* chunk = nullptr;
				(object->type == GameObjectType::Monster) ? chunk = mapa->getChunk(dynamic_cast<Monster*>(object)->base) : chunk = mapa->getChunk(object->position);

				if (chunk != nullptr)
					chunk->deleteGameObject(object);
			}

			if (editor_state == EditorStates::BuildingEditor) {
				building_to_edit->deleteGameObject(object);
			}

			delete object;
			unselectGameObjects();
			};

		ButtonWithTextAndIcon* btn_edit_mesh = new ButtonWithTextAndIcon(L"edit mesh", getSingleTexture(L"GUI\\context_menu\\btn_default"));
		btn_edit_mesh->onclick_func = [this, object]() {
			mesh_to_edit_gameobject = object;
			editor_state = EditorStates::MeshEditorInit;
			};

		ButtonWithTextAndIcon* btn_cancel = new ButtonWithTextAndIcon(L"cancel", getSingleTexture(L"GUI\\context_menu\\btn_cancel"));

		_buttons.push_back(btn_open_close);
		_buttons.push_back(btn_copy);
		_buttons.push_back(btn_cut);
		_buttons.push_back(btn_remove);
		_buttons.push_back(btn_edit_mesh);
		_buttons.push_back(btn_cancel);

	}

	void loadObjectMenu(GameObject* object) {
		ButtonWithTextAndIcon* btn_copy = new ButtonWithTextAndIcon(L"copy", getSingleTexture(L"GUI\\context_menu\\btn_default"));
		btn_copy->onclick_func = [this]() {
			clipboard->copy();
			};

		ButtonWithTextAndIcon* btn_cut = new ButtonWithTextAndIcon(L"cut", getSingleTexture(L"GUI\\context_menu\\btn_default"));
		btn_cut->onclick_func = [this]() {
			clipboard->cut();
			};

		ButtonWithTextAndIcon* btn_remove = new ButtonWithTextAndIcon(L"remove", getSingleTexture(L"GUI\\context_menu\\btn_remove"));
		btn_remove->onclick_func = [this, object]() {

			deleteGameObjectFromMainLists(object);

			if (editor_state == EditorStates::MapEditor) {
				Chunk* chunk = nullptr;
				(object->type == GameObjectType::Monster) ? chunk = mapa->getChunk(dynamic_cast<Monster*>(object)->base) : chunk = mapa->getChunk(object->position);

				if (chunk != nullptr)
					chunk->deleteGameObject(object);
			}

			if (editor_state == EditorStates::BuildingEditor) {
				building_to_edit->deleteGameObject(object);
			}

			delete object;
			unselectGameObjects();
			};

		ButtonWithTextAndIcon* btn_edit_mesh = new ButtonWithTextAndIcon(L"edit mesh", getSingleTexture(L"GUI\\context_menu\\btn_default"));
		btn_edit_mesh->onclick_func = [this, object]() {
			mesh_to_edit_gameobject = object;
			editor_state = EditorStates::MeshEditorInit;
			};

		ButtonWithTextAndIcon* btn_cancel = new ButtonWithTextAndIcon(L"cancel", getSingleTexture(L"GUI\\context_menu\\btn_cancel"));

		_buttons.push_back(btn_copy);
		_buttons.push_back(btn_cut);
		_buttons.push_back(btn_remove);
		_buttons.push_back(btn_edit_mesh);
		_buttons.push_back(btn_cancel);

	}

	void cursorHover() {
		for (auto& btn : _buttons) {
			btn->cursorHover();
		}
	}

	void handleEvent(sf::Event& event) {

		for (auto& btn : _buttons) {
			btn->handleEvent(event);
		}

		if (event.type == sf::Event::MouseButtonPressed && !rect.getGlobalBounds().contains(worldMousePosition)) {
			_state = ContextMenuState::Closing;
		}

		if (event.type == sf::Event::MouseButtonReleased) {
			_state = ContextMenuState::Closing;
		}
	}

	void update() {

		sf::Vector2f pos;
		pos.x = _position.x - cam->position.x;
		pos.y = _position.y - cam->position.y;

		for (short i = 0; i < _buttons.size(); i += 1) {
			_buttons[i]->setPosition(sf::Vector2f(pos.x, pos.y + i * 30));
			_buttons[i]->update(true);
		}

		if (_state == ContextMenuState::Closing) {
			bool do_close = true;
			for (auto& btn : _buttons) {
				if (btn->state == ButtonState::Pressed) {
					do_close = false;
					break;
				}
			}

			if (do_close) {
				_state = ContextMenuState::Close;
			}
				
		}


	}

	void draw() {

		for (auto& btn : _buttons) {
			btn->draw();
		}
	}

};

ContextMenu* context_menu = nullptr;

#endif