#include <irrlicht/irrlicht.h>
#include <bullet/btBulletDynamicsCommon.h>
#include "QuaternionToEuler.h"
#include "UpdateRender.h"

using irr::scene::ISceneNode;
using irr::f32;
using irr::core::vector3df;
// Passes bullet's orientation to irrlicht
void UpdateRender(btRigidBody *TObject) {
  ISceneNode *Node = static_cast<ISceneNode *>(TObject->getUserPointer());

	// Set position
	btPoint3 Point = TObject->getCenterOfMassPosition();
	Node->setPosition(vector3df((f32)Point[0], (f32)Point[1], (f32)Point[2]));

	// Set rotation
	btVector3 EulerRotation;
	QuaternionToEuler(TObject->getOrientation(), EulerRotation);
	Node->setRotation(vector3df(EulerRotation[0], EulerRotation[1], EulerRotation[2]));
}
