#ifndef Game_hpp
#define Game_hpp

// Music by: LisetteAmago
// www.lisetteamago.com /
// lisetteamago@gmail.com


sf::RectangleShape borderLifeBar;   // border
sf::Texture lifeBarBackgroundTexture;       // background lifebar
sf::Sprite lifeBarBackgroundSprite;
sf::Texture lifeBarTexture;         // lifebar
sf::Sprite lifeBarSprite;

bool defeatAllBeasts = false;
bool collectAllItems = false;

void refreshLifeBar();
void drawLifeBar();
bool playerAttack();
bool talkWithCharacter();
bool collectItems();
bool openFurnitures();
bool interactionsWithDoors();
void deleteCollectedItems();
void attack(Unit* attacker, Unit* defender);
void coverOutsideIfPlayerInBuilding();

void gameEvents();
void inventoryEvents();
void tradeEvents();
void dialogueEvents();
void journalEvents();
void statsEvents();

void game() {

    window->setTitle("GAME 2D RPG");

    // load the icon for windows
    sf::Image ico;
    ico.loadFromFile("assets/logo/GameLogo.png");
    window->setIcon(64, 64, ico.getPixelsPtr());

    cam = new Camera();
    window->setView(cam->view);
    prevTime = timeClock.getElapsedTime();
    currentTime = prevTime;

    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    gameState = gameStates::start;

    sf::Text title = sf::Text("welcome", basicFont, 32);
    title.setFillColor(textColor);
    title.setOrigin(title.getLocalBounds().width / 2.f, title.getLocalBounds().height / 2.f);
    title.setPosition(cam->position.x, cam->position.y - 50);

    sf::Text press = sf::Text("press Spacebar to continue", basicFont, 16);
    press.setFillColor(textColor);
    press.setOrigin(press.getLocalBounds().width / 2.f, press.getLocalBounds().height / 2.f);
    press.setPosition(cam->position.x, cam->position.y + 50);

    bool skip = false;

    while(window->isOpen() && !skip){

        sf::Event event;
        while (window->pollEvent(event)) {
            if (event.type == sf::Event::KeyPressed && sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
                skip = true;
                break;
            }
        }

        window->clear(sf::Color::Black);
        window->draw(title);
        window->draw(press);
        window->display();
    }
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    
    controls = new ControlsPanel();
    skip = false;

    while (window->isOpen() && !skip) {

        sf::Event event;
        while (window->pollEvent(event)) {
            if (event.type == sf::Event::KeyPressed && sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
                skip = true;
                break;
            }
        }

        controls->update();

        window->clear(sf::Color::Black);
        controls->draw();
        window->display();
    }

    delete controls;

    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    
    /*
    sf::Music music;
    if (!music.openFromFile("assets/music/Elkmire Keep (LOOP).ogg")) {
        return;
    }
    
    music.setLoop(true);    // TO-DO
    music.play();           // TO-DO
    */
    
    ////////////////////////////////////////////////////

    gameState = gameStates::game;

    clearAllMainListsOfGameObjects();

    createTerrainPrefabs();
    createFloorsPrefabs();
    createWaterPrefabs();

    mapa = new Mapa();
    mapa->load();
    mapa->mapVisiblings();

    createPlayer();
    cam->setPosition(player->position);
    cam->update();

    updateGameObjects();

    /////////////////////////////////////////////////

    gameState = gameStates::dialogue;
    //dialogueBox = new DialogueBox(getDialogue(5));
    dialogueBox = new DialogueBox(getDialogue(0));
    

    // TEST TRADE   ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /*
    Inventory* bag = new Inventory();
    bag->addItem("items/axe");
    inventoryLeft = new InventoryPanel(bag, -300, 0);
    inventoryRight = new InventoryPanel(player->bag, 300, 0);

    cursor = 0;
    gameState = gameStates::trade;
    activePanel = activeInventoryPanel::Left;
    */
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    while (window->isOpen()) {

        prevTime = currentTime;
        currentTime = timeClock.getElapsedTime();
        dt = currentTime.asSeconds() - prevTime.asSeconds();

        sf::Event event;
        while (window->pollEvent(event)) {

            if (event.type == sf::Event::Closed)
                window->close();

            if (event.type == sf::Event::KeyPressed) {

                if (gameState == gameStates::game) {
                    gameEvents();
                }
                else if (gameState == gameStates::inventory) {
                    inventoryEvents();
                }
                else if (gameState == gameStates::trade) {
                    tradeEvents();
                }
                else if (gameState == gameStates::journal) {
                    journalEvents();
                }
                else if (gameState == gameStates::stats) {
                    statsEvents();
                }

            }

            if (event.type == sf::Event::MouseButtonPressed) {

                if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {

                    mousePosition = sf::Mouse::getPosition(*window);	// Pobierz aktualną pozycję myszy względem bieżącego okna
                    worldMousePosition = window->mapPixelToCoords(mousePosition);	// Zamień na współrzędne świata, uwzględniając aktualny widok
                    cout << "cursor at " << worldMousePosition.x << " " << worldMousePosition.y << "\n";

                    Point start(player->position.x, player->position.y);
                    Point goal(worldMousePosition.x, worldMousePosition.y);

                    std::vector < Point > path = aStar(player, goal);

                    std::cout << "Path: ";
                    for (const Point& p : path)
                        std::cout << "(" << p.x << ", " << p.y << ") ";

                    cout << "\n\n";

                }
            }

            if (dialogueBox != nullptr) {
                dialogueBox->update(event);

                if (dialogueBox->state == DialogueState::End) {
                    delete dialogueBox;
                    dialogueBox = nullptr;
                    gameState = gameStates::game;
                }
            }
                

            
        } // events

        // UPDATES
        //cout << "cursor at: " << sf::Mouse::getPosition(*window).x << "," << sf::Mouse::getPosition(*window).y << endl;


        if (gameState == gameStates::game) {

            // WASD
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) || sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
                if (player->direction != 0)
                    player->setDirection(0);
                else if (!collisionPrediction(player, 0, -player->stepSize))
                    player->move();
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) || sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
                if (player->direction != 1)
                    player->setDirection(1);
                else if (!collisionPrediction(player, player->stepSize, 0))
                    player->move();
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) || sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
                if (player->direction != 2)
                    player->setDirection(2);
                else if (!collisionPrediction(player, 0, player->stepSize))
                    player->move();
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
                if (player->direction != 3)
                    player->setDirection(3);
                else if (!collisionPrediction(player, -player->stepSize, 0))
                    player->move();
            }
        }

        deleteCollectedItems();

        updateShaders();

        mapa->mapVisiblings();
        mapa->update();

        cam->setPosition(player->position);
        cam->update();

        updateGameObjects();
        sortGameObjects();


        if(gameState != gameStates::dialogue)
            checkQuests();

        if(gameState == gameStates::inventory)
            updateInventoryPanel();

        if(gameState == gameStates::trade)
            updateTradePanel();
        
        if (gameState == gameStates::journal)
            journal->update();

        if (gameState == gameStates::stats)
            stats->update();


        hits->update();
        refreshLifeBar();

        // DRAW
        window->clear(sf::Color(64, 128, 64));
        window->setView(cam->view);

        mapa->draw();

        for (auto& building : buildings) {
            window->draw(*building->floors);
            building->draw();
        }

        drawGameObjects();

        coverOutsideIfPlayerInBuilding();
        hits->draw();

        if (gameState == gameStates::inventory)
            drawInventoryPanel();

        if (gameState == gameStates::dialogue) {

            if(dialogueBox != nullptr)
                dialogueBox->draw();
        }

        if (gameState == gameStates::trade) {
            drawTradePanel();
        }

        if (gameState == gameStates::journal) {
            journal->draw();
        }

        if (gameState == gameStates::stats) {
            stats->draw();
        }

        drawLifeBar();
        window->display();
    } //while
    return;
}



