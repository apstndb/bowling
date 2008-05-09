#ifndef ALONEBOWLING
#define ALONEBOWLING
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

class AloneBowling {
  private:
    AloneBowlingImpl* pimpl_;

  public:
    void CreateStartScene();
    void SetupPins();
    void CreateMesh(const btVector3 &TPosition, irr::scene::IAnimatedMesh* mesh, btScalar TMass);
    void CreateSphere(const btVector3 &TPosition, btScalar TRadius, btScalar TMass);
    void CreateBox(const btVector3 &TPosition, const irr::core::vector3df &TScale, btScalar TMass);
    AloneBowling();
    void run();
    void end();
    ~AloneBowling();
};
#endif
