#ifndef TerrainAndFloors_hpp
#define TerrainAndFloors_hpp

float tileSide = 16.0f;

class TerrainPrefab : public GameObject {
public:
	short id;

	TerrainPrefab(std::wstring name, short id) : GameObject(name) {
		type = GameObjectType::Terrain;
		texture = getSingleTexture(name);
		this->id = id;

		colliders[0]->shape->setPosition(position);
	}

	virtual ~TerrainPrefab() {

	}

	virtual void update(float dt) {
		sf::Vector2f position;
		position.x = int(worldMousePosition.x) / int(tileSide) * int(tileSide);
		position.y = int(worldMousePosition.y) / int(tileSide) * int(tileSide);
	}

	virtual void draw() {
		renderer->getTheCurrentFrame()->draw(*colliders[0]->shape);
	}

};

class FloorPrefab : public GameObject {
public:
	short id;

	FloorPrefab(std::wstring name, short id) : GameObject(name) {
		type = GameObjectType::Floor;
		texture = getSingleTexture(name);
		this->id = id;
	}

	virtual ~FloorPrefab() {

	}

	virtual void update(float dt) {
		sf::Vector2f position;
		position.x = int(worldMousePosition.x) / int(tileSide) * int(tileSide);
		position.y = int(worldMousePosition.y) / int(tileSide) * int(tileSide);

		colliders[0]->shape->setPosition(position);

	}

	virtual void draw() {
		renderer->getTheCurrentFrame()->draw(*colliders[0]->shape);
	}

};


short countOfBasicTerrain;
std::vector < TerrainPrefab* > terrainGameObjects;
std::vector < FloorPrefab* > floorGameObjects;



class Terrain : public sf::Drawable, public sf::Transformable {
public:
	short width, height;		// normal is a 16x16
	sf::Vector2i coords;		// multiply by 16x16
	sf::VertexArray vertexes;	// vertexes of tiles
	SingleTexture* tileset;			// main texture
	std::vector < short > tiles;// tile values

	Terrain(short x, short y, short width, short height) {

		coords.x = x;
		coords.y = y;

		this->width = width;
		this->height = height;

		tileset = getSingleTexture(L"tiles\\0_tileset");

		tiles.resize(width * height, 2);

		vertexes.setPrimitiveType(sf::Quads);
		vertexes.resize(width * height * 4); // widthMap * heightMap * TwoTrianglesVertices

		short coord_x, coord_y;

		// TERRAIN - GRASS
		for (short y = 0; y < height; y++)
			for (short x = 0; x < width; x++) {

				sf::Vertex* quad = &vertexes[(y * width + x) * 4];

				coord_x = (coords.x + x);
				coord_y = (coords.y + y);

				quad[0].position = sf::Vector2f(coord_x * tileSide, coord_y * tileSide);
				quad[1].position = sf::Vector2f((coord_x + 1) * tileSide, coord_y * tileSide);
				quad[2].position = sf::Vector2f((coord_x + 1) * tileSide, (coord_y + 1) * tileSide);
				quad[3].position = sf::Vector2f(coord_x * tileSide, (coord_y + 1) * tileSide);

				edit(x, y, 2);
			}

	}

	void edit(short x, short y, short value) {

		if (x < 0 || x >= width || y < 0 || y >= height)
			return;

		if (value > terrainGameObjects.size() - 1 || value < 0)
			return;

		tiles[y * width + x] = value;

		short global_x = coords.x + x;	// 16*x + x
		short global_y = coords.y + y;	// 16*y + y

		sf::Vertex* quad = &vertexes[(y * width + x) * 4];

		short tu = (short(global_x * tileSide) % 64) + (value * 64);
		short tv = (short(global_y * tileSide) % 64);

		//cout << "tu: " << tu << ", tv: " << tv << "\n";

		quad[0].texCoords = sf::Vector2f(tu + 1, tv + 1);
		quad[1].texCoords = sf::Vector2f(tu + tileSide - 1, tv + 1);
		quad[2].texCoords = sf::Vector2f(tu + tileSide - 1, tv + tileSide - 1);
		quad[3].texCoords = sf::Vector2f(tu + 1, tv + tileSide - 1);

	}

	void edit(sf::Vector2f worldMousePosition, short value) {

		short coord_x = (worldMousePosition.x - coords.x * 16) / 16;
		short coord_y = (worldMousePosition.y - coords.y * 16) / 16;

		if (coord_x < 0 || coord_x >= width || coord_y < 0 || coord_y >= height)
			return;

		if (value > terrainGameObjects.size() - 1 || value < 0)
			return;

		tiles[coord_y * width + coord_x] = short(value);

		sf::Vertex* quad = &vertexes[(coord_y * width + coord_x) * 4];

		short tu = (short(abs(coord_x) * tileSide) % 64) + (value * 64);
		short tv = (short(abs(coord_y) * tileSide) % 64);

		//cout << "tu: " << tu << ", tv: " << tv << "\n";


		quad[0].texCoords = sf::Vector2f(tu + 1, tv + 1);
		quad[1].texCoords = sf::Vector2f(tu + tileSide - 1, tv + 1);
		quad[2].texCoords = sf::Vector2f(tu + tileSide - 1, tv + tileSide - 1);
		quad[3].texCoords = sf::Vector2f(tu + 1, tv + tileSide - 1);


	}

