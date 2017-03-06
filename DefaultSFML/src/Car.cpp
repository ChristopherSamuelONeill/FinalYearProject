#include "Car.h"

Car::Car()
{
}

Car::Car(Vector2f Position, Vector2f Size, String textures[8])
{
	// Initialize Data
	m_sfPosition = Position;
	m_sfSize = Size;
	m_iSteerDirection = 0;
	m_iMaxTurnAngle = 90;
	m_fSteerOrientation = 0;

	//load textures

	//base
	if (!m_sfTexture[0].loadFromFile(textures[0]))
	{
		cout << "Error: Base Texture was unable to load." << endl;
	};
	//rear lights
	if (!m_sfTexture[1].loadFromFile(textures[1]))
	{
		cout << "Error: rearlightsOFF was unable to load." << endl;
	};
	if (!m_sfTexture[2].loadFromFile(textures[2]))
	{
		cout << "Error: rearlightsON was unable to load." << endl;
	};
	//front lights
	if (!m_sfTexture[3].loadFromFile(textures[3]))
	{
		cout << "Error: frontlightsOFF was unable to load." << endl;
	};
	if (!m_sfTexture[4].loadFromFile(textures[4]))
	{
		cout << "Error: frontlightsON was unable to load." << endl;
	};

	//wheels
	if (!m_sfTexture[5].loadFromFile(textures[5]))
	{
		cout << "Error: rearWheels was unable to load." << endl;
	};
	if (!m_sfTexture[6].loadFromFile(textures[6]))
	{
		cout << "Error: frontLeftWheel was unable to load." << endl;
	};
	if (!m_sfTexture[7].loadFromFile(textures[7]))
	{
		cout << "Error: frontRightWheel was unable to load." << endl;
	};


	//Set Up drawables

	//base car
	m_sfCarRect.setPosition(m_sfPosition);
	m_sfCarRect.setSize(m_sfSize);
	m_sfCarRect.setRotation(m_fRotation);

	m_sfCarSprite.setTexture(m_sfTexture[0]);
	m_sfCarSprite.setScale(Vector2f(1, 1));
	m_sfCarSprite.setPosition(m_sfCarRect.getPosition().x + m_sfCarRect.getSize().x / 2.f, m_sfCarRect.getPosition().y + m_sfCarRect.getSize().y / 2.f);
	m_sfCarSprite.setOrigin(m_sfSize.x / 2, m_sfSize.y / 2);
	m_sfCarSprite.setRotation(m_fRotation);

	//Rear Wheels 
	m_sfWheelRect[0].setPosition(m_sfPosition);
	m_sfWheelRect[0].setSize(m_sfSize);
	m_sfWheelRect[0].setRotation(m_fRotation);

	m_sfWheelSprite[0].setTexture(m_sfTexture[5]);
	m_sfWheelSprite[0].setScale(Vector2f(1, 1));
	m_sfWheelSprite[0].setPosition(m_sfCarRect.getPosition().x + m_sfCarRect.getSize().x / 2.f, m_sfCarRect.getPosition().y + m_sfCarRect.getSize().y / 2.f);
	m_sfWheelSprite[0].setOrigin(m_sfSize.x / 2, m_sfSize.y / 2);
	m_sfWheelSprite[0].setRotation(m_fRotation);

	//Front left Wheels 
	m_sfWheelRect[1].setPosition(m_sfPosition);
	m_sfWheelRect[1].setSize(m_sfSize);
	m_sfWheelRect[1].setRotation(m_fRotation);

	m_sfWheelSprite[1].setTexture(m_sfTexture[6]);
	m_sfWheelSprite[1].setScale(Vector2f(1, 1));
	m_sfWheelSprite[1].setPosition(m_sfCarRect.getPosition().x + m_sfCarRect.getSize().x / 2.f, m_sfCarRect.getPosition().y + m_sfCarRect.getSize().y / 2.f);
	m_sfWheelSprite[1].setOrigin(m_sfSize.x / 2, m_sfSize.y / 2);
	m_sfWheelSprite[1].setRotation(m_fRotation);

	//Front right Wheels 
	m_sfWheelRect[2].setPosition(m_sfPosition);
	m_sfWheelRect[2].setSize(m_sfSize);
	m_sfWheelRect[2].setRotation(m_fRotation);

	m_sfWheelSprite[2].setTexture(m_sfTexture[7]);
	m_sfWheelSprite[2].setScale(Vector2f(1, 1));
	m_sfWheelSprite[2].setPosition(m_sfCarRect.getPosition().x + m_sfCarRect.getSize().x / 2.f, m_sfCarRect.getPosition().y + m_sfCarRect.getSize().y / 2.f);
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
		m_sfLightsSprite[0].setPosition(m_sfCarRect.getPosition().x + m_sfCarRect.getSize().x / 2.f, m_sfCarRect.getPosition().y + m_sfCarRect.getSize().y / 2.f);
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
		m_sfLightsSprite[0].setPosition(m_sfCarRect.getPosition().x + m_sfCarRect.getSize().x / 2.f, m_sfCarRect.getPosition().y + m_sfCarRect.getSize().y / 2.f);
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
		m_sfLightsSprite[1].setPosition(m_sfCarRect.getPosition().x + m_sfCarRect.getSize().x / 2.f, m_sfCarRect.getPosition().y + m_sfCarRect.getSize().y / 2.f);
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
		m_sfLightsSprite[1].setPosition(m_sfCarRect.getPosition().x + m_sfCarRect.getSize().x / 2.f, m_sfCarRect.getPosition().y + m_sfCarRect.getSize().y / 2.f);
		m_sfLightsSprite[1].setOrigin(m_sfSize.x / 2, m_sfSize.y / 2);
		m_sfLightsSprite[1].setRotation(m_fRotation);

	}

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
	m_sfCarRect.setRotation(m_fRotation);

	m_sfCarSprite.setTexture(m_sfTexture[0]);
	m_sfCarSprite.setScale(Vector2f(1, 1));
	m_sfCarSprite.setPosition(m_sfCarRect.getPosition().x + m_sfCarRect.getSize().x / 2.f, m_sfCarRect.getPosition().y + m_sfCarRect.getSize().y / 2.f);
	m_sfCarSprite.setOrigin(m_sfSize.x / 2, m_sfSize.y / 2);
	m_sfCarSprite.setRotation(m_fRotation);

	//Rear Wheels 
	m_sfWheelRect[0].setPosition(m_sfPosition);
	m_sfWheelRect[0].setSize(m_sfSize);
	m_sfWheelRect[0].setRotation(m_fRotation);

	m_sfWheelSprite[0].setTexture(m_sfTexture[5]);
	m_sfWheelSprite[0].setScale(Vector2f(1, 1));
	m_sfWheelSprite[0].setPosition(m_sfCarRect.getPosition().x + m_sfCarRect.getSize().x / 2.f, m_sfCarRect.getPosition().y + m_sfCarRect.getSize().y / 2.f);
	m_sfWheelSprite[0].setOrigin(m_sfSize.x / 2, m_sfSize.y / 2);
	m_sfWheelSprite[0].setRotation(m_fRotation);

	//Front left Wheels 
	m_sfWheelRect[1].setPosition(m_sfPosition);
	m_sfWheelRect[1].setSize(m_sfSize);
	m_sfWheelRect[1].setRotation(m_fRotation);

	m_sfWheelSprite[1].setTexture(m_sfTexture[6]);
	m_sfWheelSprite[1].setScale(Vector2f(1, 1));
	m_sfWheelSprite[1].setPosition(m_sfCarRect.getPosition().x + m_sfCarRect.getSize().x / 2.f, m_sfCarRect.getPosition().y + m_sfCarRect.getSize().y / 2.f);
	m_sfWheelSprite[1].setOrigin(m_sfSize.x / 2, m_sfSize.y / 2);
	m_sfWheelSprite[1].setRotation(m_fRotation);

	//Front right Wheels 
	m_sfWheelRect[2].setPosition(m_sfPosition);
	m_sfWheelRect[2].setSize(m_sfSize);
	m_sfWheelRect[2].setRotation(m_fRotation);

	m_sfWheelSprite[2].setTexture(m_sfTexture[7]);
	m_sfWheelSprite[2].setScale(Vector2f(1, 1));
	m_sfWheelSprite[2].setPosition(m_sfCarRect.getPosition().x + m_sfCarRect.getSize().x / 2.f, m_sfCarRect.getPosition().y + m_sfCarRect.getSize().y / 2.f);
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
		m_sfLightsSprite[0].setPosition(m_sfCarRect.getPosition().x + m_sfCarRect.getSize().x / 2.f, m_sfCarRect.getPosition().y + m_sfCarRect.getSize().y / 2.f);
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
		m_sfLightsSprite[0].setPosition(m_sfCarRect.getPosition().x + m_sfCarRect.getSize().x / 2.f, m_sfCarRect.getPosition().y + m_sfCarRect.getSize().y / 2.f);
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
		m_sfLightsSprite[1].setPosition(m_sfCarRect.getPosition().x + m_sfCarRect.getSize().x / 2.f, m_sfCarRect.getPosition().y + m_sfCarRect.getSize().y / 2.f);
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
		m_sfLightsSprite[1].setPosition(m_sfCarRect.getPosition().x + m_sfCarRect.getSize().x / 2.f, m_sfCarRect.getPosition().y + m_sfCarRect.getSize().y / 2.f);
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