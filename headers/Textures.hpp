#ifndef Textures_hpp
#define Textures_hpp

using namespace std;


bool areImagesEqual(sf::Image& img1, sf::Image& img2) {
	if (img1.getSize() != img2.getSize()) {
		return false; // Rozmiary są różne
	}

	// Porównaj każdy piksel
	for (unsigned int y = 0; y < img1.getSize().y; y++) {
		for (unsigned int x = 0; x < img1.getSize().x; x++) {
			if (img1.getPixel(x, y) != img2.getPixel(x, y)) {
				return false; // Piksele są różne
			}
		}
	}
	return true; // Wszystkie piksele są identyczne
}

enum class TextureType { Single, Set };

class Texture {
public:
	string name;
	TextureType type;
	float cx, cy;	// coordinates of center on the texture

	Texture(string pathfile, TextureType type, float cx, float cy) {
		name = "";

		short i = int(pathfile.size()) - 5;
		while (i >= 0)
			name = pathfile[i--] + name;

		this->type = type;
		this->cx = cx;
		this->cy = cy;
	}

	Texture(string name, TextureType type) {
		this->name = name;
		this->type = type;
		cx = cy = 0;
	}
};

class SingleTexture : public Texture {
public:
	sf::Texture* texture;
	
	SingleTexture(string pathfile, float cx, float cy) : Texture(pathfile, TextureType::Single, cx, cy) {

		texture = new sf::Texture;
		texture->loadFromFile("assets/" + pathfile);
		texture->setRepeated(true);

		//cout << "load texture: " << pathfile << " as: " << name << endl;
	}

	SingleTexture(string name, sf::Image image, float cx, float cy) : Texture(name, TextureType::Single) {
		
		texture = new sf::Texture;
		texture->loadFromImage(image);
		texture->setRepeated(true);
		
		this->cx = cx;
		this->cy = cy;
		//cout << "load texture from set as: " << name << endl;
	}


	SingleTexture(sf::Image image) : Texture("texture", TextureType::Single) {
		this->texture = new sf::Texture();
		this->texture->loadFromImage(image);
		cx = texture->getSize().x / 2;
		cy = texture->getSize().y / 2;
	}
};

std::vector < SingleTexture* > singleTextures;

SingleTexture* getSingleTexture(string name) {

	for (auto& t : singleTextures) {
		if (t->name == name) {
			return t;
		}
	}

	std::cout << "error - get Texture - Texture: \"" << name << "\" not exists\n";
	return nullptr;
}

std::vector < SingleTexture* > getAnimation(string name) {

	std::vector < SingleTexture* > animation;
	animation.clear();

	for (auto& tex : singleTextures)
		if (tex->name.find(name + "[") != std::string::npos)
			animation.push_back(tex);

	if (animation.empty()) {

		SingleTexture* tex = getSingleTexture(name);
		if (tex != nullptr)
			animation.push_back(tex);
	}

	if (animation.empty()) {
		std::cout << "error - get Animation - Animation: \"" << name << "\" is empty\n";
	}

	return animation;
}

std::vector < SingleTexture* > getSingleTextures(string name) {

	std::vector < SingleTexture* > textures;
	textures.clear();

	for (auto& tex : singleTextures)
		if (tex->name.find(name) != std::string::npos)
			textures.push_back(tex);

	if (textures.empty()) {
		std::cout << "error - get Textures - Textures: \"" << name << "\" is empty\n";
	}

	return textures;
}

void loadSingleTexture(string pathfile, float cx, float cy) {
	singleTextures.push_back(new SingleTexture(pathfile, cx, cy));
}

void loadTextureSets(string pathfile, int tile_width, int tile_height, float cx, float cy) {


	sf::Image image;
	image.loadFromFile("assets/" + pathfile + ".png");

	short image_width = image.getSize().x;
	short image_height = image.getSize().y;

	//cout << image_width << "x" << image_height << "\n";

	int counter = 0;

	for (short y = 0; y < image_height; y += tile_height)
		for (short x = 0; x < image_width; x += tile_width) {

			// create tile - fragment of texture
			sf::Image tile;
			tile.create(tile_width, tile_height);
			tile.copy(image, 0, 0, sf::IntRect(x, y, tile_width, tile_height));

			// searching - exist doubles or no
			bool existed = false;
			
			for (short i = 0; i < singleTextures.size(); i++) {
				sf::Image img = singleTextures[i]->texture->copyToImage();
				
				if (areImagesEqual(tile, img)) {
					existed = true;
					//cout << "exits now\n";
					break;
				}
			}

			// if no exist then add
			if (existed == false) {
				SingleTexture* new_texture = new SingleTexture(pathfile + "_" + to_string(counter), tile, cx, cy);
				//cout << "created texture: " << pathfile + "_" + to_string(counter) << "\n";
				singleTextures.push_back(new_texture);

				counter += 1;

			}

		}

}

