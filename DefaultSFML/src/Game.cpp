#include "Game.h"


Game::Game()
{
}

Game::Game(const char dir[])
{
	loadLevel(dir);
}

void Game::loadLevel(const char dir[])
{
	tinyxml2::XMLDocument levelFile;
	levelFile.LoadFile(dir);

	for (tinyxml2::XMLNode* child = levelFile.FirstChild(); child != NULL; child = child->NextSibling())
	{
		const char* Value = child->Value();
		
		if (strcmp(Value, "Car") == 0)
		{
			for (tinyxml2::XMLNode* child2 = child->FirstChild(); child2 != NULL; child2 = child2->NextSiblingElement())
			{
				Value = child2->Value();
				spawnCar(Value);

			}

		}
					
	}	
}


void Game::spawnCar(const char dir[])
{
	
	m_vCars.push_back(Car(Vector2f(400, 400), Vector2f(100, 250), dir));
}

