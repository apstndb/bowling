env = Environment( CPPDEFINES=Split('_UNICODE'), CPPPATH=Split('/usr/include/bullet /usr/include/irrlicht') )
Import( 'tools' )
Tool( tools )(env)
commonlibs = Split( 'Irrlicht png jpeg Xxf86vm GL bulletdynamics bulletcollision bulletmath' )
#ccflags = Split( '-Wall -g' )
ccflags = Split( '-fstrict-overflow -Wstrict-overflow=5 -Wsign-promo -Wstrict-null-sentinel -Wctor-dtor-privacy -Wsign-compare -Wredundant-decls -Werror -Wcast-align -Wdisabled-optimization -Wpointer-arith -Winit-self -Wunsafe-loop-optimizations -Wall -Wextra -Wformat=2 -Wcast-qual -Wcast-align -Wwrite-strings -Wconversion -Wpointer-arith -Wno-unused-parameter -std=c++98 -g' )
include = {}
include['crossmingw'] = Split( '')
include['gcc'] = Split( '' )
lib = {}
lib['crossmingw'] = commonlibs + Split( '')
lib['gcc'] = commonlibs + Split( '' )
#commonsrc = Split( 'util.cpp main.cpp CubePrototype.cpp UpdatePhysics.cpp ClearObjects.cpp MeshPrototype.cpp CreateMesh.cpp CreateShape.cpp SpherePrototype.cpp CreateStartScene.cpp CreateSphere.cpp EventReceiverClass.cpp GetRandInt.cpp QuaternionToEuler.cpp UpdateRender.cpp' )
commonsrc = Split( 'bowlingScore.cpp AloneBowlingImpl.cpp AloneBowling.cpp EventReceiverClass.cpp UpdateRender.cpp util.cpp main.cpp SpherePrototype.cpp MeshPrototype.cpp CubePrototype.cpp RoundTripAnimator.cpp' )
src = {}
src['crossmingw'] = commonsrc + Split('')
src['gcc'] = commonsrc + Split('')
ldflags = {}
ldflags['crossmingw'] = Split( '-Wl,--subsystem,windows' )
ldflags['gcc'] = Split( '' )
env . Program( 'bowling', src[tools], CCFLAGS=ccflags, LIBS=lib[tools], LINKFLAGS=ldflags[tools], INCLUDE=include[tools])
