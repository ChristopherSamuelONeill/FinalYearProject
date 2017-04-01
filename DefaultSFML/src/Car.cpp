#include "Car.h"



Car::Car()
{
	
}

Car::Car(Vector2f Position, Vector2f Goal, Vector2f Size, Texture textures[8], float rotation)
{
	

	// Initialize Data
	m_sfPosition = Position;
	m_sfSize = Size;
	m_iSteerDirection = 0;
	m_iMaxTurnAngle = 90;
	m_fSteerOrientation = 0;
	m_fRotation = 0;
	m_fMass = 500;
	m_fCarPower = 35;
	m_fRotation = rotation;


	m_sfStart = Position;
	m_sfGoal = Goal;
	m_sfDesriredPoint = Goal;

	
	m_bBraking = false;
	m_iGear = 0;
	m_bThrottle = false;
	m_fDrag = 0.2;
	m_iRPM = 0;

	m_mAcceleration = Vector2f(0, 0);
	m_sfVelocity = Vector2f(0, 0);
	fAcceleration = 0;


	// Set up gear ratios
	m_aiAccelerationRates.at(0) = 60;
	m_aiAccelerationRates.at(1) = 20;
	m_aiAccelerationRates.at(2) = 12;
	m_aiAccelerationRates.at(3) = 6;
	m_aiAccelerationRates.at(4) = 3;
	m_aiAccelerationRates.at(5) = 1;

	m_sfTexture[0] = textures[0]; // car
	m_sfTexture[1] = textures[1];// rear lights
	m_sfTexture[2] = textures[2];// rear lights
	m_sfTexture[3] = textures[3];// front lights
	m_sfTexture[4] = textures[4];// front lights
	m_sfTexture[5] = textures[5];// rear wheels
	m_sfTexture[6] = textures[6];// front wheels
	m_sfTexture[7] = textures[7];// front wheels



}

Vector2f Car::getPosition()
{
	return m_sfPosition;
}

void Car::applyDrivingForce()
{
	openCloseThrottle(true);
	m_bBraking = false;
}

void Car::openCloseThrottle(bool bOpen)
{
	m_bThrottle = bOpen;
}

void Car::driveToPoint()
{
	//find vector between car and goal
	Vector2f directionVector = m_sfDesriredPoint - m_sfPosition;
	float magDist = sqrt((directionVector.x * directionVector.x) + (directionVector.y * directionVector.y));

	// find car orientatian
	if (m_fRotation < 0)//negative
	{
		m_fRotation = 360 + m_fRotation;
	}
	else if (m_fRotation > 360)
	{
		m_fRotation = m_fRotation - 360;
	}
	int carAngle = m_fRotation;


	float angle = atan2((m_sfDesriredPoint.y - m_sfPosition.y), (m_sfDesriredPoint.x - m_sfPosition.x))*(180 / M_PI);

	// find car orientatian
	if (angle < 0)//negative
	{
		angle = 360 + angle;
	}
	else if (angle > 360)
	{
		angle = angle - 360 ;
	}

	//decide how to drive
	if (carAngle + 5 < angle)SetTurning(1);
	else if  (angle + 5 < carAngle )SetTurning(-1);
	else SetTurning(0);
	

	if (magDist  < 200 + (m_fSpeed / 2 )) applyBrakingForce();
	else if (magDist < 300 + (m_fSpeed / 2)) m_bThrottle = false;
	else applyDrivingForce();
	


}

void Car::applyBrakingForce()
{
	openCloseThrottle(false);
	m_bBraking = true;
}

