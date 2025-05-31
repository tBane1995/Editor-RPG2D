#ifndef GameObjects_hpp
#define GameObjects_hpp

enum class GameObjectType {
	GameObject,
	Nature, Object,
	Unit, Monster, Character, Player,
	ItemOnMap, InventoryOnMap,
	FlatObject, SmallObject,
	Terrain, Floor, Water,
	Door, Furniture, Wall, Building
};

enum class ColliderType { Elipse, Rectangle };

class Collider
{
public:
	float width;
	float length;
	sf::Vector2f position;
	float dx, dy;
	ColliderType type;
	sf::Shape* shape;


	Collider(float width, float length, sf::Vector2f position, float dx, float dy, ColliderType type) {
		this->width = width;
		this->length = length;
		this->position = position;
		this->dx = dx;
		this->dy = dy;
		this->type = type;

		if (type == ColliderType::Rectangle) {
			shape = new sf::RectangleShape(sf::Vector2f(width, length));
			shape->setFillColor(sf::Color(128, 64, 128, 96));
			shape->setOutlineColor(sf::Color(196, 64, 196, 128));
			shape->setOutlineThickness(4.0f);
			shape->setOrigin(width / 2.0f, length / 2.0f);
			shape->setScale(1, 1);
			shape->setPosition(this->position.x + this->dx, this->position.y + this->dy);
		}

		else if (type == ColliderType::Elipse) {
			shape = new sf::CircleShape(width / 2.0f);
			shape->setFillColor(sf::Color(128, 64, 128, 96));
			shape->setOutlineColor(sf::Color(196, 64, 196, 128));
			shape->setOutlineThickness(4.0f);
			shape->setOrigin(width / 2.0f, width / 2.0f);
			shape->setScale(1, length / width);
			shape->setPosition(this->position.x + this->dx, this->position.y + this->dy);
		}
	}

	Collider(Collider* col) {
		this->width = col->width;
		this->length = col->length;
		this->type = col->type;
		this->position = col->position;
		this->dx = col->dx;
		this->dy = col->dy;

		if (type == ColliderType::Rectangle) {
			shape = new sf::RectangleShape(sf::Vector2f(width, length));
			shape->setFillColor(col->shape->getFillColor());
			shape->setOutlineColor(col->shape->getOutlineColor());
			shape->setOutlineThickness(col->shape->getOutlineThickness());
			shape->setOrigin(col->shape->getOrigin());
			shape->setScale(col->shape->getScale());
			shape->setPosition(this->position.x + this->dx, this->position.y + this->dy);
		}
		else if (type == ColliderType::Elipse) {
			shape = new sf::CircleShape(width / 2.0f);
			shape->setFillColor(col->shape->getFillColor());
			shape->setOutlineColor(col->shape->getOutlineColor());
			shape->setOutlineThickness(col->shape->getOutlineThickness());
			shape->setOrigin(col->shape->getOrigin());
			shape->setScale(col->shape->getScale());
			shape->setPosition(this->position.x + this->dx, this->position.y + this->dy);
		}
	}

	Collider(Collider* col, sf::Vector2f position) {
		this->width = col->width;
		this->length = col->length;
		this->type = col->type;
		this->position = position;
		this->dx = col->dx;
		this->dy = col->dy;

		if (type == ColliderType::Rectangle) {
			shape = new sf::RectangleShape(sf::Vector2f(width, length));
			shape->setFillColor(col->shape->getFillColor());
			shape->setOutlineColor(col->shape->getOutlineColor());
			shape->setOutlineThickness(col->shape->getOutlineThickness());
			shape->setOrigin(col->shape->getOrigin());
			shape->setScale(col->shape->getScale());
			shape->setPosition(this->position.x + this->dx, this->position.y + this->dy);
		}
		else if (type == ColliderType::Elipse) {
			shape = new sf::CircleShape(width / 2.0f);
			shape->setFillColor(col->shape->getFillColor());
			shape->setOutlineColor(col->shape->getOutlineColor());
			shape->setOutlineThickness(col->shape->getOutlineThickness());
			shape->setOrigin(col->shape->getOrigin());
			shape->setScale(col->shape->getScale());
			shape->setPosition(this->position.x + this->dx, this->position.y + this->dy);
		}
	}


