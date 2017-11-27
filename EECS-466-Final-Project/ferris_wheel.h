#pragma once
#include "common.h"
#include "MeshReader.h"

class FerrisWheel
{
private:
	MeshReader car;
	MeshReader base;
	MeshReader wheel;
	float rotation = 0;
	float radius;
	void draw_passenger_car(double theta);
	void draw_passenger_cars();
	void draw_base();
	void draw_wheel(double theta);
public:
	FerrisWheel(float radius);
	void draw();
};
