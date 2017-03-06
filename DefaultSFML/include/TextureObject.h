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

	vector<Texture> m_vCarColourTextures;
	vector<Texture> m_vCarLights;
	vector<Texture> m_vCarWheels;
};
#endif