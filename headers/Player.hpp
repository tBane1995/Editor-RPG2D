#ifndef Player_hpp
#define Player_hpp

class Player : public GameObject {
public:
	Item* helmet;
	Item* armor;
	Item* pants;
	Item* rightHand;
	Item* leftHand;

	// TO-DO sf::Texture to Texture*
	// BODY
	std::wstring body;
	SingleTexture* bodyIdleTextures[16];	// idle for top, right, bottom, left
	SingleTexture* bodyRunTextures[16];	// run for top, right, bottom, left
	SingleTexture* bodyAttackTextures[16];	// fight for top, right, bottom, left

	// HELMET
	SingleTexture* helmetIdleTextures[16];
	SingleTexture* helmetRunTextures[16];
	SingleTexture* helmetAttackTextures[16];

	// ARMOR
	SingleTexture* armorIdleTextures[16];
	SingleTexture* armorRunTextures[16];
	SingleTexture* armorAttackTextures[16];

	// PANTS
	SingleTexture* pantsIdleTextures[16];
	SingleTexture* pantsRunTextures[16];
	SingleTexture* pantsAttackTextures[16];

	// WEAPON
	SingleTexture* rightHandIdleTextures[16];
	SingleTexture* rightHandRunTextures[16];
	SingleTexture* rightHandAttackTextures[16];

	// SHIELD
	SingleTexture* leftHandIdleTextures[16];
	SingleTexture* leftHandRunTextures[16];
	SingleTexture* leftHandAttackTextures[16];

	// SPRITES
	sf::Sprite bodySprite;
	sf::Sprite helmetSprite;
	sf::Sprite armorSprite;
	sf::Sprite pantsSprite;
	sf::Sprite rightHandSprite;
	sf::Sprite leftHandSprite;

	short direction;
	short frame;	// current frame number
	float stepSize;
	unitStates state;
	float actionRange;
	float viewRange;
	sf::CircleShape actionRangeArea;
	
	float countdown;	 // timer to determine current frame
	float attackTime;
	float cooldown;

	Inventory* bag;

	short HP, HP_FULL;
	short MP, MP_FULL;
	short STRENGTH;
	short DEXTERITY;
	short INTELLIGENCE;
	short LEVEL;
	short EXPERIENCE;
	short EXPERIENCE_TO_NEXT_LEVEL;
	short SKILL_POINTS;

	Player() : GameObject(L"hero", 24, 12, 64, true, ColliderType::Elipse) {
		type = GameObjectType::Player;
		direction = 2;
		frame = 0;
		stepSize = 6.0f;
		countdown = 0.0f;
		state = unitStates::idle;
		actionRange = 25.0f;
		cooldown = 0.0f;
		attackTime = 0.7f;

		position.x = 950;
		position.y = 1200 - 512;

		isVisible = true;
		isInTheMainList = true;

		HP = 10;
		HP_FULL = 40;
		MP = 5;
		MP_FULL = 5;
		STRENGTH = 5;
		DEXTERITY = 5;
		INTELLIGENCE = 5;
		
		LEVEL = 0;
		EXPERIENCE = 0;
		EXPERIENCE_TO_NEXT_LEVEL = 50;
		SKILL_POINTS = 0;

		body = L"sets\\body\\boy-brownhaired";
		
		bag = new Inventory(-1);
		/*
		bag->addItem("items\\torn shirt");
		bag->addItem("items\\axe");
		bag->addItem("items\\bone");
		bag->addItem("items\\health herb");
		bag->addItem("items\\skin helmet");
		bag->addItem("items\\skin pants");
		bag->addItem("items\\wooden club");
		bag->addItem("items\\skin jacket");
		bag->addItem("items\\club");
		bag->addItem("items\\iron club");
		bag->addItem("items\\stone hammer");
		bag->addItem("items\\sword");
		bag->addItem("items\\long sword");
		bag->addItem("items\\gladius");
		bag->addItem("items\\wide blade");
		bag->addItem("items\\knife");
		bag->addItem("items\\dagger");
		bag->addItem("items\\hatchet");
		bag->addItem("items\\curved sword");
		bag->addItem("items\\chain mail");
		bag->addItem("items\\chain mail pants");
		bag->addItem("items\\wool hat");
		bag->addItem("items\\wool pants");
		bag->addItem("items\\wool shirt");
		bag->addItem("items\\raw meat");
		bag->addItem("items\\plate armor");
		*/
		// ITEMS TO-DO - CREATE ITEM SETS
		//bag->addItem("items\\skin pants");

		helmet = nullptr;
		armor = nullptr;
		pants = nullptr;
		rightHand = nullptr;
		leftHand = nullptr;

		//helmet = getItem("items\\skin helmet");
		//armor = getItem("items\\skin jacket");
		//pants = getItem("items\\skin pants");
		//rightHand = getItem("items\\hatchet");
		//leftHand = nullptr;

		loadBody();
		loadHelmet();
		loadArmor();
		loadPants();
		loadRightHand();
		loadLeftHand();
		

		setActionRangeArea();
	}

