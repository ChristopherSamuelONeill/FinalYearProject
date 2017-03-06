////////////////////////////////////////////////////////////
// Car.h
// Uses Car.cpp
////////////////////////////////////////////////////////////

#ifndef CAR_H
#define CAR_H

#include <iostream>
#include <SFML/Graphics.hpp>

#include "tinyxml2.h"

using namespace std;
using namespace sf;

class Car : public Drawable
{
private:

	Vector2f m_sfSize; // \brief X Y size of car
	Vector2f m_sfPosition; // \brief X Y position of car
	Vector2f m_sfVelocity; // \breif X Y speed of car

	void turnWheels(); // \brief sets the angle of the car wheels
	float m_fRotation; // \brief Orientation of car
	float m_iSteerDirection; // \breif 0 for straight -1 for left , 1 fo right
	int m_iMaxTurnAngle; // \breif Maximum angle the cars can turn
	float m_fSteerOrientation; // \breif Orientation of wheels

	bool m_bBraking = true;// \breif True when braking
	bool m_bLights = true;// \breif True when lights on

	Texture m_sfTexture[8];

	RectangleShape m_sfCarRect;// \brief Rect for the Car
	Sprite m_sfCarSprite; // \brief Sprite for the Car

	RectangleShape m_sfWheelRect[3];// \brief Rect for the wheels
	Sprite m_sfWheelSprite[3]; // \brief Sprite for the wheels

	RectangleShape m_sfLights[2];// \brief Rect for the lights front/back
	Sprite m_sfLightsSprite[2]; // \brief Sprite for the lights front/back


public:

	////////////////////////////////////////////////////////////
	/// \brief Default Constructor
	/// Creates an empty car
	////////////////////////////////////////////////////////////
	Car();

	////////////////////////////////////////////////////////////
	/// \brief Overloaded Constructor
	///
	/// Creates the car with its parameteres
	///
	/// \param Position Vector2f Posituon of car
	/// \param size sVector2f size of the button
	/// \param Textures String Locations of the textures
	////////////////////////////////////////////////////////////
	Car(Vector2f Position, Vector2f Size, Texture textures[8]);



	void draw(RenderTarget& target, RenderStates states) const;
	void update(float dt);

	void SetTurning(int iDirection);
};


#endif // !CAR_H
