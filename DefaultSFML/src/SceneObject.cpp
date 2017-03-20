#include "..\include\SceneObject.h"



SceneObject::SceneObject()
{
}

SceneObject::SceneObject(char Name[])
{
}

SceneObject::SceneObject(Vector2f Pos, Vector2f Size, Texture Texture, float Rotation, char Name[])
{
	m_sfTexture = Texture;
	m_sfPosition = Pos;
	m_sfSize = Size;
	m_fRotation = Rotation;
	//m_cName = Name;

	//set up drawbales
	m_sfRect.setPosition(m_sfPosition);
	m_sfRect.setSize(m_sfSize);
	m_sfRect.setOrigin(m_sfSize / 2.0f);
	m_sfRect.setRotation(m_fRotation);
	m_sfRect.setFillColor(Color::Red);

	m_sfTexture.setRepeated(true);
	m_sfSprite.setPosition(m_sfRect.getPosition());
	m_sfSprite.setTexture(m_sfTexture);
	m_sfSprite.setOrigin(m_sfSize / 2.0f);
	m_sfSprite.setRotation(m_fRotation);
}

void SceneObject::update()
{
	//ensure all emements are up to date
	m_sfRect.setPosition(m_sfPosition);
	m_sfRect.setSize(m_sfSize);
	//m_sfRect.setOrigin(m_sfSize / 2.0f);
	m_sfRect.setRotation(m_fRotation);
	m_sfRect.setFillColor(Color::Red);

	m_sfTexture.setRepeated(true);
	m_sfSprite.setTextureRect({ 0,0,(int)m_sfSize.x,(int)m_sfSize.y });

	m_sfSprite.setPosition(m_sfRect.getPosition());
	m_sfSprite.setTexture(m_sfTexture);
	m_sfSprite.setOrigin(m_sfSize / 2.0f);
	m_sfSprite.setRotation(m_fRotation);
	
	

}

void SceneObject::draw(RenderTarget & target, RenderStates states) const
{
	//draw the sprite
	target.draw(m_sfSprite);
}

void SceneObject::setTexture(Texture newTexture, char Name[])
{
	m_sfTexture = newTexture;
	//m_sName = Name;


}

void SceneObject::setPosistion(Vector2f newPos)
{
	m_sfPosition = newPos;
}

void SceneObject::setSize(Vector2f newSize)
{
	m_sfSize = newSize;
}

void SceneObject::incrementRotation(float increment)
{
	m_fRotation += increment;
}
