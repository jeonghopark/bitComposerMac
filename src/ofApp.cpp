#include "ofApp.h"


//--------------------------------------------------------------
void ofApp::setup(){
    ofSetDataPathRoot("../Resources/data/");
    
    ofSetFrameRate(60);
    ofBackground( ofColor::fromHsb(0, 0, 255) );
    
    ofSoundStreamSetup(2, 0, this, 44100, 256, 4);
    
    textInput = "";
    binaryScoreSetup(textInput);
    
    textInputcounter = 0;
    noteCounter = 0;
    entropyParticleNumberFactor = 1;
    entropyParticleIndex = 1;
    oldEntropyparticleDrawIndex = 0;
    
    width = ofGetWidth();
    height = ofGetHeight();
    
    synthSetting();
    
    textDrawSetup();
    
    bEntropyParticleView = false;
    
    bTextInformation = true;
    
    
    
}

//--------------------------------------------------------------
void ofApp::update(){
    
    if (bPlay) {
        if (ofGetFrameNum()%2==0) {
            tickCounter++;
            if ( (tickCounter%8==0)||(tickCounter%4==0) ) {
                mainsScorePlay(noteCounter);
                noteCounter++;
                if (noteCounter>binaryScore.size()-1) {
                    noteCounter = 0;
                    entropyParticleIndex = entropyParticleIndex + entropyParticleNumberFactor;
                    
                    if (entropyParticleIndex>50) {
                        entropyParticleNumberFactor = -1;
                    }
                    if (entropyParticleIndex<0) {
                        entropyParticleNumberFactor = 1;
                    }
                    
                    for (int i=0; i<evolutionFactor.size(); i++) {
                        evolutionFactor[i] = evolutionFactor[i] + evolutionFactorDirection[i];
                        evolutionValue[i] = ofRandom(evolutionFactor[i]*2)-evolutionFactor[i];
                        if (evolutionFactor[i]>50) {
                            evolutionFactorDirection[i] = -1;
                        }
                        if (evolutionFactor[i]<0) {
                            evolutionFactorDirection[i] = 1;
                        }
                    }
                }
            }
        }
    }
    
    
    if (bEntropyParticleView) {
        entropyParticleMake(entropyParticleIndex);
        entropyParticleUpdate();
    }
    
}

//--------------------------------------------------------------
void ofApp::draw(){
    
    binaryScoreDraw();
    
    if (bTextInformation) {
        textInformation();
    }
    
    if (bPlay) {
        mainScoreDraw(noteCounter);
        if (bEntropyParticleView) entropyParticleDraw();
    }
    
    textDrawing();
    
}


void ofApp::binaryScoreSetup(string _sInput){
    
    textInput = _sInput;
    
    string _binaryScore = ofToBinary(textInput);
    
    for (int i=0; i<_binaryScore.size(); i++) {
        binaryScore.push_back( _binaryScore.at(i) );
    }
    
}


void ofApp::binaryScoreDraw(){
    float binaryElementSize = 1.7;
    binaryElementHeight = ofGetHeight()/height * 7 * binaryElementSize;
    binaryElementWidth = ofGetWidth()/width * 4 * binaryElementSize;
    binaryElementStep = ofGetWidth()/width * 5 * binaryElementSize;
    
    binaryScoreWidth = ( (binaryElementWidth * binaryScore.size()) + ((binaryElementStep-binaryElementWidth) * (binaryScore.size()-1)) );
    
    ofPushMatrix();
    ofTranslate( ofGetWidth()*0.5-binaryScoreWidth*0.5, ofGetHeight()*0.92 );
    ofPushStyle();
    ofSetColor( ofColor::fromHsb( 0, 0, 0, 255) );
    
    for (int i=0; i<binaryScore.size(); i++) {
        int _binaryElementHeight = binaryScore[i];
        
        if (_binaryElementHeight==1000) _binaryElementHeight = 0;
        
        ofPushMatrix();
        ofTranslate(i*binaryElementStep, 0);
        ofRect( 0, 0, binaryElementWidth, -_binaryElementHeight*binaryElementHeight+1 );
        ofPopMatrix();
    }
    
    ofPopStyle();
    ofPopMatrix();
    
}


