#ifndef Units_hpp
#define Units_hpp

float diff_x, diff_y;
float dist;

class Unit : public GameObject {
public:
	
	string bodySet;

	short LEVEL;
	short EXPERIENCE;
	short SKILL_POINTS;

	short HP, HP_FULL;
	short MP, MP_FULL;
	short STRENGTH;
	short DEXTERITY;
	short INTELLIGENCE;
	
	short ACTION_RANGE;	// range of action 
	short VIEW_RANGE;	// range of view
	
	unitStates state;		// idle, run or attack
	short frame;			// current frame
	short direction;		// direction 0 - Top, 1 - Right, 2 - Bottom, 3 - Left

	float countdown;	// timer to calculate frame
	float cooldown;		// timer past attack to freeze
	float attackTime;	// attack time in seconds

	SingleTexture* idleTextures[16];		// idle textures	
	SingleTexture* runTextures[16];		// run textures
	SingleTexture* attackTextures[16];	// attack textures
	sf::Sprite sprite;				// sprite to render texture

	sf::CircleShape viewRangeArea;		// is a range of see of units // in this range player can be a select as target
	sf::CircleShape actionRangeArea;
	sf::RectangleShape lifeBarBackground;
	sf::RectangleShape lifeBar;

	sf::Vector2f target;


	Unit(string name, string bodySet, float width, float length, float height) : GameObject(name, 0, 0, width, length, height, true, ColliderType::Elipse) {

		type = GameObjectType::Unit;

		this->name = name;
		this->bodySet = bodySet;

		LEVEL = 0;
		EXPERIENCE = 0;
		SKILL_POINTS = 0;

		HP = 40;
		HP_FULL = 40;
		MP = 10;
		MP_FULL = 10;

		STRENGTH = 5;
		DEXTERITY = 5;
		INTELLIGENCE = 5;

		VIEW_RANGE = 256;
		ACTION_RANGE = 32;

		state = unitStates::idle;
		frame = 0;
		direction = 2;

		countdown = 0.0f;
		cooldown = 0.0f;	
		attackTime = 1.0f;	// in seconds

		loadBody();
		
		createViewRangeArea();
		createActionRangeArea();
	
	}

	Unit(GameObject* object, float x, float y) : GameObject(object, x, y) {
		
		type = GameObjectType::Unit;

		this->name = dynamic_cast<Unit*>(object)->name;
		this->bodySet = dynamic_cast<Unit*>(object)->bodySet;

		LEVEL = dynamic_cast<Unit*>(object)->LEVEL;
		EXPERIENCE = dynamic_cast<Unit*>(object)->EXPERIENCE;
		SKILL_POINTS = dynamic_cast<Unit*>(object)->SKILL_POINTS;

		HP = dynamic_cast<Unit*>(object)->HP;
		HP_FULL = dynamic_cast<Unit*>(object)->HP_FULL;
		MP = dynamic_cast<Unit*>(object)->MP;
		MP_FULL = dynamic_cast<Unit*>(object)->MP_FULL;

		STRENGTH = dynamic_cast<Unit*>(object)->STRENGTH;
		DEXTERITY = dynamic_cast<Unit*>(object)->DEXTERITY;
		INTELLIGENCE = dynamic_cast<Unit*>(object)->INTELLIGENCE;

		VIEW_RANGE = dynamic_cast<Unit*>(object)->VIEW_RANGE;
		ACTION_RANGE = dynamic_cast<Unit*>(object)->ACTION_RANGE;

		state = unitStates::idle;
		frame = 0;
		direction = 2;

		countdown = 0.0f;
		cooldown = 0.0f;
		attackTime = dynamic_cast<Unit*>(object)->attackTime;

		loadBody();

		createViewRangeArea();
		createActionRangeArea();
	}

	virtual ~Unit() {
	
	}