void loadAnimation(string pathfile, int tile_width, int tile_height, float cx, float cy) {


	sf::Image image;
	image.loadFromFile("assets/" + pathfile + ".png");

	short image_width = image.getSize().x;
	short image_height = image.getSize().y;

	//cout << image_width << "x" << image_height << "\n";

	int counter = 0;

	for (short y = 0; y < image_height; y += tile_height)
		for (short x = 0; x < image_width; x += tile_width) {

			// create tile - fragment of texture
			sf::Image tile;
			tile.create(tile_width, tile_height);
			tile.copy(image, 0, 0, sf::IntRect(x, y, tile_width, tile_height));

			SingleTexture* new_texture = new SingleTexture(pathfile + "[" + to_string(counter) + "]", tile, cx, cy);
			//cout << "created texture: " << pathfile + "_" + to_string(counter) << "\n";
			singleTextures.push_back(new_texture);
			counter += 1;


		}
}

void generateTileSet() {
	sf::Image masks[16];

	for (int i = 0; i < 16; i++) {
		masks[i].create(64, 64);
		if (!masks[i].loadFromFile("assets/tiles/basic2/" + std::to_string(i) + ".png")) {
			std::cout << "Błąd wczytywania maski: " << i << "\n";
			return;
		}
	}

	std::cout << "Wczytano maski\n";

	std::vector<SingleTexture*> tiles = getSingleTextures("tiles/tile_");
	std::cout << "Tiles: " << tiles.size() << "\n";

	unsigned int N = tiles.size();
	unsigned int M = 14;  // Liczba masek
	unsigned int totalTiles = (N * (N - 1) / 2) * M;

	// Obliczanie wymiarów wynikowej tekstury
	unsigned int tileSize = 64;
	unsigned int tilesPerRow = std::ceil(std::sqrt(totalTiles));  // Najbardziej kwadratowy układ
	unsigned int rows = (totalTiles + tilesPerRow - 1) / tilesPerRow;

	sf::Image tile_set_image;
	tile_set_image.create(tilesPerRow * tileSize, rows * tileSize, sf::Color::Transparent);

	sf::Image first_tile, second_tile, mask, result_tile;
	first_tile.create(tileSize, tileSize);
	second_tile.create(tileSize, tileSize);
	result_tile.create(tileSize, tileSize);

	// Na początku zapiszemy bazowe kafelki, by się nie powtarzały
	unsigned int tileIndex = 0;

	for (short tile_id = 0; tile_id < N; tile_id++) {
		unsigned int newX = (tileIndex % tilesPerRow) * tileSize;
		unsigned int newY = (tileIndex / tilesPerRow) * tileSize;

		tile_set_image.copy(tiles[tile_id]->texture->copyToImage(), newX, newY);
		tileIndex++;
	}

	// Teraz generujemy przejściowe kafelki
	for (short tile_1_id = 0; tile_1_id < N; tile_1_id++) {
		for (short tile_2_id = tile_1_id + 1; tile_2_id < N; tile_2_id++) {
			first_tile = tiles[tile_1_id]->texture->copyToImage();
			second_tile = tiles[tile_2_id]->texture->copyToImage();

			for (short mask_id = 1; mask_id < 15; mask_id++) { // Pomiń 0 i 15
				mask = masks[mask_id];

				for (unsigned int y = 0; y < tileSize; y++) {
					for (unsigned int x = 0; x < tileSize; x++) {
						sf::Color pixel = mask.getPixel(x, y);

						if (pixel.r == 237 && pixel.g == 28 && pixel.b == 36) {
							result_tile.setPixel(x, y, first_tile.getPixel(x, y));
						}
						else if (pixel.r == 127 && pixel.g == 127 && pixel.b == 127) {
							result_tile.setPixel(x, y, second_tile.getPixel(x, y));
						}
						else {
							result_tile.setPixel(x, y, pixel);
						}
					}
				}

				unsigned int newX = (tileIndex % tilesPerRow) * tileSize;
				unsigned int newY = (tileIndex / tilesPerRow) * tileSize;

				if (newY >= rows * tileSize) {
					std::cerr << "Za dużo kafelków! Przekracza rozmiar tekstury.\n";
					return;
				}

				tile_set_image.copy(result_tile, newX, newY);
				tileIndex++;
			}
		}
	}

	// Zapisujemy obraz do pliku
	tile_set_image.saveToFile("assets/tiles/tile_set_final.png");

	SingleTexture* texture_tile_set = new SingleTexture(tile_set_image);
	singleTextures.push_back(texture_tile_set);
	std::cout << "Zapisano tile_set_final.png\n";
}

