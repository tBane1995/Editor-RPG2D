#ifndef CheckBox_hpp
#define CheckBox_hpp

class CheckBox {
public:
	sf::Vector2f position;
	sf::RectangleShape rect;
	bool value;
	sf::Sprite checkSprite;
	
	CheckBox() {
		this->value = false;
	}

	CheckBox(sf::Vector2f size, sf::Vector2f position, bool value=false) {

		this->position = position;
		this->value = value;

		rect = sf::RectangleShape(size);
		//rect.setFillColor(sf::Color::Red);
		rect.setOrigin(size.x / 2.0f, size.y / 2.0f);
		rect.setPosition(cam->position.x + position.x, cam->position.y + position.y);

		checkSprite = sf::Sprite();
		checkSprite.setTexture(*getSingleTexture("GUI\\checkbox\\check")->texture);
		sf::Vector2f texsize = sf::Vector2f( checkSprite.getTexture()->getSize().x, checkSprite.getTexture()->getSize().y);
		checkSprite.setOrigin(texsize.x / 2.0f, texsize.y / 2.0f);
		checkSprite.setScale(size.x/texsize.x, size.y/texsize.y);
		checkSprite.setPosition(cam->position.x + position.x, cam->position.y + position.y);
		
	}

	~CheckBox() { }

	void edit(sf::Vector2f size, sf::Vector2f position) {

		this->position = position;

		rect = sf::RectangleShape(size);
		rect.setOrigin(size.x / 2.0f, size.y / 2.0f);
		rect.setPosition(cam->position.x + position.x, cam->position.y + position.y);

		checkSprite = sf::Sprite();
		checkSprite.setTexture(*getSingleTexture("GUI\\checkbox\\check")->texture);
		sf::Vector2f texsize = sf::Vector2f(checkSprite.getTexture()->getSize().x, checkSprite.getTexture()->getSize().y);
		checkSprite.setOrigin(texsize.x / 2.0f, texsize.y / 2.0f);
		checkSprite.setScale(size.x / texsize.x, size.y / texsize.y);
		checkSprite.setPosition(cam->position.x + position.x, cam->position.y + position.y);

	}

	void update() {
		rect.setPosition(cam->position.x + position.x, cam->position.y + position.y);
		checkSprite.setPosition(cam->position.x + position.x, cam->position.y + position.y);
	}

	void draw() {
		//window->draw(rect);
		if(value)
			window->draw(checkSprite);
	}
};

#endif