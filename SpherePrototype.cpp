#include <BulletCollision/CollisionShapes/btSphereShape.h>
#include <irrlicht.h>
#include "SpherePrototype.h"

using irr::scene::ISceneNode;
using irr::scene::ISceneManager;

  SpherePrototype::SpherePrototype(btScalar tRadius)
: tRadius_(tRadius)
{}
ISceneNode* SpherePrototype::createSceneNode(ISceneManager* smgr) const
{
  ISceneNode* node = smgr->addSphereSceneNode(tRadius_, 32);
  return node;

}
btCollisionShape* SpherePrototype::createShape() const
{
  return new btSphereShape(tRadius_);
}
