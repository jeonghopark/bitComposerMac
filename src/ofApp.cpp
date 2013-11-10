#include "ofApp.h"


//--------------------------------------------------------------
void ofApp::setup(){
    
    ofSetFrameRate(60);
    ofBackground( ofColor::fromHsb(0, 0, 255) );
    
    ofSoundStreamSetup(2, 0, this, 44100, 256, 4);
    
    textInput = "";
    scoreZeroOneSetup(textInput);

    textInputcounter = 0;
    noteCounter = 0;
    entrophyTriLineXPosDirection = 1;
    entrophyTriLineXPos = 1;
    oldEntropyparticleDrawIndex = 0;
    
    synthSetting();
    
    bAllDrawing = false;
    
    textDrawSetup();
    
    bEntropyParticleView = false;

}

//--------------------------------------------------------------
void ofApp::update(){
    
    if (bPlay) {
        if (ofGetFrameNum()%2==0) {
            tickCounter++;
            if ( (tickCounter%8==0)||(tickCounter%4==0) ) {
                scorePlay(noteCounter);
                noteCounter++;
                if (noteCounter>scoreZeroOne.size()-1) {
                    noteCounter = 0;
                    entrophyTriLineXPos = entrophyTriLineXPos + entrophyTriLineXPosDirection;
                    
                    if (entrophyTriLineXPos>50) {
                        entrophyTriLineXPosDirection = -1;
                    }
                    if (entrophyTriLineXPos<0) {
                        entrophyTriLineXPosDirection = 1;
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
        entropyParticleMake(entrophyTriLineXPos);
        entropyParticleUpdate();
    }


}

//--------------------------------------------------------------
void ofApp::draw(){
    
    //    guideLine();
    scoreZeroOneDraw();
    
    interfaceInformation();
    
    if (bPlay) {
        scoreDraw(noteCounter);
//        entropyTriDraw(entrophyTriLineXPos);
        if (bEntropyParticleView) entropyParticleDraw();
//        allDrawing();
    }
    
    textDrawing();

    
}

void ofApp::scoreZeroOneSetup(string _sInput){
    
    textInput = _sInput;
    
    string _scoreZeroOne = ofToBinary(textInput);
    
    for (int i=0; i<_scoreZeroOne.size(); i++) {
        scoreZeroOne.push_back( _scoreZeroOne.at(i) );
    }
    
    _rectHeight = ofGetHeight()*0.00912*1.4;
    _rectWidth = ofGetWidth()*0.00390*1.4;
    _xStep = ofGetWidth()*0.00488*1.4;

}


void ofApp::scoreZeroOneDraw(){
    
    _sizeX = ( (_rectWidth * scoreZeroOne.size()) + ((_xStep-_rectWidth) * (scoreZeroOne.size()-1)) );
    
    ofPushMatrix();
    ofTranslate( ofGetWidth()*0.5-_sizeX*0.5, ofGetHeight()*0.92 );
    ofPushStyle();
    ofSetColor( ofColor::fromHsb( 0, 0, 0, 255) );
    
    for (int i=0; i<scoreZeroOne.size(); i++) {
        int _yHeight = scoreZeroOne[i];
        
        if (_yHeight==1000) _yHeight = 0;

        ofPushMatrix();
        ofTranslate(i*_xStep, 0);
        ofRect( 0, 0, _rectWidth, -_yHeight*_rectHeight+1 );
        ofPopMatrix();
    }
    
    ofPopStyle();
    ofPopMatrix();
    
}


void ofApp::scoreDraw(int _index){
    
    ofPushMatrix();
    ofTranslate( ofGetWidth()*0.5-_sizeX*0.5, ofGetHeight()*0.45 );

    ofPushStyle();
    ofSetColor( ofColor::fromHsb( 0, 0, 0, 50) );
    float _size = 2.5;
    float _xPos = _index*_xStep;
    ofLine( _xPos, -ofGetHeight()*0.0651*2.4, _xPos, ofGetHeight()*0.0651*2.4 );
    ofPopStyle();

    
    ofPushStyle();
    ofSetColor( ofColor::fromHsb( 0, 0, 0, 255) );
    
    for (int i=0; i<scoreData.size(); i++) {

        float _yHeight = scoreData[i]+ofMap(evolutionValue[i],-100,100,-20,20);

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
        } else {
            _yHeight = 1;
        }
        
        _yHeight = oldYHeight+_yHeight;
        
        scoreData.push_back(-_yHeight);
        oldYHeight = _yHeight;
    }
    
}

void ofApp::scorePlay(int _index){
    
    if (scoreData.size()>0) {
        int newScaleDegree = scoreData[_index]*3+40+ofMap(evolutionValue[_index],-100,100,-50,50);
        if(newScaleDegree != scaleDegree ){
            scaleDegree = newScaleDegree;
            trigger(scaleDegree);
//            triggerScale(scaleDegree,1);
            allValue.push_back(newScaleDegree);
        }else{
            scaleDegree = newScaleDegree;
        }
        

    }
}

void ofApp::allDrawing(){
    
    ofPushStyle();
    ofSetColor( ofColor::fromHsb( 0, 0, 0, 50) );

    for (int i=0; i<allValue.size(); i++) {
        ofRect( i*3, 0, 3, allValue[i]*10 );
    }
    ofPopStyle();
}

void ofApp::entropyTriDraw(int _xPos){
    ofPushMatrix();
    ofPushStyle();
    
    int _l = ofGetWidth() * 0.09765625;
    int _h = -_l;
    int movingPointX = ofMap(_xPos, 0, 50, 0, ofGetWidth()*0.048828125)*2;;
    int movingPointY = -movingPointX;

    float _xTranslatePos = ofGetWidth()*0.146484375;
    ofTranslate( ofGetWidth()/2-_l * 0.5, ofGetHeight()*0.8 );
    ofSetColor( ofColor::fromHsb( 0, 0, 0, 50) );
    
    ofLine( movingPointX, 0, movingPointX, movingPointY );
    ofLine( 0, movingPointY, movingPointX, movingPointY );
    
    ofLine( 0, 0, _l, 0 );
    ofLine( 0, 0, 0, _h );

    ofSetColor( ofColor::fromHsb( 0, 0, 0, 30) );
    ofLine( 0, 0, _l, _h );
    
    ofPopStyle();
    ofPopMatrix();
    
}


void ofApp::entropyParticleMake(int _index) {
    
    entropyParticleHeight = ofGetHeight() * 0.0390625;
    entropyParticleWidth = ofGetWidth() * 0.146484375;
        
    int _indexRatio = ofClamp( ofMap( _index, 0, 50, 1, 7), 1, 7 );
    
    if (_index-oldEntropyparticleDrawIndex==1) {
        for (int i=0; i<_indexRatio; i++) {
            particleCircle.push_back( ParticleCircle( entropyParticleWidth, entropyParticleHeight ) );
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
        particleCircle[i].update( entropyParticleWidth, entropyParticleHeight );
    }
}

void ofApp::entropyParticleDraw() {
    
    int _l = ofGetWidth() * 0.146484375;
    int _h = ofGetHeight() * 0.09114583;
    
    float _xTranslatePos = ofGetWidth()*0.146484375;
    
    
    ofPushMatrix();
    ofPushStyle();
    
    ofTranslate( ofGetWidth()/2 - _l * 0.5, ofGetHeight() * 0.8 );
    
    for (int i=0; i<particleCircle.size(); i++) {
        particleCircle[i].draw();
    }
    
    ofNoFill();
    ofSetColor( ofColor::fromHsb( 0, 0, 0, 40) );

    ofRect( 0, 0, entropyParticleWidth, entropyParticleHeight );
    
    ofPopStyle();
    ofPopMatrix();
    
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


void ofApp::textInputCharToNumber(char _input){

    sScoreZeroOne.push_back(ofToBinary( _input ));
    
    string _scoreZeroOne = ofToBinary( _input );

    for (int i=0; i<_scoreZeroOne.size(); i++) {
        scoreZeroOne.push_back( _scoreZeroOne.at(i)-48 );
        evolutionFactor.push_back(0);
        evolutionFactorDirection.push_back(1);
        evolutionValue.push_back(0);
    }
    
}

void ofApp::interfaceInformation(){
    
    ofPushStyle();
    ofSetColor( ofColor::fromHsb( 0, 0, 0, 255) );
    
    ofDrawBitmapString("fullScreen : enter key", 10, ofGetHeight()-40);
    ofDrawBitmapString("reset : del", 10, ofGetHeight()-25);
    ofDrawBitmapString("play : space bar", 10, ofGetHeight()-10);
    ofPopStyle();
    
}

void ofApp::synthSetting(){
    
    ControlGenerator midiNote = synth.addParameter("midiNumber");
    ControlGenerator noteFreq =  ControlMidiToFreq().input(midiNote);
    ControlGenerator tone2Vol = synth.addParameter("tone2VolIn");

    Generator tone = RectWave().freq( noteFreq );
    Generator tone2 = SawtoothWave().freq( noteFreq*12 );
    
    tone = LPF12().input(tone).Q(10).cutoff((noteFreq * 30) + SineWave().freq(3) * 0.5 * noteFreq);
    tone2 = LPF24().input(tone2).Q(20).cutoff((noteFreq * 30) + SineWave().freq(3) * 0.5 * noteFreq);
    
    tone = tone * 0.5 + tone2 * 10.8;
    
    ControlGenerator envelopeTrigger = synth.addParameter("trigger");
    Generator toneWithEnvelope = tone * ADSR().attack(0).decay(0.1).sustain(0).release(0).trigger(envelopeTrigger).legato(false);
    Generator toneWithDelay = StereoDelay(0.5, 0.75).input(toneWithEnvelope).wetLevel(0.2).feedback(0.25);
    synth.setOutputGen( toneWithDelay );
    
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
}

void ofApp::triggerScale(int _note, int _scale){
//    static int twoOctavePentatonicScale[10] = {-19, -12, -7, -4, 0, 5, 7, 12, 19, 21};
//    static int twoOctavePentatonicScale[10] = { 0, 2, 4, 5, 6, 9, 10, 12, 14, 16};  // Major Locrian scale
    static int twoOctavePentatonicScale[10] = { 0, 2, 4, 6, 9, 10, 12, 14, 16, 18};  // Prometheus scale
    int degreeToTrigger = floor(ofClamp( ofMap(_note, 20, 90, 0, 9), 0, 9));
    synth.setParameter("midiNumber",  + twoOctavePentatonicScale[degreeToTrigger] + 50);
    synth.setParameter("trigger", 1);
}


void ofApp::textDrawSetup() {
    textSizeFactor = 0.7;
    textFontSize = ofGetWidth()*0.0205078125 * textSizeFactor;
    drawingFont.loadFont("arialbd.ttf", textFontSize);
}

void ofApp::textDrawing() {
    ofPushMatrix();
    ofPushStyle();
    ofSetColor( ofColor::fromHsb( 0, 0, 0, 160) );
    ofTranslate( ofGetWidth()*0.5-sScoreZeroOne.size()*textFontSize*0.5, ofGetHeight()-ofGetHeight()*0.03451 );
    for (int i=0; i<sScoreZeroOne.size(); i++) {
        ofPushMatrix();
        drawingFont.drawString( ofBinaryToString(sScoreZeroOne[i]), (i*textFontSize), 0 );
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
            scoreData.clear();
            scoreZeroOne.clear();
//            textInputCharToNumber((char)key);
            oldYHeight = 0;
            textInputcounter = 0;
            sScoreZeroOne.clear();
        }
    }

    
    if (key==127) {
        scoreZeroOne.clear();
        oldYHeight = 0;
        scoreData.clear();
        textInputcounter = 0;
        tickCounter = 0;
        noteCounter = 0;
        entrophyTriLineXPos = 1;
        oldEntropyparticleDrawIndex = 0;
        evolutionFactor.clear();
        evolutionValue.clear();
        evolutionFactorDirection.clear();
        sScoreZeroOne.clear();
        bEntropyParticleView = false;
        particleCircle.clear();
//        entropyParticleMake(0);

    }
    
    if (key==32) {
        oldYHeight = 0;
        
        bPlay = !bPlay;
        if (bPlay) {
            scoreDataInput();
            entrophyTriLineXPos = 1;
            oldEntropyparticleDrawIndex = 0;
            if (scoreData.size()!=0) bEntropyParticleView = true;
        } else {
            particleCircle.clear();
        }
    }

    
    if (key==13) {
        bFullScreen = !bFullScreen;
        ofSetFullscreen(bFullScreen);
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
    trigger();


}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
    
}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){
    
    textDrawSetup();
    
    for (int i=0; i<particleCircle.size(); i++) {
        particleCircle[i].xMax = entropyParticleWidth;
        particleCircle[i].yMax = entropyParticleHeight;
    }
    
}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){
    
}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){
    
}