	void loadBody() {
		for (short i = 0; i < 16; i++) {
			idleTextures[i] = nullptr;
			runTextures[i] = nullptr;
			attackTextures[i] = nullptr;

		}

		for (short i = 0; i < 4; i++) {

			idleTextures[i] = getSingleTexture(bodySet + "/idleTop" + to_string(i));
			idleTextures[4 + i] = getSingleTexture(bodySet + "/idleRight" + to_string(i));
			idleTextures[8 + i] = getSingleTexture(bodySet + "/idleBottom" + to_string(i));
			idleTextures[12 + i] = getSingleTexture(bodySet + "/idleLeft" + to_string(i));

			runTextures[i] = getSingleTexture(bodySet + "/runTop" + to_string(i));
			runTextures[4 + i] = getSingleTexture(bodySet + "/runRight" + to_string(i));
			runTextures[8 + i] = getSingleTexture(bodySet + "/runBottom" + to_string(i));
			runTextures[12 + i] = getSingleTexture(bodySet + "/runLeft" + to_string(i));

			attackTextures[i] = getSingleTexture(bodySet + "/attackTop" + to_string(i));
			attackTextures[4 + i] = getSingleTexture(bodySet + "/attackRight" + to_string(i));
			attackTextures[8 + i] = getSingleTexture(bodySet + "/attackBottom" + to_string(i));
			attackTextures[12 + i] = getSingleTexture(bodySet + "/attackLeft" + to_string(i));

		}

		texture = idleTextures[0];

		sprite = sf::Sprite();
		sprite.setOrigin(texture->texture->getSize().x / 2, texture->texture->getSize().y / 2 );

	}

	void createViewRangeArea() {
		viewRangeArea = sf::CircleShape(VIEW_RANGE + colliders[0]->width / 2.0f);
		viewRangeArea.setFillColor(sf::Color(64, 64, 128, 96));
		viewRangeArea.setOutlineColor(sf::Color(64, 64, 196, 128));
		viewRangeArea.setOutlineThickness(4.0f);
		viewRangeArea.setOrigin(VIEW_RANGE + colliders[0]->width / 2.0f, VIEW_RANGE + colliders[0]->length / 2.0f);
		viewRangeArea.setScale(1.0f, colliders[0]->length / colliders[0]->width);
	}

	void createActionRangeArea() {
		actionRangeArea = sf::CircleShape(ACTION_RANGE + colliders[0]->width / 2.0f);
		actionRangeArea.setFillColor(sf::Color(128, 64, 64, 96));
		actionRangeArea.setOutlineColor(sf::Color(196, 64, 64, 128));
		actionRangeArea.setOutlineThickness(4.0f);
		actionRangeArea.setOrigin(ACTION_RANGE + colliders[0]->width / 2.0f, ACTION_RANGE + colliders[0]->width / 2.0f);
		actionRangeArea.setScale(1.0f, colliders[0]->length / colliders[0]->width);
	}

	void setLifeBar() {
		lifeBarBackground = sf::RectangleShape(sf::Vector2f(50.0f, 6.0f));
		lifeBarBackground.setOrigin(25, 3);
		lifeBarBackground.setFillColor(sf::Color::Black);
		lifeBarBackground.setPosition(position.x, position.y - height - 10);

		lifeBar = sf::RectangleShape(sf::Vector2f(48.0f * HP / HP_FULL, 4.0f));
		lifeBar.setOrigin(24, 2);
		lifeBar.setFillColor(sf::Color(128, 64, 64));
		lifeBar.setPosition(position.x, position.y - height - 10);
	}

	short takeDamage(short damage) {

		HP -= damage;

		if (HP < 0)
			HP = 0;
		
		return damage;
	}

