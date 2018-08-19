
#ifndef PARTICLE_H_
#define PARTICLE_H_

enum {POS, VEL};
class AParticle
{
public:
   AVector3 state[2];
   AVector3 derivative[2];
   double mass;
   double ttl;
   double scale;
   double alpha;
   AVector3 color;
};

#endif
