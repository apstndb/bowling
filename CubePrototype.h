#ifndef CUBEPROTOTYPE_H
#define CUBEPROTOTYPE_H
#include "Prototype.h"

namespace irr {
  namespace scene {
    class ISceneNode;
    class ISceneManager;
  }
  namespace core {
    template<class T> class vector3d;
    typedef vector3d<float> vector3df;
  }
}
class CubePrototype : public Prototype
{
  private:
      irr::core::vector3df* TScale_;
  public:
      CubePrototype(const irr::core::vector3df& TScale);
      ~CubePrototype();
      btCollisionShape* createShape() const;
      irr::scene::ISceneNode* createSceneNode(irr::scene::ISceneManager* smgr) const;
};
#endif
