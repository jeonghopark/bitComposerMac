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
    
    xSpeed = ofRandom(1.5)+0.1;
    ySpeed = ofRandom(1.5)+0.1;
    xDirection = round(ofRandom(1));
    yDirection = round(ofRandom(1));
    
    if (xDirection==0) {
        xDirection = -1;
    }
    if (yDirection==0) {
        yDirection = -1;
    }

    circleSize = 2;
}


ParticleCircle::~ParticleCircle(){
    
}


void ParticleCircle::setup() {

}


void ParticleCircle::update(int _xMax, int _yMax) {
    
    xMax = _xMax;
    yMax = _yMax;
    
    xPos = xPos + xSpeed * xDirection;
    yPos = yPos + ySpeed * yDirection;
        
    if (xPos>xMax-circleSize) xDirection = -1;
    if (xPos<circleSize) xDirection = 1;
    if (yPos>yMax-circleSize) yDirection = -1;
    if (yPos<circleSize) yDirection = 1;

    if (xPos>xMax) xPos = ofRandom( _xMax );

}


void ParticleCircle::draw() {
    
    ofPushStyle();
    ofSetColor( ofColor::fromHsb( 0, 0, 0, 170) );

    ofEllipse( xPos, yPos, circleSize, circleSize );
    ofPopStyle();
    
}