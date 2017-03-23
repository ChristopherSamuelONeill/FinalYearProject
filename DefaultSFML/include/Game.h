#ifndef GAME_H
#define GAME_H

#include <iostream>
#include <SFML\Graphics.hpp>
#include <fstream>
#include <sstream>


#include "Car.h"
#include "TextureObject.h"
#include "SceneObject.h"
#include "Road.h"
#include "CollisionDetection.h"



using namespace sf;
using namespace std;

class Game
{

private:
	
	// \breif Function to load an xml file
	// \param Path to the level
	void loadLevel(string dir);

	vector<Car> m_vCars; // \breif list of cars for the scene
	SceneObject m_Background; // \breif Background for the level
	SceneObject m_Time; // \breif time of day overlay for level
	vector<SceneObject> m_vSceneObejcts; // \breif list of SceneObjects for the Scene
	vector<Road> m_vRoads; // \breif list of the roads

	TextureObject m_Gametextures;// \breif handle to all game textures

	// \breif Function to generate a grid for the map
	void generateSnapGrid();

	vector<Vector2f> m_vGridSystem; // \breif Vector containing grid system for map


	//editor objects
	int m_iCurrentBackground;// \breif int of the current background (used for cycling)
	int m_iLevelSize;// \breif int of the Level Size (used for cycling)
	int m_iLevelTime;// \breif int of the Level time (used for cycling)
	Vector2f m_sfSize; //breif Size of temp object

public:

	Game(); // \breif Default constructor of game object

	// \breif Overloaded constructor of game object
	// \param Path to the level
	Game(string dir);

	// \breif function to spawn car objects
	// \param path to car model
	void spawnCar(int cartype,Vector2f pos , Vector2f size);

	// \breif function to update scene
	// \param time change
	void updateScene(float dt);

	// \breif function to update scene
	// \param time change
	void drawScene(RenderWindow& window);

	Vector2f m_sfLevelSize;// \breif The dimensions of the level
	//editor functions-----------------------------

	// \breif function to cycle scene background
	void cycleBackground();
	
	// \breif function to cycle Level Size
	void cycleLevelSize();

	// \breif function to cycle Level time of day
	void cycleLevelTime();

	// \breif function to cycle Level time of day
	void saveLevelToFile(string dir);

	// \breif function to cycle Level time of day
	void spawnTempObject(Vector2f position,float rot,string type);

	RectangleShape m_sfTempRect; // \breif Temp Rect for editor 
	Sprite m_sfTempSprite; // \breif Temp Rect for editor 
	Texture m_sfTempTexture; // \breif Temp Texture for editor 
	bool m_bPlacingObject = false; // \breif True while placing an object

	void placeTrafficLights();

	// \breif function to attempt to place a road to the level
	// \param Position , vector of the position the object
	// \param Rotation , float of the orientation the object
	bool placeRoad(Vector2f position, float rot, string type);

	
	

};
#endif // !GAME_H