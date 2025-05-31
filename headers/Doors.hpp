#ifndef Doors_hpp
#define Doors_hpp

enum class DoorState { Open, Opening, Close, Closing };

class Door : public GameObject {
public:
	DoorState state;
	SingleTexture* takeItTexture;
	sf::Sprite takeItSprite;
	bool showHand;

	Door(std::wstring name, float width, float length, float height, float width_left, float width_right) : GameObject(name, width, length, height, width_left, width_right) {

		type = GameObjectType::Door;

		state = DoorState::Close;

		takeItTexture = getSingleTexture(L"GUI\\hand");
		takeItSprite = sf::Sprite();
		takeItSprite.setTexture(*takeItTexture->texture);
		takeItSprite.setOrigin(takeItTexture->cx, takeItTexture->cy);

		showHand = false;

		textname.setPosition(position.x, position.y - height - 3);
		takeItSprite.setPosition(position.x, position.y - 50);
	}

	Door(GameObject* object) : GameObject(object) {

		type = GameObjectType::Door;

		state = DoorState::Close;

		takeItTexture = getSingleTexture(L"GUI\\hand");
		takeItSprite = sf::Sprite();
		takeItSprite.setTexture(*takeItTexture->texture);
		takeItSprite.setOrigin(takeItTexture->cx, takeItTexture->cy);

		showHand = false;

		textname.setPosition(position.x, position.y - height - 3);
		takeItSprite.setPosition(position.x, position.y - 50);
	}

	virtual ~Door() {

	}

	void open() {
		state = DoorState::Opening;
		last_action_time = currentTime;
	}

	void close() {
		state = DoorState::Closing;
		float width = sprite.getGlobalBounds().getSize().x - colliders[0]->width - colliders[1]->width;
		colliders.push_back(new Collider(width, colliders[0]->length, position, 0, -8, ColliderType::Rectangle));
		last_action_time = currentTime;
	}

	bool playerNextTo() {

		if (player == nullptr)
			return false;

		float x1, y1, rx1, ry1;
		float x2, y2, rx2, ry2;
		float x3, y3, rx3, ry3;

		x1 = player->position.x;
		y1 = player->position.y;
		rx1 = (player->colliders[0]->width / 2.0f + player->actionRange);
		ry1 = (player->colliders[0]->length + player->actionRange) / 2.0f;

		x3 = player->position.x;
		y3 = player->position.y;
		rx3 = (player->colliders[0]->width / 2.0f);
		ry3 = (player->colliders[0]->length / 2.0f);

		x2 = position.x;
		y2 = position.y;
		rx2 = colliders[0]->width;
		ry2 = colliders[0]->length;

		if (intersectionRectangleWithElipse(x2, y2, rx2, ry2, x1, y1, rx1, ry1) && !intersectionRectangleWithElipse(x2, y2, rx2, ry2, x3, y3, rx3, ry3))
			return true;
		else
			return false;
	}

	virtual void update() {

		mouseHovering();

		textname.setPosition(position.x, position.y - height - 35);

		for (auto& col : colliders) {
			col->setPosition(position);
		}

		(playerNextTo()) ? showHand = true : showHand = false;

		if ((currentTime - last_action_time).asSeconds() > 0.5f) {
			if (state == DoorState::Opening) {
				frame += 1;
				last_action_time = currentTime;
				sprite.setTexture(*textures[frame]->texture);

				if (frame == textures.size() - 1) {
					state = DoorState::Open;
					delete colliders.back();
					colliders.pop_back();
				}
			}
			else if (state == DoorState::Closing) {
				frame -= 1;
				last_action_time = currentTime;
				sprite.setTexture(*textures[frame]->texture);

				if (frame == 0) {
					state = DoorState::Close;
				}
			}
			/*
			// for the testing 
			else if (state == DoorState::Open) {
				close();
			}
			else if (state == DoorState::Close) {
				open();
			}
			*/

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

		if (showHand)
			renderer->getTheCurrentFrame()->draw(takeItSprite);

	}


};

std::vector < Door* > doors;

#endif