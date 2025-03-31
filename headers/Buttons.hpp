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
            float w = rect.getSize().x;
            float h = rect.getSize().y;
            float x = rect.getPosition().x;
            float y = rect.getPosition().y;

            if (worldMousePosition.x > x - w / 2.0f && worldMousePosition.x < x + w / 2.0f &&
                worldMousePosition.y > y - h / 2.0f && worldMousePosition.y < y + h / 2.0f) {

                ElementGUI_hovered = this;

            }
        }
    }

    void handleEvent(sf::Event& event) {

        float w = rect.getSize().x;
        float h = rect.getSize().y;
        float x = rect.getPosition().x;
        float y = rect.getPosition().y;

        if (worldMousePosition.x > x - w / 2.0f && worldMousePosition.x < x + w / 2.0f &&
            worldMousePosition.y > y - h / 2.0f && worldMousePosition.y < y + h / 2.0f) {

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

        rect.setPosition(cam->position.x + position.x, cam->position.y + position.y);
        sprite.setPosition(cam->position.x + position.x, cam->position.y + position.y);

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

    ButtonWithText(std::string s, sf::Vector2f position = sf::Vector2f(0, 0), short characterSize = 17) : ElementGUI() {
        this->position = position;
        margin = float(characterSize) * 0.4f;
        
        text = sf::Text();
        text.setFont(basicFont);
        text.setFillColor(textColor);
        text.setCharacterSize(characterSize);
        text.setString(s);
        text.setPosition(position.x + cam->position.x + float(margin) * 0.95f, position.y + cam->position.y + float(margin) * 0.6f);

        rect = sf::RectangleShape();
        sf::Vector2f size;
        size.x = text.getLocalBounds().getSize().x + float(margin) * 2.15f;
        size.y = float(text.getCharacterSize()) * 1.1f + float(margin) * 1.8f;
        rect.setSize(size);
        rect.setFillColor(idleColor);
        rect.setPosition(position.x + cam->position.x, position.y + cam->position.y);

        state = ButtonState::Idle;
        hover_func = { };
        onclick_func = { };

        clickTime = currentTime;
    }

    ButtonWithText(std::string s, short characterSize) : ElementGUI() {

        this->position = sf::Vector2f(0, 0);
        margin = float(characterSize) * 0.4f;

        text = sf::Text();
        text.setFont(basicFont);
        text.setFillColor(textColor);
        text.setCharacterSize(characterSize);
        text.setString(s);
        text.setPosition(position.x + cam->position.x + float(margin) * 0.95f, position.y + cam->position.y + float(margin) * 0.6f);

        rect = sf::RectangleShape();
        sf::Vector2f size;
        size.x = text.getLocalBounds().getSize().x + float(margin) * 2.15f;
        size.y = float(text.getCharacterSize()) * 1.1f + float(margin) * 1.8f;
        rect.setSize(size);
        rect.setFillColor(idleColor);
        rect.setPosition(position.x + cam->position.x, position.y + cam->position.y);

        state = ButtonState::Idle;
        hover_func = { };
        onclick_func = { };

        clickTime = currentTime;
    }

	virtual ~ButtonWithText() { }

    void setPosition(sf::Vector2f position) {
        this->position = position;
        text.setPosition(position.x + cam->position.x + margin, position.y + cam->position.y + float(margin) * 0.6f);
        rect.setPosition(position.x + cam->position.x, position.y + cam->position.y);

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
            float w = rect.getSize().x;
            float h = rect.getSize().y;
            float x = rect.getPosition().x;
            float y = rect.getPosition().y;

            if (worldMousePosition.x > x && worldMousePosition.x < x + w &&
                worldMousePosition.y > y && worldMousePosition.y < y + h) {

				ElementGUI_hovered = this;
			}
		}
	}

    void handleEvent(sf::Event& event) {

        float w = rect.getSize().x;
        float h = rect.getSize().y;
        float x = rect.getPosition().x;
        float y = rect.getPosition().y;

        if (worldMousePosition.x > x && worldMousePosition.x < x + w &&
            worldMousePosition.y > y && worldMousePosition.y < y + h) {

            if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
                ElementGUI_pressed = this;
            }
            else if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left) {
                if (ElementGUI_pressed == this) {
                    std::cout << "click\n";
                    click();
                }
            }
        }
    }

    virtual void update(bool hover_action = true) {

        rect.setPosition(position.x + cam->position.x, position.y + cam->position.y);
        text.setPosition(position.x + cam->position.x + float(margin) * 0.95f, position.y + cam->position.y + float(margin) * 0.6f);

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

        sprite.setPosition(cam->position.x + position.x, cam->position.y + position.y);


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

        sprite.setPosition(cam->position.x + position.x, cam->position.y + position.y);

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

        sprite.setPosition(cam->position.x + position.x, cam->position.y + position.y);

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

        sprite.setPosition(cam->position.x + position.x, cam->position.y + position.y);

        hover_func = { };
        onclick_func = { };

        clickTime = currentTime;
        changeColor();
    }


    void setTexture(SingleTexture* texture) {
        sprite = sf::Sprite();
        sprite.setTexture(*texture->texture);
        sprite.setOrigin(texture->texture->getSize().x / 2, texture->texture->getSize().y / 2);
        sprite.setPosition(cam->position.x + position.x, cam->position.y + position.y);
        changeColor();
        this->texture = texture;
    }

    void setPosition(sf::Vector2f position) {
        this->position = position;
        sprite.setPosition(sf::Vector2f(position.x+cam->position.x, position.y+cam->position.y));
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
            float w = 0.0f;
            float h = 0.0f;
            float x = sprite.getPosition().x;
            float y = sprite.getPosition().y;

            if (texture)
            {
                w = texture->texture->getSize().x;
                h = texture->texture->getSize().y;
            }
            else
            {
                w = sprite.getTextureRect().width;
                h = sprite.getTextureRect().height;

            }

            if (worldMousePosition.x > x - w / 2.0f && worldMousePosition.x < x + w / 2.0f &&
                worldMousePosition.y > y - h / 2.0f && worldMousePosition.y < y + h / 2.0f) {

                ElementGUI_hovered = this;
            }
        }
    }

    void handleEvent(sf::Event& event) {


        if (true) {
            float w = 0.0f;
            float h = 0.0f;
            float x = sprite.getPosition().x;
            float y = sprite.getPosition().y;

            if (texture)
            {
                w = texture->texture->getSize().x;
                h = texture->texture->getSize().y;
            }
            else
            {
                w = sprite.getTextureRect().width;
                h = sprite.getTextureRect().height;

            }

            if (worldMousePosition.x > x - w / 2.0f && worldMousePosition.x < x + w / 2.0f &&
                worldMousePosition.y > y - h / 2.0f && worldMousePosition.y < y + h / 2.0f) {

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

        sprite.setPosition(cam->position.x + position.x, cam->position.y + position.y);
        if (state == ButtonState::Pressed) {

            std::cout << "pressed\n";

            if ((currentTime - clickTime).asSeconds() > 0.05f) {

                std::cout << "time ok\n";

                if (onclick_func) {
                    std::cout << "click2\n";
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

    void draw() {
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
        _icon.setPosition(position.x + cam->position.x, position.y + cam->position.y);

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
        rect.setPosition(position.x + cam->position.x, position.y + cam->position.y);

        state = ButtonState::Idle;
        hover_func = { };
        onclick_func = { };

        clickTime = currentTime;
    }

    void setPosition(sf::Vector2f position) {
        this->position = position;
        _icon.setPosition(position.x + cam->position.x, position.y + cam->position.y);
        text.setPosition(position.x + cam->position.x + margin + icon_size.x, position.y + cam->position.y + float(margin) * 0.6f);
        rect.setPosition(position.x + cam->position.x, position.y + cam->position.y);

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
        float w = rect.getSize().x;
        float h = rect.getSize().y;
        float x = rect.getPosition().x;
        float y = rect.getPosition().y;

        if (worldMousePosition.x > x && worldMousePosition.x < x + w &&
            worldMousePosition.y > y && worldMousePosition.y < y + h) {
            
			ElementGUI_hovered = this;
        }
    }

    void handleEvent(sf::Event& event) {


        float w = rect.getSize().x;
        float h = rect.getSize().y;
        float x = rect.getPosition().x;
        float y = rect.getPosition().y;

        if (worldMousePosition.x > x && worldMousePosition.x < x + w &&
            worldMousePosition.y > y && worldMousePosition.y < y + h) {

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

        rect.setPosition(position.x + cam->position.x, position.y + cam->position.y);
        _icon.setPosition(position.x + cam->position.x, position.y + cam->position.y);
        text.setPosition(position.x + cam->position.x + float(margin) * 0.95f +icon_size.x, position.y + cam->position.y + float(margin) * 0.6f);

        if (state == ButtonState::Pressed) {
            std::cout << "btn is pressed\n";
            if ((currentTime - clickTime).asSeconds() > 0.05f) {
                std::cout << "time ok \n";
                if (onclick_func) {
                    std::cout << "click333\n";
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

class ButtonFromDialog {
public:
    sf::Vector2f position;
    sf::RectangleShape rect;
    sf::Text text;
    ButtonState state;
    std::function<void()> hover_func;
    std::function<void()> onclick_func;
    sf::Time clickTime;

    ButtonFromDialog(string text, float border_width = button_border_width) {

        this->position = position;

        float characterSize = 17.0f;
        float margin = characterSize * 0.4f;

        sf::Vector2f rect_size;
        rect_size.y = characterSize * 1.1f + margin * 1.8f - border_width * 2;
        rect_size.x = rect_size.y * 70.0f / 30.0f - border_width * 2;


        rect = sf::RectangleShape(rect_size);
        rect.setOrigin(rect_size.x / 2, rect_size.y / 2);
        rect.setFillColor(idleColor);
        rect.setPosition(position.x + cam->position.x, position.y + cam->position.y);
        rect.setOutlineColor(sf::Color::Black);
        rect.setOutlineThickness(border_width);

        this->text = sf::Text();
        this->text.setFont(basicFont);
        this->text.setFillColor(textColor);
        this->text.setCharacterSize(characterSize);
        this->text.setString(text);
        this->text.setOrigin(this->text.getGlobalBounds().getSize().x / 2, characterSize*0.65f);
        this->text.setPosition(position.x + cam->position.x, position.y + cam->position.y);

        state = ButtonState::Idle;
        hover_func = { };
        onclick_func = { };

        clickTime = currentTime;
    }

    ~ButtonFromDialog() { }

    void setPosition(sf::Vector2f position) {
        this->position = position;

        this->rect.setPosition(position.x + cam->position.x, position.y + cam->position.y);
        this->text.setPosition(this->text.getGlobalBounds().getSize().x / 2, this->text.getGlobalBounds().getSize().y / 2);


    }

    sf::Vector2f getSize() {
        
		return sf::Vector2f(rect.getSize().x + rect.getOutlineThickness() * 2.0f, rect.getSize().y + rect.getOutlineThickness() * 2.0f);
    }

    virtual void changeColor() {

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

    virtual void unclick() {
        state = ButtonState::Idle;
        changeColor();
    }

    virtual void hover() {

        state = ButtonState::Hover;
        changeColor();
        GUIwasHover = true;
    }

    virtual void click() {

        state = ButtonState::Pressed;
        changeColor();
        GUIwasClicked = true;
        clickTime = currentTime;
    }

    virtual void handleEvent(sf::Event& event) {

        if (mouse_state != MouseState::Selecting) {

            float w = rect.getSize().x + rect.getOutlineThickness()*2.0f;
            float h = rect.getSize().y + rect.getOutlineThickness() * 2.0f;
            float x = rect.getPosition().x;
            float y = rect.getPosition().y;

            if (worldMousePosition.x > x - w/2 && worldMousePosition.x < x + w/2 &&
                worldMousePosition.y > y - h/2 && worldMousePosition.y < y + h/2) {

                if (event.type == sf::Event::MouseButtonReleased)
                    if (event.mouseButton.button == sf::Mouse::Left)
                        click();

            }
        }
    }

    virtual void update(bool hover_action = true) {

        rect.setPosition(position.x + cam->position.x, position.y + cam->position.y);
        text.setPosition(position.x + cam->position.x, position.y + cam->position.y);

        if ((currentTime - clickTime).asSeconds() > 0.05f) {
            if (state == ButtonState::Pressed) {
                if (onclick_func)
                    onclick_func();
            }
            unclick();
        }



        if (hover_action && mouse_state != MouseState::Selecting && state != ButtonState::Pressed) {

            float w = rect.getSize().x + rect.getOutlineThickness() * 2.0f;
            float h = rect.getSize().y + rect.getOutlineThickness() * 2.0f;
            float x = rect.getPosition().x;
            float y = rect.getPosition().y;

            if (worldMousePosition.x > x - w/2 && worldMousePosition.x < x + w/2 &&
                worldMousePosition.y > y - h/2 && worldMousePosition.y < y + h/2) {
                hover();
            }
        }


    }

    virtual void draw() {

        window->draw(rect);
        window->draw(text);
    }
};


#endif