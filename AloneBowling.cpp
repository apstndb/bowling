#include "CubePrototype.h"
#include "MeshPrototype.h"
#include "SpherePrototype.h"
#include "AloneBowling.h"
#include "AloneBowlingImpl.h"
#include "util.h"
#include "constant.h"
#include "bowlingScore.h"
#include <iostream>
#include <algorithm>
#include <boost/bind.hpp>
#include <boost/array.hpp>
#include <boost/format.hpp>
#include <irrlicht.h>
#include <LinearMath/btVector3.h>
#include <btBulletDynamicsCommon.h>

using std::wcout;
using std::endl;
using namespace irr;
using namespace core;
using namespace scene;
using namespace video;
using namespace io;
using namespace gui;

  AloneBowling::AloneBowling()
:pimpl_(new AloneBowlingImpl(this))
{
}

void AloneBowling::run()
{
  // Initialize irrlicht

  //pimpl_->irrDevice_->getCursorControl()->setVisible(0);
  pimpl_->irrDevice_->getFileSystem()->addZipFileArchive("files.zip");
  pimpl_->arrowMesh_ = pimpl_->irrScene_->addArrowMesh("hoge");
  pimpl_->mapInitialize();
  setState(GAME_LOGO);

  // Initialize bullet

  // Add camera
  ICameraSceneNode *camera[3] = {0,0,0};

  camera[0] = pimpl_->irrScene_->addCameraSceneNode(0, vector3df(0, Factor*0.5f, Factor*-0), vector3df(0, 0, DistanceToHeadPin));
  camera[0]->setFOV(PI/6.0f);
  camera[0]->setIsOrthogonal(true);

  camera[1] = pimpl_->irrScene_->addCameraSceneNode(0,
      vector3df(0, Factor*3, DistanceToHeadPin+PinsTriangleRadius),
      vector3df(0,0,DistanceToHeadPin+PinsTriangleRadius));
  camera[1]->setUpVector(vector3df(0,0,1));

  camera[2] = pimpl_->irrScene_->addCameraSceneNode(0,
      vector3df(0, Factor*.6f, DistanceToHeadPin-PinsTriangleRadius/2),
      vector3df(0,0,DistanceToHeadPin+PinsTriangleRadius));
  camera[2]->setUpVector(vector3df(0,0,1));

  // Preload textures

  // Create text
  IGUISkin *skin = pimpl_->irrGUI_->getSkin();
  skin->setColor(EGDC_BUTTON_TEXT, SColor(255, 255, 255, 255));

  // Create the initial scene
  pimpl_->irrScene_->addLightSceneNode(0, core::vector3df(20, 50, -5), SColorf(4, 4, 4, 1));



  for (s32 i=0; i<EGDC_COUNT ; ++i)
  {
    SColor col = pimpl_->irrGUI_->getSkin()->getColor((EGUI_DEFAULT_COLOR)i);
    col.setAlpha(255);
    pimpl_->irrGUI_->getSkin()->setColor((EGUI_DEFAULT_COLOR)i, col);
  }

  // Main loop
  u32 timeStamp = pimpl_->irrTimer_->getTime(), deltaTime = 0;
  while(pimpl_->irrDevice_->run() && getState() != GAME_END) {
    deltaTime = pimpl_->irrTimer_->getTime() - timeStamp;
    timeStamp = pimpl_->irrTimer_->getTime();
    GameState state = getState();

    switch(state) {
      case GAME_LOGO:
        if(timeStamp > LogoTime) setState(GAME_TITLE);
        break;
      case GAME_TITLE:
        if(timeStamp > TitleTime) setState(GAME_WAIT);
        break;
      case GAME_RUNNING:
        pimpl_->tickTimer(deltaTime);
        if(pimpl_->timeUp()) {
          SEvent event;
          event.EventType = EET_USER_EVENT;
          pimpl_->irrDevice_->postEventFromUser(event);
        }
        break;
      default:
        break;
    }


    pimpl_->UpdatePhysics(deltaTime);

    pimpl_->irrDriver_->setViewPort(rect<s32>(0,0,ResX,ResY));
    pimpl_->irrDriver_->beginScene(true, true, (state==GAME_LOGO||state==GAME_TITLE)?SColor(255,255,255,255):SColor(255, 0, 0, 0));
    pimpl_->irrScene_->drawAll();

    pimpl_->irrGUI_->drawAll();

    pimpl_->irrScene_->setActiveCamera(camera[2]);
//    pimpl_->irrDriver_->setViewPort(rect<s32>(2*ResX/3,0+32,ResX,ResY/3+32));
	pimpl_->irrDriver_->setViewPort(rect<s32>(0,0+48,ResX/3,ResY/3+48));
    pimpl_->irrScene_->drawAll();

    //pimpl_->irrScene_->setActiveCamera(camera[2]);
    //pimpl_->irrDriver_->setViewPort(rect<s32>(0,0,ResX/3,ResY/3));
    //pimpl_->irrScene_->drawAll();

    pimpl_->irrScene_->setActiveCamera(camera[0]);

    pimpl_->irrDriver_->endScene();
  }
}

AloneBowling::~AloneBowling()
{
}

