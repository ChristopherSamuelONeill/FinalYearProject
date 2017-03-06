#include "Car.h"

Car::Car()
{
}

Car::Car(Vector2f Position, Vector2f Size, const char carType[])
{
	// Initialize Data
	m_sfPosition = Position;
	m_sfSize = Size;
	m_iSteerDirection = 0;
	m_iMaxTurnAngle = 90;
	m_fSteerOrientation = 0;
	m_fRotation = 0;


	//load textures
	tinyxml2::XMLDocument levelFile;
	levelFile.LoadFile(carType);

	string base;
	string rearlightsOFF;
	string rearlightsON;
	string frontlightsOFF;
	string frontlightsON;
	string rearWheels;
	string frontLeftWheel;
	string frontRightWheel;


	//find textures
	for (tinyxml2::XMLNode* child = levelFile.FirstChild(); child != NULL; child = child->NextSibling())
	{
		const char* Value = child->Value();

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

	}

	//base
	if (!m_sfTexture[0].loadFromFile(base))
	{
		cout << "Error: Base Texture was unable to load." << endl;
	};
	//rear lights
	if (!m_sfTexture[1].loadFromFile(rearlightsOFF))
	{
		cout << "Error: rearlightsOFF was unable to load." << endl;
	};
	if (!m_sfTexture[2].loadFromFile(rearlightsON))
	{
		cout << "Error: rearlightsON was unable to load." << endl;
	};
	//front lights
	if (!m_sfTexture[3].loadFromFile(frontlightsOFF))
	{
		cout << "Error: frontlightsOFF was unable to load." << endl;
	};
	if (!m_sfTexture[4].loadFromFile(frontlightsON))
	{
		cout << "Error: frontlightsON was unable to load." << endl;
	};

	//wheels
	if (!m_sfTexture[5].loadFromFile(rearWheels))
	{
		cout << "Error: rearWheels was unable to load." << endl;
	};
	if (!m_sfTexture[6].loadFromFile(frontLeftWheel))
	{
		cout << "Error: frontLeftWheel was unable to load." << endl;
	};
	if (!m_sfTexture[7].loadFromFile(frontRightWheel))
	{
		cout << "Error: frontRightWheel was unable to load." << endl;
	};


	//Set Up drawables

	if (!temp.loadFromFile("./Assets/textures/Cars/car_white.png"))
	{
		cout << base << endl;
	};

	


}


void Car::draw(RenderTarget & target, RenderStates states) const
{
	
	target.draw(m_sfCarSprite);
	
	target.draw(m_sfWheelSprite[0]);
	target.draw(m_sfWheelSprite[1]);
	target.draw(m_sfWheelSprite[2]);

	target.draw(m_sfLightsSprite[0]);
	target.draw(m_sfLightsSprite[1]);

}

