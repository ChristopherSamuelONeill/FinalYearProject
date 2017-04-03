#include "Game.h"

Game::Game()
{
	m_bEditorMode = false;
	m_pathfinderData = new Pathfinding;
	m_Gametextures = TextureObject::getInstance();
	m_Gametextures->loadTextures();
}

Game::Game(string dir)
{
	m_pathfinderData = new Pathfinding;
	startGame(dir);
}

void Game::generateCars()
{
	cout << "Generating "<< m_uiNumbofCars << " cars ... \n";
	for (int i = 0; i < m_uiNumbofCars; i++)
	{
		Texture tempTexture[8] =
		{
			m_Gametextures->m_vCarColourTextures[0],
			m_Gametextures->m_vCarLights[0],
			m_Gametextures->m_vCarLights[1],
			m_Gametextures->m_vCarLights[2],
			m_Gametextures->m_vCarLights[3],
			m_Gametextures->m_vCarWheels[0],
			m_Gametextures->m_vCarWheels[1],
			m_Gametextures->m_vCarWheels[2]

		};

		Car tempCar(m_vCarsStartPostions[0].getPosition() , m_vCarsEndPostions[0].getPosition(), Vector2f(250, 100), tempTexture,270);
		m_vCars.push_back(tempCar);
		m_vCars[i].receiveNodeData(m_pathfinderData);
		m_vCars[i].startPathFinding();

	}
	cout << "Finished" << endl;
}

void Game::generatePedestrians()
{
	cout << "Generating " << m_uiNumbofPed << " pedestrians ... ";
	for (int i = 0; i < m_uiNumbofPed; i++)
	{
		
	}
	cout << "Finished" << endl;
}

