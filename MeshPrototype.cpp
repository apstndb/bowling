#include "bullet/btBulletDynamicsCommon.h"
#include "irrlicht.h"
#include "MeshPrototype.h"
#include "convert.h"
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
 // btTriangleMesh* pMesh;
  //ConvertCollisionMesh(mesh_->getMesh(0, 255), pMesh, irr::core::vector3df(1,1,1));


  //btConvexHullShape* shape = new(btConvexHullShape);
  //constructConvexHull(mesh_->getMesh(0, 255), shape, irr::core::vector3df(1,1,1));
  //std::cout << mesh_->getFrameCount() << std::endl;
	return new btCylinderShape(btVector3(0.121/2, 0.381/2, 0.121/2));
}
