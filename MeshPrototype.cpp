#include "bullet/btBulletDynamicsCommon.h"
#include "irrlicht.h"
#include "MeshPrototype.h"
#include <iostream>
MeshPrototype::MeshPrototype(irr::scene::IAnimatedMesh* mesh)
  : mesh_(mesh)
{}
irr::scene::ISceneNode* MeshPrototype::createSceneNode(irr::scene::ISceneManager* smgr) const
{
  irr::scene::ISceneNode* Node = smgr->addAnimatedMeshSceneNode(mesh_);
  Node->setScale(irr::core::vector3df(0.15, 0.15, 0.15));
  return Node;

}
btCollisionShape* MeshPrototype::createShape() const
{
	return new btCylinderShape(btVector3(0.121/2, 0.381/2, 0.121/2));
}
