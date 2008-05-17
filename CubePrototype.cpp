#include "CubePrototype.h"
#include <bullet/LinearMath/btVector3.h>
#include <bullet/BulletCollision/CollisionShapes/btBoxShape.h>
#include <irrlicht.h>

using irr::core::vector3df;
using irr::scene::ISceneNode;
using irr::scene::ISceneManager;

  CubePrototype::CubePrototype(const vector3df &tScale)
: tScale_(new vector3df(tScale))
{}
ISceneNode* CubePrototype::createSceneNode(ISceneManager* smgr) const
{
  ISceneNode* node = smgr->addCubeSceneNode(1.0f);
  node->setScale(*tScale_);
  return node;

}
CubePrototype::~CubePrototype()
{
  delete tScale_;
}
btCollisionShape* CubePrototype::createShape() const
{
  btVector3 halfExtents(tScale_->X * 0.5f, tScale_->Y * 0.5f, tScale_->Z * 0.5f);
  return new btBoxShape(halfExtents);
}
