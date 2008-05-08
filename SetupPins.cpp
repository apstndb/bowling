#include <boost/bind.hpp>
#include <algorithm>
#include <bullet/btBulletDynamicsCommon.h>
#include "main.h"
#include "CreateMesh.h"
#include <cmath>
btVector3 getXZVector(btScalar deg, btScalar y = 0.0)
{
  btScalar rad = btRadians(deg);
  return btVector3(sin(rad), y, cos(rad));
}
void SetupPins()
{
  btVector3 vectors[10];
  for(size_t i = 0; i != 3; ++i) {
    vectors[i] = 0.4 * getXZVector(i*360/3+180, 0.200f);
  }
  for(size_t i = 0; i != 6; ++i) {
    vectors[i+3] = 0.4/sqrt(3) * getXZVector(i*360/6+30, 0.200f);
  }
  vectors[9] = btVector3(0, 0, 0);

  std::for_each(vectors, vectors+10, bind(&btVector3::operator+=, _1, btVector3(0, 0, 18.288-0.4)));
  std::for_each(vectors, vectors+10, bind(CreateMesh, _1, irrScene->getMesh("./missile.x"), 1.6f));
}
