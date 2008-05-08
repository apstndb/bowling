//#include <bullet/btBulletDynamicsCommon.h>
#include <bullet/LinearMath/btVector3.h>
class btQuaternion;
btVector3 getXZVector(btScalar deg, btScalar y = 0.0);
void QuaternionToEuler(const btQuaternion &, btVector3 &);
int GetRandInt(int);
