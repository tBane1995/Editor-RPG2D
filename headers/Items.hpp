#ifndef Items_hpp
#define Items_hpp

// TO-DO
enum class Attribute { ATTACK, DEFEND, HP, MP, HP_max, MP_max, STRENGTH, DEXTERITY, INTELLIGENCE };
enum class ItemType { herb, potion, food, weapon, bow, helmet, armor, pants, shield, other };

class Item {
public:
	std::wstring name;
	SingleTexture* texture;
	ItemType type;
	std::map < Attribute, int > attributes;		// TO-DO
	std::wstring description;

	Item(std::wstring name, ItemType type, std::wstring description) {

		this->name = name;
		this->type = type;
		this->description = description;
		this->texture = getSingleTexture(name);
	}
};

std::vector < Item* > items;

Item* getItem(std::wstring location) {
	for (auto& item : items) {
		if (item->name == location)
			return item;
	}

	return nullptr;
}

wstring getItemDescription(Item* item) {
	
	wstring description = item->description + L"\n\n";

	if (item->attributes[Attribute::ATTACK])
		description += L"ATTACK " + to_wstring(item->attributes[Attribute::ATTACK]) + L"\n";

	if (item->attributes[Attribute::DEFEND])
		description += L"DEFEND " + to_wstring(item->attributes[Attribute::DEFEND]) + L"\n";

	if (item->attributes[Attribute::STRENGTH])
		description += L"STRENGTH " + to_wstring(item->attributes[Attribute::STRENGTH]) + L"\n";

	if (item->attributes[Attribute::DEXTERITY])
		description += L"DEXTERITY " + to_wstring(item->attributes[Attribute::DEXTERITY]) + L"\n";

	if (item->attributes[Attribute::INTELLIGENCE])
		description += L"INTELLIGENCE " + to_wstring(item->attributes[Attribute::INTELLIGENCE]) + L"\n";

	if (item->attributes[Attribute::HP])
		description += L"HP " + to_wstring(item->attributes[Attribute::HP]) + L"\n";

	if (item->attributes[Attribute::HP_max])
		description += L"HP_max " + to_wstring(item->attributes[Attribute::HP_max]) + L"\n";

	if (item->attributes[Attribute::MP])
		description += L"MP " + to_wstring(item->attributes[Attribute::MP]) + L"\n";

	if (item->attributes[Attribute::MP_max])
		description += L"MP_max " + to_wstring(item->attributes[Attribute::MP_max]) + L"\n";

	return description;
}

class ItemOnMap : public GameObject {
public:
	Item* item;
	short count;
	bool collected;

	ItemOnMap(Item* item, short count = 1) : GameObject(item->name, 16, 8, 32, true, ColliderType::Elipse) {
		type = GameObjectType::ItemOnMap;

		this->item = item;
		this->count = count;
		collected = false;

		sprite.setScale(0.75f, 0.75f);
	}

	ItemOnMap(GameObject* object, short count = 1) : GameObject(object) {
		type = GameObjectType::ItemOnMap;

		this->item = getItem(object->name);
		this->count = count;
		collected = false;

		sprite.setScale(0.75f, 0.75f);
	}

	virtual ~ItemOnMap() { }

};

std::vector < ItemOnMap* > itemsOnMap;

