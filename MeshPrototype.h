#ifndef MESHPROTOTYPE_H
#define MESHPROTOTYPE_H
#include "Prototype.h"
namespace irr {
  namespace scene {
    class IAnimatedMesh;
    class ISceneManager;
  }
}
class btCollisionShape;

class MeshPrototype : public Prototype
{
  private:
    irr::scene::IAnimatedMesh* mesh_;

  public:
    MeshPrototype(irr::scene::IAnimatedMesh* mesh);
    btCollisionShape* createShape() const;
    irr::scene::ISceneNode* createSceneNode(irr::scene::ISceneManager* smgr) const;
};
#endif
