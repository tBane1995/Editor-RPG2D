#ifndef Water_hpp
#define Water_hpp

enum class WaterType { Lake, Swamp };

class WaterPrefab : public GameObject {
public:
	short id;
	TerrainPrefab* terrain;
	Shader* shader;

	WaterPrefab(std::wstring name, short id, TerrainPrefab* terrain) : GameObject(name) {
		GameObject::type = GameObjectType::Water;

		this->terrain = terrain;
		this->id = id;

		if (terrain != nullptr)
			texture = terrain->texture;

		shader = getShader(L"shaders\\" + name);

		colliders[0]->shape->setPosition(position);
	}

	virtual ~WaterPrefab() {

	}

	virtual void update() {
		sf::Vector2f position;
		position.x = int(worldMousePosition.x) / int(tileSide) * int(tileSide);
		position.y = int(worldMousePosition.y) / int(tileSide) * int(tileSide);
	}

	virtual void draw() {
		window->draw(*colliders[0]->shape);
	}
};



class Water : public sf::Drawable, public sf::Transformable {
public:
	int width, height;				// normal is a 16x16
	WaterType type;
	sf::Vector2i coords;			// multiply by 16x16
	sf::VertexArray vertexes;		// vertexes of water
	std::vector < short > tiles;	// tiles

	Water(WaterType type, int x, int y, int width, int height) {

		this->type = type;

		coords.x = x;
		coords.y = y;

		this->width = width;
		this->height = height;

		tiles.resize(width * height, -1);
		generate();


	}

	void generate() {
		vertexes.clear();
		vertexes.setPrimitiveType(sf::Triangles);
		for (int y = 0; y < height; y++)
		{
			for (int x = 0; x < width; x++)
			{
				if (tiles[y * width + x] > -1)
				{
					sf::Vertex tile[6];

					int coord_x = (coords.x + x);
					int coord_y = (coords.y + y);

					tile[0].position = sf::Vector2f(coord_x * tileSide, coord_y * tileSide);
					tile[1].position = sf::Vector2f((coord_x + 1) * tileSide, coord_y * tileSide);
					tile[2].position = sf::Vector2f(coord_x * tileSide, (coord_y + 1) * tileSide);
					tile[3].position = sf::Vector2f(coord_x * tileSide, (coord_y + 1) * tileSide);
					tile[4].position = sf::Vector2f((coord_x + 1) * tileSide, coord_y * tileSide);
					tile[5].position = sf::Vector2f((coord_x + 1) * tileSide, (coord_y + 1) * tileSide);

					short tu = (short(coord_x * tileSide) % 64) + ((tiles[y * width + x]) * 64);
					short tv = (short(coord_y * tileSide) % 64);

					tile[0].texCoords = sf::Vector2f(tu, tv);
					tile[1].texCoords = sf::Vector2f(tu + tileSide, tv);
					tile[2].texCoords = sf::Vector2f(tu, tv + tileSide);
					tile[3].texCoords = sf::Vector2f(tu, tv + tileSide);
					tile[4].texCoords = sf::Vector2f(tu + tileSide, tv);
					tile[5].texCoords = sf::Vector2f(tu + tileSide, tv + tileSide);

					for (int i = 0; i < 6; i++)
					{
						vertexes.append(tile[i]);
					}
				}
			}
		}
	}

	void edit(int x, int y, short value = -1) {
		tiles[y * width + x] = value;
		generate();
	}

	void edit(sf::Vector2f worldMousePosition, short value = -1) {

		short coord_x = (worldMousePosition.x - coords.x * 16) / 16;
		short coord_y = (worldMousePosition.y - coords.y * 16) / 16;

		if (coord_x < 0 || coord_x >= width || coord_y < 0 || coord_y >= height)
			return;

		tiles[coord_y * width + coord_x] = value;
		generate();
	}
	void update() {


	}

private:

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		states.transform *= getTransform();
		states.texture = &(*getSingleTexture(L"tiles\\0_tileset")->texture);
		
		if(type == WaterType::Lake)
			states.shader = &(*getShader(L"shaders\\lake")->shader);
		else if(type == WaterType::Swamp)
			states.shader = &(*getShader(L"shaders\\swamp")->shader);
		else
			states.shader = &(*getShader(L"shaders\\lake")->shader);

		target.draw(vertexes, states);
	}
};

std::vector < WaterPrefab* > waterGameObjects;
short countOfBasicWater;

void createWaterPrefabs() {

	waterGameObjects.clear();

	waterGameObjects.push_back(new WaterPrefab(L"empty", 0, nullptr));
	waterGameObjects.push_back(new WaterPrefab(L"palette_lake", 1, terrainGameObjects[0]));
	waterGameObjects.push_back(new WaterPrefab(L"palette_swamp", 2, terrainGameObjects[0]));
	//waterGameObjects.push_back(new WaterPrefab(L"palette_ocean", 3, terrainGameObjects[0]));
	//waterGameObjects.push_back(new WaterPrefab(L"palette_lava", 4, terrainGameObjects[0]));
	countOfBasicWater = 3;

	/////////////////////////////////////////////////////
	for (int i = 1; i < countOfBasicWater; i++) {

		std::wstring shader_name = waterGameObjects[i]->name;

		waterGameObjects.push_back(new WaterPrefab(shader_name, i, terrainGameObjects[countOfBasicTerrain + 0]));
		waterGameObjects.push_back(new WaterPrefab(shader_name, i, terrainGameObjects[countOfBasicTerrain + 1]));
		waterGameObjects.push_back(new WaterPrefab(shader_name, i, terrainGameObjects[countOfBasicTerrain + 2]));
		waterGameObjects.push_back(new WaterPrefab(shader_name, i, terrainGameObjects[countOfBasicTerrain + 3]));
		waterGameObjects.push_back(new WaterPrefab(shader_name, i, terrainGameObjects[countOfBasicTerrain + 4]));
		waterGameObjects.push_back(new WaterPrefab(shader_name, i, terrainGameObjects[countOfBasicTerrain + 5]));
		waterGameObjects.push_back(new WaterPrefab(shader_name, i, terrainGameObjects[countOfBasicTerrain + 6]));
		waterGameObjects.push_back(new WaterPrefab(shader_name, i, terrainGameObjects[countOfBasicTerrain + 7]));

		waterGameObjects.push_back(new WaterPrefab(shader_name, i, terrainGameObjects[countOfBasicTerrain + 8]));
		waterGameObjects.push_back(new WaterPrefab(shader_name, i, terrainGameObjects[countOfBasicTerrain + 9]));
		waterGameObjects.push_back(new WaterPrefab(shader_name, i, terrainGameObjects[countOfBasicTerrain + 10]));
		waterGameObjects.push_back(new WaterPrefab(shader_name, i, terrainGameObjects[countOfBasicTerrain + 11]));
		waterGameObjects.push_back(new WaterPrefab(shader_name, i, terrainGameObjects[countOfBasicTerrain + 12]));
		waterGameObjects.push_back(new WaterPrefab(shader_name, i, terrainGameObjects[countOfBasicTerrain + 13]));
		waterGameObjects.push_back(new WaterPrefab(shader_name, i, terrainGameObjects[countOfBasicTerrain + 14]));
		waterGameObjects.push_back(new WaterPrefab(shader_name, i, terrainGameObjects[countOfBasicTerrain + 15]));

	}


}

#endif