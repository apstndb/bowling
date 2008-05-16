#ifndef ALONE_BOWLING_H
#define ALONE_BOWLING_H
class AloneBowlingImpl;
namespace irr {
  namespace scene {
    class IAnimatedMesh;
  }
  namespace core {
    template<class T> class vector3d;
    typedef vector3d<float> vector3df;
  }
}
typedef float btScalar;
class btVector3;
class btRigidBody;

class AloneBowling {
  private:
    AloneBowlingImpl* pimpl_;

  public:
    void CreateStartScene();
    void SetupPins();
    btRigidBody* CreateMesh(const btVector3 &TPosition, irr::scene::IAnimatedMesh* mesh, btScalar TMass);
    btRigidBody* CreateSphere(const btVector3 &TPosition, btScalar TRadius, btScalar TMass);
    btRigidBody* CreateBox(const btVector3 &TPosition, const irr::core::vector3df &TScale, btScalar TMass);
    btRigidBody* CreateBall(btScalar TMass);
    unsigned int countKnockedPins();
    void BallSetVelocity(const btVector3 &lin_vel, const btVector3 &ang_vel);
    AloneBowling();
    void run();
    void end();
    ~AloneBowling();
};
#endif
