#ifndef AFireworks_H_
#define AFireworks_H_

#include "ARocket.h"
#include "ASpark.h"

// Implements a rocket and fireworks using particle systems organized with a FSM
class AFirework
{
public:
    AFirework();
    virtual ~AFirework();
    void update(double dt);
    void draw(); 
    void launch();
    bool isAlive() const;

protected:
    enum Mode {ROCKET, EXPLODE, DONE} _mode;
    ARocket _rocket;
    ASpark _sparks;
};

#endif
