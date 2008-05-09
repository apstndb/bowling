#include "MeshPrototype.h"
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
  node->setScale(vector3df(0.15, 0.15, 0.15));
  return node;

}
btCollisionShape* MeshPrototype::createShape() const
{
	return new btCylinderShape(btVector3(0.121/2, 0.381/2, 0.121/2));
}
