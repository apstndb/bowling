#include "Prototype.h"
#include "CreateBox.h"
#include <bullet/btBulletDynamicsCommon.h>
#include "main.h"

using namespace irr;
using namespace core;
using namespace scene;
using namespace video;

// Create a shape rigid body
void CreateShape(const Prototype &prototype, const btVector3 &TPosition, btScalar TMass) {
	
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
	Objects.push_back(RigidBody);
}
