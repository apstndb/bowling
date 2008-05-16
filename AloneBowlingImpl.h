#ifndef ALONE_BOWLING_IMPL_H
#define ALONE_BOWLING_IMPL_H

namespace std {
  typedef unsigned int size_t;
}

namespace boost {
  template<class T, std::size_t N> class array;
}
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
    btRigidBody* ball_;
    bool running_;
    AloneBowling* parent_;
    EventReceiverClass* receiver_;
    irr::IrrlichtDevice *irrDevice_;
    irr::video::IVideoDriver *irrDriver_;
    irr::scene::ISceneManager *irrScene_;
    irr::gui::IGUIEnvironment *irrGUI_;
    irr::ITimer *irrTimer_;
    irr::io::IFileSystem *irrFile_;
    irr::ILogger *irrLog_;
    irr::core::list<btRigidBody*>* objects_;
    btDefaultCollisionConfiguration *collisionConfiguration_;
    btBroadphaseInterface *broadPhase_;
    btCollisionDispatcher *dispatcher_;
    btSequentialImpulseConstraintSolver *solver_;
    btDiscreteDynamicsWorld *world_;
    boost::array<btRigidBody*, 10>* pins_;
    void ClearObjects();
    void UpdatePhysics(irr::u32 TDeltaTime);
    btRigidBody*  CreateShape(const Prototype &prototype, const btVector3 &TPosition, btScalar TMass);
    AloneBowlingImpl(AloneBowling*);
    ~AloneBowlingImpl();
};
#endif