void refreshLifeBar() {
    short x = cam->position.x - screenWidth / 2.0f;
    short y = cam->position.y - screenHeight / 2.0f;

    borderLifeBar = sf::RectangleShape(sf::Vector2f(200.0f, 30.0f));
    borderLifeBar.setPosition(x, y);
    borderLifeBar.setFillColor(sf::Color(0, 0, 0, 255));

    lifeBarBackgroundTexture = sf::Texture();
    lifeBarBackgroundTexture.loadFromFile("assets/GUI/lifeBarBackground.png");
    lifeBarBackgroundSprite = sf::Sprite();
    lifeBarBackgroundSprite.setTexture(lifeBarBackgroundTexture);
    lifeBarBackgroundSprite.setPosition(x + 4, y + 4);

    lifeBarTexture = sf::Texture();
    lifeBarTexture.loadFromFile("assets/GUI/lifeBar.png");
    lifeBarSprite = sf::Sprite();
    lifeBarSprite.setTexture(lifeBarTexture);
    lifeBarSprite.setTextureRect(sf::IntRect(0, 0, 192.0f * player->HP / player->HP_FULL, 22.0f));
    lifeBarSprite.setPosition(x + 4, y + 4);


}

void drawLifeBar() {
    window->draw(borderLifeBar);
    window->draw(lifeBarBackgroundSprite);
    window->draw(lifeBarSprite);
    
}

