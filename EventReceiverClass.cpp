#include "EventReceiverClass.h"
#include "util.h"
#include "constant.h"
#include "AloneBowling.h"
#include <irrlicht.h>
#include <LinearMath/btVector3.h>

using namespace irr;
using namespace core;
bool EventReceiverClass::OnEvent(const SEvent &tEvent) {

  if(tEvent.EventType == EET_KEY_INPUT_EVENT && !tEvent.KeyInput.PressedDown) {
    switch(tEvent.KeyInput.Key) {
      case KEY_ESCAPE:
        game_->end();//dev_->closeDevice();
        break;
      case KEY_KEY_1:
        //game_->CreateBox(btVector3(GetRandInt(10) - 5.0f, 7.0f, GetRandInt(10) - 5.0f), vector3df(GetRandInt(3) + 0.5f, GetRandInt(3) + 0.5f, GetRandInt(3) + 0.5f), 1.0f);
        break;
      case KEY_KEY_2:
        //game_->CreateSphere(btVector3(GetRandInt(10) - 5.0f, 1.0f, GetRandInt(10) - 5.0f), GetRandInt(5) / 5.0f + 0.2f, 3.62f);
        //game_->CreateSphere(btVector3(0.0f, 0.2f, 0.0f), 0.218f, 3.62f);
        //game_->BallSetVelocity(Factor*btVector3((GetRandInt(101)-50)/100.0f,0,10),btVector3(0,0,0));

        game_->BallSetVelocity(Factor*(GetRandInt(11)+10)*getXZVector((GetRandInt(101)-50)/40.0f), btVector3(0,GetRandInt(101)-50,0));
        break;
      case KEY_KEY_3:
        //game_->CreateMesh(btVector3(GetRandInt(10) - 5.0f, 7.0f, GetRandInt(10) - 5.0f), dev_->getSceneManager()->getMesh("./missile.x"), 1.6f);
        break;
      case KEY_KEY_4:
        game_->SetupPins();
        break;
      case KEY_KEY_X:
        game_->CreateStartScene();
        break;
      default:
        return false;
        break;
    }

    return true;
  }

  return false;
}

  EventReceiverClass::EventReceiverClass(AloneBowling* game, IrrlichtDevice* dev)
:game_(game),
  dev_(dev)
{}
