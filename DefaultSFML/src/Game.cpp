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
		m_sfLevelSize = Vector2f(5333,3000);
		m_sfLevelSize *= 2.0f;
		m_iLevelSize = 0;
		m_iLevelTime = 0;
		m_Background = SceneObject(Vector2f(0, 0), m_sfLevelSize, m_Gametextures.m_vBackgroundTextures[0] , 0.0f, "Background");
		m_Time = SceneObject(Vector2f(0, 0), m_sfLevelSize, m_Gametextures.m_vTimeTextures[0], 0.0f, "Background");
	}
	else // load level
	{
		loadLevel(dir);
	}
	
	generateSnapGrid();
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

void Game::saveLevelToFile(const char dir[])
{
	//create the file
	tinyxml2::XMLDocument levelFile;

	//Create a root node so that objects can easily be added
	tinyxml2::XMLNode * pRoot = levelFile.NewElement("Level");

	//add the root node to the document as a child
	levelFile.InsertFirstChild(pRoot);

	//creat child of root
	tinyxml2::XMLElement * pRootChild = levelFile.NewElement("Scene Object");

	//loop the scene objects
	for (int i = 0; i < m_vSceneObejcts.size(); i++)
	{
		//add a scene object with the following attributes
		pRoot->InsertEndChild(pRootChild);
		pRootChild->SetAttribute("pos x", m_vSceneObejcts[i].m_sfPosition.x);
		pRootChild->SetAttribute("pos y", m_vSceneObejcts[i].m_sfPosition.y);
		pRootChild->SetAttribute("size x", m_vSceneObejcts[i].m_sfSize.x);
		pRootChild->SetAttribute("size y", m_vSceneObejcts[i].m_sfSize.y);
		pRootChild->SetAttribute("Rotation", m_vSceneObejcts[i].m_fRotation);
		//tinyxml2::XMLText * text = m_vSceneObejcts[i].m_sName;
		//pRootChild->SetAttribute("Name",text );
		pRoot->InsertEndChild(pRootChild);

	}

	//add the cars
	pRootChild = levelFile.NewElement("Cars");
	pRoot->InsertEndChild(pRootChild);
	pRootChild->SetAttribute("Number of cars", m_vCars.size());


	pRoot->InsertEndChild(pRootChild);
	//add the root node to the document as a child
	


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