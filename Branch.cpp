#include "Branch.h"
#ifndef _USE_MATH_DEFINES
#define _USE_MATH_DEFINES
#endif
#include <math.h>
#include <iostream>

Branch::Branch(void)
{
}


Branch::~Branch(void)
{
}

void Branch::initData()
{
	if (pData)
	{
		delete[] pData;
		delete[] pIndices;
	}

	unsigned int radialStep = 20;
	unsigned int heightStep = 20;
	float conHeight = 1.0f;
	float minR = 1.f;
	float maxR = 3.0f;
	float delta = maxR - minR;

	//number of points
	dataCount = (radialStep+1)*heightStep+2; 
	//number of triangles
	unsigned int nTriangles = 2*radialStep*(heightStep-1)+2*radialStep;
	//number of indices
	indicesCount = 3*nTriangles;

	pData = new VertexData [dataCount];
	pIndices = new unsigned int [indicesCount];
	
	//fill in pData array

	//generate elements on side
	for (unsigned int j=0; j<heightStep; j++)
	{
		float zPos = conHeight*j/(heightStep-1);
		float tmp = delta * (heightStep - j) * 1.0 / heightStep;
		for (unsigned int i=0; i<radialStep+1; i++)
		{
			unsigned int pointId = j*(radialStep+1)+i;

			float fi = 2*M_PI*i/radialStep; //from 0 to 360 degrees
			float xPos = cos(fi);
			float yPos = sin(fi);

			pData[pointId].pos = glm::vec3((minR + tmp) * xPos, zPos, (minR + tmp) * yPos);
			pData[pointId].nor = glm::vec3(xPos, delta / minR ,yPos);
			pData[pointId].tex = glm::vec2((xPos+1)/2, (yPos+1)/2);		
		}
	}
	//generate north pole
	unsigned int pointId = heightStep*(radialStep+1);
	pData[pointId].pos = glm::vec3(0,conHeight,0);
	pData[pointId].nor = glm::vec3(0,1,0);
	pData[pointId].tex = glm::vec2(0.5f, 0.5f);		
	//generate south pole
	pointId = heightStep*(radialStep+1)+1;
	pData[pointId].pos = glm::vec3(0,0,0);
	pData[pointId].nor = glm::vec3(0,-1,0);
	pData[pointId].tex = glm::vec2(0.5f, 0.5f);		
	
	//fill in pIndices array

	//fill in side triangles (first 6*radialStep*(heightStep-1))
	for (unsigned int j=0; j<heightStep-1; j++)
	{
		for (unsigned int i=0; i<radialStep; i++)
		{
			unsigned int pointId = j*(radialStep+1)+i;
			unsigned int indexId = j*radialStep+i;
			//pData configuration
			//------------------------
			//--.(i,j+1)--.(i+1,j+1)--
			//--.(i,  j)--.(i+1,  j)--
			//------------------------

			//pData indices
			//------------------------
			//--pointId+radialStep+1--pointId+radialStep+2----
			//--pointId---------------pointId+1---------------
			
			//triangle 1			
			//   /|
			//  / |
			// /__|  
			pIndices[6*indexId+0] = pointId;
			pIndices[6*indexId+1] = pointId+1;
			pIndices[6*indexId+2] = pointId+radialStep+2;
			//triangle 2
			// ____
			// |  /
			// | /
			// |/  
			pIndices[6*indexId+3] = pointId;
			pIndices[6*indexId+4] = pointId+radialStep+2;
			pIndices[6*indexId+5] = pointId+radialStep+1;
		}
	}
	//fill in north pole triangles (next 3*radialStep)
	{
		unsigned int startIndex = 6*radialStep*(heightStep-1);
		unsigned int northPoleId = heightStep*(radialStep+1);
		for (unsigned int i=0; i<radialStep; i++)
		{
			//get last row
			unsigned int pointId = (heightStep-1)*(radialStep+1)+i;
			pIndices[startIndex+3*i+0] = pointId;
			pIndices[startIndex+3*i+1] = pointId+1;
			pIndices[startIndex+3*i+2] = northPoleId;
		}
	}
	
	//fill in south pole triangles (last 3*radialStep)
	{
		unsigned int startIndex = 6*radialStep*(heightStep-1)+3*radialStep;	
		unsigned int southPoleId = heightStep*(radialStep+1)+1;

		for (unsigned int i=0; i<radialStep; i++)
		{
			//get first row
			unsigned int pointId = i;
			pIndices[startIndex+3*i+0] = pointId;
			pIndices[startIndex+3*i+1] = southPoleId;
			pIndices[startIndex+3*i+2] = pointId+1;
		}
	}
}