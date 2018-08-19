include_directories(
   ../../libsrc/animation 
   ../../libsrc/ui 
   ../3rdparty/AntTweakBar/include)

link_directories(
    ../lib 
    /usr/X11R6/lib 
    libsrc/animation 
    libsrc/ui 
    ../3rdparty/AntTweakBar/lib)

add_executable(bonus-fireworks 
    AParticleSystem-basecode.cpp 
    ARocket-basecode.cpp 
    ASpark-basecode.cpp 
    AFirework.cpp 
    AFireworksViewer.cpp 
    fireworksMain.cpp)

target_link_libraries(bonus-fireworks 
    ui 
    animationik
    animationfk
    animationbasic
    AntTweakBar 
    GLEW 
    glut 
    GL 
    GLU 
    X11)

