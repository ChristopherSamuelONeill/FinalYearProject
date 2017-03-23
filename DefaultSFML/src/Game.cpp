#include "Game.h"

Game::Game()
{
}

Game::Game(string dir)
{
		
	m_Gametextures.loadTextures();
	
	//set up a blank senerio
	if (dir == "./Assets/Levels/Editor.txt")
	{
		cout << "Editor Mode" << endl;
		m_iCurrentBackground = 0;
		m_sfLevelSize = Vector2f(5333,3000);
		m_sfLevelSize *= 2.0f;
		m_iLevelSize = 0;
		m_iLevelTime = 0;
		m_Background = SceneObject(Vector2f(0, 0), m_sfLevelSize, m_Gametextures.m_vBackgroundTextures[0] , 0.0f);
		m_Time = SceneObject(Vector2f(0, 0), m_sfLevelSize, m_Gametextures.m_vTimeTextures[0], 0.0f);
	}
	else // load level
	{
		loadLevel(dir);
	}
	
	generateSnapGrid();
}

void Game::loadLevel(string dir)
{
	fstream file;
	string lineData;
	string temp;

	file.open("Assets/Levels/" + dir +".txt");
	if (file.is_open())
	{
		while (getline(file, lineData))
		{
			istringstream settings(lineData);
			settings.str(lineData);
			settings >> temp;
			if (temp == "c")
			{
				//ingore . this line is a commen
			}
			else if (temp == "LevelSize")
			{
				float x;
				float y;
				settings >> x >> y;
				m_sfLevelSize = Vector2f(x, y);

			}
			else if (temp == "Background")
			{

				int i;
				settings >> i;
				m_Background = SceneObject(Vector2f(0, 0), m_sfLevelSize, m_Gametextures.m_vBackgroundTextures[i], 0.0f, "Background");
				
			}
			else if (temp == "Time")
			{
				int i;
				settings >> i;
				m_Time = SceneObject(Vector2f(0, 0), m_sfLevelSize, m_Gametextures.m_vTimeTextures[i], 0.0f);

			}
			else if (temp == "Road")
			{
				float px;
				float py;
				float sx;
				float sy;
				float rot;
				string type;

				settings >> px >> py >> sx >> sy >> rot >> type;

				Vector2f position(px, py);
				Vector2f size(sx, sy);

				Road tempRoad;
				if (type == "T - Junction")tempRoad = Road(position, size, rot, m_Gametextures.m_vTJunctionTextures[1]);
				if (type == "Normal Road")tempRoad = Road(position, size, rot, m_Gametextures.m_vTwoWayStreetTextures[1]);

						

			}
			
		}
	}
	else
	{
		cout << "Couldnt Open file ... Assets/profiles/" << location << endl;
	}

	file.close();
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

	//update road
	for (int i = 0; i < m_vRoads.size(); i++)
	{
		m_vRoads[i].update();
	}

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

	//draw the road
	for (int i = 0; i < m_vRoads.size(); i++)
	{
		window.draw(m_vRoads[i]);
	}

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

	

	//draw temp object
	if (m_bPlacingObject)window.draw(m_sfTempSprite);
	if (m_bPlacingObject)window.draw(m_sfTempRect);
	

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

	//string sName;

	//if (m_iLevelTime == 0)sName = "GreenGrass";
	//if (m_iLevelTime == 1)sName = "YellowGrass";
	//if (m_iLevelTime == 2)sName = "GreySand";
	//if (m_iLevelTime == 3)sName = "YellowSand";
	//if (m_iLevelTime == 4)sName = "Concrete";
	//if (m_iLevelTime == 5)sName = "Dirt";

	m_Background.setTexture(m_Gametextures.m_vBackgroundTextures[m_iCurrentBackground], "");
}

 void Game::cycleLevelSize()
{
	m_iLevelSize++;

	if (m_iLevelSize == 6)
	{
		m_iLevelSize = 0;
	}

	m_sfLevelSize = Vector2f(5300 + m_iLevelSize * 3500, 3000 + m_iLevelSize * 2000);
	m_sfLevelSize *= 2.0f;
	m_Background.setSize(m_sfLevelSize);
	generateSnapGrid();
}

