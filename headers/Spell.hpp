#ifndef Spell_hpp
#define Spell_hpp

enum class SpellStates { start, in_progress, complete };
enum class AreaSpellType { growing, static_radius };

class Spell : public GameObject {
public:
	Spell(std::wstring name, float x, float y) : GameObject(name, x, y) {
	
	}

	~Spell() {
	
	}
};

class Bomb : public GameObject {
public:
	float speed;
	float angle;
	
	Bomb(std::wstring name, float x, float y, float speed, float angle) : GameObject(name, x, y) {
		this->speed = speed;
		this->angle = angle;

		textures = getAnimation(L"spells\\" + name);
		sprite.setTexture(*textures.front()->texture);
		sprite.setOrigin(16, 16);
	}

	~Bomb() { }

	void cursorHover() { }
	void handleEvent(sf::Event& event) { }
	void update() {

		if ((currentTime - last_action_time).asSeconds() > 0.1f) {
			sf::Vector2f pos;
			pos.x = position.x + speed * cos(angle * M_PI / 180.0f);
			pos.y = position.y + speed * sin(angle * M_PI / 180.0f);

			setPosition(pos);
		}

		GameObject::update();

		
	}

	void draw() {
		GameObject::draw();
	}
};

class AreaFireballSpell : public Spell {
public:
	SpellStates state;
	std::vector < Bomb* > bombs;
	sf::Time start_time;
	float life_time_seconds;

	AreaFireballSpell(float life_time_seconds, float x, float y) : Spell(L"area_fireball_spell", x, y) {
		
		state = SpellStates::start;
		this->life_time_seconds = life_time_seconds;

		generate_bombs();

		start_time = currentTime;
		state = SpellStates::in_progress;
	}

	~AreaFireballSpell() {

	}

	void generate_bombs() {
		float angle = rand() % 360;
		int bombs_count = 10;
		for (int i = 0; i < bombs_count; i++) {
			float a = angle + (360 / bombs_count) * i;
			Bomb* b = new Bomb(L"fireball", position.x, position.y, 8.0f, a);
			bombs.push_back(b);
		}
	}

	void setPosition(sf::Vector2f position) {
		
		sf::Vector2f p = GameObject::position;

		GameObject::setPosition(position);
		for (auto& bomb : bombs) {
			sf::Vector2f new_bomb_pos = bomb->position + GameObject::position - p;
			bomb->setPosition(new_bomb_pos);


		}

	}

	void cursorHover() { }
	void handleEvent(sf::Event& event) { }
	
	void update() {

		std::cout<<position.x << " " << position.y << "\n";

		if ((currentTime - start_time).asSeconds() >= life_time_seconds) {
			state = SpellStates::complete;

			for (auto& bomb : bombs) {
				delete bomb;
			}

			bombs.clear();
			generate_bombs();
			start_time = currentTime;
			state = SpellStates::in_progress;
		}
		else {
			for (auto& bomb : bombs) {
				bomb->update();
			}
		}
	}

	void draw() {
		for (auto& bomb : bombs)
			bomb->draw();
	}

};

class Cone : public GameObject {
public:

	Cone(std::wstring name, float x, float y) : GameObject(name, x, y) {

		textures = getAnimation(L"spells\\" + name);
		sprite.setTexture(*textures.front()->texture);
		sprite.setOrigin(16, 16);

		setPosition(sf::Vector2f(x,y));
	}

	~Cone() {}

	void cursorHover() {}
	void handleEvent(sf::Event& event) {}
	void update() {
		GameObject::update();
	}

	void draw() {
		GameObject::draw();
	}
};

class AreaWaterConesSpell : public Spell {
public:
	SpellStates state;
	std::vector < Cone* > cones;
	sf::Time start_time;
	float life_time_seconds;

	AreaWaterConesSpell(float life_time_seconds, float x, float y) : Spell(L"area_water_cones_spell", x, y) {

		state = SpellStates::start;
		this->life_time_seconds = life_time_seconds;

		generate_cones();

		start_time = currentTime;
		state = SpellStates::in_progress;
	}

	~AreaWaterConesSpell() {

	}

	void generate_cones() {
		float angle = rand() % 360;
		int cones_count = 10;
		for (int i = 0; i < cones_count; i++) {
			float a = angle + (360 / cones_count) * i;

			sf::Vector2f pos;
			pos.x = position.x + 48.0f * cos(a * M_PI / 180.0f);
			pos.y = position.y + 48.0f * sin(a * M_PI / 180.0f);

			Cone* b = new Cone(L"water_cone", pos.x, pos.y);
			cones.push_back(b);
		}
	}

	void setPosition(sf::Vector2f position) {

		sf::Vector2f p = GameObject::position;

		GameObject::setPosition(position);
		for (auto& cone : cones) {
			sf::Vector2f new_cone_pos = cone->position + GameObject::position - p;
			cone->setPosition(new_cone_pos);


		}

	}

	void cursorHover() {}
	void handleEvent(sf::Event& event) {}

	void update() {

		if ((currentTime - start_time).asSeconds() > life_time_seconds) {
			state = SpellStates::complete;

			for (auto& cone : cones) {
				delete cone;
			}

			cones.clear();
			generate_cones();
			start_time = currentTime;
			state = SpellStates::in_progress;
		}
		else {
			for (auto& cone : cones) {
				cone->update();
			}
		}
	}

	void draw() {
		for (auto& cone : cones)
			cone->draw();
	}

};

class StaticSpell : public Spell {
public:
	SpellStates state;

	StaticSpell(std::wstring name, float x, float y) : Spell(L"magic circle", x, y) {

		state = SpellStates::start;
		
		textures = getAnimation(L"spells\\" + name);
		sprite.setTexture(*textures.front()->texture);
		sprite.setOrigin(textures.front()->cx, textures.front()->cy);
		setPosition(sf::Vector2f(x, y));
		state = SpellStates::in_progress;
	}

	~StaticSpell() {

	}

	void cursorHover() {}
	void handleEvent(sf::Event& event) {}

	void update() {

		Spell::update();
	}

	void draw() {
		Spell::draw();
	}

};
#endif