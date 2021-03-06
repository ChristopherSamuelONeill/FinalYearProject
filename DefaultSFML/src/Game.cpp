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
	m_Gametextures = TextureObject::getInstance();
	m_Gametextures->loadTextures();
	m_bEditorMode = false;
	m_pathfinderData = new Pathfinding;
	startGame(dir);
}

void Game::generateCars()
{
	cout << "Generating "<< m_uiNumbofCars << " cars ... \n";
	srand(time(NULL));

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
		
		int iRandStart = rand() % (m_vCarsStartPostions.size() - 1);
		
		Car tempCar(m_vCarsStartPostions[iRandStart].first.getPosition(), m_vCarsEndPostions[iRandStart].first.getPosition(), Vector2f(250, 100), tempTexture, m_vCarsStartPostions[iRandStart].second);
		m_vCars.push_back(tempCar);
		m_vCars[i].receiveNodeData(*m_pathfinderData);
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
				if (type == "T-Junction")tempRoad = Road(position, size, rot, m_Gametextures->m_vTJunctionTextures[0]); 
				if (type == "NormalRoad")tempRoad = Road(position, size, rot, m_Gametextures->m_vTwoWayStreetTextures[0]); 
				if (type == "CrossRoads")tempRoad = Road(position, size, rot, m_Gametextures->m_vCrossRoadsTextures[0]);
				if (type == "Corner")tempRoad = Road(position, size, rot, m_Gametextures->m_vCornerTextures[0]);
				tempRoad.setType(type);
				m_vRoads.push_back(tempRoad);

				Pavement tempPavment;
				if (type == "T-Junction")
				{
					if (rot == 0)
					{
						tempPavment = Pavement(position - Vector2f(0, 100), Vector2f(2500, 1600), rot, m_Gametextures->m_PavementTJunctionTextures);
					}
					if (rot == 90)
					{
						tempPavment = Pavement(position - Vector2f(-100, 0), Vector2f(2500, 1600), rot, m_Gametextures->m_PavementTJunctionTextures);
					}
					if (rot == 180)
					{
						tempPavment = Pavement(position - Vector2f(0, -100), Vector2f(2500, 1600), rot, m_Gametextures->m_PavementTJunctionTextures);
					}
					if (rot == 270)
					{
						tempPavment = Pavement(position - Vector2f(100, 0), Vector2f(2500, 1600), rot, m_Gametextures->m_PavementTJunctionTextures);
					}

				}
				if (type == "NormalRoad")
				{
					if (rot == 0)
					{
						tempPavment = Pavement(position - Vector2f(100, 0), Vector2f(700, 1000), rot, m_Gametextures->m_PavementTwoWayStreetTextures);
					}
					if (rot == 90)
					{
						tempPavment = Pavement(position - Vector2f(0, 100), Vector2f(700, 1000), rot, m_Gametextures->m_PavementTwoWayStreetTextures);
					}
				}
				if (type == "CrossRoads")tempPavment = Pavement(position, Vector2f(2500, 2500), 0, m_Gametextures->m_PavementCrossRoadsTextures);
				if (type == "Corner")
				{
					if (rot == 0)
					{
						tempPavment = Pavement(position - Vector2f(0, 100), Vector2f(600, 600), rot, m_Gametextures->m_PavementCornerTextures);
					}
					if (rot == 90)
					{
						tempPavment = Pavement(position - Vector2f(-100, 0), Vector2f(600, 600), rot, m_Gametextures->m_PavementCornerTextures);
					}
					if (rot == 180)
					{
						tempPavment = Pavement(position - Vector2f(0, -100), Vector2f(600, 600), rot, m_Gametextures->m_PavementCornerTextures);
					}
					if (rot == 270)
					{
						tempPavment = Pavement(position - Vector2f(100, 0), Vector2f(600, 600), rot, m_Gametextures->m_PavementCornerTextures);
					}
				}
				tempPavment.setType(type);
				m_vPavement.push_back(tempPavment);
				
						

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
				pair<RectangleShape, float> temp;
				temp.first.setSize(Vector2f(fGridSize, fGridSize));
				float x,y,r;
				settings >> x >> y >> r;
				temp.first.setPosition(Vector2f(x, y));
				temp.first.setOutlineThickness(10.0f);
				temp.first.setOutlineColor(Color::Green);
				temp.second = r;
				m_vCarsStartPostions.push_back(temp);
			}
			else if (temp == "EndPoint")
			{
				pair<RectangleShape, float> temp;
				temp.first.setSize(Vector2f(fGridSize, fGridSize));
				float x, y, r;
				settings >> x >> y >> r;
				temp.first.setPosition(Vector2f(x, y));
				temp.first.setOutlineThickness(10.0f);
				temp.first.setOutlineColor(Color::Red);
				temp.second = r;
				
				m_vCarsEndPostions.push_back(temp);
			}
			else if (temp == "TrafficLight")
			{
				
				float x, y ,sx,sy,r;
				settings >> x >> y >>sx >>sy>>r;
				Texture lights[3] = {
					m_Gametextures->m_vTrafficLightTextures[0],
					m_Gametextures->m_vTrafficLightTextures[1],
					m_Gametextures->m_vTrafficLightTextures[2]

				};

				TrafficLight temp(Vector2f(x, y), Vector2f(sx, sy), lights, r, 0);
				m_vTrafficLights.push_back(temp);

			}
			else if (temp == "PedLight")
			{
			
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
	//spawn cars
	spawnCars();
	
	//update Background
	m_Background.update();

	//update road
	for (int i = 0; i < m_vRoads.size(); i++)
	{
		m_vRoads[i].update();
	}

	//update Pavement
	for (int i = 0; i < m_vPavement.size(); i++)
	{
		m_vPavement[i].update();
	}

	//update Traffic LIghts
	for (int i = 0; i < m_vTrafficLights.size(); i++)
	{
		m_vTrafficLights[i].update(dt);
	}

	//update cars
	for (int i = 0; i < m_vCars.size(); i++)
	{
		for (int y = 0; y < m_vCars.size(); y++)
		{
			m_vCars[i].CheckForCar(m_vCars[y]);
		}
		if (m_vTrafficLights.size() > 0)
		{
			for (int x = 0; x < m_vTrafficLights.size(); x++)
			{
				m_vCars[i].setTimeOfDay(m_iLevelTime);
				m_vCars[i].CheckForTrafficLight(m_vTrafficLights[x]);
				m_vCars[i].update(dt);

			}

		}
		else
		{
			m_vCars[i].setTimeOfDay(m_iLevelTime);
			m_vCars[i].update(dt);
		}
		

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

	// draw the pavement
	for (int i = 0; i < m_vPavement.size(); i++)
	{
		window.draw(m_vPavement[i]);
	}


	//draw nodes
	if (m_iDrawPathfinding != 0)
	{
		if (m_iDrawPathfinding == 1 )
		{
			for (int i = 0; i < CarNodes.size(); i++)
			{
				window.draw(CarNodes[i]);
			}
		}
		if (m_iDrawPathfinding == 2)
		{
			for (int i = 0; i < PedNodes.size(); i++)
			{
				window.draw(PedNodes[i]);
			}
		}
	}


	//draw TrafficLights
	for (int i = 0; i < m_vTrafficLights.size(); i++)
	{
		window.draw(m_vTrafficLights[i]);
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
			window.draw(m_vCarsStartPostions[i].first);
		}
		//draw car start positions
		for (int i = 0; i < m_vCarsEndPostions.size(); i++)
		{
			window.draw(m_vCarsEndPostions[i].first);
		}

	}



	//draw start positions
	for (int i = 0; i < m_vCarsStartPostions.size(); i++)
	{
		window.draw(m_vCarsStartPostions[i].first);
	}
	//draw end positions
	for (int i = 0; i < m_vCarsEndPostions.size(); i++)
	{
		window.draw(m_vCarsEndPostions[i].first);
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

bool Game::checkforWin()
{
	//check for end condition
	int numOfCarsFinished = 0;
	for (int i = 0; i < m_vCars.size(); i++)
	{
		if (m_vCars[i].m_bFinished == true)
		{
			numOfCarsFinished++;
		}
	}
	if (numOfCarsFinished == m_vCars.size()) return true;
	else return false;
}

bool Game::checkforLoss()
{
	//check for end condition
	int numOfCarsFinished = 0;
	for (int i = 0; i < m_vCars.size(); i++)
	{
		if (m_vCars[i].m_bCrashed == true)
		{
			numOfCarsFinished++;
		}
	}
	/*if (numOfCarsFinished == m_vCars.size()) return true;
	else return false;*/
	return false;
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

void Game::checkForTrafficLights(Vector2f pos)
{
	for (int i = 0; i < m_vTrafficLights.size(); i++)
	{
		if (m_vTrafficLights[i].m_bClicked(pos));
		{
			if (m_vTrafficLights[i].m_iState == 2)m_vTrafficLights[i].changeToRed();
			else if (m_vTrafficLights[i].m_iState == 0)m_vTrafficLights[i].changeToGreen();
			i = m_vTrafficLights.size();
		}
	}

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

		//save the Start Points
		for (int i = 0; i < m_vCarsStartPostions.size(); i++)
		{
			onewFile << "c " << "Pos X " << "Pos Y " << " rot " << endl;
			onewFile << "StartPoint " << m_vCarsStartPostions[i].first.getPosition().x << " " << m_vCarsStartPostions[i].first.getPosition().y << " " << m_vCarsStartPostions[i].second << endl;
		}
		//save the End Points
		for (int i = 0; i < m_vCarsEndPostions.size(); i++)
		{
			onewFile << "c " << "Pos X " << "Pos Y " << endl;
			onewFile << "EndPoint " << m_vCarsEndPostions[i].first.getPosition().x << " " << m_vCarsEndPostions[i].first.getPosition().y << endl;
		}

		//save the Trafiic lights 
		for (int i = 0; i < m_vTrafficLights.size(); i++)
		{
			onewFile << "c " << "Pos X " << "Pos Y " << "Scale X " << "Scale Y " << "Rotation" << endl;
			onewFile << "TrafficLight " << m_vTrafficLights[i].getPosition().x << " " << m_vTrafficLights[i].getPosition().y << " " << m_vTrafficLights[i].getSize().x << " "<< m_vTrafficLights[i].getSize().y << " " << m_vTrafficLights[i].getRotation() << endl;
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

	RectangleShape tempObject;

	tempObject.setPosition(sfSnappedPos);
	tempObject.setRotation(rot);

	if (type == "T-Junction")tempObject.setSize(Vector2f(2500, 1500));
	if (type == "NormalRoad")tempObject.setSize(Vector2f(500, 1000));
	if (type == "CrossRoads")tempObject.setSize(Vector2f(2500, 2500));
	if (type == "Corner")tempObject.setSize(Vector2f(500, 500));
	if (type == "StartPoint" || type == "EndPoint") tempObject.setSize(Vector2f(fGridSize, fGridSize));

	bool valid = true;

	//check if the new object is in the level
	if (sfSnappedPos.x > m_sfLevelSize.x)valid = false;
	else if (sfSnappedPos.x <= 0)valid = false;
	else if (sfSnappedPos.y <= 0)valid = false;
	else if (sfSnappedPos.y > m_sfLevelSize.y)valid = false;

	CollisionDetection test;

	if (type == "T-Junction" || type == "NormalRoad" || type == "CrossRoads" || type == "Corner")
	{
		//check the road doesnt overlap with any other roads
		for (int i = 0; i < m_vRoads.size(); i++)
		{
			if (test(tempObject, m_vRoads[i].getCollisionBox()) == true)
			{
				//did not place due to overlap
				valid = false;
			}
		}
	}


	//set up drawbales
	m_sfTempRect.setPosition(sfSnappedPos);
	if(valid)m_sfTempRect.setFillColor(Color(0,255,0,125));
	else m_sfTempRect.setFillColor(Color(255, 0, 0, 125));
	m_sfTempRect.setSize(Vector2f(500,500));
	m_sfTempRect.setRotation(rot);

	
	if (type == "TrafficLight")
	{
		m_sfSize = Vector2f(350, 250);
		m_sfTempRect.setSize(m_sfSize);
		m_sfTempTexture = m_Gametextures->m_vTrafficLightTextures[0];
		
	}
	if (type == "PedLight")
	{
		m_sfSize = Vector2f(250, 500);
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

	if (type == "StartPoint" || type == "EndPoint")
	{
		m_sfSize = Vector2f(fGridSize, fGridSize);
		m_sfTempRect.setSize(m_sfSize);
		
		m_sfTempTexture = m_Gametextures->m_StartEndPoint;

	}

	m_sfTempSprite.setTexture(m_sfTempTexture);
	m_sfTempSprite.setTextureRect(IntRect(0, 0, m_sfTempTexture.getSize().x, m_sfTempTexture.getSize().y));
	
	m_sfTempSprite.setPosition(sfSnappedPos);
	
	m_sfTempSprite.setRotation(rot);
	

}

bool Game::placeTrafficLights(Vector2f position, float rot, string type)
{

	cout << position.x << endl;

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

	

	RectangleShape tempObject;

	tempObject.setPosition(sfSnappedPos);
	tempObject.setRotation(rot);

	//check if the new road is in the level
	if (sfSnappedPos.x > m_sfLevelSize.x)return false;
	else if (sfSnappedPos.x <= 0)return false;
	else if (sfSnappedPos.y <= 0)return false;
	else if (sfSnappedPos.y > m_sfLevelSize.y)return false;

	if (type == "TrafficLight")
	{
		m_sfSize = Vector2f(350, 250);
		m_sfTempRect.setSize(m_sfSize);
		m_sfTempTexture = m_Gametextures->m_vTrafficLightTextures[0];

	}

	Texture lights[3] = {
		m_Gametextures->m_vTrafficLightTextures[0],
		m_Gametextures->m_vTrafficLightTextures[1],
		m_Gametextures->m_vTrafficLightTextures[2]

	};

	
	TrafficLight tempLight(sfSnappedPos, m_sfTempRect.getSize(), lights,rot,0);

	//if valid create road
	m_vTrafficLights.push_back(tempLight);
	cout << sfSnappedPos.x << endl;
	return true;
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

	//create the pavement around it

	Pavement tempPavment;
	if (type == "T-Junction")
	{
		if (rot == 0)
		{
			tempPavment = Pavement(sfSnappedPos - Vector2f(0, 100), Vector2f(2500, 1600), rot, m_Gametextures->m_PavementTJunctionTextures);
		}
		if (rot == 90)
		{
			tempPavment = Pavement(sfSnappedPos - Vector2f(-100, 0), Vector2f(2500, 1600), rot, m_Gametextures->m_PavementTJunctionTextures);
		}
		if (rot == 180)
		{
			tempPavment = Pavement(position - Vector2f(0, -100), Vector2f(2500, 1600), rot, m_Gametextures->m_PavementTJunctionTextures);
		}
		if (rot == 270)
		{
			tempPavment = Pavement(position - Vector2f(100, 0), Vector2f(2500, 1600), rot, m_Gametextures->m_PavementTJunctionTextures);
		}
		
	}
	if (type == "NormalRoad")
	{
		if (rot == 0)
		{
			tempPavment = Pavement(sfSnappedPos - Vector2f(100, 0), Vector2f(700, 1000), rot, m_Gametextures->m_PavementTwoWayStreetTextures);
		}
		if (rot == 90)
		{
			tempPavment = Pavement(sfSnappedPos - Vector2f(0, 100), Vector2f(700, 1000), rot, m_Gametextures->m_PavementTwoWayStreetTextures);
		}
		
	}
	if (type == "CrossRoads")tempPavment = Pavement(sfSnappedPos, Vector2f(2500, 2500), 0, m_Gametextures->m_PavementCrossRoadsTextures);
	if (type == "Corner")
	{
		if (rot == 0)
		{
			tempPavment = Pavement(sfSnappedPos - Vector2f(0, 100), Vector2f(600, 600), rot, m_Gametextures->m_PavementCornerTextures);
		}
	}
	m_vPavement.push_back(tempPavment);


	return true;

}

bool Game::placeStartEndPoint(Vector2f position,string type, float rot)
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

	FloatRect rect1,rect2,rect3;
	Vector2f Size(fGridSize, fGridSize);
	pair<RectangleShape, float> tempRect;
	tempRect.first.setPosition(sfSnappedPos);
	tempRect.first.setSize(Size);

	//check no start points and end points over lap
	for (int i = 0; i < m_vCarsStartPostions.size(); i++)
	{
		for (int x = 0; x < m_vCarsEndPostions.size(); x++)
		{
			rect1 = m_vCarsStartPostions[i].first.getGlobalBounds();
			rect2 = m_vCarsEndPostions[x].first.getGlobalBounds();
			rect3 = tempRect.first.getGlobalBounds();
			if (rect1.intersects(rect3)) return false;
			if (rect2.intersects(rect3)) return false;
		}
	}

	tempRect.second = rot;

	if (type == "StartPoint")
	{
		m_vCarsStartPostions.push_back(tempRect);
	}
	if (type == "EndPoint")
	{
		m_vCarsEndPostions.push_back(tempRect);
	}



	return true;


}

void Game::spawnCars()
{
	CollisionDetection spawnTest;
	// loop cars and ensure none are touching
	for (int i = 0; i < m_vCars.size(); i++)
	{
		for (int x = 0; x < m_vCars.size(); x++)
		{
			if (i != x)
			{
				if (spawnTest(m_vCars[i].m_sfCarRect, m_vCars[x].m_sfCarRect))
				{
					if (m_vCars[i].m_bSpawned == false && m_vCars[x].m_bSpawned == false)
					{
						//m_vCars[x].m_bSpawned = true; // spawn car i
					}
					else
					{
						m_vCars[x].m_bSpawned = false;
					}
				}
				else
				{
					m_vCars[x].m_bSpawned = true; // spawn car i
					
				}
			}
			
		}
	}

}

void Game::generateGrid()
{
	cout << "Generating Grid ... ";
	//clear grid (incase of resize)
	m_vGridSystem.clear();
	m_pathfinderData->clearNodes();



	// loop from 0 to level size in steps of GRIDSIZE

	int count = 1;
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


	for (int i = 0; i < m_vGridSystem.size(); i++)
	{
		//generates a full closed grid

		m_pathfinderData->addCarNode(0, 0, i, m_vGridSystem[i], true);
		m_pathfinderData->addPedNode(0, 0, i, m_vGridSystem[i], true);


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
		m_vRoads[i].passPathfinding(*m_pathfinderData);
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
		
		CarNodes.push_back(temp);
	}

	//Path Finding for pedestrians

	//fill map with inaccessible nodes nodes
	for (int i = 0; i < m_pathfinderData->m_pedNodes.size(); i++)
	{
		m_pathfinderData->m_pedNodes[i].first->m_bAccessable = false;
	}
	// replace pavements with open
	for (int i = 0; i < m_pathfinderData->m_pedNodes.size(); i++)
	{
		nodeSquare.setPosition(m_pathfinderData->m_carNodes[i].second);

		//loop pavements
		for (int x = 0; x < m_vPavement.size(); x++)
		{

			FloatRect A = nodeSquare.getGlobalBounds();
			FloatRect B = m_vPavement[x].getCollisionBox().getGlobalBounds();

			if (A.intersects(B))
			{
				//Accessible
				m_pathfinderData->m_pedNodes[i].first->m_bAccessable = true;
			}

		}

	}


	//pass pathfinding to pavement
	for (int i = 0; i < m_vPavement.size(); i++)
	{
		m_vPavement[i].passPathfinding(*m_pathfinderData);
	}

	//draw nodes list
	for (int i = 0; i < m_pathfinderData->m_pedNodes.size(); i++)
	{
		RectangleShape temp;
		temp.setPosition(m_pathfinderData->m_pedNodes[i].second);
		temp.setSize(Vector2f(fGridSize, fGridSize));
		if (m_pathfinderData->m_pedNodes[i].first->m_bAccessable == true)
		{
			temp.setFillColor(Color(0, 255, 0, 50));
			temp.setOutlineThickness(5.0f);
		}
		else if (m_pathfinderData->m_pedNodes[i].first->m_bAccessable == false)
		{
			temp.setFillColor(Color(255, 0, 0, 255));
			temp.setOutlineThickness(25.0f);
		}

		PedNodes.push_back(temp);
	}





	cout << "Finished" << endl;
}
