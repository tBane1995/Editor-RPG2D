#ifndef CharacterInfoPanel_hpp
#define CharacterInfoPanel_hpp

class CharacterInfoPanel : public Panel {
public:
	Character* _character;


	class CharacterInfoPage {
	public:
		CharacterInfoPanel* parent;

		CharacterInfoPage(CharacterInfoPanel* parent) {
			this->parent = parent;
		}

		virtual ~CharacterInfoPage() { }
		virtual void cursorHover() { }
		virtual void handleEvent(sf::Event& event) { }
		virtual void update() { }
		

		virtual void draw() { 
		}
	};


	class Statistics : public CharacterInfoPage {
	public:

		sf::RectangleShape rect;

		std::vector < TextArea* > stats_names;
		std::vector < TextArea* > stats_values;

		Statistics(CharacterInfoPanel* parent) : CharacterInfoPage(parent) {
			
			// some parameters
			float panel_height = parent->rect.getSize().y;
			float menu_height = parent->menu[0]->texture->texture->getSize().y;
			float margin = 4;

			// background rect
			sf::Vector2f rect_size;
			rect_size.x = parent->rect.getSize().x - 2 * corner_size;
			rect_size.y = parent->rect.getSize().y - 2 * corner_size - menu_height - margin;

			sf::Vector2f rect_position;
			rect_position.x = parent->position.x;
			rect_position.y = parent->position.y + menu_height / 2 + margin / 2;

			rect = sf::RectangleShape(rect_size);
			rect.setFillColor(panelColor_dark);
			rect.setOrigin(rect_size.x / 2, rect_size.y / 2);
			rect.setPosition(rect_position + cam->position);
			
			// stats
			stats_names.push_back(new TextArea(L"NAME"));
			stats_values.push_back(new TextArea(ConvertUtf8ToWide(parent->_character->name)));

			stats_names.push_back(new TextArea(L"ID"));
			stats_values.push_back(new TextArea(L"0"));

			//
			stats_names.push_back(new TextArea(L""));
			stats_values.push_back(new TextArea(L""));
			//

			stats_names.push_back(new TextArea(L"LEVEL"));
			stats_values.push_back(new TextArea(std::to_wstring(parent->_character->LEVEL)));

			stats_names.push_back(new TextArea(L"EXPERIENCE"));
			stats_values.push_back(new TextArea(std::to_wstring(parent->_character->EXPERIENCE)));

			stats_names.push_back(new TextArea(L"SKILL POINTS"));
			stats_values.push_back(new TextArea(std::to_wstring(parent->_character->SKILL_POINTS)));

			//
			stats_names.push_back(new TextArea(L""));
			stats_values.push_back(new TextArea(L""));
			//

			stats_names.push_back(new TextArea(L"CURRENT HP"));
			stats_values.push_back(new TextArea(std::to_wstring(parent->_character->attributes[Attribute::HP])));

			stats_names.push_back(new TextArea(L"MAX HP"));
			stats_values.push_back(new TextArea(std::to_wstring(parent->_character->attributes[Attribute::HP_max])));

			stats_names.push_back(new TextArea(L"CURRENT MANA"));
			stats_values.push_back(new TextArea(std::to_wstring(parent->_character->attributes[Attribute::MP])));

			stats_names.push_back(new TextArea(L"MAX MANA"));
			stats_values.push_back(new TextArea(std::to_wstring(parent->_character->attributes[Attribute::MP_max])));

			stats_names.push_back(new TextArea(L"STRENGTH"));
			stats_values.push_back(new TextArea(std::to_wstring(parent->_character->attributes[Attribute::STRENGTH])));

			stats_names.push_back(new TextArea(L"DEXTERITY"));
			stats_values.push_back(new TextArea(std::to_wstring(parent->_character->attributes[Attribute::DEXTERITY])));

			stats_names.push_back(new TextArea(L"INTELLIGENCE"));
			stats_values.push_back(new TextArea(std::to_wstring(parent->_character->attributes[Attribute::INTELLIGENCE])));

			//
			stats_names.push_back(new TextArea(L""));
			stats_values.push_back(new TextArea(L""));
			//

			stats_names.push_back(new TextArea(L"ACTION RANGE"));
			stats_values.push_back(new TextArea(std::to_wstring(parent->_character->action_range)));

			stats_names.push_back(new TextArea(L"VIEW RANGE"));
			stats_values.push_back(new TextArea(std::to_wstring(parent->_character->view_range)));

			//
			stats_names.push_back(new TextArea(L""));
			stats_values.push_back(new TextArea(L""));
			//

			stats_names.push_back(new TextArea(L"ATTACK"));
			stats_values.push_back(new TextArea(L"0"));

			stats_names.push_back(new TextArea(L"DEFEND"));
			stats_values.push_back(new TextArea(L"0"));


			sf::Vector2f pos;
			float start_pos_y = parent->position.y - panel_height / 2.0f + margin + corner_size + menu_height + margin + corner_size;
			for (int i = 0; i < stats_names.size(); i++) {

				pos.y = start_pos_y +  i * stats_names[0]->getLineHeight();
				stats_names[i]->setBackgroundColor(panelColor_dark);
				pos.x = parent->position.x - parent->rect.getSize().x / 2.0f + corner_size + corner_size;
				stats_names[i]->setPosition(sf::Vector2f(pos.x, pos.y));

				stats_values[i]->setBackgroundColor(panelColor_dark);
				pos.x = parent->position.x + parent->rect.getSize().x / 2.0f - corner_size - corner_size - stats_values[i]->getSize().x;
				stats_values[i]->setPosition(sf::Vector2f(pos.x, pos.y));
			}
		}

