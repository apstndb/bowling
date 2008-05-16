#ifndef UTIL_H
#define UTIL_H
typedef float btScalar;
class btVector3;
class btQuaternion;

btVector3 getXZVector(btScalar deg);
void QuaternionToEuler(const btQuaternion &, btVector3 &);
int GetRandInt(int);
#endif
