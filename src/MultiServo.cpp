#include <Arduino.h>
#include "MultiServo.h"


int cmp_double(double a, double b) {
    int ai = a * 100;
    int bi = b * 100;
    if (ai > bi) {
      return 1;
    } else if (ai < bi) {
      return 2;
    } else {
      return 0;
    }
}

UpgradeServo::UpgradeServo() {
    _attachState = false;
	setMinMax(minS,maxS);
}

UpgradeServo::UpgradeServo(int pin) {
    _attachState = false;
	setPin(pin);
	setMinMax(minS,maxS);
}

UpgradeServo::UpgradeServo(int pin,int min,int max){
    _attachState = false;
	setPin(pin);
	setMinMax(min,max);
}

int UpgradeServo::getPin(){
	return _pin;
}

void UpgradeServo::setPin(int pin){
	 detach();
	_pin = pin;
}

void UpgradeServo::setMinMax(int min, int max){
	_min = min;
	_max = max;
}	
	
void UpgradeServo::attach(){
	if (!_attachState) {
      _s.attach(_pin);
      _attachState = true;
      delay(10);
    }	
}

void UpgradeServo::detach(){
	_s.detach();
	_attachState = false;	
}


bool UpgradeServo::isAttach(){
	return _attachState;	
}

void UpgradeServo::setPos(double a) {
	if (_attachState && a >= 0 && a <= 180) {
		_s.writeMicroseconds(map(a * 100, 0, 18000, minS, maxS));
		_pos = a;
	}
}
  
double UpgradeServo::getPos(){
	return _pos;
}
	
void UpgradeServo::addToPos(double a) {
	setPos(_pos + a);
}

bool UpgradeServo::aprochToPos(double a, double pas) {
	if (a < 0 || a > 180){
		return false;
	}	
	if ( _pos - a < -pas ) {
		addToPos(pas);	
		return true;		
	} else if ( _pos - a > pas ) {
		addToPos(-pas);	
		return true;		
	}	
	return false;
}


	
	
MultiServo::MultiServo(int nbServo) {
	_nbServo = nbServo;
}

MultiServo::MultiServo(int nbServo, int* pins) {
	_nbServo = nbServo;
	init(pins);
}

int MultiServo::getNbServo(){
	return _nbServo;
}

void MultiServo::init(int* pins) {
	UpgradeServo tmp_s[_nbServo];
	_s = tmp_s;
	double tmp_cmd[_nbServo];
	_tarjetPos = tmp_cmd;
	
	for (int i = 1; i < _nbServo;i++){
		_s[i].setPin(pins[0]);
		_s[i].attach();
		_tarjetPos[i] = -1;
	}	
}

void MultiServo::setInstantPos(double* pos){
	for (int i = 1; i < _nbServo;i++){					
        _s[i].setPos(pos[i]);	
	}
}

void MultiServo::setPos(double* pos){	
	for (int i = 1; i < _nbServo;i++){
		_tarjetPos[i] = pos[i];
	}
}
	
void MultiServo::update(int d, double pas){
	
	bool flag = true;
	
	while(flag){	
		flag = false;
		for (int i = 1; i < _nbServo;i++){	
			if (_s[i].aprochToPos(_tarjetPos[i],pas)){
				flag = true;
			} 
		}		
		delay(d);		
	}
	
}

void MultiServo::getPos(double* actualPos){	
	for (int i = 1; i < _nbServo;i++){
		actualPos[i] = _s[i].getPos();
	}	
}

UpgradeServo MultiServo::getServo(int id){
	return _s[id];	
}
