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
      btScalar TRadius_;
  public:
      SpherePrototype(btScalar TRadius);
      btCollisionShape* createShape() const;
      irr::scene::ISceneNode* createSceneNode(irr::scene::ISceneManager* smgr) const;
};
#endif