	virtual ~Player() {
	
	}
	
	void setDirection(int direction) {
		this->direction = direction;
		frame = 0.0f;
	}

	void move() {
		state = unitStates::run;
	}

	void attack() {
		state = unitStates::attack;
		frame = 0.0f;
		cooldown = attackTime;
	}

	void setPosition(float x, float y) {
		this->position.x = x;
		this->position.y = y;
	}

	void loadBody() {
		for (short i = 0; i < 16; i++) {
			bodyIdleTextures[i] = nullptr;
			bodyRunTextures[i] = nullptr;
			bodyAttackTextures[i] = nullptr;

		}

		for (short i = 0; i < 4; i++) {

			bodyIdleTextures[i] = getSingleTexture(body + L"\\idleTop" + to_wstring(i));
			bodyIdleTextures[4 + i] = getSingleTexture(body + L"\\idleRight" + to_wstring(i));
			bodyIdleTextures[8 + i] = getSingleTexture(body + L"\\idleBottom" + to_wstring(i));
			bodyIdleTextures[12 + i] = getSingleTexture(body + L"\\idleLeft" + to_wstring(i));

			bodyRunTextures[i] = getSingleTexture(body + L"\\runTop" + to_wstring(i));
			bodyRunTextures[4 + i] = getSingleTexture(body + L"\\runRight" + to_wstring(i));
			bodyRunTextures[8 + i] = getSingleTexture(body + L"\\runBottom" + to_wstring(i));
			bodyRunTextures[12 + i] = getSingleTexture(body + L"\\runLeft" + to_wstring(i));

			bodyAttackTextures[i] = getSingleTexture(body + L"\\attackTop" + to_wstring(i));
			bodyAttackTextures[4 + i] = getSingleTexture(body + L"\\attackRight" + to_wstring(i));
			bodyAttackTextures[8 + i] = getSingleTexture(body + L"\\attackBottom" + to_wstring(i));
			bodyAttackTextures[12 + i] = getSingleTexture(body + L"\\attackLeft" + to_wstring(i));

		}

		bodySprite = sf::Sprite();
		bodySprite.setOrigin(32, 58);

	}

	void loadHelmet() {

		for (short i = 0; i < 16; i++) {
			helmetIdleTextures[i] = nullptr;
			helmetRunTextures[i] = nullptr;
			helmetAttackTextures[i] = nullptr;

		}

		if (helmet != nullptr) {

			for (short i = 0; i < 4; i++) {
				helmetIdleTextures[i] = getSingleTexture(L"sets\\" + helmet->name + L"\\idleTop" + to_wstring(i));
				helmetIdleTextures[4 + i] = getSingleTexture(L"sets\\" + helmet->name + L"\\idleRight" + to_wstring(i));
				helmetIdleTextures[8 + i] = getSingleTexture(L"sets\\" + helmet->name + L"\\idleBottom" + to_wstring(i));
				helmetIdleTextures[12 + i] = getSingleTexture(L"sets\\" + helmet->name + L"\\idleLeft" + to_wstring(i));

				helmetRunTextures[i] = getSingleTexture(L"sets\\" + helmet->name + L"\\runTop" + to_wstring(i));
				helmetRunTextures[4 + i] = getSingleTexture(L"sets\\" + helmet->name + L"\\runRight" + to_wstring(i));
				helmetRunTextures[8 + i] = getSingleTexture(L"sets\\" + helmet->name + L"\\runBottom" + to_wstring(i));
				helmetRunTextures[12 + i] = getSingleTexture(L"sets\\" + helmet->name + L"\\runLeft" + to_wstring(i));

				helmetAttackTextures[i] = getSingleTexture(L"sets\\" + helmet->name + L"\\attackTop" + to_wstring(i));
				helmetAttackTextures[4 + i] = getSingleTexture(L"sets\\" + helmet->name + L"\\attackRight" + to_wstring(i));
				helmetAttackTextures[8 + i] = getSingleTexture(L"sets\\" + helmet->name + L"\\attackBottom" + to_wstring(i));
				helmetAttackTextures[12 + i] = getSingleTexture(L"sets\\" + helmet->name + L"\\attackLeft" + to_wstring(i));

			}
		}

		helmetSprite = sf::Sprite();
		helmetSprite.setOrigin(32, 58);

	}

