#ifndef Character_hpp
#define Character_hpp
/*
class Character : public Unit {
public:

	// EQUIPMENT
	Item* helmet;
	Item* armor;
	Item* pants;
	Item* leftHand;
	Item* rightHand;

	// HELMET - textures
	SingleTexture* helmetIdleTextures[16];
	SingleTexture* helmetRunTextures[16];
	SingleTexture* helmetAttackTextures[16];

	// ARMOR - textures
	SingleTexture* armorIdleTextures[16];
	SingleTexture* armorRunTextures[16];
	SingleTexture* armorAttackTextures[16];

	// PANTS - textures
	SingleTexture* pantsIdleTextures[16];
	SingleTexture* pantsRunTextures[16];
	SingleTexture* pantsAttackTextures[16];

	// LEFT HAND - textures
	SingleTexture* leftHandIdleTextures[16];
	SingleTexture* leftHandRunTextures[16];
	SingleTexture* leftHandAttackTextures[16];

	// RIGHT HAND - textures
	SingleTexture* rightHandIdleTextures[16];
	SingleTexture* rightHandRunTextures[16];
	SingleTexture* rightHandAttackTextures[16];

	// SPRITES
	sf::Sprite bodySprite;
	sf::Sprite helmetSprite;
	sf::Sprite armorSprite;
	sf::Sprite pantsSprite;
	sf::Sprite leftHandSprite;
	sf::Sprite rightHandSprite;
	
	//
	sf::RenderTexture* renderTexture;

	Dialogue* dialogue;

	SingleTexture* talkWithTexture;
	sf::Sprite talkWithSprite;
	bool showHand;


	Character(string name, string bodySet="sets\\body\\hero") : Unit(name, bodySet, 36, 18, 64) {
		
		type = GameObjectType::Character;
		
		helmet = nullptr;
		armor = nullptr;
		pants = nullptr;
		leftHand = nullptr;
		rightHand = nullptr;

		renderTexture = new sf::RenderTexture();

		loadBody();
		loadHelmet();
		loadArmor();
		loadPants();
		loadLeftHand();
		loadRightHand();

		dialogue = getDialogue(0);

		talkWithTexture = getSingleTexture("GUI\\talk");
		talkWithSprite = sf::Sprite();
		talkWithSprite.setTexture(*talkWithTexture->texture);
		talkWithSprite.setOrigin(talkWithTexture->cx, talkWithTexture->cy);
		showHand = false;

		
	}

	Character(GameObject* object) : Unit(object) {
		
		type = GameObjectType::Character;
				
		helmet = dynamic_cast <Character*>(object)->helmet;
		armor = dynamic_cast <Character*>(object)->armor;
		pants = dynamic_cast <Character*>(object)->pants;
		leftHand = dynamic_cast <Character*>(object)->leftHand;
		rightHand = dynamic_cast <Character*>(object)->rightHand;

		renderTexture = new sf::RenderTexture();

		loadBody();
		loadHelmet();
		loadArmor();
		loadPants();
		loadLeftHand();
		loadRightHand();
		
		dialogue = dynamic_cast <Character*>(object)->dialogue;

		talkWithTexture = getSingleTexture("GUI\\talk");
		talkWithSprite = sf::Sprite();
		talkWithSprite.setTexture(*talkWithTexture->texture);
		talkWithSprite.setOrigin(talkWithTexture->cx, talkWithTexture->cy);
		showHand = false;

	}

	virtual ~Character() {
		
	}

	void loadBody() {
		for (short i = 0; i < 16; i++) {
			idleTextures[i] = nullptr;
			runTextures[i] = nullptr;
			attackTextures[i] = nullptr;

		}

		for (short i = 0; i < 4; i++) {

			idleTextures[i] = getSingleTexture(bodySet + "\\idleTop" + to_string(i));
			idleTextures[4 + i] = getSingleTexture(bodySet + "\\idleRight" + to_string(i));
			idleTextures[8 + i] = getSingleTexture(bodySet + "\\idleBottom" + to_string(i));
			idleTextures[12 + i] = getSingleTexture(bodySet + "\\idleLeft" + to_string(i));

			runTextures[i] = getSingleTexture(bodySet + "\\runTop" + to_string(i));
			runTextures[4 + i] = getSingleTexture(bodySet + "\\runRight" + to_string(i));
			runTextures[8 + i] = getSingleTexture(bodySet + "\\runBottom" + to_string(i));
			runTextures[12 + i] = getSingleTexture(bodySet + "\\runLeft" + to_string(i));

			attackTextures[i] = getSingleTexture(bodySet + "\\attackTop" + to_string(i));
			attackTextures[4 + i] = getSingleTexture(bodySet + "\\attackRight" + to_string(i));
			attackTextures[8 + i] = getSingleTexture(bodySet + "\\attackBottom" + to_string(i));
			attackTextures[12 + i] = getSingleTexture(bodySet + "\\attackLeft" + to_string(i));

		}

		bodySprite = sf::Sprite();

	}


	void loadHelmet() {

		for (short i = 0; i < 16; i++) {
			helmetIdleTextures[i] = nullptr;
			helmetRunTextures[i] = nullptr;
			helmetAttackTextures[i] = nullptr;

		}

		if (helmet != nullptr) {

			for (short i = 0; i < 4; i++) {
				helmetIdleTextures[i] = getSingleTexture("sets\\" + helmet->name + "\\idleTop" + to_string(i));
				helmetIdleTextures[4 + i] = getSingleTexture("sets\\" + helmet->name + "\\idleRight" + to_string(i));
				helmetIdleTextures[8 + i] = getSingleTexture("sets\\" + helmet->name + "\\idleBottom" + to_string(i));
				helmetIdleTextures[12 + i] = getSingleTexture("sets\\" + helmet->name + "\\idleLeft" + to_string(i));

				helmetRunTextures[i] = getSingleTexture("sets\\" + helmet->name + "\\runTop" + to_string(i));
				helmetRunTextures[4 + i] = getSingleTexture("sets\\" + helmet->name + "\\runRight" + to_string(i));
				helmetRunTextures[8 + i] = getSingleTexture("sets\\" + helmet->name + "\\runBottom" + to_string(i));
				helmetRunTextures[12 + i] = getSingleTexture("sets\\" + helmet->name + "\\runLeft" + to_string(i));

				helmetAttackTextures[i] = getSingleTexture("sets\\" + helmet->name + "\\attackTop" + to_string(i));
				helmetAttackTextures[4 + i] = getSingleTexture("sets\\" + helmet->name + "\\attackRight" + to_string(i));
				helmetAttackTextures[8 + i] = getSingleTexture("sets\\" + helmet->name + "\\attackBottom" + to_string(i));
				helmetAttackTextures[12 + i] = getSingleTexture("sets\\" + helmet->name + "\\attackLeft" + to_string(i));

			}
		}

		helmetSprite = sf::Sprite();

	}

	void loadArmor() {

		for (short i = 0; i < 16; i++) {
			armorIdleTextures[i] = nullptr;
			armorRunTextures[i] = nullptr;
			armorAttackTextures[i] = nullptr;

		}

		if (armor != nullptr) {

			for (short i = 0; i < 4; i++) {
				armorIdleTextures[i] = getSingleTexture("sets\\" + armor->name + "\\idleTop" + to_string(i));
				armorIdleTextures[4 + i] = getSingleTexture("sets\\" + armor->name + "\\idleRight" + to_string(i));
				armorIdleTextures[8 + i] = getSingleTexture("sets\\" + armor->name + "\\idleBottom" + to_string(i));
				armorIdleTextures[12 + i] = getSingleTexture("sets\\" + armor->name + "\\idleLeft" + to_string(i));

				armorRunTextures[i] = getSingleTexture("sets\\" + armor->name + "\\runTop" + to_string(i));
				armorRunTextures[4 + i] = getSingleTexture("sets\\" + armor->name + "\\runRight" + to_string(i));
				armorRunTextures[8 + i] = getSingleTexture("sets\\" + armor->name + "\\runBottom" + to_string(i));
				armorRunTextures[12 + i] = getSingleTexture("sets\\" + armor->name + "\\runLeft" + to_string(i));

				armorAttackTextures[i] = getSingleTexture("sets\\" + armor->name + "\\attackTop" + to_string(i));
				armorAttackTextures[4 + i] = getSingleTexture("sets\\" + armor->name + "\\attackRight" + to_string(i));
				armorAttackTextures[8 + i] = getSingleTexture("sets\\" + armor->name + "\\attackBottom" + to_string(i));
				armorAttackTextures[12 + i] = getSingleTexture("sets\\" + armor->name + "\\attackLeft" + to_string(i));

			}
		}

		armorSprite = sf::Sprite();
	}

	void loadPants() {

		for (short i = 0; i < 16; i++) {
			pantsIdleTextures[i] = nullptr;
			pantsRunTextures[i] = nullptr;
			pantsAttackTextures[i] = nullptr;

		}

		if (pants != nullptr) {

			for (short i = 0; i < 4; i++) {
				pantsIdleTextures[i] = getSingleTexture("sets\\" + pants->name + "\\idleTop" + to_string(i));
				pantsIdleTextures[4 + i] = getSingleTexture("sets\\" + pants->name + "\\idleRight" + to_string(i));
				pantsIdleTextures[8 + i] = getSingleTexture("sets\\" + pants->name + "\\idleBottom" + to_string(i));
				pantsIdleTextures[12 + i] = getSingleTexture("sets\\" + pants->name + "\\idleLeft" + to_string(i));

				pantsRunTextures[i] = getSingleTexture("sets\\" + pants->name + "\\runTop" + to_string(i));
				pantsRunTextures[4 + i] = getSingleTexture("sets\\" + pants->name + "\\runRight" + to_string(i));
				pantsRunTextures[8 + i] = getSingleTexture("sets\\" + pants->name + "\\runBottom" + to_string(i));
				pantsRunTextures[12 + i] = getSingleTexture("sets\\" + pants->name + "\\runLeft" + to_string(i));

				pantsAttackTextures[i] = getSingleTexture("sets\\" + pants->name + "\\attackTop" + to_string(i));
				pantsAttackTextures[4 + i] = getSingleTexture("sets\\" + pants->name + "\\attackRight" + to_string(i));
				pantsAttackTextures[8 + i] = getSingleTexture("sets\\" + pants->name + "\\attackBottom" + to_string(i));
				pantsAttackTextures[12 + i] = getSingleTexture("sets\\" + pants->name + "\\attackLeft" + to_string(i));

			}
		}

		pantsSprite = sf::Sprite();

	}

	void loadLeftHand() {

		for (short i = 0; i < 16; i++) {
			leftHandIdleTextures[i] = nullptr;
			leftHandRunTextures[i] = nullptr;
			leftHandAttackTextures[i] = nullptr;

		}

		if (leftHand != nullptr) {

			for (short i = 0; i < 4; i++) {
				leftHandIdleTextures[i] = getSingleTexture("sets\\" + leftHand->name + "\\idleTop" + to_string(i));
				leftHandIdleTextures[4 + i] = getSingleTexture("sets\\" + leftHand->name + "\\idleRight" + to_string(i));
				leftHandIdleTextures[8 + i] = getSingleTexture("sets\\" + leftHand->name + "\\idleBottom" + to_string(i));
				leftHandIdleTextures[12 + i] = getSingleTexture("sets\\" + leftHand->name + "\\idleLeft" + to_string(i));

				leftHandRunTextures[i] = getSingleTexture("sets\\" + leftHand->name + "\\runTop" + to_string(i));
				leftHandRunTextures[4 + i] = getSingleTexture("sets\\" + leftHand->name + "\\runRight" + to_string(i));
				leftHandRunTextures[8 + i] = getSingleTexture("sets\\" + leftHand->name + "\\runBottom" + to_string(i));
				leftHandRunTextures[12 + i] = getSingleTexture("sets\\" + leftHand->name + "\\runLeft" + to_string(i));

				leftHandAttackTextures[i] = getSingleTexture("sets\\" + leftHand->name + "\\attackTop" + to_string(i));
				leftHandAttackTextures[4 + i] = getSingleTexture("sets\\" + leftHand->name + "\\attackRight" + to_string(i));
				leftHandAttackTextures[8 + i] = getSingleTexture("sets\\" + leftHand->name + "\\attackBottom" + to_string(i));
				leftHandAttackTextures[12 + i] = getSingleTexture("sets\\" + leftHand->name + "\\attackLeft" + to_string(i));

			}
		}

		leftHandSprite = sf::Sprite();

	}

	void loadRightHand() {

		for (short i = 0; i < 16; i++) {
			rightHandIdleTextures[i] = nullptr;
			rightHandRunTextures[i] = nullptr;
			rightHandAttackTextures[i] = nullptr;

		}

		if (rightHand != nullptr) {

			for (short i = 0; i < 4; i++) {
				rightHandIdleTextures[i] = getSingleTexture("sets\\" + rightHand->name + "\\idleTop" + to_string(i));
				rightHandIdleTextures[4 + i] = getSingleTexture("sets\\" + rightHand->name + "\\idleRight" + to_string(i));
				rightHandIdleTextures[8 + i] = getSingleTexture("sets\\" + rightHand->name + "\\idleBottom" + to_string(i));
				rightHandIdleTextures[12 + i] = getSingleTexture("sets\\" + rightHand->name + "\\idleLeft" + to_string(i));

				rightHandRunTextures[i] = getSingleTexture("sets\\" + rightHand->name + "\\runTop" + to_string(i));
				rightHandRunTextures[4 + i] = getSingleTexture("sets\\" + rightHand->name + "\\runRight" + to_string(i));
				rightHandRunTextures[8 + i] = getSingleTexture("sets\\" + rightHand->name + "\\runBottom" + to_string(i));
				rightHandRunTextures[12 + i] = getSingleTexture("sets\\" + rightHand->name + "\\runLeft" + to_string(i));

				rightHandAttackTextures[i] = getSingleTexture("sets\\" + rightHand->name + "\\attackTop" + to_string(i));
				rightHandAttackTextures[4 + i] = getSingleTexture("sets\\" + rightHand->name + "\\attackRight" + to_string(i));
				rightHandAttackTextures[8 + i] = getSingleTexture("sets\\" + rightHand->name + "\\attackBottom" + to_string(i));
				rightHandAttackTextures[12 + i] = getSingleTexture("sets\\" + rightHand->name + "\\attackLeft" + to_string(i));

			}
		}

		rightHandSprite = sf::Sprite();

	}

	void loadTexture() {

		renderTexture->create(64, 64);
		renderTexture->clear(sf::Color::Transparent);

		switch (direction) {
		case 0: // TOP
			renderTexture->draw(rightHandSprite);
			renderTexture->draw(leftHandSprite);
			renderTexture->draw(bodySprite);
			renderTexture->draw(helmetSprite);
			renderTexture->draw(pantsSprite);
			renderTexture->draw(armorSprite);
			break;
		case 1: // RIGHT
			renderTexture->draw(leftHandSprite);
			renderTexture->draw(bodySprite);
			renderTexture->draw(helmetSprite);
			renderTexture->draw(pantsSprite);
			renderTexture->draw(armorSprite);
			renderTexture->draw(rightHandSprite);
			break;
		case 2: // BOTTOM
			renderTexture->draw(bodySprite);
			renderTexture->draw(helmetSprite);
			renderTexture->draw(pantsSprite);
			renderTexture->draw(armorSprite);
			renderTexture->draw(leftHandSprite);
			renderTexture->draw(rightHandSprite);
			break;
		case 3: // LEFT
			renderTexture->draw(rightHandSprite);
			renderTexture->draw(bodySprite);
			renderTexture->draw(helmetSprite);
			renderTexture->draw(pantsSprite);
			renderTexture->draw(armorSprite);
			renderTexture->draw(leftHandSprite);
			break;
		default:
			break;
		}

		renderTexture->display();
		sprite.setTexture(renderTexture->getTexture());
		sprite.setOrigin(32, 58);
		GameObject::draw();
	}

	virtual void update() {

		float dt = currentTime.asSeconds() - prevTime.asSeconds();;
		calculateCurrentFrame(dt);
		GameObject::update();
		textname.setPosition(position.x, position.y - height - 10);
		
		bodySprite.setTexture(*idleTextures[direction * 4 + frame]->texture);

		if (helmet != nullptr) {
			helmetSprite.setTexture(*helmetIdleTextures[direction * 4 + frame]->texture);
		}

		if (armor != nullptr) {
			armorSprite.setTexture(*armorIdleTextures[direction * 4 + frame]->texture);
		}

		if (pants != nullptr) {
			pantsSprite.setTexture(*pantsIdleTextures[direction * 4 + frame]->texture);
		}

		if (rightHand != nullptr) {
			rightHandSprite.setTexture(*rightHandIdleTextures[direction * 4 + frame]->texture);
		}

		if (leftHand != nullptr) {
			leftHandSprite.setTexture(*leftHandIdleTextures[direction * 4 + frame]->texture);
		}

		viewRangeArea.setPosition(position);
		actionRangeArea.setPosition(position);

		setLifeBar();

		showHand = false;
		talkWithSprite.setPosition(position.x, position.y - 90);

		if (dialogue != nullptr) {
			if (player != nullptr) {

				float x1, y1, rx1, ry1;
				float x2, y2, rx2, ry2;

				x1 = player->position.x;
				y1 = player->position.y;
				rx1 = (player->colliders[0]->width / 2.0f + player->actionRange);
				ry1 = (player->colliders[0]->length + player->actionRange) / 2.0f;

				x2 = position.x;
				y2 = position.y;
				rx2 = (colliders[0]->width / 2.0f + ACTION_RANGE);
				ry2 = (colliders[0]->length + ACTION_RANGE) / 2.0f;

				if (intersectionTwoEllipses(x1, y1, rx1, ry1, x2, y2, rx2, ry2)) {
					showHand = true;
				}
			}

		}

		loadTexture();
		sprite.setPosition(position);
	}

	virtual void drawColliders() {
		Unit::drawColliders();
	}

	virtual void draw() {

		renderer->getTheCurrentFrame()->draw(sprite);
		
		if (showHand == true)
			renderer->getTheCurrentFrame()->draw(talkWithSprite);
		
		GameObject::draw();
		//window->draw(lifeBarBackground);
		//window->draw(lifeBar);
	}
};
*/
class Character : public Unit {
public:
	Dialogue* dialogue = nullptr;

