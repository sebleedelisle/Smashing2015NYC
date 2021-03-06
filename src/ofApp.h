// STILL TO DO :
// Test TDOAs in SonicHitFinder to show where TDOA radii should be - set up on mouse click.
// Add numbers to projections
// Check volume in sound clips - see if there's a volume threshold we can check? 


#pragma once

#include "ofMain.h"
#include "LaserManager.h"
#include "ParticleSystemManager.h"
#include "Synchroniser.h"
#include "PipeOrganData.h"
#include "DomeData.h"
#include "EffectLaserBeams.h"
#include "EffectLines.h"
#include "EffectGrowingShapes.h"

#include "AnimationSequence.h"
#include "EffectDomeLines.h"
#include "EffectPipeOrganLines.h"
#include "EffectParticles.h"
#include "ColourSystemGradient.h"
#include "ClappyBird.h"


#include <GLFW/glfw3.h>
#define GLFW_EXPOSE_NATIVE_COCOA
#define GLFW_EXPOSE_NATIVE_NSGL
#include "GLFW/glfw3native.h"

#include "WordParticle.h"


struct TimingNote {
	float start;
	float duration;
	String label;
	
};

class ofApp : public ofBaseApp{

	public:
	
	ofApp() : particleSystemManager(*ParticleSystemManager::instance()), laserManager(*LaserManager::instance()){
	};
	
	void setup();
	void update();
	void draw();
	void audioIn(float * input, int bufferSize, int numChannels);
	void windowResized(int width, int height);
	void keyPressed(int key);
	void keyReleased(int key);
	void mouseMoved(int x, int y );
	void mouseDragged(int x, int y, int button);
	void mousePressed(int x, int y, int button);
	void mouseReleased(int x, int y, int button);
	void gotMessage(ofMessage msg);
	void exit();
	
	void drawEffects();
	void resetEffects(); 
	
	void updatePeakFrequency(float * val, int numBands);
	
	void calculateScreenSizes();
	
	void drawSpirograph(ofPoint pos, int numrevolutions, float smallradius, float largeradius, float start, float end, float rotation);

	void showBlippySquares(int rownum =2, bool oddBarNumber = true);
	void showWaveform(float vpos = 0, float threshold = 0, bool useBass = true);
	void showWooeeyShapes(float voffset = 0, bool oddBarNumber = false );
	void updateWooeeyShapes();
	
	float currentWooeyPosition = -1;
	deque	<float> wooeyPositions;
	
	void setPosition(int posMS);
	void setVideoPositionMS(int posMS);
	
	
	void addWordParticle(string message, ofPoint pos); 
	void writeMessage(string message);
	
	void initNotes();
	void showNotes();
	
	void initStageOutlinePoly();
	
	//ofCamera cam;
	//ColourSystem cyan;
	
	ofRectangle secondScreenRect; 
	
	PipeOrganData pipeOrganData;
	DomeData domeData; 
	//float currentPipeIndex = 0;
	
	float currentPeakFrequency; // unit value
	
	int screenWidth, screenHeight;

	ofxPanel appGui;
	ofxPanel laserGui;
	ofxPanel redGui;
	ofxPanel greenGui;
	ofxPanel blueGui;
	
	vector<ofxPanel*> panels;
	
	ofParameter<bool> laserDomePoints;
	ofParameter<bool> laserOrganPoints;
	ofParameter<bool> showGuideImage;
	ofParameter<bool> showBands;
	
	
	ofParameter<bool> showStageOutline;
	
	ofParameter<ofPoint> stageOutlinePosition;
	ofParameter<ofPoint> stageOutlineRotation;
	ofParameter<ofPoint> stageOutlineScale;
	ofParameter<bool> stageOutlineLockScaleAspect;
	
	
	LaserManager& laserManager;
	ParticleSystemManager& particleSystemManager;
	
	ofFbo projectorFbo;
	ofFbo uiFbo; 
	ofRectangle projectorPosition;
	ofImage guideImage;
	
	EffectLaserBeams effectLaserBeams;
	EffectDomeLines effectDomeLines;
	EffectPipeOrganLines effectPipeOrganLines;
	EffectParticles effectParticles;
	
	EffectLines effectLines;
	EffectGrowingShapes effectGrowingShapes; 
	
	ClappyBird clappyBird;
	ofSoundStream soundStream;
	vector <float> left;
	vector <float> right;
	float smoothedInputVolume;
	bool clappyBirdActive;
    
    int svgCounter; 
	
	bool previewProjector;
	
	float clapLineBrightness = 0; 
	

	ofSoundPlayer music;
	//ofVideoPlayer video;
	
	Synchroniser sync;
	
	
	//ofxSVG worldMap;
	//ofxSVG laMap;
	
	ofxSVG stageOutlineSVG;
	
	
	
	ofImage smashingTitle;
	vector <ofxSVG> svgs;
	int currentSVG = -1;
	
	
	float soundPositionMS;
	float smoothVol;
	float vol;
	
	deque<float> volumes;
	deque<float> bassVolumes;
	
	AnimationSequence screenAnimation;
	
	ofPolyline poly;
	ofPolyline stagePoly;
	
	
	ofTrueTypeFont	proximaNovaLB;
	deque<WordParticle> wordParticles;
	
	
	vector <TimingNote> timingNotes;
	

	
};
