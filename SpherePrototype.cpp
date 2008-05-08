#include <bullet/BulletCollision/CollisionShapes/btSphereShape.h>
#include <irrlicht.h>
#include "SpherePrototype.h"

using irr::scene::ISceneNode;
using irr::scene::ISceneManager;

SpherePrototype::SpherePrototype(btScalar TRadius)
  : TRadius_(TRadius)
{}
ISceneNode* SpherePrototype::createSceneNode(ISceneManager* smgr) const
{
  ISceneNode* Node = smgr->addSphereSceneNode(TRadius_, 32);
  return Node;

}
btCollisionShape* SpherePrototype::createShape() const
{
	return new btSphereShape(TRadius_);
}
