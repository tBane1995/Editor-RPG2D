#ifndef InventoryPanel_hpp
#define InventoryPanel_hpp

short itemsInRow = 6;
short itemsInCol = 4;
short slotSide = 80;
short cursor = 0;

class InventoryPanel {
public:

	Inventory* inventory;
	sf::Vector2f position;
	short scroll;

	std::vector < Item* > sortedItems;
	std::vector < short > sortedItemsCounts;

	std::vector < sf::Sprite > slotsSprites;
	std::vector <sf::Sprite > itemsSprites;
	std::vector < sf::Text > counts;
	bool drawSelector;
	sf::Sprite selector;

	InventoryPanel(Inventory* inventory, float position_x = 0, float position_y = 0) {
		this->inventory = inventory;
		this->position.x = position_x;
		this->position.y = position_y;
		scroll = 0;

		// SLOTS
		for (int i = 0; i < itemsInRow * itemsInCol; i++) {
			slotsSprites.emplace_back();
			float x = cam->position.x + position.x - (itemsInRow / 2 - i % itemsInRow) * slotSide + slotSide / 2;
			float y = cam->position.y + position.y - (itemsInCol / 2 - i / itemsInRow) * slotSide + slotSide / 2;
			slotsSprites[i].setOrigin(slotSide / 2, slotSide / 2);
			slotsSprites[i].setPosition(x, y);
			slotsSprites[i].setTexture(*getSingleTexture(L"GUI\\slot1")->texture);
		}

		// SELECTOR
		selector = sf::Sprite();
		selector.setTexture(*getSingleTexture(L"GUI\\selector")->texture);
		selector.setOrigin(slotSide / 2, slotSide / 2);

		drawSelector = false;
	}

	void update(int cursor) {
		
		// SORT THE ITEMS

		sortedItems.clear();
		sortedItemsCounts.clear();

		for (auto& item : items) {
			// create sorted items list
			sortedItems.push_back(item);
			sortedItemsCounts.push_back(0);
		}

		for (short i = 0; i < inventory->items.size(); i++)
			for (short j = 0; j < sortedItems.size(); j++) {
				// adding items to sorted items list
				if (inventory->items[i] == sortedItems[j])
					sortedItemsCounts[j] += inventory->counts[i];

			}


		std::vector < Item* > s;
		std::vector < short > c;

		s.clear();
		c.clear();

		for (short i = 0; i < sortedItems.size(); i++) {
			// delete items who count is zero
			if (sortedItemsCounts[i] > 0) {
				s.push_back(sortedItems[i]);
				c.push_back(sortedItemsCounts[i]);
			}
		}

		sortedItems = s;
		sortedItemsCounts = c;

		// SLOTS SPRITES
		for (short i = 0; i < itemsInRow * itemsInCol; i++) {
			float x = cam->position.x + position.x - (itemsInRow / 2 - i % itemsInRow) * slotSide + slotSide / 2;
			float y = cam->position.y + position.y - (itemsInCol / 2 - i / itemsInRow) * slotSide + slotSide / 2;
			slotsSprites[i].setPosition(x, y);
			slotsSprites[i].setColor(sf::Color::White);
		}

		// ITEMS SPRITES
		itemsSprites.clear();
		counts.clear();

		if (inventory != nullptr) {
			for (short i = 0; i < itemsInRow * itemsInCol; i++) {

				if (i+scroll*itemsInRow < sortedItems.size()) {

					Item* item = sortedItems[i + scroll * itemsInRow];
					
					if(inventory == player->bag)
						if (item == player->helmet || item == player->armor || item == player->pants || item==player->rightHand || item == player->leftHand)
							slotsSprites[i].setColor(sf::Color::Red);

					itemsSprites.emplace_back();

					float x = cam->position.x + position.x - (itemsInRow / 2 - i % itemsInRow) * slotSide + slotSide / 2;
					float y = cam->position.y + position.y - (itemsInCol / 2 - i / itemsInRow) * slotSide + slotSide / 2;

					float twidth = item->texture->texture->getSize().x;
					float theight = item->texture->texture->getSize().y;
					
					itemsSprites[i].setTexture(*item->texture->texture);
					itemsSprites[i].setOrigin(twidth / 2, theight / 2);
					itemsSprites[i].setPosition(x, y);
					itemsSprites[i].setScale(64.0f / twidth, 64.0f / theight);

					counts.emplace_back(to_string(sortedItemsCounts[i+scroll*itemsInRow]), basicFont, 16);
					counts[i].setPosition(x, y);
					
					short width = counts[i].getLocalBounds().width;
					short height = counts[i].getLocalBounds().height;
					
					counts[i].setOrigin(width / 2, height / 2);
					counts[i].setPosition(x - width / 2 + 24, y - height / 2 + 24);
					counts[i].setFillColor(dialoguesColor);

				}
			}
		}

		// SELECTOR
		if (cursor != -1) {

			drawSelector = true;

			float x = cam->position.x + position.x - (itemsInRow / 2 - cursor % itemsInRow) * slotSide + slotSide / 2;
			float y = cam->position.y + position.y - (itemsInCol / 2 - cursor / itemsInRow) * slotSide + slotSide / 2;

			selector.setPosition(x, y);
		}
		else {
			drawSelector = false;
		}
	}

