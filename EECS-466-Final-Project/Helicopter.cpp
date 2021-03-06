#include "Helicopter.h"



Helicopter::Helicopter()
{
	mesh_body.setFilename("helicopter-noblades.obj");
	mesh_blades.setFilename("helicopter-bladesonly.obj");
	mesh_body.read();
	mesh_blades.read();
	mesh_body.reduce(reductionRatio);
	mesh_blades.reduce(0.15);
}


Helicopter::~Helicopter()
{
}


void Helicopter::draw()
{
	mesh_body.draw();
	//glRotatef(PI / 12, 0.0, 1.0, 0.0);
	//glRotatef(PI / 4, 0.0, 0.0, 1.0);
	//glPushMatrix();
	//glRotatef(PI / 4, 0.0f, 1.0f, 1.0f);
	mesh_blades.draw(blades_rotation_theta);
	//glPopMatrix();
}

void Helicopter::doAnimation()
{
	blades_rotation_theta += PI / 64;
	if (blades_rotation_theta > 2 * PI)
		blades_rotation_theta = 0;
}

void Helicopter::increaseRatio()
{
	mesh_body.reset();
	reductionRatio += 0.10;
	mesh_body.reduce(reductionRatio);
}
void Helicopter::decreaseRatio()
{
	mesh_body.reset();
	reductionRatio -= 0.10;
	mesh_body.reduce(reductionRatio);
}