	std::string head;

	short LEVEL;
	short EXPERIENCE;
	short SKILL_POINTS;

	// Equipment
	Item* helmet;
	Item* armor;
	Item* pants;
	Item* leftHand;
	Item* rightHand;

	// HEAD - textures
	SingleTexture* headIdleTextures[16];
	SingleTexture* headRunTextures[16];
	SingleTexture* headAttackTextures[16];

	// HELMET - textures
	SingleTexture* helmetIdleTextures[16];
	SingleTexture* helmetRunTextures[16];
	SingleTexture* helmetAttackTextures[16];

	// ARMOR - textures
	SingleTexture* armorIdleTextures[16];
	SingleTexture* armorRunTextures[16];
	SingleTexture* armorAttackTextures[16];

	// PANTS - textures
	SingleTexture* pantsIdleTextures[16];
	SingleTexture* pantsRunTextures[16];
	SingleTexture* pantsAttackTextures[16];

	// LEFT HAND - textures
	SingleTexture* leftHandIdleTextures[16];
	SingleTexture* leftHandRunTextures[16];
	SingleTexture* leftHandAttackTextures[16];

	// RIGHT HAND - textures
	SingleTexture* rightHandIdleTextures[16];
	SingleTexture* rightHandRunTextures[16];
	SingleTexture* rightHandAttackTextures[16];

