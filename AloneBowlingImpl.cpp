#include "AloneBowlingImpl.h"
#include "EventReceiverClass.h"
#include "UpdateRender.h"
#include "Prototype.h"
#include <btBulletDynamicsCommon.h>
#include <irrlicht.h>
using namespace irr;
using namespace core;
using namespace scene;
using namespace video;
AloneBowlingImpl::AloneBowlingImpl(AloneBowling* parent)
  :running(true),
  parent_(parent),
  Receiver(new EventReceiverClass(parent, irrDevice)),
  irrDevice(createDevice(video::EDT_OPENGL, core::dimension2di(800, 600), 32, false, false, false, Receiver)),
  irrDriver(irrDevice->getVideoDriver()),
  irrScene(irrDevice->getSceneManager()),
  irrGUI(irrDevice->getGUIEnvironment()),
  irrTimer(irrDevice->getTimer()),
  Objects(new core::list<btRigidBody*>),
  CollisionConfiguration(new btDefaultCollisionConfiguration()),
  BroadPhase(new btAxisSweep3(btVector3(-1000, -1000, -1000), btVector3(1000, 1000, 1000))),
  Dispatcher(new btCollisionDispatcher(CollisionConfiguration)),
  Solver(new btSequentialImpulseConstraintSolver()),
  World(new btDiscreteDynamicsWorld(Dispatcher, BroadPhase, Solver, CollisionConfiguration))
{
}

// Runs the physics simulation.
// - TDeltaTime tells the simulation how much time has passed since the last frame so the simulation can run independently of the frame rate.
void AloneBowlingImpl::UpdatePhysics(u32 TDeltaTime) {

	World->stepSimulation(TDeltaTime * 0.001f, 60);

	// Relay the object's orientation to irrlicht
	for(core::list<btRigidBody *>::Iterator Iterator = Objects->begin(); Iterator != Objects->end(); ++Iterator) {

		UpdateRender(*Iterator);
	}	
}
// Removes all objects from the world
void AloneBowlingImpl::ClearObjects() {

	for(core::list<btRigidBody *>::Iterator Iterator = Objects->begin(); Iterator != Objects->end(); ++Iterator) {
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
// Create a shape rigid body
void AloneBowlingImpl::CreateShape(const Prototype &prototype, const btVector3 &TPosition, btScalar TMass) {
	
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
AloneBowlingImpl::~AloneBowlingImpl()
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

