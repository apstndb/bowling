#include "GetRandInt.h"
#include "main.h"
#include <irrlicht/irrlicht.h>
#include "EventReceiverClass.h"
#include "CreateStartScene.h"
#include "CreateSphere.h"
#include "CreateBox.h"
#include "CreateMesh.h"
#include "SetupPins.h"
#include <bullet/btBulletDynamicsCommon.h>
using namespace irr;
using namespace core;
bool EventReceiverClass::OnEvent(const irr::SEvent &TEvent) {

  if(TEvent.EventType == EET_KEY_INPUT_EVENT && !TEvent.KeyInput.PressedDown) {
    switch(TEvent.KeyInput.Key) {
      case KEY_ESCAPE:
        Done = true;
        break;
      case KEY_KEY_1:
        CreateBox(btVector3(GetRandInt(10) - 5.0f, 7.0f, GetRandInt(10) - 5.0f), vector3df(GetRandInt(3) + 0.5f, GetRandInt(3) + 0.5f, GetRandInt(3) + 0.5f), 1.0f);
        break;
      case KEY_KEY_2:
        //CreateSphere(btVector3(GetRandInt(10) - 5.0f, 7.0f, GetRandInt(10) - 5.0f), GetRandInt(5) / 5.0f + 0.2f, 1.0f);
        CreateSphere(btVector3(GetRandInt(10) - 5.0f, 1.0f, GetRandInt(10) - 5.0f), GetRandInt(5) / 5.0f + 0.2f, 3.62f);
        break;
      case KEY_KEY_3:
        //CreateMesh(btVector3(GetRandInt(10) - 5.0f, 7.0f, GetRandInt(10) - 5.0f), GetRandInt(5) / 5.0f + 0.2f, 1.0f);
        CreateMesh(btVector3(GetRandInt(10) - 5.0f, 7.0f, GetRandInt(10) - 5.0f), irrScene->getMesh("./missile.x"), 1.6f);
        break;
      case KEY_KEY_4:
        SetupPins();
        break;
      case KEY_KEY_X:
        CreateStartScene();
        break;
      default:
        return false;
        break;
    }

    return true;
  }

  return false;
}
