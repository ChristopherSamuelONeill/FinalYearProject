#ifndef GAME_H
#define GAME_H

#include <iostream>
#include <SFML\Graphics.hpp>

#include "tinyxml2.h"
#include "Car.h"
#include "TextureObject.h"
#include "SceneObject.h"

using namespace sf;
using namespace std;

class Game
{

private:
	
	// \breif Function to load an xml file
	// \param Path to the level
	void loadLevel(const char dir[]);

	vector<Car> m_vCars; // \breif list of cars for the scene
	SceneObject m_Background; // \breif Background for the level
	SceneObject m_Time; // \breif time of day overlay for level
	vector<SceneObject> m_vSceneObejcts; // \breif list of SceneObjects for the Scene


	TextureObject m_Gametextures;// \breif handle to all game textures


	//editor objects
	int m_iCurrentBackground;// \breif int of the current background (used for cycling)
	int m_iLevelSize;// \breif int of the Level Size (used for cycling)
	int m_iLevelTime;// \breif int of the Level time (used for cycling)

public:

	Game(); // \breif Default constructor of game object

	// \breif Overloaded constructor of game object
	// \param Path to the level
	Game(const char dir[]);

	// \breif function to spawn car objects
	// \param path to car model
	void spawnCar(int cartype,Vector2f pos , Vector2f size);

	// \breif function to update scene
	// \param time change
	void updateScene(float dt);

	// \breif function to update scene
	// \param time change
	void drawScene(RenderWindow& window);

	//editor functions-----------------------------

	// \breif function to cycle scene background
	void cycleBackground();
	
	// \breif function to cycle Level Size
	void cycleLevelSize();

	// \breif function to cycle Level time of day
	void cycleLevelTime();

	// \breif function to cycle Level time of day
	void spawnTempRoad(Vector2f position);

	void placeRoad();

	Vector2f m_sfLevelSize;// \breif Function to load an xml file
	

};
#endif // !GAME_H