#pragma once

#include "ofMain.h"

class ofApp : public ofBaseApp{
    
public:
    void setup();
    void update();
    void draw();
    
    void keyPressed(int key);
    void keyReleased(int key);
    void mouseMoved(int x, int y );
    void mouseDragged(int x, int y, int button);
    void mousePressed(int x, int y, int button);
    void mouseReleased(int x, int y, int button);
    void windowResized(int w, int h);
    void dragEvent(ofDragInfo dragInfo);
    void gotMessage(ofMessage msg);
    
    
    string textInput;
    
    void scoreZeroOneSetup(string _input);
    void scoreZeroOneDraw();
    
    vector<int> scoreZeroOne;
    
    void guideLine();
    
    void textInputField(int _input);
    int textInputcounter;
    
    
    void interfaceInformation();
    bool bFullScreen;
    
    bool bPlay;
    void scoreDraw();
    void scoreDataInput();
    vector<int> scoreData;
    
    float _sizeX;
    int _rectHeight;
    int _rectWidth;
    int _xStep;
    
    int oldYHeight;
    
    
};