void Game::startGame(string dir)
{

	//get singletons
	m_Player = Profile::getInstance();
	m_Gametextures = TextureObject::getInstance();
	//m_Gametextures->loadTextures();
	m_Sound = SoundObject::getInstance();

	//set up a blank senerio
	if (dir == "./Assets/Levels/Editor.txt")
	{
		cout << "Editor Mode" << endl;
		m_iCurrentBackground = 0;
		m_sfLevelSize = Vector2f(5333, 3000);
		m_sfLevelSize *= 2.0f;
		m_iLevelSize = 0;
		m_iLevelTime = 0;
		m_Background = SceneObject(Vector2f(0, 0), m_sfLevelSize, m_Gametextures->m_vBackgroundTextures[0], 0.0f);
		m_Time = SceneObject(Vector2f(0, 0), m_sfLevelSize, m_Gametextures->m_vTimeTextures[0], 0.0f);
		m_bEditorMode = true;
	}
	else // load level
	{
		loadLevel(dir);
	}

	//set up music
	//get the volume settings
	Profile *player;
	player = Profile::getInstance();

	//get the sound
	m_Sound = SoundObject::getInstance();


	//play the time sound
	if (m_iLevelTime == 0 || m_iLevelTime == 1 || m_iLevelTime == 2)
	{

		if (!m_Sound->m_timeMusic.openFromFile("./Assets/sounds/Ambience/Summer Normal Day.wav"))
		{
			cout << "Error : Summer Normal Day.wav failed to load" << endl;
		}
		m_Sound->m_timeMusic.setVolume(player->m_iMusicAudioVolume);
		m_Sound->m_timeMusic.setLoop(true);
		m_Sound->m_timeMusic.play();

	}
	if (m_iLevelTime == 3 || m_iLevelTime == 4)
	{
		if (!m_Sound->m_timeMusic.openFromFile("./Assets/sounds/Ambience/Night.wav"))
		{
			cout << "Error :  Night.wav failed to load" << endl;
		}
		m_Sound->m_timeMusic.setVolume(player->m_iMusicAudioVolume);
		m_Sound->m_timeMusic.setLoop(true);
		m_Sound->m_timeMusic.play();

	}
	if (m_iLevelTime == 5)
	{
		if (!m_Sound->m_timeMusic.openFromFile("./Assets/sounds/Ambience/Winter.wav"))
		{
			cout << "Error :  Winter.wav failed to load" << endl;
		}
		m_Sound->m_timeMusic.setVolume(player->m_iMusicAudioVolume);
		m_Sound->m_timeMusic.setLoop(true);
		m_Sound->m_timeMusic.play();


	}
	//play the background sound
	if (m_iCurrentBackground == 0 || m_iCurrentBackground == 1 || m_iCurrentBackground == 2 || m_iCurrentBackground == 3 || m_iCurrentBackground == 5)
	{
		if (!m_Sound->m_locMusic.openFromFile("./Assets/sounds/Ambience/Rural.wav"))
		{
			cout << "Error : Rural.wav failed to load" << endl;
		}
		m_Sound->m_locMusic.setVolume(player->m_iMusicAudioVolume);
		m_Sound->m_locMusic.setLoop(true);
		m_Sound->m_locMusic.play();

	}
	else if (m_iCurrentBackground == 4)
	{
		if (!m_Sound->m_locMusic.openFromFile("./Assets/sounds/Ambience/City.wav"))
		{
			cout << "Error : City.wav failed to load" << endl;
		}
		m_Sound->m_locMusic.setVolume(player->m_iMusicAudioVolume);
		m_Sound->m_locMusic.setLoop(true);
		m_Sound->m_locMusic.play();
	}
	else if (m_iCurrentBackground == 6)
	{
		m_Sound->m_timeMusic.stop();
		if (!m_Sound->m_locMusic.openFromFile("./Assets/sounds/Ambience/Winter.wav"))
		{
			cout << "Error :  Winter.wav failed to load" << endl;
		}
		m_Sound->m_locMusic.setVolume(player->m_iMusicAudioVolume);
		m_Sound->m_locMusic.setLoop(true);
		m_Sound->m_locMusic.play();

	}
	else
	{
		m_Sound->m_locMusic.stop();

	}

	//pathfinding
	generateGrid();
	chooseNodes();

	//generate cars
	generateCars();


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
				m_iCurrentBackground = i;
				m_Background = SceneObject(Vector2f(0, 0), m_sfLevelSize, m_Gametextures->m_vBackgroundTextures[i], 0.0f);
				
			}
			else if (temp == "Time")
			{
				int i;
				settings >> i;
				m_iLevelTime = i;
				m_Time = SceneObject(Vector2f(0, 0), m_sfLevelSize, m_Gametextures->m_vTimeTextures[i], 0.0f);

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
				if (type == "T-Junction")tempRoad = Road(position, size, rot, m_Gametextures->m_vTJunctionTextures[1]); 
				if (type == "NormalRoad")tempRoad = Road(position, size, rot, m_Gametextures->m_vTwoWayStreetTextures[1]); 
				if (type == "CrossRoads")tempRoad = Road(position, size, rot, m_Gametextures->m_vCrossRoadsTextures[1]);
				if (type == "Corner")tempRoad = Road(position, size, rot, m_Gametextures->m_vCornerTextures[1]);
				tempRoad.setType(type);
				m_vRoads.push_back(tempRoad);
				
						

			}
			else if (temp == "Cars")
			{
				int i;
				settings >> i;
				m_uiNumbofCars = i;

			}
			else if (temp == "Pedestrians")
			{
				int i;
				settings >> i;
				m_uiNumbofPed = i;

			}
			else if (temp == "StartPoint")
			{
				RectangleShape temp;
				temp.setSize(Vector2f(fGridSize, fGridSize));
				float x,y;
				settings >> x >> y;
				temp.setPosition(Vector2f(x, y));
				temp.setOutlineThickness(10.0f);
				temp.setOutlineColor(Color::Green);
				m_vCarsStartPostions.push_back(temp);
			}
			else if (temp == "EndPoint")
			{
				RectangleShape temp;
				temp.setSize(Vector2f(fGridSize, fGridSize));
				float x, y;
				settings >> x >> y;
				temp.setPosition(Vector2f(x, y));
				temp.setOutlineThickness(10.0f);
				temp.setOutlineColor(Color::Red);
				m_vCarsEndPostions.push_back(temp);
			}
			
		}
	}
	else
	{
		cout << "Couldnt Open file ... Assets/levels/" << dir << ".txt" << endl;
		//set up a blank senerio
		
		cout << "Editor Mode" << endl;
		m_bEditorMode = true;
		m_iCurrentBackground = 0;
		m_sfLevelSize = Vector2f(5333, 3000);
		m_sfLevelSize *= 2.0f;
		m_iLevelSize = 0;
		m_iLevelTime = 0;
		m_Background = SceneObject(Vector2f(0, 0), m_sfLevelSize, m_Gametextures->m_vBackgroundTextures[0], 0.0f);
		m_Time = SceneObject(Vector2f(0, 0), m_sfLevelSize, m_Gametextures->m_vTimeTextures[0], 0.0f);
		
	}


	file.close();
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
		m_vCars[i].setTimeOfDay(m_iLevelTime);
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

	if (m_bEditorMode)
	{
		//draw car start positions
		for (int i = 0; i < m_vCarsStartPostions.size(); i++)
		{
			window.draw(m_vCarsStartPostions[i]);
		}
		//draw car start positions
		for (int i = 0; i < m_vCarsEndPostions.size(); i++)
		{
			window.draw(m_vCarsEndPostions[i]);
		}

	}

	//draw nodes
	if (m_bDrawPathfinding)
	{
		for (int i = 0; i < rectsForTesting.size(); i++)
		{
			window.draw(rectsForTesting[i]);
		}
	}

	//draw start positions
	for (int i = 0; i < m_vCarsStartPostions.size(); i++)
	{
		window.draw(m_vCarsStartPostions[i]);
	}
	//draw end positions
	for (int i = 0; i < m_vCarsEndPostions.size(); i++)
	{
		window.draw(m_vCarsEndPostions[i]);
	}

	//draw route
	for (int i = 0; i < m_vCars.size(); i++)
	{
		VertexArray path;

		for (int x = 0; x < m_vCars[i].m_path.size(); x++)
		{
			Vector2f pos = m_vCars[i].m_path.front();
			sf::Vertex newPoint(pos, sf::Color::Green);
			path.append(newPoint);

			cout << m_vCars[i].m_path.size() << endl;
		}
		window.draw(path);
		
	}


	//draw temp object
	if (m_bPlacingObject)window.draw(m_sfTempSprite);
	if (m_bPlacingObject)window.draw(m_sfTempRect);
	

	//draw time of day
	window.draw(m_Time);
}

