//***************************************************************
// Bullet/irrlicht demo by Alan Witkowski
// http://www.cs.utah.edu/~witkowsk
// http://code.google.com/p/irrlamb/
//***************************************************************
#include "CubePrototype.h"
#include "MeshPrototype.h"
#include "SpherePrototype.h"
#include "AloneBowling.h"
#include "AloneBowlingImpl.h"
#include "util.h"
#include <algorithm>
#include <boost/bind.hpp>
#include <irrlicht.h>
#include <LinearMath/btVector3.h>

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

  pimpl_->irrDevice->getCursorControl()->setVisible(0);

  // Initialize bullet

  // Add camera
  //ICameraSceneNode *Camera = irrScene->addCameraSceneNode();
  ICameraSceneNode *Camera = pimpl_->irrScene->addCameraSceneNodeFPS(0, 10.0f, 1.0f);
  Camera->setPosition(vector3df(0, 1.7f, 0));
  Camera->setTarget(vector3df(0, 0, 18.288));

  // Preload textures
  //irrDriver->getTexture("ice0.jpg");
  pimpl_->irrDriver->getTexture("rust0.jpg");


  // Create text
  IGUISkin *Skin = pimpl_->irrGUI->getSkin();
  Skin->setColor(EGDC_BUTTON_TEXT, SColor(255, 255, 255, 255));
  pimpl_->irrGUI->addStaticText(L"Hit 1 to create a box\nHit 2 to create a sphere\nHit x to reset", rect<s32>(0, 0, 200, 100), false);

  // Create the initial scene
  pimpl_->irrScene->addLightSceneNode(0, core::vector3df(2, 5, -2), SColorf(4, 4, 4, 1));
  CreateStartScene();

  // Main loop
  u32 TimeStamp = pimpl_->irrTimer->getTime(), DeltaTime = 0;
  while(pimpl_->irrDevice->run() && pimpl_->running) {

    DeltaTime = pimpl_->irrTimer->getTime() - TimeStamp;
    TimeStamp = pimpl_->irrTimer->getTime();

    pimpl_->UpdatePhysics(DeltaTime);

    pimpl_->irrDriver->beginScene(true, true, SColor(255, 20, 0, 0));
    pimpl_->irrScene->drawAll();
    pimpl_->irrGUI->drawAll();
    pimpl_->irrDriver->endScene();
    //irrDevice->run();
  }
}

AloneBowling::~AloneBowling()
{
  delete pimpl_;
}

// Create a box rigid body
void AloneBowling::CreateBox(const btVector3 &TPosition, const vector3df &TScale, btScalar TMass) {
  pimpl_->CreateShape(CubePrototype(TScale), TPosition, TMass);
}
// Create a mesh rigid body
void AloneBowling::CreateMesh(const btVector3 &TPosition, IAnimatedMesh* mesh, btScalar TMass) 
{
  pimpl_->CreateShape(MeshPrototype(mesh), TPosition, TMass);
}
// Create a sphere rigid body
void AloneBowling::CreateSphere(const btVector3 &TPosition, btScalar TRadius, btScalar TMass) 
{

  pimpl_->CreateShape(SpherePrototype(TRadius), TPosition, TMass);
}
void AloneBowling::CreateStartScene() {

	pimpl_->ClearObjects();
	//CreateBox(btVector3(0.0f, 0.0f, 0.0f), vector3df(10.0f, 0.5f, 10.0f), 0.0f);
	CreateBox(btVector3(0.0f, -0.100f, 23.72f/2-3), vector3df(1.066f, 0.01f, 23.72f), 0.0f);
}
void AloneBowling::SetupPins()
{
  btVector3 vectors[10];
  for(size_t i = 0; i != 3; ++i) {
    vectors[i] = 0.4 * getXZVector(i*360/3+180, 0.200f);
  }
  for(size_t i = 0; i != 6; ++i) {
    vectors[i+3] = 0.4/sqrt(3) * getXZVector(i*360/6+30, 0.200f);
  }
  vectors[9] = btVector3(0, 0, 0);

  std::for_each(vectors, vectors+10, bind(&btVector3::operator+=, _1, btVector3(0, 0, 18.288-0.4)));
  std::for_each(vectors, vectors+10, bind(&AloneBowling::CreateMesh, this, _1, pimpl_->irrScene->getMesh("./missile.x"), 1.6f));
}

void AloneBowling::end()
{
  pimpl_->running = false;
}

