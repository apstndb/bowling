#include "bullet/btBulletDynamicsCommon.h"
#include "irrlicht.h"
#include "SpherePrototype.h"
SpherePrototype::SpherePrototype(btScalar TRadius)
  : TRadius_(TRadius)
{}
irr::scene::ISceneNode* SpherePrototype::createSceneNode(irr::scene::ISceneManager* smgr) const
{
  irr::scene::ISceneNode* Node = smgr->addSphereSceneNode(TRadius_, 32);
  return Node;

}
btCollisionShape* SpherePrototype::createShape() const
{
	return new btSphereShape(TRadius_);
}
