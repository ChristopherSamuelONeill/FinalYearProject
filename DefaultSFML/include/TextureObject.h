#ifndef TEXTUREOBJECT_H
#define TEXTUREOBJECT_H

#include <iostream>
#include <SFML\Graphics.hpp>

using namespace std;
using namespace sf;

class TextureObject
{
public:
	TextureObject(); // \breif Default constructor of Texture Obejct

	void loadTextures(); // \breif Loads all of the textures needed for game just once

	//car textures
	vector<Texture> m_vCarColourTextures;// \breif Base colour of car
	vector<Texture> m_vCarLights;// \breif Texture for car lights
	vector<Texture> m_vCarWheels;// \breif Texture for car wheels

	//Scene texture
	vector<Texture> m_vBackgroundTextures; // \breif Texture for background
	vector<Texture> m_vTimeTextures; // \breif Texture for background
};
#endif