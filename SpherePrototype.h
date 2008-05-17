#ifndef SPHERE_PROTOTYPE_H
#define SPHERE_PROTOTYPE_H
#include "Prototype.h"

namespace irr {
  namespace scene {
    class ISceneNode;
    class ISceneManager;
  }
}
typedef float btScalar;
class SpherePrototype : public Prototype
{
  private:
    btScalar tRadius_;
  public:
    SpherePrototype(btScalar tRadius);
    btCollisionShape* createShape() const;
    irr::scene::ISceneNode* createSceneNode(irr::scene::ISceneManager* smgr) const;
};
#endif
