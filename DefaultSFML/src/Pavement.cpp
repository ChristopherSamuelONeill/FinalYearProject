#include "Pavement.h"

Pavement::Pavement()
{
}

Pavement::Pavement(Vector2f Position, Vector2f Size, float Rotation, Texture texture)
{
	m_sfTexture = texture;
	m_sfPosition = Position;
	m_sfSize = Size;
	m_fRotation = Rotation;

	//set up drawbales
	m_sfPavementRect.setPosition(m_sfPosition);
	m_sfPavementRect.setSize(m_sfSize);
	m_sfPavementRect.setRotation(m_fRotation);
	m_sfPavementRect.setFillColor(Color::Red);
	
	m_sfPavementSprite.setPosition(m_sfPavementRect.getPosition());
	m_sfPavementSprite.setTexture(m_sfTexture);
	m_sfPavementSprite.setRotation(m_fRotation);
}

void Pavement::draw(RenderTarget & target, RenderStates states) const
{
	target.draw(m_sfPavementSprite);
}

void Pavement::update()
{
	//set up drawbales
	m_sfPavementRect.setPosition(m_sfPosition);
	m_sfPavementRect.setSize(m_sfSize);
	m_sfPavementRect.setRotation(m_fRotation);
	m_sfPavementRect.setFillColor(Color::Red);
	
	m_sfPavementSprite.setPosition(m_sfPavementRect.getPosition());
	m_sfPavementSprite.setTexture(m_sfTexture);
	m_sfPavementSprite.setRotation(m_fRotation);
}

