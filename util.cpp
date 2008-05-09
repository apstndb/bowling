#include <cstdlib>
#include <bullet/LinearMath/btQuaternion.h>
#include "util.h"

int GetRandInt(int TMax) { return std::rand() % TMax; }

btVector3 getXZVector(btScalar deg, btScalar y)
{
  btScalar rad = btRadians(deg);
  return btVector3(sin(rad), y, cos(rad));
}

// Converts a quaternion to an euler angle
void QuaternionToEuler(const btQuaternion &tQuat, btVector3 &tEuler) {
	btScalar w = tQuat.getW();
	btScalar x = tQuat.getX();
	btScalar y = tQuat.getY();
	btScalar z = tQuat.getZ();
	float wSquared = w * w;
	float xSquared = x * x;
	float ySquared = y * y;
	float zSquared = z * z;

	tEuler.setX(atan2f(2.0f * (y * z + x * w), -xSquared - ySquared + zSquared + wSquared));
	tEuler.setY(asinf(-2.0f * (x * z - y * w)));
	tEuler.setZ(atan2f(2.0f * (x * y + z * w), xSquared - ySquared - zSquared + wSquared));
	tEuler *= SIMD_DEGS_PER_RAD;//irr::core::RADTODEG;
}
