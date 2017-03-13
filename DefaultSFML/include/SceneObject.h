#ifndef SCENEOBJECT_H
#define SCENEOBJECT_H

#include <iostream>
#include <SFML\Graphics.hpp>

using namespace sf;


class SceneObject : public Drawable
{

private :
	RectangleShape m_sfRect;
	Sprite m_sfSprite;
	Texture m_sfTexture;

	Vector2f m_sfPosition;
	Vector2f m_sfSize;
	float m_fRotation;

public:

	// \breif Default constructor of scene object
	SceneObject();

	// \breif Default constructor of scene object
	// \param Postion of sceneObject
	// \param Size sceneObject
	// \param Texture of sceneObject
	// \param Rotation of sceneObject
	SceneObject(Vector2f Pos, Vector2f Size, Texture Texture,float Rotation);

	// \breif Updates object
	void update();

	// \breif Render function , draws object
	void draw(RenderTarget& target, RenderStates states) const;

	// \breif function to update objects texture
	// \param Texture of sceneObject
	void setTexture(Texture newTexture);

	// \breif function to update objects postion
	// \param Postion of sceneObject
	void setPosistion(Vector2f newPos);

	// \breif function to update objects size
	// \param Size sceneObject
	void setSize(Vector2f newSize);

	// \breif function to change objects rotation
	// \param Rotation , amount to change rotation by
	void incrementRotation(float increment);

};

#endif SCENEOBJECT_H