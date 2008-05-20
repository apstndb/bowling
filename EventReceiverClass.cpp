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
      case KEY_KEY_2:
        if(game_->getState()==GAME_WAIT) {
          game_->BallSetVelocity(BallSpeed*getXZVector(game_->getArrowRad()), btVector3(0,0,0));
          game_->stopArrow();
          game_->setState(GAME_RUNNING);
        }
        break;
      /*case KEY_KEY_X:
        game_->misc();
        break;*/
      default:
        return false;
        break;
    }

    return true;
  }
  else if(tEvent.EventType == EET_MOUSE_INPUT_EVENT) {
    switch(tEvent.MouseInput.Event) {
      case EMIE_LMOUSE_PRESSED_DOWN:
        if(game_->getState()==GAME_WAIT) {
          game_->BallSetVelocity(BallSpeed*getXZVector(game_->getArrowRad()), btVector3(0,0,0));
          game_->stopArrow();
          game_->setState(GAME_RUNNING);
        }
        break;
      /*case EMIE_RMOUSE_PRESSED_DOWN:
        if(game_->getState()==GAME_RUNNING) {
          game_->misc();
        }
        break;
        */
      default:
        return false;
        break;
    }

    return true;
  }
  else if(tEvent.EventType == EET_USER_EVENT) {
    game_->misc();
    return true;
  }

  return false;
}

  EventReceiverClass::EventReceiverClass(AloneBowling* game)
:game_(game)
{}
