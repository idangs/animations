#ifndef ASPARK_H_
#define ASPARK_H_

#include "AParticleSystem.h"
class ARocket;
class ASpark : public AParticleSystem
{
public:
   ASpark() : AParticleSystem() {}
   virtual ~ASpark() {}
   void init(const ARocket& rocket, int numRings = 4, int numParticles = 10);
   void draw();
};

#endif