void Game::closeGame()
{
	loadLevel("Editor");
	m_Sound->m_locMusic.stop();
	m_Sound->m_timeMusic.stop();
	m_vCars.clear();
	m_vSceneObejcts.clear();
	m_vRoads.clear();
	m_vCarsStartPostions.clear();
	m_vCarsEndPostions.clear();
	m_pathfinderData->clearNodes();
	m_uiNumbofCars = 0;


}

void Game::cycleBackground()
{

	m_iCurrentBackground++;
	if (m_iCurrentBackground == m_Gametextures->m_vBackgroundTextures.size())
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
	//if (m_iLevelTime == 6)sName = "ice";

	//get the volume settings
	Profile *player;
	player = Profile::getInstance();

	//get the sound
	m_Sound = SoundObject::getInstance();


	//play the background sound
	if (m_iCurrentBackground == 0 || m_iCurrentBackground == 1 || m_iCurrentBackground == 2 || m_iCurrentBackground == 3 || m_iCurrentBackground == 5)
	{
		if (!m_Sound->m_locMusic.openFromFile("./Assets/sounds/Ambience/Rural.wav"))
		{
			cout << "Error : Rural.wav failed to load" << endl;
		}
		m_Sound->m_locMusic.setVolume(player->m_iMusicAudioVolume);
		m_Sound->m_locMusic.setLoop(true);
		m_Sound->m_locMusic.play();

	}
	else if (m_iCurrentBackground == 4)
	{
		if (!m_Sound->m_locMusic.openFromFile("./Assets/sounds/Ambience/City.wav"))
		{
			cout << "Error : City.wav failed to load" << endl;
		}
		m_Sound->m_locMusic.setVolume(player->m_iMusicAudioVolume);
		m_Sound->m_locMusic.setLoop(true);
		m_Sound->m_locMusic.play();
	}
	else
	{
		m_Sound->m_locMusic.stop();

	}


	m_Background.setTexture(m_Gametextures->m_vBackgroundTextures[m_iCurrentBackground], "");
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
	generateGrid();
	chooseNodes();
}