	void loadArmor() {

		for (short i = 0; i < 16; i++) {
			armorIdleTextures[i] = nullptr;
			armorRunTextures[i] = nullptr;
			armorAttackTextures[i] = nullptr;

		}

		if (armor != nullptr) {
		
			for (short i = 0; i < 4; i++) {
				armorIdleTextures[i] = getSingleTexture(L"sets\\" + armor->name + L"\\idleTop" + to_wstring(i));
				armorIdleTextures[4 + i] = getSingleTexture(L"sets\\" + armor->name + L"\\idleRight" + to_wstring(i));
				armorIdleTextures[8 + i] = getSingleTexture(L"sets\\" + armor->name + L"\\idleBottom" + to_wstring(i));
				armorIdleTextures[12 + i] = getSingleTexture(L"sets\\" + armor->name + L"\\idleLeft" + to_wstring(i));

				armorRunTextures[i] = getSingleTexture(L"sets\\" + armor->name + L"\\runTop" + to_wstring(i));
				armorRunTextures[4 + i] = getSingleTexture(L"sets\\" + armor->name + L"\\runRight" + to_wstring(i));
				armorRunTextures[8 + i] = getSingleTexture(L"sets\\" + armor->name + L"\\runBottom" + to_wstring(i));
				armorRunTextures[12 + i] = getSingleTexture(L"sets\\" + armor->name + L"\\runLeft" + to_wstring(i));

				armorAttackTextures[i] = getSingleTexture(L"sets\\" + armor->name + L"\\attackTop" + to_wstring(i));
				armorAttackTextures[4 + i] = getSingleTexture(L"sets\\" + armor->name + L"\\attackRight" + to_wstring(i));
				armorAttackTextures[8 + i] = getSingleTexture(L"sets\\" + armor->name + L"\\attackBottom" + to_wstring(i));
				armorAttackTextures[12 + i] = getSingleTexture(L"sets\\" + armor->name + L"\\attackLeft" + to_wstring(i));

			}
		}

		armorSprite = sf::Sprite();
		armorSprite.setOrigin(32, 58);
	}

	void loadPants() {

		for (short i = 0; i < 16; i++) {
			pantsIdleTextures[i] = nullptr;
			pantsRunTextures[i] = nullptr;
			pantsAttackTextures[i] = nullptr;

		}

		if (pants != nullptr) {

			for (short i = 0; i < 4; i++) {
				pantsIdleTextures[i] = getSingleTexture(L"sets\\" + pants->name + L"\\idleTop" + to_wstring(i));
				pantsIdleTextures[4 + i] = getSingleTexture(L"sets\\" + pants->name + L"\\idleRight" + to_wstring(i));
				pantsIdleTextures[8 + i] = getSingleTexture(L"sets\\" + pants->name + L"\\idleBottom" + to_wstring(i));
				pantsIdleTextures[12 + i] = getSingleTexture(L"sets\\" + pants->name + L"\\idleLeft" + to_wstring(i));

				pantsRunTextures[i] = getSingleTexture(L"sets\\" + pants->name + L"\\runTop" + to_wstring(i));
				pantsRunTextures[4 + i] = getSingleTexture(L"sets\\" + pants->name + L"\\runRight" + to_wstring(i));
				pantsRunTextures[8 + i] = getSingleTexture(L"sets\\" + pants->name + L"\\runBottom" + to_wstring(i));
				pantsRunTextures[12 + i] = getSingleTexture(L"sets\\" + pants->name + L"\\runLeft" + to_wstring(i));

				pantsAttackTextures[i] = getSingleTexture(L"sets\\" + pants->name + L"\\attackTop" + to_wstring(i));
				pantsAttackTextures[4 + i] = getSingleTexture(L"sets\\" + pants->name + L"\\attackRight" + to_wstring(i));
				pantsAttackTextures[8 + i] = getSingleTexture(L"sets\\" + pants->name + L"\\attackBottom" + to_wstring(i));
				pantsAttackTextures[12 + i] = getSingleTexture(L"sets\\" + pants->name + L"\\attackLeft" + to_wstring(i));

			}
		}

		pantsSprite = sf::Sprite();
		pantsSprite.setOrigin(32, 58);

	}

