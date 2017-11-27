#pragma once
#include "MeshReader.h"
#include "common.h"
class Helicopter
{
private:
	MeshReader mesh_body;
	MeshReader mesh_blades;
	float blades_rotation_theta = 0;
public:
	Helicopter();
	~Helicopter();
	void draw();
	void doAnimation();
};

