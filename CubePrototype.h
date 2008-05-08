#ifndef CUBEPROTOTYPE_H
#define CUBEPROTOTYPE_H
#include "Prototype.h"
//#include "irrlicht.h"

class CubePrototype : public Prototype
{
  private:
      irr::core::vector3df TScale_;
  public:
      CubePrototype(const irr::core::vector3df& TScale);
      btCollisionShape* createShape() const;
      irr::scene::ISceneNode* createSceneNode(irr::scene::ISceneManager* smgr) const;
};
#endif
