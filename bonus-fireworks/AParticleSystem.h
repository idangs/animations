#ifndef PARTICLESYSTEM_H
#define PARTICLESYSTEM_H

#include <vector>
#include "AVector3.h"
#include "AParticle.h"

class AParticleSystem 
{
public:
   virtual ~AParticleSystem() {}
   virtual void update(double dt);
   
   bool isAlive() const;

   AParticle& getParticle(int idx) { return _particles[idx];  }
   const AParticle& getParticle(int idx) const { return _particles[idx]; }

protected:
   AParticleSystem() {}
   std::vector<AParticle> _particles;
};

inline bool AParticleSystem::isAlive() const
{
   for (unsigned int i = 0; i < _particles.size(); i++)
   {
      if (_particles[i].ttl > 0) return true;
   }
   return false;
}

#endif 
