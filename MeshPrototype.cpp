#include "MeshPrototype.h"
#include "constant.h"
#include <bullet/BulletCollision/CollisionShapes/btCylinderShape.h>
#include <irrlicht.h>
using irr::scene::IAnimatedMesh;
using irr::scene::ISceneManager;
using irr::scene::ISceneNode;
using irr::core::vector3df;

MeshPrototype::MeshPrototype(IAnimatedMesh* mesh)
  : mesh_(mesh)
{}
ISceneNode* MeshPrototype::createSceneNode(ISceneManager* smgr) const
{
  ISceneNode* node = smgr->addAnimatedMeshSceneNode(mesh_);
  node->setScale(vector3df(0.1*Factor, 0.1*Factor, 0.1*Factor));
  return node;

}
btCollisionShape* MeshPrototype::createShape() const
{
	return new btCylinderShape(btVector3(PinsRadius, PinsHeight/2, PinsRadius));
}
