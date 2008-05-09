#ifndef ALONEBOWLINGIMPL_H
#define ALONEBOWLINGIMPL_H

namespace irr {
  typedef unsigned int u32;
  class IrrlichtDevice;
  class ITimer;
  class ILogger;
  namespace video {
    class IVideoDriver;
  }
  namespace scene {
    class ISceneManager;
  }
  namespace gui {
    class IGUIEnvironment;
  }
  namespace io {
    class IFileSystem;
  }
  namespace core {
    template<class T> class list;
  }
}

class btDefaultCollisionConfiguration;
class btBroadphaseInterface;
class btCollisionDispatcher;
class btSequentialImpulseConstraintSolver;
class btDiscreteDynamicsWorld;
class btRigidBody;
class btVector3;
typedef float btScalar;

class EventReceiverClass;
class Prototype;

class AloneBowling;

class AloneBowlingImpl {
  public:
    bool running;
    AloneBowling* parent_;
    EventReceiverClass* Receiver;
    irr::IrrlichtDevice *irrDevice;
    irr::video::IVideoDriver *irrDriver;
    irr::scene::ISceneManager *irrScene;
    irr::gui::IGUIEnvironment *irrGUI;
    irr::ITimer *irrTimer;
    irr::io::IFileSystem *irrFile;
    irr::ILogger *irrLog;
    irr::core::list<btRigidBody*>* Objects;
    btDefaultCollisionConfiguration *CollisionConfiguration;
    btBroadphaseInterface *BroadPhase;
    btCollisionDispatcher *Dispatcher;
    btSequentialImpulseConstraintSolver *Solver;
    btDiscreteDynamicsWorld *World;
    void ClearObjects();
    void UpdatePhysics(irr::u32 TDeltaTime);
    void CreateShape(const Prototype &prototype, const btVector3 &TPosition, btScalar TMass);
    AloneBowlingImpl(AloneBowling*);
    ~AloneBowlingImpl();
};
#endif