	void draw() {
		for (auto& slot : slotsSprites)
			window->draw(slot);

		for (auto& item : itemsSprites)
			window->draw(item);

		for (auto& count : counts)
			window->draw(count);

		if (drawSelector)
			window->draw(selector);
	}
};

InventoryPanel* inventory;

sf::Sprite background;
sf::Sprite itemSprite;
sf::Text itemName;
sf::Text itemDescription;
bool drawItemStats;

void updateInventoryPanel() {

	inventory->update(cursor);
	
	drawItemStats = false;
	
	background = sf::Sprite();
	background.setTexture(*getSingleTexture(L"GUI\\infoPanel")->texture);
	background.setPosition(cam->position.x, cam->position.y + 275);
	background.setOrigin(300,75);

	Item* item = nullptr;
	short itemIndex = cursor + inventory->scroll * itemsInRow;
	if (itemIndex < inventory->sortedItems.size()) {
		item = inventory->sortedItems[itemIndex];
	}
		

	if (item!=nullptr)
	{
		drawItemStats = true;
		itemSprite = sf::Sprite();
		itemSprite.setTexture(*item->texture->texture);
		itemSprite.setOrigin(32, 32);
		itemSprite.setScale(2, 2);
		itemSprite.setPosition(cam->position.x-300+80, cam->position.y+275);

		itemName = sf::Text();
		itemName.setCharacterSize(28);
		itemName.setFillColor(dialoguesColor);
		itemName.setFont(basicFont);
		itemName.setPosition(cam->position.x-300 + 192, cam->position.y+275-64);
		itemName.setString(getShortName(item->name));

		itemDescription = sf::Text();
		itemDescription.setCharacterSize(16);
		itemDescription.setFillColor(dialoguesColor);
		itemDescription.setFont(basicFont);
		itemDescription.setPosition(cam->position.x - 300 + 192, cam->position.y + 275 - 32);
		itemDescription.setString(getItemDescription(item));
	}
	
}

void drawInventoryPanel() {
	
	inventory->draw();
	window->draw(background);
	if (drawItemStats == true){
		window->draw(itemSprite);
		window->draw(itemName);
		window->draw(itemDescription);
	}
}

void useItem() {
    
	if (inventory == nullptr)
		return;

	if (inventory->inventory == nullptr)
		return;

	if (cursor+inventory->scroll*itemsInRow >= inventory->inventory->items.size())
		return;

	Item* item = inventory->sortedItems[cursor+inventory->scroll*itemsInRow];

    if (item->type == ItemType::herb || item->type == ItemType::potion || item->type == ItemType::food) {
        player->heal(item->attributes[Attribute::HP]);
		inventory->inventory->removeItem(item);
    }

    if (item->type == ItemType::helmet) {

        if (player->helmet == item)
            player->helmet = nullptr;
        else
            player->helmet = item;
        
        player->loadHelmet();
    }

    if (item->type == ItemType::armor) {
        
        if (player->armor == item)
            player->armor = nullptr;
        else
        player->armor = item;
        
        player->loadArmor();
    }

    if (item->type == ItemType::pants) {

        if (player->pants == item)
            player->pants = nullptr;
        else
            player->pants = item;
        
        player->loadPants();
    }

	if (item->type == ItemType::weapon) {

		if (player->rightHand == item)
			player->rightHand = nullptr;
		else
			player->rightHand = item;

		player->loadRightHand();
	}

	if (item->type == ItemType::shield) {

		if (player->leftHand == item)
			player->leftHand = nullptr;
		else
			player->leftHand = item;

		player->loadLeftHand();
	}

    
}


#endif