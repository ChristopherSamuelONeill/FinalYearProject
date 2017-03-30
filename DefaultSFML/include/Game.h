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
#include "Sound.h"
#include "Profile.h"
#include "Pedestrian.h"


using namespace sf;
using namespace std;

class Game
{

private:
	
	// \brief Function that creates "m_uiNumbofCars" number of cars 
	void generateCars();

	// \brief Function that creates "m_uiNumbofPed" number of pedestrians 
	void generatePedestrians();


	// \brief Function to load an xml file
	// \param Path to the level
	void loadLevel(string dir);

	
	vector<Car> m_vCars; // \brief list of cars for the scene
	vector<Pedestrian> m_vPedestrians;// \brief list of pedestrians for the scene
	SceneObject m_Background; // \brief Background for the level
	SceneObject m_Time; // \brief time of day overlay for level
	vector<SceneObject> m_vSceneObejcts; // \brief list of SceneObjects for the Scene
	vector<Road> m_vRoads; // \brief list of the roads
	vector<RectangleShape> m_vCarsStartPostions;// \brief vector of all the start positions
	vector<RectangleShape> m_vCarsEndPostions;// \brief vector of all the start positions

	TextureObject *m_Gametextures;// \brief handle to all game textures

	// \brief Function to generate a grid for the map
	void generateSnapGrid();

	vector<Vector2f> m_vGridSystem; // \brief Vector containing grid system for map

	SoundObject *m_Sound;// \brief Sound object
	Profile *m_Player;// \brief Sound object


	//editor objects
	int m_iCurrentBackground;// \brief int of the current background (used for cycling)
	int m_iLevelSize;// \brief int of the Level Size (used for cycling)
	int m_iLevelTime;// \brief int of the Level time (used for cycling)
	Vector2f m_sfSize; //brief Size of temp object
	bool m_bEditorMode; //brief bool of wetaher game is in editor mode or not (false for not)



public:

	Game(); // \brief Default constructor of game object

	// \brief Overloaded constructor of game object
	// \param Path to the level
	Game(string dir);

	// \brief function to spawn car objects
	// \param path to car model
	void spawnCar(int cartype,Vector2f pos , Vector2f size);

	// \brief function to update scene
	// \param time change
	void updateScene(float dt);

	// \brief function to update scene
	// \param time change
	void drawScene(RenderWindow& window);

	// \brief function to clear scene
	void closeGame();

	unsigned int m_uiNumbofCars; // \brief Number of cars that will spawn for the level
	unsigned int m_uiNumbofPed; // \brief Number of pedestrians that will spawn for the level

	Vector2f m_sfLevelSize;// \brief The dimensions of the level

	//editor functions-----------------------------

	// \brief function to cycle scene background
	void cycleBackground();
	
	// \brief function to cycle Level Size
	void cycleLevelSize();

	// \brief function to cycle Level time of day
	void cycleLevelTime();

	// \brief function to save the current scene to a file
	// \param dir , string location of the map file
	void saveLevelToFile(string dir);

	// \brief function to spawn a temporary object (rendered in the editor)
	// \param Position , vector of the position the object
	// \param Rot , float of the orientation the object
	// \param type , string of the type of temp object
	void spawnTempObject(Vector2f position,float rot,string type);

	RectangleShape m_sfTempRect; // \brief Temp Rect for editor 
	Sprite m_sfTempSprite; // \brief Temp Sprite for editor 
	Texture m_sfTempTexture; // \brief Temp Texture for editor 
	
	bool m_bPlacingObject = false; // \brief True while placing an object

	void placeTrafficLights();

	// \brief function to attempt to place a road to the level
	// \param Position , vector of the position the object
	// \param Rotation , float of the orientation the object
	bool placeRoad(Vector2f position, float rot, string type);

	
	

};
#endif // !GAME_H