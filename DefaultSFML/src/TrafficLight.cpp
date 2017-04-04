#include "TrafficLight.h"


TrafficLight::TrafficLight()
{
	m_fTimePassed = 0;
}

TrafficLight::TrafficLight(Vector2f Pos, Vector2f Size, Texture textures[3], float Rotation, int state)
{
	m_sfPosition = Pos;
	m_sfVTopLeftPos = Pos;
	m_sfSize = Size;
	m_sfVSize = Size;
	m_fRotation = Rotation;
	m_iState = state;
	m_fTimePassed = 0;

	m_sfTextures[0] = textures[0];
	m_sfTextures[1] = textures[1];
	m_sfTextures[2] = textures[2];

	//set up drawbales
	m_sfRect.setPosition(m_sfPosition);
	m_sfRect.setSize(m_sfSize);
	
	m_sfRect.setRotation(m_fRotation);
	m_sfRect.setFillColor(Color::Red);

	
	m_sfSprite.setPosition(m_sfRect.getPosition());
	m_sfSprite.setRotation(m_fRotation);

}

void TrafficLight::draw(RenderTarget & target, RenderStates states) const
{
	target.draw(m_sfSprite);
}

void TrafficLight::update(float dt)
{
	//set up drawbales
	m_sfRect.setPosition(m_sfPosition);
	m_sfRect.setSize(m_sfSize);
	
	m_sfRect.setRotation(m_fRotation);
	m_sfRect.setFillColor(Color::Red);

	if (m_iState == 0 && m_iDesiredState == 0) // if currently red
	{
		m_fTimePassed = 0;
	}
	if (m_iState == 1 && m_iDesiredState == 0) // currently amber
	{
		m_fTimePassed += dt;
		if (m_fTimePassed > 2.0f)
		{
			m_iState = 0;
		}
	}
	if (m_iState == 2 && m_iDesiredState == 0) // if currently green
	{
		m_iState = 1; // switch to amber
	}

	if (m_iState == 0 && m_iDesiredState == 2) // if currently red
	{
		m_iState = 1; // switch to amber
	}
	if (m_iState == 1 && m_iDesiredState == 2) // currently amber
	{
		m_fTimePassed += dt;
		if (m_fTimePassed > 2.0f)
		{
			m_iState = 2;
		}
	}
	if (m_iState == 2 && m_iDesiredState == 2) // if currently green
	{

		m_fTimePassed = 0;
		
	}


	//decide on colour
	if (m_iState == 0) m_sfSprite.setTexture(m_sfTextures[0]);
	if (m_iState == 1) m_sfSprite.setTexture(m_sfTextures[1]);
	if (m_iState == 2) m_sfSprite.setTexture(m_sfTextures[2]);

	m_sfSprite.setPosition(m_sfRect.getPosition());

	m_sfSprite.setRotation(m_fRotation);


}

void TrafficLight::changeToRed()
{
	m_iDesiredState = 0;
	
}

void TrafficLight::changeToGreen()
{
	m_iDesiredState = 2;
}

Vector2f TrafficLight::getPosition()
{
	return m_sfPosition;
}

Vector2f TrafficLight::getSize()
{
	return m_sfSize;
}

float TrafficLight::getRotation()
{
	return m_fRotation;
}

RectangleShape TrafficLight::getCollisionBox()
{
	return m_sfRect;
}