void Pavement::passPathfinding(Pathfinding & pathData)
{
	// find all the nodes that are in the middle of the Pavement

	vector<Vector2f> middleOfPavement;
	Vector2f temp;
	Vector2f local;


	pair< Node*, Vector2f> tempNode;
	RectangleShape PavementnodeSquare;
	PavementnodeSquare.setSize(Vector2f(100, 100));
	RectangleShape nodeSquare;
	nodeSquare.setSize(Vector2f(100, 100));


	//find rotation matrix
	float vdRotationMatrix1[2][2]; // X Y

	vdRotationMatrix1[0][0] = cos(m_fRotation * float((3.14159265359 / 180)));
	vdRotationMatrix1[0][1] = -sin(m_fRotation *float((3.14159265359 / 180)));
	vdRotationMatrix1[1][0] = sin(m_fRotation * float((3.14159265359 / 180)));
	vdRotationMatrix1[1][1] = cos(m_fRotation * float((3.14159265359 / 180)));




	if (m_sType == "NormalRoad")
	{

		if (m_fRotation == 0)
		{
			for (int x = 100; x < 600; x += 100)
			{
				for (int y = 0; y < 1000; y += 100)
				{
					temp = Vector2f(m_sfPosition.x + x, m_sfPosition.y + y);
					middleOfPavement.push_back(temp);
					
				}
			}
		}
		if (m_fRotation == 90)
		{
			for (int x = 100; x < 1100; x += 100)
			{
				for (int y = 100; y < 600; y += 100)
				{
					temp = Vector2f(m_sfPosition.x - x, m_sfPosition.y + y);
					middleOfPavement.push_back(temp);

				}
			}
		}
		
	}

	if (m_sType == "CrossRoads")
	{
		//left top
		for (int x = 0; x < 1000; x += 100)
		{
			for (int y = 0; y < 1000; y += 100)
			{
				temp = Vector2f(m_sfPosition.x + x, m_sfPosition.y + y);
				if (x != 900 && y != 900)
				{
					middleOfPavement.push_back(temp);
				}
				
			}
		}

		//top right
		for (int x = 0; x < 1000; x += 100)
		{
			for (int y = 0; y < 1000; y += 100)
			{
				temp = Vector2f(m_sfPosition.x + 1500 + x, m_sfPosition.y + y);
				if (x != 0 && y != 900)
				{
					middleOfPavement.push_back(temp);
				}

			}
		}
		//bottom right
		for (int x = 0; x < 1000; x += 100)
		{
			for (int y = 0; y < 1000; y += 100)
			{
				temp = Vector2f(m_sfPosition.x + 1500 + x, m_sfPosition.y + 1500 + y);
				if (x != 0 && y != 0)
				{
					middleOfPavement.push_back(temp);
				}

			}
		}
		//bottom left
		for (int x = 0; x < 1000; x += 100)
		{
			for (int y = 0; y < 1000; y += 100)
			{
				temp = Vector2f(m_sfPosition.x + x, m_sfPosition.y + 1500 + y);
				if (x != 9 && y != 0)
				{
					middleOfPavement.push_back(temp);
				}

			}
		}


	}

	if (m_sType == "T-Junction")
	{
		if (m_fRotation == 0)
		{
			for (int x = 0; x < 2500; x += 100)
			{
				for (int y = 100; y < 600; y += 100)
				{
					temp = Vector2f(m_sfPosition.x + x, m_sfPosition.y + y);
					middleOfPavement.push_back(temp);

				}

			}
			for (int x = 1000; x < 1500; x += 100)
			{
				for (int y = 600; y < 1600; y += 100)
				{
					temp = Vector2f(m_sfPosition.x + x, m_sfPosition.y + y);
					middleOfPavement.push_back(temp);

				}


			}
		}
		if (m_fRotation == 90)
		{
			for (int x = 200; x < 700; x += 100)
			{
				for (int y = 0; y < 2500; y += 100)
				{
					temp = Vector2f(m_sfPosition.x - x, m_sfPosition.y + y);
					middleOfPavement.push_back(temp);

				}

			}
			for (int x = -1600; x < -500; x += 100)
			{
				for (int y = 1000; y < 1500; y += 100)
				{
					temp = Vector2f(m_sfPosition.x + x, m_sfPosition.y + y);
					middleOfPavement.push_back(temp);

				}


			}
		}
		if (m_fRotation == 180)
		{
			for (int x = 100; x < 2600; x += 100)
			{
				for (int y = 200; y < 700; y += 100)
				{
					temp = Vector2f(m_sfPosition.x - x, m_sfPosition.y - y);
					middleOfPavement.push_back(temp);

				}

			}
			for (int x = 1100; x < 1600; x += 100)
			{
				for (int y = 700; y < 1700; y += 100)
				{
					temp = Vector2f(m_sfPosition.x - x, m_sfPosition.y - y);
					middleOfPavement.push_back(temp);

				}


			}
		}
		if (m_fRotation == 270)
		{
			for (int x = 100; x < 600; x += 100)
			{
				for (int y = 100; y < 2600; y += 100)
				{
					temp = Vector2f(m_sfPosition.x + x, m_sfPosition.y - y);
					middleOfPavement.push_back(temp);

				}

			}
			for (int x = -1500; x < -500; x += 100)
			{
				for (int y = 1100; y < 1600; y += 100)
				{
					temp = Vector2f(m_sfPosition.x - x, m_sfPosition.y - y);
					middleOfPavement.push_back(temp);

				}


			}
		}
	}

	if (m_sType == "Corner")
	{
		if (m_fRotation == 0)
		{
			for (int x = 0; x < 500; x += 100)
			{
				for (int y = 100; y < 600; y += 100)
				{
					temp = Vector2f(m_sfPosition.x + x, m_sfPosition.y + y);
					middleOfPavement.push_back(temp);

				}

			}
		}
		if (m_fRotation == 90)
		{
			for (int x = 200; x < 700; x += 100)
			{
				for (int y = 0; y < 500; y += 100)
				{
					temp = Vector2f(m_sfPosition.x - x, m_sfPosition.y + y);
					middleOfPavement.push_back(temp);

				}

			}
		}
		if (m_fRotation == 180)
		{
			for (int x = 100; x < 600; x += 100)
			{
				for (int y = 200; y < 700; y += 100)
				{
					temp = Vector2f(m_sfPosition.x - x, m_sfPosition.y - y);
					middleOfPavement.push_back(temp);

				}

			}
		}
		if (m_fRotation == 270)
		{
			for (int x = 100; x < 600; x += 100)
			{
				for (int y = 100; y < 600; y += 100)
				{
					temp = Vector2f(m_sfPosition.x + x, m_sfPosition.y - y);
					middleOfPavement.push_back(temp);

				}

			}
		}
	}


	//sort through nodes and find ones with the same position
	for (int i = 0; i < middleOfPavement.size(); i++)
	{
		PavementnodeSquare.setPosition(middleOfPavement[i]);

		for (int x = 0; x < pathData.m_pedNodes.size(); x++)
		{
			nodeSquare.setPosition(pathData.m_pedNodes[x].second);

			FloatRect A = PavementnodeSquare.getGlobalBounds();
			FloatRect B = nodeSquare.getGlobalBounds();


			//if the node has the same position add it to the closed list
			if (A.intersects(B))
			{
				pathData.m_pedNodes[x].first->m_bAccessable = false;
			}

		}
	}



}

void Pavement::setType(string type)
{
	m_sType = type;
}

Vector2f Pavement::getPosition()
{
	return m_sfPosition;
}

string Pavement::getType()
{
	return m_sType;
}

float Pavement::getRotation()
{
	return m_fRotation;
}

Vector2f Pavement::getSize()
{
	return m_sfSize;
}

RectangleShape Pavement::getCollisionBox()
{
	return m_sfPavementRect;
}
