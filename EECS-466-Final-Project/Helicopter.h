#pragma once
#include "MeshReader.h"
#include "common.h"
class Helicopter
{
private:
	MeshReader mesh_body;
	MeshReader mesh_blades;
public:
	Helicopter();
	~Helicopter();
	void draw();
};

