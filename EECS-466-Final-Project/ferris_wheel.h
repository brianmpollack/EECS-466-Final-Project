#pragma once
#include "common.h"
#include "MeshReader.h"

class FerrisWheel
{
private:
	MeshReader passenger_car_mesh_reader;
	float rotation = 0;
	float radius;
	void draw_passenger_car(double x, double y, double z);
	void draw_passenger_cars();
public:
	FerrisWheel(float radius);
	void draw();
};