// Create a box rigid body
btRigidBody* AloneBowling::CreateBox(const btVector3 &TPosition, const vector3df &TScale, btScalar TMass) {
  btRigidBody* result = pimpl_->CreateShape(CubePrototype(TScale), TPosition, TMass);
  static_cast<ISceneNode*>(result->getUserPointer())->setMaterialTexture(0, pimpl_->irrDriver_->getTexture("wood.tga"));
  return result;
}
// Create a mesh rigid body
btRigidBody* AloneBowling::CreateMesh(const btVector3 &TPosition, IAnimatedMesh* mesh, btScalar TMass) 
{
  return pimpl_->CreateShape(MeshPrototype(mesh), TPosition, TMass);
}

// Create a sphere rigid body
btRigidBody* AloneBowling::CreateBall(btScalar TMass) 
{
  return pimpl_->ball_ = pimpl_->CreateShape(SpherePrototype(BallRadius), btVector3(0,BallRadius,0), TMass);
}

void AloneBowling::BallSetVelocity(const btVector3 &lin_vel, const btVector3 &ang_vel)
{
  CreateBall(BallMass);
  pimpl_->ball_->setLinearVelocity(lin_vel);
  pimpl_->ball_->setAngularVelocity(ang_vel);
}

btRigidBody* AloneBowling::CreateSphere(const btVector3 &TPosition, btScalar TRadius, btScalar TMass) 
{

  return pimpl_->CreateShape(SpherePrototype(TRadius), TPosition, TMass);
}

unsigned int AloneBowling::countKnockedPins()
{
  boost::array<btRigidBody*, 10>& pins = *pimpl_->pins_;
  unsigned int result(0);
  boost::array<btRigidBody*, 10>::iterator end(pins.end());
  for(boost::array<btRigidBody*, 10>::iterator i = pins.begin();
      i != end; ++i) {
    if(*i && (*i)->getCenterOfMassPosition().y() < PinsHeight/2-0.1) {
      pimpl_->vanishObject(*i);
      *i = 0;
      ++result;
    }
  }
  return result;
}

void AloneBowling::misc()
{
  unsigned int temp = pimpl_->score_->getCurrentFrame();
  unsigned int knockedPins = countKnockedPins();
  if(pimpl_->score_->put(knockedPins)) {
    setState(GAME_RESULT);
  }
  else {
    if(temp != pimpl_->score_->getCurrentFrame() || (temp == 10 && !pimpl_->score_->anyPinIsStanding())) {
      resetScene();
    }
    else {
      setState(GAME_WAIT);
    }
  }
  pimpl_->printScore();
}
void AloneBowling::CreateStartScene()
{
  pimpl_->ClearObjects();
  CreateBox(btVector3(0.0f, -LaneThick/2, LaneLength/2-LaneMargin), vector3df(LaneWidth, LaneThick, LaneLength), 0.0f);
  SetupPins();
}

/*
void AloneBowling::cleanKnockedPins()
{

}
*/
void AloneBowling::resetScene()
{
  CreateStartScene();
  setState(GAME_WAIT);
}
void AloneBowling::SetupPins()
{
  btVector3 vectors[10];
  for(std::size_t i = 0; i != 3; ++i) {
    vectors[i] = PinsTriangleRadius * getXZVector(btRadians(btScalar(i)*360/3+180));
  }
  for(std::size_t i = 0; i != 6; ++i) {
    vectors[i+3] = PinsTriangleRadius/sqrt(3.0f) * getXZVector(btRadians(btScalar(i)*360/6+30));
  }
  vectors[9] = btVector3(0, 0, 0);

  for(std::size_t i = 0; i != 10; ++i) {
    vectors[i] += btVector3(0, PinsHeight/2, DistanceToHeadPin+PinsTriangleRadius);
    pimpl_->pins_->at(i) = CreateMesh(vectors[i], pimpl_->irrScene_->getMesh("pin.x"), PinsMass);
  }
}

void AloneBowling::setState(GameState state)
{
  pimpl_->irrGUI_->clear();
  switch(state) {
  case GAME_LOGO:
    pimpl_->irrGUI_->addImage(pimpl_->irrDriver_->getTexture("sofmelogo.tga"), position2d<s32>(ResX/2-1024/2,ResY/2-128/2));
	break;
  case GAME_TITLE:
    pimpl_->irrGUI_->addImage(pimpl_->irrDriver_->getTexture("titlelogo.tga"), position2d<s32>(ResX/2-640/2,ResY/2-480/2));
    break;
  case GAME_RUNNING:
    if(getState() == GAME_WAIT) pimpl_->setTimer(TimeUp);
	pimpl_->printScore();
	break;
  case GAME_WAIT:
    if(getState() == GAME_TITLE) {
      CreateStartScene();
      pimpl_->printScore();
	}
    pimpl_->setupArrow();
	break;
  case GAME_RESULT:
    pimpl_->irrGUI_->addImage(pimpl_->irrDriver_->getTexture("sign.tga"), position2d<s32>(ResX/2-200/2,ResY/2-25/2));
    break;
  default:
    break;
  }
  pimpl_->state_ = state;
}


float AloneBowling::getArrowRad()
{
  if(!pimpl_->arrow_) throw 1;
  vector3df pos = pimpl_->arrow_->getPosition();
  return atan2f(pos.X, pos.Z);
}

GameState AloneBowling::getState()
{
  return pimpl_->state_;
}
void AloneBowling::stopArrow()
{
  pimpl_->arrow_->removeAnimators();
  irr::scene::ISceneNodeAnimator* anim = pimpl_->irrScene_->createDeleteAnimator(1000);
  pimpl_->arrow_->addAnimator(anim);
  anim->drop();
  pimpl_->arrow_ = 0;
}