	void setPosition(sf::Vector2f position) {

		coords.x = position.x / 16;
		coords.y = position.y / 16;

		short coord_x, coord_y;

		for (short y = 0; y < height; y++)
			for (short x = 0; x < width; x++) {

				sf::Vertex* quad = &vertexes[(y * width + x) * 4];

				coord_x = (coords.x + x);
				coord_y = (coords.y + y);

				quad[0].position = sf::Vector2f(coord_x * tileSide, coord_y * tileSide);
				quad[1].position = sf::Vector2f((coord_x + 1) * tileSide, coord_y * tileSide);
				quad[2].position = sf::Vector2f((coord_x + 1) * tileSide, (coord_y + 1) * tileSide);
				quad[3].position = sf::Vector2f(coord_x * tileSide, (coord_y + 1) * tileSide);
			}
	}

private:

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		// draw tiles - terrain
		states.transform *= getTransform();
		states.texture = &*tileset->texture;	// TO-DO
		target.draw(vertexes, states);

	}
};


class Floors : public sf::Drawable, public sf::Transformable {
public:
	short width, height;
	sf::Vector2i coords;

	sf::VertexArray vertexes;
	SingleTexture* floorset;	// TO-DO

	std::vector < short > floors;

	Floors(short x, short y, short width, short height) {

		coords.x = x;
		coords.y = y;

		this->width = width;
		this->height = height;

		floorset = getSingleTexture(L"floors\\0_floorset");

		vertexes.setPrimitiveType(sf::Quads);
		vertexes.resize(width * height * 4); // widthMap * heightMap * TwoTrianglesVertices

		floors.resize(width * height);

		short coord_x, coord_y;

		for (short y = 0; y < height; y++)
			for (short x = 0; x < width; x++) {

				sf::Vertex* quad = &vertexes[(y * width + x) * 4];

				coord_x = (coords.x + x);
				coord_y = (coords.y + y);

				quad[0].position = sf::Vector2f(coord_x * tileSide, coord_y * tileSide);
				quad[1].position = sf::Vector2f((coord_x + 1) * tileSide, coord_y * tileSide);
				quad[2].position = sf::Vector2f((coord_x + 1) * tileSide, (coord_y + 1) * tileSide);
				quad[3].position = sf::Vector2f(coord_x * tileSide, (coord_y + 1) * tileSide);

				edit(x, y, 0);
			}
	}

	Floors(Floors* flo) {
		coords.x = flo->coords.x;
		coords.y = flo->coords.y;

		this->width = flo->width;
		this->height = flo->height;

		floorset = getSingleTexture(L"floors\\0_floorset");

		vertexes.setPrimitiveType(sf::Quads);
		vertexes.resize(width * height * 4); // widthMap * heightMap * TwoTrianglesVertices

		floors.resize(width * height);

		short coord_x, coord_y;

		for (short y = 0; y < height; y++)
			for (short x = 0; x < width; x++) {

				sf::Vertex* quad = &vertexes[(y * width + x) * 4];

				coord_x = (coords.x + x);
				coord_y = (coords.y + y);

				quad[0].position = sf::Vector2f(coord_x * tileSide, coord_y * tileSide);
				quad[1].position = sf::Vector2f((coord_x + 1) * tileSide, coord_y * tileSide);
				quad[2].position = sf::Vector2f((coord_x + 1) * tileSide, (coord_y + 1) * tileSide);
				quad[3].position = sf::Vector2f(coord_x * tileSide, (coord_y + 1) * tileSide);

				edit(x, y, flo->floors[y * width + x]);
			}
	}

	void edit(short x, short y, short value) {

		if (x < 0 || x >= width || y < 0 || y >= height)
			return;

		if (value > floorGameObjects.size() - 1 || value < 0)
			return;

		floors[y * width + x] = value;

		short global_x = coords.x + x;
		short global_y = coords.y + y;

		sf::Vertex* quad = &vertexes[(y * width + x) * 4];

		short tu = (short(abs(global_x) * tileSide) % 64) + (value * 64);
		short tv = (short(abs(global_y) * tileSide) % 64);

		//cout << "tu: " << tu << ", tv: " << tv << "\n";

		quad[0].texCoords = sf::Vector2f(tu, tv);
		quad[1].texCoords = sf::Vector2f(tu + tileSide, tv);
		quad[2].texCoords = sf::Vector2f(tu + tileSide, tv + tileSide);
		quad[3].texCoords = sf::Vector2f(tu, tv + tileSide);
	}