	short getDamage() {
		short damage = STRENGTH * 2;
		damage = damage * (rand() % 50 + 75) / 100;	// 75% - 125%
		return damage;
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

	void cooldownDecrease(float dt) {
		if (cooldown >= 0.0f)
			cooldown -= dt;
	}

	bool playerInActionRange() {

		if (player == nullptr)
			return false;

		return intersectionTwoEllipses(position.x, position.y, colliders[0]->width / 2.0f + ACTION_RANGE, (colliders[0]->length + ACTION_RANGE) / 2.0f, player->position.x, player->position.y, player->colliders[0] ->width / 2.0f, player->colliders[0]->length / 2.0f);

	}

	bool playerInViewRange() {
		if (player == nullptr)
			return false;

		return intersectionTwoEllipses(position.x, position.y, colliders[0]->width / 2.0f + VIEW_RANGE, (colliders[0]->length + VIEW_RANGE) / 2.0f, player->position.x, player->position.y, player->colliders[0]->width / 2.0f, player->colliders[0]->length / 2.0f);
	}

	void goToTarget(float dt) {
		 
		dist = 15.0f * 4.0f * dt;	// distance to move
		diff_x = target.x - position.x;	// difference x
		diff_y = target.y - position.y;	// difference y

		if (diff_x == 0 && diff_y == 0)
		{
			state = unitStates::idle;
			frame = 0;

		}
		else if (diff_x!=0 && abs(diff_x) < dist) {
			position.x = target.x;
		}
		else if (diff_y!=0 && abs(diff_y) < dist) {
			position.y = target.y;
		}
		else {

			if (diff_x > 0) direction = 1; // prawo
			if (diff_x < 0) direction = 3; // lewo

			// Ruch w pionie
			if (diff_y > 0) direction = 2; // dół
			if (diff_y < 0) direction = 0; // góra

			// TO TOP
			if (direction == 0) {
				if (!collisionPrediction(this, 0, -dist))
					position.y -= dist;
				else
					state = unitStates::idle;
			}

			// TO RIGHT
			if (direction == 1) {
				if (!collisionPrediction(this, dist, 0))
					position.x += dist;
				else
					state = unitStates::idle;
			}

			// TO DOWN
			if (direction == 2) {
				if (!collisionPrediction(this, 0, dist))
					position.y += dist;
				else
					state = unitStates::idle;
			}

			// TO LEFT
			if (direction == 3) {
				if (!collisionPrediction(this, -dist, 0))
					position.x -= dist;
				else
					state = unitStates::idle;
			}
		}
		
	}

	void idle(float dt) {
		if (rand() % 60 == 0) {
			state = unitStates::run;
			target.x = position.x + rand() % 100 - 50;
			target.y = position.y + rand() % 100 - 50;
		}

		calculateCurrentFrame(dt);
		texture = idleTextures[direction * 4 + frame];
		sprite.setTexture(*texture->texture);
	}

	void run(float dt) {
		
		goToTarget(dt);

		calculateCurrentFrame(dt);
		texture = runTextures[direction * 4 + frame];
		sprite.setTexture(*texture->texture);
	}

	void attack(float dt) {

		if (cooldown <= 0.0f) {

			sf::Vector2f hitposition = sf::Vector2f(player->position.x, player->position.y - player->height);
			
			if (rand() % (DEXTERITY + 10) - rand() % (player->DEXTERITY + 5) > 0) {
				
				short damage = player->takeDamage(getDamage());
				hits->addHitText(hitposition, to_string(damage), sf::Color::Red);
			}
			else {
				hits->addHitText(hitposition, "miss", sf::Color::Red);
			}
				

			cooldown = attackTime;
			frame = 0;
		}else
			frame = (attackTime-cooldown) / attackTime * 4.0f;
			
		if (frame < 0)
			frame = 0;

		if (frame >= 4) 
			frame = 3;

		texture = attackTextures[direction * 4 + frame];
		sprite.setTexture(*texture->texture);
	}

	void idling() {

		float dt = currentTime.asSeconds() - prevTime.asSeconds();

		calculateCurrentFrame(dt);
		texture = idleTextures[direction * 4 + frame];
		sprite.setTexture(*texture->texture);
		sprite.setPosition(position);
	}

	virtual void update() {

		float dt = currentTime.asSeconds() - prevTime.asSeconds();

		calculateCurrentFrame(dt);
		sprite.setPosition(position);
		setLifeBar();

		GameObject::update();

		viewRangeArea.setPosition(position);
		actionRangeArea.setPosition(position);
	}

	virtual void drawStatistics() {
		
		if (renderViewRange || isSelected || (!GUIwasOpen && !GUIwasClicked && !GUIwasHover && mouseIsHover))
			window->draw(viewRangeArea);

		if (renderActionRange || isSelected || (!GUIwasOpen && !GUIwasClicked && !GUIwasHover && mouseIsHover))
			window->draw(actionRangeArea);

		GameObject::drawStatistics();
	}

	virtual void draw() {

		window->draw(sprite);
		window->draw(lifeBarBackground);
		window->draw(lifeBar);
	}

};

#endif