	sf::Sprite bodySprite;
	sf::Sprite headSprite;
	sf::Sprite helmetSprite;
	sf::Sprite pantsSprite;
	sf::Sprite armorSprite;
	sf::Sprite rightHandSprite;
	sf::Sprite leftHandSprite;

	sf::RenderTexture* renderTexture;

	Character(std::string name, std::string body, std::string head) : Unit(name, body, 36, 18, 64) {
		type = GameObjectType::Character;

		this->head = head;

		helmet = nullptr;
		armor = nullptr;
		pants = nullptr;
		leftHand = nullptr;
		rightHand = nullptr;

		loadBody();
		loadHead();
		loadHelmet();
		loadArmor();
		loadPants();
		loadLeftHand();
		loadRightHand();

		texture = idleTextures[direction * 4 + frame];

		dialogue = getDialogue(0);

		renderTexture = new sf::RenderTexture();
	}

	Character(GameObject* object) : Unit(object) {

		type = GameObjectType::Character;

		this->head = dynamic_cast<Character*>(object)->head;

		helmet = dynamic_cast <Character*>(object)->helmet;
		armor = dynamic_cast <Character*>(object)->armor;
		pants = dynamic_cast <Character*>(object)->pants;
		leftHand = dynamic_cast <Character*>(object)->leftHand;
		rightHand = dynamic_cast <Character*>(object)->rightHand;
		
		loadBody();
		loadHead();
		loadHelmet();
		loadArmor();
		loadPants();
		loadLeftHand();
		loadRightHand();

		texture = idleTextures[direction * 4 + frame];

		dialogue = dynamic_cast <Character*>(object)->dialogue;

		renderTexture = new sf::RenderTexture();

	}

