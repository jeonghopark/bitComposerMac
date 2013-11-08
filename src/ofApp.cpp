#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    
    ofBackground( ofColor::fromHsb(0, 0, 255) );
    
    textInput = "";
    scoreZeroOneSetup(textInput);
    
    textInputcounter = 0;
}

//--------------------------------------------------------------
void ofApp::update(){
    
    
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
//    cout << textInput.c_str() << endl;
//    cout << ofToBinary(textInput) << endl;
    
    string _scoreZeroOne = ofToBinary(textInput);
    
    for (int i=0; i<_scoreZeroOne.size(); i++) {
        scoreZeroOne.push_back(  _scoreZeroOne.at(i)-48 );
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

    for (int i=0; i<scoreZeroOne.size(); i++) {
        int _yHeight = scoreZeroOne[i];
        ofPushMatrix();
        if (_yHeight==0) _yHeight = -1;
        
        _yHeight = oldYHeight+_yHeight;


        ofTranslate(i*_xStep, 0);
        ofRect( 0, 0, _rectWidth, -_yHeight*_rectHeight+1 );

        ofPopMatrix();

        oldYHeight = _yHeight;
    }
    
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
            scoreZeroOne.clear();
            textInputField(key-48);
            textInputcounter = 1;
        }
    }
    
    if (key==127) {
        scoreZeroOne.clear();
        textInputcounter = 0;
    }
    
    if (key==32) {
        bPlay = !bPlay;
    }

    if (key=='F') {
        bFullScreen = !bFullScreen;
        ofSetFullscreen(bFullScreen);
    }
    
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

    scoreZeroOneSetup(textInput);

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){
    
}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){
    
}
