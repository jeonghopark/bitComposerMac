//
//  Particle.cpp
//  stringToBinaryComposition
//
//  Created by JeongHoPark on 10.11.13.
//
//

#include "ParticleCircle.h"

ParticleCircle::ParticleCircle(int _xPos, int _yPos){

    xMax = _xPos;
    yMax = _yPos;
    
    xPos = ofRandom(xMax);
    yPos = ofRandom(yMax);
    
    xSpeed = ofRandom(3)+1;
    ySpeed = ofRandom(3)+1;
    xDirection = round(ofRandom(1));
    yDirection = round(ofRandom(1));
    
    if (xDirection==0) {
        xDirection = -1;
    }
    if (yDirection==0) {
        yDirection = -1;
    }

}

void ParticleCircle::setup() {

}


void ParticleCircle::update() {
    xPos = xPos + xSpeed * xDirection;
    yPos = yPos + ySpeed * yDirection;
        
    if (xPos>xMax) xDirection = -1;
    if (xPos<0) xDirection = 1;
    if (yPos>yMax) yDirection = -1;
    if (yPos<0) yDirection = 1;
 
}


void ParticleCircle::draw() {
    
    ofPushStyle();
    ofSetColor( ofColor::fromHsb( 0, 0, 0, 255) );

    ofEllipse( xPos, yPos, 2, 2 );
    ofPopStyle();
    
}