//#include <btBulletDynamicsCommon.h>
#include <LinearMath/btPoint3.h>
//#include <irrlicht.h>
namespace irr {
  typedef unsigned int u32;
  class IrrlichtDevice;
  class ITimer;
  class ILogger;
  namespace video {
    class IVideoDriver;
  }
  namespace scene {

    class IAnimatedMesh;
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
    template<class T> class vector3d;
    typedef vector3d<float> vector3df;
  }
}
class btDefaultCollisionConfiguration;
class btBroadphaseInterface;
class btCollisionDispatcher;
class btSequentialImpulseConstraintSolver;
class btDiscreteDynamicsWorld;
class btRigidBody;
class EventReceiverClass;
class Prototype;
class AloneBowling {
  private:
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
  public:
  void CreateStartScene();
  void SetupPins();
  void CreateMesh(const btVector3 &TPosition, irr::scene::IAnimatedMesh* mesh, btScalar TMass);
  void CreateSphere(const btVector3 &TPosition, btScalar TRadius, btScalar TMass);
  void CreateBox(const btVector3 &TPosition, const irr::core::vector3df &TScale, btScalar TMass);
  AloneBowling();
  void run();
  ~AloneBowling();
};
