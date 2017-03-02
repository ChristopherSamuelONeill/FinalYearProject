#include "Car.h"

Car::Car()
{
}

Car::Car(Vector2f Position, Vector2f Size)
{
	// Initialize Data
	m_sfPosition = Position;
	m_sfSize = Size;
	m_iSteerDirection = 0;
	m_iMaxTurnAngle = 90;
	m_fSteerOrientation = 0;


	//Set Up drawables
	m_sfCarRect.setPosition(m_sfPosition);
	m_sfCarRect.setSize(m_sfSize);
	m_sfCarRect.setRotation(m_fRotation);



}

void Car::draw(RenderTarget & target, RenderStates states) const
{
	target.draw(m_sfCarSprite);
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