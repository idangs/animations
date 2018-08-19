#include "ASpark.h"
#include "ARocket.h"
#include <GL/glut.h>
#include <cmath>
#include <algorithm>
#include <boost/bind.hpp>


std::default_random_engine generator_2;
std::uniform_real_distribution<double> distribution_2(0, 2 * M_PI);
auto mice_2 = std::bind(distribution_2, generator_2);

std::default_random_engine generator_3;
std::uniform_real_distribution<double> distribution_3(0,1);
auto mice_3 = std::bind(distribution_3, generator_3);



void ASpark::init(const ARocket& rocket, int numRings, int numParticlesPerRing)
{
   _particles.clear();
   int radius = 5;
    for(int i = 0;i < numRings; i++){
      radius = 5;
     for(int j = 0; j < numParticlesPerRing; j++){
       AParticle s = AParticle();
       s.state[POS] = rocket.getParticle(i).state[POS];
       s.state[VEL] = AVector3(radius * cos(mice_2()), radius * sin(mice_2()), 0);
       std::cout << "theta = " << mice_2() << std::endl;
       s.derivative[POS] = rocket.getParticle(i).derivative[POS];
       s.derivative[VEL] = rocket.getParticle(i).derivative[VEL];;
       s.mass = 5.0;
       s.ttl = 7.0;
       radius = radius + 5;
       s.color = AVector3(mice_3(),mice_3(),mice_3());
       _particles.push_back(s);
     }
   }
}

void ASpark::draw()
{
  //  double scale = 1;
  //  const AParticle& p = getParticle(0);

  //  std::default_random_engine generator;
  //  std::uniform_real_distribution<double> distribution(0,1);
  //  auto mice = std::bind(distribution, generator);
  //  auto dice = std::bind(distribution, generator);
  //  AVector3 color(1,0,0);


   for (unsigned int i =0; i < _particles.size(); i++)
   {
      const AParticle& p = _particles[i];
      double factor = p.ttl;
      double scale = 1.0;
      double scale_1 = 4.0;
      scale = scale * (7.0 - factor) + scale_1 * (factor);
      double alpha = 1.0;
      double alpha_1 = 3.0;
      alpha = alpha * (7.0 - factor) + alpha_1 * (factor);

      if (p.ttl < 0) continue;

      glColor4f(p.color[0], p.color[1], p.color[2], alpha);
      glPushMatrix();
      glTranslatef(p.state[POS][0], p.state[POS][1], p.state[POS][2]);
      glScalef(scale, scale, scale);
      glutSolidSphere(1.0, 10, 10);
      glPopMatrix();

   }
}
