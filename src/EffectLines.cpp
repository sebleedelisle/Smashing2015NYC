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

	
	//float yRotation = (ofGetMouseX() - (ofGetWidth()/2));
	
	
	if(sync.currentBar<8) {
		
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
	else if(sync.currentBar>=8) {
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
	}
	
	else if (false) {
		
		
		
		camera.rotateAround(ofMap(sync.currentBarFloat, 8, 1200, 0, 360), ofVec3f(0,-1,0.5).normalize(), ofVec3f(0,0,0));
		
		
//		if(sync.beatTriggered) {
//			spikes.push_back((LineSpike){0, 50, 10});
//			
//			
//		}
		
		
	}
	
	
	
	camera.lookAt(ofVec3f(0,0,0));
	
	
	
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
	
	ofNoFill();
	ofDisableSmoothing();
	ofSetLineWidth(2);
	
	ofPushMatrix();
	ofTranslate(shape.pos);

//	ofRotateY(90);
	

	if(sync.sixteenthTriggered) {
		if(shape.sixteens[sync.current16th] >0) {
			shape.size = shape.sixteens[sync.current16th];
			shape.addLineSpike();
		}
	}
	
	
	ofPushMatrix();
	ofRotateZ(shape.rotation);
	ofScale(shape.masterScale,shape.masterScale);
	if(shape.points.size()==0) {
		ofSetCircleResolution(shape.numsides);
		ofCircle(0,0,0,20 * shape.size);
	} else {
		
		ofScale(20*shape.size, 20*shape.size);
		ofBeginShape();
		for(int i = 0; i<shape.points.size(); i++) {
			ofPoint p = shape.points[i];//ofPoint(ofRandom(-0.05,0.05), ofRandom(-0.05,0.05)) + ;
			ofVertex(p);
		}
		ofEndShape();
		
		
	}
	
	ofPopMatrix();
	
	ofSetLineWidth(1);
	deque<LineSpike> &spikes = shape.spikes;
	ofBeginShape();
	ofVertex(0,0,0);
	for (int i = spikes.size()-1; i>=0; i-- ) {
		LineSpike&spike = spikes[i];
	
		ofVertex(spike.position);
		
		int z =0;
		for(z = 1; z<7; z++) {
		
			ofPoint p =ofPoint(spike.position.x , spike.position.y + ((abs((z%2)-1)-0.5)*4) , spike.position.z + (z*4));
			p+= (ofPoint(ofRandom(-1,1), ofRandom(-1,1), ofRandom(-1,1)) *0.5);
			
			ofVertex(p);
		}
	
		ofVertex(spike.position.x , spike.position.y , spike.position.z + (z*4));
		
	
	}
	ofEndShape();
		
	ofPopMatrix();
	
}


