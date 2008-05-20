#include <irrlicht.h>
#include <BulletDynamics/Dynamics/btRigidBody.h>
#include "UpdateRender.h"
#include "util.h"

using irr::scene::ISceneNode;
using irr::f32;
using irr::core::vector3df;
// Passes bullet's orientation to irrlicht
void UpdateRender(btRigidBody *tObject) {
  ISceneNode *node = static_cast<ISceneNode *>(tObject->getUserPointer());

  // Set position
  btPoint3 point = tObject->getCenterOfMassPosition();
  node->setPosition(vector3df((f32)point[0], (f32)point[1], (f32)point[2]));

  // Set rotation
  btVector3 eulerRotation;
  QuaternionToEuler(tObject->getOrientation(), eulerRotation);
  node->setRotation(vector3df(eulerRotation[0], eulerRotation[1], eulerRotation[2]));
}
