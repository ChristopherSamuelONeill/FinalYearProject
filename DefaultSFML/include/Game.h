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
	vector<SceneObject> m_vSceneObejcts; // \breif list of SceneObjects for the Scene


	TextureObject m_Gametextures;// \breif handle to all game textures

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

	

};
#endif // !GAME_H