//
//  EffectGrowingShapes.h
//  SmashingLaser2015_NYC
//
//  Created by Seb Lee-Delisle on 13/06/2015.
//
//

#pragma once

#include "ofMain.h"
#include "LaserManager.h"
#include "Synchroniser.h"



class AudioLaserShape {
	
	public :
	AudioLaserShape() {
		
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
	
};





class EffectGrowingShapes {

	public :
	
	EffectGrowingShapes();
	
	void update(float deltaTime);
	void draw(Synchroniser& sync, float volume, LaserManager& lm); 

	void drawShape(AudioLaserShape& shape, Synchroniser& sync, LaserManager& lm);

	bool enabled = false;

	AudioLaserShape kickShape;
	AudioLaserShape snareShape;
	AudioLaserShape hihatShape;
	AudioLaserShape bassShape;
	AudioLaserShape guitarShape;
	
	ofPoint centre;

	ofPolyline poly; 

	//vector<AudioLaserShape&> audioLaserShapes;

} ;