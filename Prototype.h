#ifndef PROTOTYPE_H
#define PROTOTYPE_H
namespace irr {
  namespace scene {
    class ISceneNode;
    class ISceneManager;
  }
}
class btCollisionShape;

class Prototype {
  public:
    virtual irr::scene::ISceneNode* createSceneNode(irr::scene::ISceneManager*) const = 0;
    virtual btCollisionShape* createShape() const = 0;
};
#endif
