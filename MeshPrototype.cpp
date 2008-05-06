#include "bullet/btBulletDynamicsCommon.h"
#include "irrlicht.h"
#include "MeshPrototype.h"
MeshPrototype::MeshPrototype(irr::scene::IAnimatedMesh* mesh)
  : mesh_(mesh)
{}
irr::scene::ISceneNode* MeshPrototype::createSceneNode(irr::scene::ISceneManager* smgr) const
{
  irr::scene::ISceneNode* Node = smgr->addAnimatedMeshSceneNode(mesh_);
  return Node;

}
btCollisionShape* MeshPrototype::createShape() const
{
	return new btSphereShape(1.0);
}
