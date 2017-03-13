#include "Game.h"


Game::Game()
{
}

Game::Game(const char dir[])
{
	
	m_Gametextures.loadTextures();
	
	//set up a blank senerio
	if (dir == "./Assets/Levels/Editor.xml")
	{
		cout << "Editor Mode" << endl;
		m_iCurrentBackground = 0;
		m_sfLevelSize = Vector2f(1024 ,1024);
		m_iLevelSize = 0;
		m_iLevelTime = 0;
		m_Background = SceneObject(Vector2f(0, 0), m_sfLevelSize, m_Gametextures.m_vBackgroundTextures[0], 0.0f);
		m_Time = SceneObject(Vector2f(0, 0), m_sfLevelSize, m_Gametextures.m_vTimeTextures[0], 0.0f);
	}
	else // load level
	{
		loadLevel(dir);
	}
	

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

			//spawnCar(model, pos, size);
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

	//update Background
	m_Background.update();

	//update cars
	for (int i = 0; i < m_vCars.size(); i++)
	{
		m_vCars[i].update(dt);
	}

	//update time
	m_Time.setSize(m_sfLevelSize);
	m_Time.update();
}

void Game::drawScene(RenderWindow & window)
{

	//drawBackground
	window.draw(m_Background);

	//draw SceneObjects
	for (int i = 0; i < m_vSceneObejcts.size(); i++)
	{
		window.draw(m_vSceneObejcts[i]);
	}

	//draw cars
	for (int i = 0; i < m_vCars.size(); i++)
	{
		window.draw(m_vCars[i]);
	}

	//draw time of day
	window.draw(m_Time);
}

void Game::cycleBackground()
{

	m_iCurrentBackground++;
	if (m_iCurrentBackground == m_Gametextures.m_vBackgroundTextures.size()-1)
	{
		m_iCurrentBackground = 0;
	}

	m_Background.setTexture(m_Gametextures.m_vBackgroundTextures[m_iCurrentBackground]);
}

void Game::cycleLevelSize()
{
	m_iLevelSize++;

	// 0 - 3000
	// 1 - 5000
	// 2 - 7000
	// 3 - 9000
	// 4 - 11000
	// 5 - 13000
 

	if (m_iLevelSize == 6)
	{
		m_iLevelSize = 0;
	}

	m_sfLevelSize = Vector2f(3000 + m_iLevelSize * 2000, 3000 + m_iLevelSize * 2000);

	std::cout << " P : " << m_sfLevelSize.x / 2.0f << " " <<m_sfLevelSize.y / 2.0f << std::endl;
	std::cout << " S : " << m_sfLevelSize.x << " " << m_sfLevelSize.y << std::endl;

	m_Background.setSize(m_sfLevelSize);
}

void Game::cycleLevelTime()
{
	m_iLevelTime++;
	if (m_iLevelTime == m_Gametextures.m_vTimeTextures.size() )
	{
		m_iLevelTime = 0;
	}

	m_Time.setTexture(m_Gametextures.m_vTimeTextures[m_iLevelTime]);
}

