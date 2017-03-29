#ifndef SCENEOBJECT_H
#define SCENEOBJECT_H

#include <iostream>
#include <SFML\Graphics.hpp>

using namespace std;
using namespace sf;


class SceneObject : public Drawable
{

private :
	RectangleShape m_sfRect;
	Sprite m_sfSprite;
	Texture m_sfTexture;

public:

	// \brief Default constructor of scene object
	SceneObject();

	// \brief Default constructor of scene object
	// \param Name the name of the texture (used for the saving)
	SceneObject(char Name[]);

	// \brief Default constructor of scene object
	// \param Postion of sceneObject
	// \param Size sceneObject
	// \param Texture of sceneObject
	// \param Rotation of sceneObject
	// \param Name the name of the texture (used for the saving)
	SceneObject(Vector2f Pos, Vector2f Size, Texture Texture, float Rotation);

	// \brief Updates object
	void update();

	// \brief Render function , draws object
	void draw(RenderTarget& target, RenderStates states) const;

	// \brief function to update objects texture
	// \param Texture of sceneObject
	void setTexture(Texture newTexture, char Name[]);

	// \brief function to update objects postion
	// \param Postion of sceneObject
	void setPosistion(Vector2f newPos);

	// \brief function to update objects size
	// \param Size sceneObject
	void setSize(Vector2f newSize);

	// \brief function to change objects rotation
	// \param Rotation , amount to change rotation by
	void incrementRotation(float increment);

	Vector2f m_sfPosition; 	// \brief X Y coords of the object
	Vector2f m_sfSize;// \brief Dimensions of the object
	float m_fRotation;// \brief oreientation of the object
	

	

};

#endif SCENEOBJECT_H