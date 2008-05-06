#include "UpdatePhysics.h"
#include "UpdateRender.h"
#include "btBulletDynamicsCommon.h"
#include "main.h"

using namespace irr;
using namespace core;

// Runs the physics simulation.
// - TDeltaTime tells the simulation how much time has passed since the last frame so the simulation can run independently of the frame rate.
void UpdatePhysics(u32 TDeltaTime) {

	World->stepSimulation(TDeltaTime * 0.001f, 60);

	// Relay the object's orientation to irrlicht
	for(list<btRigidBody *>::Iterator Iterator = Objects.begin(); Iterator != Objects.end(); ++Iterator) {

		UpdateRender(*Iterator);
	}	
}

