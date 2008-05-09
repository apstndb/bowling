#ifndef UTIL_H
#define UTIL_H
typedef float btScalar;
class btVector3;
class btQuaternion;

btVector3 getXZVector(btScalar deg, btScalar y = 0.0);
void QuaternionToEuler(const btQuaternion &, btVector3 &);
int GetRandInt(int);
#endif
