#ifndef Furnitures_hpp
#define Furnitures_hpp

class Furniture : public GameObject {
public:
	sf::Sprite sprite;

	Inventory* inventory;
	SingleTexture* takeItTexture;
	sf::Sprite takeItSprite;
	bool showHand;

	Furniture(std::wstring name, float width, float length, float height) : GameObject(name, width, length, height, true, ColliderType::Rectangle) {
		type = GameObjectType::Furniture;
		
		texture = getSingleTexture(name);
		sprite = sf::Sprite();
		sprite.setTexture(*texture->texture);
		sprite.setOrigin(texture->cx, texture->cy);

		inventory = nullptr;
		takeItTexture = getSingleTexture(L"GUI\\hand");
		takeItSprite = sf::Sprite();
		takeItSprite.setTexture(*takeItTexture->texture);
		takeItSprite.setOrigin(takeItTexture->cx, takeItTexture->cy);
		showHand = false;

		setPosition(position);
	}
	
	Furniture(GameObject* object) : GameObject(object) {
		type = GameObjectType::Furniture;
		
		texture = getSingleTexture(name);
		sprite = sf::Sprite();
		sprite.setTexture(*texture->texture);
		sprite.setOrigin(texture->cx, texture->cy);

		inventory = nullptr;
		
		takeItTexture = getSingleTexture(L"GUI\\hand");
		takeItSprite = sf::Sprite();
		takeItSprite.setTexture(*takeItTexture->texture);
		takeItSprite.setOrigin(takeItTexture->cx, takeItTexture->cy);
		showHand = false;

		setPosition(position);
	}

	virtual ~Furniture() {

	}

	virtual void setPosition(sf::Vector2f position) {
		GameObject::setPosition(position);

		sprite.setPosition(position);
		takeItSprite.setPosition(position.x, position.y - 50);
	}

	virtual void update() {

		
		showHand = false;

		if (player != nullptr) {

			if (inventory != nullptr) {

				// SHOW HAND
				float x1, y1, rx1, ry1;
				float x2, y2, rx2, ry2;
				
				x1 = player->position.x;
				y1 = player->position.y;
				rx1 = (player->colliders[0]->width / 2.0f + player->actionRange);
				ry1 = (player->colliders[0]->length + player->actionRange) / 2.0f;

				x2 = position.x;
				y2 = position.y;
				rx2 = colliders[0]->width;
				ry2 = colliders[0]->length;

				if (intersectionRectangleWithElipse(x2, y2, rx2, ry2, x1, y1, rx1, ry1)) {
					showHand = true;

					if (inventory->items.size() > 0)
						takeItSprite.setTexture(*getSingleTexture(L"GUI\\hand")->texture);
					else
						takeItSprite.setTexture(*getSingleTexture(L"GUI\\grey_hand")->texture);
				}

			}

		}

		// TO-DO
		if (player == nullptr) {
			if (inventory != nullptr) {
				if (isPointInRectangle(worldMousePosition.x, worldMousePosition.y, position.x, position.y, colliders[0]->width, colliders[0]->length)) {
					showHand = true;
				}
			}
		}
		//

	}

	virtual void drawColliders() {
		GameObject::drawColliders();
	}

	virtual void draw() {

		renderer->getTheCurrentFrame()->draw(sprite);

		if(showHand)
			renderer->getTheCurrentFrame()->draw(takeItSprite);
	}
};

std::vector < Furniture* > furnitures;

#endif