#ifndef TRAFFICLIGHT_H
#define TRAFFICLIGHT_H

#include <SFML\Graphics.hpp>


using namespace sf;

class TrafficLight : public Drawable
{
public:

	// \breif Default constructor of TrafficLight
	TrafficLight();

	// \breif Overloaded constructor of TrafficLight
	// \param Postion of TrafficLight
	// \param Size of TrafficLight
	// \param Texture of TrafficLight
	// \param Rotation of TrafficLight
	// \param State of TrafficLight (r y g)
	TrafficLight(Vector2f Pos, Vector2f Size, Texture textures[3], float Rotation, int state);

	// \breif Render function , draws object
	void draw(RenderTarget& target, RenderStates states) const;

	// \breif Updates object
	void update();

	// \breif Changes the traffic light to red , returns true when finished
	// \param DeltaTime , amount of time passed (should be called every frame untill returning true)
	bool changeToRed(float dt);

	// \breif Changes the traffic light to green , returns true when finished
	// \param DeltaTime , amount of time passed (should be called every frame untill returning true)
	bool changeToGreen(float dt);

private:
	Vector2f m_sfPosition; 	// \breif X Y coords of the object
	Vector2f m_sfSize;		// \breif Dimensions of the object
	float m_fRotation;		// \breif oreientation of the object
	int m_iState;			// \breif 0 red , 1 amber , 2 green.
	float m_fTimePassed;	// \breif used to track time delays (for changing sequence)

	RectangleShape m_sfRect;// \breif Rectangle representing the traffic lights poistion
	Sprite m_sfSprite;// \breif Sprite of the traffic light for drawing 
	Texture m_sfTextures[3];

};

#endif SCENEOBJECT_H