void Car::update(float dt)
{
	//base car
	m_sfCarRect.setPosition(m_sfPosition);
	m_sfCarRect.setSize(m_sfSize);
	m_sfCarRect.setFillColor(Color::Red);
	m_sfCarRect.setOrigin(m_sfSize.x / 2, m_sfSize.y / 2);
	m_sfCarRect.setRotation(m_fRotation);

	m_sfCarSprite.setTexture(temp);
	m_sfCarSprite.setPosition(m_sfCarRect.getPosition());
	m_sfCarSprite.setOrigin(m_sfSize.x / 2, m_sfSize.y / 2);
	m_sfCarSprite.setRotation(m_fRotation);


	//Rear Wheels 
	m_sfWheelRect[0].setPosition(m_sfPosition);
	m_sfWheelRect[0].setSize(m_sfSize);
	m_sfWheelRect[0].setRotation(m_fRotation);

	m_sfWheelSprite[0].setTexture(m_sfTexture[5]);
	m_sfWheelSprite[0].setPosition(m_sfCarRect.getPosition());
	m_sfWheelSprite[0].setOrigin(m_sfSize.x / 2, m_sfSize.y / 2);
	m_sfWheelSprite[0].setRotation(m_fRotation);

	//Front left Wheels 
	m_sfWheelRect[1].setPosition(m_sfPosition);
	m_sfWheelRect[1].setSize(m_sfSize);
	m_sfWheelRect[1].setRotation(m_fRotation);

	m_sfWheelSprite[1].setTexture(m_sfTexture[6]);
	m_sfWheelSprite[1].setPosition(m_sfCarRect.getPosition().x, m_sfCarRect.getPosition().y + 25);
	m_sfWheelSprite[1].setOrigin(m_sfSize.x / 2, m_sfSize.y / 2);
	m_sfWheelSprite[1].setRotation(m_fRotation);

	//Front right Wheels 
	m_sfWheelRect[2].setPosition(m_sfPosition);
	m_sfWheelRect[2].setSize(m_sfSize);
	m_sfWheelRect[2].setRotation(m_fRotation);

	m_sfWheelSprite[2].setTexture(m_sfTexture[7]);
	m_sfWheelSprite[2].setScale(Vector2f(1, 1));
	m_sfWheelSprite[2].setPosition(m_sfCarRect.getPosition().x + 86.5f, m_sfCarRect.getPosition().y + 25);
	m_sfWheelSprite[2].setOrigin(m_sfSize.x / 2, m_sfSize.y / 2);
	m_sfWheelSprite[2].setRotation(m_fRotation);

	//rear lights
	if (m_bBraking)
	{
		m_sfLights[0].setPosition(m_sfPosition);
		m_sfLights[0].setSize(m_sfSize);
		m_sfLights[0].setRotation(m_fRotation);

		m_sfLightsSprite[0].setTexture(m_sfTexture[2]);
		m_sfLightsSprite[0].setScale(Vector2f(1, 1));
		m_sfLightsSprite[0].setPosition(m_sfCarRect.getPosition());
		m_sfLightsSprite[0].setOrigin(m_sfSize.x / 2, m_sfSize.y / 2);
		m_sfLightsSprite[0].setRotation(m_fRotation);

	}
	else
	{
		m_sfLights[0].setPosition(m_sfPosition);
		m_sfLights[0].setSize(m_sfSize);
		m_sfLights[0].setRotation(m_fRotation);

		m_sfLightsSprite[0].setTexture(m_sfTexture[1]);
		m_sfLightsSprite[0].setScale(Vector2f(1, 1));
		m_sfLightsSprite[0].setPosition(m_sfCarRect.getPosition());
		m_sfLightsSprite[0].setOrigin(m_sfSize.x / 2, m_sfSize.y / 2);
		m_sfLightsSprite[0].setRotation(m_fRotation);

	}
	//front lights
	if (m_bLights)
	{
		m_sfLights[1].setPosition(m_sfPosition);
		m_sfLights[1].setSize(m_sfSize);
		m_sfLights[1].setRotation(m_fRotation);

		m_sfLightsSprite[1].setTexture(m_sfTexture[4]);
		m_sfLightsSprite[1].setScale(Vector2f(1, 1));
		m_sfLightsSprite[1].setPosition(m_sfCarRect.getPosition());
		m_sfLightsSprite[1].setOrigin(m_sfSize.x / 2, m_sfSize.y / 2);
		m_sfLightsSprite[1].setRotation(m_fRotation);

	}
	else
	{
		m_sfLights[1].setPosition(m_sfPosition);
		m_sfLights[1].setSize(m_sfSize);
		m_sfLights[1].setRotation(m_fRotation);

		m_sfLightsSprite[1].setTexture(m_sfTexture[3]);
		m_sfLightsSprite[1].setScale(Vector2f(1, 1));
		m_sfLightsSprite[1].setPosition(m_sfCarRect.getPosition());
		m_sfLightsSprite[1].setOrigin(m_sfSize.x / 2, m_sfSize.y / 2);
		m_sfLightsSprite[1].setRotation(m_fRotation);

	}
}

void Car::SetTurning(int iDirection)
{
	m_iSteerDirection = iDirection;
}

void Car::turnWheels()
{
	//set a speed to turn the wheels at
	float fTurnSpeed = 5.0f;

	//find the speed the car is moving at 
	float fSpeed = sqrt((m_sfVelocity.x * m_sfVelocity.x) + (m_sfVelocity.y * m_sfVelocity.y));
	
	//ensure there is no division by 0
	fSpeed = abs(fSpeed);
	if (fSpeed < 1) fSpeed = 1;

	//Turn the Wheels
	m_fSteerOrientation += fTurnSpeed * m_iSteerDirection;

	//stop the wheels from turning past their limit
	if (m_fSteerOrientation > m_iMaxTurnAngle / fSpeed)
	{
		m_fSteerOrientation = m_iMaxTurnAngle / fSpeed;
	}
	if (m_fSteerOrientation < -m_iMaxTurnAngle / fSpeed)
	{
		m_fSteerOrientation = -m_iMaxTurnAngle / fSpeed;
	}

	//if not turning , turn wheels back to stright
	if (m_iSteerDirection == 0)
	{

		if (m_fSteerOrientation < 0)
		{
			m_fSteerOrientation += fTurnSpeed;
		}

		if (m_fSteerOrientation > 0)
		{
			m_fSteerOrientation -= fTurnSpeed;
		}
	}


}