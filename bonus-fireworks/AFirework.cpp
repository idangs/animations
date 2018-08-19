#include "AFirework.h"
#include <GL/glut.h>
#include <cmath>

AFirework::AFirework() : _mode(DONE), _rocket(), _sparks() 
{
}

AFirework::~AFirework()
{

}

void AFirework::launch()
{
   _mode = ROCKET;
   _rocket.init();
}

void AFirework::update(double dt)
{
   dt = std::min(0.1, dt); // guard against very large dt, as when debugging
   switch (_mode)
   {
      case ROCKET:
      {
          _rocket.update(dt);
          if (!_rocket.isAlive())
          {
              _mode = EXPLODE;
              _sparks.init(_rocket);
          }
          break;
      }
      case EXPLODE:
      {
          _sparks.update(dt);
          if (!_sparks.isAlive())
          {
            _mode = DONE;
          }
          break;
      }
      case DONE: break;
   }
}

void AFirework::draw()
{
   switch (_mode)
   {
   case ROCKET: _rocket.draw(); break;
   case EXPLODE: _sparks.draw(); break;
   case DONE: break;
   }
}

bool AFirework::isAlive() const
{
   return _mode != DONE;
}
