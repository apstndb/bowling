//***************************************************************
// Bullet/irrlicht demo by Alan Witkowski
// http://www.cs.utah.edu/~witkowsk
// http://code.google.com/p/irrlamb/
//***************************************************************
#include <algorithm>
#include <boost/bind.hpp>
#include <btBulletCollisionCommon.h>
#include <btBulletDynamicsCommon.h>
#include <irrlicht.h>
#include "CubePrototype.h"
#include "EventReceiverClass.h"
#include "MeshPrototype.h"
#include "SpherePrototype.h"
#include "UpdateRender.h"
#include "AloneBowling.h"
#include "util.h"

using namespace irr;
using namespace core;
using namespace scene;
using namespace video;
using namespace io;
using namespace gui;

AloneBowling::AloneBowling()
  :Receiver(new EventReceiverClass(this, irrDevice)),
  irrDevice(createDevice(video::EDT_OPENGL, dimension2di(800, 600), 32, false, false, false, Receiver)),
  irrDriver(irrDevice->getVideoDriver()),
  irrScene(irrDevice->getSceneManager()),
  irrGUI(irrDevice->getGUIEnvironment()),
  irrTimer(irrDevice->getTimer()),
  Objects(new list<btRigidBody*>),
  CollisionConfiguration(new btDefaultCollisionConfiguration()),
  BroadPhase(new btAxisSweep3(btVector3(-1000, -1000, -1000), btVector3(1000, 1000, 1000))),
  Dispatcher(new btCollisionDispatcher(CollisionConfiguration)),
  Solver(new btSequentialImpulseConstraintSolver()),
  World(new btDiscreteDynamicsWorld(Dispatcher, BroadPhase, Solver, CollisionConfiguration))
{
}
void AloneBowling::run() {
  // Initialize irrlicht

  irrDevice->getCursorControl()->setVisible(0);

  // Initialize bullet

  // Add camera
  //ICameraSceneNode *Camera = irrScene->addCameraSceneNode();
  ICameraSceneNode *Camera = irrScene->addCameraSceneNodeFPS(0, 10.0f, 1.0f);
  Camera->setPosition(vector3df(0, 1.7f, 0));
  Camera->setTarget(vector3df(0, 0, 18.288));

  // Preload textures
  irrDriver->getTexture("ice0.jpg");
  irrDriver->getTexture("rust0.jpg");


  // Create text
  IGUISkin *Skin = irrGUI->getSkin();
  Skin->setColor(EGDC_BUTTON_TEXT, SColor(255, 255, 255, 255));
  irrGUI->addStaticText(L"Hit 1 to create a box\nHit 2 to create a sphere\nHit x to reset", rect<s32>(0, 0, 200, 100), false);

  // Create the initial scene
  irrScene->addLightSceneNode(0, core::vector3df(2, 5, -2), SColorf(4, 4, 4, 1));
  CreateStartScene();

  // Main loop
  u32 TimeStamp = irrTimer->getTime(), DeltaTime = 0;
  while(irrDevice->run()) {

    DeltaTime = irrTimer->getTime() - TimeStamp;
    TimeStamp = irrTimer->getTime();

    UpdatePhysics(DeltaTime);

    irrDriver->beginScene(true, true, SColor(255, 20, 0, 0));
    irrScene->drawAll();
    irrGUI->drawAll();
    irrDriver->endScene();
    //irrDevice->run();
  }
}

AloneBowling::~AloneBowling()
{
  ClearObjects();

  delete World;
  delete Solver;
  delete Dispatcher;
  delete BroadPhase;
  delete Objects;
  delete CollisionConfiguration;
  irrDevice->drop();
}

// Create a box rigid body
void AloneBowling::CreateBox(const btVector3 &TPosition, const vector3df &TScale, btScalar TMass) {
  CreateShape(CubePrototype(TScale), TPosition, TMass);
}
// Create a mesh rigid body
void AloneBowling::CreateMesh(const btVector3 &TPosition, IAnimatedMesh* mesh, btScalar TMass) 
{
  CreateShape(MeshPrototype(mesh), TPosition, TMass);
}
// Create a shape rigid body
void AloneBowling::CreateShape(const Prototype &prototype, const btVector3 &TPosition, btScalar TMass) {
	
	ISceneNode *Node = prototype.createSceneNode(irrScene);
	Node->setMaterialFlag(EMF_LIGHTING, 1);
	Node->setMaterialFlag(EMF_NORMALIZE_NORMALS, true);
	Node->setMaterialTexture(0, irrDriver->getTexture("rust0.jpg"));

	// Set the initial position of the object
	btTransform Transform;
	Transform.setIdentity();
	Transform.setOrigin(TPosition);

	btDefaultMotionState *MotionState = new btDefaultMotionState(Transform);

	// Create the shape
	btCollisionShape *Shape = prototype.createShape();

	// Add mass
	btVector3 LocalInertia;
	Shape->calculateLocalInertia(TMass, LocalInertia);

	// Create the rigid body object
	btRigidBody *RigidBody = new btRigidBody(TMass, MotionState, Shape, LocalInertia);

	// Store a pointer to the irrlicht node so we can update it later
	RigidBody->setUserPointer((void *)(Node));

	// Add it to the world
	World->addRigidBody(RigidBody);
	Objects->push_back(RigidBody);
}
// Create a sphere rigid body
void AloneBowling::CreateSphere(const btVector3 &TPosition, btScalar TRadius, btScalar TMass) 
{

  CreateShape(SpherePrototype(TRadius), TPosition, TMass);
}
void AloneBowling::CreateStartScene() {

	ClearObjects();
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
  std::for_each(vectors, vectors+10, bind(&AloneBowling::CreateMesh, this, _1, irrScene->getMesh("./missile.x"), 1.6f));
}

// Removes all objects from the world
void AloneBowling::ClearObjects() {

	for(list<btRigidBody *>::Iterator Iterator = Objects->begin(); Iterator != Objects->end(); ++Iterator) {
		btRigidBody *Object = *Iterator;

		// Delete irrlicht node
		ISceneNode *Node = static_cast<ISceneNode *>(Object->getUserPointer());
		Node->remove();

		// Remove the object from the world
		World->removeRigidBody(Object);

		// Free memory
		delete Object->getMotionState();
		delete Object->getCollisionShape();
		delete Object;
	}

	Objects->clear();
}
// Runs the physics simulation.
// - TDeltaTime tells the simulation how much time has passed since the last frame so the simulation can run independently of the frame rate.
void AloneBowling::UpdatePhysics(u32 TDeltaTime) {

	World->stepSimulation(TDeltaTime * 0.001f, 60);

	// Relay the object's orientation to irrlicht
	for(list<btRigidBody *>::Iterator Iterator = Objects->begin(); Iterator != Objects->end(); ++Iterator) {

		UpdateRender(*Iterator);
	}	
}

