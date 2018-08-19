#ifndef ARocket_H_
#define ARocket_H_

#include "AParticleSystem.h"

class ARocket : public AParticleSystem
{
public:
   ARocket() {} 
   virtual ~ARocket() {}
   void init();
   void draw();
};

#endif
