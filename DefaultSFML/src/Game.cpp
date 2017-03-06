#include "Game.h"


Game::Game()
{
}

Game::Game(string Level)
{

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
	tinyxml2::XMLDocument levelFile;
	levelFile.LoadFile(dir);

	for (tinyxml2::XMLNode* child = levelFile.FirstChild(); child != NULL; child = child->NextSibling())
	{
		const char* Value = child->Value();

		string base;
		string rearlightsOFF;
		string rearlightsON;
		string frontlightsOFF;
		string frontlightsON;
		string rearWheels;
		string frontLeftWheel;
		string frontRightWheel;

		if (strcmp(Value, "baseModel") == 0)
		{
			for (tinyxml2::XMLNode* child2 = child->FirstChild(); child2 != NULL; child2 = child2->NextSiblingElement())
			{
				Value = child2->Value();
				base = Value;

			}

		}
		if (strcmp(Value, "rearLightsUnlitModel") == 0)
		{
			for (tinyxml2::XMLNode* child2 = child->FirstChild(); child2 != NULL; child2 = child2->NextSiblingElement())
			{
				Value = child2->Value();
				rearlightsOFF = Value;

			}

		}
		if (strcmp(Value, "rearLightslitModel") == 0)
		{
			for (tinyxml2::XMLNode* child2 = child->FirstChild(); child2 != NULL; child2 = child2->NextSiblingElement())
			{
				Value = child2->Value();
				rearlightsON = Value;

			}

		}
		if (strcmp(Value, "frontLightsUnlitModel") == 0)
		{
			for (tinyxml2::XMLNode* child2 = child->FirstChild(); child2 != NULL; child2 = child2->NextSiblingElement())
			{
				Value = child2->Value();
				frontlightsOFF = Value;

			}

		}
		
		if (strcmp(Value, "frontLightslitModel") == 0)
		{
			for (tinyxml2::XMLNode* child2 = child->FirstChild(); child2 != NULL; child2 = child2->NextSiblingElement())
			{
				Value = child2->Value();
				frontlightsON = Value;

			}

		}
		if (strcmp(Value, "LeftWheelModel") == 0)
		{
			for (tinyxml2::XMLNode* child2 = child->FirstChild(); child2 != NULL; child2 = child2->NextSiblingElement())
			{
				Value = child2->Value();
				frontLeftWheel = Value;

			}

		}
		if (strcmp(Value, "rightWheelModel") == 0)
		{
			for (tinyxml2::XMLNode* child2 = child->FirstChild(); child2 != NULL; child2 = child2->NextSiblingElement())
			{
				Value = child2->Value();
				frontRightWheel = Value;

			}

		}
		if (strcmp(Value, "rearWheelModel") == 0)
		{
			for (tinyxml2::XMLNode* child2 = child->FirstChild(); child2 != NULL; child2 = child2->NextSiblingElement())
			{
				Value = child2->Value();
				rearWheels = Value;

			}

		}

		String texture[8] = { base,rearlightsOFF ,rearlightsON ,frontlightsOFF ,frontlightsON ,rearWheels,frontLeftWheel,frontRightWheel };
		m_vCars.push_back(Car(Vector2f(720,400),Vector2f(250,100),texture));
	}

	
}

void Game::drawScene(RenderWindow& renderWindow)
{
	for (int i = 0; i < m_vCars.size(); i++)
	{
		renderWindow.draw(m_vCars[i]);
	}
}
