#ifndef Tips_hpp
#define Tips_hpp

class Tip {
public:
	sf::Time hover_start;
	ButtonWithImage* btn;
	sf::Vector2f position;
	TextArea* text;
	
	Tip(wstring tip, ButtonWithImage* btn=nullptr) {
		
		this->btn = btn;

		hover_start = currentTime;

		if (btn == nullptr) {
			position.x = 0;
			position.y = 0;
		}
		else
		{
			position.x = btn->position.x - btn->sprite.getTexture()->getSize().x/2.0f;
			position.y = btn->position.y + btn->sprite.getTexture()->getSize().y/2.0f;
		}
		

		text = new TextArea(tip, position);
		text->rect.setOutlineThickness(2.0f);
		text->rect.setOutlineColor(sf::Color::Black);
	
		if (this->position.x + text->rect.getSize().x >= screenWidth / 2.0f) {
			this->position.x = screenWidth/2.0f - text->rect.getSize().x;
			text->setPosition(this->position);
		}
	}

	Tip(wstring tip, sf::Vector2f position, ButtonWithImage* btn = nullptr) {

		this->btn = btn;

		hover_start = currentTime;

		this->position = position;

		text = new TextArea(tip, position);
		text->rect.setOutlineThickness(2.0f);
		text->rect.setOutlineColor(sf::Color::Black);

		if (this->position.x + text->rect.getSize().x >= screenWidth / 2.0f) {
			this->position.x = screenWidth/2.0f - text->rect.getSize().x;
			text->setPosition(this->position);
		}
	}

	~Tip() { 
		delete text;
	}

	void update() {
		text->setPosition(position);
		text->update();
	}

	void draw() {
		if((currentTime - hover_start).asSeconds() > 0.5f)
			text->draw();
	}
};

Tip* tip = nullptr;

#endif