void Game::cycleLevelTime()
{
	m_iLevelTime++;
	if (m_iLevelTime == m_Gametextures.m_vTimeTextures.size() )
	{
		m_iLevelTime = 0;
	}
	/*string sName;

	if (m_iLevelTime == 0)sName = "Normal";
	if (m_iLevelTime == 1)sName = "Day";
	if (m_iLevelTime == 2)sName = "Summer";
	if (m_iLevelTime == 3)sName = "Evening";
	if (m_iLevelTime == 4)sName = "Night";
	if (m_iLevelTime == 5)sName = "Winter";*/


	m_Time.setTexture(m_Gametextures.m_vTimeTextures[m_iLevelTime],"");
}

void Game::saveLevelToFile(string dir)
{
	//load list list
	vector<string> LevelNames;
	fstream file;
	ofstream ofile;

	ofstream onewFile;

	string tempLevel;
	string lineData;

	file.open("Assets/Levels/LevelList.txt");


	if (file.is_open())
	{
		while (getline(file, lineData))
		{
			istringstream iss(lineData);
			iss.str(lineData);
			iss >> tempLevel;
			LevelNames.push_back(tempLevel);
		}

	}

	file.close();

	ofile.open("Assets/Levels/LevelList.txt");
	// add new player to list
	LevelNames.push_back(dir + ".txt");

	for (int i = 0; i < LevelNames.size(); i++)
	{
		ofile << LevelNames[i] << endl;
	}

	//create name .txt file

	onewFile.open("Assets/Levels/" + dir + ".txt");
	if (onewFile.is_open())
	{
		//save the level Size
		onewFile << "c" << "Scale X " << "Scale Y " << endl;
		onewFile << "Level Size" << m_sfLevelSize.x << " " << m_sfLevelSize.y << endl;

		//save the background
		onewFile << "c" << "Texture Number" << endl;
		onewFile << "Background" << m_iCurrentBackground << endl;

		//save the time
		onewFile << "c" << "Texture Number" << endl;
		onewFile << "Time" << m_iLevelTime << endl;


		//save the Roads
		for (int i = 0; i < m_vRoads.size(); i++)
		{
			onewFile << "c" << "Pos X " << "Pos Y " << "Scale x " << "Scale y "<< "Rotation " << "Type " << endl;
			onewFile << "Road" << m_vRoads[i].getPosition().x << " " << m_vRoads[i].getPosition().y << " " << m_vRoads[i].getSize().x << " " << m_vRoads[i].getSize().y << " " << m_vRoads[i].getRotation() << " " << m_vRoads[i].getType() <<  endl;
		}
	
		
	}
	onewFile.close();
	
	


}

