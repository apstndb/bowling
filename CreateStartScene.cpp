#include "irrlicht.h"
#include "CreateBox.h"
#include "ClearObjects.h"
#include "CreateStartScene.h"

using irr::core::vector3df;
// Creates a base box
void CreateStartScene() {

	ClearObjects();
	//CreateBox(btVector3(0.0f, 0.0f, 0.0f), vector3df(10.0f, 0.5f, 10.0f), 0.0f);
	CreateBox(btVector3(0.0f, 0.0f, 0.0f), vector3df(1.066f, 0.5f, 23.72f), 0.0f);
}
