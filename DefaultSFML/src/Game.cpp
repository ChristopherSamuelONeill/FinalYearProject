#include "Game.h"


Game::Game()
{
}

Game::Game(const char dir[])
{
	
	m_Gametextures.loadTextures();
	loadLevel(dir);

}

void Game::loadLevel(const char dir[])
{
	tinyxml2::XMLDocument levelFile;
	levelFile.LoadFile(dir);

	for (tinyxml2::XMLNode* child = levelFile.FirstChild(); child != NULL; child = child->NextSibling())
	{
		const char* Value = child->Value();
		
		int model;
		Vector2f pos;
		Vector2f size;

		if (strcmp(Value, "Car") == 0)
		{
			for (tinyxml2::XMLNode* child2 = child->FirstChild(); child2 != NULL; child2 = child2->NextSiblingElement())
			{
				Value = child2->Value();
				if (strcmp(Value, "type") == 0)
				{
					string smodel = child2->ToElement()->GetText();
					model = stoi(smodel);
				}

				if (strcmp(Value, "x") == 0)
				{
					string posx = child2->ToElement()->GetText();
					pos.x = stof(posx);
				}
				if (strcmp(Value, "y") == 0)
				{
					string posy = child2->ToElement()->GetText();
					pos.y = stof(posy);
				}
				
				if (strcmp(Value, "sx") == 0)
				{
					string posSx = child2->ToElement()->GetText();
					size.x = stof(posSx);
				}
				if (strcmp(Value, "sy") == 0)
				{
					string posSy = child2->ToElement()->GetText();
					size.y = stof(posSy);
				}

			}

			spawnCar(model,pos,size);
		}			

		if (strcmp(Value, "Map") == 0)
		{
			for (tinyxml2::XMLNode* child2 = child->FirstChild(); child2 != NULL; child2 = child2->NextSiblingElement())
			{
				Value = child2->Value();
			

				if (strcmp(Value, "x") == 0)
				{
					string posx = child2->ToElement()->GetText();
					pos.x = stof(posx);
				}
				if (strcmp(Value, "y") == 0)
				{
					string posy = child2->ToElement()->GetText();
					pos.y = stof(posy);
				}

			}

			spawnCar(model, pos, size);
		}
	}	
}


void Game::spawnCar(int cartype, Vector2f pos, Vector2f size)
{

	Texture tempTexture[8] = { 
		m_Gametextures.m_vCarColourTextures[cartype] ,
		m_Gametextures.m_vCarLights[0],
		m_Gametextures.m_vCarLights[1],
		m_Gametextures.m_vCarLights[2],
		m_Gametextures.m_vCarLights[3],
		m_Gametextures.m_vCarWheels[0],
		m_Gametextures.m_vCarWheels[1],
		m_Gametextures.m_vCarWheels[2]
	};
	m_vCars.push_back(Car(pos, size, tempTexture));
		
	
}

void Game::updateScene(float dt)
{
	for (int i = 0; i < m_vCars.size(); i++)
	{
		m_vCars[i].update(dt);
	}
}

void Game::drawScene(RenderWindow & window)
{
	for (int i = 0; i < m_vCars.size(); i++)
	{
		window.draw(m_vCars[i]);
	}
}