	void loadBody() {
		for (short i = 0; i < 4; i++) {


			idleTextures[i] = getSingleTexture(body + "\\idleTop" + to_string(i));
			idleTextures[4 + i] = getSingleTexture(body + "\\idleRight" + to_string(i));
			idleTextures[8 + i] = getSingleTexture(body + "\\idleBottom" + to_string(i));
			idleTextures[12 + i] = getSingleTexture(body + "\\idleLeft" + to_string(i));

			runTextures[i] = getSingleTexture(body + "\\runTop" + to_string(i));
			runTextures[4 + i] = getSingleTexture(body + "\\runRight" + to_string(i));
			runTextures[8 + i] = getSingleTexture(body + "\\runBottom" + to_string(i));
			runTextures[12 + i] = getSingleTexture(body + "\\runLeft" + to_string(i));

			if (rightHand != nullptr) {
				if (rightHand->type == ItemType::weapon) {
					attackTextures[i] = getSingleTexture(body + "\\attackTop" + to_string(i));
					attackTextures[4 + i] = getSingleTexture(body + "\\attackRight" + to_string(i));
					attackTextures[8 + i] = getSingleTexture(body + "\\attackBottom" + to_string(i));
					attackTextures[12 + i] = getSingleTexture(body + "\\attackLeft" + to_string(i));
				}
				else if (rightHand->type == ItemType::bow) {
					attackTextures[i] = getSingleTexture(body + "\\bowAttackTop" + to_string(i));
					attackTextures[4 + i] = getSingleTexture(body + "\\bowAttackRight" + to_string(i));
					attackTextures[8 + i] = getSingleTexture(body + "\\bowAttackBottom" + to_string(i));
					attackTextures[12 + i] = getSingleTexture(body + "\\bowAttackLeft" + to_string(i));
				}
			}
			else {
				attackTextures[i] = getSingleTexture(body + "\\attackTop" + to_string(i));
				attackTextures[4 + i] = getSingleTexture(body + "\\attackRight" + to_string(i));
				attackTextures[8 + i] = getSingleTexture(body + "\\attackBottom" + to_string(i));
				attackTextures[12 + i] = getSingleTexture(body + "\\attackLeft" + to_string(i));
			}
		
		}
	}

