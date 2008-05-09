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
  :running_(true),
  parent_(parent),
  receiver_(new EventReceiverClass(parent, irrDevice_)),
  irrDevice_(createDevice(video::EDT_OPENGL, core::dimension2di(800, 600), 32, false, false, false, receiver_)),
  irrDriver_(irrDevice_->getVideoDriver()),
  irrScene_(irrDevice_->getSceneManager()),
  irrGUI_(irrDevice_->getGUIEnvironment()),
  irrTimer_(irrDevice_->getTimer()),
  objects_(new core::list<btRigidBody*>),
  collisionConfiguration_(new btDefaultCollisionConfiguration()),
  broadPhase_(new btAxisSweep3(btVector3(-1000, -1000, -1000), btVector3(1000, 1000, 1000))),
  dispatcher_(new btCollisionDispatcher(collisionConfiguration_)),
  solver_(new btSequentialImpulseConstraintSolver()),
  world_(new btDiscreteDynamicsWorld(dispatcher_, broadPhase_, solver_, collisionConfiguration_))
{
}

// Runs the physics simulation.
// - TDeltaTime tells the simulation how much time has passed since the last frame so the simulation can run independently of the frame rate.
void AloneBowlingImpl::UpdatePhysics(u32 TDeltaTime) {

	world_->stepSimulation(TDeltaTime * 0.001f, 60);

	// Relay the object's orientation to irrlicht
	for(core::list<btRigidBody *>::Iterator iterator = objects_->begin(); iterator != objects_->end(); ++iterator) {

		UpdateRender(*iterator);
	}	
}
// Removes all objects from the world
void AloneBowlingImpl::ClearObjects() {

	for(core::list<btRigidBody *>::Iterator iterator = objects_->begin(); iterator != objects_->end(); ++iterator) {
		btRigidBody *object = *iterator;

		// Delete irrlicht node
		ISceneNode *node = static_cast<ISceneNode *>(object->getUserPointer());
		node->remove();

		// Remove the object from the world
		world_->removeRigidBody(object);

		// Free memory
		delete object->getMotionState();
		delete object->getCollisionShape();
		delete object;
	}

	objects_->clear();
}
// Create a shape rigid body
void AloneBowlingImpl::CreateShape(const Prototype &prototype, const btVector3 &TPosition, btScalar TMass) {
	
	ISceneNode *node = prototype.createSceneNode(irrScene_);
	node->setMaterialFlag(EMF_LIGHTING, 1);
	node->setMaterialFlag(EMF_NORMALIZE_NORMALS, true);
	node->setMaterialTexture(0, irrDriver_->getTexture("rust0.jpg"));

	// Set the initial position of the object
	btTransform transform;
	transform.setIdentity();
	transform.setOrigin(TPosition);

	btDefaultMotionState *motionState = new btDefaultMotionState(transform);

	// Create the shape
	btCollisionShape *shape = prototype.createShape();

	// Add mass
	btVector3 localInertia;
	shape->calculateLocalInertia(TMass, localInertia);

	// Create the rigid body object
	btRigidBody *rigidBody = new btRigidBody(TMass, motionState, shape, localInertia);

	// Store a pointer to the irrlicht node so we can update it later
	rigidBody->setUserPointer((void *)(node));

	// Add it to the world
	world_->addRigidBody(rigidBody);
	objects_->push_back(rigidBody);
}
AloneBowlingImpl::~AloneBowlingImpl()
{
  ClearObjects();
  delete world_;
  delete solver_;
  delete dispatcher_;
  delete broadPhase_;
  delete objects_;
  delete collisionConfiguration_;
  irrDevice_->drop();
}

