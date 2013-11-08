#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    
    ofBackground( ofColor::fromHsb(0, 0, 0) );
    
    textInput = "dfashkjdf";
    scoreZeroOneSetup(textInput);
    
}

//--------------------------------------------------------------
void ofApp::update(){
    
    
}

//--------------------------------------------------------------
void ofApp::draw(){
    
    guideLine();
    scoreZeroOneDraw();
    
}

void ofApp::scoreZeroOneSetup(string _sInput){
    
    textInput = _sInput;
    cout << textInput.c_str() << endl;
    cout << ofToBinary(textInput) << endl;
    
    string _scoreZeroOne = ofToBinary(textInput);
    
    
    for (int i=0; i<_scoreZeroOne.size(); i++) {
        scoreZeroOne.push_back(  _scoreZeroOne.at(i)-48 );
        cout << scoreZeroOne[i] <<endl;
    }
    
}


void ofApp::scoreZeroOneDraw(){
    
    float _sizeX;
    int _rectWidth = 7;
    int _xStep = 10;

    _sizeX = ( (_rectWidth * scoreZeroOne.size()) + ((_xStep-_rectWidth) * (scoreZeroOne.size()-1)) );
    cout << _sizeX << endl;
    
    ofPushMatrix();
    ofTranslate( ofGetWidth()/2-_sizeX/2, ofGetHeight()/2 );
    ofPushStyle();
    ofSetColor( ofColor::fromHsb( 0, 0, 255, 255) );
    
    for (int i=0; i<scoreZeroOne.size(); i++) {
        int _ySize = scoreZeroOne[i];
        ofPushMatrix();
        ofTranslate(i*_xStep, 0);
        ofRect( 0, 0, _rectWidth, -_ySize*10+1 );
        ofPopMatrix();
    }
    
    ofPopStyle();
    
    ofPopMatrix();
    
}


void ofApp::guideLine(){
    
    ofPushMatrix();
    ofPushStyle();
    
    ofSetColor( ofColor::fromHsb( 80, 255, 255, 120) );
    
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

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
    
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
    
}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){
    
}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 
    
}