bool playerAttack() {

    bool result = false;
    float x, y, rx, ry;
    x = player->position.x;
    y = player->position.y;
    rx = player->colliders[0]->width / 2.0f + player->actionRange;
    ry = (player->colliders[0]->length + player->actionRange) / 2.0f;

    for (auto& m : monsters)
    {
        if(m->isAlive == true)
            if (intersectionTwoEllipses(x, y, rx, ry, m->position.x, m->position.y, m->colliders[0]->width / 2.0f, m->colliders[0]->length / 2.0f)) {
                
                //attack(player, m); // TO-DO
                sf::Vector2f hitPosition = sf::Vector2f(m->position.x, m->position.y - m->height);
                if (rand() % (player->DEXTERITY + 10) - rand() % (m->DEXTERITY + 5) > 0) {

                    // TO-DO - must be dependent on the monster's height
                    int damage = m->takeDamage(player->getDamage());
                    
                    hits->addHitText(hitPosition, to_string(damage));
                }
                else {
                    // TO-DO - hits->addHitText(m->position, 0);
                    hits->addHitText(hitPosition, "miss");
                }
                    

                

                result = true;
            }
    }
    player->attack();   // animation
    return result;
}

bool talkWithCharacter() {

    float x1, y1, rx1, ry1;
    float x2, y2, rx2, ry2;

    x1 = player->position.x;
    y1 = player->position.y;
    rx1 = (player->colliders[0]->width / 2.0f + player->actionRange);
    ry1 = (player->colliders[0]->length + player->actionRange) / 2.0f;

    for (auto& character : characters) {

        if (character->dialogue != nullptr) {

            x2 = character->position.x;
            y2 = character->position.y;
            rx2 = (character->colliders[0]->width / 2.0f + character->ACTION_RANGE);
            ry2 = (character->colliders[0]->length + character->ACTION_RANGE) / 2.0f;

            if (intersectionTwoEllipses(x1, y1, rx1, ry1, x2, y2, rx2, ry2)) {

                // talking 
                // TO-DO
                //setDialogue(character->dialogue);
                return true;
            }
        }

    }


    return false;
}

