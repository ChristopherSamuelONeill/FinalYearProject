////////////////////////////////////////////////////////////
// Car.h
// Uses Car.cpp
////////////////////////////////////////////////////////////

#ifndef CAR_H
#define CAR_H

#include <SFML/Graphics.hpp>

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

	RectangleShape m_sfCarRect;// \brief Rect for the Car
	Sprite m_sfCarSprite; // \brief Sprite for the Car

	RectangleShape m_sfWheelRect[4];// \brief Rect for the wheels
	Sprite m_sfWheelSprite[4]; // \brief Sprite for the wheels


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
	////////////////////////////////////////////////////////////
	Car(Vector2f Position, Vector2f Size);

	void draw(RenderTarget& target, RenderStates states) const;

	void SetTurning(int iDirection);
};


#endif // !CAR_H