		~Statistics() {
			
			for (auto& sn : stats_names)
				delete sn;

			for (auto& sv : stats_values)
				delete sv;
		}

		virtual void cursorHover() { }
		virtual void handleEvent(sf::Event& event) { }
		virtual void update() { }

		virtual void draw() {
		
			window->draw(rect);
			drawFrame(rect.getPosition() - cam->position, rect.getSize());

			//std::cout << "draw Statistics\n";
			for (auto& sn : stats_names)
				sn->draw();

			for (auto& sv : stats_values)
				sv->draw();
		}
	};

	class Layout : public CharacterInfoPage {
	public:

		class DirectionButton : public ButtonWithImage {
		public:
			sf::Sprite sprite;

			DirectionButton(SingleTexture* texture, sf::Vector2f position, CharacterInfoPanel* parent, short direction) : ButtonWithImage(getSingleTexture("GUI\\character_menu\\layout_slot"), position) {

				sprite = sf::Sprite();
				sprite.setTexture(*texture->texture);
				sprite.setOrigin(texture->texture->getSize().x/2, texture->texture->getSize().y/2);
				sprite.setPosition(position.x + cam->position.x, position.y + cam->position.y);

				onclick_func = [this, parent, direction]() {
					parent->_character->direction = direction;
					};

				hover_func = [this, texture, direction]() {

					if (tip == nullptr || (tip != nullptr && tip->btn != this)) {
						sf::Vector2f pos;
						pos.x = this->position.x + texture->texture->getSize().x / 4.0f;
						pos.y = this->position.y + texture->texture->getSize().y / 4.0f;
						if (tip != nullptr)
							delete tip;

						std::wstring dir_string;
						if (direction == 0) dir_string = L"to north";
						if (direction == 1) dir_string = L"to east";
						if (direction == 2) dir_string = L"to south";
						if (direction == 3) dir_string = L"to west";

						tip = new Tip(dir_string, pos, this);
					}
					};
			}

			void draw() {
				ButtonWithImage::draw();
				window->draw(sprite);
			}
		};

		class LayoutButton : public ButtonWithImage {
		public:
			
			std::string body_name;
			sf::Sprite sprite;

			LayoutButton(SingleTexture* texture, sf::Vector2f position, std::string body_name = "sets\\body\\hero") : ButtonWithImage(getSingleTexture("GUI\\character_menu\\layout_slot"), position) {

				this->body_name = body_name;

				sprite = sf::Sprite();
				sprite.setTexture(*texture->texture);
				sprite.setOrigin(texture->texture->getSize().x/2, texture->texture->getSize().y/2);
				sprite.setPosition(position.x + cam->position.x, position.y + cam->position.y);
			}

			void draw() {
				ButtonWithImage::draw();
				window->draw(sprite);
			}
		};

		std::vector < ButtonWithImage* > buttons;
		sf::Sprite preview;
		sf::RectangleShape rect;
		
