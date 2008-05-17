#ifndef ROUND_TRIP_ANIMATOR_H
#define ROUND_TRIP_ANIMATOR_H
#include <ISceneNodeAnimator.h>

namespace irr {
  namespace scene {
    //class ISceneManager;
    //class ISceneNode;
  }
}

class RoundTripAnimator : public irr::scene::ISceneNodeAnimator
{
  irr::scene::ISceneManager* smgr_;
  irr::core::vector3df from_, to_;
  irr::u32 time_, timeStamp_;
  const irr::u32 timeForWay_;
  bool initialized_;
  irr::scene::ISceneNodeAnimator* anim_;
  //State state_;
  public:
  RoundTripAnimator(irr::scene::ISceneManager* smgr, const irr::core::vector3df& from,
      const irr::core::vector3df& to, irr::u32 timeForWay);
  virtual void animateNode(irr::scene::ISceneNode* node, irr::u32 timeMs);
  virtual ~RoundTripAnimator();
};
#endif
