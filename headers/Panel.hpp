#ifndef Panel_hpp
#define Panel_hpp

class Panel : public Dialog {
public:

	Panel(sf::Vector2f size = sf::Vector2f(600, 400), DialogType dialog_type = DialogType::Panel) : Dialog(dialog_type, size) {
		
	}

	~Panel() {

	}

	void cursorHover() { }

	void handleEvent(sf::Event& event) {

	}

	void update() {
		GUIwasOpen = true;
	}

	virtual void draw() {
		Dialog::draw();
	}
};

#endif