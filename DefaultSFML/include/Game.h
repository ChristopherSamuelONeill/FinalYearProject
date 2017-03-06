#ifndef GAME_H
#define GAME_H

#include <iostream>
#include <SFML\Graphics.hpp>

#include "tinyxml2.h"
#include "Car.h"

using namespace sf;
using namespace std;

class Game
{

private:
	vector<Car> m_vCars; // \breif list of cars for the scene

	// \breif Function to load an xml file
	// \param Path to the level
	void loadLevel(const char dir[]);


public:
	Game(); // \breif Default constructor of game object

	// \breif Overloaded constructor of game object
	// \param Path to the level
	Game(string Level); 

	// \breif function to spawn car objects
	// \param path to car model
	void spawnCar(const char dir[]);

	// \breif function to draw objects within scene
	// \param renderWindow Window pointer to the render object
	void drawScene(RenderWindow& renderWindow);

};
#endif // !GAME_H