	void loadHead() {
		for (short i = 0; i < 4; i++) {


			headIdleTextures[i] = getSingleTexture(head + "\\idleTop" + to_string(i));
			headIdleTextures[4 + i] = getSingleTexture(head + "\\idleRight" + to_string(i));
			headIdleTextures[8 + i] = getSingleTexture(head + "\\idleBottom" + to_string(i));
			headIdleTextures[12 + i] = getSingleTexture(head + "\\idleLeft" + to_string(i));

			headRunTextures[i] = getSingleTexture(head + "\\runTop" + to_string(i));
			headRunTextures[4 + i] = getSingleTexture(head + "\\runRight" + to_string(i));
			headRunTextures[8 + i] = getSingleTexture(head + "\\runBottom" + to_string(i));
			headRunTextures[12 + i] = getSingleTexture(head + "\\runLeft" + to_string(i));

			if (rightHand != nullptr) {
				if (rightHand->type == ItemType::weapon) {
					headAttackTextures[i] = getSingleTexture(head + "\\attackTop" + to_string(i));
					headAttackTextures[4 + i] = getSingleTexture(head + "\\attackRight" + to_string(i));
					headAttackTextures[8 + i] = getSingleTexture(head + "\\attackBottom" + to_string(i));
					headAttackTextures[12 + i] = getSingleTexture(head + "\\attackLeft" + to_string(i));
				}
				else if (rightHand->type == ItemType::bow) {
					headAttackTextures[i] = getSingleTexture(head + "\\bowAttackTop" + to_string(i));
					headAttackTextures[4 + i] = getSingleTexture(head + "\\bowAttackRight" + to_string(i));
					headAttackTextures[8 + i] = getSingleTexture(head + "\\bowAttackBottom" + to_string(i));
					headAttackTextures[12 + i] = getSingleTexture(head + "\\bowAttackLeft" + to_string(i));
				}
			}
			else {
				headAttackTextures[i] = getSingleTexture(head + "\\attackTop" + to_string(i));
				headAttackTextures[4 + i] = getSingleTexture(head + "\\attackRight" + to_string(i));
				headAttackTextures[8 + i] = getSingleTexture(head + "\\attackBottom" + to_string(i));
				headAttackTextures[12 + i] = getSingleTexture(head + "\\attackLeft" + to_string(i));
			}

		}
	}

	void loadHelmet() {

		for (short i = 0; i < 16; i++) {
			helmetIdleTextures[i] = nullptr;
			helmetRunTextures[i] = nullptr;
			helmetAttackTextures[i] = nullptr;

		}

		if (helmet != nullptr) {

			for (short i = 0; i < 4; i++) {
				helmetIdleTextures[i] = getSingleTexture("sets\\" + helmet->name + "\\idleTop" + to_string(i));
				helmetIdleTextures[4 + i] = getSingleTexture("sets\\" + helmet->name + "\\idleRight" + to_string(i));
				helmetIdleTextures[8 + i] = getSingleTexture("sets\\" + helmet->name + "\\idleBottom" + to_string(i));
				helmetIdleTextures[12 + i] = getSingleTexture("sets\\" + helmet->name + "\\idleLeft" + to_string(i));

				helmetRunTextures[i] = getSingleTexture("sets\\" + helmet->name + "\\runTop" + to_string(i));
				helmetRunTextures[4 + i] = getSingleTexture("sets\\" + helmet->name + "\\runRight" + to_string(i));
				helmetRunTextures[8 + i] = getSingleTexture("sets\\" + helmet->name + "\\runBottom" + to_string(i));
				helmetRunTextures[12 + i] = getSingleTexture("sets\\" + helmet->name + "\\runLeft" + to_string(i));

				helmetAttackTextures[i] = getSingleTexture("sets\\" + helmet->name + "\\attackTop" + to_string(i));
				helmetAttackTextures[4 + i] = getSingleTexture("sets\\" + helmet->name + "\\attackRight" + to_string(i));
				helmetAttackTextures[8 + i] = getSingleTexture("sets\\" + helmet->name + "\\attackBottom" + to_string(i));
				helmetAttackTextures[12 + i] = getSingleTexture("sets\\" + helmet->name + "\\attackLeft" + to_string(i));

			}
		}
	}

