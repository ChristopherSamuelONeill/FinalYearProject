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
	
	// \breif Function to load an xml file
	// \param Path to the level
	void loadLevel(const char dir[]);



public:

	vector<Car> m_vCars; // \breif list of cars for the scene


	Game(); // \breif Default constructor of game object

	// \breif Overloaded constructor of game object
	// \param Path to the level
	Game(const char dir[]);

	// \breif function to spawn car objects
	// \param path to car model
	void spawnCar(const char dir[]);

	

};
#endif // !GAME_H