	void edit(sf::Vector2f worldMousePosition, short value) {

		short coord_x = (worldMousePosition.x - coords.x * width) / 16;
		short coord_y = (worldMousePosition.y - coords.y * height) / 16;

		if (coord_x < 0 || coord_x >= width || coord_y < 0 || coord_y >= height)
			return;

		if (value > floorGameObjects.size() - 1 || value < 0)
			return;

		floors[coord_y * width + coord_x] = value;

		sf::Vertex* quad = &vertexes[(coord_y * width + coord_x) * 4];

		short tu = (short(coord_x * tileSide) % 64) + (value * 64);
		short tv = (short(coord_y * tileSide) % 64);

		//cout << "tu: " << tu << ", tv: " << tv << "\n";

		quad[0].texCoords = sf::Vector2f(tu, tv);
		quad[1].texCoords = sf::Vector2f(tu + tileSide, tv);
		quad[2].texCoords = sf::Vector2f(tu + tileSide, tv + tileSide);
		quad[3].texCoords = sf::Vector2f(tu, tv + tileSide);
	}

	void setPosition(sf::Vector2f position) {

		coords.x = position.x / 16;
		coords.y = position.y / 16;

		short coord_x, coord_y;

		for (short y = 0; y < height; y++)
			for (short x = 0; x < width; x++) {

				sf::Vertex* quad = &vertexes[(y * width + x) * 4];

				coord_x = (coords.x + x);
				coord_y = (coords.y + y);

				quad[0].position = sf::Vector2f(coord_x * tileSide, coord_y * tileSide);
				quad[1].position = sf::Vector2f((coord_x + 1) * tileSide, coord_y * tileSide);
				quad[2].position = sf::Vector2f((coord_x + 1) * tileSide, (coord_y + 1) * tileSide);
				quad[3].position = sf::Vector2f(coord_x * tileSide, (coord_y + 1) * tileSide);
			}
	}

private:

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const
	{

		states.transform *= getTransform();
		states.texture = &*floorset->texture;	// TO-DO
		target.draw(vertexes, states);


	}
};

Terrain* terrain;

void createTerrainPrefabs() {

	terrainGameObjects.clear();

	terrainGameObjects.push_back(new TerrainPrefab(L"tiles\\water", 0));           // 1
	terrainGameObjects.push_back(new TerrainPrefab(L"tiles\\sands", 1));           // 2
	terrainGameObjects.push_back(new TerrainPrefab(L"tiles\\grass", 2));           // 3
	terrainGameObjects.push_back(new TerrainPrefab(L"tiles\\gravel", 3));           // 4
	terrainGameObjects.push_back(new TerrainPrefab(L"tiles\\steps", 4));           // 5
	terrainGameObjects.push_back(new TerrainPrefab(L"tiles\\highlands", 5));       // 6
	terrainGameObjects.push_back(new TerrainPrefab(L"tiles\\tile_6", 6));                 // 7
	terrainGameObjects.push_back(new TerrainPrefab(L"tiles\\tile_7", 7));                 // 8
	terrainGameObjects.push_back(new TerrainPrefab(L"tiles\\tile_8", 8));                 // 9
	terrainGameObjects.push_back(new TerrainPrefab(L"tiles\\tile_9", 9));                 // 10
	terrainGameObjects.push_back(new TerrainPrefab(L"tiles\\tile_10", 10));               // 11

	countOfBasicTerrain = terrainGameObjects.size();

	std::vector < std::wstring > sets_names;
	sets_names.push_back(L"tiles\\set_0_water_sands");
	sets_names.push_back(L"tiles\\set_0_sands_water");
	sets_names.push_back(L"tiles\\set_1_sands_grass");
	sets_names.push_back(L"tiles\\set_1_grass_sands");
	sets_names.push_back(L"tiles\\set_2_grass_gravel");
	sets_names.push_back(L"tiles\\set_2_gravel_grass");

	short id = countOfBasicTerrain;

	for (auto& texture : singleTextures) {
		for (auto& name : sets_names) {
			if (texture->name.find(name) != std::string::npos) {

				TerrainPrefab* tpref = new TerrainPrefab(texture->name, id);
				terrainGameObjects.push_back(tpref);
				//cout << tpref->name << "\t" << id << "\n";
				id += 1;
			}
		}
	}


	// create tileset
	sf::RenderTexture rtex;
	rtex.create(id * 64, 64);
	rtex.clear(sf::Color::Transparent);

	short offsetX = 0;

	for (auto& t : terrainGameObjects) {
		sf::Texture tex = *dynamic_cast<TerrainPrefab*>(t)->texture->texture;
		sf::Sprite spr(tex);
		spr.setPosition(offsetX, 0);
		rtex.draw(spr);
		offsetX += 64;
	}
	rtex.display();

	sf::Texture tileset = rtex.getTexture();
	*getSingleTexture(L"tiles\\0_tileset")->texture = tileset;

}

void createFloorsPrefabs() {
	floorGameObjects.clear();
	floorGameObjects.push_back(new FloorPrefab(L"floors\\floor_0", 0));
	floorGameObjects.push_back(new FloorPrefab(L"floors\\floor_1", 1));
	floorGameObjects.push_back(new FloorPrefab(L"floors\\floor_2", 2));
	floorGameObjects.push_back(new FloorPrefab(L"floors\\floor_3", 3));
	floorGameObjects.push_back(new FloorPrefab(L"floors\\floor_4", 4));
	floorGameObjects.push_back(new FloorPrefab(L"floors\\floor_5", 5));

}


#endif