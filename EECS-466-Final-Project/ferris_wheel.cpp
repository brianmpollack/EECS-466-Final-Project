#pragma once
#include "ferris_wheel.h"

FerrisWheel::FerrisWheel(float radius)
{
	this->radius = radius;
	//Set mesh readers
	passenger_car_mesh_reader.setFilename("diamond.obj");
	passenger_car_mesh_reader.read();
}

void FerrisWheel::draw()
{
	draw_passenger_cars();
}

void FerrisWheel::draw_passenger_cars()
{
	double step = 2 * PI / 10;
	double rotation = 0;

	for (int i = 0; i<10; i++)
	{
		double passenger_box_x = radius * cos(i*step + rotation);
		double passenger_box_y = radius * sin(i*step + rotation);
		FerrisWheel::draw_passenger_car(passenger_box_x, passenger_box_y, 0);
		return; //TODO: REMOVE - LIMITS TO ONE CAR
	}
}

void FerrisWheel::draw_passenger_car(double x, double y, double z)
{

	//  Save transformation
	glPushMatrix();
	//  Offset
	glTranslated(x, y, z);
	glRotated(rotation, 0, 1, 0);


	//glScaled(dx, dy, dz); TODO MIGHT WANT THIS

	passenger_car_mesh_reader.draw();
	
}