void ofApp::mainScoreDraw(int _index){
    
    ofPushMatrix();
    ofTranslate( ofGetWidth()*0.5-binaryScoreWidth*0.5, ofGetHeight()*0.45 );
    
    ofPushStyle();
    ofSetColor( ofColor::fromHsb( 0, 0, 0, 50) );
    float binaryElementSize = 2.5;
    float _binaryElementXPos = _index * binaryElementStep;
    ofLine( _binaryElementXPos, -ofGetHeight()/height * 50 * 2.4, _binaryElementXPos, ofGetHeight()/height * 50 * 2.4 );
    ofPopStyle();
    
    
    ofPushStyle();
    ofSetColor( ofColor::fromHsb( 0, 0, 0, 255) );
    
    for (int i=0; i<mainScoreData.size(); i++) {
        
        float _binaryElementHeight = mainScoreData[i]+ofMap(evolutionValue[i],-100,100,-20,20);
        
        ofPushMatrix();
        ofTranslate(i*binaryElementStep, 0);
        ofRect( 0, 0, binaryElementWidth, -_binaryElementHeight * binaryElementHeight+1 );
        ofPopMatrix();
    }
    
    ofPopStyle();
    ofPopMatrix();
    
}

void ofApp::mainScoreDataInput(){
    mainScoreData.clear();
    
    for (int i=0; i<binaryScore.size(); i++) {
        
        int _yHeight = binaryScore[i];
        
        if (_yHeight==0) {
            _yHeight = -1;
        } else {
            _yHeight = 1;
        }
        
        _yHeight = oldYHeight+_yHeight;
        
        mainScoreData.push_back(-_yHeight);
        oldYHeight = _yHeight;
    }
    
}

void ofApp::mainsScorePlay(int _index){
    
    if (mainScoreData.size()>0) {
        int newScaleDegree = mainScoreData[_index]*3+40+ofMap(evolutionValue[_index],-100,100,-50,50);
        if(newScaleDegree != scaleDegree ){
            scaleDegree = newScaleDegree;
            trigger(scaleDegree);
        }else{
            scaleDegree = newScaleDegree;
        }
    }
}


void ofApp::entropyParticleMake(int _index) {
    
    entropyParticleBoxHeight = ofGetHeight()/height * 30;
    entropyParticleBoxWidth = ofGetWidth()/width * 150;
    
    int _indexRatio = ofClamp( ofMap( _index, 0, 50, 1, 7), 1, 7 );
    
    if (_index-oldEntropyparticleDrawIndex==1) {
        for (int i=0; i<_indexRatio; i++) {
            particleCircle.push_back( ParticleCircle( entropyParticleBoxWidth, entropyParticleBoxHeight ) );
        }
    }
    if (_index-oldEntropyparticleDrawIndex==-1) {
        for (int i=0; i<_indexRatio; i++) {
            particleCircle.erase( particleCircle.end() );
        }
    }
    
    oldEntropyparticleDrawIndex = _index;
    
}

void ofApp::entropyParticleUpdate(){
    for (int i=0; i<particleCircle.size(); i++) {
        particleCircle[i].update( entropyParticleBoxWidth, entropyParticleBoxHeight );
    }
}

void ofApp::entropyParticleDraw() {
    
    int _l = ofGetWidth()/width * 150;
    int _h = ofGetHeight()/height * 70;
    
    float _xTranslatePos = ofGetWidth()/width * 150;
    
    
    ofPushMatrix();
    ofPushStyle();
    
    ofTranslate( ofGetWidth()/2 - _l * 0.5, ofGetHeight() * 0.8 );
    
    for (int i=0; i<particleCircle.size(); i++) {
        particleCircle[i].draw();
    }
    
    ofNoFill();
    ofSetColor( ofColor::fromHsb( 0, 0, 0, 40) );
    
    ofRect( 0, 0, entropyParticleBoxWidth, entropyParticleBoxHeight );
    
    ofPopStyle();
    ofPopMatrix();
    
}

