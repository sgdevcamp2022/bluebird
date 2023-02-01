#pragma once

using std::cout; using std::endl;
using std::chrono::duration_cast;
using std::chrono::milliseconds;
using std::chrono::seconds;
using std::chrono::system_clock;

class GameUtils
{
public:
	static void SetVector3(Protocol::Vector* v1, Vector3& v2) ;
	static void SetVector3(Npc::Vector3* v1, Vector3&& v2) ;

	static int64 GetTick() {
		return duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();
	}
};

