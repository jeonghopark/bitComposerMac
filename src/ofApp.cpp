#include "ofApp.h"


#define NUMBER_OF_KEYS 10


//--------------------------------------------------------------
void ofApp::setup(){
    
    ofSetFrameRate(60);
    ofBackground( ofColor::fromHsb(0, 0, 255) );
    
    ofSoundStreamSetup(2, 0, this, 44100, 256, 4);
    
    textInput = "";
    scoreZeroOneSetup(textInput);
    
    textInputcounter = 0;
    noteCounter = 0;
    
    synthSetting();
}

//--------------------------------------------------------------
void ofApp::update(){
    
    if (bPlay) {
        if (ofGetFrameNum()%3==0) {
            tickCounter++;
            if ( (tickCounter%8==0)||(tickCounter%6==0) ) {
                scorePlay(noteCounter);
                noteCounter++;
                if (noteCounter>scoreZeroOne.size()-1) {
                    noteCounter = 0;
                }
            }
        }
    }
    
}

//--------------------------------------------------------------
void ofApp::draw(){
    
    //    guideLine();
    scoreZeroOneDraw();
    
    interfaceInformation();
    
    if (bPlay) {
        scoreDraw();
    }
    
}

void ofApp::scoreZeroOneSetup(string _sInput){
    
    textInput = _sInput;
    
    string _scoreZeroOne = ofToBinary(textInput);
    
    for (int i=0; i<_scoreZeroOne.size(); i++) {
        scoreZeroOne.push_back( _scoreZeroOne.at(i)-48 );
    }
    
    _rectHeight = ofGetHeight()*0.00912;
    _rectWidth = ofGetWidth()*0.00390;
    _xStep = ofGetWidth()*0.00488;
    
    
    
}


void ofApp::scoreZeroOneDraw(){
    
    
    _sizeX = ( (_rectWidth * scoreZeroOne.size()) + ((_xStep-_rectWidth) * (scoreZeroOne.size()-1)) );
    
    
    ofPushMatrix();
    ofTranslate( ofGetWidth()/2-_sizeX/2, ofGetHeight()/2 );
    ofPushStyle();
    ofSetColor( ofColor::fromHsb( 0, 0, 0, 255) );
    
    for (int i=0; i<scoreZeroOne.size(); i++) {
        int _yHeight = scoreZeroOne[i];
        ofPushMatrix();
        ofTranslate(i*_xStep, 0);
        ofRect( 0, 0, _rectWidth, -_yHeight*_rectHeight+1 );
        ofPopMatrix();
    }
    
    ofPopStyle();
    ofPopMatrix();
    
}


void ofApp::scoreDraw(){
    
    ofPushMatrix();
    ofTranslate( ofGetWidth()/2-_sizeX/2, ofGetHeight()/4 );
    ofPushStyle();
    ofSetColor( ofColor::fromHsb( 0, 0, 0, 255) );
    
    for (int i=0; i<scoreData.size(); i++) {
        int _yHeight = scoreData[i];
        ofPushMatrix();
        ofTranslate(i*_xStep, 0);
        ofRect( 0, 0, _rectWidth, -_yHeight*_rectHeight+1 );
        
        ofPopMatrix();
    }
    
    ofPopStyle();
    ofPopMatrix();
    
}

void ofApp::scoreDataInput(){
    scoreData.clear();
    
    for (int i=0; i<scoreZeroOne.size(); i++) {
        
        int _yHeight = scoreZeroOne[i];
        
        if (_yHeight==0) {
            _yHeight = -1;
        }
        else {
            _yHeight = 1;
        }
        
        _yHeight = oldYHeight+_yHeight;
        
        scoreData.push_back(-_yHeight);
        oldYHeight = _yHeight;
    }
    
}

void ofApp::scorePlay(int _index){
    
    if (scoreData.size()>0) {
        int newScaleDegree = scoreData[_index]*3+40;
        if(newScaleDegree != scaleDegree ){
            scaleDegree = newScaleDegree;
            trigger(scaleDegree);
        }else{
            scaleDegree = newScaleDegree;
        }
    }
    //
    //    scaleDegree = scoreData[_index]+60;
    //    trigger();
    //
    
    cout << _index << " : " << scaleDegree << endl;
    
}