		Layout(CharacterInfoPanel* parent) : CharacterInfoPage(parent) {
			
			// some parameters
			float panel_height = parent->rect.getSize().y;
			float menu_height = parent->menu[0]->texture->texture->getSize().y;
			float margin = 4;

			// background rect
			sf::Vector2f rect_size;
			rect_size.x = parent->rect.getSize().x - 2 * corner_size;
			rect_size.y = parent->rect.getSize().y - 2 * corner_size - menu_height - margin;

			sf::Vector2f rect_position;
			rect_position.x = parent->position.x;
			rect_position.y = parent->position.y + menu_height/2 + margin/2;

			rect = sf::RectangleShape(rect_size);
			rect.setFillColor(panelColor_dark);
			rect.setOrigin(rect_size.x / 2, rect_size.y / 2);
			rect.setPosition(rect_position+cam->position);

			// load the Bodies
			std::vector < std::filesystem::directory_entry > sets;
			for (auto& entry : std::filesystem::directory_iterator("assets\\sets\\body"))
				sets.push_back(entry);

			std::sort(sets.begin(), sets.end(), [](const auto& a, const auto& b) { return a.path().filename().string() < b.path().filename().string(); });

			

			sf::Vector2f preview_size(parent->_character->texture->texture->getSize().x*2.0f, parent->_character->texture->texture->getSize().y * 2.0f);
			
			float preview_margin = margin;
			sf::Vector2f btn_size(80, 80);
			
			// create Preview
			sf::Vector2f preview_pos;
			preview_pos.x = parent->position.x;
			preview_pos.y = parent->position.y - panel_height/2.0f + corner_size + preview_margin + menu_height + corner_size + preview_margin + preview_size.y / 2.0f;
			preview.setTexture(*parent->_character->sprite.getTexture());
			preview.setOrigin(32, 32);
			preview.setScale(2.0f, 2.0f);
			preview.setPosition(preview_pos.x + cam->position.x, preview_pos.y + cam->position.y);

			// create Buttons
			sf::Vector2f start_pos;
			start_pos.x = parent->position.x - float(btn_size.x * 4) / 2.0f + btn_size.x / 2.0f;
			start_pos.y = parent->position.y + parent->rect.getSize().y / 2 - 3 * (btn_size.y) - (btn_size.y) - corner_size;

			// direction buttons
			sf::Vector2f btn_pos;
			btn_pos.y = start_pos.y;

			btn_pos.x = start_pos.x + (0) * (btn_size.x);
			DirectionButton* left = new DirectionButton(getSingleTexture("GUI\\character_menu\\direction_left"), btn_pos, parent, 3);
			buttons.push_back(left);

			btn_pos.x = start_pos.x + (1) * (btn_size.x);
			DirectionButton* bottom = new DirectionButton(getSingleTexture("GUI\\character_menu\\direction_bottom"), btn_pos, parent, 2);
			buttons.push_back(bottom);

			btn_pos.x = start_pos.x + (2) * (btn_size.x);
			DirectionButton* top = new DirectionButton(getSingleTexture("GUI\\character_menu\\direction_top"), btn_pos, parent, 0);
			buttons.push_back(top);

			btn_pos.x = start_pos.x + (3) * (btn_size.x);
			DirectionButton* right = new DirectionButton(getSingleTexture("GUI\\character_menu\\direction_right"), btn_pos, parent, 1);
			buttons.push_back(right);

			// layout buttons
			for (short i = 0; i < sets.size(); i++) {
				
				btn_pos.x = start_pos.x + (i%4)*(btn_size.x);
				btn_pos.y = parent->position.y + parent->rect.getSize().y/2 + (i / 4 - 2) * (btn_size.y) - (btn_size.y) - corner_size;
				std::string body_name = "sets\\body\\" + sets[i].path().filename().string();
				SingleTexture* tex = getSingleTexture(body_name + "\\attackBottom0");
				LayoutButton* btn = new LayoutButton(tex, btn_pos, body_name);
				
				btn->onclick_func = [this, btn]() {
					this->parent->_character->bodyset = btn->body_name;
					this->parent->_character->loadBodySet();
					};

				btn->hover_func = [this, btn, tex]() {
					
					if (tip == nullptr || (tip != nullptr && tip->btn != btn)) {
						sf::Vector2f pos;
						pos.x = btn->position.x + tex->texture->getSize().x / 4.0f;
						pos.y = btn->position.y + tex->texture->getSize().y / 4.0f;
						if (tip != nullptr)
							delete tip;
						tip = new Tip(ConvertUtf8ToWide(getShortName(btn->body_name)), pos, btn);
					}
					};

				buttons.push_back(btn);
			}
		}

		~Layout() {

			for (auto& btn : buttons) {

				if (tip != nullptr && tip->btn == btn) {
					delete tip;
					tip = nullptr;
				}

				delete btn;
			}

			
		}

		virtual void cursorHover() {
		
			for (auto& btn : buttons) {
				btn->cursorHover();
			}
		}

		virtual void handleEvent(sf::Event& event) {
			for (auto& btn : buttons)
				btn->handleEvent(event);
		}

		virtual void update() {
			for (auto& btn : buttons)
				btn->update();

			preview.setTexture(*parent->_character->sprite.getTexture());
		}

