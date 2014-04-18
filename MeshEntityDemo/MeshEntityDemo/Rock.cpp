#ifndef ROCK_H
#define ROCK_H

#include "Rock.h"
#include "..\..\Engine\Advanced2D.h"

Rock::Rock(D3DCOLORVALUE color, const btVector3 &startPos) : 
	GameObject(
	new btCylinderShape(btVector3(1.5, 1, 1)),
	10, 
	startPos, 
	btQuaternion((90), (0), (1), (0))
	)
{
	D3DCOLORVALUE ambColor;
	ambColor.r = color.r * 0.3;
	ambColor.g = color.g * 0.3;
	ambColor.b = color.b * 0.3;
	ambColor.a = 0;

	D3DCOLORVALUE diffColor;
	diffColor.r = color.r*1;
	diffColor.g = color.g*1;
	diffColor.b = color.b*1;
	diffColor.a = 0;

	CreateMeshFromShape();
	GetMesh()->SetColour(diffColor, Advanced2D::Mesh::MT_DIFFUSE);
	GetMesh()->SetColour(ambColor,Advanced2D::Mesh::MT_AMBIENT);
	GetMesh()->SetRotation(0, 90, 0);
	//GetRigidBody()->setWorldTransform(btTransform(
}


Rock::~Rock()
{
}

#endif