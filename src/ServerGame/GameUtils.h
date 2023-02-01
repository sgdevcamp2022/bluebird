#pragma once
class GameUtils
{
public:
	static void SetVector3(Protocol::Vector* v1, Vector3& v2) ;
	static void SetVector3(Npc::Vector3* v1, Vector3&& v2) ;
};

