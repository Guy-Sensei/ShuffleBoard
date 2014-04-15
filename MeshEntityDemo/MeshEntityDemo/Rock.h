#pragma once
#include "GameObject.h"

//#include "C:\Users\Jean-G\Google Drive\School\Semester 4\GAME2002\Mesh Demo Post Class\Engine\Mesh.h"
class Rock :
	public GameObject
{
public:
	Rock(D3DCOLORVALUE color, const btVector3 &startPos);
	~Rock();

	const btVector3* GetPos() { return pos; }
	void SetPos(btVector3* p) { pos = p; }
	void SetMass(int _m) { mass = _m;}
	
protected:
	btVector3* pos;
	int mass;
};