bool collectItems() {

    float x1, y1, rx1, ry1;
    float x2, y2, rx2, ry2;

    x1 = player->position.x;
    y1 = player->position.y;
    rx1 = (player->colliders[0]->width / 2.0f + player->actionRange);
    ry1 = (player->colliders[0]->length + player->actionRange) / 2.0f;


    for (auto& item : itemsOnMap) {
        x2 = item->position.x;
        y2 = item->position.y;
        rx2 = item->colliders[0]->width / 2.0f;
        ry2 = item->colliders[0]->length / 2.0f;

        if (intersectionTwoEllipses(x1, y1, rx1, ry1, x2, y2, rx2, ry2)) {

            // collect the Item
            player->collectItem(item->item);
            item->collected = true;
            return true;
        }
    }

    for (auto& bag : inventoriesOnMap) {
        x2 = bag->position.x;
        y2 = bag->position.y;
        rx2 = bag->colliders[0]->width / 2.0f;
        ry2 = bag->colliders[0]->length / 2.0f;

        if (intersectionTwoEllipses(x1, y1, rx1, ry1, x2, y2, rx2, ry2)) {

            // collect the bag

            for (int i = 0; i < bag->inventory->items.size(); i++) {
                player->collectItem(bag->inventory->items[i], bag->inventory->counts[i]);
            }

            bag->collected = true;
            return true;
        }
    }

    return false;
}

bool openFurnitures() {
    
    float x1, y1, rx1, ry1;
    float x2, y2, rx2, ry2;

    x1 = player->position.x;
    y1 = player->position.y;
    rx1 = (player->colliders[0]->width / 2.0f + player->actionRange);
    ry1 = (player->colliders[0]->length + player->actionRange) / 2.0f;

    for (auto& furniture : furnitures) {

        if (furniture->inventory != nullptr) {
            x2 = furniture->position.x;
            y2 = furniture->position.y;
            rx2 = furniture->colliders[0]->width;
            ry2 = furniture->colliders[0]->length;

            if (intersectionRectangleWithElipse(x2, y2, rx2, ry2, x1, y1, rx1, ry1)) {
                inventoryLeft = new InventoryPanel(furniture->inventory, -300);
                inventoryRight = new InventoryPanel(player->bag, 300);
                cursor = 0;
                activePanel = activeInventoryPanel::Left;
                gameState = gameStates::trade;
                return true;
            }
        }
    }
    
    return false;
}

bool interactionsWithDoors() {

    for (auto& door : doors) {
        if(door->playerNextTo()) {

            if (door->state == DoorState::Open) {
                door->close();
                return true;
            }
            
            if (door->state == DoorState::Close) {
                door->open();
                return true;
            }
                
        }
            
    }

    return false;
}

void deleteCollectedItems() {
    std::vector < GameObject* > newGameObjectsList;
    std::vector < ItemOnMap* > newItemsOnMapList;
    std::vector < InventoryOnMap* > newInventoriesOnMapList;

    // DELETE ITEMS
    newGameObjectsList.clear();
    newItemsOnMapList.clear();

    for (auto& go : gameObjects) {
        if (go->type != GameObjectType::ItemOnMap) {
            newGameObjectsList.push_back(go);
        }
    }

    for (auto& item : itemsOnMap) {
        if (item->collected != true) {
            newGameObjectsList.push_back(item);
            newItemsOnMapList.push_back(item);
        }
    }

    gameObjects = newGameObjectsList;
    itemsOnMap = newItemsOnMapList;

    // DELETE INVENTORIES
    newGameObjectsList.clear();
    newInventoriesOnMapList.clear();

    for (auto& go : gameObjects) {
        if (go->type != GameObjectType::InventoryOnMap) {
            newGameObjectsList.push_back(go);
        }
    }

    for (auto& bag : inventoriesOnMap) {
        if (bag->collected != true) {
            newGameObjectsList.push_back(bag);
            newInventoriesOnMapList.push_back(bag);
        }
    }

    gameObjects = newGameObjectsList;
    inventoriesOnMap = newInventoriesOnMapList;

}

void attack(Unit* attacker, Unit* defender) {

    if (rand() % attacker->DEXTERITY - rand() % defender->DEXTERITY > 0) {
        defender->takeDamage(attacker->getDamage());
    }

}

