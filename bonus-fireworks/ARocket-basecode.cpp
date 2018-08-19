#include "ARocket.h"
#include <GL/glut.h>
#include <cmath>
#include <algorithm>
#include <boost/bind.hpp>

std::default_random_engine generator;
std::uniform_real_distribution<double> distribution(0,1);
auto mice = std::bind(distribution, generator);

void ARocket::init()
{
   _particles.clear();
   for(int i = 0; i < 10; i++){
     AParticle s_part = AParticle();
     s_part.state[POS] = AVector3(10,50,0) ;
     s_part.state[VEL] = AVector3(0,0,0);
     s_part.derivative[POS] = AVector3(0,0,0);
     s_part.derivative[VEL] = AVector3(0,0,0);
     s_part.mass = 5.0;
     s_part.ttl = 7.0;
     s_part.color = AVector3(mice(),mice(),mice());
     _particles.push_back(s_part);
   }


   // create a single particle to simulate the rocket
}

void ARocket::draw()
{
   const AParticle& p = getParticle(0);
   double factor = p.ttl;
   double scale = 1.0;
   double scale_1 = 5.0;
   scale = scale * (7.0 - factor) + scale_1 * (factor);
   double alpha = 5.0;
   double alpha_1 = 1.0;
   alpha = alpha * (7.0 - factor) + alpha_1 * (factor);

   // set color and transparency

   glColor4f(p.color[0], p.color[1], p.color[2], alpha);

   // draw cone rocket
   double dir = atan2(p.state[VEL][1], p.state[VEL][0]) * 180.0 / 3.14;
   glPushMatrix();
   glTranslatef(p.state[POS][0], p.state[POS][1], p.state[POS][2]);
   glScalef(scale, scale, scale);
   glRotatef(90 + dir, 0, 0, 1);
   glRotatef(90, 1, 0, 0);
   glutSolidCone(1.0, 3, 10, 10);
   glPopMatrix();
}
