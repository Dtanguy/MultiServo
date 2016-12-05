
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
	
void UpgradeServo::setPosAdd(double a) {
	setPos(_pos + a);
}

bool UpgradeServo::aprochToPos(double a, double pas) {
	if (a < 0 || a > 180){
		return false;
	}	
	if ( _pos - a < -pas ) {
		setPosAdd(pas);	
		return true;		
	} else if ( _pos - a > pas ) {
		setPosAdd(-pas);	
		return true;		
	}	
	return false;
}


	
	
MultiServo::MultiServo(int nbServo) {
	_nbServo = nbServo;
}

void MultiServo::init(int pins[]) {		
	for (int i = 0; i < _nbServo;i++){
		_s[i].setPin(pins[i]);
		_s[i].attach();
		_tarjetPos[i] = -1;
	}	
}

int MultiServo::size(){
	return _nbServo;
}

void MultiServo::setBrutPos(double pos[]){
	for (int i = 0; i < _nbServo;i++){					
        _s[i].setPos(pos[i]);	
	}
}

void MultiServo::setBrutPosAll(double pos){
	for (int i = 0; i < _nbServo;i++){					
        _s[i].setPos(pos);	
	}
}

void MultiServo::setPos(double pos[]){	
	for (int i = 0; i < _nbServo;i++){
		_tarjetPos[i] = pos[i];
	}
}

void MultiServo::setPos(int id,double pos){		
	_tarjetPos[id] = pos;
}
	
void MultiServo::setPosAdd(int id,double pos){		
	_tarjetPos[id] += pos;
	if (_tarjetPos[id] < 0){
		_tarjetPos[id] = 0;
	} else if (_tarjetPos[id] > 180) {
		_tarjetPos[id] = 180;
	}
}
	
	
void MultiServo::update(int d, double pas){
	
	bool flag = true;
	
	while(flag){	
		flag = false;
		for (int i = 0; i < _nbServo;i++){	
			if (_s[i].aprochToPos(_tarjetPos[i],pas)){
				flag = true;
			} 
		}		
		delay(d);		
	}
	
}

void MultiServo::updateOnce(double pas){
	for (int i = 0; i < _nbServo;i++){	
		_s[i].aprochToPos(_tarjetPos[i],pas);
	}
}

void MultiServo::getPos(double actualPos[]){	
	for (int i = 0; i < _nbServo;i++){
		actualPos[i] = _s[i].getPos();
	}	
}


char* MultiServo::getPosChar(){	
	
	int nbmax = 30*_nbServo;
	char str[nbmax];
	for (int i = 0; i < nbmax;i++){
		str[i] = 0;
	}
	str[0] = '{';
	
	for (int i = 0; i < _nbServo;i++){
		
		char tmpstr[30];
		itoa(_s[i].getPos()*100,tmpstr,10);		
		
		char str3[3];
		str3[0]= ',';
		str3[1]= ' ';
		str3[2]= '\0';
		
		size_t len1 = strlen(str);
		size_t len2 = strlen(tmpstr);
		size_t len3 = strlen(str3);

		memcpy(str + len1, tmpstr, len2);
		memcpy(str + len1+len2, str3, len3);
		str[len1 + len2 + len3] = '\0';			
	}	
	
	size_t len = strlen(str);
	str[len-2] = '}';
	str[len-1] = '\0';		
	return str;
}

UpgradeServo MultiServo::getServo(int id){
	return _s[id];	
}
