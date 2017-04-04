#ifndef TEXTUREOBJECT_H
#define TEXTUREOBJECT_H

#include <iostream>
#include <SFML\Graphics.hpp>

using namespace std;
using namespace sf;

class TextureObject
{
public:
	TextureObject(); // \brief Default constructor of Texture Obejct

	static bool bInstanceFlag;
	static TextureObject *textureObject;
	static TextureObject* getInstance();


	void loadTextures(); // \brief Loads all of the textures needed for game just once

	//car textures
	vector<Texture> m_vCarColourTextures;// \brief Base colour of car
	vector<Texture> m_vCarLights;// \brief Texture for car lights
	vector<Texture> m_vCarWheels;// \brief Texture for car wheels

	//Scene texture
	vector<Texture> m_vBackgroundTextures; // \brief Texture for background
	vector<Texture> m_vTimeTextures; // \brief Texture for background

	//Road Textures
	vector<Texture> m_vTwoWayStreetTextures; // \brief Texture for 2 way road 

	vector<Texture> m_vTJunctionTextures; // \brief Texture for T Juntion

	vector<Texture> m_vCornerTextures; // \brief Texture for Corner
	
	vector<Texture> m_vCrossRoadsTextures; // \brief Texture for cross roads

   //Pavement Textures
	Texture m_PavementTwoWayStreetTextures; // \brief Texture for 2 way road 
			 
	Texture m_PavementTJunctionTextures; // \brief Texture for T Juntion
			 
	Texture m_PavementCornerTextures; // \brief Texture for Corner
			
	Texture m_PavementCrossRoadsTextures; // \brief Texture for cross roads


	//StartEnd point teture
	Texture m_StartEndPoint; // \brief Texture Start and end point

	//Traffic Textures
	vector<Texture> m_vTrafficLightTextures; // \brief Texture traffic lights  0 red , 1 yellow, 2 green

	//Pedestrian Light Textures
	vector<Texture> m_vPedestrianLightTextures; // \brief Texture traffic lights  0 red , 1 yellow, 2 green

};
#endif