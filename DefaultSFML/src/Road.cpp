#include "..\include\Road.h"

Road::Road()
{
}

Road::Road(Vector2f Position, Vector2f Size, float Rotation, Texture texture)
{
	m_sfTexture = texture;
	m_sfPosition = Position;
	m_sfSize = Size;
	m_fRotation = Rotation;

	//set up drawbales
	m_sfRoadRect.setPosition(m_sfPosition);
	m_sfRoadRect.setSize(m_sfSize);
	m_sfRoadRect.setRotation(m_fRotation);
	m_sfRoadRect.setFillColor(Color::Red);

	m_sfRoadSprite.setPosition(m_sfRoadRect.getPosition());
	m_sfRoadSprite.setTexture(m_sfTexture);
	m_sfRoadSprite.setRotation(m_fRotation);
}

void Road::draw(RenderTarget & target, RenderStates states) const
{
	target.draw(m_sfRoadSprite);
}

void Road::update()
{
	//set up drawbales
	m_sfRoadRect.setPosition(m_sfPosition);
	m_sfRoadRect.setSize(m_sfSize);
	m_sfRoadRect.setRotation(m_fRotation);
	m_sfRoadRect.setFillColor(Color::Red);

	m_sfRoadSprite.setPosition(m_sfRoadRect.getPosition());
	m_sfRoadSprite.setTexture(m_sfTexture);
	m_sfRoadSprite.setRotation(m_fRotation);
}

