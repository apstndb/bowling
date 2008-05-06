#include "SpherePrototype.h"
#include "CreateShape.h"
#include <bullet/btBulletDynamicsCommon.h>
#include "main.h"

using namespace irr;
using namespace core;
using namespace scene;
using namespace video;

// Create a sphere rigid body
void CreateSphere(const btVector3 &TPosition, btScalar TRadius, btScalar TMass) 
{
  CreateShape(SpherePrototype(TRadius), TPosition, TMass);
}