void Game::cycleLevelTime()
{
	m_iLevelTime++;
	if (m_iLevelTime == m_Gametextures->m_vTimeTextures.size() )
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

	//get the volume settings
	Profile *player;
	player = Profile::getInstance();

	//get the sound
	m_Sound = SoundObject::getInstance();

	//play the time sound
	if (m_iLevelTime == 0 || m_iLevelTime == 1 || m_iLevelTime == 2)
	{

		if (!m_Sound->m_timeMusic.openFromFile("./Assets/sounds/Ambience/Summer Normal Day.wav"))
		{
			cout << "Error : Summer Normal Day.wav failed to load" << endl;
		}
		m_Sound->m_timeMusic.setVolume(player->m_iMusicAudioVolume);
		m_Sound->m_timeMusic.setLoop(true);
		m_Sound->m_timeMusic.play();

	}
	if (m_iLevelTime == 3 || m_iLevelTime == 4)
	{
		if (!m_Sound->m_timeMusic.openFromFile("./Assets/sounds/Ambience/Night.wav"))
		{
			cout << "Error :  Night.wav failed to load" << endl;
		}
		m_Sound->m_timeMusic.setVolume(player->m_iMusicAudioVolume);
		m_Sound->m_timeMusic.setLoop(true);
		m_Sound->m_timeMusic.play();

	}
	if (m_iLevelTime == 5)
	{
		if (!m_Sound->m_timeMusic.openFromFile("./Assets/sounds/Ambience/Winter.wav"))
		{
			cout << "Error :  Winter.wav failed to load" << endl;
		}
		m_Sound->m_timeMusic.setVolume(player->m_iMusicAudioVolume);
		m_Sound->m_timeMusic.setLoop(true);
		m_Sound->m_timeMusic.play();


	}

	m_Time.setTexture(m_Gametextures->m_vTimeTextures[m_iLevelTime],"");
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
		onewFile << "c " << "Scale X " << "Scale Y " << endl;
		onewFile << "LevelSize " << m_sfLevelSize.x << " " << m_sfLevelSize.y << endl;

		//save the background
		onewFile << "c " << "Texture Number" << endl;
		onewFile << "Background " << m_iCurrentBackground << endl;

		//save the time
		onewFile << "c " << "Texture Number" << endl;
		onewFile << "Time " << m_iLevelTime << endl;

		//save the number of cars
		onewFile << "c " << "Cars" << endl;
		onewFile << "Cars " << m_uiNumbofCars << endl;

		//save the number of pedestrians
		onewFile << "c " << "Pedestrians" << endl;
		onewFile << "Pedestrians " << m_uiNumbofPed << endl;

		//save the Roads
		for (int i = 0; i < m_vRoads.size(); i++)
		{
			onewFile << "c " << "Pos X " << "Pos Y " << "Scale x " << "Scale y "<< "Rotation " << "Type " << endl;
			onewFile << "Road " << m_vRoads[i].getPosition().x << " " << m_vRoads[i].getPosition().y << " " << m_vRoads[i].getSize().x << " " << m_vRoads[i].getSize().y << " " << m_vRoads[i].getRotation() << " " << m_vRoads[i].getType() <<  endl;
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
		if (mag < fGridSize)
		{
			sfSnappedPos = m_vGridSystem[i];
			i = m_vGridSystem.size();
		}

	}

	RectangleShape tempRoad;

	tempRoad.setPosition(sfSnappedPos);
	tempRoad.setRotation(rot);

	if (type == "T-Junction")tempRoad.setSize(Vector2f(2500, 1500));
	if (type == "NormalRoad")tempRoad.setSize(Vector2f(500, 1000));
	if (type == "CrossRoads")tempRoad.setSize(Vector2f(2500, 2500));
	if (type == "Corner")tempRoad.setSize(Vector2f(500, 500));

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
		if (test(tempRoad, m_vRoads[i].getCollisionBox()) == true)
		{
			//did not place due to overlap
			valid = false;
		}
	}

	//set up drawbales
	m_sfTempRect.setPosition(sfSnappedPos);
	if(valid)m_sfTempRect.setFillColor(Color(0,255,0,125));
	else m_sfTempRect.setFillColor(Color(255, 0, 0, 125));
	m_sfTempRect.setSize(Vector2f(500,500));
	m_sfTempRect.setRotation(rot);

	
	if (type == "Traffic Light")
	{
		m_sfSize = Vector2f(800, 600);
		m_sfTempRect.setSize(m_sfSize);
		m_sfTempTexture = m_Gametextures->m_vTrafficLightTextures[0];
		
	}
	if (type == "Pedestrian Light")
	{
		m_sfSize = Vector2f(800, 600);
		m_sfTempRect.setSize(m_sfSize);
		m_sfTempTexture = m_Gametextures->m_vPedestrianLightTextures[0];
		
	}
	if (type == "NormalRoad")
	{
		
		m_sfSize = Vector2f(500, 1000);
		m_sfTempRect.setSize(m_sfSize);
		m_sfTempTexture = m_Gametextures->m_vTwoWayStreetTextures[1];

		
		
	}
	if (type == "T-Junction")
	{
		m_sfSize = Vector2f(2500, 1500);
		m_sfTempRect.setSize(m_sfSize);
		m_sfTempTexture = m_Gametextures->m_vTJunctionTextures[1];

	}
	if (type == "CrossRoads")
	{

		m_sfSize = Vector2f(2500, 2500);
		m_sfTempRect.setSize(m_sfSize);
		m_sfTempTexture = m_Gametextures->m_vCrossRoadsTextures[1];



	}
	if (type == "Corner")
	{
		m_sfSize = Vector2f(500, 500);
		m_sfTempRect.setSize(m_sfSize);
		m_sfTempTexture = m_Gametextures->m_vCornerTextures[1];

	}

	m_sfTempSprite.setTexture(m_sfTempTexture);
	m_sfTempSprite.setTextureRect(IntRect(0, 0, m_sfTempTexture.getSize().x, m_sfTempTexture.getSize().y));
	
	m_sfTempSprite.setPosition(sfSnappedPos);
	
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
		if (mag < fGridSize)
		{
			sfSnappedPos = m_vGridSystem[i];
			i = m_vGridSystem.size();
			
		}
	}


	Road tempRoad;
	if (type == "T-Junction")tempRoad = Road(sfSnappedPos, Vector2f(2500, 1500), rot, m_Gametextures->m_vTJunctionTextures[1]);
	if (type == "NormalRoad")tempRoad = Road(sfSnappedPos, Vector2f(500, 1000), rot, m_Gametextures->m_vTwoWayStreetTextures[1]);
	if (type == "CrossRoads")tempRoad = Road(sfSnappedPos, Vector2f(2500, 2500), 0 , m_Gametextures->m_vCrossRoadsTextures[1]);
	if (type == "Corner")tempRoad	= Road(sfSnappedPos, Vector2f(500, 500), rot, m_Gametextures->m_vCornerTextures[1]);

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

	return true;

}

