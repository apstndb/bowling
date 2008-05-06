//***************************************************************
// Bullet/irrlicht demo by Alan Witkowski
// http://www.cs.utah.edu/~witkowsk
// http://code.google.com/p/irrlamb/
//***************************************************************
#include <irrlicht/irrlicht.h>
#include <bullet/btBulletCollisionCommon.h>
#include <bullet/btBulletDynamicsCommon.h>
#include "EventReceiverClass.h"
#include "CreateStartScene.h"
#include "ClearObjects.h"
#include "UpdatePhysics.h"

using namespace irr;
using namespace core;
using namespace scene;
using namespace video;
using namespace io;
using namespace gui;

// Globals
bool Done = false;
btDiscreteDynamicsWorld *World;
IrrlichtDevice *irrDevice;
IVideoDriver *irrDriver;
ISceneManager *irrScene;
IGUIEnvironment *irrGUI;
IFileSystem *irrFile;
ITimer *irrTimer;
ILogger *irrLog;
list<btRigidBody *> Objects;


int main() {

	// Initialize irrlicht
	EventReceiverClass Receiver;
	irrDevice = createDevice(video::EDT_OPENGL, dimension2di(800, 600), 32, false, false, false, &Receiver);
	irrGUI = irrDevice->getGUIEnvironment();
	irrTimer = irrDevice->getTimer();
	irrScene = irrDevice->getSceneManager();
	irrDriver = irrDevice->getVideoDriver();

	irrDevice->getCursorControl()->setVisible(0);

	// Initialize bullet
	btDefaultCollisionConfiguration *CollisionConfiguration = new btDefaultCollisionConfiguration();
	btBroadphaseInterface *BroadPhase = new btAxisSweep3(btVector3(-1000, -1000, -1000), btVector3(1000, 1000, 1000));
	btCollisionDispatcher *Dispatcher = new btCollisionDispatcher(CollisionConfiguration);
	btSequentialImpulseConstraintSolver *Solver = new btSequentialImpulseConstraintSolver();
	World = new btDiscreteDynamicsWorld(Dispatcher, BroadPhase, Solver, CollisionConfiguration);
	
	// Add camera
	ICameraSceneNode *Camera = irrScene->addCameraSceneNodeFPS(0, 100, 10);
	Camera->setPosition(vector3df(0, 5, -5));
	Camera->setTarget(vector3df(0, 0, 0));

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
	while(irrDevice->run() && !Done) {

		DeltaTime = irrTimer->getTime() - TimeStamp;
		TimeStamp = irrTimer->getTime();

		UpdatePhysics(DeltaTime);

		irrDriver->beginScene(true, true, SColor(255, 20, 0, 0));
		irrScene->drawAll();
		irrGUI->drawAll();
		irrDriver->endScene();
		//irrDevice->run();
	}

	ClearObjects();
	delete World;
	delete Solver;
	delete Dispatcher;
	delete BroadPhase;
	delete CollisionConfiguration;

	irrDevice->drop();

	return 0;
}

