#ifndef TRAFFICLIGHT_H
#define TRAFFICLIGHT_H

#include <SFML\Graphics.hpp>


using namespace sf;

class TrafficLight : public Drawable
{
public:

	// \brief Default constructor of TrafficLight
	TrafficLight();

	// \brief Overloaded constructor of TrafficLight
	// \param Postion of TrafficLight
	// \param Size of TrafficLight
	// \param Texture of TrafficLight
	// \param Rotation of TrafficLight
	// \param State of TrafficLight (r y g)
	TrafficLight(Vector2f Pos, Vector2f Size, Texture textures[3], float Rotation, int state);

	// \brief Render function , draws object
	void draw(RenderTarget& target, RenderStates states) const;

	// \brief Updates object
	void update();

	// \brief Changes the traffic light to red , returns true when finished
	// \param DeltaTime , amount of time passed (should be called every frame untill returning true)
	bool changeToRed(float dt);

	// \brief Changes the traffic light to green , returns true when finished
	// \param DeltaTime , amount of time passed (should be called every frame untill returning true)
	bool changeToGreen(float dt);

	// \brief Vector 2f Returns the position of the light
	Vector2f getPosition();

	// \brief Vector 2f Returns the size of the light
	Vector2f getSize();

	// \brief Float Returns the roation of the light
	float getRotation();

	// \brief Vector 2f Returns the rectangle for the Light
	RectangleShape getCollisionBox();


	int m_iState;			// \brief 0 red , 1 amber , 2 green.

private:
	Vector2f m_sfPosition; 	// \brief X Y coords of the object
	Vector2f m_sfSize;		// \brief Dimensions of the object
	float m_fRotation;		// \brief oreientation of the object
	
	float m_fTimePassed;	// \brief used to track time delays (for changing sequence)

	RectangleShape m_sfRect;// \brief Rectangle representing the traffic lights poistion
	Sprite m_sfSprite;// \brief Sprite of the traffic light for drawing 
	Texture m_sfTextures[3];

};

#endif SCENEOBJECT_H