	~Collider() {
		delete shape;	// sf::Shape* shape
	}

	void setPosition(sf::Vector2f position) {
		this->position = position;
		shape->setPosition(this->position.x + this->dx, this->position.y + this->dy);
	}

	void draw() {
		window->draw(*shape);
	}
};

class GameObject;
GameObject* hover_gameObject = nullptr;
GameObject* clicked_gameObject = nullptr;

class GameObject {
public:
	std::wstring name;
	GameObjectType type;
	sf::Vector2f position;
	float height;
	SingleTexture* texture;
	std::vector < SingleTexture* > textures;
	short frame;
	sf::Time last_action_time;
	sf::Sprite sprite;
	
	std::vector < Collider* > colliders;
	sf::Text textname;

	bool collisioning;	// check the collision
	bool mouseIsHover;	// mouse is on GameObject
	bool isVisible;
	bool isSelected;
	bool isInTheMainList;

	Mesh* mesh;

	GameObject(std::wstring name, float width, float length, float height, bool collisioning, ColliderType col_type) {
		// CREATE PREFAB
		this->name = name;

		textures = getAnimation(name);
		if (textures.empty() && getSingleTexture(name) != nullptr)
			textures.push_back(getSingleTexture(name));

		mesh = getMesh(name);

		type = GameObjectType::GameObject;
		position.x = 0;
		position.y = 0;
		this->height = height;

		frame = 0;
		last_action_time = currentTime;

		sprite = sf::Sprite();
		if (!textures.empty()) {
			sprite.setTexture(*textures[0]->texture);
			sprite.setOrigin(textures[0]->cx, textures[0]->cy);
		}
		sprite.setPosition(position);

		this->collisioning = collisioning;
		colliders.clear();
		colliders.push_back(new Collider(width, length, position, 0, 0, col_type));

		mouseIsHover = false;

		createTextname();

		isInTheMainList = false;
		isVisible = false;
		isSelected = false;

	}

	GameObject(std::wstring name, float width, float length, float height, float width_left, float width_right) {
		// CREATE PREFAB: DOORS/GATES
		this->name = name;

		textures = getAnimation(name);
		if (textures.empty() && getSingleTexture(name) != nullptr)
			textures.push_back(getSingleTexture(name));

		mesh = getMesh(name);

		type = GameObjectType::GameObject;
		position.x = 0;
		position.y = 0;
		this->height = height;

		frame = 0;
		last_action_time = currentTime;

		sprite = sf::Sprite();
		if (!textures.empty()) {
			sprite.setTexture(*textures[0]->texture);
			sprite.setOrigin(textures[0]->cx, textures[0]->texture->getSize().y - 1);
		}
		sprite.setPosition(position);

		this->collisioning = true;
		colliders.clear();
		colliders.push_back(new Collider(width_left, length, position, -width / 2 + width_left / 2, -8, ColliderType::Rectangle));
		colliders.push_back(new Collider(width_right, length, position, +width / 2 - width_right / 2, -8, ColliderType::Rectangle));
		colliders.push_back(new Collider(width - width_left - width_right, length, position, 0, -8, ColliderType::Rectangle));

		mouseIsHover = false;

		createTextname();

		isInTheMainList = false;
		isVisible = false;
		isSelected = false;
	}

	GameObject(GameObject* go) {
		// CREATE GAMEOBJECT FROM PREFAB
		this->name = go->name;
		
		textures = go->textures;
		mesh = go->mesh;

		type = GameObjectType::GameObject;
		position.x = 0;
		position.y = 0;
		this->height = go->height;

		frame = 0;
		last_action_time = currentTime;

		sprite = sf::Sprite();
		if (!textures.empty()) {
			sprite.setTexture(*textures[0]->texture);
			sprite.setOrigin(go->sprite.getOrigin());
		}
		sprite.setPosition(position);

		this->collisioning = go->collisioning;
		colliders.clear();
		for (auto& col : go->colliders)
			colliders.push_back(new Collider(col, position));


		mouseIsHover = false;

		createTextname();

		isInTheMainList = false;
		isVisible = false;
		isSelected = false;
	}

