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
	
	bool enabled = true;
	
	vector<ofPoint> graphics;
	
	// TODO should probably take into account the delta time
	void update() {
		
		if(!enabled) return;
		position += vel;
		//cout << position << " " << vel <<endl;
		life --;
		if(life<=0) enabled = false;
		
	}
	
	float life = 300;
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
			
			spikes[i].update();
			//lineSpike.update();
			
			
		}
		
		while((spikes.size()>0) &&(!spikes.front().enabled)) spikes.pop_front();
	}
	
	void addLineSpike() {
		if(!emittingSpikes) return;
		spikes.push_back(LineSpike());
		LineSpike& spike = spikes.back();
		//spike.position = kickShape.pos;
		spike.vel.z = 4;


	}
	
	int numsides = 3; 
	vector<ofPoint> points;
	
	float rotation = 0;
	float spin = 0;
	
	ofPoint pos = ofPoint(0,0,0);
	ofPoint targetPos = ofPoint(0,0,0);
	ofPoint vel = ofPoint(0,0,0);
	
	bool enabled  = false;
	
	bool emittingSpikes = false;
	
	float size = 0.5;
	float targetSize = 0.5;
	float sizeChangeSpeed = 0.1;
	
	float masterScale = 1; 
	
	
	vector<float> sixteens;
	
	
	deque<LineSpike> spikes;
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