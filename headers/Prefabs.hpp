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

uint32_t getPrefabID(string name) {

    uint32_t id = 0;

    for (auto& go : prefabs) {
        if (go->name == name)
            return id;
        id += 1;
    }

    std::cout << "error - get Prefab - Prefab: \"" << name << "\" not exists\n";
    return UINT32_MAX;
}

void loadPrefabs() {

    prefabs.clear();

    // NATURES
    // name, radius, width, height
    prefabs.push_back(new Nature("natures\\tree9", 50, 25, 185));
    prefabs.push_back(new Nature("natures\\bush_1", 52, 26, 40));
    prefabs.push_back(new Nature("natures\\stump_1", 56, 26, 36));
    prefabs.push_back(new Nature("natures\\reed_1", 16, 8, 16));
    prefabs.push_back(new Nature("natures\\reed_2", 16, 8, 16));
    prefabs.push_back(new Nature("natures\\boulder_1", 90, 45, 65));
    prefabs.push_back(new Nature("natures\\boulder_2", 90, 45, 65));
    prefabs.push_back(new Nature("natures\\boulder_3", 90, 45, 57));

    prefabs.push_back(new Nature("natures\\column_2", 50, 35, 57));
    prefabs.push_back(new Nature("natures\\column_3", 50, 35, 57));
    prefabs.push_back(new Nature("natures\\stone_altar", 50, 35, 57));
    prefabs.push_back(new Nature("natures\\stone_platform", 90, 45, 65));
    prefabs.push_back(new Nature("natures\\driftwood", 125, 35, 30));
    prefabs.push_back(new Nature("natures\\rock_1", 32, 12, 10));
    prefabs.push_back(new Nature("natures\\rock_2", 28, 12, 10));

    // OBJECTS
    prefabs.push_back(new Object("objects\\palisade_1", 32, 32, 128, true));
    prefabs.push_back(new Object("objects\\palisade_2", 32, 32, 128, true));
    prefabs.push_back(new Object("objects\\stone_wall", 16, 16, 64, true));
    prefabs.push_back(new Object("objects\\great_stone_wall", 32, 32, 128, true));
    prefabs.push_back(new Object("objects\\brazier", 48, 40, 40, true, ColliderType::Elipse));
    prefabs.push_back(new Object("objects\\well", 72, 38, 60, true, ColliderType::Elipse));
    prefabs.push_back(new Object("objects\\hunter_tent", 200, 70, 130, true));
    prefabs.push_back(new Object("objects\\log_with_saw", 70, 20, 40, true));
    prefabs.push_back(new Object("objects\\pile_of_wood_1", 114, 56, 64, true));
    prefabs.push_back(new Object("objects\\pile_of_wood_2", 114, 56, 64, true));
    prefabs.push_back(new Object("objects\\stone_altar_1", 74, 56, 64, true));

    prefabs.push_back(new Object("objects\\wooden_stake_1", 26, 16, 32, true, ColliderType::Elipse));


    // HIGHLANDS
    for (auto& texture : singleTextures) {
        if (texture->name.find("highlands\\low_highlands") != std::string::npos) {
            Object* ob = new Object(texture->name, 64, 64, 64, true);
            prefabs.push_back(ob);
            //cout << "created prefab: " << ob->name << "\\n";
        }
    }

    for (auto& texture : singleTextures) {
        if (texture->name.find("highlands\\high_highlands") != std::string::npos) {
            Object* ob = new Object(texture->name, 64, 64, 64, true);
            prefabs.push_back(ob);
            //cout << "created prefab: " << ob->name << "\\n";
        }
    }

    // FLAT OBJECTS
    prefabs.push_back(new FlatObject("flatObjects\\path_1", 64, 32, 32));
    prefabs.push_back(new FlatObject("flatObjects\\path_2", 64, 32, 32));
    prefabs.push_back(new FlatObject("flatObjects\\stonepath_1", 64, 32, 32));
    prefabs.push_back(new FlatObject("flatObjects\\stonepath_2", 64, 32, 32));
    prefabs.push_back(new FlatObject("flatObjects\\sandspath_1", 64, 32, 32));
    prefabs.push_back(new FlatObject("flatObjects\\sandspath_2", 64, 32, 32));

    prefabs.push_back(new FlatObject("flatObjects\\herb_1", 16, 8, 16));
    prefabs.push_back(new FlatObject("flatObjects\\herb_2", 16, 8, 16));


    prefabs.push_back(new FlatObject("flatObjects\\small_rock_1", 16, 8, 16));
    prefabs.push_back(new FlatObject("flatObjects\\small_rock_2", 16, 8, 16));
    prefabs.push_back(new FlatObject("flatObjects\\small_rock_3", 16, 8, 16));
    prefabs.push_back(new FlatObject("flatObjects\\small_rock_4", 16, 8, 16));
    prefabs.push_back(new FlatObject("flatObjects\\small_sands_rock_1", 16, 8, 16));
    prefabs.push_back(new FlatObject("flatObjects\\small_sands_rock_2", 16, 8, 16));
    prefabs.push_back(new FlatObject("flatObjects\\small_sands_rock_3", 16, 8, 16));
    prefabs.push_back(new FlatObject("flatObjects\\small_sands_rock_4", 16, 8, 16));

    // SMALL OBJECTS
    prefabs.push_back(new SmallObject("smallObjects\\grass_1", 16, 8, 16));
    prefabs.push_back(new SmallObject("smallObjects\\grass_2", 16, 8, 16));
    prefabs.push_back(new SmallObject("smallObjects\\grass_3", 16, 8, 16));

    // FURNITURES - TO-DO - heights
    prefabs.push_back(new Furniture("furnitures\\table", 60, 26, 36));
    prefabs.push_back(new Furniture("furnitures\\table_alchemist", 60, 26, 36));
    prefabs.push_back(new Furniture("furnitures\\table_alchemist_2", 60, 26, 36));
    prefabs.push_back(new Furniture("furnitures\\table_herbalist", 60, 26, 36));
    prefabs.push_back(new Furniture("furnitures\\table_herbalist_2", 60, 26, 36));
    prefabs.push_back(new Furniture("furnitures\\bench", 60, 26, 36));
    prefabs.push_back(new Furniture("furnitures\\chest", 60, 26, 36));
    prefabs.push_back(new Furniture("furnitures\\wardrobe", 64, 32, 60));
    prefabs.push_back(new Furniture("furnitures\\bookshelf", 64, 32, 60));
    prefabs.push_back(new Furniture("furnitures\\bookshelf_2", 64, 32, 60));
    prefabs.push_back(new Furniture("furnitures\\furnace", 60, 26, 60));
    prefabs.push_back(new Furniture("furnitures\\bed", 64, 32, 60));
    prefabs.push_back(new Furniture("furnitures\\chair", 16, 16, 24));
    prefabs.push_back(new Furniture("furnitures\\barrel", 16, 16, 24));
    prefabs.push_back(new Furniture("furnitures\\shield_1", 16, 0, 64));
    prefabs.push_back(new Furniture("furnitures\\shield_2", 16, 0, 64));
    prefabs.push_back(new Furniture("furnitures\\shield_3", 16, 0, 64));
    prefabs.push_back(new Furniture("furnitures\\lectern", 24, 16, 40));

    // WALLS
    Wall* wall = new Wall("walls\\empty_wall", 32, 32, 32);
    prefabs.push_back(wall);

    prefabs.push_back(new Wall("walls\\mud_wall", 32, 32, 32));
    prefabs.push_back(new Wall("walls\\stone_wall", 32, 32, 32));
    prefabs.push_back(new Wall("walls\\wooden_wall", 32, 32, 32));
    prefabs.push_back(new Wall("walls\\brick_wall", 32, 32, 32));
    prefabs.push_back(new Wall("walls\\mulch_wall", 32, 32, 32));

    prefabs.push_back(new Wall("walls\\mud_wall_overgrown", 32, 32, 32));
    prefabs.push_back(new Wall("walls\\stone_wall_overgrown", 32, 32, 32));
    prefabs.push_back(new Wall("walls\\wooden_wall_overgrown", 32, 32, 32));
    prefabs.push_back(new Wall("walls\\brick_wall_overgrown", 32, 32, 32));
    prefabs.push_back(new Wall("walls\\mulch_wall_overgrown", 32, 32, 32));

    std::vector < std::string > walls_names;
    walls_names.push_back("walls\\set_mud_wall");
    walls_names.push_back("walls\\set_stone_wall");
    walls_names.push_back("walls\\set_wooden_wall");
    walls_names.push_back("walls\\set_brick_wall");
    walls_names.push_back("walls\\set_mulch_wall");

    for (auto& texture : singleTextures) {
        for (auto& name : walls_names) {
            if (texture->name.find(name) != std::string::npos) {
                Wall* wall = new Wall(texture->name, 32, 32, 32);
                prefabs.push_back(wall);
                //cout << "created prefab: " << wall->name << "\\n";
            }
        }
    }


    // DOORS
    prefabs.push_back(new Door("doors\\wooden_door", 64, 16, 64, 12, 12));
    prefabs.push_back(new Door("doors\\wooden_gate", 128, 32, 128, 16, 16));
    prefabs.push_back(new Door("doors\\great_stone_gate", 128, 32, 128, 16, 16));

    // ITEMS
    for (auto& i : items) {
        prefabs.push_back(new ItemOnMap(i));
    }

    // CHARACTERS
    // name, bodySet

    Character* character = nullptr;

    character = new Character("characters\\jack", "sets\\body\\man", "sets\\head\\man-black-haired");
    prefabs.push_back(character);

    character = new Character("characters\\john", "sets\\body\\man", "sets\\head\\man-black-haired");
    prefabs.push_back(character);

    character = new Character("characters\\peter", "sets\\body\\man", "sets\\head\\man-black-haired");
    prefabs.push_back(character);

    character = new Character("characters\\pit", "sets\\body\\man", "sets\\head\\man-black-haired");

    prefabs.push_back(character);


    // MONSTERS TO-DO - heights

    Monster* dziobak = new Monster("monsters\\dziobak", 72, 36, 50, 10);
    dziobak->attributes[Attribute::HP] = 40;
    dziobak->attributes[Attribute::HP_max] = 40;
    dziobak->attributes[Attribute::MP] = 10;
    dziobak->attributes[Attribute::MP_max] = 10;
    dziobak->attributes[Attribute::STRENGTH] = 2;
    dziobak->attributes[Attribute::DEXTERITY] = 2;
    dziobak->attributes[Attribute::INTELLIGENCE] = 2;
    prefabs.push_back(dziobak);

    Monster* goblin = new Monster("monsters\\goblin", 32, 16, 50, 20);
    goblin->attributes[Attribute::HP] = 80;
    goblin->attributes[Attribute::HP_max] = 80;
    goblin->attributes[Attribute::MP] = 10;
    goblin->attributes[Attribute::MP_max] = 10;
    goblin->attributes[Attribute::STRENGTH] = 8;
    goblin->attributes[Attribute::DEXTERITY] = 4;
    goblin->attributes[Attribute::INTELLIGENCE] = 2;
    prefabs.push_back(goblin);

    Monster* wilczur = new Monster("monsters\\wilczur", 70, 35, 60, 50);
    wilczur->attributes[Attribute::HP] = 120;
    wilczur->attributes[Attribute::HP_max] = 120;
    wilczur->attributes[Attribute::MP] = 10;
    wilczur->attributes[Attribute::MP_max] = 10;
    wilczur->attributes[Attribute::STRENGTH] = 12;
    wilczur->attributes[Attribute::DEXTERITY] = 6;
    wilczur->attributes[Attribute::INTELLIGENCE] = 3;
    prefabs.push_back(wilczur);

    Monster* jaszczur = new Monster("monsters\\jaszczur", 70, 35, 50, 80);
    jaszczur->attributes[Attribute::HP] = 160;
    jaszczur->attributes[Attribute::HP_max] = 160;
    jaszczur->attributes[Attribute::MP] = 10;
    jaszczur->attributes[Attribute::MP_max] = 10;
    jaszczur->attributes[Attribute::STRENGTH] = 16;
    jaszczur->attributes[Attribute::DEXTERITY] = 8;
    jaszczur->attributes[Attribute::INTELLIGENCE] = 4;
    prefabs.push_back(jaszczur);

    Monster* niedzwiedz = new Monster("monsters\\niedzwiedz", 70, 35, 75, 80);
    niedzwiedz->attributes[Attribute::HP] = 160;
    niedzwiedz->attributes[Attribute::HP_max] = 160;
    niedzwiedz->attributes[Attribute::MP] = 10;
    niedzwiedz->attributes[Attribute::MP_max] = 10;
    niedzwiedz->attributes[Attribute::STRENGTH] = 16;
    niedzwiedz->attributes[Attribute::DEXTERITY] = 8;
    niedzwiedz->attributes[Attribute::INTELLIGENCE] = 4;
    prefabs.push_back(niedzwiedz);

    Monster* szpon = new Monster("monsters\\szpon", 66, 32, 75, 100);
    szpon->attributes[Attribute::HP] = 200;
    szpon->attributes[Attribute::HP_max] = 200;
    szpon->attributes[Attribute::MP] = 10;
    szpon->attributes[Attribute::MP_max] = 10;
    szpon->attributes[Attribute::STRENGTH] = 20;
    szpon->attributes[Attribute::DEXTERITY] = 10;
    szpon->attributes[Attribute::INTELLIGENCE] = 5;
    prefabs.push_back(szpon);

    Monster* kolcorozec = new Monster("monsters\\kolcorozec", 70, 35, 70, 140);
    kolcorozec->attributes[Attribute::HP] = 240;
    kolcorozec->attributes[Attribute::HP_max] = 240;
    kolcorozec->attributes[Attribute::MP] = 10;
    kolcorozec->attributes[Attribute::MP_max] = 10;
    kolcorozec->attributes[Attribute::STRENGTH] = 24;
    kolcorozec->attributes[Attribute::DEXTERITY] = 12;
    kolcorozec->attributes[Attribute::INTELLIGENCE] = 6;
    prefabs.push_back(kolcorozec);

    Monster* golem = new Monster("monsters\\golem", 90, 60, 80, 180);
    golem->attributes[Attribute::HP] = 280;
    golem->attributes[Attribute::HP_max] = 280;
    golem->attributes[Attribute::MP] = 10;
    golem->attributes[Attribute::MP_max] = 10;
    golem->attributes[Attribute::STRENGTH] = 28;
    golem->attributes[Attribute::DEXTERITY] = 14;
    golem->attributes[Attribute::INTELLIGENCE] = 7;
    prefabs.push_back(golem);

    Monster* troll = new Monster("monsters\\troll", 90, 60, 85, 240);
    troll->attributes[Attribute::HP] = 320;
    troll->attributes[Attribute::HP_max] = 320;
    troll->attributes[Attribute::MP] = 10;
    troll->attributes[Attribute::MP_max] = 10;
    troll->attributes[Attribute::STRENGTH] = 32;
    troll->attributes[Attribute::DEXTERITY] = 16;
    troll->attributes[Attribute::INTELLIGENCE] = 8;
    prefabs.push_back(troll);

    Monster* bies = new Monster("monsters\\bies", 90, 60, 85, 300);
    bies->attributes[Attribute::HP] = 360;
    bies->attributes[Attribute::HP_max] = 360;
    bies->attributes[Attribute::MP] = 10;
    bies->attributes[Attribute::MP_max] = 10;
    bies->attributes[Attribute::STRENGTH] = 36;
    bies->attributes[Attribute::DEXTERITY] = 18;
    bies->attributes[Attribute::INTELLIGENCE] = 9;
    prefabs.push_back(bies);
}




#endif
