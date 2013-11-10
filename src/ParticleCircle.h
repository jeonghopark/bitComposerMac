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
    ~ParticleCircle();
    
    void setup();
    void update(int _xMax, int _yMax);
    void draw();
    
    float xMax, yMax;
    float xPos, yPos;
    int xDirection, yDirection;
    
    float xSpeed, ySpeed;
    int circleSize;
};

#endif /* defined(__stringToBinaryComposition__Particle__) */