void loadItems() {

	items.clear();
	Item* item;
	
	// BOWS
	item = new Item(L"items\\bow", ItemType::bow, L"normal bow");
	item->attributes[Attribute::ATTACK] = 50;
	items.push_back(item);

	// WEAPONS

	item = new Item(L"items\\axe", ItemType::weapon, L"do rąbania głów");
	item->attributes[Attribute::ATTACK] = 50;
	items.push_back(item);

	item = new Item(L"items\\iron club", ItemType::weapon, L"żelazna pałka");
	item->attributes[Attribute::ATTACK] = 45;
	items.push_back(item);
	
	item = new Item(L"items\\wide blade", ItemType::weapon, L"szerokie ostrze");
	item->attributes[Attribute::ATTACK] = 40;
	items.push_back(item);

	item = new Item(L"items\\long sword", ItemType::weapon, L"długi miecz");
	item->attributes[Attribute::ATTACK] = 35;
	items.push_back(item);
	
	item = new Item(L"items\\curved sword", ItemType::weapon, L"zakrzywiony miecz");
	item->attributes[Attribute::ATTACK] = 30;
	items.push_back(item);

	item = new Item(L"items\\club", ItemType::weapon, L"pałka");
	item->attributes[Attribute::ATTACK] = 20;
	items.push_back(item);

	item = new Item(L"items\\stone hammer", ItemType::weapon, L"prymitywna broń");
	item->attributes[Attribute::ATTACK] = 15;
	items.push_back(item);

	item = new Item(L"items\\gladius", ItemType::weapon, L"ceniony przez wojowników");
	item->attributes[Attribute::ATTACK] = 15;
	items.push_back(item);

	item = new Item(L"items\\sword", ItemType::weapon, L"miecz");
	item->attributes[Attribute::ATTACK] = 10;
	items.push_back(item);

	item = new Item(L"items\\dagger", ItemType::weapon, L"zdradziecka broń");
	item->attributes[Attribute::ATTACK] = 8;
	items.push_back(item);

	item = new Item(L"items\\hatchet", ItemType::weapon, L"zazwyczaj służy do rąbania drewna");
	item->attributes[Attribute::ATTACK] = 5;
	items.push_back(item);

	item = new Item(L"items\\knife", ItemType::weapon, L"zwykly nóż");
	item->attributes[Attribute::ATTACK] = 3;
	items.push_back(item);


	item = new Item(L"items\\wooden club", ItemType::weapon, L"drewniana pałka");
	item->attributes[Attribute::ATTACK] = 2;
	items.push_back(item);

	// SHIELDS

	item = new Item(L"items\\shield", ItemType::shield, L"zwyczajna tarcza");
	item->attributes[Attribute::DEFEND] = 2;
	items.push_back(item);

	// HELMETS

	item = new Item(L"items\\skin helmet", ItemType::helmet, L"skórzany helm");
	item->attributes[Attribute::DEFEND] = 2;
	items.push_back(item);

	item = new Item(L"items\\wool hat", ItemType::helmet, L"wełniana czapka");
	item->attributes[Attribute::DEFEND] = 1;
	items.push_back(item);
	
	// ARMORS

	item = new Item(L"items\\plate armor", ItemType::armor, L"zbroja płytowa");
	item->attributes[Attribute::DEFEND] = 20;
	items.push_back(item);

	item = new Item(L"items\\chain mail", ItemType::armor, L"kolczuga");
	item->attributes[Attribute::DEFEND] = 10;
	items.push_back(item);

	item = new Item(L"items\\skin jacket", ItemType::armor, L"skórzana kurtka");
	item->attributes[Attribute::DEFEND] = 5;
	items.push_back(item);

	item = new Item(L"items\\wool shirt", ItemType::armor, L"wełniana koszula");
	item->attributes[Attribute::DEFEND] = 2;
	items.push_back(item);
	
	item = new Item(L"items\\torn shirt", ItemType::armor, L"podarta koszula");
	item->attributes[Attribute::DEFEND] = 1;
	items.push_back(item);

	item = new Item(L"items\\mage's robe", ItemType::armor, L"szata maga");
	item->attributes[Attribute::DEFEND] = 5;
	items.push_back(item);

	item = new Item(L"items\\gray apron", ItemType::armor, L"szary fartuch");
	item->attributes[Attribute::DEFEND] = 5;
	items.push_back(item);

	// PANTS

	item = new Item(L"items\\chain mail pants", ItemType::pants, L"nogawice kolcze");
	item->attributes[Attribute::DEFEND] = 10;
	items.push_back(item);

	item = new Item(L"items\\skin pants", ItemType::pants, L"skórzane spodnie");
	item->attributes[Attribute::DEFEND] = 5;
	items.push_back(item);

	item = new Item(L"items\\wool pants", ItemType::pants, L"wełniane spodnie");
	item->attributes[Attribute::DEFEND] = 2;
	items.push_back(item);


	// HERBS
	
	item = new Item(L"items\\health plant", ItemType::herb, L"roślina życia");
	item->attributes[Attribute::HP] = 50;
	items.push_back(item);

	item = new Item(L"items\\mana plant", ItemType::herb, L"roślina many");
	item->attributes[Attribute::MP] = 50;
	items.push_back(item);

	item = new Item(L"items\\health root", ItemType::herb, L"korzeń życia");
	item->attributes[Attribute::HP] = 25;
	items.push_back(item);

	item = new Item(L"items\\health herb", ItemType::herb, L"zioło życia");
	item->attributes[Attribute::HP] = 15;
	items.push_back(item);

	item = new Item(L"items\\mushroom", ItemType::herb, L"grzyb");
	item->attributes[Attribute::HP] = 5;
	items.push_back(item);

	// POTIONS
	item = new Item(L"items\\potion", ItemType::potion, L"mikstura");
	item->attributes[Attribute::HP] = 30;
	items.push_back(item);

	// FOOD
	item = new Item(L"items\\roasted meat", ItemType::food, L"pieczone mięso");
	item->attributes[Attribute::HP] = 20;
	items.push_back(item);

	item = new Item(L"items\\raw meat", ItemType::food, L"surowe mięso");
	item->attributes[Attribute::HP] = 10;
	items.push_back(item);

	// OTHERS
	item = new Item(L"items\\bone", ItemType::other, L"kość");
	items.push_back(item);

	item = new Item(L"items\\tooth", ItemType::other, L"kieł zwierza");
	items.push_back(item);

	item = new Item(L"items\\spike", ItemType::other, L"kolec zwierza");
	items.push_back(item);

	item = new Item(L"items\\wolf skin", ItemType::other, L"skóra wilka");
	items.push_back(item);

}