void Road::passPathfinding(Pathfinding & pathData)
{
	// find all the nodes that are in the middle of the road
	
	vector<Vector2f> middleOfRoad;
	Vector2f temp;
	Vector2f local;


	pair< Node*, Vector2f> tempNode;
	RectangleShape RoadnodeSquare;
	RoadnodeSquare.setSize(Vector2f(100, 100));
	RectangleShape nodeSquare;
	nodeSquare.setSize(Vector2f(100, 100));
	

	//find rotation matrix
	float vdRotationMatrix1[2][2]; // X Y

	vdRotationMatrix1[0][0] = cos(m_fRotation * float((3.14159265359 / 180))) ;
	vdRotationMatrix1[0][1] = -sin(m_fRotation *float((3.14159265359 / 180)));
	vdRotationMatrix1[1][0] = sin(m_fRotation * float((3.14159265359 / 180)));
	vdRotationMatrix1[1][1] = cos(m_fRotation * float((3.14159265359 / 180)));


	

	if (m_sType == "NormalRoad")
	{

		if (m_fRotation == 0)
		{
			//middle
			for (int i = 0; i < 1000; i += 100)
			{
				temp = Vector2f(m_sfPosition.x + 200, m_sfPosition.y + i);
				middleOfRoad.push_back(temp);
			}
			//left
			for (int i = 0; i < 1000; i += 100)
			{
				temp = Vector2f(m_sfPosition.x - 100, m_sfPosition.y + i);
				middleOfRoad.push_back(temp);
			}
			//right
			for (int i = 0; i < 1000; i += 100)
			{
				temp = Vector2f(m_sfPosition.x + 500, m_sfPosition.y + i);
				middleOfRoad.push_back(temp);
			}
		}
		
		else if (m_fRotation == 90)
		{
			//middle
			for (int i = 0; i < 1000; i += 100)
			{
				temp = Vector2f(m_sfPosition.x - i - 100, m_sfPosition.y + 200);
				middleOfRoad.push_back(temp);
			}
			//top
			for (int i = 0; i < 1000; i += 100)
			{
				temp = Vector2f(m_sfPosition.x - i - 100, m_sfPosition.y - 100);
				middleOfRoad.push_back(temp);
			}
			//bottom
			for (int i = 0; i < 1000; i += 100)
			{
				temp = Vector2f(m_sfPosition.x - i - 100, m_sfPosition.y + 500);
				middleOfRoad.push_back(temp);
			}
		}
	
	}

	if (m_sType == "CrossRoads")
	{
		//left top
		for (int i = 0; i < 1000; i += 100)
		{
			temp = Vector2f(m_sfPosition.x + i, m_sfPosition.y + 900);
			middleOfRoad.push_back(temp);
		}
		//left prong
		for (int i = 0; i < 1000; i += 100)
		{
			temp = Vector2f(m_sfPosition.x + i, m_sfPosition.y + 1200);
			middleOfRoad.push_back(temp);
		}
		//left bottom
		for (int i = 0; i < 1000; i += 100)
		{
			temp = Vector2f(m_sfPosition.x + i, m_sfPosition.y + 1500);
			middleOfRoad.push_back(temp);
		}

		//right top
		for (int i = 0; i < 1000; i += 100)
		{
			temp = Vector2f(m_sfPosition.x + 2400 - i, m_sfPosition.y + 900);
			middleOfRoad.push_back(temp);
		}
		//right prong
		for (int i = 0; i < 1000; i += 100)
		{
			temp = Vector2f(m_sfPosition.x + 2400 -  i, m_sfPosition.y + 1200);
			middleOfRoad.push_back(temp);
		}
		//right bottom
		for (int i = 0; i < 1000; i += 100)
		{
			temp = Vector2f(m_sfPosition.x + 2400 - i, m_sfPosition.y + 1500);
			middleOfRoad.push_back(temp);
		}

		//top left
		for (int i = 0; i < 900; i += 100)
		{
			temp = Vector2f(m_sfPosition.x + 900, m_sfPosition.y + i);
			middleOfRoad.push_back(temp);
		}
		//top prong
		for (int i = 0; i < 1000; i += 100)
		{
			temp = Vector2f(m_sfPosition.x + 1200 , m_sfPosition.y + i);
			middleOfRoad.push_back(temp);
		}
		//top right
		for (int i = 0; i < 900; i += 100)
		{
			temp = Vector2f(m_sfPosition.x + 1500, m_sfPosition.y + i);
			middleOfRoad.push_back(temp);
		}


		//bottom left
		for (int i = 0; i < 900; i += 100)
		{
			temp = Vector2f(m_sfPosition.x + 900, m_sfPosition.y + 2400 - i);
			middleOfRoad.push_back(temp);
		}
		//bottom prong
		for (int i = 0; i < 1000; i += 100)
		{
			temp = Vector2f(m_sfPosition.x + 1200 , m_sfPosition.y + 2400 -  i);
			middleOfRoad.push_back(temp);
		}
		//bottom right
		for (int i = 0; i < 900; i += 100)
		{
			temp = Vector2f(m_sfPosition.x + 1500, m_sfPosition.y + 2400 - i);
			middleOfRoad.push_back(temp);
		}
	
		
	}

	if (m_sType == "T-Junction")
	{
		
		if (m_fRotation == 0)
		{
			//right prong
			for (int i = 0; i < 1000; i += 100)
			{
				temp = Vector2f(m_sfPosition.x + 2400 - i, m_sfPosition.y + 200);
				middleOfRoad.push_back(temp);
			}

			//left prong
			for (int i = 0; i < 1000; i += 100)
			{
				temp = Vector2f(m_sfPosition.x + i, m_sfPosition.y + 200);
				middleOfRoad.push_back(temp);
			}

			//bottom prong
			for (int i = 0; i < 1000; i += 100)
			{
				temp = Vector2f(m_sfPosition.x + 1200, m_sfPosition.y + 1400 - i);
				middleOfRoad.push_back(temp);
			}

		}

		if (m_fRotation == 180)
		{
			//right prong
			for (int i = 0; i < 1000; i += 100)
			{
				temp = Vector2f(m_sfPosition.x -100 - i , m_sfPosition.y - 300);
				middleOfRoad.push_back(temp);
			}

			//left prong
			for (int i = 0; i < 1000; i += 100)
			{
				temp = Vector2f(m_sfPosition.x - 2500 + i, m_sfPosition.y - 300);
				middleOfRoad.push_back(temp);
			}

			//top prong
			for (int i = 0; i < 1000; i += 100)
			{
				temp = Vector2f(m_sfPosition.x - 1300, m_sfPosition.y - 1500 + i);
				middleOfRoad.push_back(temp);
			}

		}

		if (m_fRotation == 90)
		{
			//top prong
			for (int i = 0; i < 1000; i += 100)
			{
				temp = Vector2f(m_sfPosition.x - 300, m_sfPosition.y + i);
				middleOfRoad.push_back(temp);
			}

			//left prong
			for (int i = 0; i < 1000; i += 100)
			{
				temp = Vector2f(m_sfPosition.x - 1500 + i, m_sfPosition.y + 1200);
				middleOfRoad.push_back(temp);
			}

			//bottom prong
			for (int i = 0; i < 1000; i += 100)
			{
				temp = Vector2f(m_sfPosition.x - 300, m_sfPosition.y + 2400 - i);
				middleOfRoad.push_back(temp);
			}

		}

		if (m_fRotation == 270)
		{
			//top prong
			for (int i = 0; i < 1000; i += 100)
			{
				temp = Vector2f(m_sfPosition.x + 200, m_sfPosition.y - 2500 + i);
				middleOfRoad.push_back(temp);
			}

			//right prong
			for (int i = 0; i < 1000; i += 100)
			{
				temp = Vector2f(m_sfPosition.x + 1400 - i, m_sfPosition.y - 1300);
				middleOfRoad.push_back(temp);
			}

			//bottom prong
			for (int i = 0; i < 1000; i += 100)
			{
				temp = Vector2f(m_sfPosition.x + 200, m_sfPosition.y - 100 - i);
				middleOfRoad.push_back(temp);
			}

		}
	}

	if (m_sType == "Corner")
	{

		if (m_fRotation == 0)
		{

			//top edge
			for (int i = 0; i < 600; i += 100)
			{
				temp = Vector2f(m_sfPosition.x + i, m_sfPosition.y - 100);
				middleOfRoad.push_back(temp);
			}

			//right edge
			for (int i = 0; i < 500; i += 100)
			{
				temp = Vector2f(m_sfPosition.x + 500, m_sfPosition.y + i);
				middleOfRoad.push_back(temp);
			}
			//right prong
			for (int i = 0; i < 200; i += 100)
			{
				temp = Vector2f(m_sfPosition.x  + i, m_sfPosition.y + 200);
				middleOfRoad.push_back(temp);
				
			}

			//bottom prong
			for (int i = 0; i < 300; i += 100)
			{
				temp = Vector2f(m_sfPosition.x + 200, m_sfPosition.y + 400 - i);
				middleOfRoad.push_back(temp);
			}

		}

		if (m_fRotation == 180)
		{
			//bottom edge
			for (int i = 0; i < 600; i += 100)
			{
				temp = Vector2f(m_sfPosition.x -100 - i, m_sfPosition.y );
				middleOfRoad.push_back(temp);
			}

			//left edge
			for (int i = 0; i < 500; i += 100)
			{
				temp = Vector2f(m_sfPosition.x - 600, m_sfPosition.y - 100 - i);
				middleOfRoad.push_back(temp);
			}
			//right prong
			for (int i = 0; i < 200; i += 100)
			{
				temp = Vector2f(m_sfPosition.x - 100 - i, m_sfPosition.y - 300);
				middleOfRoad.push_back(temp);

			}

			//top prong
			for (int i = 0; i < 300; i += 100)
			{
				temp = Vector2f(m_sfPosition.x - 300, m_sfPosition.y - 400 - i);
				middleOfRoad.push_back(temp);
			}

		}

		if (m_fRotation == 90)
		{
			//bottom edge
			for (int i = 0; i < 600; i += 100)
			{
				temp = Vector2f(m_sfPosition.x - i , m_sfPosition.y + 500);
				middleOfRoad.push_back(temp);
			}

			//right edge
			for (int i = 0; i < 500; i += 100)
			{
				temp = Vector2f(m_sfPosition.x , m_sfPosition.y + 400 - i);
				middleOfRoad.push_back(temp);
			}
			//left prong
			for (int i = 0; i < 200; i += 100)
			{
				temp = Vector2f(m_sfPosition.x - 500 + i, m_sfPosition.y + 200);
				middleOfRoad.push_back(temp);

			}

			//top prong
			for (int i = 0; i < 300; i += 100)
			{
				temp = Vector2f(m_sfPosition.x - 300, m_sfPosition.y + i);
				middleOfRoad.push_back(temp);
			}


		}

		if (m_fRotation == 270)
		{
			
			//bottom edge
			for (int i = 0; i < 600; i += 100)
			{
				temp = Vector2f(m_sfPosition.x - 100 + i, m_sfPosition.y - 600 );
				middleOfRoad.push_back(temp);
			}

			//left edge
			for (int i = 0; i < 500; i += 100)
			{
				temp = Vector2f(m_sfPosition.x - 100, m_sfPosition.y - 100 - i);
				middleOfRoad.push_back(temp);
			}
			//left prong
			for (int i = 0; i < 200; i += 100)
			{
				temp = Vector2f(m_sfPosition.x + 300 + i, m_sfPosition.y - 300);
				middleOfRoad.push_back(temp);

			}

			//top prong
			for (int i = 0; i < 300; i += 100)
			{
				temp = Vector2f(m_sfPosition.x + 200, m_sfPosition.y - 100 - i);
				middleOfRoad.push_back(temp);
			}

		}
	}

	
	//sort through nodes and find ones with the same position
	for (int i = 0; i < middleOfRoad.size(); i++)
	{
		RoadnodeSquare.setPosition(middleOfRoad[i]);
		
		for (int x = 0; x < pathData.m_carNodes.size(); x++)
		{
			nodeSquare.setPosition(pathData.m_carNodes[x].second);

			FloatRect A = RoadnodeSquare.getGlobalBounds();
			FloatRect B = nodeSquare.getGlobalBounds();


			//if the node has the same position add it to the closed list
			if (A.intersects(B))
			{
				pathData.m_carNodes[x].first->m_bAccessable = false;
			}
			
		}
	}


	
}

void Road::setType(string type)
{
	m_sType = type;
}

Vector2f Road::getPosition()
{
	return m_sfPosition;
}

string Road::getType()
{
	return m_sType;
}

float Road::getRotation()
{
	return m_fRotation;
}

Vector2f Road::getSize()
{
	return m_sfSize;
}

RectangleShape Road::getCollisionBox()
{
	return m_sfRoadRect;
}
