#include "MeshPrototype.h"
#include "CreateShape.h"
#include <bullet/btBulletDynamicsCommon.h>
#include "main.h"

class irr::scene::IAnimatedMesh;

// Create a mesh rigid body
void CreateMesh(const btVector3 &TPosition, irr::scene::IAnimatedMesh* mesh, btScalar TMass) 
{
  CreateShape(MeshPrototype(mesh), TPosition, TMass);
}
