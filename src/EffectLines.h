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
		
		counter ++;
		
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
	
	
	void draw() {
		
		
		
		ofNoFill();
		
		ofPushMatrix();
		ofTranslate(pos);

		ofDisableSmoothing();
		
		ofColor col;
		
		if(rainbows) {
			
			ofSetLineWidth(size*5);
			col.setHsb((int)rotation%255, 250,255);
			
		}else {
			col = colour;
			ofSetLineWidth(2);
		}
		
		ofSetColor(col);
		
		ofPushMatrix();
		ofRotateZ(rotation);
		ofScale(masterScale,masterScale);
		if(points.size()==0) {
			ofSetCircleResolution(numsides);
			ofCircle(0,0,0,20 * size);
		} else {
			
			ofScale(20*size, 20*size);
			ofBeginShape();
			for(int i = 0; i<points.size(); i++) {
				ofPoint p = points[i];//ofPoint(ofRandom(-0.05,0.05), ofRandom(-0.05,0.05)) + ;
				ofVertex(p);
			}
			ofEndShape();
			
			
		}
		
		ofPopMatrix();

		ofSetLineWidth(1);
		//deque<LineSpike> &spikes = shape.spikes;
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
	
	void trigger16th(int sixteenth) {
		
		if(sixteenth>=sixteens.size()) return;
		
		if(sixteens[sixteenth] >0) {
			size = sixteens[sixteenth];
			addLineSpike();
		}
		
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
	
	ofColor colour = ofColor::white;
	
	bool enabled  = false;
	
	bool emittingSpikes = false;
	
	bool rainbows = false;
	
	int counter = 0;
	
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