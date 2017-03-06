#include "..\include\Button.h"

Button::Button()
{
}

Button::Button(string text, Vector2f pos, Vector2f size, string textureName)
{

	m_sButtonText = text;
	float scalex = size.x / 400 ;
	float scaley = size.y / 118 ;
	float textScale = scalex / scaley;

	m_sfVTopLeftPos = pos;
	m_sfVSize = size;
	if (!m_sfTexture.loadFromFile("Assets/textures/" + textureName + ".png"))
	{
		cout << "Error: " + textureName + ".png was unable to load.";
	};

	//load font
	if (!m_sfFont.loadFromFile("Assets/fonts/ariali.ttf"))
	{
		cout << "Error: Font ariali.ttf was unable to load.";
	};

	m_sfRect.setPosition(m_sfVTopLeftPos.x, m_sfVTopLeftPos.y);
	m_sfRect.setSize(size);


	m_sfSprite.setScale(Vector2f(scalex, scaley));
	m_sfSprite.setTexture(m_sfTexture);
	m_sfSprite.setPosition(m_sfRect.getPosition().x , m_sfRect.getPosition().y );
	
	// Create a text
	m_sfButtonText = Text(m_sButtonText, m_sfFont);
	m_sfButtonText.setCharacterSize(36 * textScale);
	m_sfButtonText.setStyle(Text::Bold);
	m_sfButtonText.setFillColor(Color(0, 0, 0));

}



void Button::draw(RenderTarget & target, RenderStates states) const
{
	target.draw(m_sfSprite);
//	target.draw(m_sfButtonText);
}
