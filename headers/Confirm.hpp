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
		textarea->setBackgroundColor(sf::Color::Transparent);
		textarea->setRectColor(panelColor_normal);

		btn_yes = new ButtonWithText("tak");
		btn_no = new ButtonWithText("nie");
		float x1 = 128 - btn_yes->rect.getSize().x;
		float x2 = 128 - btn_no->rect.getSize().x;
		float margin_bottom = 16;

		btn_yes->setPosition(sf::Vector2f(position.x - x1, position.y + rect.getSize().y - dialog_border_width - 8 - margin_bottom));
		btn_no->setPosition(sf::Vector2f(position.x + x2, position.y + rect.getSize().y - dialog_border_width - 8 - margin_bottom));

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