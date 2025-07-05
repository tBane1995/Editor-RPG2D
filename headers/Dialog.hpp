#ifndef Dialog_hpp
#define Dialog_hpp

enum class DialogType { Message, Panel, ScrollableText, OpenFile, SaveFile, Confirm, DialogueEditor };

void drawFrame(sf::Vector2f position, sf::Vector2f size) {

	sf::Sprite left_border;
	sf::Sprite right_border;
	sf::Sprite top_border;
	sf::Sprite bottom_border;
	sf::Sprite top_left_corner;
	sf::Sprite top_right_corner;
	sf::Sprite bottom_left_corner;
	sf::Sprite bottom_right_corner;

	// generate border
	float border_wdt = size.x - 2.0f * corner_size;
	float border_hgh = size.y - 2.0f * corner_size;

	sf::Vector2f pos;

	left_border = sf::Sprite(*getSingleTexture(L"GUI\\border_vertical")->texture);
	pos.x = position.x + cam->position.x - size.x / 2.0f;
	pos.y = position.y + cam->position.y - size.y / 2.0f + corner_size;
	left_border.setScale(1.0f, border_hgh / border_part_size.y);
	left_border.setPosition(pos);

	right_border = sf::Sprite(*getSingleTexture(L"GUI\\border_vertical")->texture);
	pos.x = position.x + cam->position.x + size.x / 2.0f - border_part_size.x;
	pos.y = position.y + cam->position.y - size.y / 2.0f + corner_size;
	right_border.setScale(1.0f, border_hgh / border_part_size.y);
	right_border.setPosition(pos);

	top_border = sf::Sprite(*getSingleTexture(L"GUI\\border_horizontal")->texture);
	pos.x = position.x + cam->position.x - size.x / 2.0f + corner_size;
	pos.y = position.y + cam->position.y - size.y / 2.0f;
	top_border.setScale(border_wdt / border_part_size.x, 1.0f);
	top_border.setPosition(pos);

	bottom_border = sf::Sprite(*getSingleTexture(L"GUI\\border_horizontal")->texture);
	pos.x = position.x + cam->position.x - size.x / 2.0f + corner_size;
	pos.y = position.y + cam->position.y + size.y / 2.0f - border_part_size.y;
	bottom_border.setScale(border_wdt / border_part_size.x, 1.0f);
	bottom_border.setPosition(pos);

	top_left_corner = sf::Sprite(*getSingleTexture(L"GUI\\corner")->texture);
	pos.x = position.x + cam->position.x - size.x / 2.0f;
	pos.y = position.y + cam->position.y - size.y / 2.0f;
	top_left_corner.setPosition(pos);

	top_right_corner = sf::Sprite(*getSingleTexture(L"GUI\\corner")->texture);
	pos.x = position.x + cam->position.x + size.x / 2.0f - corner_size;
	pos.y = position.y + cam->position.y - size.y / 2.0f;
	top_right_corner.setPosition(pos);

	bottom_left_corner = sf::Sprite(*getSingleTexture(L"GUI\\corner")->texture);
	pos.x = position.x + cam->position.x - size.x / 2.0f;
	pos.y = position.y + cam->position.y + size.y / 2.0f - corner_size;
	bottom_left_corner.setPosition(pos);

	bottom_right_corner = sf::Sprite(*getSingleTexture(L"GUI\\corner")->texture);
	pos.x = position.x + cam->position.x + size.x / 2.0f - corner_size;
	pos.y = position.y + cam->position.y + size.y / 2.0f - corner_size;
	bottom_right_corner.setPosition(pos);

	window->draw(left_border);
	window->draw(right_border);
	window->draw(top_border);
	window->draw(bottom_border);
	window->draw(top_left_corner);
	window->draw(top_right_corner);
	window->draw(bottom_left_corner);
	window->draw(bottom_right_corner);
}

enum class DialogState { Idle, Close };

class Dialog {
public:
	DialogType type;
	sf::Vector2f position;
	sf::Vector2f size;
	sf::RectangleShape rect;
	DialogState state;

	Dialog(DialogType type, sf::Vector2f size) {
		this->type = type;
		this->size = size;

		setSize(size);

		state = DialogState::Idle;
		
	}

	void setSize(sf::Vector2f size) {
		
		rect = sf::RectangleShape(sf::Vector2f(size.x - 2 * dialog_border_width, size.y - 2 * dialog_border_width));
		rect.setFillColor(panelColor_normal);
		rect.setPosition(cam->position.x - size.x / 2.0f + dialog_border_width, cam->position.y - size.y / 2.0f + dialog_border_width);
		rect.setOutlineThickness(dialog_border_width);
		rect.setOutlineColor(panelColor_dark);
	}
	
	sf::Vector2f getSize() {
		return rect.getSize();
	}

	virtual ~Dialog() { }
	
	virtual void cursorHover() { }

	virtual void handleEvent(sf::Event& event) {
		std::cout << "dialog handle event\n";
	}

	virtual void update() {
		GUIwasOpen = true;
	}

	virtual void draw() {
		
		
		window->draw(rect);

		sf::Vector2f frame_size(size.x - 2 * margin, size.y - 2 * margin);
		drawFrame(position, frame_size);
		
	}
};



std::vector < Dialog* > dialogs;

#endif