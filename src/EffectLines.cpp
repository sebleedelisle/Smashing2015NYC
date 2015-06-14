//
//  EffectLines.cpp
//  SmashingLaser2015_NYC
//
//  Created by Seb Lee-Delisle on 04/06/2015.
//
//

#include "EffectLines.h"


EffectLines :: EffectLines() {
	
	
//	for(float x = 1000; x>-1000; x-=2) {
//		
//		linePoints.push_back(ofPoint(x, 0, 0));
//		
//	}
	
	camera.setFov(20);
	emitterRotation = 0;
	
	
	// blocks introduced just for scoping and variable name reuse.
	
	// KICK
	{
	
		kickShape.enabled = true;
		kickShape.numsides = 7;
		kickShape.masterScale =0.8;
	
	}
	// GUITAR
	{
		float beats[] = {1,0,0,1,0,0,1,0,1,0,0,0,1,0,0,0};
		vector<float> tmp(beats, beats+16);
		guitarShape.sixteens = tmp;
		guitarShape.numsides = 4;
		guitarShape.targetSize = 0.2;
		
		ofPoint points[] = {ofPoint(-0.2,-0.8), ofPoint(0.2,-0.8), ofPoint(0.2,0.8), ofPoint(-0.2,0.8),ofPoint(-0.2,-0.8)};
		
		vector<ofPoint> pnts (points, points+5);
		guitarShape.points  = pnts;
	}
	// HIHAT
	{
		float beats[] = {1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,1};
		vector<float> tmp(beats, beats+16);
		hihatShape.sixteens = tmp;
		hihatShape.numsides = 4;
		hihatShape.targetSize = 0.1;
		hihatShape.sizeChangeSpeed = 0.3;
		hihatShape.masterScale = 0.8;
		
		ofPoint points[] = {ofPoint(0,-1), ofPoint(0,1), ofPoint(0.1,0.1), ofPoint(1,0),ofPoint(-1,0)};
		
		vector<ofPoint> pnts (points, points+5);
		hihatShape.points  = pnts;
	}
	
	// SNARE
	{
	
		float beats[] = {0,0,0,0,1,0,0,0,0,0,0,0,1,0,0,0};
		vector<float> tmp(beats, beats+16);
		snareShape.sixteens = tmp;
		snareShape.numsides = 3;
		snareShape.targetSize = 0.2;
	}

}


void EffectLines::update() {


}


