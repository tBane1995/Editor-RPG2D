#ifndef ScrollableText_hpp
#define ScrollableText_hpp

class ScrollableText : public Panel {
public:

	TextArea* textarea;
	Scrollbar* scrollbar;
	sf::RenderTexture text_texture;
	sf::Sprite text_sprite;

	ScrollableText(std::wstring text) : Panel(sf::Vector2f(600 + 16, 400 + 16), DialogType::ScrollableText) {

		sf::Vector2f scrollbar_size = sf::Vector2f(16, size.y - 2.0f * dialog_border_width - 16);

		textarea = new TextArea(text, cam->position, size.x - 2.0f * dialog_border_width - 2.0f * 8 - scrollbar_size.x);
		textarea->setRectColor(panelColor_normal);
		textarea->setPosition(sf::Vector2f(-size.x / 2.0f + dialog_border_width + 8, -size.y / 2.0f + dialog_border_width + 8));
		sf::Vector2f scrollbar_position = sf::Vector2f(size.x / 2.0f - dialog_border_width - scrollbar_size.x - 8, -size.y / 2.0f + dialog_border_width + 8);
		float line_hgh = textarea->font.getLineSpacing(textarea->characterSize);
		float scroll_max = textarea->getSize().y - this->getSize().y + line_hgh;
		float scroll_step = line_hgh;
		float scroll_len = size.y - 2.0f * (dialog_border_width + 8);
		scrollbar = new Scrollbar(scrollbar_size, scrollbar_position, 0, scroll_max, 0, scroll_step, scroll_len, ScrollbarPartSize::_16);

		// TO-DO - generowanie tekstury przewijalnej dla tekstu - dodać scrollbar onclick
		text_texture.create(size.x - 2.0f * (dialog_border_width + 8) - scrollbar_size.x, size.y - 2.0f * (dialog_border_width + 8));
		sf::View v = sf::View(sf::FloatRect(
			sf::Vector2f(cam->position.x - size.x / 2.0f + dialog_border_width + 8, cam->position.y - size.y / 2.0f + dialog_border_width + 8), 
			sf::Vector2f(size.x - 2 * (dialog_border_width + 8) - scrollbar->size.x, size.y - 2 * (dialog_border_width + 8))));
		text_texture.setView(v);
		text_texture.setSmooth(true);
		text_texture.clear(sf::Color::Transparent);

		for (auto& text : textarea->texts)
			text_texture.draw(text);
		text_texture.display();
		text_sprite = sf::Sprite(text_texture.getTexture());

		sf::Vector2f textpos;
		textpos.x = cam->position.x + position.x - size.x / 2.0f + dialog_border_width + 8;
		textpos.y = cam->position.y + position.y - size.y / 2.0f + dialog_border_width + 8;
		text_sprite.setPosition(textpos);

		sf::Vector2f scroll_rect_size;
		scroll_rect_size.x = this->text_texture.getSize().x + scrollbar->size.x;
		scroll_rect_size.y = scrollbar->size.y;

		scrollbar->setScrollAreaSize(scroll_rect_size);
		scrollbar->setScrollAreaPosition(sf::Vector2f(text_sprite.getPosition() - cam->position));
	}

	~ScrollableText() {
		delete textarea;
		delete scrollbar;
	}

	void handleEvent(sf::Event& event) {

		scrollbar->handleEvent(event);

		sf::Vector2f position;
		position.x = textarea->position.x;
		position.y = dialog_border_width + 8 - scrollbar->scroll_value - size.y / 2.0f;
		std::cout << position.y << "\n";
		textarea->setPosition(position);

		sf::View v = sf::View(sf::FloatRect(sf::Vector2f(cam->position.x - size.x / 2.0f + dialog_border_width + 8, cam->position.y - size.y / 2.0f + dialog_border_width + 8), sf::Vector2f(size.x - 2 * (dialog_border_width + 8) - scrollbar->size.x, size.y - 2 * (dialog_border_width + 8))));
		text_texture.setView(v);
		text_texture.clear(sf::Color::Transparent);
		text_texture.draw(textarea->rect);
		for (auto& text : textarea->texts)
			text_texture.draw(text);
		text_texture.display();

	}

	void update() {
		GUIwasOpen = true;
		scrollbar->update();
	}

	void draw() {
		Panel::draw();
		
		window->draw(text_sprite);
		scrollbar->draw();
	}

};


#endif