class Inventory {
public:
	std::vector < Item* > items;
	std::vector < short > counts;
	short id;

	Inventory() {

		this->id = -1;

		items.clear();
		counts.clear();
	}

	Inventory(short id) {

		this->id = id;

		items.clear();
		counts.clear();
	}

	void addItem(std::wstring location, short count = 1) {

		for (short i = 0; i < items.size(); i++)
			if (items[i]->name == location) {
				counts[i] += count;
				return;
			}

		items.push_back(getItem(location));
		counts.push_back(count);
	}

	void addItem(Item* item, short count = 1) {

		bool addedItem = false;

		for (short i = 0; i < items.size(); i++)
			if (items[i] == item) {
				counts[i] += count;
				return;
			}

		items.push_back(item);
		counts.push_back(count);
	}

	bool hasItemsInInventory(std::wstring location, short count=1) {
		
		for (short i = 0; i < items.size(); i++)
			if (items[i]->name == location) {
				
				if (counts[i] >= count)
					return true;
				else
					return false;
			}

		return false;
	}

	void removeItem(std::wstring name, short count = 1) {
		for (short i = 0; i < items.size(); i++)
			if (items[i]->name == name) {
				counts[i] -= count;
			}

		// delete zeros (count)
		std::vector < Item* > newItems;
		std::vector < short > newCounts;

		for (short i = 0; i < items.size(); i++) {
			if (counts[i] > 0) {
				newItems.push_back(items[i]);
				newCounts.push_back(counts[i]);
			}
				
		}

		items = newItems;
		counts = newCounts;
	}

	void removeItem(Item* item, short count = 1) {
		for (short i = 0; i < items.size(); i++)
			if (items[i] == item) {
				counts[i] -= count;
			}

		// delete zeros (count)
		std::vector < Item* > newItems;
		std::vector < short > newCounts;

		for (short i = 0; i < items.size(); i++) {
			if (counts[i] > 0) {
				newItems.push_back(items[i]);
				newCounts.push_back(counts[i]);
			}

		}

		items = newItems;
		counts = newCounts;
	}


};

std::vector < Inventory* > inventories;

void clearInventories() {
	for (auto& inventory : inventories)
		delete inventory;

	inventories.clear();
}

void loadInventories() {
	inventories.clear();

	Inventory* inventory;

	inventory = new Inventory(0);
	inventory->addItem(L"items\\roasted meat", 3);
	inventories.push_back(inventory);

	inventory = new Inventory(1);
	inventory->addItem(L"items\\wooden club");
	inventory->addItem(L"items\\wool shirt");
	inventory->addItem(L"items\\wool pants");				
	inventories.push_back(inventory);

	
}

Inventory* getInventory(short id) {

	for (auto& i : inventories)
		if (i->id == id)
			return i;


	cout << "Inventory id=" << id << " not exists!\n";
	return nullptr;

}

class InventoryOnMap : public GameObject {
public:
	bool collected;
	Inventory* inventory;

	InventoryOnMap(Inventory* inventory) : GameObject(L"inventory", 16, 8, 16, true, ColliderType::Elipse) {
		type = GameObjectType::InventoryOnMap;

		sprite.setScale(0.75f, 0.75f);
		collected = false;
		this->inventory = inventory;
	}
	
	~InventoryOnMap() { }
};

std::vector < InventoryOnMap* > inventoriesOnMap;

void transferItem(Item* item, Inventory* &from, Inventory* &to) {
	
	from->removeItem(item);
	to->addItem(item);
}

#endif 
