////////////////////////////////////////////////////////////
//
// TextBox.h
//
// Uses TextBox.cpp
//
////////////////////////////////////////////////////////////
#ifndef TEXTBOX_H
#define TEXTBOX_H

#include <SFML/Graphics.hpp>
#include <iostream>
#include "Clickable.h"
#include <sstream>

using namespace std;
using namespace sf;



class TextBox : public Clickable , public Drawable
{
public:
	
	////////////////////////////////////////////////////////////
	/// \brief Default Constructor
	///
	/// Creates an empty TextBox 
	///
	////////////////////////////////////////////////////////////
	TextBox();

	////////////////////////////////////////////////////////////
	/// \brief Overloaded Constructor
	///
	/// Creates the TextBox with its parameteres
	///
	/// \param text string Text that is displayed on the TextBox
	/// \param pos sVector2f position of the TextBox
	/// \param size sVector2f size of the TextBox
	////////////////////////////////////////////////////////////
	TextBox(string text, Vector2f pos, Vector2f size, string textureName);

	////////////////////////////////////////////////////////////
	/// \brief Default deConstructor
	///
	/// Deletes the textBox 
	///
	////////////////////////////////////////////////////////////
	~TextBox();

	///////////////////////////////////////////////////////////
	/// \brief Processes key presses while button is selected
	///
	/// If valid charachter add to string
	/// if enter complete string
	/// if escape clear string
	///
	/// \param 
	///
	////////////////////////////////////////////////////////////
	void takeInput(Keyboard::Key pressedKey);

	////////////////////////////////////////////////////////////
	/// \brief draw function
	///
	/// draws the Buttons sprite and text
	///
	////////////////////////////////////////////////////////////
	void draw(RenderTarget& target, RenderStates states) const;

	///////////////////////////////////////////////////////////
	/// \brief bool for entering text
	////////////////////////////////////////////////////////////
	bool m_bIsEntering = false;

	///////////////////////////////////////////////////////////
	/// \brief string for the text
	////////////////////////////////////////////////////////////
	String m_sText;

private:
	///////////////////////////////////////////////////////////
	/// \brief Text for the box
	////////////////////////////////////////////////////////////
	Text m_sfButtonText;

	///////////////////////////////////////////////////////////
	/// \brief Texture for the box
	////////////////////////////////////////////////////////////
	Texture m_sfTexture;

	///////////////////////////////////////////////////////////
	/// \brief Sprite for the box
	////////////////////////////////////////////////////////////
	Sprite m_sfSprite;

	///////////////////////////////////////////////////////////
	/// \brief Rect for the box
	////////////////////////////////////////////////////////////
	RectangleShape m_sfRect;

	///////////////////////////////////////////////////////////
	/// \brief font for the box
	////////////////////////////////////////////////////////////
	Font m_sfFont;




};
#endif
////////////////////////////////////////////////////////////
/// \class TextBox.h
///
/// Textbox is an object class that inherests from button
///
/// objects that the user click on and type into should be a TextBox
///
/// It contains a string of what was typed into the box after been clicked on and functions for handling input
///
/// Usage example:
/// \code
/// 
/// Textbox windowSizex;
/// if(windowSizex.bIsclicked)
/// {
///		windowSizex.takeInput(key)
///
///	}
/// 
/// \endcode
///
////////////////////////////////////////////////////////////
