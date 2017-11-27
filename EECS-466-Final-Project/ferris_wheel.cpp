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
	wheel.reduce();
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
	draw_passenger_car(0);
	draw_passenger_car(PI / 8.0); // 2PI/16
	draw_passenger_car(2.0 * PI / 8.0); // 4PI/16
	draw_passenger_car(3.0 * PI / 8.0); // 6PI/16
	draw_passenger_car(4.0 * PI / 8.0); // 8PI/16
	draw_passenger_car(5.0 * PI / 8.0); // 10PI/16
	draw_passenger_car(6.0 * PI / 8.0); // 12PI/16
	draw_passenger_car(7.0 * PI / 8.0); // 14PI/16
	draw_passenger_car(PI); // 16PI/16
	draw_passenger_car(9.0 * PI / 8.0); // 18PI/16
	draw_passenger_car(10.0 * PI / 8.0); // 20PI/16
	draw_passenger_car(11.0 * PI / 8.0); // 22PI/16
	draw_passenger_car(12.0 * PI / 8.0); // 24PI/16
	draw_passenger_car(13.0 * PI / 8.0); // 26PI/16
	draw_passenger_car(14.0 * PI / 8.0); // 28PI/16
	draw_passenger_car(15.0 * PI / 8.0); // 30PI/16
}

void FerrisWheel::draw_passenger_car(double theta)
{
	//car.draw(-100*sin(theta), 100-100*cos(theta));
}