	void loadRightHand() {

		for (short i = 0; i < 16; i++) {
			rightHandIdleTextures[i] = nullptr;
			rightHandRunTextures[i] = nullptr;
			rightHandAttackTextures[i] = nullptr;

		}

		if (rightHand != nullptr) {

			for (short i = 0; i < 4; i++) {
				rightHandIdleTextures[i] = getSingleTexture(L"sets\\" + rightHand->name + L"\\idleTop" + to_wstring(i));
				rightHandIdleTextures[4 + i] = getSingleTexture(L"sets\\" + rightHand->name + L"\\idleRight" + to_wstring(i));
				rightHandIdleTextures[8 + i] = getSingleTexture(L"sets\\" + rightHand->name + L"\\idleBottom" + to_wstring(i));
				rightHandIdleTextures[12 + i] = getSingleTexture(L"sets\\" + rightHand->name + L"\\idleLeft" + to_wstring(i));

				rightHandRunTextures[i] = getSingleTexture(L"sets\\" + rightHand->name + L"\\runTop" + to_wstring(i));
				rightHandRunTextures[4 + i] = getSingleTexture(L"sets\\" + rightHand->name + L"\\runRight" + to_wstring(i));
				rightHandRunTextures[8 + i] = getSingleTexture(L"sets\\" + rightHand->name + L"\\runBottom" + to_wstring(i));
				rightHandRunTextures[12 + i] = getSingleTexture(L"sets\\" + rightHand->name + L"\\runLeft" + to_wstring(i));

				rightHandAttackTextures[i] = getSingleTexture(L"sets\\" + rightHand->name + L"\\attackTop" + to_wstring(i));
				rightHandAttackTextures[4 + i] = getSingleTexture(L"sets\\" + rightHand->name + L"\\attackRight" + to_wstring(i));
				rightHandAttackTextures[8 + i] = getSingleTexture(L"sets\\" + rightHand->name + L"\\attackBottom" + to_wstring(i));
				rightHandAttackTextures[12 + i] = getSingleTexture(L"sets\\" + rightHand->name + L"\\attackLeft" + to_wstring(i));

			}
		}

		rightHandSprite = sf::Sprite();
		rightHandSprite.setOrigin(32, 58);

	}

	void loadLeftHand() {

		for (short i = 0; i < 16; i++) {
			leftHandIdleTextures[i] = nullptr;
			leftHandRunTextures[i] = nullptr;
			leftHandAttackTextures[i] = nullptr;

		}

		if (leftHand != nullptr) {

			for (short i = 0; i < 4; i++) {
				leftHandIdleTextures[i] = getSingleTexture(L"sets\\" + leftHand->name + L"\\idleTop" + to_wstring(i));
				leftHandIdleTextures[4 + i] = getSingleTexture(L"sets\\" + leftHand->name + L"\\idleRight" + to_wstring(i));
				leftHandIdleTextures[8 + i] = getSingleTexture(L"sets\\" + leftHand->name + L"\\idleBottom" + to_wstring(i));
				leftHandIdleTextures[12 + i] = getSingleTexture(L"sets\\" + leftHand->name + L"\\idleLeft" + to_wstring(i));

				leftHandRunTextures[i] = getSingleTexture(L"sets\\" + leftHand->name + L"\\runTop" + to_wstring(i));
				leftHandRunTextures[4 + i] = getSingleTexture(L"sets\\" + leftHand->name + L"\\runRight" + to_wstring(i));
				leftHandRunTextures[8 + i] = getSingleTexture(L"sets\\" + leftHand->name + L"\\runBottom" + to_wstring(i));
				leftHandRunTextures[12 + i] = getSingleTexture(L"sets\\" + leftHand->name + L"\\runLeft" + to_wstring(i));

				leftHandAttackTextures[i] = getSingleTexture(L"sets\\" + leftHand->name + L"\\attackTop" + to_wstring(i));
				leftHandAttackTextures[4 + i] = getSingleTexture(L"sets\\" + leftHand->name + L"\\attackRight" + to_wstring(i));
				leftHandAttackTextures[8 + i] = getSingleTexture(L"sets\\" + leftHand->name + L"\\attackBottom" + to_wstring(i));
				leftHandAttackTextures[12 + i] = getSingleTexture(L"sets\\" + leftHand->name + L"\\attackLeft" + to_wstring(i));

			}
		}

		leftHandSprite = sf::Sprite();
		leftHandSprite.setOrigin(32, 58);

	}

