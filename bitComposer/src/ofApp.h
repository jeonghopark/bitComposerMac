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
    void exit();
    
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
    
    float width, height;
    
    void binaryScoreSetup(string _input);
    void binaryScoreDraw();
    
    vector<int> binaryScore;
    
    void textInputCharToNumber(char _input);
    int textInputcounter;
    
    void textInformation();
    bool bFullScreen;
    bool bTextInformation;
    
    bool bPlay;
    void mainScoreDraw(int _index);
    void mainScoreDataInput();
    void mainsScorePlay(int _index);
    vector<int> mainScoreData;
    int noteCounter;
    int tickCounter;
    vector<string> sBinaryScore;
    
    vector<int> evolutionFactor;
    vector<int> evolutionFactorDirection;
    vector<float> evolutionValue;

    int entropyParticleIndex;
    int entropyParticleNumberFactor;
    void entropyParticleMake(int _index);
    void entropyParticleUpdate();
    void entropyParticleDraw();
    int entropyParticleBoxHeight, entropyParticleBoxWidth;
    int oldEntropyparticleDrawIndex;
    bool bEntropyParticleView;

    float binaryScoreWidth;
    float binaryElementHeight;
    float binaryElementWidth;
    float binaryElementStep;
    
    int oldYHeight;
    
    ofxTonicSynth synth;
    ofxTonicSynth synthBass;
    void synthSetting();
    int scaleDegree;
    void trigger();
    void trigger(int _note);
    void triggerScale(int _note, int _scale);
    void audioRequested(float * output, int bufferSize, int nChannels);
        
    ofTrueTypeFont drawingFont;
    int textFontSize;
    float textSizeFactor;
    void textDrawSetup();
    void textDrawing();
    
    vector<ParticleCircle> particleCircle;
    
};