void coverOutsideIfPlayerInBuilding() {
    for (auto& b : buildings) {
        if (b->playerInside()) {

            float x1, x2, y1, y2;
            x1 = b->position.x - b->size.x / 2 * 16;
            x2 = b->position.x + b->size.x / 2 * 16;
            y1 = b->position.y - b->size.y * 16;
            y2 = b->position.y;

            sf::RectangleShape rectTop(sf::Vector2f(screenWidth, y1 - cam->position.y + screenHeight / 2));
            rectTop.setFillColor(sf::Color::Black);
            rectTop.setPosition(cam->position.x - screenWidth / 2, cam->position.y - screenHeight / 2);
            window->draw(rectTop);

            sf::RectangleShape rectBottom(sf::Vector2f(screenWidth, cam->position.y + screenHeight / 2 - y2));
            rectBottom.setFillColor(sf::Color::Black);
            rectBottom.setPosition(cam->position.x - screenWidth / 2, y2);
            window->draw(rectBottom);

            sf::RectangleShape rectLeft(sf::Vector2f(x1 - cam->position.x + screenWidth / 2, y2 - y1));
            rectLeft.setFillColor(sf::Color::Black);
            rectLeft.setPosition(cam->position.x - screenWidth / 2, y1);
            window->draw(rectLeft);

            sf::RectangleShape rectRight(sf::Vector2f(cam->position.x + screenWidth / 2 - x2, y2 - y1));
            rectRight.setFillColor(sf::Color::Black);
            rectRight.setPosition(x2, y1);
            window->draw(rectRight);

        }
    }
}


void gameEvents() {

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
        window->close();
        exit(0);
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) || sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)) {

        if (player->cooldown <= 0.0f)
            if (!playerAttack())
                if (!collectItems())
                    if (!openFurnitures())
                        if(!interactionsWithDoors())
                            if (!talkWithCharacter())
                                player->attack();   // animation of attack
                 
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::E) || sf::Keyboard::isKeyPressed(sf::Keyboard::LControl)) {
        cursor = 0;
        inventory = new InventoryPanel(player->bag);
        gameState = gameStates::inventory;
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::J)) {
        cursor = 0;
        journal = new JournalPanel();
        gameState = gameStates::journal;
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::H)) {
        gameState = gameStates::stats;
        stats = new StatsPanel();
    }


}

void inventoryEvents() {
    // INVENTORY
    // TO-DO WASD with inventory->scroll

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
        gameState = gameStates::game;
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::E) || sf::Keyboard::isKeyPressed(sf::Keyboard::LControl)) {
        gameState = gameStates::game;
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::J)) {
        cursor = 0;
        journal = new JournalPanel();
        gameState = gameStates::journal;
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) || sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)) {
        // USE THE ITEM
        useItem();

        if (cursor + inventory->scroll * itemsInRow >= inventory->sortedItems.size()) {
            
            short maxScroll = (inventory->sortedItems.size() + itemsInRow - 1) / itemsInRow - itemsInCol;
            if (maxScroll < 0)
                maxScroll = 0;

            if (inventory->scroll > maxScroll) {

                cursor = cursor + (inventory->scroll-maxScroll)*itemsInRow - 1;
                inventory->scroll = maxScroll;
                
            }
            else
                cursor -= 1;
        }

    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
        if(cursor%itemsInRow != 0)
          cursor -= 1;
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) || sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
        if((cursor + 1)%itemsInRow != 0 )
            if(cursor + 1 + inventory->scroll * itemsInRow < inventory->sortedItems.size())
                cursor += 1;
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) || sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
        cursor -= itemsInRow;

        if (cursor < 0) {
            inventory->scroll -= 1;
            if (inventory->scroll < 0)
                inventory->scroll = 0;

            cursor += itemsInRow;
        }
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) || sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
        if (inventory->sortedItems.size() > 0) {
            if ((cursor / itemsInRow * itemsInRow) + itemsInRow < inventory->sortedItems.size())
                cursor += itemsInRow;

            short maxScroll = (inventory->sortedItems.size() + itemsInRow - 1) / itemsInRow - itemsInCol;
            if (maxScroll < 0)
                maxScroll = 0;

            if (cursor >= itemsInRow * itemsInCol) {
                inventory->scroll += 1;

                if (inventory->scroll > maxScroll)
                    inventory->scroll = maxScroll;

                cursor -= itemsInRow;
            }

            if (cursor + inventory->scroll * itemsInRow >= inventory->sortedItems.size()) {
                cursor = inventory->sortedItems.size() - inventory->scroll * itemsInRow - 1;
            }
        }
        else
            cursor = 0;
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::J)) {
        gameState = gameStates::journal;
        journal = new JournalPanel();
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::H)) {
        gameState = gameStates::stats;
        stats = new StatsPanel();
    }

}

