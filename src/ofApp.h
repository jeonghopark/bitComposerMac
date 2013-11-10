#pragma once

#include "ofMain.h"
#include "ofxTonic.h"
#include "ParticleCircle.h"

using namespace Tonic;

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
    
    void textInputField(char _input);
    int textInputcounter;
    
    
    void interfaceInformation();
    bool bFullScreen;
    
    bool bPlay;
    void scoreDraw(int _index);
    void scoreDataInput();
    void scorePlay(int _index);
    vector<int> scoreData;
    int noteCounter;
    int tickCounter;
    vector<string> sScoreZeroOne;
    
    vector<int> evolutionFactor;
    vector<int> evolutionFactorDirection;
    vector<float> evolutionValue;
    int entrophyTriLineXPos;
    int entrophyTriLineXPosDirection;
    void entropyTriDraw(int _xPos);
    
    void entropyParticleMake(int _index);
    void entropyParticleUpdate();
    void entropyParticleDraw();
    int entropyParticleHeight, entropyParticleWidth;
    int oldEntropyparticleDrawIndex;
    bool bEntropyParticleView;

    float _sizeX;
    int _rectHeight;
    int _rectWidth;
    int _xStep;
    
    int oldYHeight;
    
    
    ofxTonicSynth synth;
    void synthSetting();
    int scaleDegree;
    void trigger();
    void trigger(int _note);
    void triggerScale(int _note, int _scale);
    void audioRequested (float * output, int bufferSize, int nChannels);
    
    
    vector<int> allValue;
    void allDrawing();
    bool bAllDrawing;
    
    ofTrueTypeFont drawingFont;
    int textFontSize;
    float textSizeFactor;
    void textDrawSetup();
    void textDrawing();

    
    vector<ParticleCircle> particleCircle;
};
