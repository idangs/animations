#include <string>
#include "AFireworksViewer.h"
#include "AConstants.h"
#include "GL/glew.h"
#include "GL/glut.h"
#include <algorithm>
#include <AntTweakBar.h>

AFireworksViewer::AFireworksViewer() :
    AFramework(AFramework::Orthographic)
{
}

AFireworksViewer::~AFireworksViewer()
{
}


void AFireworksViewer::setup()
{
    for (int i = 0; i < 10; i++)
    {
        _fireworks.push_back(AFirework());
    }
}

void AFireworksViewer::update()
{
    for (unsigned int i = 0; i < _fireworks.size(); i++)
    {
        if (!_fireworks[i].isAlive()) continue;
        _fireworks[i].update(dt());
    }
}

void AFireworksViewer::keyPress(unsigned char key, int specialKey, int x, int y)
{
    if (key == ' ')
    {
        for (unsigned int i = 0; i < _fireworks.size(); i++)
        {
            if (!_fireworks[i].isAlive())
            {
               _fireworks[i].launch();
               break;
            }
        }
    }
}

void AFireworksViewer::draw()
{
    for (int i = 0; i < (int) _fireworks.size(); i++)
    {
        _fireworks[i].draw();
    }
}