void ofApp::textInputCharToNumber(char _input){
    
    sBinaryScore.push_back(ofToBinary( _input ));
    
    string _binaryScore = ofToBinary( _input );
    
    for (int i=0; i<_binaryScore.size(); i++) {
        binaryScore.push_back( _binaryScore.at(i)-48 );
        evolutionFactor.push_back(0);
        evolutionFactorDirection.push_back(1);
        evolutionValue.push_back(0);
    }
    
}



void ofApp::textInformation(){
    
    ofPushStyle();
    ofSetColor( ofColor::fromHsb( 0, 0, 0, 255) );
    
    ofDrawBitmapString("hide/view information : \"1\" key", 10, ofGetHeight()-70);
    ofDrawBitmapString("fullScreen : enter key", 10, ofGetHeight()-55);
    ofDrawBitmapString("1: enter alphabets", 10, ofGetHeight()-40);
    ofDrawBitmapString("2: play (space bar)", 10, ofGetHeight()-25);
    ofDrawBitmapString("3: reset: del key", 10, ofGetHeight()-10);
    ofPopStyle();
    
}

void ofApp::synthSetting(){
    
    ControlGenerator midiNote = synth.addParameter("midiNumber");
    ControlGenerator noteFreq =  ControlMidiToFreq().input(midiNote);
    ControlGenerator tone2Vol = synth.addParameter("tone2VolIn");
    
    Generator tone = RectWave().freq( noteFreq );
    Generator tonePlus = SawtoothWave().freq( noteFreq*12 );
    
    tone = LPF12().input(tone).Q(10).cutoff((noteFreq * 30) + SineWave().freq(3) * 0.5 * noteFreq);
    tonePlus = LPF24().input(tonePlus).Q(20).cutoff((noteFreq * 30) + SineWave().freq(3) * 0.5 * noteFreq);
    
    tone = tone * 0.5 + tonePlus * 10;
    
    ControlGenerator envelopeTrigger = synth.addParameter("trigger");
    Generator toneWithEnvelope = tone * ADSR().attack(0).decay(0.1).sustain(0).release(0).trigger(envelopeTrigger).legato(false);
    Generator toneWithDelay = StereoDelay(0.5, 0.75).input(toneWithEnvelope).wetLevel(0.2).feedback(0.25);
    
    //-----
    ControlGenerator midiNoteBass = synthBass.addParameter("midiNumber");
    ControlGenerator noteFreqBass =  ControlMidiToFreq().input(midiNoteBass);
    
    Generator toneBass = RectWave().freq( noteFreqBass );
    
    toneBass = LPF12().input(toneBass).Q(10).cutoff((noteFreqBass * 30) + SineWave().freq(3) * 0.5 * noteFreqBass);
    
    ControlGenerator envelopeTriggerBass = synthBass.addParameter("trigger");
    Generator toneWithEnvelopeBass = toneBass * ADSR().attack(0).decay(0.03).sustain(0).release(0).trigger(envelopeTriggerBass).legato(false);
    
    //-----
    synth.setOutputGen( toneWithDelay + toneWithEnvelopeBass );
    
}



//--------------------------------------------------------------
void ofApp::trigger(){
    static int twoOctavePentatonicScale[10] = {0, 2, 4, 7, 9, 12, 14, 16, 19, 21};
    int degreeToTrigger = floor(ofClamp(scaleDegree, 0, 9));
	
    synth.setParameter("midiNumber", 44 + twoOctavePentatonicScale[degreeToTrigger]);
    synth.setParameter("trigger", 1);
}

void ofApp::trigger(int _note){
    synth.setParameter("midiNumber", _note);
    synth.setParameter("trigger", 1);
    synth.setParameter("tone2VolIn", ofMap(_note,30,80,0.2,5.0));
    
    synthBass.setParameter("midiNumber", _note-24);
    synthBass.setParameter("trigger", 1);
}

