#include "Prototype.h"
#include "bullet/btBulletDynamicsCommon.h"
class irr::scene::IAnimatedMesh;

class MeshPrototype : public Prototype
{
  private:
    irr::scene::IAnimatedMesh* mesh_;

  public:
    MeshPrototype(irr::scene::IAnimatedMesh* mesh);
    btCollisionShape* createShape() const;
    irr::scene::ISceneNode* createSceneNode(irr::scene::ISceneManager* smgr) const;
};
