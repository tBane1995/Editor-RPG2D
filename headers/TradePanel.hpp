#ifndef TradePanel_hpp
#define TradePanel_hpp


enum class activeInventoryPanel { Left, Right };
activeInventoryPanel activePanel = activeInventoryPanel::Right;

InventoryPanel* inventoryLeft;
InventoryPanel* inventoryRight;

void updateTradePanel() {
	
	Item* item = nullptr;

	if (activePanel == activeInventoryPanel::Left) {
		inventoryLeft->update(cursor);
		inventoryRight->update(-1);

		if (inventoryLeft->inventory != nullptr )
			if(inventoryLeft->sortedItems.size() > 0 )
				if(cursor + inventoryLeft->scroll * itemsInRow < inventoryLeft->sortedItems.size())
					item = inventoryLeft->sortedItems[cursor + inventoryLeft->scroll * itemsInRow];
	}

	if (activePanel == activeInventoryPanel::Right) {
		inventoryLeft->update(-1);
		inventoryRight->update(cursor);

		if (inventoryRight->inventory != nullptr)
			if (inventoryRight->sortedItems.size() > 0)
				if (cursor + inventoryRight->scroll * itemsInRow < inventoryRight->sortedItems.size())
					item = inventoryRight->sortedItems[cursor + inventoryRight->scroll * itemsInRow];
	}
	
	drawItemStats = false;

	background = sf::Sprite();
	background.setTexture(*getSingleTexture(L"GUI\\infoPanel")->texture);
	background.setPosition(cam->position.x, cam->position.y + 275);
	background.setOrigin(300, 75);

	if (item != nullptr)
	{
		drawItemStats = true;

		itemSprite = sf::Sprite();
		itemSprite.setTexture(*item->texture->texture);
		itemSprite.setOrigin(32, 32);
		itemSprite.setScale(2, 2);
		itemSprite.setPosition(cam->position.x - 300 + 80, cam->position.y + 275);

		itemName = sf::Text();
		itemName.setCharacterSize(28);
		itemName.setFillColor(dialoguesColor);
		itemName.setFont(basicFont);
		itemName.setPosition(cam->position.x - 300 + 192, cam->position.y + 275 - 64);
		itemName.setString(getShortName(item->name));

		itemDescription = sf::Text();
		itemDescription.setCharacterSize(16);
		itemDescription.setFillColor(dialoguesColor);
		itemDescription.setFont(basicFont);
		itemDescription.setPosition(cam->position.x - 300 + 192, cam->position.y + 275 - 32);
		itemDescription.setString(getItemDescription(item));
	}

}

void drawTradePanel() {
	inventoryLeft->draw();
	inventoryRight->draw();
	
	window->draw(background);
	if (drawItemStats == true) {
		window->draw(itemSprite);
		window->draw(itemName);
		window->draw(itemDescription);
	}
}
#endif