		virtual void draw() {

			window->draw(rect);
			drawFrame(rect.getPosition()-cam->position, rect.getSize());

			window->draw(preview);
		 
			for (auto& btn : buttons)
				btn->draw();
		}
	};

	class Equipment : public CharacterInfoPage {
	public:
		
		class Slot : public ButtonWithImage {
		public:
			Item* _item;
			sf::Sprite sprite;

			Slot(SingleTexture* texture, sf::Vector2f position) : ButtonWithImage(texture, position) {
				_item = nullptr;

				sprite = sf::Sprite();
				sprite.setPosition(position.x + cam->position.x, position.y + cam->position.y);
			}

			~Slot() {

			}

			void setItem(Item* item) {
				_item = item;

				sprite = sf::Sprite();
				
				sprite.setPosition(position.x + cam->position.x, position.y + cam->position.y);

				if (_item != nullptr) {
					sprite.setTexture(*_item->texture->texture);
					sprite.setOrigin(24, 24);
					sprite.setTextureRect(sf::IntRect(8, 8, 48, 48));
				}
					

				
			}

			void draw() {
				ButtonWithImage::draw();
				window->draw(sprite);
			}
		};

		sf::RectangleShape rect;

		sf::Sprite preview;
		sf::Vector2i slots_count = sf::Vector2i(6, 6);
		std::vector < Slot* > slots;
		std::vector < Item* > items_list;
		Scrollbar* scrollbar;

		Equipment(CharacterInfoPanel* parent) : CharacterInfoPage(parent) { 
			slots.clear();

			// some parameters
			float panel_height = parent->rect.getSize().y;
			float menu_height = parent->menu[0]->texture->texture->getSize().y;
			float margin = 4;

			// background rect
			sf::Vector2f rect_size;
			rect_size.x = parent->rect.getSize().x - 2 * corner_size;
			rect_size.y = parent->rect.getSize().y - 2 * corner_size - menu_height - margin;

			sf::Vector2f rect_position;
			rect_position.x = parent->position.x;
			rect_position.y = parent->position.y + menu_height / 2 + margin / 2;

			rect = sf::RectangleShape(rect_size);
			rect.setFillColor(panelColor_dark);
			rect.setOrigin(rect_size.x / 2, rect_size.y / 2);
			rect.setPosition(rect_position + cam->position);

			// 
			SingleTexture* slot_texture = getSingleTexture("GUI\\character_menu\\item_slot");
			sf::Vector2f preview_size(parent->_character->texture->texture->getSize().x * 2.0f, parent->_character->texture->texture->getSize().y * 2.0f);
			float preview_margin = margin;
			sf::Vector2f slot_size(slot_texture->texture->getSize());
			float border_width = 6;

			// create Preview
			sf::Vector2f preview_pos;
			preview_pos.x = parent->position.x;
			preview_pos.y = parent->position.y - panel_height / 2.0f + corner_size + preview_margin + menu_height + corner_size + preview_margin + preview_size.y / 2.0f;
			preview.setTexture(*parent->_character->sprite.getTexture());
			preview.setOrigin(32, 32);
			preview.setScale(2.0f, 2.0f);
			preview.setPosition(preview_pos.x + cam->position.x, preview_pos.y + cam->position.y);

			// create Slots
			for (short y = 0; y < slots_count.y; y += 1) {
				for (short x = 0; x < slots_count.x; x += 1) {
					sf::Vector2f pos;
					pos.x = parent->position.x + border_part_size.x + corner_size - (float(slots_count.x)/2.0f - float(x)) * slot_size.x + corner_size;
					pos.y = parent->position.y + panel_height/2.0f - 2*corner_size - float(slots_count.y - y) *slot_size.y + slot_size.y/2.;
					Slot* slot = new Slot(slot_texture, pos);
					slot->onclick_func = [slot, parent]() {
						if (slot->_item != nullptr) {
							
							// TO-DO - it is under rewrite to parent->_character->useItem();
							if (slot->_item->type == ItemType::helmet) {
								(parent->_character->helmet != slot->_item) ? parent->_character->helmet = slot->_item : parent->_character->helmet = nullptr;
								parent->_character->loadHelmet();
							}

							if (slot->_item->type == ItemType::armor) {
								(parent->_character->armor != slot->_item) ? parent->_character->armor = slot->_item : parent->_character->armor = nullptr;
								parent->_character->loadArmor();
							}

							if (slot->_item->type == ItemType::pants) {
								(parent->_character->pants != slot->_item) ? parent->_character->pants = slot->_item : parent->_character->pants = nullptr;
								parent->_character->loadPants();
							}

							if (slot->_item->type == ItemType::weapon) {
								(parent->_character->rightHand != slot->_item) ? parent->_character->rightHand = slot->_item : parent->_character->rightHand = nullptr;
								parent->_character->loadRightHand();
							}

							if (slot->_item->type == ItemType::shield) {
								(parent->_character->leftHand != slot->_item) ? parent->_character->leftHand = slot->_item : parent->_character->leftHand = nullptr;
								parent->_character->loadLeftHand();
							}
							//////////////////
						}

					};

					slot->hover_func = [slot, parent]() {
		
						if (slot->_item != nullptr) {
							if (tip == nullptr || (tip != nullptr && tip->btn != slot)) {
								sf::Vector2f pos;
								pos.x = slot->position.x + slot->texture->texture->getSize().x / 4.0f;
								pos.y = slot->position.y + slot->texture->texture->getSize().y / 4.0f;
								if (tip != nullptr)
									delete tip;
								tip = new Tip(ConvertUtf8ToWide(getShortName(slot->_item->name)), pos, slot);
							}
						}
						};

					slots.push_back(slot);
				}
			}

			setItemsToSlots();

			sf::Vector2f scrollbar_size(16, slots_count.y*64);
			sf::Vector2f scrollbar_position;
			scrollbar_position.x = parent->position.x + parent->rect.getSize().x / 2.0f - 16 - border_width - corner_size;
			scrollbar_position.y = slots.front()->position.y - slots.front()->texture->texture->getSize().y / 2.0f;
			scrollbar = new Scrollbar(scrollbar_size, scrollbar_position, 0, items_list.size(), 0, slots_count.x*slots_count.y);
		}

