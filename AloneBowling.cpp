#include "CubePrototype.h"
#include "MeshPrototype.h"
#include "SpherePrototype.h"
#include "AloneBowling.h"
#include "AloneBowlingImpl.h"
#include "util.h"
#include "constant.h"
#include <iostream>
#include <algorithm>
#include <boost/bind.hpp>
#include <boost/array.hpp>
#include <irrlicht.h>
#include <LinearMath/btVector3.h>
#include <btBulletDynamicsCommon.h>

using std::cout;
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
void AloneBowling::run() {
  // Initialize irrlicht

  //pimpl_->irrDevice_->getCursorControl()->setVisible(0);

  // Initialize bullet

  // Add camera
  //ICameraSceneNode *Camera = irrScene->addCameraSceneNode();
  ICameraSceneNode *camera[2] = {0,0};

  camera[0] = pimpl_->irrScene_->addCameraSceneNode(0, vector3df(0, Factor*0.5f, 0), vector3df(0, 0, DistanceToHeadPin));
  camera[0]->setFOV(PI/6.0f);

  camera[1] = pimpl_->irrScene_->addCameraSceneNode(0, vector3df(0, Factor*1, DistanceToHeadPin-PinsTriangleRadius), vector3df(0,0,DistanceToHeadPin+PinsTriangleRadius));
//  camera[1]->setPosition(vector3df(0, 2, DistanceToHeadPin));
//  camera[1]->setTarget(vector3df(0, 0, DistanceToHeadPin));
  camera[1]->setUpVector(vector3df(0,0,1));

  // Preload textures
  //irrDriver->getTexture("ice0.jpg");
  pimpl_->irrDriver_->getTexture("rust0.jpg");

  //IAnimatedMesh* arrowMesh = pimpl_->irrScene_->addArrowMesh("hoge");
  //IAnimatedMeshSceneNode* arrow = pimpl_->irrScene_->addAnimatedMeshSceneNode(arrowMesh);
  //ISceneNodeAnimator* anim = pimpl_->irrScene_->createFlyStraightAnimator(vector3df(LaneWidth*1.5,Factor*1,DistanceToHeadPin+PinsTriangleRadius), vector3df(-LaneWidth*1.5,Factor*1,DistanceToHeadPin+PinsTriangleRadius),10000, false);
  //arrow->addAnimator(anim);
  //arrow->setScale(vector3df(5.0,5.0,5.0));
  //arrow->setRotation(vector3df(180,0,0));
	//arrow->setMaterialFlag(EMF_LIGHTING, false);


  // Create text
  IGUISkin *skin = pimpl_->irrGUI_->getSkin();
  skin->setColor(EGDC_BUTTON_TEXT, SColor(255, 255, 255, 255));
  pimpl_->irrGUI_->addStaticText(L"Hit 1 to create a box\nHit 2 to create a sphere\nHit x to reset", rect<s32>(0, 0, 200, 100), false);

  // Create the initial scene
  pimpl_->irrScene_->addLightSceneNode(0, core::vector3df(20, 50, -5), SColorf(4, 4, 4, 1));
  CreateStartScene();

  //pimpl_->irrGUI_->getSkin()->setColor;

  for (s32 i=0; i<EGDC_COUNT ; ++i)
  {
    SColor col = pimpl_->irrGUI_->getSkin()->getColor((EGUI_DEFAULT_COLOR)i);
    col.setAlpha(255);
    pimpl_->irrGUI_->getSkin()->setColor((EGUI_DEFAULT_COLOR)i, col);
  }
  /*IGUIWindow* window(pimpl_->irrGUI_->addWindow(rect<s32>(ResX/2, ResY/2, ResX, ResY)));
  cout << window->getRelativePosition() << endl;
  cout << window->getAbsolutePosition() << endl;
  cout << window->getAbsoluteClippingRect() << endl;*/
  // Main loop
  u32 timeStamp = pimpl_->irrTimer_->getTime(), deltaTime = 0;
  while(pimpl_->irrDevice_->run() && pimpl_->running_) {

    deltaTime = pimpl_->irrTimer_->getTime() - timeStamp;
    timeStamp = pimpl_->irrTimer_->getTime();

    pimpl_->UpdatePhysics(deltaTime);
    pimpl_->irrDriver_->setViewPort(rect<s32>(0,0,ResX,ResY));
    pimpl_->irrDriver_->beginScene(true, true, SColor(255, 0, 0, 0));
    pimpl_->irrScene_->drawAll();

    pimpl_->irrGUI_->drawAll();

    pimpl_->irrScene_->setActiveCamera(camera[1]);
    pimpl_->irrDriver_->setViewPort(rect<s32>(ResX/2,0,ResX,ResY/2));
    //pimpl_->irrDriver_->setViewPort(window->getRelativePosition());
    //pimpl_->irrDriver_->beginScene(true, true, SColor(255, 0, 0, 0));
    pimpl_->irrScene_->drawAll();

    pimpl_->irrScene_->setActiveCamera(camera[0]);

    pimpl_->irrDriver_->endScene();

    //btVector3 lin_vel = pimpl_->ball_->getLinearVelocity();
    //std::wstring tmp = boost::str(boost::wformat(L"%1%") % countKnockedPins());
    //pimpl_->irrDevice_->setWindowCaption(tmp.c_str());
  }
}

AloneBowling::~AloneBowling()
{
  delete pimpl_;
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
  std::cout << pimpl_->ball_ << std::endl;
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
    if((*i)->getCenterOfMassPosition().y() < PinsHeight/2-0.1) ++result;
  }
  return result;
}
void AloneBowling::CreateStartScene()
{

	pimpl_->ClearObjects();
	CreateBox(btVector3(0.0f, -LaneThick/2, LaneLength/2-LaneMargin), vector3df(LaneWidth, LaneThick, LaneLength), 0.0f);
  SetupPins();
  //CreateBall(BallMass);
}
void AloneBowling::SetupPins()
{
  btVector3 vectors[10];
  for(std::size_t i = 0; i != 3; ++i) {
    vectors[i] = PinsTriangleRadius * getXZVector(i*360/3+180);
  }
  for(std::size_t i = 0; i != 6; ++i) {
    vectors[i+3] = PinsTriangleRadius/sqrt(3) * getXZVector(i*360/6+30);
  }
  vectors[9] = btVector3(0, 0, 0);

  for(std::size_t i = 0; i != 10; ++i) {
    vectors[i] += btVector3(0, PinsHeight/2, DistanceToHeadPin+PinsTriangleRadius);
    pimpl_->pins_->at(i) = CreateMesh(vectors[i], pimpl_->irrScene_->getMesh("./pin.x"), PinsMass);
  }
}

void AloneBowling::end()
{
  pimpl_->running_ = false;
}

