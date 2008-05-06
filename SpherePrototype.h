#include "Prototype.h"
#include "bullet/btBulletDynamicsCommon.h"

class SpherePrototype : public Prototype
{
  private:
      btScalar TRadius_;
  public:
      SpherePrototype(btScalar TRadius);
      btCollisionShape* createShape() const;
      irr::scene::ISceneNode* createSceneNode(irr::scene::ISceneManager* smgr) const;
};
