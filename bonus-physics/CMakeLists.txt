include_directories(
    ../../libsrc/animation 
    ../../libsrc/ui 
    ../../3rdparty/ode-0.13/include
    /usr/include/eigen3
    /usr/local/include)

link_directories(
    /usr/local/lib 
    /usr/X11R6/lib 
    ../../3rdparty/ode-0.13/libs
    libsrc/animation 
    libsrc/ui )

add_executable(bonus-physics 
    APhysicsViewer-basecode.cpp)

target_link_libraries(bonus-physics 
    animationik
    animationfk
    animationbasic
    ui AntTweakBar GLEW glut GL GLU X11 ode pthread)
