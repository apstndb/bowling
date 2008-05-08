#include <bullet/LinearMath/btVector3.h>
#include <bullet/BulletCollision/CollisionShapes/btBoxShape.h>
#include <irrlicht.h>
#include "CubePrototype.h"

using irr::core::vector3df;
using irr::scene::ISceneNode;
using irr::scene::ISceneManager;

CubePrototype::CubePrototype(const vector3df &TScale)
  : TScale_(TScale)
{}
ISceneNode* CubePrototype::createSceneNode(ISceneManager* smgr) const
{
  ISceneNode* Node = smgr->addCubeSceneNode(1.0f);
  Node->setScale(TScale_);
  return Node;

}
btCollisionShape* CubePrototype::createShape() const
{
  btVector3 HalfExtents(TScale_.X * 0.5f, TScale_.Y * 0.5f, TScale_.Z * 0.5f);
  return new btBoxShape(HalfExtents);
}
