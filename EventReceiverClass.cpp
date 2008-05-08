#include "util.h"
#include "main.h"
#include <irrlicht/irrlicht.h>
#include "EventReceiverClass.h"

using namespace irr;
using namespace core;
bool EventReceiverClass::OnEvent(const SEvent &TEvent) {

  if(TEvent.EventType == EET_KEY_INPUT_EVENT && !TEvent.KeyInput.PressedDown) {
    switch(TEvent.KeyInput.Key) {
      case KEY_ESCAPE:
        dev_->closeDevice();
        break;
      case KEY_KEY_1:
        game_->CreateBox(btVector3(GetRandInt(10) - 5.0f, 7.0f, GetRandInt(10) - 5.0f), vector3df(GetRandInt(3) + 0.5f, GetRandInt(3) + 0.5f, GetRandInt(3) + 0.5f), 1.0f);
        break;
      case KEY_KEY_2:
        game_->CreateSphere(btVector3(GetRandInt(10) - 5.0f, 1.0f, GetRandInt(10) - 5.0f), GetRandInt(5) / 5.0f + 0.2f, 3.62f);
        break;
      case KEY_KEY_3:
        game_->CreateMesh(btVector3(GetRandInt(10) - 5.0f, 7.0f, GetRandInt(10) - 5.0f), dev_->getSceneManager()->getMesh("./missile.x"), 1.6f);
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
