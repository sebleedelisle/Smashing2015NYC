//
//  EffectGrowingShapes.cpp
//  SmashingLaser2015_NYC
//
//  Created by Seb Lee-Delisle on 13/06/2015.
//
//

#include "EffectGrowingShapes.h"



EffectGrowingShapes :: EffectGrowingShapes() {
	
	
	//	for(float x = 1000; x>-1000; x-=2) {
	//
	//		linePoints.push_back(ofPoint(x, 0, 0));
	//
	//	}
	
	//camera.setFov(20);
	//emitterRotation = 0;
	
	centre.set(640,480);
	
	
	// blocks introduced just for scoping and variable name reuse.
	
	// KICK
	float spinspeed = 1;
	
	{
		
		kickShape.enabled = true;
		kickShape.numsides = 7;
		kickShape.masterScale =0.8;
		kickShape.spin = spinspeed;
		
		kickShape.targetSize = 0.9;
	}
	// GUITAR
	{
		float beats[] = {1,0,0,1,0,0,1,0,1,0,0,0,1,0,0,0};
		vector<float> tmp(beats, beats+16);
		guitarShape.sixteens = tmp;
		guitarShape.numsides = 8;
		guitarShape.targetSize = 0.9;
		
//		ofPoint points[] = {ofPoint(-0.2,-0.8), ofPoint(0.2,-0.8), ofPoint(0.2,0.8), ofPoint(-0.2,0.8),ofPoint(-0.2,-0.8)};
//		;
//		vector<ofPoint> pnts (points, points+5);
//		guitarShape.points  = pnts;
//		guitarShape.spin = -spinspeed;
		guitarShape.enabled = true;
		guitarShape.targetPos.z = -100;
		
	}
	// HIHAT
	{
		float beats[] = {1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,1};
		vector<float> tmp(beats, beats+16);
		hihatShape.sixteens = tmp;
		hihatShape.numsides = 10;
		hihatShape.targetSize = 0.9;
		hihatShape.sizeChangeSpeed = 0.3;
		hihatShape.masterScale = 0.8;
		hihatShape.targetPos.z  = -200;
//		ofPoint points[] = {ofPoint(0,-1), ofPoint(0,1), ofPoint(0.1,0.1), ofPoint(1,0),ofPoint(-1,0)};
//		
//		vector<ofPoint> pnts (points, points+5);
//		hihatShape.points  = pnts;
//		hihatShape.spin = spinspeed;
		hihatShape.enabled= true;
	
	
	}
	
	// SNARE
	{
		
		float beats[] = {0,0,0,0,1,0,0,0,0,0,0,0,1,0,0,0};
		vector<float> tmp(beats, beats+16);
		snareShape.sixteens = tmp;
		snareShape.numsides = 3;
		snareShape.targetSize = 0.9;
		snareShape.spin = -spinspeed;

		snareShape.enabled = true;
		snareShape.targetPos.z = -300;
	}
	
}


void EffectGrowingShapes::update(float deltaTime) {
	
	
}




void EffectGrowingShapes :: draw(Synchroniser& sync, float volume, LaserManager& lm) {
	
	if(!enabled) return;
	
	ofSetLineWidth(2);
	ofSetColor(255);
	ofNoFill();
	
	drawShape(kickShape, sync, lm);
	drawShape(guitarShape, sync, lm);
	drawShape(snareShape, sync, lm);
	drawShape(hihatShape, sync, lm);
	
	
}


void EffectGrowingShapes:: drawShape(AudioLaserShape& shape, Synchroniser& sync, LaserManager& lm) {
	
	shape.targetPos.z += 1;

	shape.update();
	if(shape.pos.z>600) {
		shape.pos.z-=1200;
		shape.targetPos.z -=1200;
		
	}
	
	if(!shape.enabled) return;
	
	
	if(sync.sixteenthTriggered) {
		if(shape.sixteens[sync.current16th] >0) {
			shape.size = shape.sixteens[sync.current16th];
			
		}
	}
	
	poly.clear();
	float size = 100;
	if(shape.points.size()==0) {
		
		
		for(int i = 0; i<=shape.numsides; i++) {
			
			ofPoint p(size*shape.size, 0);
			p.rotate(ofMap(i, 0, shape.numsides, 0, 360), ofPoint(0,0,1));
			p *= shape.masterScale;
			p.rotate(shape.rotation, ofPoint(0,0,1));
			
			p += shape.pos + centre;
			poly.addVertex(p);
			
			
			
		}
		
		
		
	} else {
		
			for(int i = 0; i<shape.points.size(); i++) {
			ofPoint p = shape.points[i];//ofPoint(ofRandom(-0.05,0.05), ofRandom(-0.05,0.05)) + ;
			
			p *= shape.masterScale * size*shape.size;
			p.rotate(shape.rotation, ofPoint(0,0,1));
			
			p += shape.pos + centre;
			poly.addVertex(p);

			
		}
		
		
	}
	

	poly.close();
	poly.simplify();
	lm.addLaserPolyline(poly);
	
}



