#include "TextureObject.h"

TextureObject::TextureObject()
{
}

void TextureObject::loadTextures()
{
	cout << "Loading Textures" << endl;

	Texture sfTempTexture;

	//base colours------------------------------------------

	//White
	if (!sfTempTexture.loadFromFile("./Assets/textures/Cars/car_white.png"))
	{
		cout << "Error: car_white.png Texture was unable to load." << endl;
	};

	m_vCarColourTextures.push_back(sfTempTexture);

	//Black
	if (!sfTempTexture.loadFromFile("./Assets/textures/Cars/car_black.png"))
	{
		cout << "Error: car_black.png Texture was unable to load." << endl;
	};

	m_vCarColourTextures.push_back(sfTempTexture);

	//Blue
	if (!sfTempTexture.loadFromFile("./Assets/textures/Cars/car_blue.png"))
	{
		cout << "Error: car_blue.png Texture was unable to load." << endl;
	};

	m_vCarColourTextures.push_back(sfTempTexture);

	//blue_light
	if (!sfTempTexture.loadFromFile("./Assets/textures/Cars/car_blue_light.png"))
	{
		cout << "Error: car_blue_light.png Texture was unable to load." << endl;
	};

	m_vCarColourTextures.push_back(sfTempTexture);

	//Green
	if (!sfTempTexture.loadFromFile("./Assets/textures/Cars/car_green.png"))
	{
		cout << "Error: car_green.png Texture was unable to load." << endl;
	};

	m_vCarColourTextures.push_back(sfTempTexture);

	//Orange
	if (!sfTempTexture.loadFromFile("./Assets/textures/Cars/car_orange.png"))
	{
		cout << "Error: car_orange.png Texture was unable to load." << endl;
	};

	m_vCarColourTextures.push_back(sfTempTexture);

	//Pink
	if (!sfTempTexture.loadFromFile("./Assets/textures/Cars/car_pink.png"))
	{
		cout << "Error: car_pink.png Texture was unable to load." << endl;
	};

	m_vCarColourTextures.push_back(sfTempTexture);

	//Purple
	if (!sfTempTexture.loadFromFile("./Assets/textures/Cars/car_purple.png"))
	{
		cout << "Error: car_purple.png Texture was unable to load." << endl;
	};

	m_vCarColourTextures.push_back(sfTempTexture);

	//Red
	if (!sfTempTexture.loadFromFile("./Assets/textures/Cars/car_red.png"))
	{
		cout << "Error: car_red.png Texture was unable to load." << endl;
	};

	m_vCarColourTextures.push_back(sfTempTexture);

	//Yellow
	if (!sfTempTexture.loadFromFile("./Assets/textures/Cars/car_yellow.png"))
	{
		cout << "Error: car_yellow.png Texture was unable to load." << endl;
	};

	m_vCarColourTextures.push_back(sfTempTexture);

	//Lights-------------------------------------------------------------------------

	//rear lights
	if (!sfTempTexture.loadFromFile("./Assets/textures/Cars/rearLight_notLit.png"))
	{
		cout << "Error: rearLight_notLit was unable to load." << endl;
	};

	m_vCarLights.push_back(sfTempTexture);

	if (!sfTempTexture.loadFromFile("./Assets/textures/Cars/rearLight_Lit.png"))
	{
		cout << "Error: rearLight_Lit was unable to load." << endl;
	};

	m_vCarLights.push_back(sfTempTexture);

	//front lights
	if (!sfTempTexture.loadFromFile("./Assets/textures/Cars/FrontLights_NotLit.png"))
	{
		cout << "Error: FrontLights_NotLit.png was unable to load." << endl;
	};

	m_vCarLights.push_back(sfTempTexture);

	if (!sfTempTexture.loadFromFile("./Assets/textures/Cars/FrontLights_Lit.png"))
	{
		cout << "Error: FrontLights_Lit.png was unable to load." << endl;
	};

	m_vCarLights.push_back(sfTempTexture);


	//Wheels---------------------------------------------------------------------

	//wheels
	if (!sfTempTexture.loadFromFile("./Assets/textures/Cars/RearWheels.png"))
	{
		cout << "Error: RearWheels.png was unable to load." << endl;
	};
	m_vCarWheels.push_back(sfTempTexture);

	if (!sfTempTexture.loadFromFile("./Assets/textures/Cars/FrontWheel_left.png"))
	{
		cout << "Error: FrontWheel_left.png was unable to load." << endl;
	};
	m_vCarWheels.push_back(sfTempTexture);

	if (!sfTempTexture.loadFromFile("./Assets/textures/Cars/FrontWheel_right.png"))
	{
		cout << "Error: FrontWheel_right.png was unable to load." << endl;
	};
	m_vCarWheels.push_back(sfTempTexture);

	cout << "Textures Loaded" << endl;

}
