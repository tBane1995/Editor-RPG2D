#ifndef Buttons_hpp
#define Buttons_hpp

sf::Color idleColor = sf::Color(32.0f, 32.0f, 32.0f);
sf::Color hoverColor = sf::Color(40.0f, 40.0f, 40.0f);
sf::Color pressedColor = sf::Color(48.0f, 48.0f, 48.0f);

sf::Color spriteIdleColor = sf::Color(192.0f, 192.0f, 192.0f);
sf::Color spriteHoverColor = sf::Color(224.0f, 224.0f, 224.0f);
sf::Color spritePressedColor = sf::Color::White;

enum class ButtonState { Idle, Hover, Pressed };

class Btn : public ElementGUI {
public:
    sf::Vector2f position;
    sf::RectangleShape rect;
    sf::Sprite sprite;
    ButtonState state;
    std::function<void()> hover_func;
    std::function<void()> onclick_func;
    sf::Time clickTime;
    SingleTexture* texture = nullptr;

    Btn(float width = 64, float height = 64, sf::Vector2f position = sf::Vector2f(0, 0)) : ElementGUI() {
        this->position = position;

        rect = sf::RectangleShape(sf::Vector2f(width, height));
        rect.setOrigin(width / 2, height / 2);
        rect.setPosition(position.x + cam->position.x, position.y + cam->position.y);

        sprite = sf::Sprite();

        state = ButtonState::Idle;
        hover_func = { };
        onclick_func = { };

        clickTime = currentTime;

        changeColor();
    }

    Btn(Btn* btn) : ElementGUI() {
        this->position = btn->position;

        this->rect = btn->rect;
        this->sprite = btn->sprite;

        state = ButtonState::Idle;
        this->hover_func = btn->hover_func;
        this->onclick_func = btn->onclick_func;

        clickTime = currentTime;

        changeColor();
    }

    Btn(Btn* btn, sf::Vector2f position) : ElementGUI() {
        this->position = position;

        this->rect = btn->rect;
        this->rect.setPosition(position.x + cam->position.x, position.y + cam->position.y);
        this->sprite = btn->sprite;
        this->sprite.setPosition(position.x + cam->position.x, position.y + cam->position.y);

        state = ButtonState::Idle;
        this->hover_func = btn->hover_func;
        this->onclick_func = btn->onclick_func;

        clickTime = currentTime;

        changeColor();
    }

    Btn(SingleTexture* texture, sf::Vector2f position) : ElementGUI() {
        this->position = position;
        this->texture = texture;

        sf::Vector2f size = sf::Vector2f(texture->texture->getSize().x, texture->texture->getSize().y);
        rect = sf::RectangleShape(size);
        rect.setOrigin(size.x / 2, size.y / 2);
        rect.setPosition(position.x + cam->position.x, position.y + cam->position.y);

        sprite = sf::Sprite();
        sprite.setTexture(*texture->texture);
        sprite.setOrigin(texture->texture->getSize().x / 2.0f, texture->texture->getSize().y / 2.0f);

        sf::Vector2f scale = sf::Vector2f(size.x / texture->texture->getSize().x, size.y / texture->texture->getSize().y);
        sprite.setScale(scale);
        sprite.setPosition(position.x + cam->position.x, position.y + cam->position.y);

        state = ButtonState::Idle;

        hover_func = { };
        onclick_func = { };

        clickTime = currentTime;

        changeColor();
    }


    void setTexture(SingleTexture* texture) {
        sf::Vector2f size = sf::Vector2f(texture->texture->getSize().x, texture->texture->getSize().y);
        rect = sf::RectangleShape(size);
        rect.setOrigin(size.x / 2, size.y / 2);
        rect.setPosition(position.x + cam->position.x, position.y + cam->position.y);

        sprite = sf::Sprite();
        sprite.setTexture(*texture->texture);
        sprite.setOrigin(texture->texture->getSize().x / 2, texture->texture->getSize().y / 2);
        sf::Vector2f scale = sf::Vector2f(size.x / texture->texture->getSize().x, size.y / texture->texture->getSize().y);
        sprite.setScale(scale);
        sprite.setPosition(position.x + cam->position.x, position.y + cam->position.y);
        this->texture = texture;

        changeColor();
    }

    void setPosition(sf::Vector2f position) {
        this->position = position;
        rect.setPosition(position.x + cam->position.x, position.y + cam->position.y);
        sprite.setPosition(position.x + cam->position.x, position.y + cam->position.y);
    }

