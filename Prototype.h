#include <irrlicht.h>
class btCollisionShape;

class Prototype {
  public:
  virtual irr::scene::ISceneNode* createSceneNode(irr::scene::ISceneManager*) const = 0;
  virtual btCollisionShape* createShape() const = 0;
};
