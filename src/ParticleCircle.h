//
//  Particle.h
//  stringToBinaryComposition
//
//  Created by JeongHoPark on 10.11.13.
//
//

#ifndef __stringToBinaryComposition__ParticleCircle__
#define __stringToBinaryComposition__ParticleCircle__

#include "ofMain.h"

class ParticleCircle {
    
    public :
    
    ParticleCircle(int _xPos, int _yPos);
    
    
    void setup();
    void update();
    void draw();
    
    float xMax, yMax;
    float xPos, yPos;
    int xDirection, yDirection;
    
    int xSpeed, ySpeed;
    
};

#endif /* defined(__stringToBinaryComposition__Particle__) */