    void changeColor() {

        if (state == ButtonState::Pressed) {
            rect.setFillColor(pressedColor);
            sprite.setColor(spritePressedColor);
        }
        else if (state == ButtonState::Hover) {
            rect.setFillColor(hoverColor);
            sprite.setColor(spriteHoverColor);
        }
        else {
            rect.setFillColor(idleColor);
            sprite.setColor(spriteIdleColor);
        }

    }

    void unclick() {
        state = ButtonState::Idle;
        changeColor();

    }

    void hover() {
        state = ButtonState::Hover;
        changeColor();
        GUIwasHover = true;

    }

    void click() {

        state = ButtonState::Pressed;
        changeColor();
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

    void update(bool hover_action = true) {

        rect.setPosition(position + cam->position);
        sprite.setPosition(position+cam->position);

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

    void draw() {
        window->draw(rect);
        if (sprite.getTexture() != nullptr)
            window->draw(sprite);
    }

};

class ButtonWithText : public ElementGUI {
public:
    sf::Vector2f position;
    sf::RectangleShape rect;
    sf::Text text;
    ButtonState state;
    std::function<void()> hover_func;
    std::function<void()> onclick_func;
    sf::Time clickTime;
    short margin;
    TextAlignment align;
    sf::Color idleCol, hoverCol, pressCol, textCol;

    ButtonWithText(std::string s, short characterSize = 17, TextAlignment align = TextAlignment::Left, sf::Vector2f size = sf::Vector2f(-1,-1)) : ElementGUI() {
        this->position = sf::Vector2f(0, 0);
        margin = float(characterSize) * 0.4f;
        this->align = align;

        idleCol = idleColor;
        hoverCol = hoverColor;
        pressCol = pressedColor;
        textCol = textColor;

        text = sf::Text();
        text.setFont(basicFont);
        text.setFillColor(textCol);
        text.setCharacterSize(characterSize);
        text.setString(s);

        rect = sf::RectangleShape();
        if (size == sf::Vector2f(-1, -1)) {
            size.x = text.getLocalBounds().getSize().x + float(margin) * 2.15f;
            size.y = float(text.getCharacterSize()) * 1.1f + float(margin) * 1.8f;
        }
        else if (size.x != -1 && size.y == -1) {
            size.y = float(text.getCharacterSize()) * 1.1f + float(margin) * 1.8f;
        }
        
        rect.setSize(size);
        rect.setFillColor(idleCol);

        setPosition(position);

        state = ButtonState::Idle;
        hover_func = { };
        onclick_func = { };

        clickTime = currentTime;
    }

	virtual ~ButtonWithText() { }

    void setPosition(sf::Vector2f position) {
        this->position = position;

        if (align == TextAlignment::Left)
            text.setPosition(position.x + cam->position.x + margin, position.y + cam->position.y + float(margin) * 0.6f);
        else if (align == TextAlignment::Center)
            text.setPosition(
                position.x + cam->position.x + rect.getSize().x / 2.0f - (text.getLocalBounds().width / 2.0f + text.getLocalBounds().left),
                position.y + cam->position.y + float(margin) * 0.6f
            );

        rect.setPosition(position.x + cam->position.x, position.y + cam->position.y);

    }

    void changeColor() {

        if (state == ButtonState::Pressed) {
            rect.setFillColor(pressCol);
        }
        else if (state == ButtonState::Hover) {
            rect.setFillColor(hoverCol);
        }
        else {
            rect.setFillColor(idleCol);
        }

    }

    sf::Vector2f getSize() {

        return sf::Vector2f(rect.getSize().x + rect.getOutlineThickness() * 2.0f, rect.getSize().y + rect.getOutlineThickness() * 2.0f);
    }

    void unclick() {
        state = ButtonState::Idle;
        changeColor();
    }

    void hover() {

        state = ButtonState::Hover;
        changeColor();
        GUIwasHover = true;
    }

    void click() {

        state = ButtonState::Pressed;
        changeColor();
        GUIwasClicked = true;
        clickTime = currentTime;
    }

    void setColors(sf::Color idleColor, sf::Color hoverColor, sf::Color pressedColor, sf::Color textColor) {
        idleCol = idleColor;
        hoverCol = hoverColor;
        pressCol = pressedColor;
        textCol = textColor;
    }

	void cursorHover() {
		if (mouse_state != MouseState::Selecting) {

            if (rect.getGlobalBounds().contains(worldMousePosition)) {

				ElementGUI_hovered = this;
			}
		}
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

    virtual void update(bool hover_action = true) {

        setPosition(position);

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

    virtual void draw() {

        window->draw(rect);
        window->draw(text);
    }


};

class ButtonWithImage : public ElementGUI {
public:

    sf::Vector2f position;
    sf::Sprite sprite;
    ButtonState state;
    std::function<void()> hover_func;
    std::function<void()> onclick_func;
    sf::Time clickTime;
    SingleTexture* texture = nullptr;

    ButtonWithImage() : ElementGUI() {
        sprite = sf::Sprite();
        state = ButtonState::Idle;
        hover_func = { };
        onclick_func = { };

        clickTime = currentTime;
        changeColor();
    }

    ButtonWithImage(ButtonWithImage* btn) : ElementGUI() {

        this->position = btn->position;
        this->sprite = btn->sprite;
        state = ButtonState::Idle;
        this->hover_func = btn->hover_func;
        this->onclick_func = btn->onclick_func;

        sprite.setPosition(position + cam->position);


        clickTime = currentTime;
        changeColor();
    }

    ButtonWithImage(ButtonWithImage* btn, sf::Vector2f position) : ElementGUI() {
        this->position = position;
        this->sprite = btn->sprite;
        this->texture = btn->texture;
        state = ButtonState::Idle;
        this->hover_func = btn->hover_func;
        this->onclick_func = btn->onclick_func;

        sprite.setPosition(position + cam->position);

        clickTime = currentTime;
        changeColor();

    }

    ButtonWithImage(SingleTexture* texture, sf::Vector2f position) : ElementGUI() {
        this->position = position;
        this->texture = texture;

        sprite = sf::Sprite();

        state = ButtonState::Idle;

        if (texture != nullptr) {
            sprite.setTexture(*texture->texture);
            sprite.setOrigin(texture->texture->getSize().x / 2.0f, texture->texture->getSize().y / 2.0f);
        }

        sprite.setPosition(position + cam->position);

        hover_func = { };
        onclick_func = { };

        clickTime = currentTime;
        changeColor();
    }

    ButtonWithImage(SingleTexture* texture) : ElementGUI() {
        this->position = sf::Vector2f(0,0);
        this->texture = texture;

        sprite = sf::Sprite();

        state = ButtonState::Idle;

        if (texture != nullptr) {
            sprite.setTexture(*texture->texture);
            sprite.setOrigin(texture->texture->getSize().x / 2.0f, texture->texture->getSize().y / 2.0f);
        }

        sprite.setPosition(position + cam->position);

        hover_func = { };
        onclick_func = { };

        clickTime = currentTime;
        changeColor();
    }

    ~ButtonWithImage() {

    }

    void setTexture(SingleTexture* texture) {
        sprite = sf::Sprite();
        sprite.setTexture(*texture->texture);
        sprite.setOrigin(texture->texture->getSize().x / 2, texture->texture->getSize().y / 2);
        sprite.setPosition(cam->position + position);
        changeColor();
        this->texture = texture;
    }

    void setPosition(sf::Vector2f position) {
        this->position = position;
        sprite.setPosition(sf::Vector2f(position+cam->position));
    }

    void changeColor() {
        if (state == ButtonState::Pressed) {
            sprite.setColor(spritePressedColor);
        }
        else if (state == ButtonState::Hover) {
            sprite.setColor(spriteHoverColor);
        }
        else {
            sprite.setColor(spriteIdleColor);
        }

    }

    void unclick() {
        state = ButtonState::Idle;
        changeColor();
    }

    void hover() {
        state = ButtonState::Hover;
        changeColor();
        GUIwasHover = true;

        if (hover_func)
            hover_func();

    }

    void click() {
        state = ButtonState::Pressed;
        changeColor();
        GUIwasClicked = true;
        clickTime = currentTime;
    }

    void cursorHover() {
        if (mouse_state != MouseState::Selecting) {

            sf::FloatRect rect;
            rect.width = 0.0f;
            rect.height = 0.0f;

            if (texture)
            {
                rect.width = texture->texture->getSize().x;
                rect.height = texture->texture->getSize().y;
            }
            else
            {
                rect.width = sprite.getTextureRect().width;
                rect.height = sprite.getTextureRect().height;

            }

            rect.left = sprite.getPosition().x - rect.width / 2.0f;
            rect.top = sprite.getPosition().y - rect.height / 2.0f;

            if (rect.contains(worldMousePosition)) {

                ElementGUI_hovered = this;
            }
        }
    }

    void handleEvent(sf::Event& event) {


        if (true) { // TO-DO
            sf::FloatRect rect;
            rect.width = 0.0f;
            rect.height = 0.0f;

            if (texture)
            {
                rect.width = texture->texture->getSize().x;
                rect.height = texture->texture->getSize().y;
            }
            else
            {
                rect.width = sprite.getTextureRect().width;
                rect.height = sprite.getTextureRect().height;

            }

            rect.left = sprite.getPosition().x - rect.width / 2.0f;
            rect.top = sprite.getPosition().y - rect.height / 2.0f;

            if (rect.contains(worldMousePosition)) {

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
    }

    void update(bool hover_action = true) {

        sprite.setPosition(position + cam->position);
        if (state == ButtonState::Pressed) {

            if ((currentTime - clickTime).asSeconds() > 0.05f) {

                if (onclick_func) {
                    onclick_func();
                }
                unclick();
            }

            
        }
        else if ( hover_action && ElementGUI_hovered == this) {
            hover();
        }
        else
            unclick();

    }

    virtual void draw() {
        window->draw(sprite);
    }
};




class ButtonWithTextAndIcon : public ElementGUI {
public:
    sf::Vector2f position;
    sf::RectangleShape rect;
    sf::Text text;
    sf::Sprite _icon;
    ButtonState state;
    std::function<void()> hover_func;
    std::function<void()> onclick_func;
    sf::Time clickTime;
    short margin;

    sf::Vector2u icon_size;


    ButtonWithTextAndIcon(std::wstring s, SingleTexture* icon) : ElementGUI() {

        float characterSize = 17;
        icon_size = icon->texture->getSize();

        this->position = sf::Vector2f(0, 0);
        margin = float(characterSize) * 0.4f;

        _icon = sf::Sprite();
        _icon.setTexture(*icon->texture);
        _icon.setPosition(position + cam->position);

        text = sf::Text();
        text.setFont(basicFont);
        text.setFillColor(textColor);
        text.setCharacterSize(characterSize);
        text.setString(s);
        text.setPosition(position.x + cam->position.x + float(margin) * 0.95f + icon_size.x, position.y + cam->position.y + float(margin) * 0.6f);

        rect = sf::RectangleShape();
        sf::Vector2f size;
        size.x = text.getLocalBounds().getSize().x + float(margin) * 2.15f + icon_size.x;
        size.y = float(text.getCharacterSize()) * 1.1f + float(margin) * 1.8f;
        rect.setSize(size);
        rect.setFillColor(idleColor);
        rect.setPosition(position + cam->position);

        state = ButtonState::Idle;
        hover_func = { };
        onclick_func = { };

        clickTime = currentTime;
    }

    void setPosition(sf::Vector2f position) {
        this->position = position;
        _icon.setPosition(position + cam->position);
        text.setPosition(position.x + cam->position.x + margin + icon_size.x, position.y + cam->position.y + float(margin) * 0.6f);
        rect.setPosition(position + cam->position);

    }

    void changeColor() {

        if (state == ButtonState::Pressed) {
            rect.setFillColor(pressedColor);
        }
        else if (state == ButtonState::Hover) {
            rect.setFillColor(hoverColor);
        }
        else {
            rect.setFillColor(idleColor);
        }

    }

    void setRectSize(sf::Vector2f rect_size) {
        rect.setSize(rect_size);
    }

    void unclick() {
        state = ButtonState::Idle;
        changeColor();
    }

    void hover() {

        state = ButtonState::Hover;
        changeColor();
        GUIwasHover = true;
    }

    void click() {

        state = ButtonState::Pressed;
        changeColor();
        GUIwasClicked = true;
        clickTime = currentTime;
    }

    void cursorHover() {

        if (rect.getGlobalBounds().contains(worldMousePosition)) {
            
			ElementGUI_hovered = this;
        }
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

    void update(bool hover_action = true) {

        rect.setPosition(position + cam->position);
        _icon.setPosition(position + cam->position);
        text.setPosition(position.x + cam->position.x + float(margin) * 0.95f +icon_size.x, position.y + cam->position.y + float(margin) * 0.6f);

        if (state == ButtonState::Pressed) {

            if ((currentTime - clickTime).asSeconds() > 0.05f) {
                if (onclick_func) {
                    onclick_func();
                }
                unclick();
            }
        }
        else if (hover_action && ElementGUI_hovered == this) {
            hover();
        }
        else
            unclick();


    }

    void draw() {

        window->draw(rect);
        window->draw(_icon);
        window->draw(text);
    }
};


#endif