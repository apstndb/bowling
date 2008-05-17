#ifndef CUBE_PROTOTYPE_H
#define CUBE_PROTOTYPE_H
#include "Prototype.h"

namespace irr {
  typedef float f32;
  namespace scene {
    class ISceneNode;
    class ISceneManager;
  }
  namespace core {
    template<class T> class vector3d;
    typedef vector3d<irr::f32> vector3df;
  }
}
class CubePrototype : public Prototype
{
  private:
    irr::core::vector3df* tScale_;
  public:
    CubePrototype(const irr::core::vector3df& tScale);
    ~CubePrototype();
    btCollisionShape* createShape() const;
    irr::scene::ISceneNode* createSceneNode(irr::scene::ISceneManager* smgr) const;
};
#endif