void ofApp::guideLine(){
    
    ofPushMatrix();
    ofPushStyle();
    
    ofSetColor( ofColor::fromHsb( 90, 125, 255, 255) );
    
    int _size = 20;
    int step = 80;
    
    for (int i=0; i<=ofGetWidth()/step; i++) {
        for (int j=0; j<=ofGetHeight()/step; j++) {
            ofPushMatrix();
            ofTranslate(i*step, j*step);
            ofLine( 0, -_size/2, 0, _size/2 );
            ofLine( -_size/2, 0, _size/2, 0 );
            ofPopMatrix();
        }
    }
    
    ofPopStyle();
    ofPopMatrix();
    
}


void ofApp::textInputField(int _input){
    
    string _scoreZeroOne = ofToBinary( ofToString(_input) );
    
    for (int i=0; i<_scoreZeroOne.size(); i++) {
        scoreZeroOne.push_back(  _scoreZeroOne.at(i)-48 );
    }
    
}

void ofApp::interfaceInformation(){
    
    ofPushStyle();
    ofSetColor( ofColor::fromHsb( 0, 0, 0, 255) );
    
    ofDrawBitmapString("FullScreen : Shift+F", 10, ofGetHeight()-40);
    ofDrawBitmapString("delete : del", 10, ofGetHeight()-25);
    ofDrawBitmapString("Play : space bar", 10, ofGetHeight()-10);
    ofPopStyle();
    
}

void ofApp::synthSetting(){
    
    ControlGenerator midiNote = synth.addParameter("midiNumber");
    ControlGenerator noteFreq =  ControlMidiToFreq().input(midiNote);
    Generator tone = RectWave().freq( noteFreq );
    tone = LPF12().input(tone).Q(10).cutoff((noteFreq * 20) + SineWave().freq(3) * 0.5 * noteFreq);
    ControlGenerator envelopeTrigger = synth.addParameter("trigger");
    Generator toneWithEnvelope = tone * ADSR().attack(0.01).decay(1.5).sustain(0).release(0).trigger(envelopeTrigger).legato(true);
    Generator toneWithDelay = StereoDelay(0.5, 0.75).input(toneWithEnvelope).wetLevel(0.1).feedback(0.2);
    synth.setOutputGen( toneWithDelay );
    
}

//--------------------------------------------------------------
void ofApp::trigger(){
    static int twoOctavePentatonicScale[10] = {0, 2, 4, 7, 9, 12, 14, 16, 19, 21};
    int degreeToTrigger = floor(ofClamp(scaleDegree, 0, 9));
	
    // set a parameter that we created when we defined the synth
    synth.setParameter("midiNumber", 44 + twoOctavePentatonicScale[degreeToTrigger]);
    
    // simply setting the value of a parameter causes that parameter to send a "trigger" message to any
    // using them as triggers
    synth.setParameter("trigger", 1);
}

void ofApp::trigger(int _note){
    static int twoOctavePentatonicScale[10] = {0, 2, 4, 7, 9, 12, 14, 16, 19, 21};
    int degreeToTrigger = floor(ofClamp(scaleDegree, 0, 9));
	
    // set a parameter that we created when we defined the synth
    synth.setParameter("midiNumber", _note);
    
    // simply setting the value of a parameter causes that parameter to send a "trigger" message to any
    // using them as triggers
    synth.setParameter("trigger", 1);
}


//--------------------------------------------------------------
void ofApp::setScaleDegreeBasedOnMouseX(){
    int newScaleDegree = ofGetMouseX() * NUMBER_OF_KEYS / ofGetWindowWidth();
    if(ofGetMousePressed() && ( newScaleDegree != scaleDegree )){
        scaleDegree = newScaleDegree;
        trigger();
    }else{
        scaleDegree = newScaleDegree;
    }
}



//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
    
    if ( (key<=122)&&(key>=97) ) {
        textInputcounter++;
        if (textInputcounter<12) {
            textInputField(key-48);
        } else {
            //            scoreZeroOne.clear();
            textInputField(key-48);
            textInputcounter = 0;
        }
    }
    
    if (key==127) {
        scoreZeroOne.clear();
        oldYHeight = 0;
        scoreData.clear();
        textInputcounter = 0;
    }
    
    if (key==32) {
        oldYHeight = 0;
        
        bPlay = !bPlay;
        if (bPlay) scoreDataInput();
    }
    
    if (key=='F') {
        bFullScreen = !bFullScreen;
        ofSetFullscreen(bFullScreen);
    }
    
}

void ofApp::audioRequested (float * output, int bufferSize, int nChannels){
    synth.fillBufferOfFloats(output, bufferSize, nChannels);
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){
    setScaleDegreeBasedOnMouseX();
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){
    setScaleDegreeBasedOnMouseX();
    
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
    trigger();
    
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
    
}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){
    
    scoreZeroOneSetup(textInput);
    
}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){
    
}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){
    
}
