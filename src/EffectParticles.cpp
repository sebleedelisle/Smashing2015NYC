//
//  EffectParticles.cpp
//  LaserShow
//
//  Created by Seb Lee-Delisle on 16/03/2014.
//
//

#include "EffectParticles.h"


void EffectParticles :: makeParticleForPipe(int pipeindex) {
	if(pipeOrganData == NULL) return; 
	
	ParticleSystem &ps = *particleSystemManager.getParticleSystem();
	
	ParticleSystemSettings pss;
	pss.emitLifeTime = 0.1;
	pss.emitMode = PARTICLE_EMIT_BURST;
	pss.emitCount = 1;
	pss.renderer = new ParticleRendererLaserLine(6);
	pss.speedMin = 600 ;
	pss.speedMax = 650;
	pss.drag = 1;
	pss.gravity.set(0,500,0);
	
	pss.sizeStartMin = pss.sizeStartMax = 1;
	pss.sizeChangeRatio = 0.1;
	//pss.emitShape = &explodeMesh;
	pss.directionYVar = pss.directionZVar = 0;
	pss.directionY = 50;
	pss.directionX = -35;
	
	pss.hueStartMin = pss.hueStartMax = 0;
	pss.hueChange = 360;
	pss.saturationMin = pss.saturationMax = 255;
	pss.saturationEnd = 255;
	pss.brightnessStartMin = pss.brightnessStartMax =pss.brightnessEnd = 255;
	pss.lifeMin = pss.lifeMax = 1.7;
	pss.shimmerMin = 0;
	pss.timeSpeed = 0.7;
	//pss.doNotScale = true;
	
	ps.pos = pipeOrganData->pipes[pipeindex].top;
	ps.init(pss);
	
	
	
}

void EffectParticles:: makeRainbowBurst(ofPoint pos) {

	if(pipeOrganData == NULL) return;
	
	ParticleSystem &ps = *particleSystemManager.getParticleSystem();
	
	ParticleSystemSettings pss;
	pss.emitLifeTime = 0.1;
	pss.emitMode = PARTICLE_EMIT_BURST;
	pss.emitCount = 20;
	//pss.renderer = new ParticleRendererLaserLine(2);
	pss.renderer = new ParticleRendererLaser();
	//pss.renderer = new ParticleRendererShape();
	pss.speedMin = 800 ;
	pss.speedMax = 1600;
	pss.drag = 0.6;
	pss.gravity.set(0,500,0);
	
	pss.sizeStartMin = pss.sizeStartMax = 1;
	pss.sizeChangeRatio = 0.1;
	//pss.emitShape = &explodeMesh;
	pss.directionYVar = 180;
//	pss.directionZVar = 0;
//	pss.directionY = 50;
//	pss.directionX = 0;
//	pss.directionZ = 90;
//	pss.directionXVar = 30;
	
	
	pss.hueStartMin = pss.hueStartMax = 0;
	pss.hueChange = 360;
	pss.saturationMin = pss.saturationMax = 255;
	pss.saturationEnd = 255;
	pss.brightnessStartMin = pss.brightnessStartMax =pss.brightnessEnd = 255;
	pss.lifeMin = 0.1;
	pss.lifeMax = 0.3;
	pss.shimmerMin = 0;
	pss.timeSpeed = 1;
	//pss.doNotScale = true;
	
	ps.pos = pos;
	ps.init(pss);
	
	
	

	
}


void EffectParticles:: makeStarBurst(float timespeed ) {
	
	if(pipeOrganData == NULL) return; 
	
	
	int numpipes = pipeOrganData->pipes.size();
	
	for(int i =0; i<numpipes; i+=1) {
		
		ParticleSystem &ps = *particleSystemManager.getParticleSystem();
		
		ParticleSystemSettings pss;
		pss.emitLifeTime = 0.2;
		//pss.emitMode = PARTICLE_EMIT_BURST;
		pss.emitCount = 20;
		pss.renderer = new ParticleRendererLaser();
	//	pss.renderer = new ParticleRendererShape();
		
		
		pss.speedMin = 1000 ;
		pss.speedMax = 1650;
		pss.drag = 0.90;
		pss.gravity.set(0,600,0);
		
		pss.sizeStartMin = pss.sizeStartMax = 1;
		pss.sizeChangeRatio = 0.5;
		//pss.emitShape = &explodeMesh;
		pss.directionYVar = pss.directionZVar = 0;
		pss.directionX = -35;
		pss.directionXVar = 20;
		pss.directionZVar = 5;
		
		pss.hueStartMin = pss.hueStartMax = 0;
		pss.hueChange = 0;
		pss.saturationMin = pss.saturationMax = 0;
		pss.saturationEnd = 0;
		pss.brightnessStartMin = pss.brightnessStartMax =pss.brightnessEnd = 255;
		pss.lifeMin = 2;
		pss.lifeMax = 3;
		pss.shimmerMin = 0;
		pss.timeSpeed = timespeed;
	
		pss.emitDelay = ofRandom(0.1);

		ps.pos = pipeOrganData->pipes[i].bottom + ofPoint(0,100);
		ps.init(pss);
	}
	
	
}


void EffectParticles ::  setObjects(PipeOrganData* pipeorgandata, DomeData* domedata) {
	pipeOrganData = pipeorgandata;
	domeData = domedata; 
	
}