void Game::spawnTempObject(Vector2f position, float rot, string type)
{

	//snap to nearest grid
	Vector2f sfSnappedPos;

	for (int i = 0; i < m_vGridSystem.size(); i++)
	{
		//find the distance from nearest the road to every grid
		Vector2f dist = m_vGridSystem[i] - position;
		float mag = sqrt(dist.x * dist.x + dist.y * dist.y);
		if (mag < 50)
		{
			sfSnappedPos = m_vGridSystem[i];
			i = m_vGridSystem.size();
		}

	}

	Road tempRoad;
	if (type == "T - Junction")tempRoad = Road(sfSnappedPos, Vector2f(2500, 1500), rot, m_Gametextures.m_vTJunctionTextures[0]);
	if (type == "Normal Road")tempRoad = Road(sfSnappedPos, Vector2f(500, 1000), rot, m_Gametextures.m_vTwoWayStreetTextures[0]);

	bool valid = true;

	//check if the new road is in the level
	if (sfSnappedPos.x > m_sfLevelSize.x)valid = false;
	else if (sfSnappedPos.x <= 0)valid = false;
	else if (sfSnappedPos.y <= 0)valid = false;
	else if (sfSnappedPos.y > m_sfLevelSize.y)valid = false;

	CollisionDetection test;


	//check the road doesnt overlap with any other roads
	for (int i = 0; i < m_vRoads.size(); i++)
	{
		if (test(tempRoad.getCollisionBox(), m_vRoads[i].getCollisionBox()) == true)
		{
			//did not place due to overlap
			valid = false;
		}
	}

	//set up drawbales
	m_sfTempRect.setPosition(sfSnappedPos);
	if(valid)m_sfTempRect.setFillColor(Color(0,255,0,125));
	if (!valid)m_sfTempRect.setFillColor(Color(255, 0, 0, 125));
	m_sfTempRect.setSize(Vector2f(500,500));
	m_sfTempRect.setRotation(rot);

	
	if (type == "Traffic Light")
	{
		m_sfSize = Vector2f(800, 600);
		m_sfTempRect.setSize(m_sfSize);
		m_sfTempTexture = m_Gametextures.m_vTrafficLightTextures[0];
		
	}
	if (type == "Pedestrian Light")
	{
		m_sfSize = Vector2f(800, 600);
		m_sfTempRect.setSize(m_sfSize);
		m_sfTempTexture = m_Gametextures.m_vPedestrianLightTextures[0];
		
	}
	if (type == "Normal Road")
	{
		
		m_sfSize = Vector2f(500, 1000);
		m_sfTempRect.setSize(m_sfSize);
		m_sfTempTexture = m_Gametextures.m_vTwoWayStreetTextures[1];

		
		
	}
	if (type == "T - Junction")
	{
		m_sfSize = Vector2f(2500, 1500);
		m_sfTempRect.setSize(m_sfSize);
		m_sfTempTexture = m_Gametextures.m_vTJunctionTextures[1];

	}
	
	m_sfTempSprite.setPosition(sfSnappedPos);
	m_sfTempSprite.setTexture(m_sfTempTexture);
	m_sfTempSprite.setRotation(rot);
	

}

bool Game::placeRoad(Vector2f position, float rot,string type)
{
	
	//snap to nearest grid
	Vector2f sfSnappedPos;

	for (int i = 0; i < m_vGridSystem.size(); i++)
	{
		//find the distance from nearest the road to every grid
		Vector2f dist = m_vGridSystem[i] - position;
		float mag = sqrt(dist.x * dist.x + dist.y * dist.y);
		if (mag < 50)
		{
			sfSnappedPos = m_vGridSystem[i];
			i = m_vGridSystem.size();
			
		}
	}


	Road tempRoad;
	if (type == "T - Junction")tempRoad = Road(sfSnappedPos, Vector2f(2500, 1500), rot, m_Gametextures.m_vTJunctionTextures[0]);
	if (type == "Normal Road")tempRoad = Road(sfSnappedPos, Vector2f(500, 1000), rot, m_Gametextures.m_vTwoWayStreetTextures[0]);

	//check if the new road is in the level
	if (sfSnappedPos.x > m_sfLevelSize.x)return false;
	else if (sfSnappedPos.x <= 0)return false;
	else if (sfSnappedPos.y <= 0)return false;
	else if (sfSnappedPos.y > m_sfLevelSize.y)return false;

	CollisionDetection test;


	//check the road doesnt overlap with any other roads
	for (int i = 0; i < m_vRoads.size(); i++)
	{
		if (test(tempRoad.getCollisionBox(), m_vRoads[i].getCollisionBox()) == true)
		{
			//did not place due to overlap
			return false;
		}
	}
	
	//if valid create road
	m_vRoads.push_back(tempRoad);
	m_vRoads[m_vRoads.size() - 1].setType(type);


}

void Game::generateSnapGrid()
{
	cout << "Generating Pathfinding ... ";
	//clear grid (incase of resize)
	m_vGridSystem.clear();

	// loop from 0 to level size in steps of GRIDSIZE
	float fGridSize = 50.0f;

	for (int y = 0; y < m_sfLevelSize.y - fGridSize; y += fGridSize)
	{
		for (int x = 0; x < m_sfLevelSize.x - fGridSize; x += fGridSize)
		{
			m_vGridSystem.push_back(Vector2f(x, y));
			
		}

	}
	cout << "Finished" << endl;

}