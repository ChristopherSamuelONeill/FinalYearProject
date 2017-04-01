////////////////////////////////////////////////////////////
// Car.h
// Uses Car.cpp
////////////////////////////////////////////////////////////

#ifndef CAR_H
#define CAR_H

#include <iostream>
#include <SFML/Graphics.hpp>
#include "Controller.h"

using namespace std;
using namespace sf;


class Car : public Drawable , public Controller
{
private:

	Vector2f m_sfSize; // \brief X Y size of car
	Vector2f m_sfVelocity; // \brief X Y speed of car

	void turnWheels(); // \brief sets the angle of the car wheels
	float m_fRotation; // \brief Orientation of car
	float m_iSteerDirection; // \brief 0 for straight -1 for left , 1 fo right
	int m_iMaxTurnAngle; // \brief Maximum angle the cars can turn
	float m_fSteerOrientation; // \brief Orientation of wheels

	bool m_bBraking = true;// \brief True when braking
	bool m_bLights = true;// \brief True when lights on

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
	/// \param Position Vector2f Position of car
	/// \param Goal Vector2f Poistion the car wants to reach
	/// \param size sVector2f size of the button
	/// \param Textures String Locations of the textures
	////////////////////////////////////////////////////////////
	Car(Vector2f Position, Vector2f Goal, Vector2f Size, Texture textures[8]);


	void startPathFinding();
	void draw(RenderTarget& target, RenderStates states) const;
	void update(float dt);
	void setTimeOfDay(int time);
	void SetTurning(int iDirection);
};


#endif // !CAR_H
