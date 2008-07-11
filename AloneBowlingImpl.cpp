#include "AloneBowlingImpl.h"
#include "EventReceiverClass.h"
#include "RoundTripAnimator.h"
#include "UpdateRender.h"
#include "Prototype.h"
#include "constant.h"
#include <btBulletDynamicsCommon.h>
#include <irrlicht.h>
#include <fstream>
#include <map>
#include <boost/array.hpp>
#include <boost/format.hpp>
#include <boost/shared_ptr.hpp>
using namespace irr;
using namespace core;
using namespace scene;
using namespace video;
using std::ifstream;
using boost::wformat;
  AloneBowlingImpl::AloneBowlingImpl(AloneBowling* parent)
:ball_(0),
  parent_(parent),
  timer_(0),
  receiver_(new EventReceiverClass(parent)),
  irrDevice_(createDevice(video::EDT_OPENGL, core::dimension2di(ResX, ResY), 32, FullScreen, false, false, receiver_)),
  irrDriver_(irrDevice_->getVideoDriver()),
  irrScene_(irrDevice_->getSceneManager()),
  irrGUI_(irrDevice_->getGUIEnvironment()),
  irrTimer_(irrDevice_->getTimer()),
  objects_(new core::list<btRigidBody*>),
  collisionConfiguration_(new btDefaultCollisionConfiguration()),
  broadPhase_(new btAxisSweep3(btVector3(-1000, -1000, -1000), btVector3(1000, 1000, 1000))),
  dispatcher_(new btCollisionDispatcher(collisionConfiguration_)),
  solver_(new btSequentialImpulseConstraintSolver()),
  world_(new btDiscreteDynamicsWorld(dispatcher_, broadPhase_, solver_, collisionConfiguration_)),
  pins_(new boost::array<btRigidBody*, 10>),
  arrow_(0),
  arrowMesh_(0),
  state_(GAME_LOGO)
{
  pins_->assign(0);
  world_->setGravity(btVector3(0,-Gravity,0));
}

void AloneBowlingImpl::UpdatePhysics(u32 TDeltaTime)
{

  world_->stepSimulation(TDeltaTime * 0.001f, 120);

  for(core::list<btRigidBody *>::Iterator iterator = objects_->begin(); iterator != objects_->end(); ++iterator) {

    UpdateRender(*iterator);
  }	
}
void AloneBowlingImpl::ClearObject(btRigidBody* object)
{
  ISceneNode *node = static_cast<ISceneNode *>(object->getUserPointer());
  node->remove();

  world_->removeRigidBody(object);

  delete object->getMotionState();
  delete object->getCollisionShape();
  delete object;
}
void AloneBowlingImpl::vanishObject(btRigidBody* object)
{
  ISceneNode *node = static_cast<ISceneNode *>(object->getUserPointer());
  node->setVisible(false);
  world_->removeRigidBody(object);
}
void AloneBowlingImpl::ClearObjects()
{

  for(core::list<btRigidBody *>::Iterator iterator = objects_->begin(); iterator != objects_->end(); ++iterator) {
    ClearObject(*iterator);
  }
  objects_->clear();
}
btRigidBody* AloneBowlingImpl::CreateShape(const Prototype &prototype, const btVector3 &TPosition, btScalar TMass)
{

  ISceneNode *node = prototype.createSceneNode(irrScene_);
  node->setMaterialFlag(EMF_LIGHTING, 1);
  node->setMaterialFlag(EMF_NORMALIZE_NORMALS, true);

  btTransform transform;
  transform.setIdentity();
  transform.setOrigin(TPosition);

  btDefaultMotionState *motionState = new btDefaultMotionState(transform);

  btCollisionShape *shape = prototype.createShape();

  btVector3 localInertia;
  shape->calculateLocalInertia(TMass, localInertia);

  btRigidBody::btRigidBodyConstructionInfo info(TMass, motionState, shape, localInertia);
  btRigidBody *rigidBody = new btRigidBody(info);

  rigidBody->setUserPointer((void *)(node));

  world_->addRigidBody(rigidBody);
  objects_->push_back(rigidBody);
  return rigidBody;
}
AloneBowlingImpl::~AloneBowlingImpl()
{
  ClearObjects();
  delete pins_;
  delete world_;
  delete solver_;
  delete dispatcher_;
  delete broadPhase_;
  delete objects_;
  delete collisionConfiguration_;
  irrDevice_->drop();
  delete receiver_;
}

void AloneBowlingImpl::setupArrow()
{
  if(arrow_) arrow_->remove();
  arrow_ = irrScene_->addAnimatedMeshSceneNode(arrowMesh_);
  irr::scene::ISceneNodeAnimator* anim(new RoundTripAnimator(irrScene_,
      vector3df( LaneWidth*1.5f,Factor*1,DistanceToHeadPin+PinsTriangleRadius*(1+sqrt(2.0f)/2)),
      vector3df(-LaneWidth*1.5f,Factor*1,DistanceToHeadPin+PinsTriangleRadius*(1+sqrt(2.0f)/2)),
      ArrowTimeForWay));
  arrow_->addAnimator(anim);
  anim->drop();
  arrow_->setScale(Factor*vector3df(0.5,0.5,0.5));
  arrow_->setRotation(vector3df(180,0,0));
  arrow_->setMaterialFlag(EMF_LIGHTING, false);
}
void AloneBowlingImpl::mapInitialize()
{

  typedef std::pair<wchar_t, irr::video::ITexture*> WIP;
  map_.insert(WIP(L' ', irrDriver_->getTexture("empty.png")));
  map_.insert(WIP(L'0', irrDriver_->getTexture("0.png")));
  map_.insert(WIP(L'1', irrDriver_->getTexture("1.png")));
  map_.insert(WIP(L'2', irrDriver_->getTexture("2.png")));
  map_.insert(WIP(L'3', irrDriver_->getTexture("3.png")));
  map_.insert(WIP(L'4', irrDriver_->getTexture("4.png")));
  map_.insert(WIP(L'5', irrDriver_->getTexture("5.png")));
  map_.insert(WIP(L'6', irrDriver_->getTexture("6.png")));
  map_.insert(WIP(L'7', irrDriver_->getTexture("7.png")));
  map_.insert(WIP(L'8', irrDriver_->getTexture("8.png")));
  map_.insert(WIP(L'9', irrDriver_->getTexture("9.png")));
  map_.insert(WIP(L'X', irrDriver_->getTexture("strike.png")));
  map_.insert(WIP(L'/', irrDriver_->getTexture("spare.png")));
  map_.insert(WIP(L'-', irrDriver_->getTexture("none.png")));
  map_.insert(WIP(L'G', irrDriver_->getTexture("G.png")));
}

void AloneBowlingImpl::printScore()
{
  std::wstring wstr;
  //if(wstr.empty()) {
    for(std::size_t i = 0; i < score_->numberOfFrames(); ++i) {
      wstr += str(wformat(L"% 4d") % (i+1));
    }
  //}
  printLine(wstr, 0);
  printLine(score_->str1(), 16);
  printLine(score_->str2(), 32);
}
void AloneBowlingImpl::printLine(const std::wstring& str, int y)
{
  for(std::size_t i = 0; i != str.size(); ++i) {
    std::map<wchar_t, irr::video::ITexture*>::iterator iter = map_.find(str[i]);
    if(iter != map_.end()) {
		irrGUI_->addImage(iter->second, core::position2d<s32>(irr::s32(i)*16,y));
    }
  }
}
