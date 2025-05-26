#ifndef TextArea_hpp
#define TextArea_hpp

enum class TextAlignment { Left, Center };

class TextArea {
public:
	sf::Vector2f position;
	float characterSize = 17;
	float line_length;
	sf::Font font;
	TextAlignment alignment;

	std::vector < std::wstring > lines;

	std::vector < sf::Text > texts;		// texts
	sf::RectangleShape background;		// texts background
	sf::RectangleShape rect;			// rectangle field
	
	sf::Color text_color;
	sf::Color background_color;
	sf::Color rect_color;

	TextArea(std::wstring text, sf::Vector2f position = sf::Vector2f(0, 0), float line_length = 0, sf::Vector2f size = sf::Vector2f(0, 0)) {
		this->position = position;
		this->line_length = line_length;
		this->font = basicFont;
		this->alignment = TextAlignment::Left;

		lines = wrapText(text, basicFont, characterSize, this->line_length);

		
		
		//std::cout << "lines size: " << lines.size() << "\n";

		text_color = textColor;
		background_color = panelColor_medium;
		rect_color = panelColor_dark;

		generateText();
		generateBackground();
		generateRect(size);
	}

	~TextArea() {

	}

	void setTextColor(sf::Color color) {
		this->text_color = color;

		for (auto& t : texts)
			t.setFillColor(text_color);
	}

	void setBackgroundColor(sf::Color color) {
		background_color = color;
		background.setFillColor(background_color);
	}

	void setRectColor(sf::Color color) {
		rect_color = color;
		rect.setFillColor(rect_color);;
	}

	

	void generateText() {
		texts.clear();

		float i = 0;
		for (auto& line : lines) {
			sf::Text t;
			t.setFont(font);
			t.setFillColor(text_color);
			t.setCharacterSize(characterSize);
			t.setString(line);

			if (alignment == TextAlignment::Left) {
				sf::Vector2f textPos;
				textPos.x = position.x + characterSize * 0.2f;
				textPos.y = position.y + getLineHeight(17) * float(i);
				t.setPosition(textPos.x + cam->position.x, textPos.y + cam->position.y);
			}
			else if (alignment == TextAlignment::Center) {
				sf::Vector2f textPos;
				textPos.x = position.x + rect.getSize().x / 2.0f - t.getGlobalBounds().getSize().x/2.0f;
				textPos.y = position.y + getLineHeight(17) * float(i);
				t.setPosition(textPos.x + cam->position.x, textPos.y + cam->position.y);
			}
			
			texts.push_back(t);
			i += 1.0f;
		}

		generateBackground();
	}

	void generateBackground() {
		sf::Vector2f size;
		if (texts.size() > 0) {
			(line_length > 0.0f) ? size.x = line_length : size.x = float(texts.front().getLocalBounds().getSize().x) + characterSize * 0.5f;
			size.y = texts.size() * getLineHeight(17);
		}
		else if (!texts.empty() && texts[0].getString() != "") {
			size.x = float(texts.front().getLocalBounds().getSize().x) + characterSize * 0.5f;
			size.y = getLineHeight(17);
		}
		else {
			size.x = 0;
			size.y = 0;
		}

		background.setSize(size);
		background.setFillColor(background_color);
		background.setPosition(position.x + cam->position.x, position.y + cam->position.y);

	}

	void generateRect(sf::Vector2f size = sf::Vector2f(0,0)) {
		if (size == sf::Vector2f(0, 0)) {
			rect.setSize(background.getSize());
		}
		else
			rect.setSize(size);

		rect.setFillColor(rect_color);
		rect.setPosition(position.x + cam->position.x, position.y + cam->position.y);

	}

	void setCharacterSize(short val) {

		characterSize = val;

		generateText();
		generateBackground();
	}

	void setFont(sf::Font& font) {
		this->font = font;
	}

	void setBackgroundSize(sf::Vector2f size) {
		background.setSize(size);
	}

	void setRectSize(sf::Vector2f size) {
		rect.setSize(size);
	}

	void setWstring(std::wstring text) {

		lines = wrapText(text, basicFont, characterSize, line_length);

		generateText();
	}

	void setPosition(sf::Vector2f position) {
		this->position = position;

		background.setPosition(position.x + cam->position.x, position.y + cam->position.y);
		generateText();
		rect.setPosition(position.x + cam->position.x, position.y + cam->position.y);

	}

	sf::Vector2f getSize() {
		return rect.getSize();
	}

	void setAlignment(TextAlignment alignment) {
		this->alignment = alignment;
		generateText();
	}

	void update() {

	}

	void draw() {
		window->draw(rect);
		window->draw(background);
		for (auto& t : texts)
			window->draw(t);
	}
};
#endif