void ofApp::triggerScale(int _note, int _scale){
    //    static int twoOctavePentatonicScale[10] = {-19, -12, -7, -4, 0, 5, 7, 12, 19, 21};
    //    static int twoOctavePentatonicScale[10] = { 0, 2, 4, 5, 6, 9, 10, 12, 14, 16};  // Major Locrian scale
    static int twoOctavePentatonicScale[10] = { 0, 2, 4, 6, 9, 10, 12, 14, 16, 18};  // Prometheus scale
    int degreeToTrigger = floor(ofClamp( ofMap(_note, 20, 90, 0, 9), 0, 9));
    synth.setParameter("midiNumber",  + twoOctavePentatonicScale[degreeToTrigger] + 50);
    synth.setParameter("trigger", 1);
}




//--------------------------------------------------------------
void ofApp::textDrawSetup() {
    textSizeFactor = 0.7;
    textFontSize = ofGetWidth()/width * 20 * textSizeFactor;
    drawingFont.loadFont("arialbd.ttf", textFontSize);
}


void ofApp::textDrawing() {
    ofPushMatrix();
    ofPushStyle();
    ofSetColor( ofColor::fromHsb( 0, 0, 0, 160) );
    ofTranslate( ofGetWidth()*0.5-sBinaryScore.size()*textFontSize*0.5, ofGetHeight()-ofGetHeight()/height*26 );
    
    for (int i=0; i<sBinaryScore.size(); i++) {
        ofRectangle r = drawingFont.getStringBoundingBox(ofBinaryToString(sBinaryScore[i]), 0, 0);
        ofPushMatrix();
        drawingFont.drawString( ofBinaryToString(sBinaryScore[i]), (i*textFontSize) - r.width/2, 0 );
        ofPopMatrix();
    }
    
    ofPopStyle();
    ofPopMatrix();
}


//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
    
    if ( ((key<=122)&&(key>=97))||((key<=90)&&(key>=65)) ) {
        textInputcounter++;
        bPlay = false;
        if (textInputcounter<12) {
            textInputCharToNumber((char)key);
        } else {
            mainScoreData.clear();
            binaryScore.clear();
            oldYHeight = 0;
            textInputcounter = 0;
            sBinaryScore.clear();
        }
    }
    
    if (key==127) {
        binaryScore.clear();
        oldYHeight = 0;
        mainScoreData.clear();
        textInputcounter = 0;
        tickCounter = 0;
        noteCounter = 0;
        entropyParticleIndex = 1;
        oldEntropyparticleDrawIndex = 0;
        evolutionFactor.clear();
        evolutionValue.clear();
        evolutionFactorDirection.clear();
        sBinaryScore.clear();
        bEntropyParticleView = false;
        particleCircle.clear();
    }
    
    if (key==32) {
        oldYHeight = 0;
        
        bPlay = !bPlay;
        if (bPlay) {
            mainScoreDataInput();
            entropyParticleIndex = 1;
            oldEntropyparticleDrawIndex = 0;
            if (mainScoreData.size()!=0) bEntropyParticleView = true;
        } else {
            particleCircle.clear();
        }
    }
    
    if (key==13) {
        bFullScreen = !bFullScreen;
        ofSetFullscreen(bFullScreen);
    }
    
    if (key=='1') {
        bTextInformation = !bTextInformation;
    }
    
}

void ofApp::audioRequested (float * output, int bufferSize, int nChannels){
    synth.fillBufferOfFloats(output, bufferSize, nChannels);
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){
    
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){
    
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
    
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
    
}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){
    
    textDrawSetup();
    
    for (int i=0; i<particleCircle.size(); i++) {
        particleCircle[i].xMax = entropyParticleBoxWidth;
        particleCircle[i].yMax = entropyParticleBoxHeight;
    }
    
}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){
    
}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){
    
}