	void setActionRangeArea() {
		actionRangeArea = sf::CircleShape(actionRange + colliders[0]->width / 2.0f);
		actionRangeArea.setFillColor(sf::Color(128, 64, 64, 128));
		actionRangeArea.setOutlineColor(sf::Color(196, 64, 64, 128));
		actionRangeArea.setOutlineThickness(4.0f);
		actionRangeArea.setOrigin(actionRange + colliders[0]->width / 2.0f, actionRange + colliders[0]->width / 2.0f);
		actionRangeArea.setScale(1.0f, colliders[0]->length / colliders[0]->width);
	}


	void calculateCurrentFrame(float dt) {
		countdown -= dt;
		while (countdown <= 0.0f) {
			countdown += 1.0f / 8.0f;	// 8 FPS
			frame += 1;
		}

		if (frame > 3)
			frame = frame % 4;
	}

	int takeDamage(short damage) {

		short defend = 0;

		if (armor != nullptr)
			defend += armor->attributes[Attribute::DEFEND];

		if (helmet != nullptr)
			defend += helmet->attributes[Attribute::DEFEND];
		 
		if (pants != nullptr)
			defend += pants->attributes[Attribute::DEFEND];

		if (leftHand != nullptr)
			defend += leftHand->attributes[Attribute::DEFEND];

		short dam = damage - defend;

		if (dam > 0) {
			HP = HP - dam;

			if (HP < 0)
				HP = 0;
		}

		return dam;
	}
	
	int getDamage() {
		int damage = STRENGTH * 2;

		if (rightHand != nullptr)
			damage += rightHand->attributes[Attribute::ATTACK];

		damage = damage * (rand() % 50 + 75) / 100;		// 75% - 125% 

		return int(damage);
	}

	void heal(short HP) {
		this->HP += HP;

		if (this->HP > HP_FULL)
			this->HP = HP_FULL;
	}

	void collectItem(Item* item, short count = 1) {

		bag->addItem(item,count);
	}

	void gainEXP(short EXP) {
		EXPERIENCE += EXP;
		while (levelUp());
	}

	bool levelUp() {
		
		short LEVEL_SCALAR = 2;

		if (EXPERIENCE >= EXPERIENCE_TO_NEXT_LEVEL) {
			LEVEL++;
			HP += 40;
			HP_FULL += 40;
			EXPERIENCE_TO_NEXT_LEVEL *= LEVEL_SCALAR;
			SKILL_POINTS += 5;
		
			hits->addHitText(sf::Vector2f(position.x, position.y-height), "lvl up!");
			return true;
		}

		return false;
	}