void Game::generateGrid()
{
	cout << "Generating Grid ... ";
	//clear grid (incase of resize)
	m_vGridSystem.clear();
	m_pathfinderData->clearNodes();

	// loop from 0 to level size in steps of GRIDSIZE

	for (int y = 0; y < m_sfLevelSize.y - fGridSize; y += fGridSize)
	{
		m_pathfinderData->m_uiNodeY++;
		for (int x = 0; x < m_sfLevelSize.x - fGridSize; x += fGridSize)
		{
			
			m_vGridSystem.push_back(Vector2f(x, y));
			
		}

	}

	for (int x = 0; x < m_sfLevelSize.x - fGridSize; x += fGridSize)
	{
		m_pathfinderData->m_uiNodeX++;
	}
	m_pathfinderData->m_uiNodeY;

	for (int i = 0; i < m_vGridSystem.size(); i++)
	{
		//generates a full closed grid

		m_pathfinderData->addNode(0, 0, i, m_vGridSystem[i],true);


	}
	cout << "Finished" << endl;

	
	

}

void Game::chooseNodes()
{

	cout << "Generating Pathfinding ... ";

	RectangleShape nodeSquare;
	nodeSquare.setSize(Vector2f(fGridSize, fGridSize));
	
	//fill map with inaccessible nodes nodes
	for (int i = 0; i < m_pathfinderData->m_carNodes.size(); i++)
	{
		m_pathfinderData->m_carNodes[i].first->m_bAccessable = false;
	}
	// replace roads with open
	for (int i = 0; i < m_pathfinderData->m_carNodes.size(); i++)
	{
		nodeSquare.setPosition(m_pathfinderData->m_carNodes[i].second);

		//loop roads
		for (int x = 0; x < m_vRoads.size(); x++)
		{

			FloatRect A = nodeSquare.getGlobalBounds();
			FloatRect B = m_vRoads[x].getCollisionBox().getGlobalBounds();

			if (A.intersects(B))
			{
				//Accessible
				m_pathfinderData->m_carNodes[i].first->m_bAccessable = true;
			}
	
		}

	}


	//pass pathfinding to roads
	for (int i = 0; i < m_vRoads.size(); i++)
	{
		//m_vRoads[i].passPathfinding(*m_pathfinderData);
	}

	//draw nodes list
	for (int i = 0; i < m_pathfinderData->m_carNodes.size(); i++)
	{
		RectangleShape temp;
		temp.setPosition(m_pathfinderData->m_carNodes[i].second);
		temp.setSize(Vector2f(fGridSize, fGridSize));
		if (m_pathfinderData->m_carNodes[i].first->m_bAccessable == true)
		{
			temp.setFillColor(Color(0, 255, 0, 50));
			temp.setOutlineThickness(5.0f);
		}
		else if (m_pathfinderData->m_carNodes[i].first->m_bAccessable == false)
		{
			temp.setFillColor(Color(255, 0, 0, 255));
			temp.setOutlineThickness(25.0f);
		}
		
		rectsForTesting.push_back(temp);
	}



	cout << "Finished" << endl;
}
