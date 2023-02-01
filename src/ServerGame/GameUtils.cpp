#include "pch.h"
#include "GameUtils.h"


void GameUtils::SetVector3(Protocol::Vector* v1, Vector3& v2)
{
	v1->set_x(v2.x);
	v1->set_y(v2.y);
	v1->set_z(v2.z);	
}


void GameUtils::SetVector3(Npc::Vector3* v1, Vector3&& v2)
{
	v1->set_x(v2.x);
	v1->set_y(v2.y);
	v1->set_z(v2.z);
}