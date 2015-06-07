//
//  EffectLines.h
//  SmashingLaser2015_NYC
//
//  Created by Seb Lee-Delisle on 04/06/2015.
//
//

#pragma once

#include "ofMain.h"
#include "Synchroniser.h"




class LineSpike {
	
	public :
	
	
	
	ofPoint position;
	ofPoint vel;
	
	vector<ofPoint> graphics;
	
	// TODO should probably take into account the delta time
	void update() {
		
		position += vel;
		
	}
	
//	float width;
//	float height;
	
};


class AudioShape {
	
	public :
	AudioShape() {
		
		for(int i = 0; i<16; i++) {
			sixteens.push_back((i%4==0) ? 1 : 0);
		}
	};
	
	void update() {
		
		
		rotation += spin;
		size += ((targetSize - size) * sizeChangeSpeed);
		
		vel.set(0,0,0);
		vel += (targetPos - pos) * 0.1;
		pos +=vel;
		
		
		for(int i  = 0; i<spikes.size(); i++) {
			
			
			lineSpike.update();
			
			
		}
		
		
	}
	
	
	
	int numsides = 3; 
	vector<ofPoint> points;
	
	float rotation = 0;
	float spin = 0;
	
	ofPoint pos = ofPoint(0,0,0);
	ofPoint targetPos = ofPoint(0,0,0);
	ofPoint vel = ofPoint(0,0,0);
	
	bool enabled  = false;
	
	float size = 0.5;
	float targetSize = 0.5;
	float sizeChangeSpeed = 0.1;
	
	float masterScale = 1; 
	
	
	vector<float> sixteens;
	
	
	vector<LineSpike> spikes;
};


class EffectLines {

	public :
	
	EffectLines();
	
	void update();
	void draw(Synchroniser& sync);
	void drawShape(AudioShape& shape, Synchroniser& sync);

	ofCamera camera; 

	//vector<LineSpike> spikes;
	//vector<ofPoint> linePoints;
	
	float emitterRotation;
	
	//ofPolyline poly;
	
	AudioShape kickShape;
	AudioShape snareShape;
	AudioShape hihatShape;
	AudioShape bassShape;
	AudioShape guitarShape;
	
	
};