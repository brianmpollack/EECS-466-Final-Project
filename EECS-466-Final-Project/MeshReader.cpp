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

void MeshReader::draw(float x_trans, float y_trans)
{
	//std::cout << "DRAWING MESH" << std::endl;
	glColor3f(1, 0, 0);

	//int tempSTOP = 0; //TODO: REMOVE
	int numFacesPrinted = 0;
/*
	std::map<int, std::shared_ptr<Vertex>>::iterator it; //All vertices
	for (it = mesh.vertList.begin(); it != mesh.vertList.end(); it++)
	{
		auto v1 = it->second;
		if (v1->isDeleted == true) continue;

		std::vector<std::shared_ptr<Edge>>::iterator it2; //v1's edges
		for (it2 = v1->edges.begin(); it2 != v1->edges.end(); it2++)
		{
			auto v2 = (*it2)->v2;
			if (v2->isDeleted == true) continue;
			std::vector<std::shared_ptr<Edge>>::iterator it3; //v2's edges
			for (it3 = it2; it3 != v1->edges.end(); it3++)
			{
				auto v3 = (*it3)->v2;
				//If v3 is connected to v2
				//std::cout << "V2" << v2.x << "," << "v2.y" << "," << v2.z << std::endl;
				//Vertex vtest = *v2.connectedVertices[0];
				//std::cout << vtest.x << "," << vtest.y << "," << vtest.z << std::endl;
				//if (std::find(v2.connectedVertices.begin(), v2.connectedVertices.end(), &v3) != v2.connectedVertices.end())
				if (v2->isConnectedTo(v3))
				{
					//std::cout << "PRINTING TRIANGLE" << std::endl;
					glBegin(GL_TRIANGLES);
					glVertex3f(v1->x, v1->y, v1->z);
					glVertex3f(v2->x, v2->y, v2->z);
					glVertex3f(v3->x, v3->y, v3->z);
					glEnd();
					numFacesPrinted++;
				}
				//if (tempSTOP > 5) return;
				//tempSTOP ++ ;
			}
		}
	}
	std::cout << "NUM FACES PRINTED: " << numFacesPrinted << std::endl;*/

	for (auto face : mesh.faceList)
	{
		if (face->deleted == true) continue;
		glBegin(GL_TRIANGLES);
		glVertex3f(face->v1->x + x_trans, face->v1->y, face->v1->z + y_trans);
		glVertex3f(face->v2->x + x_trans, face->v2->y, face->v2->z + y_trans);
		glVertex3f(face->v3->x + x_trans, face->v3->y, face->v3->z + y_trans);
		glEnd();
		numFacesPrinted++;
	}
	std::cout << "NUM FACES PRINTED: " << numFacesPrinted << std::endl;
	// for (int i = 0; i < mesh.faces; i++)
	/*for (std::vector<Face>::iterator it = mesh.faceList.begin(); it != mesh.faceList.end(); it++)
	{
		Face f = *it;
		glBegin(GL_TRIANGLES);
		glVertex3f(f.v1->x, f.v1->y, f.v1->z);
		glVertex3f(f.v2->x, f.v2->y, f.v2->z);
		glVertex3f(f.v3->x, f.v3->y, f.v3->z);
		glEnd();
	}*/
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
	//point v1, v2, crossP;
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
	for (i = 1; i <= mesh.verts; i++)
	{
		fscanf(fp, "%c %f %f %f\n", &letter, &x, &y, &z);
		mesh.vertList.insert(std::pair <int, std::shared_ptr<Vertex>>(i, std::make_shared<Vertex>(x, y, z, i)));
		//auto shared_vertex = std::make_shared<Vertex>(x, y, z, i);
		//std::cout << "Inserting vertex number" << i << std::endl;
	}


	std::cout << "Vertex numbering test: 3......" << mesh.vertList[3]->id << std::endl;

	// Read the faces
	for (i = 0; i < mesh.faces; i++)
	{
		fscanf(fp, "%c %d %d %d\n", &letter, &ix, &iy, &iz);
		
		mesh.faceList.push_back(std::make_shared<Face>(Face(mesh.vertList[ix], mesh.vertList[iy], mesh.vertList[iz])));
	}
	fclose(fp);

}