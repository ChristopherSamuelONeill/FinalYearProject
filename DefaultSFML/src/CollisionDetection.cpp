#include "CollisionDetection.h"

bool CollisionDetection::operator()(RectangleShape A, RectangleShape B)
{
	//early out test
	FloatRect Recta = A.getGlobalBounds();
	FloatRect Rectb = B.getGlobalBounds();

	//if not colliding then quit
	if (!Recta.intersects(Rectb)) return false;

	//Collision detection variables
	Vector2f obb1LocalPoints[4];
	Vector2f obb2LocalPoints[4];
	Vector2f obb1Normals[4];
	Vector2f obb2Normals[4];
	Vector2f separetedAxis[4];

	bool testAxis[6];

	// find center of each rectangle
	Vector2f obb1Center = A.getPosition() + (A.getSize() / 2.0f);
	Vector2f obb2Center = B.getPosition() + (B.getSize() / 2.0f);

	///find the extents of each rectangle
	Vector2f obb1Extent = (A.getSize() / 2.0f);
	Vector2f obb2Extent = (B.getSize() / 2.0f);

	//create local position of each of the verticies
	obb1LocalPoints[0] = Vector2f(obb1Center.x + obb1Extent.x, obb1Center.y + obb1Extent.y);
	obb1LocalPoints[1] = Vector2f(obb1Center.x + obb1Extent.x, obb1Center.y + -obb1Extent.y);
	obb1LocalPoints[2] = Vector2f(obb1Center.x + -obb1Extent.x, obb1Center.y + obb1Extent.y);
	obb1LocalPoints[3] = Vector2f(obb1Center.x + -obb1Extent.x, obb1Center.y + -obb1Extent.y);

	//create local position of each of the verticies
	obb2LocalPoints[0] = Vector2f(obb2Center.x + obb2Extent.x, obb2Center.y + obb2Extent.y);
	obb2LocalPoints[1] = Vector2f(obb2Center.x + obb2Extent.x, obb2Center.y + -obb2Extent.y);
	obb2LocalPoints[2] = Vector2f(obb2Center.x + -obb2Extent.x, obb2Center.y + obb2Extent.y);
	obb2LocalPoints[3] = Vector2f(obb2Center.x + -obb2Extent.x, obb2Center.y + -obb2Extent.y);
	
	//find rotation matrix
	vector<array<float, 2>> vdRotationMatrix1;
	vector<array<float, 2>> vdRotationMatrix2;

	vdRotationMatrix1[0][0] = cos(A.getRotation());
	vdRotationMatrix1[0][1] = sin(A.getRotation());
	vdRotationMatrix1[1][0] = -sin(A.getRotation());
	vdRotationMatrix1[1][1] = cos(A.getRotation());

	vdRotationMatrix2[0][0] = cos(B.getRotation());
	vdRotationMatrix2[0][1] = sin(B.getRotation());
	vdRotationMatrix2[1][0] = -sin(B.getRotation());
	vdRotationMatrix2[1][1] = cos(B.getRotation());

	//translate local coords by rotation matrix
	obb1LocalPoints[0] = Vector2f(	obb1LocalPoints[0].x * vdRotationMatrix1[0][0] + obb1LocalPoints[0].x * vdRotationMatrix1[0][1],
									obb1LocalPoints[0].y * vdRotationMatrix1[1][0] + obb1LocalPoints[0].y * vdRotationMatrix1[1][0]
									);
	obb1LocalPoints[1] = Vector2f(	obb1LocalPoints[1].x * vdRotationMatrix1[0][0] + obb1LocalPoints[1].x * vdRotationMatrix1[0][1],
									obb1LocalPoints[1].y * vdRotationMatrix1[1][0] + obb1LocalPoints[1].y * vdRotationMatrix1[1][0]
									);
	obb1LocalPoints[2] = Vector2f(	obb1LocalPoints[2].x * vdRotationMatrix1[0][0] + obb1LocalPoints[2].x * vdRotationMatrix1[0][1],
									obb1LocalPoints[2].y * vdRotationMatrix1[1][0] + obb1LocalPoints[2].y * vdRotationMatrix1[1][0]
									);
	obb1LocalPoints[3] = Vector2f(	obb1LocalPoints[3].x * vdRotationMatrix1[0][0] + obb1LocalPoints[3].x * vdRotationMatrix1[0][1],
									obb1LocalPoints[3].y * vdRotationMatrix1[1][0] + obb1LocalPoints[3].y * vdRotationMatrix1[1][0]
									);

	obb2LocalPoints[0] = Vector2f(	obb2LocalPoints[0].x * vdRotationMatrix2[0][0] + obb2LocalPoints[0].x * vdRotationMatrix2[0][1],
									obb2LocalPoints[0].y * vdRotationMatrix2[1][0] + obb2LocalPoints[0].y * vdRotationMatrix2[1][0]
								);																							
	obb2LocalPoints[1] = Vector2f(	obb2LocalPoints[1].x * vdRotationMatrix2[0][0] + obb2LocalPoints[1].x * vdRotationMatrix2[0][1],
									obb2LocalPoints[1].y * vdRotationMatrix2[1][0] + obb2LocalPoints[1].y * vdRotationMatrix2[1][0]
								);																							
	obb2LocalPoints[2] = Vector2f(	obb2LocalPoints[2].x * vdRotationMatrix2[0][0] + obb2LocalPoints[2].x * vdRotationMatrix2[0][1],
									obb2LocalPoints[2].y * vdRotationMatrix2[1][0] + obb2LocalPoints[2].y * vdRotationMatrix2[1][0]
								);																							
	obb2LocalPoints[3] = Vector2f(	obb2LocalPoints[3].x * vdRotationMatrix2[0][0] + obb2LocalPoints[3].x * vdRotationMatrix2[0][1],
									obb2LocalPoints[3].y * vdRotationMatrix2[1][0] + obb2LocalPoints[3].y * vdRotationMatrix2[1][0]
									);

	//find the normals
	Vector2f OBBNormals[2];
	OBBNormals[0] = Vector2f(0, 1);
	OBBNormals[1] = Vector2f(1, 0);

	//multiply these normals by rotation matrix
	separetedAxis[0] = Vector2f(OBBNormals[0].x * vdRotationMatrix1[0][0] + OBBNormals[0].x * vdRotationMatrix1[0][1],
								OBBNormals[0].y * vdRotationMatrix1[1][0] + OBBNormals[0].y * vdRotationMatrix1[1][0]
								);
	separetedAxis[1] = Vector2f(OBBNormals[1].x * vdRotationMatrix1[0][0] + OBBNormals[1].x * vdRotationMatrix1[0][1],
								OBBNormals[1].y * vdRotationMatrix1[1][0] + OBBNormals[1].y * vdRotationMatrix1[1][0]
								);

	separetedAxis[2] = Vector2f(OBBNormals[0].x * vdRotationMatrix2[0][0] + OBBNormals[0].x * vdRotationMatrix2[0][1],
								OBBNormals[0].y * vdRotationMatrix2[1][0] + OBBNormals[0].y * vdRotationMatrix2[1][0]
								);
	separetedAxis[2] = Vector2f(OBBNormals[1].x * vdRotationMatrix2[0][0] + OBBNormals[1].x * vdRotationMatrix2[0][1],
								OBBNormals[1].y * vdRotationMatrix2[1][0] + OBBNormals[1].y * vdRotationMatrix2[1][0]
								);
	//values used for holding min , max
	float OBB1Min = 9999999999;
	float OBB1Max = -9999999999;
	float OBB2Min = 9999999999;
	float OBB2Max = -9999999999;

	//project each point onto each axis

	for (int axisTestNum = 0; axisTestNum < 4; axisTestNum++)
	{

		// check each vertex on box 1 to get min and max
		for (int vertexNum = 0; vertexNum < 4; vertexNum++)
		{
			// dot product to project this point onto our axis
			float fDotProduct = ((separetedAxis[axisTestNum].x * separetedAxis[vertexNum].x) + (separetedAxis[axisTestNum].y * obb1LocalPoints[vertexNum].y));
			if (fDotProduct < OBB1Min)
			{
				OBB1Min = fDotProduct;
			}
			if (fDotProduct > OBB1Max)
			{
				OBB1Max = fDotProduct;
			}

		}

		// check each vertex on box 2 to get min and max
		for (int vertexNum = 0; vertexNum < 4; vertexNum++)
		{
			float fDotProduct = ((separetedAxis[axisTestNum].x * obb2LocalPoints[vertexNum].x) + (separetedAxis[axisTestNum].y * obb2LocalPoints[vertexNum].y));
			if (fDotProduct < OBB2Min)
			{
				OBB2Min = fDotProduct;
			}
			if (fDotProduct > OBB2Max)
			{
				OBB2Max = fDotProduct;
			}

		}

		//check each box min and max for over lap
		if (OBB2Min < OBB1Max && OBB2Min > OBB1Min)
		{
			testAxis[axisTestNum] = true; // There is a collision along this axis
		}
		else if (OBB2Max > OBB1Min && OBB2Max < OBB1Max)
		{
			testAxis[axisTestNum] = true; // There is a collision along this axis
		}
		else
		{
			testAxis[axisTestNum] = false; // There is no collision along this axis
			return false;

		}
	}

	//there was a collision
	return true;
}

