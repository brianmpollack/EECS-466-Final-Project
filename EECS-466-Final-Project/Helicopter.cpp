#include "Helicopter.h"



Helicopter::Helicopter()
{
	mesh_body.setFilename("helicopter-noblades.obj");
	mesh_blades.setFilename("helicopter-bladesonly.obj");
	mesh_body.read();
	mesh_blades.read();
}


Helicopter::~Helicopter()
{
}


void Helicopter::draw()
{
	mesh_body.draw();
	mesh_blades.draw();
}