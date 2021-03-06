//
//  PipeOrganData.cpp
//  LaserShow
//
//  Created by Seb Lee-Delisle on 11/03/2014.
//
//

#include "PipeOrganData.h"

PipeOrganData::PipeOrganData() {


	editable = false; 

	

};

void PipeOrganData::init(ofRectangle rect) {
	
	rect.scaleFromCenter(0.7,0.7);
	int numPipes = 22;
	
	for (int i = 0; i<numPipes; i++) {
		
		pipes.push_back(Pipe(i));
		Pipe& pipe = pipes[pipes.size()-1];
		
		pipe.setTop(ofMap(i,0,numPipes, rect.getLeft(), rect.getRight()), rect.getTop()+rect.getHeight()/3);
		pipe.setBottom(pipe.top.x, rect.getBottom()-rect.getHeight()/3);
		
		params.add(pipe.topParam);
		params.add(pipe.bottomParam);
		
		
	}
	
	//gui.setup(params, "pipeOrganData.xml");
	
	
	
	
	
};


void PipeOrganData::draw() {
	if(!editable) return; 
	
		
	for(int i = 0; i<pipes.size(); i++) {
		pipes[i].draw();
	
	}
	
	
	
	

}



void PipeOrganData::mouseDragged(int x, int y){
	if(!editable) return; 
	for(int i = 0; i<pipes.size(); i++) {
		pipes[i].mouseDragged(x, y);
		
	}
	
	
}

void PipeOrganData::mousePressed(int x, int y){
	if(!editable) return; 
	for(int i = 0; i<pipes.size(); i++) {
		// only click the first one it finds
		if (pipes[i].mousePressed(x, y)) break;
		
	}
	
	
}

void PipeOrganData::mouseReleased(int x, int y){
	if(!editable) return; 
	for(int i = 0; i<pipes.size(); i++) {
		pipes[i].mouseReleased(x, y);
		
	}
	
	save();
	
}


void PipeOrganData::save(){

	settings.serialize(params);
	settings.save("pipeOrganData.xml");
}



void PipeOrganData::load(){
	
	// how do we know if it loaded?
	if(settings.load("pipeOrganData.xml")) {
		settings.deserialize(params);
		for(int i = 0; i<pipes.size(); i++) {		
			pipes[i].copyDataFromParams();
		}
	}
	
}



