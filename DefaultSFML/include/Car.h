////////////////////////////////////////////////////////////
// Car.h
// Uses Car.cpp
////////////////////////////////////////////////////////////

#ifndef CAR_H
#define CAR_H

#define _USE_MATH_DEFINES

#include <iostream>
#include <SFML/Graphics.hpp>
#include "Controller.h"
#include <math.h>
#include <array>
#include "Sound.h"
#include "Profile.h"
#include "TrafficLight.h"
#include "CollisionDetection.h"

using namespace std;
using namespace sf;


class Car : public Drawable , public Controller
{
private:

	SoundObject *m_Sound;// \brief Sound object
	Sound m_engineSound;
	Sound m_idleSound;
	Sound m_BrakeSound;
	Profile *m_Player;// \brief Profile object

	bool m_bCarIdleSoundIsPlaying = false;
	bool m_bCarIsAtLights = false;
	bool m_bCarIsBehindCar = false;


	Vector2f m_sfSize; // \brief X Y size of car
	Vector2f m_sfVelocity; // \brief X Y speed of car

	void turnWheels(); // \brief sets the angle of the car wheels
	float m_fRotation; // \brief Orientation of car
	float m_iSteerDirection; // \brief 0 for straight -1 for left , 1 fo right
	int m_iMaxTurnAngle; // \brief Maximum angle the cars can turn
	float m_fSteerOrientation; // \brief Orientation of wheels

	int m_iNumbOfPointsOnRoute;// \brief How many nodes on the route
	int m_iCurrentNodeOnRoute;// \brief How far along the route
	Vector2f m_sfDesriredPoint;// \brief the next point for the car to reach

	bool m_bBraking = false;// \brief True when braking
	bool m_bLights = true;// \brief True when lights on

	Texture m_sfTexture[8];


	
	Sprite m_sfCarSprite; // \brief Sprite for the Car

	RectangleShape m_sfWheelRect[3];// \brief Rect for the wheels
	Sprite m_sfWheelSprite[3]; // \brief Sprite for the wheels

	RectangleShape m_sfLights[2];// \brief Rect for the lights front/back
	Sprite m_sfLightsSprite[2]; // \brief Sprite for the lights front/back

	

	void driveToPoint();// \brief Drives the car to the next point
	float m_fDrag;

	///////////////////////////////////////////////////////////
	/// \brief Vector2f for the acceleration of the colliadable
	////////////////////////////////////////////////////////////
	Vector2f m_mAcceleration;

	///////////////////////////////////////////////////////////
	/// \brief Float to store the mass of the collidable
	////////////////////////////////////////////////////////////
	float m_fMass;

	////////////////////////////////////////////////////////////
	/// \brief Opens throttle and removes braking
	////////////////////////////////////////////////////////////
	void applyDrivingForce();

	////////////////////////////////////////////////////////////
	/// \brief Opens or closes throttle
	///
	/// \param bool for opening and closing
	///
	////////////////////////////////////////////////////////////
	void openCloseThrottle(bool bOpen);

	////////////////////////////////////////////////////////////
	/// \brief closes throttle and starts braking
	////////////////////////////////////////////////////////////
	void applyBrakingForce();

	////////////////////////////////////////////////////////////
	/// \brief The rpm of the car
	////////////////////////////////////////////////////////////
	int m_iRPM;
	////////////////////////////////////////////////////////////
	/// \brief The current gear of the  car
	////////////////////////////////////////////////////////////
	int m_iGear;
	////////////////////////////////////////////////////////////
	/// \brief bool for the status of the throttle
	////////////////////////////////////////////////////////////
	bool m_bThrottle; //!< Is the throttle preesed or not 

	////////////////////////////////////////////////////////////
	/// \brief array of doubles of size 6 that stores the rate of acceleration per gear
	////////////////////////////////////////////////////////////
	array<double, 6> m_aiAccelerationRates; //!< Rates at which RPM increase by gear

	////////////////////////////////////////////////////////////
	/// \brief Scalar force used to push car forawrds
	////////////////////////////////////////////////////////////
	float m_fForce; // controlling the speed of the car

	////////////////////////////////////////////////////////////
	/// \brief power of the car used to make cars faster or slower
	////////////////////////////////////////////////////////////
	float m_fCarPower;

	////////////////////////////////////////////////////////////
	/// \brief Scalar speed of car
	////////////////////////////////////////////////////////////
	float m_fSpeed;
	////////////////////////////////////////////////////////////
	/// \brief vector for the center of the car , used in the bicycle steering model
	////////////////////////////////////////////////////////////
	Vector2f m_MiddleVector;

	////////////////////////////////////////////////////////////
	/// \brief distance between wheels
	////////////////////////////////////////////////////////////
	float m_fWheelBase;

	////////////////////////////////////////////////////////////
	/// \brief Current angle the car is steering
	////////////////////////////////////////////////////////////
	float m_fSteeringAngle;

	////////////////////////////////////////////////////////////
	/// \brief Scalar value for accerlaration
	////////////////////////////////////////////////////////////
	float fAcceleration;

	

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
	/// \param rotation float rotation of car (0 is point right)
	////////////////////////////////////////////////////////////
	Car(Vector2f Position, Vector2f Goal, Vector2f Size, Texture textures[8],float rotation);

	Vector2f getPosition();
	
	RectangleShape m_sfCarRect;// \brief Rect for the Car
	RectangleShape m_sfRearRect;// \brief Rect for the Cars rear (car behind will brake)
	bool m_bFinished = false;
	void startPathFinding();
	void draw(RenderTarget& target, RenderStates states) const;
	void update(float dt);
	void CheckForTrafficLight(TrafficLight &trafficLight);
	void CheckForCar(Car &car);
	void setTimeOfDay(int time);
	void SetTurning(int iDirection); // -1 left , 1right , 0 straight
};


#endif // !CAR_H
