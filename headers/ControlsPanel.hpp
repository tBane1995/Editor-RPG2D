#ifndef ControlsPanel_hpp
#define ControlsPanel_hpp

class ControlsPanel {
public:

    sf::Text title;
    sf::Text press;

    sf::Sprite panel;

    sf::Sprite up;
    sf::Sprite down;
    sf::Sprite left;
    sf::Sprite right;
    sf::Sprite space;
    sf::Sprite e;
    sf::Sprite h;
    sf::Sprite j;

    sf::Text uptext;
    sf::Text downtext;
    sf::Text lefttext;
    sf::Text righttext;
    sf::Text spacetext;
    sf::Text etext;
    sf::Text htext;
    sf::Text jtext;


	ControlsPanel() {
        title = sf::Text("controls", basicFont, 32);
        title.setFillColor(dialoguesColor);
        title.setOrigin(title.getLocalBounds().width / 2.f, title.getLocalBounds().height / 2.f);

        press = sf::Text("press space to continue", basicFont, 16);
        press.setFillColor(dialoguesColor);
        press.setOrigin(press.getLocalBounds().width / 2.f, press.getLocalBounds().height / 2.f);

        panel = sf::Sprite();
        panel.setTexture(*getSingleTexture("GUI\\bigPanel")->texture);
        panel.setOrigin(300, 200);

        up = sf::Sprite();
        up.setTexture(*getSingleTexture("GUI\\smallButtons\\smallbutton-ArrowUp")->texture);
        up.setOrigin(20, 20);

        down = sf::Sprite() ;
        down.setTexture(*getSingleTexture("GUI\\smallButtons\\smallbutton-ArrowDown")->texture);
        down.setOrigin(20, 20);

        left = sf::Sprite();
        left.setTexture(*getSingleTexture("GUI\\smallButtons\\smallbutton-ArrowLeft")->texture);
        left.setOrigin(20, 20);

        right = sf::Sprite();
        right.setTexture(*getSingleTexture("GUI\\smallButtons\\smallbutton-ArrowRight")->texture);
        right.setOrigin(20, 20);

        space = sf::Sprite();
        space.setTexture(*getSingleTexture("GUI\\spacebutton")->texture);
        space.setOrigin(80, 20);

        e = sf::Sprite();
        e.setTexture(*getSingleTexture("GUI\\smallButtons\\smallbutton")->texture);
        e.setOrigin(20, 20);

        h = sf::Sprite();
        h.setTexture(*getSingleTexture("GUI\\smallButtons\\smallbutton")->texture);
        h.setOrigin(20, 20);

        j = sf::Sprite();
        j.setTexture(*getSingleTexture("GUI\\smallButtons\\smallbutton")->texture);
        j.setOrigin(20, 20);

        uptext = sf::Text("W", basicFont, 16);
        uptext.setOrigin(uptext.getLocalBounds().width / 2, uptext.getLocalBounds().height / 2);

        downtext = sf::Text("S", basicFont, 16);
        downtext.setOrigin(downtext.getLocalBounds().width / 2, downtext.getLocalBounds().height / 2);

        lefttext = sf::Text("A", basicFont, 16);
        lefttext.setOrigin(lefttext.getLocalBounds().width / 2, lefttext.getLocalBounds().height / 2);

        righttext = sf::Text("D", basicFont, 16);
        righttext.setOrigin(righttext.getLocalBounds().width / 2, righttext.getLocalBounds().height / 2);

        spacetext = sf::Text("space", basicFont, 16);
        spacetext.setOrigin(spacetext.getLocalBounds().width / 2, spacetext.getLocalBounds().height / 2);

        etext = sf::Text("E", basicFont, 16);
        etext.setOrigin(etext.getLocalBounds().width / 2, etext.getLocalBounds().height / 2);

        htext = sf::Text("H", basicFont, 16);
        htext.setOrigin(htext.getLocalBounds().width / 2, htext.getLocalBounds().height / 2);

        jtext = sf::Text("J", basicFont, 16);
        jtext.setOrigin(jtext.getLocalBounds().width / 2, jtext.getLocalBounds().height / 2);
	}

	~ControlsPanel() { }

	void update() {

        title.setPosition(cam->position.x, cam->position.y - 200);
        press.setPosition(cam->position.x, cam->position.y + 200);
        panel.setPosition(cam->position);

        sf::Vector2f position = sf::Vector2f(cam->position.x - 270, cam->position.y);
        
        up.setPosition(position.x + 80, position.y - 20);
        down.setPosition(position.x + 80, position.y + 20);
        left.setPosition(position.x + 40, position.y + 20);
        right.setPosition(position.x + 120, position.y + 20);
        space.setPosition(position.x + 280, position.y + 20);
        e.setPosition(position.x + 420, position.y + 20);
        h.setPosition(position.x + 480, position.y + 20);
        j.setPosition(position.x + 540, position.y + 20);
        
        uptext.setPosition(position.x + 80, position.y - 60);
        downtext.setPosition(position.x + 80, position.y + 60);
        lefttext.setPosition(position.x, position.y + 20);
        righttext.setPosition(position.x + 160, position.y + 20);
        spacetext.setPosition(position.x + 280, position.y + 60);
        etext.setPosition(position.x + 420, position.y + 60);
        htext.setPosition(position.x + 480, position.y + 60);
        jtext.setPosition(position.x + 540, position.y + 60);

        
	}

	void draw() {

        window->draw(title);
        window->draw(press);

        window->draw(up);
        window->draw(down);
        window->draw(left);
        window->draw(right);
        window->draw(space);
        window->draw(e);
        window->draw(h);
        window->draw(j);

        window->draw(uptext);
        window->draw(downtext);
        window->draw(lefttext);
        window->draw(righttext);
        window->draw(spacetext);
        window->draw(etext);
        window->draw(htext);
        window->draw(jtext);
	}
};

ControlsPanel* controls = nullptr;

#endif