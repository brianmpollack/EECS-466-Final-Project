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

	/*std::map<int, Vertex>::iterator it;
	for (it = mesh.vertList.begin(); it != mesh.vertList.end(); it++)
	{
		Vertex v1 = it->second;

		std::vector<int>::iterator it2;
		for (it2 = v1.connectedVerticesIDs.begin(); it2 != v1.connectedVerticesIDs.end(); it2++)
		{
			Vertex v2 = mesh.vertList[*it2];
			std::vector<int>::iterator it3;
			for (it3 = it2; it3 != v1.connectedVerticesIDs.end(); it3++)
			{
				Vertex v3 = mesh.vertList[*it3];
				//If v3 is connected to v2
				//std::cout << "V2" << v2.x << "," << "v2.y" << "," << v2.z << std::endl;
				//Vertex vtest = *v2.connectedVertices[0];
				//std::cout << vtest.x << "," << vtest.y << "," << vtest.z << std::endl;
				if (std::find(v2.connectedVerticesIDs.begin(), v2.connectedVerticesIDs.end(), v3.id) != v2.connectedVerticesIDs.end())
				{
					//std::cout << "PRINTING TRIANGLE" << std::endl;
					glBegin(GL_TRIANGLES);
					glVertex3f(v1.x, v1.y, v1.z);
					glVertex3f(v2.x, v2.y, v2.z);
					glVertex3f(v3.x, v3.y, v3.z);
					glEnd();
				}
				//return;
			}
		}
	}*/
	// for (int i = 0; i < mesh.faces; i++)
	for (std::vector<Face>::iterator it = mesh.faceList.begin(); it != mesh.faceList.end(); it++)
	{
		Face f = *it;
		glBegin(GL_TRIANGLES);
		glVertex3f(f.v1->x, f.v1->y, f.v1->z);
		glVertex3f(f.v2->x, f.v2->y, f.v2->z);
		glVertex3f(f.v3->x, f.v3->y, f.v3->z);
		glEnd();
	}
	/*for (int i = 0; i < mesh.faces; i++)
	{
		glBegin(GL_TRIANGLES);
		Vertex v1 = mesh.vertList[mesh.faceList[i].v1];
		Vertex v3 = mesh.vertList[mesh.faceList[i].v3];
		Vertex v2 = mesh.vertList[mesh.faceList[i].v2];
		glVertex3f(v1.x, v1.y, v1.z);
		glVertex3f(v2.x, v2.y, v2.z);
		glVertex3f(v3.x, v3.y, v3.z);
		glEnd();
	}*/
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
	//mesh.faceList = (faceStruct *)malloc(sizeof(faceStruct)*mesh.faces);

	fp = fopen(filename, "r");

	// Read the veritces
	for (i = 0; i < mesh.verts; i++)
	{
		fscanf(fp, "%c %f %f %f\n", &letter, &x, &y, &z);
		mesh.vertList.insert(std::pair <int, Vertex>(i, Vertex(x, y, z, i)));
	}

	// Read the faces
	for (i = 0; i < mesh.faces; i++)
	{
		fscanf(fp, "%c %d %d %d\n", &letter, &ix, &iy, &iz);
		/*mesh.faceList[i].v1 = ix - 1;
		mesh.faceList[i].v2 = iy - 1;
		mesh.faceList[i].v3 = iz - 1;*/
		/*mesh.vertList[ix].connectedVerticesIDs.push_back(iy);
		mesh.vertList[ix].connectedVerticesIDs.push_back(iz);
		mesh.vertList[iy].connectedVerticesIDs.push_back(ix);
		mesh.vertList[iy].connectedVerticesIDs.push_back(iz);
		mesh.vertList[iz].connectedVerticesIDs.push_back(ix);
		mesh.vertList[iz].connectedVerticesIDs.push_back(iy);*/
		mesh.faceList.push_back(Face(&mesh.vertList[ix-1], &mesh.vertList[iy-1], &mesh.vertList[iz-1]));
	}
	fclose(fp);


	// The part below calculates the normals of each vertex

	/*for (i = 0; i < mesh.faces; i++)
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

		mesh.vertList[mesh.faceList[i].v1].addNormal(crossP.x, crossP.y, crossP.z);
		mesh.vertList[mesh.faceList[i].v2].addNormal(crossP.x, crossP.y, crossP.z);
		mesh.vertList[mesh.faceList[i].v3].addNormal(crossP.x, crossP.y, crossP.z);
	}*/
	/*for (i = 0; i < mesh.verts; i++)
	{
		mesh.vertList[i].normX = (float)sign*mesh.vertList[i].normX / mesh.vertList[i].normCount;
		mesh.vertList[i].normY = (float)sign*mesh.vertList[i].normX / mesh.vertList[i].normCount;
		mesh.vertList[i].normZ = (float)sign*mesh.vertList[i].normX / mesh.vertList[i].normCount;
	}*/
}