void tradeEvents() {

    // TO-DO - whole function to repair

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
        gameState = gameStates::game;
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::E) || sf::Keyboard::isKeyPressed(sf::Keyboard::LControl)) {
        gameState = gameStates::game;
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
        if (activePanel == activeInventoryPanel::Right) {
            // ACTIVE PANEL RIGHT

            if (cursor % itemsInRow == 0) {

                activePanel = activeInventoryPanel::Left;
                
                if (inventoryLeft->sortedItems.size() == 0)
                    cursor = 0;
                else {
                    cursor = cursor + itemsInRow - 1;

                    short diff = cursor + inventoryLeft->scroll * itemsInRow - (inventoryLeft->sortedItems.size() - 1);
                    if (diff > 0)
                        cursor -= diff;
                }
            }
            else
                cursor -= 1;
        }
        else {
            // ACTIVE PANEL LEFT
            if ((cursor % itemsInRow != 0))
                cursor -= 1;
        }
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) || sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {

        if (activePanel == activeInventoryPanel::Left) {
            // ACTIVE PANEL LEFT
            if (inventoryLeft->inventory->items.size() == 0) {
                activePanel = activeInventoryPanel::Right;
                cursor = 0;
            }
            else if ((cursor + inventoryLeft->scroll * itemsInRow >= inventoryLeft->sortedItems.size()-1) || cursor % itemsInRow == itemsInRow - 1) {
                activePanel = activeInventoryPanel::Right;

                short diff = cursor + inventoryRight->scroll * itemsInRow - (inventoryRight->sortedItems.size() - 1);
                if (diff > 0)
                    cursor -= diff;
                cursor -= cursor % itemsInRow;


            }
            else {
                cursor += 1;
            }
               
        }
        else {
            // ACTIVE PANEL RIGHT
            if (cursor % itemsInRow != itemsInRow - 1) {
                if(cursor + 1 + inventoryRight->scroll*itemsInRow < inventoryRight->sortedItems.size())
                    cursor += 1;
            }
        }

    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) || sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
        cursor -= itemsInRow;

        if (cursor < 0)
        {
            if (activePanel == activeInventoryPanel::Right) {
                if(inventoryRight->scroll > 0)
                    inventoryRight->scroll -= 1;
            }

            if (activePanel == activeInventoryPanel::Left) {
                if (inventoryLeft->scroll > 0)
                    inventoryLeft->scroll -= 1;
            }

            cursor += itemsInRow;
        }

    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) || sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
       
        if (activePanel == activeInventoryPanel::Right) {

            if (inventoryRight->inventory->items.size() > 0) {

                if ((cursor / itemsInRow * itemsInRow) + itemsInRow < inventoryRight->sortedItems.size())
                    cursor += itemsInRow;

                short maxScroll = (inventoryRight->sortedItems.size() + itemsInRow - 1) / itemsInRow - itemsInCol;
                if (maxScroll < 0)
                    maxScroll = 0;

                if (cursor >= itemsInRow * itemsInCol) {
                    inventoryRight->scroll += 1;

                    if (inventoryRight->scroll > maxScroll) {
                        inventoryRight->scroll = maxScroll;
                    }

                    cursor -= itemsInRow;
                }

                if (cursor + inventoryRight->scroll * itemsInRow >= inventoryRight->sortedItems.size()) {
                    cursor = inventoryRight->sortedItems.size() - inventoryRight->scroll * itemsInRow - 1;
                }
            }
            else
                cursor = 0;
            
        }

        if (activePanel == activeInventoryPanel::Left) {

            if (inventoryLeft->sortedItems.size() > 0) {
                if ((cursor / itemsInRow * itemsInRow) + itemsInRow < inventoryLeft->sortedItems.size())
                    cursor += itemsInRow;

                short maxScroll = (inventoryLeft->sortedItems.size() + itemsInRow - 1) / itemsInRow - itemsInCol;
                if (maxScroll < 0)
                    maxScroll = 0;

                if (cursor >= itemsInRow * itemsInCol) {
                    inventoryLeft->scroll += 1;

                    if (inventoryLeft->scroll > maxScroll)
                        inventoryLeft->scroll = maxScroll;

                    cursor -= itemsInRow;
                }

                if (cursor + inventoryLeft->scroll * itemsInRow >= inventoryLeft->sortedItems.size()) {
                    cursor = inventoryLeft->sortedItems.size() - inventoryLeft->scroll * itemsInRow - 1;
                }
            }
            else
                cursor = 0;
            
            
        }

    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) || sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)) {

        if (activePanel == activeInventoryPanel::Left) {

            if (inventoryLeft->sortedItems.size() > 0) {
                if (cursor < inventoryLeft->sortedItems.size()) {

                    transferItem(inventoryLeft->sortedItems[cursor + inventoryLeft->scroll * itemsInRow], inventoryLeft->inventory, inventoryRight->inventory);

                    if (cursor + inventoryLeft->scroll * itemsInRow >= inventoryLeft->sortedItems.size()) {

                        short maxScroll = (inventoryLeft->sortedItems.size() + itemsInRow - 1) / itemsInRow - itemsInCol;
                        if (maxScroll < 0)
                            maxScroll = 0;

                        if (inventoryLeft->scroll > maxScroll) {
                            cursor = cursor + (inventoryLeft->scroll - maxScroll) * itemsInRow - 1;
                            inventoryLeft->scroll = maxScroll;
                        }
                        else {
                            if(cursor != 0)
                                cursor -= 1;
                        }
                            
                    }
                }
            }
        } 

        if (activePanel == activeInventoryPanel::Right) {
            if (inventoryRight->inventory->items.size() > 0) {
                if (cursor < inventoryRight->inventory->items.size()) {

                    transferItem(inventoryRight->sortedItems[cursor + inventoryRight->scroll * itemsInRow], inventoryRight->inventory, inventoryLeft->inventory);

                    if (cursor + inventoryRight->scroll * itemsInRow >= inventoryRight->sortedItems.size()) {

                        short maxScroll = (inventoryRight->sortedItems.size() + itemsInRow - 1) / itemsInRow - itemsInCol;
                        if (maxScroll < 0)
                            maxScroll = 0;

                        if (inventoryRight->scroll > maxScroll) {
                            cursor = cursor + (inventoryRight->scroll - maxScroll) * itemsInRow - 1;
                            inventoryRight->scroll = maxScroll;
                        }
                        else {
                            if(cursor != 0)
                                cursor -= 1;
                        }
                            
                    }

                }

            }
            else
                cursor = 0;
        }
    }


}

void dialogueEvents(sf::Event& event) {

    // TO-DO
    dialogueBox->update(event);
}

void journalEvents() {

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
        gameState = gameStates::game;
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::J)) {
        gameState = gameStates::game;
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::E)) {
        gameState = gameStates::inventory;
        inventory = new InventoryPanel(player->bag);
        cursor = 0;
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::H)) {
        gameState = gameStates::stats;
        stats = new StatsPanel();
        
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) || sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
        cursor -= 1;
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) || sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
        cursor += 1;
    }
}

void statsEvents() {

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
        gameState = gameStates::game;
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::H)) {
        gameState = gameStates::game;
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::E) || sf::Keyboard::isKeyPressed(sf::Keyboard::LControl)) {
        gameState = gameStates::inventory;
        cursor = 0;
        inventory = new InventoryPanel(player->bag);
        
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::J)) {
        gameState = gameStates::journal;
        cursor = 0;
        journal = new JournalPanel();
        
    }
}

#endif