#include <irrlicht/irrlicht.h>
#include <bullet/BulletDynamics/Dynamics/btRigidBody.h>
#include "UpdateRender.h"
#include "util.h"

using irr::scene::ISceneNode;
using irr::f32;
using irr::core::vector3df;
// Passes bullet's orientation to irrlicht
void UpdateRender(btRigidBody *TObject) {
  ISceneNode *node = static_cast<ISceneNode *>(TObject->getUserPointer());

	// Set position
	btPoint3 point = TObject->getCenterOfMassPosition();
	node->setPosition(vector3df((f32)point[0], (f32)point[1], (f32)point[2]));

	// Set rotation
	btVector3 eulerRotation;
	QuaternionToEuler(TObject->getOrientation(), eulerRotation);
	node->setRotation(vector3df(eulerRotation[0], eulerRotation[1], eulerRotation[2]));
}