	GameObject(std::wstring name) {
		// FOR TILES PALETTE (TERRAIN OR FLOOR) 
		this->name = name;
		position.x = 0;
		position.y = 0;
		this->height = 16;

		collisioning = true;
		colliders.clear();
		colliders.push_back(new Collider(16, 16, position, 0, 0, ColliderType::Rectangle));

		// TO-DO -
		dynamic_cast<sf::RectangleShape*>(colliders[0]->shape)->setOrigin(sf::Vector2f(0, 0));
		dynamic_cast<sf::RectangleShape*>(colliders[0]->shape)->setSize(sf::Vector2f(16, 16));
		dynamic_cast<sf::RectangleShape*>(colliders[0]->shape)->setOutlineThickness(0);
		dynamic_cast<sf::RectangleShape*>(colliders[0]->shape)->setPosition(position);
		//

		mesh = nullptr;

		mouseIsHover = false;

		createTextname();

		isInTheMainList = false;
		isVisible = false;
		isSelected = false;
	}

	GameObject(GameObjectType object_type, short id, float x, float y) {

		if (object_type == GameObjectType::Building) {
			this->name = L"building_" + to_wstring(id);
			position.x = x;
			position.y = y;
			this->height = 0;

			textures.clear();
			mesh = nullptr;
			sprite = sf::Sprite();

			collisioning = false;
			colliders.clear();

			mouseIsHover = false;

			createTextname();

			isInTheMainList = false;
			isVisible = false;
			isSelected = false;
		}

		if (object_type == GameObjectType::Character) {
			this->name = L"character_" + to_wstring(id);

			textures.clear();

			mesh = nullptr;

			position.x = x;
			position.y = y;
			this->height = 64;

			frame = 0;
			last_action_time = currentTime;

			sprite = sf::Sprite();
			sprite.setPosition(position);

			this->collisioning = collisioning;
			colliders.clear();
			colliders.push_back(new Collider(36, 18, position, 0, 0, ColliderType::Elipse));

			mouseIsHover = false;

			createTextname();

			isInTheMainList = false;
			isVisible = false;
			isSelected = false;
		}

		
	}

	virtual ~GameObject() {
		
		if (!colliders.empty()) {
			for (auto& col : colliders) {
				delete col;
			}

			colliders.clear();
		}
	}


	virtual void setPosition(sf::Vector2f position) {
		this->position = position;

		for (auto& col : colliders)
			col->setPosition(position);

		sf::Vector2f pos;
		pos.x = position.x;
		pos.y = position.y;
		sprite.setPosition(pos);

		textname.setPosition(position.x, position.y - height - 35);
	}

	void createTextname() {
		textname = sf::Text(getShortName(name), basicFont, 16);

		textname.setOrigin(textname.getGlobalBounds().width / 2.f, textname.getGlobalBounds().height / 2.f);
		textname.setFillColor(dialoguesColor);
		textname.setOutlineColor(sf::Color::Black);
		textname.setOutlineThickness(2.0f);

		textname.setPosition(position.x, position.y - height - 35);
	}

	virtual void mouseHovering() {

		mouseIsHover = false;

		if (mesh != nullptr) {
			for (auto& tri : mesh->triangles) {
				if (isPointInTriangle(tri.a + position, tri.b + position, tri.c + position, worldMousePosition)) {

					if(hover_gameObject)
						hover_gameObject->mouseIsHover = false;
					mouseIsHover = true;
					hover_gameObject = this;
					return;
				}
			}
		}

		// if mesh == nullptr then check the colliders

		for (int i = 0; i < colliders.size() && mouseIsHover == false; i++) {
			if (colliders[i]->type == ColliderType::Elipse) {

				if (isPointInEllipse(worldMousePosition.x, worldMousePosition.y, position.x + colliders[i]->dx, position.y + colliders[i]->dy, colliders[i]->width / 2.0f, colliders[i]->length / 2.0f)) {

					if (hover_gameObject)
						hover_gameObject->mouseIsHover = false;
					mouseIsHover = true;
					hover_gameObject = this;
					return;
				}

			}

			else if (colliders[i]->type == ColliderType::Rectangle) {

				if (isPointInRectangle(worldMousePosition.x, worldMousePosition.y, position.x + colliders[i]->dx, position.y + colliders[i]->dy, colliders[i]->width, colliders[i]->length)) {

					if (hover_gameObject)
						hover_gameObject->mouseIsHover = false;
					mouseIsHover = true;
					hover_gameObject = this;
					return;
				}
			}
		}
		
		
	}

