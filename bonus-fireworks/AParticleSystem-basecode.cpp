#include "AParticleSystem.h"
#include <cstring>
#include <math.h>
#include <algorithm>
#include <boost/bind.hpp>


void AParticleSystem::update(double dt)
{
   // accumilate forces
   // you can hard-code external forces such as gravity and wind here
   AVector3 externalForces(100, 50, 40);

   for(int i = 0; i < _particles.size(); i++){
     _particles[i].derivative[POS] =  _particles[i].state[VEL];
     _particles[i].derivative[VEL] = (externalForces/_particles[i].mass);

     // update state
      _particles[i].state[POS] =   _particles[i].state[POS] + _particles[i].derivative[POS] * dt;
      _particles[i].state[VEL] =  _particles[i].state[VEL] + _particles[i].derivative[VEL] * dt;
     _particles[i].ttl = _particles[i].ttl - dt;
   }





   // If we were doing spring forces, we would need to compute the netForce
   // in its own loop before computing derivatives. However, for our simple
   // foreworks we can compute the derivative without accumilating forces first

   //computeDerivatives for all _particles
   //updateState for all _particles
}
