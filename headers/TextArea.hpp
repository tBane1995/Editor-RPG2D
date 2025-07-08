#ifndef TextArea_hpp
#define TextArea_hpp

enum class TextAlignment { Left, Center };
enum class VerticalAlignment{ Top, Center };


class TextArea {
public:
	sf::Vector2f position;
	float characterSize = 17;
	float margin = 4;
	float line_length;
	sf::Font font;
	TextAlignment alignment;
	VerticalAlignment vertical_alignment;
	WrapperType wrapper_type;

	std::wstring text;
	std::vector < std::wstring > lines;

	std::vector < sf::Text > texts;		// texts
	sf::RectangleShape rect;			// rectangle field
	
	sf::Color text_color;
	sf::Color rect_color;

	

	TextArea(std::wstring text, sf::Vector2f position = sf::Vector2f(0, 0), 
		float line_length = 0, sf::Vector2f size = sf::Vector2f(0, 0), 
		TextAlignment alignment = TextAlignment::Left, VerticalAlignment vert_alignment = VerticalAlignment::Center,
		WrapperType wrapperType = WrapperType::Simple) {

		this->text = text;
		this->position = position;
		this->line_length = line_length - 2 * characterSize * 0.2f;
		this->font = basicFont;
		this->alignment = alignment;
		this->vertical_alignment = vert_alignment;

		this->wrapper_type = wrapperType;

		lines = wrapText(text, wrapper_type, font, characterSize, line_length - 2*margin);

		//std::cout << "lines size: " << lines.size() << "\n";

		text_color = textColor;
		rect_color = panelColor_dark;

		generateRect(size);
		generateText();
		
	}

	~TextArea() {

	}

	void setTextColor(sf::Color color) {
		this->text_color = color;

		for (auto& t : texts)
			t.setFillColor(text_color);
	}

	void setRectColor(sf::Color color) {
		rect_color = color;
		rect.setFillColor(rect_color);
	}

	

	void generateText() {
		texts.clear();

		float start_line_pos;
		if (vertical_alignment == VerticalAlignment::Top) start_line_pos = 0;
		else if(vertical_alignment == VerticalAlignment::Center) start_line_pos = (rect.getSize().y - float(lines.size()) * font.getLineSpacing(characterSize)) / 2.0f;

		float i = 0;
		for (auto& line : lines) {
			sf::Text t;
			t.setFont(font);
			t.setFillColor(text_color);
			t.setCharacterSize(characterSize);
			t.setString(line);

			if (alignment == TextAlignment::Left) {
				sf::Vector2f textPos;
				textPos.x = position.x + margin;
				textPos.y = position.y + start_line_pos + font.getLineSpacing(characterSize) * float(i);
				t.setPosition(textPos.x + cam->position.x, textPos.y + cam->position.y);
			}
			else if (alignment == TextAlignment::Center) {
				sf::Vector2f textPos;
				textPos.x = position.x + rect.getSize().x / 2.0f - t.getGlobalBounds().getSize().x/2.0f;
				textPos.y = position.y + start_line_pos + font.getLineSpacing(characterSize) * float(i);
				t.setPosition(textPos.x + cam->position.x, textPos.y + cam->position.y);
			}
			
			texts.push_back(t);
			i += 1.0f;
		}

	}

	void generateRect(sf::Vector2f size = sf::Vector2f(0,0)) {
		if (size == sf::Vector2f(0, 0)) {

			float max_width = 0.0f;
			for (auto& line : lines) {
				sf::Text text(line, font, characterSize);
				if (text.getGlobalBounds().width > max_width)
					max_width = text.getGlobalBounds().width;
			}
				

			max_width = max_width + 2 * margin;

			rect.setSize(sf::Vector2f(max_width, lines.size() * font.getLineSpacing(characterSize)));
		}
		else
			rect.setSize(size);

		rect.setFillColor(rect_color);
		rect.setPosition(position.x + cam->position.x, position.y + cam->position.y);

	}

	void setCharacterSize(short val) {

		characterSize = val;

		lines = wrapText(text, wrapper_type, font, characterSize, line_length - 2 * margin);

		generateText();
	}

	void setFont(sf::Font& font) {
		this->font = font;

		lines = wrapText(text, wrapper_type, font, characterSize, line_length - 2 * margin);

		generateText();
	}

	void setRectSize(sf::Vector2f size) {

		generateRect(size);
		generateText();
	}

	void setWstring(std::wstring text) {

		this->text = text;

		lines = wrapText(text, wrapper_type, font, characterSize, line_length - 2 * margin);

		generateText();
	}

	void setPosition(sf::Vector2f position) {
		this->position = position;

		
		rect.setPosition(position.x + cam->position.x, position.y + cam->position.y);
		generateText();
	}

	sf::Vector2f getSize() {
		return rect.getSize();

	}

	void setAlignment(TextAlignment alignment) {
		this->alignment = alignment;
		generateText();
	}

	void setVerticalAlignment(VerticalAlignment alignment) {
		this->vertical_alignment = alignment;
		generateText();
	}

	void update() {

	}

	void draw() {
		window->draw(rect);
		for (auto& t : texts)
			window->draw(t);
	}
};
#endif