	void loadArmor() {

		for (short i = 0; i < 16; i++) {
			armorIdleTextures[i] = nullptr;
			armorRunTextures[i] = nullptr;
			armorAttackTextures[i] = nullptr;
		}

		if (armor != nullptr) {

			for (short i = 0; i < 4; i++) {
				armorIdleTextures[i] = getSingleTexture("sets\\" + armor->name + "\\idleTop" + to_string(i));
				armorIdleTextures[4 + i] = getSingleTexture("sets\\" + armor->name + "\\idleRight" + to_string(i));
				armorIdleTextures[8 + i] = getSingleTexture("sets\\" + armor->name + "\\idleBottom" + to_string(i));
				armorIdleTextures[12 + i] = getSingleTexture("sets\\" + armor->name + "\\idleLeft" + to_string(i));

				armorRunTextures[i] = getSingleTexture("sets\\" + armor->name + "\\runTop" + to_string(i));
				armorRunTextures[4 + i] = getSingleTexture("sets\\" + armor->name + "\\runRight" + to_string(i));
				armorRunTextures[8 + i] = getSingleTexture("sets\\" + armor->name + "\\runBottom" + to_string(i));
				armorRunTextures[12 + i] = getSingleTexture("sets\\" + armor->name + "\\runLeft" + to_string(i));

				if (rightHand != nullptr) {
					if (rightHand->type == ItemType::weapon) {
						armorAttackTextures[i] = getSingleTexture("sets\\" + armor->name + "\\attackTop" + to_string(i));
						armorAttackTextures[4 + i] = getSingleTexture("sets\\" + armor->name + "\\attackRight" + to_string(i));
						armorAttackTextures[8 + i] = getSingleTexture("sets\\" + armor->name + "\\attackBottom" + to_string(i));
						armorAttackTextures[12 + i] = getSingleTexture("sets\\" + armor->name + "\\attackLeft" + to_string(i));
					}
					else if (rightHand->type == ItemType::bow) {

						armorAttackTextures[i] = getSingleTexture("sets\\" + armor->name + "\\attackTop" + to_string(i));
						armorAttackTextures[4 + i] = getSingleTexture("sets\\" + armor->name + "\\attackRight" + to_string(i));
						armorAttackTextures[8 + i] = getSingleTexture("sets\\" + armor->name + "\\attackBottom" + to_string(i));
						armorAttackTextures[12 + i] = getSingleTexture("sets\\" + armor->name + "\\attackLeft" + to_string(i));

						if (armor->name == "items\\chain mail") {
							armorAttackTextures[i] = getSingleTexture("sets\\" + armor->name + "\\bowAttackTop" + to_string(i));
							armorAttackTextures[4 + i] = getSingleTexture("sets\\" + armor->name + "\\bowAttackRight" + to_string(i));
							armorAttackTextures[8 + i] = getSingleTexture("sets\\" + armor->name + "\\bowAttackBottom" + to_string(i));
							armorAttackTextures[12 + i] = getSingleTexture("sets\\" + armor->name + "\\bowAttackLeft" + to_string(i));
						}
						
					}
				}
				else {
					armorAttackTextures[i] = getSingleTexture("sets\\" + armor->name + "\\attackTop" + to_string(i));
					armorAttackTextures[4 + i] = getSingleTexture("sets\\" + armor->name + "\\attackRight" + to_string(i));
					armorAttackTextures[8 + i] = getSingleTexture("sets\\" + armor->name + "\\attackBottom" + to_string(i));
					armorAttackTextures[12 + i] = getSingleTexture("sets\\" + armor->name + "\\attackLeft" + to_string(i));
				}

			}
		}
	}