	virtual void update() {

		textname.setPosition(position.x, position.y - height - 35);

		for (auto& col : colliders) {
			col->setPosition(position);
		}

		if (textures.size() > 1) {
			if ((currentTime - last_action_time).asSeconds() > 0.1f) {

				last_action_time = currentTime;
				frame += 1;

				if (frame >= textures.size())
					frame = 0;

				sprite.setTexture(*textures[frame]->texture);
			}
		}
	}


	virtual void drawColliders() {
		if (renderer->renderColliders || isSelected || (!GUIwasOpen && !GUIwasClicked && !GUIwasHover && mouseIsHover)) {

			for (auto& col : colliders) {
				renderer->getTheCurrentFrame()->draw(*col->shape);
			}
		}
			
	}

	virtual void draw() {

		if (mouseIsHover || isSelected) {
			sf::Shader* sh = getShader(L"shaders\\highlighted")->shader;
			sh->setUniform("texture", *sprite.getTexture());
			renderer->getTheCurrentFrame()->draw(sprite, sh);
		}
		else {
			renderer->getTheCurrentFrame()->draw(sprite);
		}


		if (renderer->renderMeshes == true) {
			if (mesh != nullptr) {
				mesh->draw(position);
			}
		}
	}
	
};

std::vector < GameObject* > gameObjects;

bool intersection(GameObject* object1, GameObject* object2) {

	for (auto& collider_1 : object1->colliders) {

		if (collider_1->type == ColliderType::Elipse) {

			for (auto& collider_2 : object2->colliders) {
				if (collider_2->type == ColliderType::Elipse) {
					// elipse with elipse
					if (intersectionTwoEllipses(object1->position.x + collider_1->dx, object1->position.y + collider_1->dy, collider_1->width / 2.0f, collider_1->length / 2.f, object2->position.x + collider_2->dx, object2->position.y + collider_2->dy, collider_2->width / 2.0f, collider_2->length / 2.f)) {
						return true;
					}
				}

				if (collider_2->type == ColliderType::Rectangle) {
					// elipse with rectangle
					if (intersectionRectangleWithElipse(object2->position.x + collider_2->dx, object2->position.y + collider_2->dy, collider_2->width, collider_2->length, object1->position.x + collider_1->dx, object1->position.y + collider_1->dy, collider_1->width / 2.0f, collider_1->length / 2.0f)) {
						return true;
					}

				}
			}
		}
		else if (collider_1->type == ColliderType::Rectangle) {

			for (auto& collider_2 : object2->colliders) {
				if (collider_2->type == ColliderType::Elipse) {
					// rectangle with elipse
					if (intersectionRectangleWithElipse(object1->position.x + collider_1->dx, object1->position.y + collider_1->dy, collider_1->width, collider_1->length, object2->position.x + collider_2->dx, object2->position.y + collider_2->dy, collider_2->width / 2.0f, collider_2->length / 2.0f))
						return true;
				}

				if (collider_2->type == ColliderType::Rectangle) {
					// rectangle with rectangle
					if (intersectionTwoRectangles(object1->position.x + collider_1->dx, object1->position.y + collider_1->dy, collider_1->width, collider_1->length, object2->position.x + collider_2->dx, object2->position.y + collider_2->dy, collider_2->width, collider_2->length))
						return true;
				}
			}

		}
	}

	return false;

}

