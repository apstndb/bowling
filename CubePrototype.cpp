#include "bullet/btBulletDynamicsCommon.h"
#include "irrlicht.h"
#include "CubePrototype.h"
CubePrototype::CubePrototype(const irr::core::vector3df &TScale)
  : TScale_(TScale)
{}
irr::scene::ISceneNode* CubePrototype::createSceneNode(irr::scene::ISceneManager* smgr) const
{
  irr::scene::ISceneNode* Node = smgr->addCubeSceneNode(1.0f);
  Node->setScale(TScale_);
  return Node;

}
btCollisionShape* CubePrototype::createShape() const
{
  btVector3 HalfExtents(TScale_.X * 0.5f, TScale_.Y * 0.5f, TScale_.Z * 0.5f);
  return new btBoxShape(HalfExtents);
}
