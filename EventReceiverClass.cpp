#include "EventReceiverClass.h"
#include "util.h"
#include "constant.h"
#include "AloneBowling.h"
#include <irrlicht.h>
#include <LinearMath/btVector3.h>

using namespace irr;
using namespace core;
bool EventReceiverClass::OnEvent(const SEvent &tEvent) {
  btScalar zAxisSpin, xAxisSpin;
  if(tEvent.EventType == EET_KEY_INPUT_EVENT && !tEvent.KeyInput.PressedDown) {
    switch(tEvent.KeyInput.Key) {
      case KEY_ESCAPE:
        game_->setState(GAME_END);//dev_->closeDevice();
        break;
      case KEY_RETURN:
        if(game_->getState()==GAME_RESULT) game_->setState(GAME_END);
        break;
      case KEY_KEY_1:
      case KEY_KEY_2:
      case KEY_KEY_3:
      case KEY_KEY_4:
      case KEY_KEY_5:
      case KEY_KEY_6:
      case KEY_KEY_7:
      case KEY_KEY_8:
      case KEY_KEY_9:
      case KEY_KEY_0:
        game_->start((tEvent.KeyInput.Key==KEY_KEY_0)?
            10:tEvent.KeyInput.Key-KEY_KEY_0);
        break;
      default:
        return false;
        break;
    }

    return true;
  }
  else if(tEvent.EventType == EET_MOUSE_INPUT_EVENT) {
    switch(tEvent.MouseInput.Event) {
      case EMIE_LMOUSE_PRESSED_DOWN:
		  zAxisSpin = -Spin*(btScalar(tEvent.MouseInput.X)/ResX-0.5f);
		  xAxisSpin = Spin*(btScalar(tEvent.MouseInput.Y)/ResY-0.5f);
        if(game_->getState()==GAME_WAIT) {
          game_->BallSetVelocity(BallSpeed*getXZVector(game_->getArrowRad()),
			btVector3(xAxisSpin, 0.0f, zAxisSpin));
          game_->stopArrow();
          game_->setState(GAME_RUNNING);
        }
        break;
      case EMIE_RMOUSE_PRESSED_DOWN:
	  if(game_->getState()==GAME_RESULT) game_->setState(GAME_END);
        break;
        
      default:
        return false;
        break;
    }

    return true;
  }
  else if(tEvent.EventType == EET_USER_EVENT) {
    if(game_->getState() == GAME_LOGO) {
      game_->setState(GAME_TITLE);
    }
    else {
      game_->misc();
    }
    return true;
  }

  return false;
}

  EventReceiverClass::EventReceiverClass(AloneBowling* game)
:game_(game)
{}
