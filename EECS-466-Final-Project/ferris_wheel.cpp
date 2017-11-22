#pragma once
#include "ferris_wheel.h"

FerrisWheel::FerrisWheel(float radius)
{
	this->radius = radius;
	car.setFilename("car.obj");
	wheel.setFilename("wheel.obj");
	base.setFilename("base.obj");
	car.read();
	wheel.read();
	base.read();
}

void FerrisWheel::draw()
{
	draw_wheel(0);
	draw_base();
	draw_passenger_cars();
}

void FerrisWheel::draw_base()
{
	base.draw();
}

void FerrisWheel::draw_wheel(double theta)
{
	wheel.draw();
}

void FerrisWheel::draw_passenger_cars()
{
	car.draw();
}

//void FerrisWheel::draw_passenger_car(double theta) {}