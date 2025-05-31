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

		class Stat {
		public:
			sf::RectangleShape rect;
			TextArea* stat_name;
			EditableTextArea* stat_value;
				
			Stat(std::wstring name, std::wstring value, short maxCharacters = -1) {
				stat_name = new TextArea(name);
				stat_value = new EditableTextArea(value, maxCharacters);
			}

			~Stat() {

			}

			virtual void cursorHover() {
				
			}

			virtual void update() {
				
				stat_value->update();
			}

			virtual void handleEvent(sf::Event& event) {

				if (rect.getGlobalBounds().contains(worldMousePosition)) {

					rect.setFillColor(panelColor_medium);
					stat_name->setRectColor(panelColor_medium);
					stat_value->setRectColor(sf::Color::Transparent);
				}
				else {
					rect.setFillColor(panelColor_dark);
					stat_name->setRectColor(panelColor_dark);
					stat_value->setRectColor(sf::Color::Transparent);
				}

				stat_value->handleEvent(event);
				
			}

			virtual void draw() {
				window->draw(rect);
				stat_name->draw();
				stat_value->draw();
			}
		};

		class TextStat : public Stat {
		public:
			std::wstring& value;
		
			TextStat(std::wstring name, std::wstring& value, short maxCharacters = -1) : Stat(name, value, maxCharacters), value(value) {

			}

			~TextStat() {

			}

			void cursorHover() {

			}

			void update() {
				stat_value->update();
			}

			void handleEvent(sf::Event& event) {
				if (rect.getGlobalBounds().contains(worldMousePosition)) {

					rect.setFillColor(panelColor_medium);
					stat_name->setRectColor(panelColor_medium);
					stat_value->setRectColor(sf::Color::Transparent);
				}
				else {
					rect.setFillColor(panelColor_dark);
					stat_name->setRectColor(panelColor_dark);
					stat_value->setRectColor(sf::Color::Transparent);
				}

				stat_value->handleEvent(event);
				value = stat_value->lines[0];
			}

			void draw() {
				Stat::draw();
			}
		};

		class NumbSelector : public Stat {
		public:
			int& value;
			sf::Sprite less_sprite;
			sf::Sprite more_sprite;
			ButtonWithImage* less_btn;
			ButtonWithImage* more_btn;

			NumbSelector(std::wstring name, int& value, short step) : Stat(name, std::to_wstring(value)), value(value) {

				stat_value->setRectColor(sf::Color::Transparent);
				stat_value->setRectSize(sf::Vector2f(80, stat_value->font.getLineSpacing(17)));
				stat_value->setWstring(std::to_wstring(this->value));
				stat_value->setAlignment(TextAlignment::Center);

				sf::Vector2f pos(cam->position);

				less_sprite.setTexture(*getSingleTexture(L"GUI\\character_menu\\value_less")->texture);
				more_sprite.setTexture(*getSingleTexture(L"GUI\\character_menu\\value_more")->texture);

				less_btn = new ButtonWithImage(getSingleTexture(L"GUI\\character_menu\\value_less"));
				less_btn->onclick_func = [this, step]() {
					this->value -= step;
					if (this->value < 0)
						this->value = 0;

					stat_value->setWstring(std::to_wstring(this->value));
					};

				more_btn = new ButtonWithImage(getSingleTexture(L"GUI\\character_menu\\value_more"));
				more_btn->onclick_func = [this, step]() {
					this->value += step;
					stat_value->setWstring(std::to_wstring(this->value));
					};
			}

			~NumbSelector() {

			}

			void cursorHover() {
				less_btn->cursorHover();
				more_btn->cursorHover();
			}

			void update() {
				less_btn->update();
				more_btn->update();
			}

			void handleEvent(sf::Event& event) {

				if (rect.getGlobalBounds().contains(worldMousePosition)) {

					rect.setFillColor(panelColor_medium);
					stat_name->setRectColor(panelColor_medium);
					stat_value->setRectColor(sf::Color::Transparent);
				}
				else {
					rect.setFillColor(panelColor_dark);
					stat_name->setRectColor(panelColor_dark);
					stat_value->setRectColor(sf::Color::Transparent);
				}

				less_btn->handleEvent(event);
				more_btn->handleEvent(event);

			}

			void draw() {
				Stat::draw();

				less_btn->draw();
				more_btn->draw();
			}
		};

		sf::RectangleShape rect;
		std::vector < Stat* > stats;

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
			
			// new stats
			stats.push_back(new TextStat(L"NAME", parent->_character->name, 16));
			stats.push_back(new Stat(L"ID", std::to_wstring(parent->_character->id)));

			stats.push_back(nullptr);

			stats.push_back(new NumbSelector(L"LEVEL", parent->_character->LEVEL, 1));
			stats.push_back(new NumbSelector(L"EXPERIENCE", parent->_character->EXPERIENCE, 50));
			stats.push_back(new NumbSelector(L"SKILL POINTS", parent->_character->SKILL_POINTS, 1));

			std::cout << parent->_character->EXPERIENCE;

			stats.push_back(nullptr);

			stats.push_back(new NumbSelector(L"CURRENT HP", parent->_character->attributes[Attribute::HP], 10));
			stats.push_back(new NumbSelector(L"MAX HP", parent->_character->attributes[Attribute::HP_max], 10));

			stats.push_back(new NumbSelector(L"CURRENT MANA", parent->_character->attributes[Attribute::MP],5));
			stats.push_back(new NumbSelector(L"MAX MANA", parent->_character->attributes[Attribute::MP_max],5));

			stats.push_back(new NumbSelector(L"STRENGTH", parent->_character->attributes[Attribute::STRENGTH],1));
			stats.push_back(new NumbSelector(L"DEXTERITY", parent->_character->attributes[Attribute::DEXTERITY],1));
			stats.push_back(new NumbSelector(L"INTELLIGENCE", parent->_character->attributes[Attribute::INTELLIGENCE],1));

			stats.push_back(nullptr);

			stats.push_back(new Stat(L"ACTION RANGE", std::to_wstring(parent->_character->action_range)));
			stats.push_back(new Stat(L"VIEW RANGE", std::to_wstring(parent->_character->view_range)));

			stats.push_back(nullptr);

			stats.push_back(new Stat(L"ATTACK", L"0"));
			stats.push_back(new Stat(L"DEFEND", L"0"));


			float start_pos_y = parent->position.y - panel_height / 2.0f + margin + corner_size + menu_height + margin + corner_size;
			float m = 8.0f;	// margin
			for (short i = 0; i < stats.size(); i++) {
				
				if (stats[i] != nullptr) {

					float line_height = stats[i]->stat_name->font.getLineSpacing(17);

					sf::Vector2f pos;
					pos.y = start_pos_y + i * line_height + m;

					// rect
					stats[i]->rect.setFillColor(panelColor_dark);
					stats[i]->rect.setSize(sf::Vector2f( parent->rect.getSize().x - 4*corner_size, line_height));
					sf::Vector2f rect_pos;
					rect_pos.x = cam->position.x - parent->rect.getSize().x/2.0f + 2*corner_size;
					rect_pos.y = pos.y + cam->position.y;
					stats[i]->rect.setPosition(rect_pos);

					// stat name
					pos.x = parent->position.x - parent->rect.getSize().x / 2.0f + corner_size + corner_size + m;
					stats[i]->stat_name->setPosition(pos);

					// stat value 
					pos.x = parent->position.x + parent->rect.getSize().x / 2.0f - corner_size - corner_size - stats[i]->stat_value->getSize().x - m;
					stats[i]->stat_value->setPosition(pos);
					
					if (dynamic_cast<NumbSelector*>(stats[i]) != nullptr) {

						NumbSelector* selector = dynamic_cast<NumbSelector*>(stats[i]);
						sf::Vector2f rect_size = selector->stat_value->rect.getSize();

						ButtonWithImage* less_btn = selector->less_btn;
						ButtonWithImage* more_btn = selector->more_btn;

						selector->less_btn->setPosition(sf::Vector2f(pos.x+less_btn->sprite.getGlobalBounds().width/2.0f, pos.y + rect_size.y/2.0f));
						selector->more_btn->setPosition(sf::Vector2f(pos.x+rect_size.x - more_btn->sprite.getGlobalBounds().width / 2.0f, pos.y + rect_size.y/2.0f));
					}
				}

			}

			positioningStats();


		}

		~Statistics() {
			
			for (auto& stat : stats)
				delete stat;


		}

		void positioningStats() {

			// some parameters
			float panel_height = parent->rect.getSize().y;
			float menu_height = parent->menu[0]->texture->texture->getSize().y;
			float margin = 4;

			float start_pos_y = parent->position.y - panel_height / 2.0f + margin + corner_size + menu_height + margin + corner_size;
			float m = 8.0f;	// margin

			float line_height = stats[0]->stat_name->font.getLineSpacing(17);

			for (short i = 0; i < stats.size(); i++) {

				if (stats[i] != nullptr) {

					sf::Vector2f pos;
					pos.y = start_pos_y + i * line_height + m;

					// stat name
					pos.x = parent->position.x - parent->rect.getSize().x / 2.0f + corner_size + corner_size + m;
					stats[i]->stat_name->setPosition(pos);

					// stat value - TO-DO - right alignment
					if(dynamic_cast<NumbSelector*>(stats[i]))
						pos.x = parent->position.x + parent->rect.getSize().x / 2.0f - corner_size - corner_size - stats[i]->stat_value->getSize().x - m;
					else
						pos.x = parent->position.x + parent->rect.getSize().x / 2.0f - corner_size - corner_size - stats[i]->stat_value->texts[0].getGlobalBounds().width - m;

					stats[i]->stat_value->setPosition(pos);
					
				}

			}
		}

		virtual void cursorHover() {
			for (auto& stat : stats) {
				if (stat != nullptr)
					stat->cursorHover();
			}
		}
		
		virtual void handleEvent(sf::Event& event) {

			for (auto& stat : stats) {
				if(stat != nullptr)
					stat->handleEvent(event);
			}

			positioningStats();
			
		}

		virtual void update() {
			
			for (auto& stat : stats)
				if(stat != nullptr)
					stat->update();
		}

		virtual void draw() {
		
			window->draw(rect);
			drawFrame(rect.getPosition() - cam->position, rect.getSize());

			/*
			//std::cout << "draw Statistics\n";
			for (auto& sn : stats_names)
				sn->draw();

			for (auto& sv : stats_values)
				sv->draw();
			*/

			for (auto& stat : stats)
				if(stat != nullptr)
					stat->draw();

		}
	};

	class Layout : public CharacterInfoPage {
	public:

		class DirectionButton : public ButtonWithImage {
		public:
			sf::Sprite sprite;

			DirectionButton(SingleTexture* texture, sf::Vector2f position, CharacterInfoPanel* parent, short direction) : ButtonWithImage(getSingleTexture(L"GUI\\character_menu\\layout_slot"), position) {

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
			
			std::wstring body;
			std::wstring head;
			sf::RenderTexture* render_texture = nullptr;
			sf::Sprite sprite;

			LayoutButton(sf::Vector2f position, std::wstring body, std::wstring head ) : ButtonWithImage(getSingleTexture(L"GUI\\character_menu\\layout_slot"), position) {

				this->body = body;
				this->head = head;

				sprite = sf::Sprite();
				loadRenderTexture();
				sprite.setTexture(render_texture->getTexture());
				sprite.setOrigin(render_texture->getTexture().getSize().x/2, render_texture->getTexture().getSize().y/2);
				sprite.setPosition(position.x + cam->position.x, position.y + cam->position.y);
			}

			void loadRenderTexture() {
				if (render_texture != nullptr)
					delete render_texture;

				render_texture = new sf::RenderTexture();
				render_texture->create(64, 64);
				render_texture->clear(sf::Color::Transparent);

				sf::Sprite body_spr, head_spr;

				body_spr.setTexture(*getSingleTexture(body + L"\\attackBottom0")->texture);
				head_spr.setTexture(*getSingleTexture(head + L"\\attackBottom0")->texture);

				render_texture->draw(body_spr);
				render_texture->draw(head_spr);

				render_texture->display();
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
			DirectionButton* left = new DirectionButton(getSingleTexture(L"GUI\\character_menu\\direction_left"), btn_pos, parent, 3);
			buttons.push_back(left);

			btn_pos.x = start_pos.x + (1) * (btn_size.x);
			DirectionButton* bottom = new DirectionButton(getSingleTexture(L"GUI\\character_menu\\direction_bottom"), btn_pos, parent, 2);
			buttons.push_back(bottom);

			btn_pos.x = start_pos.x + (2) * (btn_size.x);
			DirectionButton* top = new DirectionButton(getSingleTexture(L"GUI\\character_menu\\direction_top"), btn_pos, parent, 0);
			buttons.push_back(top);

			btn_pos.x = start_pos.x + (3) * (btn_size.x);
			DirectionButton* right = new DirectionButton(getSingleTexture(L"GUI\\character_menu\\direction_right"), btn_pos, parent, 1);
			buttons.push_back(right);

			// load the Bodies
			std::vector < std::wstring > bodies;
			bodies.push_back(L"sets\\body\\man");
			bodies.push_back(L"sets\\body\\man");
			bodies.push_back(L"sets\\body\\woman");

			// load the Heads
			std::vector < std::wstring > heads;
			heads.push_back(L"sets\\head\\man-black-haired");
			heads.push_back(L"sets\\head\\man-brown-haired");
			heads.push_back(L"sets\\head\\man-gray-haired");
			heads.push_back(L"sets\\head\\man-red-haired");

			heads.push_back(L"sets\\head\\boy-black-haired");
			heads.push_back(L"sets\\head\\boy-brown-haired");
			heads.push_back(L"sets\\head\\boy-gray-haired");
			heads.push_back(L"sets\\head\\boy-red-haired");

			heads.push_back(L"sets\\head\\woman-black-haired");
			heads.push_back(L"sets\\head\\woman-brown-haired");
			heads.push_back(L"sets\\head\\woman-gray-haired");
			heads.push_back(L"sets\\head\\woman-red-haired");



			// layout buttons
			for (short i = 0; i < heads.size(); i++) {
				btn_pos.x = start_pos.x + i%4 * (btn_size.x);
				btn_pos.y = parent->position.y + parent->rect.getSize().y / 2 + (i/4 - 2) * (btn_size.y) - (btn_size.y) - corner_size;

				LayoutButton* btn = new LayoutButton(btn_pos, bodies[i/4], heads[i]);

				btn->onclick_func = [this, btn]() {
					this->parent->_character->body = btn->body;
					this->parent->_character->head = btn->head;
					this->parent->_character->loadBody();
					this->parent->_character->loadHead();
					};

				btn->hover_func = [this, btn]() {

					if (tip == nullptr || (tip != nullptr && tip->btn != btn)) {
						sf::Vector2f pos;
						pos.x = btn->position.x + btn->render_texture->getTexture().getSize().x / 4.0f;
						pos.y = btn->position.y + btn->render_texture->getTexture().getSize().y / 4.0f;
						if (tip != nullptr)
							delete tip;
						tip = new Tip(getShortName(btn->head), pos, btn);
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
			SingleTexture* slot_texture = getSingleTexture(L"GUI\\character_menu\\item_slot");
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
							parent->_character->useItem(slot->_item);
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
								tip = new Tip(getShortName(slot->_item->name), pos, slot);
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
				if (item->type == ItemType::helmet || item->type == ItemType::armor || item->type == ItemType::pants || item->type == ItemType::weapon || item->type == ItemType::bow || item->type == ItemType::shield)
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
				setRectColor(panelColor_medium);
			}

			void hover() {

				state = ButtonState::Hover;
				setRectColor(panelColor_normal);
				GUIwasHover = true;
			}

			void click() {

				state = ButtonState::Pressed;
				setRectColor(panelColor_medium);
				GUIwasClicked = true;
				clickTime = currentTime;
			}

			void cursorHover() {
				if (mouse_state != MouseState::Selecting) {

					if (rect.getGlobalBounds().contains(worldMousePosition)) {

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

				if (rect.getGlobalBounds().contains(worldMousePosition)) {

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

		ButtonWithText* change_dialogue_btn;
		ButtonWithText* edit_dialogue_btn;
		
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
			(dialogue != nullptr) ? current_dialogue_option = dialogue->options.front() : current_dialogue_option = nullptr;
			selected_dialogue_option_index = -1;

			// dialogue text
			TextArea* test_text = new TextArea(L"line1\nline2\nline3\nline4\nline5\nline6\nline7\nline8");	// 8 lines
			dialogue_textarea_size = sf::Vector2f(parent->rect.getSize().x - 6 * corner_size, test_text->getSize().y);
			dialogue_textarea_position = sf::Vector2f(-dialogue_textarea_size.x / 2, -parent->rect.getSize().y/2.0f + dialog_border_width + corner_size + menu_height + corner_size + margin);			
			delete test_text;


			std::wstring dialogue_text;
			(current_dialogue_option != nullptr) ? dialogue_text = current_dialogue_option->text : dialogue_text = L"";
			dialogue_textarea = new TextArea(dialogue_text, dialogue_textarea_position, dialogue_textarea_size.x, dialogue_textarea_size);
			dialogue_textarea->setFont(dialogueFont);
			dialogue_textarea->setRectColor(panelColor_medium);
			dialogue_textarea->setVerticalAlignment(VerticalAlignment::Top);

			// prev and next buttons
			btn_prev = new ButtonWithImage(getSingleTexture(L"GUI\\character_menu\\dialogue_prev"));
			btn_next = new ButtonWithImage(getSingleTexture(L"GUI\\character_menu\\dialogue_next"));
			
			float pos_y = dialogue_textarea->position.y + dialogue_textarea->getSize().y + corner_size + btn_prev->texture->texture->getSize().y/2 + margin;
			float dx = parent->rect.getSize().x / 2 - 64;
			
			btn_prev->setPosition(sf::Vector2f(-dx, pos_y));
			btn_next->setPosition(sf::Vector2f(dx, pos_y));
			
			// dialogue answers
			test_text = new TextArea(L"line1\nline2");	// 2 lines
			sf::Vector2f dialogue_answer_size(dialogue_textarea_size.x, test_text->getSize().y );
			delete test_text;

			dialogues_answers_count = 5;
			pos_y = pos_y + btn_prev->sprite.getGlobalBounds().height/2.0f + margin;

			for (short i = 0; i < dialogues_answers_count; i += 1) {
				sf::Vector2f pos;
				pos.x = -dialogue_textarea_size.x / 2;
				pos.y = pos_y + corner_size;
				pos_y += dialogue_answer_size.y + margin;

				AnswerText* op = new AnswerText(L"", pos, dialogue_answer_size.x, dialogue_answer_size);
				dialogue_answers.push_back(op);
			}

			loadDialogueAnswersTexts();

			sf::Vector2f btn_size(128, 32);
			float pos_x = 80;
			pos_y += margin + 14;

			change_dialogue_btn = new ButtonWithText("change", 17, TextAlignment::Center, btn_size);
			change_dialogue_btn->setColors(panelColor_medium, panelColor_normal, panelColor_medium, textColor);
			change_dialogue_btn->setPosition(sf::Vector2f(-pos_x - change_dialogue_btn->getSize().x/2, pos_y));
			change_dialogue_btn->onclick_func = [this, parent]() {
				int dial_id = 0;
				if (dialogue != nullptr) {
					dial_id = dialogue->id;
					(dial_id < dialogues.size()) ? dial_id += 1 : dial_id = 0;
				}

				dialogue = getDialogue(dial_id);
				parent->_character->dialogue = dialogue;
				(dialogue != nullptr) ? current_dialogue_option = dialogue->options.front() : current_dialogue_option = nullptr;
				loadDialogueOptionText();
				loadDialogueAnswersTexts();
				

			};


			edit_dialogue_btn = new ButtonWithText("edit", 17, TextAlignment::Center, btn_size);
			edit_dialogue_btn->setColors(panelColor_medium, panelColor_normal, panelColor_medium, textColor);
			edit_dialogue_btn->setPosition(sf::Vector2f(pos_x - edit_dialogue_btn->getSize().x/2, pos_y));
			edit_dialogue_btn->onclick_func = [this]() {
				dialogs.push_back(new DialogueEditor(dialogue));
			};
			
		}

		~Dialogues() {
			delete dialogue_textarea;

			for (auto& answer : dialogue_answers)
				delete answer;

			delete btn_prev;
			delete btn_next;

			delete change_dialogue_btn;
			delete edit_dialogue_btn;
		}

		void loadDialogueOptionText() {
			if(current_dialogue_option != nullptr)
				this->dialogue_textarea->setWstring(current_dialogue_option->text);
			else
				this->dialogue_textarea->setWstring(L"");
		}

		void loadDialogueAnswersTexts() {
			
			if (current_dialogue_option == nullptr) {
				for (short i = 0; i < dialogues_answers_count; i++) {
					dialogue_answers[i]->setWstring(L"");
					dialogue_answers[i]->onclick_func = []() {};
				}
				return;
			}
				

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

			change_dialogue_btn->cursorHover();
			edit_dialogue_btn->cursorHover();
		}

		virtual void update() {

			
			btn_prev->update();
			btn_next->update();
			/////////////////////////////

			for (auto& answer : dialogue_answers) {
				answer->update();
			}

			change_dialogue_btn->update();
			edit_dialogue_btn->update();
		}

		virtual void handleEvent(sf::Event& event) {
			for (auto& answer : dialogue_answers)
				answer->handleEvent(event);

			change_dialogue_btn->handleEvent(event);
			edit_dialogue_btn->handleEvent(event);
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
			
			//
			edit_dialogue_btn->draw();
			change_dialogue_btn->draw();
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

		SingleTexture* menu_button_texture = getSingleTexture(L"GUI\\character_menu\\menu_slot");

		float btn_wdt = menu_button_texture->texture->getSize().x;
		float btn_hgh = menu_button_texture->texture->getSize().y;

		sf::Vector2f pos;
		pos.x = position.x - size.x / 2.0f + btn_wdt/2.0f + margin + corner_size + corner_size;
		pos.y = position.y - size.y / 2.0f + btn_hgh/2.0f + margin + corner_size;
		
		// create menu buttons
		ButtonWithImage* menu_statistics = new ButtonWithImage(getSingleTexture(L"GUI\\character_menu\\menu_statistics"), sf::Vector2f(pos.x, pos.y));
		menu_statistics->onclick_func = [this]() {
			active_page = pages[0];
			};

		ButtonWithImage* menu_layout = new ButtonWithImage(getSingleTexture(L"GUI\\character_menu\\menu_layout"), sf::Vector2f(pos.x + btn_wdt, pos.y));
		menu_layout->onclick_func = [this]() {
			active_page = pages[1];
			};

		ButtonWithImage* menu_equipment = new ButtonWithImage(getSingleTexture(L"GUI\\character_menu\\menu_equipment"), sf::Vector2f(pos.x + 2*btn_wdt, pos.y));
		menu_equipment->onclick_func = [this]() {
			active_page = pages[2];
			};

		ButtonWithImage* menu_inventory = new ButtonWithImage(getSingleTexture(L"GUI\\character_menu\\menu_inventory"), sf::Vector2f(pos.x + 3*btn_wdt, pos.y));
		menu_inventory->onclick_func = [this]() {
			active_page = pages[3];
			};

		ButtonWithImage* menu_dialogues = new ButtonWithImage(getSingleTexture(L"GUI\\character_menu\\menu_dialogues"), sf::Vector2f(pos.x + 4*btn_wdt, pos.y));
		menu_dialogues->onclick_func = [this]() {
			active_page = pages[4];
			};

		ButtonWithImage* menu_quests = new ButtonWithImage(getSingleTexture(L"GUI\\character_menu\\menu_quests"), sf::Vector2f(pos.x + 5*btn_wdt, pos.y));
		menu_quests->onclick_func = [this]() {
			active_page = pages[5];
			};


		left_sider = sf::Sprite(*getSingleTexture(L"GUI\\character_menu\\menu_sider_left")->texture);
		right_sider = sf::Sprite(*getSingleTexture(L"GUI\\character_menu\\menu_sider_right")->texture);
		
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