	void loadPants() {

		for (short i = 0; i < 16; i++) {
			pantsIdleTextures[i] = nullptr;
			pantsRunTextures[i] = nullptr;
			pantsAttackTextures[i] = nullptr;

		}

		if (pants != nullptr) {

			for (short i = 0; i < 4; i++) {
				pantsIdleTextures[i] = getSingleTexture("sets\\" + pants->name + "\\idleTop" + to_string(i));
				pantsIdleTextures[4 + i] = getSingleTexture("sets\\" + pants->name + "\\idleRight" + to_string(i));
				pantsIdleTextures[8 + i] = getSingleTexture("sets\\" + pants->name + "\\idleBottom" + to_string(i));
				pantsIdleTextures[12 + i] = getSingleTexture("sets\\" + pants->name + "\\idleLeft" + to_string(i));

				pantsRunTextures[i] = getSingleTexture("sets\\" + pants->name + "\\runTop" + to_string(i));
				pantsRunTextures[4 + i] = getSingleTexture("sets\\" + pants->name + "\\runRight" + to_string(i));
				pantsRunTextures[8 + i] = getSingleTexture("sets\\" + pants->name + "\\runBottom" + to_string(i));
				pantsRunTextures[12 + i] = getSingleTexture("sets\\" + pants->name + "\\runLeft" + to_string(i));

				pantsAttackTextures[i] = getSingleTexture("sets\\" + pants->name + "\\attackTop" + to_string(i));
				pantsAttackTextures[4 + i] = getSingleTexture("sets\\" + pants->name + "\\attackRight" + to_string(i));
				pantsAttackTextures[8 + i] = getSingleTexture("sets\\" + pants->name + "\\attackBottom" + to_string(i));
				pantsAttackTextures[12 + i] = getSingleTexture("sets\\" + pants->name + "\\attackLeft" + to_string(i));

			}
		}
	}

	void loadLeftHand() {

		for (short i = 0; i < 16; i++) {
			leftHandIdleTextures[i] = nullptr;
			leftHandRunTextures[i] = nullptr;
			leftHandAttackTextures[i] = nullptr;

		}

		if (leftHand != nullptr) {

			for (short i = 0; i < 4; i++) {
				leftHandIdleTextures[i] = getSingleTexture("sets\\" + leftHand->name + "\\idleTop" + to_string(i));
				leftHandIdleTextures[4 + i] = getSingleTexture("sets\\" + leftHand->name + "\\idleRight" + to_string(i));
				leftHandIdleTextures[8 + i] = getSingleTexture("sets\\" + leftHand->name + "\\idleBottom" + to_string(i));
				leftHandIdleTextures[12 + i] = getSingleTexture("sets\\" + leftHand->name + "\\idleLeft" + to_string(i));

				leftHandRunTextures[i] = getSingleTexture("sets\\" + leftHand->name + "\\runTop" + to_string(i));
				leftHandRunTextures[4 + i] = getSingleTexture("sets\\" + leftHand->name + "\\runRight" + to_string(i));
				leftHandRunTextures[8 + i] = getSingleTexture("sets\\" + leftHand->name + "\\runBottom" + to_string(i));
				leftHandRunTextures[12 + i] = getSingleTexture("sets\\" + leftHand->name + "\\runLeft" + to_string(i));

				leftHandAttackTextures[i] = getSingleTexture("sets\\" + leftHand->name + "\\attackTop" + to_string(i));
				leftHandAttackTextures[4 + i] = getSingleTexture("sets\\" + leftHand->name + "\\attackRight" + to_string(i));
				leftHandAttackTextures[8 + i] = getSingleTexture("sets\\" + leftHand->name + "\\attackBottom" + to_string(i));
				leftHandAttackTextures[12 + i] = getSingleTexture("sets\\" + leftHand->name + "\\attackLeft" + to_string(i));

			}
		}
	}

	void loadRightHand() {

		for (short i = 0; i < 16; i++) {
			rightHandIdleTextures[i] = nullptr;
			rightHandRunTextures[i] = nullptr;
			rightHandAttackTextures[i] = nullptr;

		}

		if (rightHand != nullptr) {

			for (short i = 0; i < 4; i++) {

				rightHandIdleTextures[i] = getSingleTexture("sets\\" + rightHand->name + "\\idleTop" + to_string(i));
				rightHandIdleTextures[4 + i] = getSingleTexture("sets\\" + rightHand->name + "\\idleRight" + to_string(i));
				rightHandIdleTextures[8 + i] = getSingleTexture("sets\\" + rightHand->name + "\\idleBottom" + to_string(i));
				rightHandIdleTextures[12 + i] = getSingleTexture("sets\\" + rightHand->name + "\\idleLeft" + to_string(i));

				rightHandRunTextures[i] = getSingleTexture("sets\\" + rightHand->name + "\\runTop" + to_string(i));
				rightHandRunTextures[4 + i] = getSingleTexture("sets\\" + rightHand->name + "\\runRight" + to_string(i));
				rightHandRunTextures[8 + i] = getSingleTexture("sets\\" + rightHand->name + "\\runBottom" + to_string(i));
				rightHandRunTextures[12 + i] = getSingleTexture("sets\\" + rightHand->name + "\\runLeft" + to_string(i));

				rightHandAttackTextures[i] = getSingleTexture("sets\\" + rightHand->name + "\\attackTop" + to_string(i));
				rightHandAttackTextures[4 + i] = getSingleTexture("sets\\" + rightHand->name + "\\attackRight" + to_string(i));
				rightHandAttackTextures[8 + i] = getSingleTexture("sets\\" + rightHand->name + "\\attackBottom" + to_string(i));
				rightHandAttackTextures[12 + i] = getSingleTexture("sets\\" + rightHand->name + "\\attackLeft" + to_string(i));

			}
		}
	}

