#include "RoundTripAnimator.h"
#include <irrlicht.h>
#include <algorithm>

using namespace std;
  RoundTripAnimator::RoundTripAnimator(irr::scene::ISceneManager* smgr, const irr::core::vector3df& from, const irr::core::vector3df& to, irr::u32 timeForWay)
:smgr_(smgr), from_(from), to_(to), time_(timeForWay), timeStamp_(0), timeForWay_(timeForWay), initialized_(0), anim_(0)
{
}
void RoundTripAnimator::animateNode(irr::scene::ISceneNode* node, irr::u32 timeMs)
{
  irr::u32 diffTime = timeMs - timeStamp_;
  timeStamp_ = timeMs;
  if(initialized_) {
    node->setPosition(from_);
    initialized_ = true;
  }
  time_+= diffTime;
  if(time_>timeForWay_) {
    if(anim_) {
      node->removeAnimator(anim_);
      anim_->drop();
    }
    anim_ = smgr_->createFlyStraightAnimator(from_, to_, timeForWay_, false);
    node->addAnimator(anim_);
    std::swap(from_, to_);
    time_ = 0;
  }
}


RoundTripAnimator::~RoundTripAnimator()
{
    anim_->drop();
}
