#ifndef ALONE_BOWLING_H
#define ALONE_BOWLING_H
#include <boost/shared_ptr.hpp>
#include "GameState.h"
class AloneBowlingImpl;
namespace irr {
  typedef unsigned int u32;
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
    boost::shared_ptr<AloneBowlingImpl> pimpl_;

  public:
    void CreateStartScene();
    void resetScene();
    void SetupPins();
    btRigidBody* CreateMesh(const btVector3 &TPosition, irr::scene::IAnimatedMesh* mesh, btScalar TMass);
    btRigidBody* CreateSphere(const btVector3 &TPosition, btScalar TRadius, btScalar TMass);
    btRigidBody* CreateBox(const btVector3 &TPosition, const irr::core::vector3df &TScale, btScalar TMass);
    btRigidBody* CreateBall(btScalar TMass);
    float getArrowRad();
    unsigned int countKnockedPins();
    void BallSetVelocity(const btVector3 &lin_vel, const btVector3 &ang_vel);
    AloneBowling();
    void stopArrow();
    void run();
    void misc();
    void start(unsigned int n);
    bool timeUp();
    void setState(GameState state);
    GameState getState();
    ~AloneBowling();
};
#endif
