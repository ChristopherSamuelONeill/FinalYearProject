#include "..\include\Road.h"

Road::Road()
{
}

Road::Road(Vector2f Position, Vector2f Size, float Rotation, Texture texture)
{
	m_sfTexture = texture;
	m_sfPosition = Position;
	m_sfSize = Size;
	m_fRotation = Rotation;

	//set up drawbales
	m_sfRoadRect.setPosition(m_sfPosition);
	m_sfRoadRect.setSize(m_sfSize);
	m_sfRoadRect.setOrigin(m_sfSize / 2.0f);
	m_sfRoadRect.setRotation(m_fRotation);
	m_sfRoadRect.setFillColor(Color::Red);

	m_sfRoadSprite.setPosition(m_sfRoadRect.getPosition());
	m_sfRoadSprite.setTexture(m_sfTexture);
	m_sfRoadSprite.setOrigin(m_sfSize / 2.0f);
	m_sfRoadSprite.setRotation(m_fRotation);
}

void Road::draw(RenderTarget & target, RenderStates states) const
{
	target.draw(m_sfRoadSprite);
}

void Road::update()
{
	//set up drawbales
	m_sfRoadRect.setPosition(m_sfPosition);
	m_sfRoadRect.setSize(m_sfSize);
	m_sfRoadRect.setOrigin(m_sfSize / 2.0f);
	m_sfRoadRect.setRotation(m_fRotation);
	m_sfRoadRect.setFillColor(Color::Red);

	m_sfRoadSprite.setPosition(m_sfRoadRect.getPosition());
	m_sfRoadSprite.setTexture(m_sfTexture);
	m_sfRoadSprite.setOrigin(m_sfSize / 2.0f);
	m_sfRoadSprite.setRotation(m_fRotation);
}