bool collisionPrediction(GameObject* object, float dx, float dy)
{
	if (object->collisioning == false)
		return false;

	for (auto& collider_1 : object->colliders) {

		if (collider_1->type == ColliderType::Elipse) {

			for (auto& go : gameObjects) {
				if (go != object && go->collisioning != false) {

					for (auto& collider_2 : go->colliders) {
						if (collider_2->type == ColliderType::Elipse) {
							// elipse with elipse
							if (intersectionTwoEllipses(object->position.x + dx + collider_1->dx, object->position.y + dy + collider_1->dy, collider_1->width / 2.0f, collider_1->length / 2.f, go->position.x + collider_2->dx, go->position.y + collider_2->dy, collider_2->width / 2.0f, collider_2->length / 2.f)) {
								return true;
							}

						}

						if (collider_2->type == ColliderType::Rectangle) {
							// elipse with rectangle
							if (intersectionRectangleWithElipse(go->position.x + collider_2->dx, go->position.y + collider_2->dy, collider_2->width, collider_2->length, object->position.x + dx + collider_1->dx, object->position.y + dy + collider_1->dy, collider_1->width / 2.0f, collider_1->length / 2.0f)) {
								return true;
							}


						}
					}

				}
			}
		}
		else if (collider_1->type == ColliderType::Rectangle) {

			for (auto& go : gameObjects) {
				if (go != object && go->collisioning != false) {

					for (auto& collider_2 : go->colliders) {
						if (collider_2->type == ColliderType::Elipse) {
							// rectangle with elipse
							if (intersectionRectangleWithElipse(object->position.x + dx + collider_1->dx, object->position.y + dy + collider_1->dy, collider_1->width, collider_1->length, go->position.x + collider_2->dx, go->position.y + collider_2->dy, collider_2->width / 2.0f, collider_2->length / 2.0f))
								return true;
						}

						if (collider_2->type == ColliderType::Rectangle) {
							// rectangle with rectangle
							if (intersectionTwoRectangles(object->position.x + dx + collider_1->dx, object->position.y + dy + collider_1->dy, collider_1->width, collider_1->length, go->position.x + collider_2->dx, go->position.y + collider_2->dy, collider_2->width, collider_2->length))
								return true;

						}
					}

				}
			}
		}

	}

	return false;
}

bool collisionPrediction(GameObject* object, Point p, float dx, float dy)
{
	if (object->collisioning == false)
		return false;

	for (auto& collider_1 : object->colliders) {

		if (collider_1->type == ColliderType::Elipse) {

			for (auto& go : gameObjects) {
				if (go != object && go->collisioning != false) {
					for (auto& collider_2 : go->colliders) {
						if (collider_2->type == ColliderType::Elipse) {
							// elipse with elipse
							if (intersectionTwoEllipses(p.x + dx + collider_1->dx, p.y + dy + collider_1->dy, collider_1->width / 2.0f, collider_1->length / 2.f, go->position.x + collider_2->dx, go->position.y + collider_2->dy, collider_2->width / 2.0f, collider_2->length / 2.f))
								return true;
						}

						if (collider_2->type == ColliderType::Rectangle) {
							// elipse with rectangle
							if (intersectionRectangleWithElipse(go->position.x + collider_2->dx, go->position.y + collider_2->dy, collider_2->width, collider_2->length, p.x + dx + collider_1->dx, p.y + dy + collider_1->dy, collider_1->width / 2.0f, collider_1->length / 2.0f))
								return true;

						}
					}
				}
			}
		}
		else if (collider_1->type == ColliderType::Rectangle) {
			for (auto& go : gameObjects) {
				if (go != object && go->collisioning != false) {
					for (auto& collider_2 : go->colliders) {

						if (collider_2->type == ColliderType::Elipse) {
							// rectangle with elipse
							if (intersectionRectangleWithElipse(p.x + dx + collider_1->dx, p.y + dy + collider_1->dy, collider_1->width, collider_1->length, go->position.x + collider_2->dx, go->position.y + collider_2->dy, collider_2->width / 2.0f, collider_2->length / 2.0f))
								return true;
						}

						if (collider_2->type == ColliderType::Rectangle) {
							// rectangle with rectangle
							if (intersectionTwoRectangles(p.x + dx + collider_1->dx, p.y + dy + collider_1->dy, collider_1->width, collider_1->length, go->position.x + collider_2->dx, go->position.y + collider_2->dy, collider_2->width, collider_2->length))
								return true;

						}
					}
				}
			}
		}

	}

	return false;
}



#endif