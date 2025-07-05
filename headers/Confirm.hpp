#ifndef Confirm_hpp
#define Confirm_hpp

enum class ConfirmValue { Undefinded, True, False };

class Confirm : public Dialog {
public:
	sf::Vector2f position;

	TextArea* textarea;
	ButtonWithText* btn_yes;
	ButtonWithText* btn_no;
	ConfirmValue value;

	Confirm(std::wstring text) : Dialog(DialogType::Confirm, sf::Vector2f(256+32,128+32)) {

		position = sf::Vector2f(0, 0);

		short width = 256;
		short height = 128;

		sf::Vector2f pos;
		pos.x = position.x - width / 2.0f;
		pos.y = position.y - height / 2.0f;

		sf::Vector2f textpos = sf::Vector2f(pos.x + dialog_border_width + margin, pos.y + dialog_border_width + margin);
		textarea = new TextArea(text, textpos, width - 2 * dialog_border_width - 2 * margin);

		textarea->setTextColor(textColor);
		textarea->setRectColor(panelColor_normal);

		sf::Vector2f btn_size = sf::Vector2f(64, -1);
		btn_yes = new ButtonWithText("tak", 17, TextAlignment::Center, btn_size);
		btn_no = new ButtonWithText("nie", 17, TextAlignment::Center, btn_size);

		float x1 = -64 - btn_yes->rect.getSize().x / 2;
		float x2 = 64 - btn_no->rect.getSize().x / 2;;
		float margin_bottom = 48;

		btn_yes->setPosition(sf::Vector2f(position.x + x1, position.y + rect.getSize().y/2 - dialog_border_width - margin_bottom));
		btn_yes->onclick_func = [this]() {
			state = DialogState::Close;
			};

		btn_no->setPosition(sf::Vector2f(position.x + x2, position.y + rect.getSize().y/2 - dialog_border_width - margin_bottom));
		btn_no->onclick_func = [this]() {
			state = DialogState::Close;
			};

		value = ConfirmValue::Undefinded;
	}

	~Confirm() {
		if (textarea != nullptr)
			delete textarea;

		if (btn_yes != nullptr)
			delete btn_yes;

		if (btn_no != nullptr)
			delete btn_no;
	}

	void cursorHover() {
		
		btn_yes->cursorHover();
		btn_no->cursorHover();
	}

	void handleEvent(sf::Event& event) {
		btn_yes->handleEvent(event);
		btn_no->handleEvent(event);

		if (btn_yes->state == ButtonState::Pressed)
			value = ConfirmValue::True;

		if (btn_no->state == ButtonState::Pressed)
			value = ConfirmValue::False;
	}

	void update() {

		GUIwasOpen = true;

		btn_yes->update();
		btn_no->update();
	}

	void draw() {
		Dialog::draw();
		textarea->draw();
		btn_yes->draw();
		btn_no->draw();
	}
};

#endif