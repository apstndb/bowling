env = Environment( CPPDEFINES=Split('_UNICODE'), CPPPATH=Split('/usr/include/bullet /usr/include/irrlicht') )
Import( 'tools' )
Tool( tools )(env)
commonlibs = Split( 'Irrlicht png jpeg Xxf86vm GL bulletdynamics bulletcollision bulletmath' )
ccflags = Split( '-Wall' )
include = {}
include['crossmingw'] = Split( '')
include['gcc'] = Split( '' )
lib = {}
lib['crossmingw'] = commonlibs + Split( '')
lib['gcc'] = commonlibs + Split( '' )
commonsrc = Split( 'main.cpp CubePrototype.cpp UpdatePhysics.cpp ClearObjects.cpp CreateBox.cpp MeshPrototype.cpp CreateMesh.cpp CreateShape.cpp SpherePrototype.cpp CreateStartScene.cpp CreateSphere.cpp EventReceiverClass.cpp GetRandInt.cpp QuaternionToEuler.cpp UpdateRender.cpp' )
src = {}
src['crossmingw'] = commonsrc + Split('')
src['gcc'] = commonsrc + Split('')
ldflags = {}
ldflags['crossmingw'] = Split( '-Wl,--subsystem,windows' )
ldflags['gcc'] = Split( '' )
env . Program( 'mirage', src[tools], CCFLAGS=ccflags, LIBS=lib[tools], LINKFLAGS=ldflags[tools], INCLUDE=include[tools])