		~Equipment() {
			for (auto& slot : slots) {

				if (tip != nullptr && tip->btn == slot) {
					delete tip;
					tip = nullptr;
				}

				delete slot;
			}
				

			slots.clear();

			delete scrollbar;
			scrollbar = nullptr;
		}

		void setItemsToSlots() {
			items_list.clear();
			for (Item* item : items) {
				if (item->type == ItemType::helmet || item->type == ItemType::armor || item->type == ItemType::pants || item->type == ItemType::weapon || item->type == ItemType::shield)
					items_list.push_back(item);
			}

			for (int i = 0; i < 36; i++) {
				if (i < items_list.size()) {
					slots[i]->setItem(items_list[i]);
				}
			}
		}

		virtual void cursorHover() { 
			for (auto& slot : slots) {
				slot->cursorHover();
			}
		}

		virtual void handleEvent(sf::Event& event) {
			scrollbar->handleEvent(event);
			setItemsToSlots();

			for (auto& slot : slots)
				slot->handleEvent(event);
		}

		virtual void update() {
			scrollbar->update();
			preview.setTexture(*parent->_character->sprite.getTexture());

			for (auto& slot : slots)
				slot->update();
		}

		virtual void draw() {

			window->draw(rect);
			drawFrame(rect.getPosition() - cam->position, rect.getSize());

			for (auto& slot : slots) {
				slot->draw();
			}

			scrollbar->draw();
			window->draw(preview);
		}
	};

	class Inventory : public CharacterInfoPage {
	public:
		Inventory(CharacterInfoPanel* parent) : CharacterInfoPage(parent) { }
		~Inventory() { }
		virtual void cursorHover() { }
		virtual void handleEvent(sf::Event& event) { }
		virtual void update() { }
		
		virtual void draw() {
		}
	};

	class Dialogues : public CharacterInfoPage {
	public:

		class AnswerText : public TextArea, public ElementGUI {
		public:

			ButtonState state;
			std::function<void()> onclick_func;
			sf::Time clickTime;

			AnswerText(std::wstring text, sf::Vector2f position, float line_length, sf::Vector2f size) : TextArea(text, position, line_length, size) {

				state = ButtonState::Idle;
				clickTime = currentTime;
			}

			~AnswerText() { }

			void unclick() {
				state = ButtonState::Idle;
				setBackgroundColor(panelColor_medium);
				setRectColor(panelColor_medium);
			}

			void hover() {

				state = ButtonState::Hover;
				setBackgroundColor(panelColor_normal);
				setRectColor(panelColor_normal);
				GUIwasHover = true;
			}

			void click() {

				state = ButtonState::Pressed;
				setBackgroundColor(panelColor_medium);
				setRectColor(panelColor_medium);
				GUIwasClicked = true;
				clickTime = currentTime;
			}

