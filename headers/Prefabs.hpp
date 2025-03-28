#ifndef Prefabs_hpp
#define Prefabs_hpp

std::vector < GameObject* > prefabs;

GameObject* getPrefab(string name) {
    for (auto& go : prefabs) {
        if (go->name == name)
            return go;
    }

    std::cout << "error - get Prefab - Prefab: \"" << name << "\" not exists\n";
    return nullptr;
}

void loadPrefabs() {

    prefabs.clear();

    // NATURES
    // name, radius, width, height
    prefabs.push_back(new Nature("natures/tree9", 50, 25, 185));
    prefabs.push_back(new Nature("natures/reed_1", 16, 8, 16));
    prefabs.push_back(new Nature("natures/reed_2", 16, 8, 16));
    prefabs.push_back(new Nature("natures/boulder_1", 90, 45, 65));
    prefabs.push_back(new Nature("natures/boulder_2", 90, 45, 65));
    prefabs.push_back(new Nature("natures/boulder_3", 90, 45, 57));
    prefabs.push_back(new Nature("natures/column_1", 50, 35, 57));
    prefabs.push_back(new Nature("natures/column_2", 50, 35, 57));
    prefabs.push_back(new Nature("natures/column_3", 50, 35, 57));
    prefabs.push_back(new Nature("natures/stone_altar", 50, 35, 57));
    prefabs.push_back(new Nature("natures/stone_platform", 90, 45, 65));
    prefabs.push_back(new Nature("natures/driftwood", 125, 35, 30));
    prefabs.push_back(new Nature("natures/rock_1", 32, 12, 10));
    prefabs.push_back(new Nature("natures/rock_2", 28, 12, 10));

    // OBJECTS
    prefabs.push_back(new Object("objects/palisade", 32, 32, 128, true));
    prefabs.push_back(new Object("objects/great_stone_gate", 128, 32, 128, false));  // TO-DO
    prefabs.push_back(new Object("objects/stone_wall", 16, 16, 64, true));
    prefabs.push_back(new Object("objects/great_stone_wall", 32, 32, 128, true));
    prefabs.push_back(new Object("objects/great_gate", 64, 32, 128, false));
    prefabs.push_back(new Object("objects/brazier", 48, 40, 40, true, ColliderType::Elipse));
    prefabs.push_back(new Object("objects/well", 72, 38, 60, true, ColliderType::Elipse));
    prefabs.push_back(new Object("objects/hunter_tent", 200, 70, 130, true));
    prefabs.push_back(new Object("objects/log_with_saw", 70, 20, 40, true));
    prefabs.push_back(new Object("objects/pile_of_wood", 114, 56, 64, true));
    prefabs.push_back(new Object("objects/stone_altar_1", 74, 56, 64, true));

    // FLAT OBJECTS
    prefabs.push_back(new FlatObject("flatObjects/path_1", 64, 32, 32));
    prefabs.push_back(new FlatObject("flatObjects/path_2", 64, 32, 32));
    prefabs.push_back(new FlatObject("flatObjects/stonepath_1", 64, 32, 32));
    prefabs.push_back(new FlatObject("flatObjects/stonepath_2", 64, 32, 32));
    prefabs.push_back(new FlatObject("flatObjects/sandspath_1", 64, 32, 32));
    prefabs.push_back(new FlatObject("flatObjects/sandspath_2", 64, 32, 32));

    prefabs.push_back(new FlatObject("flatObjects/herb_1", 16, 8, 16));
    prefabs.push_back(new FlatObject("flatObjects/herb_2", 16, 8, 16));


    prefabs.push_back(new FlatObject("flatObjects/small_rock_1", 16, 8, 16));
    prefabs.push_back(new FlatObject("flatObjects/small_rock_2", 16, 8, 16));
    prefabs.push_back(new FlatObject("flatObjects/small_rock_3", 16, 8, 16));
    prefabs.push_back(new FlatObject("flatObjects/small_rock_4", 16, 8, 16));
    prefabs.push_back(new FlatObject("flatObjects/small_sands_rock_1", 16, 8, 16));
    prefabs.push_back(new FlatObject("flatObjects/small_sands_rock_2", 16, 8, 16));
    prefabs.push_back(new FlatObject("flatObjects/small_sands_rock_3", 16, 8, 16));
    prefabs.push_back(new FlatObject("flatObjects/small_sands_rock_4", 16, 8, 16));

    // SMALL OBJECTS
    prefabs.push_back(new SmallObject("smallObjects/grass_1", 16, 8, 16));
    prefabs.push_back(new SmallObject("smallObjects/grass_2", 16, 8, 16));
    prefabs.push_back(new SmallObject("smallObjects/grass_3", 16, 8, 16));

    // FURNITURES - TO-DO - heights
    prefabs.push_back(new Furniture("furnitures/table", 60, 26, 36));
    prefabs.push_back(new Furniture("furnitures/table_alchemist", 60, 26, 36));
    prefabs.push_back(new Furniture("furnitures/table_alchemist_2", 60, 26, 36));
    prefabs.push_back(new Furniture("furnitures/table_herbalist", 60, 26, 36));
    prefabs.push_back(new Furniture("furnitures/table_herbalist_2", 60, 26, 36));
    prefabs.push_back(new Furniture("furnitures/bench", 60, 26, 36));
    prefabs.push_back(new Furniture("furnitures/chest", 60, 26, 36));
    prefabs.push_back(new Furniture("furnitures/wardrobe", 64, 32, 60));
    prefabs.push_back(new Furniture("furnitures/bookshelf", 64, 32, 60));
    prefabs.push_back(new Furniture("furnitures/furnace", 60, 26, 60));
    prefabs.push_back(new Furniture("furnitures/bed", 64, 32, 60));
    prefabs.push_back(new Furniture("furnitures/chair", 16, 16, 24));
    prefabs.push_back(new Furniture("furnitures/barrel", 16, 16, 24));
    prefabs.push_back(new Furniture("furnitures/shield_1", 16, 0, 64));
    prefabs.push_back(new Furniture("furnitures/shield_2", 16, 0, 64));
    prefabs.push_back(new Furniture("furnitures/shield_3", 16, 0, 64));
    prefabs.push_back(new Furniture("furnitures/lectern", 24, 16, 40));

    // WALLS
    Wall* wall = new Wall("walls/empty_wall", 32, 32, 32);
    prefabs.push_back(wall);

    prefabs.push_back(new Wall("walls/mud_wall", 32, 32, 32));
    prefabs.push_back(new Wall("walls/stone_wall", 32, 32, 32));
    prefabs.push_back(new Wall("walls/wooden_wall", 32, 32, 32));
    prefabs.push_back(new Wall("walls/brick_wall", 32, 32, 32));
    prefabs.push_back(new Wall("walls/mulch_wall", 32, 32, 32));

    prefabs.push_back(new Wall("walls/mud_wall_overgrown", 32, 32, 32));
    prefabs.push_back(new Wall("walls/stone_wall_overgrown", 32, 32, 32));
    prefabs.push_back(new Wall("walls/wooden_wall_overgrown", 32, 32, 32));
    prefabs.push_back(new Wall("walls/brick_wall_overgrown", 32, 32, 32));
    prefabs.push_back(new Wall("walls/mulch_wall_overgrown", 32, 32, 32));

    std::vector < std::string > walls_names;
    walls_names.push_back("walls/set_mud_wall");
    walls_names.push_back("walls/set_stone_wall");
    walls_names.push_back("walls/set_wooden_wall");
    walls_names.push_back("walls/set_brick_wall");
    walls_names.push_back("walls/set_mulch_wall");

    for (auto& texture : singleTextures) {
        for (auto& name : walls_names) {
            if (texture->name.find(name) != std::string::npos) {
                Wall* wall = new Wall(texture->name, 32, 32, 32);
                prefabs.push_back(wall);
                //cout << "created prefab: " << wall->name << "\n";
            }
        }
    }

    prefabs.push_back(new Object("fortifications/fortified_gate", 128, 32, 128, false));  // TO-DO

    std::vector <std::string > fortifications_names;
    fortifications_names.push_back("fortifications/fortified_wall");

    // TO-DO
    for (auto& texture : singleTextures) {
        for (auto& name : fortifications_names) {
            if (texture->name.find(name) != std::string::npos) {
                Wall* wall = new Wall(texture->name, 32, 32, 32);
                prefabs.push_back(wall);
                //cout << "created prefab: " << wall->name << "\n";
            }
        }
    }



    // DOORS
    prefabs.push_back(new Door("doors/wooden_door", 64, 16, 64, 12, 12));
    prefabs.push_back(new Door("doors/wooden_gate", 128, 32, 128, 16, 16));  // TO-DO

    // ITEMS
    for (auto& i : items) {
        prefabs.push_back(new ItemOnMap(i, 0, 0));
    }

    // CHARACTERS
    // name, bodySet

    Character* character = nullptr;

    character = new Character("characters/jack", "sets/body/man-blackhaired");
    character->dialogue = getDialogue(1);
    character->armor = getItem("items/skin jacket");
    character->pants = getItem("items/wool pants");
    character->helmet = getItem("items/wool helmet");
    character->rightHand = getItem("items/sword");
    character->leftHand = getItem("items/shield");
    prefabs.push_back(character);

    character = new Character("characters/john", "sets/body/boy-brownhaired");
    character->armor = getItem("items/wool shirt");
    character->pants = getItem("items/wool pants");
    character->helmet = getItem("items/wool helmet");
    prefabs.push_back(character);

    character = new Character("characters/peter", "sets/body/boy-brownhaired");
    character->armor = getItem("items/wool shirt");
    character->pants = getItem("items/wool pants");
    character->helmet = getItem("items/wool helmet");
    prefabs.push_back(character);

    character = new Character("characters/pit", "sets/body/boy-brownhaired");
    character->dialogue = getDialogue(5);
    character->armor = getItem("items/wool shirt");
    character->pants = getItem("items/wool pants");
    character->helmet = getItem("items/wool helmet");
    prefabs.push_back(character);


    // MONSTERS TO-DO - heights

    Monster* dziobak = new Monster("monsters/dziobak", 72, 36, 50, 10);
    dziobak->HP = 40;
    dziobak->HP_FULL = 40;
    dziobak->MP = 10;
    dziobak->MP_FULL = 10;
    dziobak->STRENGTH = 2;
    dziobak->DEXTERITY = 2;
    dziobak->INTELLIGENCE = 1;
    prefabs.push_back(dziobak);

    Monster* goblin = new Monster("monsters/goblin", 32, 16, 50, 20);
    goblin->HP = 80;
    goblin->HP_FULL = 80;
    goblin->MP = 10;
    goblin->MP_FULL = 10;
    goblin->STRENGTH = 8;
    goblin->DEXTERITY = 4;
    goblin->INTELLIGENCE = 2;
    prefabs.push_back(goblin);

    Monster* wilczur = new Monster("monsters/wilczur", 70, 35, 60, 50);
    wilczur->HP = 120;
    wilczur->HP_FULL = 120;
    wilczur->MP = 10;
    wilczur->MP_FULL = 10;
    wilczur->STRENGTH = 12;
    wilczur->DEXTERITY = 6;
    wilczur->INTELLIGENCE = 3;
    prefabs.push_back(wilczur);

    Monster* jaszczur = new Monster("monsters/jaszczur", 70, 35, 50, 80);
    jaszczur->HP = 160;
    jaszczur->HP_FULL = 160;
    jaszczur->MP = 10;
    jaszczur->MP_FULL = 10;
    jaszczur->STRENGTH = 16;
    jaszczur->DEXTERITY = 8;
    jaszczur->INTELLIGENCE = 4;
    prefabs.push_back(jaszczur);

    Monster* niedzwiedz = new Monster("monsters/niedzwiedz", 70, 35, 75, 80);
    niedzwiedz->HP = 160;
    niedzwiedz->HP_FULL = 160;
    niedzwiedz->MP = 10;
    niedzwiedz->MP_FULL = 10;
    niedzwiedz->STRENGTH = 16;
    niedzwiedz->DEXTERITY = 8;
    niedzwiedz->INTELLIGENCE = 4;
    prefabs.push_back(niedzwiedz);

    Monster* szpon = new Monster("monsters/szpon", 66, 32, 75, 100);
    szpon->HP = 200;
    szpon->HP_FULL = 200;
    szpon->MP = 10;
    szpon->MP_FULL = 10;
    szpon->STRENGTH = 20;
    szpon->DEXTERITY = 10;
    szpon->INTELLIGENCE = 5;
    prefabs.push_back(szpon);

    Monster* kolcorozec = new Monster("monsters/kolcorozec", 70, 35, 70, 140);
    kolcorozec->HP = 240;
    kolcorozec->HP_FULL = 240;
    kolcorozec->MP = 10;
    kolcorozec->MP_FULL = 10;
    kolcorozec->STRENGTH = 24;
    kolcorozec->DEXTERITY = 12;
    kolcorozec->INTELLIGENCE = 6;
    prefabs.push_back(kolcorozec);

    Monster* golem = new Monster("monsters/golem", 90, 60, 80, 180);
    golem->HP = 280;
    golem->HP_FULL = 280;
    golem->MP = 10;
    golem->MP_FULL = 10;
    golem->STRENGTH = 28;
    golem->DEXTERITY = 14;
    golem->INTELLIGENCE = 7;
    prefabs.push_back(golem);

    Monster* troll = new Monster("monsters/troll", 90, 60, 85, 240);
    troll->HP = 320;
    troll->HP_FULL = 320;
    troll->MP = 10;
    troll->MP_FULL = 10;
    troll->STRENGTH = 32;
    troll->DEXTERITY = 16;
    troll->INTELLIGENCE = 8;
    prefabs.push_back(troll);

    Monster* bies = new Monster("monsters/bies", 90, 60, 85, 300);
    bies->HP = 360;
    bies->HP_FULL = 360;
    bies->MP = 10;
    bies->MP_FULL = 10;
    bies->STRENGTH = 36;
    bies->DEXTERITY = 18;
    bies->INTELLIGENCE = 9;
    prefabs.push_back(bies);
}




#endif
