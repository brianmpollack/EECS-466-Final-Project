#pragma once
#include "MeshReader.h"

MeshReader::MeshReader()
{

}

void MeshReader::setFilename(char* filename)
{
	this->filename = filename;
}

void MeshReader::collapse()
{

}

void MeshReader::draw()
{
	std::cout << "DRAWING MESH" << std::endl;
	glColor3f(1, 0, 0);
	for (int i = 0; i < mesh.faces; i++)
	{
		glBegin(GL_TRIANGLES);
		point v1 = mesh.vertList[mesh.faceList[i].v1];
		point v3 = mesh.vertList[mesh.faceList[i].v3];
		point v2 = mesh.vertList[mesh.faceList[i].v2];
		glVertex3f(v1.x, v1.y, v1.z);
		glVertex3f(v2.x, v2.y, v2.z);
		glVertex3f(v3.x, v3.y, v3.z);
		glEnd();
	}
}


void MeshReader::read()
{
	//MeshReader from Assignment 2 template

	float x, y, z, len;
	int i;
	char letter;
	point v1, v2, crossP;
	int ix, iy, iz;
	int *normCount;
	FILE *fp;

	fp = fopen(filename, "r");
	if (fp == NULL) {
		printf("Cannot open %s\n!", filename);
		exit(0);
	}

	// Count the number of vertices and faces
	while (!feof(fp))
	{
		fscanf(fp, "%c %f %f %f\n", &letter, &x, &y, &z);
		if (letter == 'v')
		{
			mesh.verts++;
		}
		else
		{
			mesh.faces++;
		}
	}

	fclose(fp);

	printf("verts : %d\n", mesh.verts);
	printf("faces : %d\n", mesh.faces);

	// Dynamic allocation of vertex and face lists
	mesh.faceList = (faceStruct *)malloc(sizeof(faceStruct)*mesh.faces);
	mesh.vertList = (point *)malloc(sizeof(point)*mesh.verts);
	mesh.normList = (point *)malloc(sizeof(point)*mesh.verts);

	fp = fopen(filename, "r");

	// Read the veritces
	for (i = 0; i < mesh.verts; i++)
	{
		fscanf(fp, "%c %f %f %f\n", &letter, &x, &y, &z);
		mesh.vertList[i].x = x;
		mesh.vertList[i].y = y;
		mesh.vertList[i].z = z;
	}

	// Read the faces
	for (i = 0; i < mesh.faces; i++)
	{
		fscanf(fp, "%c %d %d %d\n", &letter, &ix, &iy, &iz);
		mesh.faceList[i].v1 = ix - 1;
		mesh.faceList[i].v2 = iy - 1;
		mesh.faceList[i].v3 = iz - 1;
	}
	fclose(fp);


	// The part below calculates the normals of each vertex
	normCount = (int *)malloc(sizeof(int)*mesh.verts);
	for (i = 0; i < mesh.verts; i++)
	{
		mesh.normList[i].x = mesh.normList[i].y = mesh.normList[i].z = 0.0;
		normCount[i] = 0;
	}

	for (i = 0; i < mesh.faces; i++)
	{
		v1.x = mesh.vertList[mesh.faceList[i].v2].x - mesh.vertList[mesh.faceList[i].v1].x;
		v1.y = mesh.vertList[mesh.faceList[i].v2].y - mesh.vertList[mesh.faceList[i].v1].y;
		v1.z = mesh.vertList[mesh.faceList[i].v2].z - mesh.vertList[mesh.faceList[i].v1].z;
		v2.x = mesh.vertList[mesh.faceList[i].v3].x - mesh.vertList[mesh.faceList[i].v2].x;
		v2.y = mesh.vertList[mesh.faceList[i].v3].y - mesh.vertList[mesh.faceList[i].v2].y;
		v2.z = mesh.vertList[mesh.faceList[i].v3].z - mesh.vertList[mesh.faceList[i].v2].z;

		crossP.x = v1.y*v2.z - v1.z*v2.y;
		crossP.y = v1.z*v2.x - v1.x*v2.z;
		crossP.z = v1.x*v2.y - v1.y*v2.x;

		len = sqrt(crossP.x*crossP.x + crossP.y*crossP.y + crossP.z*crossP.z);

		crossP.x = -crossP.x / len;
		crossP.y = -crossP.y / len;
		crossP.z = -crossP.z / len;

		mesh.normList[mesh.faceList[i].v1].x = mesh.normList[mesh.faceList[i].v1].x + crossP.x;
		mesh.normList[mesh.faceList[i].v1].y = mesh.normList[mesh.faceList[i].v1].y + crossP.y;
		mesh.normList[mesh.faceList[i].v1].z = mesh.normList[mesh.faceList[i].v1].z + crossP.z;
		mesh.normList[mesh.faceList[i].v2].x = mesh.normList[mesh.faceList[i].v2].x + crossP.x;
		mesh.normList[mesh.faceList[i].v2].y = mesh.normList[mesh.faceList[i].v2].y + crossP.y;
		mesh.normList[mesh.faceList[i].v2].z = mesh.normList[mesh.faceList[i].v2].z + crossP.z;
		mesh.normList[mesh.faceList[i].v3].x = mesh.normList[mesh.faceList[i].v3].x + crossP.x;
		mesh.normList[mesh.faceList[i].v3].y = mesh.normList[mesh.faceList[i].v3].y + crossP.y;
		mesh.normList[mesh.faceList[i].v3].z = mesh.normList[mesh.faceList[i].v3].z + crossP.z;
		normCount[mesh.faceList[i].v1]++;
		normCount[mesh.faceList[i].v2]++;
		normCount[mesh.faceList[i].v3]++;
	}
	for (i = 0; i < mesh.verts; i++)
	{
		mesh.normList[i].x = (float)sign*mesh.normList[i].x / (float)normCount[i];
		mesh.normList[i].y = (float)sign*mesh.normList[i].y / (float)normCount[i];
		mesh.normList[i].z = (float)sign*mesh.normList[i].z / (float)normCount[i];
	}
}