			void cursorHover() {
				if (mouse_state != MouseState::Selecting) {
					float w = rect.getSize().x;
					float h = rect.getSize().y;
					float x = rect.getPosition().x;
					float y = rect.getPosition().y;

					if (worldMousePosition.x > x && worldMousePosition.x < x + w &&
						worldMousePosition.y > y && worldMousePosition.y < y + h) {

						ElementGUI_hovered = this;
					}
				}
			}

			void update(bool hover_action = true) {

				rect.setPosition(position.x + cam->position.x, position.y + cam->position.y);

				if (state == ButtonState::Pressed) {
					if ((currentTime - clickTime).asSeconds() > 0.05f) {
						if (onclick_func)
							onclick_func();

						unclick();
					}

				}
				else if (hover_action && ElementGUI_hovered == this) {
					hover();
				}
				else
					unclick();


			}

			void handleEvent(sf::Event& event) {

				float w = rect.getSize().x;
				float h = rect.getSize().y;
				float x = rect.getPosition().x;
				float y = rect.getPosition().y;

				if (worldMousePosition.x > x && worldMousePosition.x < x + w &&
					worldMousePosition.y > y && worldMousePosition.y < y + h) {

					if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
						ElementGUI_pressed = this;
					}
					else if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left) {
						if (ElementGUI_pressed == this) {
							click();
						}
					}
				}

			}
		};

		sf::RectangleShape rect;

		Dialogue* dialogue;
		DialogueOption* current_dialogue_option;

		TextArea* dialogue_textarea;
		sf::Vector2f dialogue_textarea_position;
		sf::Vector2f dialogue_textarea_size;

		ButtonWithImage* btn_prev;
		ButtonWithImage* btn_next;

		short dialogues_answers_count;
		std::vector < AnswerText* > dialogue_answers;
		
		short selected_dialogue_option_index;

		Dialogues(CharacterInfoPanel* parent) : CharacterInfoPage(parent) { 
			
			// some parameters
			float menu_height = parent->menu[0]->texture->texture->getSize().y;
			float margin = 4;

			// background rect
			sf::Vector2f rect_size;
			rect_size.x = parent->rect.getSize().x - 2 * corner_size;
			rect_size.y = parent->rect.getSize().y - 2 * corner_size - menu_height - margin;

			sf::Vector2f rect_position;
			rect_position.x = parent->position.x;
			rect_position.y = parent->position.y + menu_height / 2 + margin / 2;

			rect = sf::RectangleShape(rect_size);
			rect.setFillColor(panelColor_dark);
			rect.setOrigin(rect_size.x / 2, rect_size.y / 2);
			rect.setPosition(rect_position + cam->position);

			// dialogue
			dialogue = parent->_character->dialogue;
			current_dialogue_option = dialogue->options.front();
			selected_dialogue_option_index = -1;

			// dialogue text
			TextArea* test_text = new TextArea(L"line1\nline2\nline3\nline4\nline5\nline6\nline7\nline8");	// 8 lines
			dialogue_textarea_size = sf::Vector2f(parent->rect.getSize().x - 6 * corner_size, test_text->getSize().y);
			dialogue_textarea_position = sf::Vector2f(-dialogue_textarea_size.x / 2, -parent->rect.getSize().y/2.0f + dialog_border_width + corner_size + menu_height + corner_size + margin);			
			delete test_text;

			dialogue_textarea = new TextArea(current_dialogue_option->text, dialogue_textarea_position, dialogue_textarea_size.x, dialogue_textarea_size);
			dialogue_textarea->setFont(dialogueFont);
			dialogue_textarea->setBackgroundColor(panelColor_medium);
			dialogue_textarea->setRectColor(panelColor_medium);

			// prev and next buttons
			btn_prev = new ButtonWithImage(getSingleTexture("GUI\\character_menu\\dialogue_prev"));
			btn_next = new ButtonWithImage(getSingleTexture("GUI\\character_menu\\dialogue_next"));
			
			float pos_y = dialogue_textarea->position.y + dialogue_textarea->getSize().y + corner_size + btn_prev->texture->texture->getSize().y/2 + margin;
			float dx = parent->rect.getSize().x / 2 - 64;
			
			btn_prev->setPosition(sf::Vector2f(-dx, pos_y));
			btn_next->setPosition(sf::Vector2f(dx, pos_y));
			
			// dialogue answers
			test_text = new TextArea(L"line1\nline2");	// 2 lines
			sf::Vector2f dialogue_answer_size(dialogue_textarea_size.x, test_text->getSize().y);
			delete test_text;

			dialogues_answers_count = 5;

			for (short i = 0; i < dialogues_answers_count; i += 1) {
				sf::Vector2f pos;
				pos.x = -dialogue_textarea_size.x / 2;
				pos.y = parent->rect.getSize().y / 2 - 2.0f * corner_size + margin + (dialogue_answer_size.y + margin) * float(-dialogues_answers_count + i) - corner_size;

				AnswerText* op = new AnswerText(L"", pos, dialogue_answer_size.x, dialogue_answer_size);
				dialogue_answers.push_back(op);
			}

			loadDialogueAnswersTexts();

		}

		~Dialogues() {
			delete dialogue_textarea;

			for (auto& answer : dialogue_answers)
				delete answer;

			delete btn_prev;
			delete btn_next;
		}

		void loadDialogueOptionText() {
			this->dialogue_textarea->setWstring(current_dialogue_option->text);
		}

		void loadDialogueAnswersTexts() {
			
			if (current_dialogue_option->answers.empty()) {

				dialogue_answers.front()->setWstring(L"continue");
				dialogue_answers.front()->onclick_func = [this]() {
					current_dialogue_option = dialogue->options.front();
					loadDialogueOptionText();
					loadDialogueAnswersTexts();
					};

				for (short i = 1; i < dialogues_answers_count; i++) {
					dialogue_answers[i]->setWstring(L"");
					dialogue_answers[i]->onclick_func = []() {};
				}
					
			}
			else {
				for (short i = 0; i < dialogues_answers_count; i++) {
					
					if (i < current_dialogue_option->answers.size()) {
						dialogue_answers[i]->setWstring(current_dialogue_option->answers[i]->text);
						dialogue_answers[i]->onclick_func = [this, i]() {
							if (!current_dialogue_option->answers.empty() && current_dialogue_option->answers[i]->next_option != nullptr)
								current_dialogue_option = current_dialogue_option->answers[i]->next_option;
							else
								current_dialogue_option = dialogue->options.front();
							
							loadDialogueOptionText();
							loadDialogueAnswersTexts();
							};
					}
					else {
						dialogue_answers[i]->setWstring(L"");
						dialogue_answers[i]->onclick_func = []() {};
					}
						
				}
			}
		}

		virtual void cursorHover() {
			
			btn_prev->cursorHover();
			btn_next->cursorHover();

			for (auto& answer : dialogue_answers) {
				answer->cursorHover();
			}
		}

		virtual void update() {

			
			btn_prev->update();
			btn_next->update();
			/////////////////////////////

			for (auto& answer : dialogue_answers) {
				answer->update(true);
			}
		}

		virtual void handleEvent(sf::Event& event) {
			for (auto& answer : dialogue_answers)
				answer->handleEvent(event);
		}
		
		virtual void draw() {

			window->draw(rect);
			drawFrame(rect.getPosition() - cam->position, rect.getSize());

			// textarea frame
			sf::Vector2f size(dialogue_textarea_size.x+2* corner_size, dialogue_textarea_size.y + 2 * corner_size);
			sf::Vector2f position;
			position.x = dialogue_textarea_position.x + dialogue_textarea_size.x / 2;
			position.y = dialogue_textarea_position.y + dialogue_textarea_size.y / 2;
			drawFrame(position, size);

			dialogue_textarea->draw();

			// nav buttons
			btn_prev->draw();
			btn_next->draw();

			// dialogue options 
			size.x = dialogue_answers[0]->getSize().x + 2 * corner_size;
			size.y = dialogue_answers.size() * dialogue_answers[0]->getSize().y + (dialogue_answers.size() - 1) * margin;
			position.x = dialogue_textarea_position.x + dialogue_textarea_size.x / 2;
			position.y = (dialogue_answers.front()->position.y + dialogue_answers.back()->position.y + dialogue_answers.front()->getSize().y) / 2.0f;

			sf::RectangleShape rect2(size);
			rect2.setFillColor(panelColor_dark);
			rect2.setOrigin(rect2.getSize().x / 2, rect2.getSize().y / 2);
			rect2.setPosition(position.x + cam->position.x, position.y + cam->position.y);
			
			window->draw(rect2);
			drawFrame(position, size);

			for (auto& option : dialogue_answers)
				option->draw();
			
		}
	};

	class Quests : public CharacterInfoPage {
	public:
		Quests(CharacterInfoPanel* parent) : CharacterInfoPage(parent) { }
		virtual void handleEvent(sf::Event& event) { }
		virtual void update() { }

		virtual void draw() {
		}
	};

	sf::Sprite left_sider, right_sider;	// left&right decoration fragment of menu
	std::vector < ButtonWithImage* > menu;
	std::vector < CharacterInfoPage* > pages;
	CharacterInfoPage* active_page;

	CharacterInfoPanel(Character* character) : Panel(sf::Vector2f(412+16+2*corner_size, 580+16+32)) {

		_character = character;

		SingleTexture* menu_button_texture = getSingleTexture("GUI\\character_menu\\menu_slot");

		float btn_wdt = menu_button_texture->texture->getSize().x;
		float btn_hgh = menu_button_texture->texture->getSize().y;

		sf::Vector2f pos;
		pos.x = position.x - size.x / 2.0f + btn_wdt/2.0f + margin + corner_size + corner_size;
		pos.y = position.y - size.y / 2.0f + btn_hgh/2.0f + margin + corner_size;
		
		// create menu buttons
		ButtonWithImage* menu_statistics = new ButtonWithImage(getSingleTexture("GUI\\character_menu\\menu_statistics"), sf::Vector2f(pos.x, pos.y));
		menu_statistics->onclick_func = [this]() {
			active_page = pages[0];
			};

		ButtonWithImage* menu_layout = new ButtonWithImage(getSingleTexture("GUI\\character_menu\\menu_layout"), sf::Vector2f(pos.x + btn_wdt, pos.y));
		menu_layout->onclick_func = [this]() {
			active_page = pages[1];
			};

		ButtonWithImage* menu_equipment = new ButtonWithImage(getSingleTexture("GUI\\character_menu\\menu_equipment"), sf::Vector2f(pos.x + 2*btn_wdt, pos.y));
		menu_equipment->onclick_func = [this]() {
			active_page = pages[2];
			};

		ButtonWithImage* menu_inventory = new ButtonWithImage(getSingleTexture("GUI\\character_menu\\menu_inventory"), sf::Vector2f(pos.x + 3*btn_wdt, pos.y));
		menu_inventory->onclick_func = [this]() {
			active_page = pages[3];
			};

		ButtonWithImage* menu_dialogues = new ButtonWithImage(getSingleTexture("GUI\\character_menu\\menu_dialogues"), sf::Vector2f(pos.x + 4*btn_wdt, pos.y));
		menu_dialogues->onclick_func = [this]() {
			active_page = pages[4];
			};

		ButtonWithImage* menu_quests = new ButtonWithImage(getSingleTexture("GUI\\character_menu\\menu_quests"), sf::Vector2f(pos.x + 5*btn_wdt, pos.y));
		menu_quests->onclick_func = [this]() {
			active_page = pages[5];
			};


		left_sider = sf::Sprite(*getSingleTexture("GUI\\character_menu\\menu_sider_left")->texture);
		right_sider = sf::Sprite(*getSingleTexture("GUI\\character_menu\\menu_sider_right")->texture);
		
		left_sider.setOrigin(left_sider.getTexture()->getSize().x/2, left_sider.getTexture()->getSize().y/2);
		right_sider.setOrigin(right_sider.getTexture()->getSize().x/2, right_sider.getTexture()->getSize().y/2);

		float sider_y = pos.y + cam->position.y;
		float dx = corner_size + left_sider.getTexture()->getSize().x/2;

		left_sider.setPosition(position.x + cam->position.x - rect.getSize().x/2 + dx, sider_y);
		right_sider.setPosition(position.x + cam->position.x + rect.getSize().x/2 - dx, sider_y);

		menu.push_back(menu_statistics);
		menu.push_back(menu_layout);
		menu.push_back(menu_equipment);
		menu.push_back(menu_inventory);
		menu.push_back(menu_dialogues);
		menu.push_back(menu_quests);

		// create pages
		pages.push_back(new Statistics(this));
		pages.push_back(new Layout(this));
		pages.push_back(new Equipment(this));
		pages.push_back(new Inventory(this));
		pages.push_back(new Dialogues(this));
		pages.push_back(new Quests(this));

		active_page = pages[0];

		
	}

	~CharacterInfoPanel() {

		for (auto& m : menu)
			delete m;

		for (auto& p : pages)
			delete p;
	}

	virtual void cursorHover() {
		for (auto& m : menu)
			m->cursorHover();

		active_page->cursorHover();

	}

	virtual void handleEvent(sf::Event& event) {
	
		for (auto& m : menu)
			m->handleEvent(event);

		active_page->handleEvent(event);
	}

	virtual void update() {
		GUIwasOpen = true;

		for (auto& m : menu)
			m->update(); 

		active_page->update();
	}

	virtual void draw() {

		Panel::draw();

		// draw left&&right decorations frag of menu
		window->draw(left_sider);
		window->draw(right_sider);

		// draw menu
		for (auto& m : menu)
			m->draw();

		active_page->draw();

		
	}

};

#endif