void loadTextures() {

	singleTextures.clear();

	// NOISE //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	loadSingleTexture("noise.png", 256, 256);
	loadSingleTexture("noise2.png", 256, 256);
	loadSingleTexture("empty.png", 32, 32);

	// GUI ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	loadSingleTexture("GUI/slot1.png", 40, 40);
	loadSingleTexture("GUI/slot2.png", 32, 32);
	loadSingleTexture("GUI/selector.png", 40, 40);

	loadSingleTexture("GUI/corner.png", 4, 4);
	loadSingleTexture("GUI/border_horizontal.png", 3, 3);
	loadSingleTexture("GUI/border_vertical.png", 3, 3);

	loadSingleTexture("GUI/infoPanel.png", 300, 75);
	loadSingleTexture("GUI/bigPanel.png", 300, 200);

	loadSingleTexture("GUI/wideArrowUp1.png", 80, 20);
	loadSingleTexture("GUI/wideArrowUp2.png", 80, 20);
	loadSingleTexture("GUI/wideArrowDown1.png", 160, 18.5f);
	loadSingleTexture("GUI/wideArrowDown2.png", 160, 18.5f);

	// menu buttons textures
	loadSingleTexture("GUI/menuButtons/menuButton.png", 32, 26);
	loadSingleTexture("GUI/menuButtons/menuButton-terrain.png", 32, 26);
	loadSingleTexture("GUI/menuButtons/menuButton-floors.png", 32, 26);
	loadSingleTexture("GUI/menuButtons/menuButton-water.png", 32, 26);
	loadSingleTexture("GUI/menuButtons/menuButton-furnitures.png", 32, 26);
	loadSingleTexture("GUI/menuButtons/menuButton-walls.png", 32, 26);
	loadSingleTexture("GUI/menuButtons/menuButton-monsters.png", 32, 26);
	loadSingleTexture("GUI/menuButtons/menuButton-flat_objects.png", 32, 26);
	loadSingleTexture("GUI/menuButtons/menuButton-items.png", 32, 26);
	loadSingleTexture("GUI/menuButtons/menuButton-natures.png", 32, 26);
	loadSingleTexture("GUI/menuButtons/menuButton-smallObjects.png", 32, 26);
	loadSingleTexture("GUI/menuButtons/menuButton-objects.png", 32, 26);
	loadSingleTexture("GUI/menuButtons/menuButton-buildings.png", 32, 26);
	loadSingleTexture("GUI/menuButtons/menuButton-directions.png", 32, 26);

	// small buttons textures
	loadSingleTexture("GUI/smallButtons/smallbutton.png", 20, 20);
	loadSingleTexture("GUI/smallButtons/smallbutton-ArrowUp.png", 20, 20);
	loadSingleTexture("GUI/smallButtons/smallbutton-ArrowDown.png", 20, 20);
	loadSingleTexture("GUI/smallButtons/smallbutton-ArrowLeft.png", 20, 20);
	loadSingleTexture("GUI/smallButtons/smallbutton-ArrowRight.png", 20, 20);

	// tool butttons textures
	loadSingleTexture("GUI/toolButtons/toolbutton.png", 20, 16);
	loadSingleTexture("GUI/toolButtons/toolbutton-cursor.png", 20, 16);
	loadSingleTexture("GUI/toolButtons/toolbutton-brush.png", 20, 16);
	loadSingleTexture("GUI/toolButtons/toolbutton-rect_brush.png", 20, 16);
	loadSingleTexture("GUI/toolButtons/toolbutton-increase.png", 20, 16);
	loadSingleTexture("GUI/toolButtons/toolbutton-decrease.png", 20, 16);
	loadSingleTexture("GUI/toolButtons/toolbutton-rectangle.png", 20, 16);
	loadSingleTexture("GUI/toolButtons/toolbutton-elipse.png", 20, 16);
	loadSingleTexture("GUI/toolButtons/toolbutton-fill.png", 20, 16);
	loadSingleTexture("GUI/toolButtons/toolbutton-eraser.png", 20, 16);

	loadSingleTexture("GUI/spacebutton.png", 80, 20);

	loadSingleTexture("GUI/scrollbar_16/bar_bottom.png", 8, 8);
	loadSingleTexture("GUI/scrollbar_16/bar_top.png", 8, 8);
	loadSingleTexture("GUI/scrollbar_16/bar_center.png", 8, 8);
	loadSingleTexture("GUI/scrollbar_16/scroll_bottom.png", 8, 8);
	loadSingleTexture("GUI/scrollbar_16/scroll_top.png", 8, 8);
	loadSingleTexture("GUI/scrollbar_16/scroll_center.png", 8, 8);

	loadSingleTexture("GUI/scrollbar_20/bar_bottom.png", 10, 10);
	loadSingleTexture("GUI/scrollbar_20/bar_top.png", 10, 10);
	loadSingleTexture("GUI/scrollbar_20/bar_center.png", 10, 10);
	loadSingleTexture("GUI/scrollbar_20/scroll_bottom.png", 10, 10);
	loadSingleTexture("GUI/scrollbar_20/scroll_top.png", 10, 10);
	loadSingleTexture("GUI/scrollbar_20/scroll_center.png", 10, 10);

	loadSingleTexture("GUI/checkbox/check.png", 8, 8);

	loadSingleTexture("GUI/hand.png", 8, 8);
	loadSingleTexture("GUI/grey_hand.png", 8, 8);
	loadSingleTexture("GUI/talk.png", 8, 8);

	loadSingleTexture("GUI/icons/MapEditor_small_ico.png", 15, 15);
	loadSingleTexture("GUI/icons/dictionary.png", 15, 15);
	loadSingleTexture("GUI/icons/file.png", 15, 15);
	loadSingleTexture("GUI/icons/empty.png", 15, 15);

	loadSingleTexture("GUI/context_menu/btn_default.png", 15, 15);
	loadSingleTexture("GUI/context_menu/btn_info.png", 15, 15);
	loadSingleTexture("GUI/context_menu/btn_edit.png", 15, 15);
	loadSingleTexture("GUI/context_menu/btn_remove.png", 15, 15);
	loadSingleTexture("GUI/context_menu/btn_cancel.png", 15, 15);

	loadSingleTexture("GUI/character_menu/menu_slot.png", 32, 20);
	loadSingleTexture("GUI/character_menu/menu_statistics.png", 32, 20);
	loadSingleTexture("GUI/character_menu/menu_layout.png", 32, 20);
	loadSingleTexture("GUI/character_menu/menu_equipment.png", 32, 20);
	loadSingleTexture("GUI/character_menu/menu_inventory.png", 32, 20);
	loadSingleTexture("GUI/character_menu/menu_dialogues.png", 32, 20);
	loadSingleTexture("GUI/character_menu/menu_quests.png", 32, 20);
	loadSingleTexture("GUI/character_menu/layout_slot.png", 40, 40);
	loadSingleTexture("GUI/character_menu/item_slot.png", 32, 32);
	loadSingleTexture("GUI/character_menu/direction_top.png", 32, 32);
	loadSingleTexture("GUI/character_menu/direction_bottom.png", 32, 32);
	loadSingleTexture("GUI/character_menu/direction_left.png", 32, 32);
	loadSingleTexture("GUI/character_menu/direction_right.png", 32, 32);



	// TILES //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	loadSingleTexture("tiles/0_tileset.png", 0, 0);
	loadSingleTexture("tiles/tile_0_water.png", 32, 32);
	loadSingleTexture("tiles/tile_1_sands.png", 32, 32);
	loadSingleTexture("tiles/tile_2_grass.png", 32, 32);
	loadSingleTexture("tiles/tile_3_gravel.png", 32, 32);
	loadSingleTexture("tiles/tile_4_steps.png", 32, 32);
	loadSingleTexture("tiles/tile_5_highlands.png", 32, 32);
	loadSingleTexture("tiles/tile_6.png", 32, 32);
	loadSingleTexture("tiles/tile_7.png", 32, 32);
	loadSingleTexture("tiles/tile_8.png", 32, 32);
	loadSingleTexture("tiles/tile_9.png", 32, 32);
	loadSingleTexture("tiles/tile_10.png", 32, 32);

	generateTileSet();

	loadTextureSets("tiles/set_0_water_sands", 64, 64, 32, 32);
	loadTextureSets("tiles/set_0_sands_water", 64, 64, 32, 32);
	loadTextureSets("tiles/set_1_sands_grass", 64, 64, 32, 32);
	loadTextureSets("tiles/set_1_grass_sands", 64, 64, 32, 32);
	loadTextureSets("tiles/set_2_grass_gravel", 64, 64, 32, 32);
	loadTextureSets("tiles/set_2_gravel_grass", 64, 64, 32, 32);

	// FLOORS ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	loadSingleTexture("floors/0_floorset.png", 0, 0);
	loadSingleTexture("floors/floor_0.png", 32, 32);
	loadSingleTexture("floors/floor_1.png", 32, 32);
	loadSingleTexture("floors/floor_2.png", 32, 32);
	loadSingleTexture("floors/floor_3.png", 32, 32);

	// NATURES ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	loadSingleTexture("natures/tree9.png", 129, 213);
	loadSingleTexture("natures/bush_1.png", 32, 44);
	loadSingleTexture("natures/stump_1.png", 62, 90);
	loadSingleTexture("natures/boulder_1.png", 66, 72);
	loadSingleTexture("natures/boulder_2.png", 65, 78);
	loadSingleTexture("natures/boulder_3.png", 60, 80);
	loadSingleTexture("natures/column_1.png", 65, 85);
	loadSingleTexture("natures/column_2.png", 65, 85);
	loadSingleTexture("natures/column_3.png", 65, 85);
	loadSingleTexture("natures/stone_altar.png", 65, 85);
	loadSingleTexture("natures/stone_platform.png", 65, 78);
	loadSingleTexture("natures/driftwood.png", 59, 77);
	loadSingleTexture("natures/rock_1.png", 32, 36);
	loadSingleTexture("natures/rock_2.png", 32, 36);
	loadSingleTexture("natures/reed_1.png", 32, 54);
	loadSingleTexture("natures/reed_2.png", 32, 54);


	// SMALL OBJECTS ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	loadSingleTexture("smallObjects/grass_1.png", 33, 32);
	loadSingleTexture("smallObjects/grass_2.png", 33, 32);
	loadSingleTexture("smallObjects/grass_3.png", 33, 32);

	// OBJECTS ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	loadSingleTexture("objects/palisade.png", 16, 112);
	loadSingleTexture("objects/palisade.png", 16, 112);
	loadSingleTexture("objects/stone_wall.png", 8, 56);
	loadSingleTexture("objects/great_stone_wall.png", 16, 112);
	loadSingleTexture("objects/great_gate.png", 32, 112);
	loadSingleTexture("objects/great_stone_gate.png", 64, 112);
	loadSingleTexture("objects/well.png", 64, 96);
	loadSingleTexture("objects/hunter_tent.png", 128, 175);
	loadSingleTexture("objects/log_with_saw.png", 64, 70);
	loadSingleTexture("objects/pile_of_wood_1.png", 64, 80);
	loadSingleTexture("objects/pile_of_wood_2.png", 64, 80);
	loadSingleTexture("objects/stone_altar_1.png", 66, 66);

	loadAnimation("objects/brazier", 64, 64, 32, 40);

	// FLAT OBJECTS ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	loadSingleTexture("flatObjects/path_1.png", 32, 32);
	loadSingleTexture("flatObjects/path_2.png", 32, 32);
	loadSingleTexture("flatObjects/stonepath_1.png", 32, 32);
	loadSingleTexture("flatObjects/stonepath_2.png", 32, 32);
	loadSingleTexture("flatObjects/sandspath_1.png", 32, 32);
	loadSingleTexture("flatObjects/sandspath_2.png", 32, 32);

	loadSingleTexture("flatObjects/herb_1.png", 33, 32);
	loadSingleTexture("flatObjects/herb_2.png", 33, 32);

	loadSingleTexture("flatObjects/small_rock_1.png", 16, 16);
	loadSingleTexture("flatObjects/small_rock_2.png", 16, 16);
	loadSingleTexture("flatObjects/small_rock_3.png", 16, 16);
	loadSingleTexture("flatObjects/small_rock_4.png", 16, 16);

	loadSingleTexture("flatObjects/small_sands_rock_1.png", 16, 16);
	loadSingleTexture("flatObjects/small_sands_rock_2.png", 16, 16);
	loadSingleTexture("flatObjects/small_sands_rock_3.png", 16, 16);
	loadSingleTexture("flatObjects/small_sands_rock_4.png", 16, 16);

	// ITEMS ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	loadSingleTexture("items/bag.png", 28, 48);

	// WEAPONS
	loadSingleTexture("items/club.png", 32, 32);
	loadSingleTexture("items/knife.png", 32, 32);
	loadSingleTexture("items/hatchet.png", 32, 32);
	loadSingleTexture("items/sword.png", 32, 32);
	loadSingleTexture("items/dagger.png", 32, 32);
	loadSingleTexture("items/wooden club.png", 32, 32);
	loadSingleTexture("items/long sword.png", 32, 32);
	loadSingleTexture("items/curved sword.png", 32, 32);
	loadSingleTexture("items/wide blade.png", 32, 32);
	loadSingleTexture("items/gladius.png", 32, 32);
	loadSingleTexture("items/iron club.png", 32, 32);
	loadSingleTexture("items/axe.png", 32, 32);
	loadSingleTexture("items/stone hammer.png", 32, 32);

	// HELMET
	loadSingleTexture("items/skin helmet.png", 32, 32);
	loadSingleTexture("items/wool hat.png", 32, 32);

	// ARMORS
	loadSingleTexture("items/plate armor.png", 32, 32);
	loadSingleTexture("items/chain mail.png", 32, 32);
	loadSingleTexture("items/skin jacket.png", 32, 32);
	loadSingleTexture("items/torn shirt.png", 32, 32);
	loadSingleTexture("items/wool shirt.png", 32, 32);

	// PANTS
	loadSingleTexture("items/chain mail pants.png", 32, 32);
	loadSingleTexture("items/skin pants.png", 32, 32);
	loadSingleTexture("items/wool pants.png", 32, 32);

	// SHIELDS
	loadSingleTexture("items/shield.png", 32, 32);	// TO-DO to delete

	// HERBS
	loadSingleTexture("items/mana plant.png", 30, 50);
	loadSingleTexture("items/health herb.png", 32, 34);
	loadSingleTexture("items/health root.png", 31, 46);
	loadSingleTexture("items/health plant.png", 30, 44);
	loadSingleTexture("items/mushroom.png", 30, 44);

	// POTIONS
	loadSingleTexture("items/potion.png", 32, 32);

	// FOOD
	loadSingleTexture("items/raw meat.png", 32, 32);
	loadSingleTexture("items/roasted meat.png", 32, 32);

	// OTHERS
	loadSingleTexture("items/bone.png", 32, 32);
	loadSingleTexture("items/bone.png", 40, 40);
	loadSingleTexture("items/tooth.png", 32, 32);
	loadSingleTexture("items/spike.png", 32, 32);
	loadSingleTexture("items/wolf skin.png", 32, 32);

	// DOORS ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	loadSingleTexture("doors/wooden_door[0].png", 32, 32);
	loadSingleTexture("doors/wooden_door[1].png", 32, 32);
	loadSingleTexture("doors/wooden_door[2].png", 32, 32);
	loadSingleTexture("doors/wooden_door[3].png", 32, 32);

	loadSingleTexture("doors/wooden_gate[0].png", 64, 112);
	loadSingleTexture("doors/wooden_gate[1].png", 64, 112);
	loadSingleTexture("doors/wooden_gate[2].png", 64, 112);
	loadSingleTexture("doors/wooden_gate[3].png", 64, 112);

	// MONSTERS ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	std::vector < string > monsters;

	monsters.push_back("dziobak");
	monsters.push_back("goblin");
	monsters.push_back("wilczur");
	monsters.push_back("jaszczur");
	monsters.push_back("niedzwiedz");
	monsters.push_back("szpon");
	monsters.push_back("kolcorozec");
	monsters.push_back("golem");
	monsters.push_back("troll");
	monsters.push_back("bies");

	for (auto& m : monsters) {
		for (short i = 0; i < 4; i++) {

			loadSingleTexture("monsters/" + m + ".png", 63, 87);

			loadSingleTexture("monsters/" + m + "/idleTop" + to_string(i) + ".png", 63, 87);
			loadSingleTexture("monsters/" + m + "/idleRight" + to_string(i) + ".png", 63, 87);
			loadSingleTexture("monsters/" + m + "/idleBottom" + to_string(i) + ".png", 63, 87);
			loadSingleTexture("monsters/" + m + "/idleLeft" + to_string(i) + ".png", 63, 87);

			loadSingleTexture("monsters/" + m + "/attackTop" + to_string(i) + ".png", 63, 87);
			loadSingleTexture("monsters/" + m + "/attackRight" + to_string(i) + ".png", 63, 87);
			loadSingleTexture("monsters/" + m + "/attackBottom" + to_string(i) + ".png", 63, 87);
			loadSingleTexture("monsters/" + m + "/attackLeft" + to_string(i) + ".png", 63, 87);

			loadSingleTexture("monsters/" + m + "/runTop" + to_string(i) + ".png", 63, 87);
			loadSingleTexture("monsters/" + m + "/runRight" + to_string(i) + ".png", 63, 87);
			loadSingleTexture("monsters/" + m + "/runBottom" + to_string(i) + ".png", 63, 87);
			loadSingleTexture("monsters/" + m + "/runLeft" + to_string(i) + ".png", 63, 87);

		}
	}

	// FURNITURES
	loadSingleTexture("furnitures/table.png", 32, 32);
	loadSingleTexture("furnitures/table_alchemist.png", 32, 32);
	loadSingleTexture("furnitures/table_alchemist_2.png", 32, 32);
	loadSingleTexture("furnitures/table_herbalist.png", 32, 32);
	loadSingleTexture("furnitures/table_herbalist_2.png", 32, 32);
	loadSingleTexture("furnitures/bench.png", 32, 32);
	loadSingleTexture("furnitures/chest.png", 32, 32);
	loadSingleTexture("furnitures/wardrobe.png", 32, 50);
	loadSingleTexture("furnitures/bookshelf.png", 32, 50);
	loadSingleTexture("furnitures/furnace.png", 32, 50);
	loadSingleTexture("furnitures/bed.png", 32, 50);
	loadSingleTexture("furnitures/chair.png", 34, 38);
	loadSingleTexture("furnitures/barrel.png", 34, 38);
	loadSingleTexture("furnitures/shield_1.png", 32, 32);
	loadSingleTexture("furnitures/shield_2.png", 32, 32);
	loadSingleTexture("furnitures/shield_3.png", 32, 32);
	loadSingleTexture("furnitures/lectern.png", 34, 38);


	// WALLS
	loadSingleTexture("walls/empty_wall.png", 16, 16);

	loadSingleTexture("walls/mud_wall.png", 16, 16);
	loadSingleTexture("walls/stone_wall.png", 16, 16);
	loadSingleTexture("walls/wooden_wall.png", 16, 16);
	loadSingleTexture("walls/brick_wall.png", 16, 16);
	loadSingleTexture("walls/mulch_wall.png", 16, 16);

	loadSingleTexture("walls/mud_wall_overgrown.png", 16, 16);
	loadSingleTexture("walls/stone_wall_overgrown.png", 16, 16);
	loadSingleTexture("walls/wooden_wall_overgrown.png", 16, 16);
	loadSingleTexture("walls/brick_wall_overgrown.png", 16, 16);
	loadSingleTexture("walls/mulch_wall_overgrown.png", 16, 16);


	loadTextureSets("walls/set_mud_wall", 32, 32, 16, 16);
	loadTextureSets("walls/set_stone_wall", 32, 32, 16, 16);
	loadTextureSets("walls/set_wooden_wall", 32, 32, 16, 16);
	loadTextureSets("walls/set_brick_wall", 32, 32, 16, 16);
	loadTextureSets("walls/set_mulch_wall", 32, 32, 16, 16);

	// FORTIFICATIONS
	loadSingleTexture("fortifications/fortified_gate.png", 64, 112);
	loadTextureSets("fortifications/fortified_wall", 32, 32, 16, 16);

	// BODY SETS
	std::vector < string > bodySets;
	bodySets.clear();
	bodySets.push_back("boy-redhaired");		// face without beard
	bodySets.push_back("boy-blackhaired");		// face without beard
	bodySets.push_back("boy-brownhaired");		// face without beard
	bodySets.push_back("boy-greyhaired");		// face without beard

	bodySets.push_back("man-redhaired");		// face have a beard
	bodySets.push_back("man-blackhaired");		// face have a beard
	bodySets.push_back("man-brownhaired");		// face have a beard
	bodySets.push_back("man-greyhaired");		// face have a beard

	bodySets.push_back("woman-redhaired");		// face with long hair
	bodySets.push_back("woman-blackhaired");	// face with long hair
	bodySets.push_back("woman-brownhaired");	// face with long hair
	bodySets.push_back("woman-greyhaired");	// face with long hair


	for (auto& set : bodySets) {
		for (short i = 0; i < 4; i++) {

			loadSingleTexture("sets/body/" + set + "/idleTop" + to_string(i) + ".png", 32, 58);
			loadSingleTexture("sets/body/" + set + "/idleRight" + to_string(i) + ".png", 32, 58);
			loadSingleTexture("sets/body/" + set + "/idleBottom" + to_string(i) + ".png", 32, 58);
			loadSingleTexture("sets/body/" + set + "/idleLeft" + to_string(i) + ".png", 32, 58);

			loadSingleTexture("sets/body/" + set + "/runTop" + to_string(i) + ".png", 32, 58);
			loadSingleTexture("sets/body/" + set + "/runRight" + to_string(i) + ".png", 32, 58);
			loadSingleTexture("sets/body/" + set + "/runBottom" + to_string(i) + ".png", 32, 58);
			loadSingleTexture("sets/body/" + set + "/runLeft" + to_string(i) + ".png", 32, 58);

			loadSingleTexture("sets/body/" + set + "/attackTop" + to_string(i) + ".png", 32, 58);
			loadSingleTexture("sets/body/" + set + "/attackRight" + to_string(i) + ".png", 32, 58);
			loadSingleTexture("sets/body/" + set + "/attackBottom" + to_string(i) + ".png", 32, 58);
			loadSingleTexture("sets/body/" + set + "/attackLeft" + to_string(i) + ".png", 32, 58);

		}
	}


	// ITEMS SETS
	std::vector < string > itemSets;
	itemSets.clear();
	itemSets.push_back("skin jacket");
	itemSets.push_back("skin pants");
	itemSets.push_back("skin helmet");
	itemSets.push_back("torn shirt");
	itemSets.push_back("wool shirt");
	itemSets.push_back("wool hat");
	itemSets.push_back("wool pants");
	itemSets.push_back("wooden club");
	itemSets.push_back("axe");
	itemSets.push_back("club");
	itemSets.push_back("iron club");
	itemSets.push_back("stone hammer");
	itemSets.push_back("sword");
	itemSets.push_back("long sword");
	itemSets.push_back("gladius");
	itemSets.push_back("wide blade");
	itemSets.push_back("knife");
	itemSets.push_back("dagger");
	itemSets.push_back("hatchet");
	itemSets.push_back("curved sword");
	itemSets.push_back("chain mail");
	itemSets.push_back("chain mail pants");
	itemSets.push_back("plate armor");
	itemSets.push_back("shield");



	for (auto& set : itemSets) {

		for (short i = 0; i < 4; i++) {

			loadSingleTexture("sets/items/" + set + "/idleTop" + to_string(i) + ".png", 32, 58);
			loadSingleTexture("sets/items/" + set + "/idleRight" + to_string(i) + ".png", 32, 58);
			loadSingleTexture("sets/items/" + set + "/idleBottom" + to_string(i) + ".png", 32, 58);
			loadSingleTexture("sets/items/" + set + "/idleLeft" + to_string(i) + ".png", 32, 58);

			loadSingleTexture("sets/items/" + set + "/runTop" + to_string(i) + ".png", 32, 58);
			loadSingleTexture("sets/items/" + set + "/runRight" + to_string(i) + ".png", 32, 58);
			loadSingleTexture("sets/items/" + set + "/runBottom" + to_string(i) + ".png", 32, 58);
			loadSingleTexture("sets/items/" + set + "/runLeft" + to_string(i) + ".png", 32, 58);

			loadSingleTexture("sets/items/" + set + "/attackTop" + to_string(i) + ".png", 32, 58);
			loadSingleTexture("sets/items/" + set + "/attackRight" + to_string(i) + ".png", 32, 58);
			loadSingleTexture("sets/items/" + set + "/attackBottom" + to_string(i) + ".png", 32, 58);
			loadSingleTexture("sets/items/" + set + "/attackLeft" + to_string(i) + ".png", 32, 58);

		}
	}

	// BUILDING PARTS
	loadSingleTexture("buildings/parts/logo.png", 16, 16);

	loadSingleTexture("buildings/parts/tile_left.png", 8, 8);
	loadSingleTexture("buildings/parts/tile_left_top.png", 8, 4);
	loadSingleTexture("buildings/parts/tile_left_bottom.png", 8, 4);
	loadSingleTexture("buildings/parts/tile_right.png", 8, 8);
	loadSingleTexture("buildings/parts/tile_right_top.png", 8, 4);
	loadSingleTexture("buildings/parts/tile_right_bottom.png", 8, 4);
	loadSingleTexture("buildings/parts/tile_center.png", 8, 8);
	loadSingleTexture("buildings/parts/tile_center_top.png", 8, 4);
	loadSingleTexture("buildings/parts/tile_center_bottom.png", 8, 4);


	loadSingleTexture("buildings/parts/roof.png", 32, 32);
	loadSingleTexture("buildings/parts/roof2.png", 8, 8);
	loadSingleTexture("buildings/parts/window.png", 16, 16);
	loadSingleTexture("buildings/parts/window_2.png", 16, 16);
	loadSingleTexture("buildings/parts/bar.png", 32, 5);


}



#endif