	virtual void update() {
		float dt = currentTime.asSeconds() - prevTime.asSeconds();
		float distance = 20.0f * stepSize * dt;

		if (state == unitStates::attack) {
		
			if (cooldown <= 0.0f)
			{
				state = unitStates::idle;
				frame = 0;
			}
			frame = cooldown / attackTime * 4.0f - 1.0f;
			if (frame < 0)
				frame = 0;

			bodySprite.setTexture(*bodyAttackTextures[direction * 4 + frame]->texture);
			
			if(helmet!=nullptr)
				helmetSprite.setTexture(*helmetAttackTextures[direction * 4 + frame]->texture);
			
			if(armor!=nullptr)
				armorSprite.setTexture(*armorAttackTextures[direction * 4 + frame]->texture);
			
			if(pants!=nullptr)
				pantsSprite.setTexture(*pantsAttackTextures[direction * 4 + frame]->texture);

			if (rightHand != nullptr)
				rightHandSprite.setTexture(*rightHandAttackTextures[direction * 4 + frame]->texture);

			if (leftHand != nullptr)
				leftHandSprite.setTexture(*leftHandAttackTextures[direction * 4 + frame]->texture);
		}		
		else if (state == unitStates::run) {

			calculateCurrentFrame(dt);
			state = unitStates::idle;

			if (direction == 0) position.y -= distance;
			if (direction == 1) position.x += distance;
			if (direction == 2) position.y += distance;
			if (direction == 3) position.x -= distance;

			bodySprite.setTexture(*bodyRunTextures[direction * 4 + frame]->texture);
			
			if(helmet!=nullptr)
				helmetSprite.setTexture(*helmetRunTextures[direction * 4 + frame]->texture);
			
			if(armor!=nullptr)
				armorSprite.setTexture(*armorRunTextures[direction * 4 + frame]->texture);
			
			if(pants!=nullptr)
				pantsSprite.setTexture(*pantsRunTextures[direction * 4 + frame]->texture);

			if (rightHand != nullptr)
				rightHandSprite.setTexture(*rightHandRunTextures[direction * 4 + frame]->texture);
			
			if (leftHand != nullptr)
				leftHandSprite.setTexture(*leftHandRunTextures[direction * 4 + frame]->texture);

		}
		else if(state == unitStates::idle) {

			calculateCurrentFrame(dt);
			bodySprite.setTexture(*bodyIdleTextures[direction * 4 +frame]->texture);
			
			if(helmet!=nullptr)
				helmetSprite.setTexture(*helmetIdleTextures[direction * 4 +frame]->texture);
			
			if(armor!=nullptr)
				armorSprite.setTexture(*armorIdleTextures[direction * 4 +frame]->texture);
			
			if(pants!=nullptr)
				pantsSprite.setTexture(*pantsIdleTextures[direction * 4 +frame]->texture);
			
			if (rightHand != nullptr)
				rightHandSprite.setTexture(*rightHandIdleTextures[direction * 4 + frame]->texture);

			if (leftHand != nullptr)
				leftHandSprite.setTexture(*leftHandIdleTextures[direction * 4 + frame]->texture);
		}

		if (cooldown > 0.0f)
			cooldown -= dt;

		bodySprite.setPosition(position);
		
		helmetSprite.setPosition(position);
		armorSprite.setPosition(position);
		pantsSprite.setPosition(position);
		rightHandSprite.setPosition(position);
		leftHandSprite.setPosition(position);
		
		actionRangeArea.setPosition(position);
		
	}

	virtual void drawColliders() {
		GameObject::drawColliders();
	}

	virtual void draw() {
		if (mouseIsHover) {
			window->draw(actionRangeArea);
			GameObject::draw();
		}
		
		if (direction == 0) {
			// TOP
			renderer->getTheCurrentFrame()->draw(rightHandSprite);
			renderer->getTheCurrentFrame()->draw(leftHandSprite);
			renderer->getTheCurrentFrame()->draw(bodySprite);
			renderer->getTheCurrentFrame()->draw(helmetSprite);
			renderer->getTheCurrentFrame()->draw(pantsSprite);
			renderer->getTheCurrentFrame()->draw(armorSprite);
		}

		if (direction == 1) {
			// RIGHT
			
			renderer->getTheCurrentFrame()->draw(leftHandSprite);
			renderer->getTheCurrentFrame()->draw(bodySprite);
			renderer->getTheCurrentFrame()->draw(helmetSprite);
			renderer->getTheCurrentFrame()->draw(pantsSprite);
			renderer->getTheCurrentFrame()->draw(armorSprite);
			renderer->getTheCurrentFrame()->draw(rightHandSprite);
		}

		if (direction == 2) {
			// BOTTOM
			renderer->getTheCurrentFrame()->draw(bodySprite);
			renderer->getTheCurrentFrame()->draw(helmetSprite);
			renderer->getTheCurrentFrame()->draw(pantsSprite);
			renderer->getTheCurrentFrame()->draw(armorSprite);
			renderer->getTheCurrentFrame()->draw(leftHandSprite);
			renderer->getTheCurrentFrame()->draw(rightHandSprite);
		}

		if (direction == 3) {
			// LEFT
			renderer->getTheCurrentFrame()->draw(rightHandSprite);
			renderer->getTheCurrentFrame()->draw(bodySprite);
			renderer->getTheCurrentFrame()->draw(helmetSprite);
			renderer->getTheCurrentFrame()->draw(pantsSprite);
			renderer->getTheCurrentFrame()->draw(armorSprite);
			renderer->getTheCurrentFrame()->draw(leftHandSprite);
			
			
		}
		
	}
};

Player* player = nullptr;

void createPlayer() {
	player = new Player();
	gameObjects.push_back(player);

	//player->gainEXP(50 + 100 + 200 + 400 + 800 + 1600);

	//player->STRENGTH += 8;
	//player->DEXTERITY += 4;

	//player->SKILL_POINTS -= 12;
	
	player->gainEXP(40);
	player->HP = 10;
}
#endif