void Car::startPathFinding()
{
	//generatePath();
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

	driveToPoint();
	
	////bicycle model-----------------------------------------------------

	//find middle
	m_MiddleVector = Vector2f(m_sfPosition.x + (m_sfSize.y / 2), m_sfPosition.y + (m_sfSize.y / 2));
	// find wheel base
	m_fWheelBase = m_sfSize.x * 0.8;



	// finds steering angle
	turnWheels();

	//find unitVector of rotation
	Vector2f unitNormal(1, 0);
	Vector2f carOrientationVector(
		(cos(m_fRotation*(M_PI / 180)) * unitNormal.x)
		+ (-sin(m_fRotation*(M_PI / 180)) * unitNormal.y),
		(sin(m_fRotation*(M_PI / 180)) * unitNormal.x)
		+ (cos(m_fRotation*(M_PI / 180)) * unitNormal.y));

	Vector2f steerOrientationVector(
		(cos(((m_fSteerOrientation + m_fRotation)*(M_PI / 180))) * unitNormal.x)
		+ (-sin(((m_fSteerOrientation + m_fRotation)*(M_PI / 180))) * unitNormal.y),
		(sin((m_fSteerOrientation + m_fRotation)*(M_PI / 180)) * unitNormal.x) +
		(cos(((m_fSteerOrientation + m_fRotation)*(M_PI / 180))) * unitNormal.y));

	//find position of wheels
	Vector2f frontWheel(m_MiddleVector.x + carOrientationVector.x *(m_fWheelBase / 2), m_MiddleVector.y + carOrientationVector.y *(m_fWheelBase / 2));
	Vector2f backWheel(m_MiddleVector.x - carOrientationVector.x *(m_fWheelBase / 2), m_MiddleVector.y - carOrientationVector.y *(m_fWheelBase / 2));

	//find displacement

	m_fSpeed = sqrt((m_sfVelocity.x * m_sfVelocity.x) + (m_sfVelocity.y * m_sfVelocity.y));

	float displacement = m_fSpeed * dt;

	//move by displacement along steering angle
	frontWheel = Vector2f(frontWheel.x + (steerOrientationVector.x * displacement), frontWheel.y + (steerOrientationVector.y * displacement));
	backWheel = Vector2f(backWheel.x + (carOrientationVector.x * displacement), backWheel.y + (carOrientationVector.y * displacement));

	//new position of car is avergae of wheels
	m_MiddleVector = Vector2f((frontWheel.x + backWheel.x) / 2, (frontWheel.y + backWheel.y) / 2);
	//m_sfPosition = Vector2f(m_MiddleVector.x - (m_sfSize.x / 2), m_MiddleVector.y - (m_sfSize.y / 2));

	////update rotation
	m_fRotation = atan2((frontWheel.y - backWheel.y), (frontWheel.x - backWheel.x))*(180 / M_PI);

	

	//gearing and rpm-----------------------------------------------------
	if (m_bThrottle) // if the throttle is open
	{
		m_iRPM += 2.2 * m_aiAccelerationRates.at(m_iGear); // increase rpm by the current gear ratio
		if (m_iGear < 5)
		{
			if (m_iRPM > 4000)
			{
				//change gear
				m_iGear++;

				//loose some revs
				if (m_iGear > 0)
				{
					m_iRPM -= 4500 / m_iGear;
				}
				else
				{
					m_iRPM -= 4500;
				}
			}
		}
		else if (m_iRPM >= 5000)
		{
			//hit limit
			m_iRPM = 5000;
		}
	}
	else // throttle is closed
	{

		// decrease rpm
		if (m_bBraking)
		{
			m_iRPM -= 1.45*m_aiAccelerationRates.at(m_iGear); // decrease rpm by the current gear ratio
		}
		else
		{
			m_iRPM -= 0.9*m_aiAccelerationRates.at(m_iGear); // decrease rpm by the current gear ratio
		}

		if (m_iGear > 1)
		{
			if (m_iRPM < 10 + 1200 * m_iGear)
			{
				//change down a gear
				m_iGear--;
				//gain some revs
				m_iRPM += 100;
			}
		}

		if (m_iRPM <= 0)
		{
			m_iRPM = 0;
		}
	}


	if (m_iGear > 0) // driving foward ------------------------------------------
	{

		if (m_bBraking)
		{
			//if braking incrases frictional force on car
			m_fForce = m_fCarPower * m_iRPM * m_iGear;
			fAcceleration = (m_fForce / m_fMass);
			if (m_fDrag <= 0.8)
			{
				cout << m_fDrag << endl;
				m_fDrag += 0.0025;
			}


		}
		else
		{
			// apply driving force
			m_fForce = m_fCarPower * m_iRPM * m_iGear;
			m_fDrag = 0.2;

			fAcceleration = (m_fForce / m_fMass);
		}

	}

	// suvat variables
	Vector2f s = Vector2f(0, 0);
	Vector2f s1;
	Vector2f u = Vector2f(0, 0);
	Vector2f v = Vector2f(0, 0);
	Vector2f a = Vector2f(0, 0);
	float t;

	// initialize values
	s1 = m_sfPosition;
	u = Vector2f(m_sfVelocity.x, m_sfVelocity.y);
	t = dt;
	Vector2f Drag(m_sfVelocity.x * m_fDrag * 9.8, m_sfVelocity.y * m_fDrag * 9.8);
	a = Vector2f((fAcceleration * carOrientationVector.x) - Drag.x, (fAcceleration* carOrientationVector.y) - Drag.y);


	// perform eular calculation 
	v = Vector2f((u.x + (a.x*t)), ((u.y + (a.y * t))));
	s = Vector2f(s1.x + u.x*t, s1.y + u.y*t);
	m_mAcceleration = a;

	// update car with new values
	m_sfVelocity = v;
	m_sfPosition = s;
	

	//Set Up drawables

	//base car
	m_sfCarRect.setPosition(m_sfPosition);
	m_sfCarRect.setSize(m_sfSize);
	m_sfCarRect.setFillColor(Color::Red);
	m_sfCarRect.setOrigin(m_sfSize.x / 2, m_sfSize.y / 2);
	m_sfCarRect.setRotation(m_fRotation);

	m_sfCarSprite.setTexture(m_sfTexture[0]);
	m_sfCarSprite.setPosition(m_sfCarRect.getPosition());
	m_sfCarSprite.setOrigin(m_sfSize.x / 2, m_sfSize.y / 2);
	m_sfCarSprite.setRotation(m_fRotation);


	//Rear Wheels 
	m_sfWheelRect[0].setPosition(backWheel);
	m_sfWheelRect[0].setSize(m_sfSize);
	m_sfWheelRect[0].setRotation(m_fRotation);

	m_sfWheelSprite[0].setTexture(m_sfTexture[5]);
	m_sfWheelSprite[0].setPosition(m_sfCarRect.getPosition());
	m_sfWheelSprite[0].setOrigin(m_sfSize.x / 2, m_sfSize.y / 2);
	m_sfWheelSprite[0].setRotation(m_fRotation);

	//Front left Wheels 
	m_sfWheelRect[1].setPosition(frontWheel);
	m_sfWheelRect[1].setSize(m_sfSize);
	m_sfWheelRect[1].setRotation(m_fRotation);

	m_sfWheelSprite[1].setTexture(m_sfTexture[6]);
	m_sfWheelSprite[1].setPosition(m_sfCarRect.getPosition().x, m_sfCarRect.getPosition().y + 25);
	m_sfWheelSprite[1].setOrigin(m_sfSize.x / 2, m_sfSize.y / 2);
	m_sfWheelSprite[1].setRotation(m_fRotation);

	//Front right Wheels 
	m_sfWheelRect[2].setPosition(frontWheel);
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

void Car::setTimeOfDay(int time)
{
	//lights on
	if (time == 3 || time == 4 || time == 5)
	{
		m_bLights = true;
	}
	else // lights off
	{
		m_bLights = false;
	}
}

void Car::SetTurning(int iDirection)
{
	m_iSteerDirection = iDirection;
	
	
}

void Car::turnWheels()
{
	//set a speed to turn the wheels at
	float fTurnSpeed = 2.0f;

	//find the speed the car is moving at 
	float fSpeed = sqrt((m_sfVelocity.x * m_sfVelocity.x) + (m_sfVelocity.y * m_sfVelocity.y));
	
	//ensure there is no division by 0
	fSpeed = abs(fSpeed);
	if (fSpeed < 1) fSpeed = 1;

	fSpeed /= 100;

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

