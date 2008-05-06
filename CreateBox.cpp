#include "CreateBox.h"
#include "CreateShape.h"
#include "CubePrototype.h"
#include <bullet/btBulletDynamicsCommon.h>
#include "main.h"

using namespace irr;
using namespace core;
using namespace scene;
using namespace video;

// Create a box rigid body
void CreateBox(const btVector3 &TPosition, const vector3df &TScale, btScalar TMass) {
  CreateShape(CubePrototype(TScale), TPosition, TMass);
}
