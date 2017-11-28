#pragma once
#include "MeshReader.h"

MeshReader::MeshReader()
{

}

void MeshReader::setFilename(char* filename)
{
	this->filename = filename;
}

void MeshReader::reduce(float ratio)
{
	mesh.reduce(ratio);
}

void MeshReader::draw(float theta)
{

	//int tempSTOP = 0; //TODO: REMOVE
	int numFacesPrinted = 0;

	float cos_theta = cos(theta);
	float sin_theta = sin(theta);

	for (auto face : mesh.faceList)
	{
		if (face->deleted == true) continue;
		glBegin(GL_TRIANGLES); 
		glColor3f(65.0/255.0, 83.0/255.0, 59.0/255.0);



		//glVertex3f(face->v1->x, face->v1->y, face->v1->z);
		//glVertex3f(face->v2->x, face->v2->y, face->v2->z);
		//glVertex3f(face->v3->x, face->v3->y, face->v3->z);

		//x' = x*cos q - y*sin q
		//y' = x*sin q + y*cos q 
		//z' = z

		glVertex3f(face->v1->x * cos_theta - face->v1->y * sin_theta,
			face->v1->x * sin_theta + face->v1->y * cos_theta,
			face->v1->z);
		glVertex3f(face->v2->x * cos_theta - face->v2->y * sin_theta,
			face->v2->x * sin_theta + face->v2->y * cos_theta,
			face->v2->z);
		glVertex3f(face->v3->x * cos_theta - face->v3->y * sin_theta,
			face->v3->x * sin_theta + face->v3->y * cos_theta,
			face->v3->z);
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

	// Read the faces
	for (i = 0; i < mesh.faces; i++)
	{
		fscanf(fp, "%c %d %d %d\n", &letter, &ix, &iy, &iz);
		
		mesh.faceList.push_back(std::make_shared<Face>(Face(mesh.vertList[ix], mesh.vertList[iy], mesh.vertList[iz])));
	}
	fclose(fp);
}

void MeshReader::reset()
{
	mesh = Mesh();
	read();
}