	void useItem(Item* item) {

		if (item->type == ItemType::helmet) {
			(item != helmet) ? helmet = item : helmet = nullptr;
			loadHelmet();
		}

		if (item->type == ItemType::armor) {
			(item != armor) ? armor = item : armor = nullptr;
			loadArmor();
		}

		if (item->type == ItemType::pants) {
			(item != pants) ? pants = item : pants = nullptr;
			loadPants();
			
		}

		if (item->type == ItemType::weapon) {
			(item != rightHand) ? rightHand = item : rightHand = nullptr;
			loadRightHand();
			loadLeftHand();
			loadArmor();
			loadBody();
			loadHead();
		}

		if (item->type == ItemType::shield) {

			if (rightHand != nullptr && rightHand->type == ItemType::bow) {
				rightHand = nullptr;
				leftHand = item;
			}
			else if (item != leftHand) {
				leftHand = item;
			}
			else {
				leftHand = nullptr;
			}

			loadRightHand();
			loadLeftHand();
			loadArmor();
			loadBody();
			loadHead();
		}

		if (item->type == ItemType::bow) {
			if (leftHand != nullptr) {
				leftHand = nullptr;
			}

			(rightHand != item) ? rightHand = item : rightHand = nullptr;

			loadRightHand();
			loadLeftHand();
			loadArmor();
			loadBody();
			loadHead();
		}

	}

	void update() {
		state = State::Attack;
		attacking();

		bodySprite = sf::Sprite();
		headSprite = sf::Sprite();
		helmetSprite = sf::Sprite();
		armorSprite = sf::Sprite();
		pantsSprite = sf::Sprite();
		leftHandSprite = sf::Sprite();
		rightHandSprite = sf::Sprite();

		if (state == State::Idle) {
			bodySprite.setTexture(*idleTextures[direction * 4 + frame]->texture);
			headSprite.setTexture(*headIdleTextures[direction * 4 + frame]->texture);

			if (helmet != nullptr) helmetSprite.setTexture(*helmetIdleTextures[direction * 4 + frame]->texture);
			if (armor != nullptr) armorSprite.setTexture(*armorIdleTextures[direction * 4 + frame]->texture);
			if (pants != nullptr) pantsSprite.setTexture(*pantsIdleTextures[direction * 4 + frame]->texture);
			if (leftHand != nullptr) leftHandSprite.setTexture(*leftHandIdleTextures[direction * 4 + frame]->texture);
			if (rightHand != nullptr) rightHandSprite.setTexture(*rightHandIdleTextures[direction * 4 + frame]->texture);

		}

		if (state == State::Run) {
			bodySprite.setTexture(*runTextures[direction * 4 + frame]->texture);
			headSprite.setTexture(*headRunTextures[direction * 4 + frame]->texture);

			if (helmet != nullptr) helmetSprite.setTexture(*helmetRunTextures[direction * 4 + frame]->texture);
			if (armor != nullptr) armorSprite.setTexture(*armorRunTextures[direction * 4 + frame]->texture);
			if (pants != nullptr) pantsSprite.setTexture(*pantsRunTextures[direction * 4 + frame]->texture);
			if (leftHand != nullptr) leftHandSprite.setTexture(*leftHandRunTextures[direction * 4 + frame]->texture);
			if (rightHand != nullptr) rightHandSprite.setTexture(*rightHandRunTextures[direction * 4 + frame]->texture);

		}

		if (state == State::Attack) {
			bodySprite.setTexture(*attackTextures[direction * 4 + frame]->texture);
			headSprite.setTexture(*headAttackTextures[direction * 4 + frame]->texture);

			if (helmet != nullptr) helmetSprite.setTexture(*helmetAttackTextures[direction * 4 + frame]->texture);
			if (armor != nullptr) armorSprite.setTexture(*armorAttackTextures[direction * 4 + frame]->texture);
			if (pants != nullptr) pantsSprite.setTexture(*pantsAttackTextures[direction * 4 + frame]->texture);
			if (leftHand != nullptr) leftHandSprite.setTexture(*leftHandAttackTextures[direction * 4 + frame]->texture);
			if (rightHand != nullptr) rightHandSprite.setTexture(*rightHandAttackTextures[direction * 4 + frame]->texture);
		}

		renderTexture->create(64, 64);
		renderTexture->clear(sf::Color::Transparent);

		switch (direction) {
		case 0: // TOP
			renderTexture->draw(rightHandSprite);
			renderTexture->draw(leftHandSprite);
			renderTexture->draw(bodySprite);
			renderTexture->draw(pantsSprite);
			renderTexture->draw(armorSprite);
			renderTexture->draw(headSprite);
			renderTexture->draw(helmetSprite);
			
			break;
		case 1: // RIGHT
			renderTexture->draw(leftHandSprite);
			renderTexture->draw(bodySprite);
			renderTexture->draw(pantsSprite);
			renderTexture->draw(armorSprite);
			renderTexture->draw(rightHandSprite);
			renderTexture->draw(headSprite);
			renderTexture->draw(helmetSprite);
			break;
		case 2: // BOTTOM
			renderTexture->draw(bodySprite);
			renderTexture->draw(pantsSprite);
			renderTexture->draw(armorSprite);
			renderTexture->draw(leftHandSprite);
			renderTexture->draw(rightHandSprite);
			renderTexture->draw(headSprite);
			renderTexture->draw(helmetSprite);
			break;
		case 3: // LEFT
			renderTexture->draw(rightHandSprite);
			renderTexture->draw(bodySprite);
			renderTexture->draw(pantsSprite);
			renderTexture->draw(armorSprite);
			renderTexture->draw(leftHandSprite);
			renderTexture->draw(headSprite);
			renderTexture->draw(helmetSprite);
			break;
		default:
			break;
		}

		renderTexture->display();

		sprite.setTexture(renderTexture->getTexture());
		sprite.setOrigin(32, 58);
		setPosition(position);

	}

	void draw() {
		renderer->getTheCurrentFrame()->draw(sprite);
	}
};

std::vector < Character* > characters;


#endif