void EffectLines :: draw(Synchroniser& sync) {
	
	
	//poly.clear();
	
	camera.setPosition(0,0,600);
	hihatShape.emittingSpikes = false;
	kickShape.emittingSpikes = false;
	snareShape.emittingSpikes = false;
	guitarShape.emittingSpikes = false;
	
	hihatShape.rainbows = false;
	kickShape.rainbows = false;
	snareShape.rainbows = false;
	guitarShape.rainbows = false;
	
	ofPoint cameraTarget(0,0,0);

	
	//float yRotation = (ofGetMouseX() - (ofGetWidth()/2));
	
	
	if(sync.currentBar<8) {
		
		if(sync.currentBarFloat<0.5) {
			kickShape.colour = ofColor(ofMap(sync.currentBarFloat, 0, 0.5, 0,255));
		} else {
			kickShape.colour = ofColor(255);
		}
		if(sync.currentBar<4) {
			kickShape.targetSize = ofMap(sync.currentBarFloat, 0, 4, 1, 0.5);
			
		}
		
		kickShape.spin = snareShape.spin = sync.currentBarFloat*2;
		snareShape.enabled = false;
		guitarShape.enabled = false;
		
		camera.setPosition(0,0,ofMap(sync.currentBarFloat,0,8,5000,600));
		guitarShape.targetPos.x = 0;
		snareShape.targetPos.x = 0;
		kickShape.targetPos.x = 0;
		
//		if(sync.currentBar>=6) {
//			kickShape.targetPos.x = 20;
//			snareShape.targetPos.x = -20;
//			snareShape.enabled =true;
//		}
		
		
	}
	else if ((sync.currentBar>=8) && ( sync.currentBar<32)) {
		kickShape.spin =  snareShape.spin = (sin(sync.currentBarFloat*2) *5) + 10;
		guitarShape.enabled = true;
		snareShape.enabled =true;
		guitarShape.spin = (cos((sync.currentBarFloat-8)*2) *10) + 18;
		hihatShape.spin = (cos((sync.currentBarFloat)*2) *5);
		//guitarShape.pos.x = ofMap(sync.currentBarFloat,8,8.2,0,20, true);
		//kickShape.pos.x = ofMap(sync.currentBarFloat,8,8.2,0,-20, true);
		
		if(sync.currentBar<12) {
			guitarShape.targetPos.x = 40;
			kickShape.targetPos.x = 0;
			snareShape.targetPos.x = -40;
			hihatShape.enabled = false;
		} else {
			hihatShape.enabled = true;
			guitarShape.targetPos.x = 60;
			kickShape.targetPos.x = 20;
			hihatShape.targetPos.x = -20;
			snareShape.targetPos.x = -60;
			
		}
		if(sync.currentBar>=16) {
			
			//camera.setPosition(camera.getPosition().x, ofMap(sync.currentBarFloat, 16, 32, 0, 36), camera.getPosition().z);
			camera.rotateAround(ofMap(sync.currentBarFloat, 16, 48, 0, 360), ofVec3f(0,1,0.5).normalize(), ofVec3f(0,0,0));
			
			//if(sync.beatTriggered) {
			//
			//
			//}
			
			hihatShape.emittingSpikes = true;
			kickShape.emittingSpikes = true;
			snareShape.emittingSpikes = true;
			guitarShape.emittingSpikes = true;
			
		}
	} else if((sync.currentBar>=32)&&(sync.currentBar<56)) {
		
		camera.setPosition(0,0,ofMap(sync.currentBarFloat, 46, 52, 600,1000,true));
		camera.rotateAround(ofMap(sync.currentBarFloat, 16, 48, 0, 360), ofVec3f(0,1,0.5).normalize(), ofVec3f(0,0,0));
		
//		hihatShape.emittingSpikes = false;
//		kickShape.emittingSpikes = false;
//		snareShape.emittingSpikes = false;
//		guitarShape.emittingSpikes = false;
		if(sync.currentBar>=48) {
			hihatShape.rainbows = true;
			kickShape.rainbows = true;
			snareShape.rainbows = true;
			guitarShape.rainbows = true;
		}
		
	} else if((sync.currentBar>=56)&&(sync.currentBar<84)) {
		// AFTER FIRST CHORUS
		
		camera.setPosition(0,0,ofMap(sync.currentBarFloat, 56, 57, 1000,400,true));
		
		
		// FOR COOL CAMERA MOVES
		//camera.rotateAround(ofMap(sync.currentBarFloat, 56, 64, -10, 360), ofVec3f(0,1,0.1).normalize(), ofVec3f(0,0,500));
		
		camera.rotateAround(ofMap(sync.currentBarFloat, 56, 64, -20, 380), ofVec3f(0,1,0.14).normalize(), ofVec3f(0,0,ofMap(sync.currentBarFloat, 64,68,0,500,true)));
		cameraTarget.z = 40;

		
		hihatShape.emittingSpikes = true;
		kickShape.emittingSpikes = true;
		snareShape.emittingSpikes = true;
		guitarShape.emittingSpikes = true;
		hihatShape.rainbows = true;
		kickShape.rainbows = true;
		snareShape.rainbows = true;
		guitarShape.rainbows = true;
		
	} else if (false) {
		
		
		
		camera.rotateAround(ofMap(sync.currentBarFloat, 8, 1200, 0, 360), ofVec3f(0,-1,0.5).normalize(), ofVec3f(0,0,0));
		
		
//		if(sync.beatTriggered) {
//			spikes.push_back((LineSpike){0, 50, 10});
//			
//			
//		}
		
		
	}
	
	
	
	camera.lookAt(cameraTarget);
	
	
	
	// reset points
	
//	
//	for(int i = 0; i<linePoints.size(); i++) {
//		
//		linePoints[i].y =0 ;
//		linePoints[i].z = 0;
//		
//	}
//	
//	for(int i = 0; i<spikes.size(); i++) {
//		
//		LineSpike &spike = spikes[i];
//		spike.position +=4;
//		
//		for(int j = 0; j<linePoints.size(); j++) {
//			
//			ofPoint& point = linePoints[j];
//			
//			if((point.x>0) &&(point.x>spike.position-spike.width) && (point.x<spike.position)){
//				float xpos = point.x - spike.position + spike.width;
//				
//				float h = spike.height*2;
//				float hh = spike.height;
//				
//				float ypos = fabs(fmod(xpos*1.4f,h) - hh) -hh/2 ;
//				point.y = ypos;// + ofRandom(-1,1); // spike.height;
//				
//				//cout << point.y << " " << xpos << endl;
//			}
//		}
//		
//		
//		
//	}
//
//	for(int i = 0; i<linePoints.size(); i++) {
//		poly.addVertex(linePoints[i]);
//	}
//	
//	poly.simplify();
//
//	for(int i = 0; i<poly.getVertices().size(); i++) {
//
//		ofPoint& p = poly.getVertices()[i];
//		if(p.y!=0) p.y+=ofRandom(-1,1);
//	}

	camera.begin();
	
	ofSetLineWidth(2);
	ofSetColor(255);
	ofNoFill();
	ofEnableBlendMode(OF_BLENDMODE_ADD);
	
	drawShape(kickShape, sync);
	drawShape(guitarShape, sync);
	drawShape(snareShape, sync);
	drawShape(hihatShape, sync);

	//poly.draw();
	
	
	camera.end();

}


void EffectLines:: drawShape(AudioShape& shape, Synchroniser& sync) {

	shape.update();
	
	if(!shape.enabled) return;
	
//	ofRotateY(90);
	

	if(sync.sixteenthTriggered) {
		shape.trigger16th(sync.current16th);
	}
	
	
	shape.draw();
	
	
}


