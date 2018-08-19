#ifndef FireworksViewer_H_
#define FireworksViewer_H_

#include "AFramework.h"
#include "AFirework.h"

class AFireworksViewer : public AFramework
{
public:
    AFireworksViewer();
    virtual ~AFireworksViewer();
    
protected:

    void keyPress(unsigned char key, int specialKey, int x, int y);
    void setup();
    void draw();
    void update();

protected:
    std::vector<AFirework> _fireworks;
};

#endif
