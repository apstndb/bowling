#include "EventReceiverClass.h"
#include "util.h"
#include "constant.h"
#include "AloneBowling.h"
#include <irrlicht.h>
#include <LinearMath/btVector3.h>
#include <iostream>

using namespace irr;
using namespace core;
bool EventReceiverClass::OnEvent(const SEvent &tEvent) {

  if(tEvent.EventType == EET_KEY_INPUT_EVENT && !tEvent.KeyInput.PressedDown) {
    switch(tEvent.KeyInput.Key) {
      case KEY_ESCAPE:
        game_->setState(GAME_END);//dev_->closeDevice();
        break;
      case KEY_KEY_1:
        //std::cout << game_->getArrowRad() << std::endl;
        //game_->CreateBox(btVector3(GetRandInt(10) - 5.0f, 7.0f, GetRandInt(10) - 5.0f), vector3df(GetRandInt(3) + 0.5f, GetRandInt(3) + 0.5f, GetRandInt(3) + 0.5f), 1.0f);
        break;
      case KEY_KEY_2:
        if(game_->getState()==GAME_WAIT) {
          game_->BallSetVelocity(BallSpeed*getXZVector(game_->getArrowRad()), btVector3(0,0,0));
          game_->stopArrow();
          game_->setState(GAME_RUNNING);
        }
        break;
      case KEY_KEY_3:
        //game_->CreateMesh(btVector3(GetRandInt(10) - 5.0f, 7.0f, GetRandInt(10) - 5.0f), dev_->getSceneManager()->getMesh("./missile.x"), 1.6f);
        break;
      case KEY_KEY_4:
        game_->SetupPins();
        break;
      case KEY_KEY_X:
        game_->misc();
        break;
      default:
        return false;
        break;
    }

    return true;
  }

  return false;
}

  EventReceiverClass::EventReceiverClass(AloneBowling* game)
:game_(game)
{}
