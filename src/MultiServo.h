#ifndef MultiServo_h
#define MultiServo_h
    
#include <Arduino.h>
#include <Servo.h>
	
#define minS 500
#define maxS 2500
  
class UpgradeServo {
	public :	
	UpgradeServo();
	UpgradeServo(int pin);
	UpgradeServo(int pin,int min,int max);
	void setMinMax(int min, int max);
	int getPin();
	void setPin(int pin);	
	bool isAttach();
	void attach();
	void detach();	
	void setPos(double a);
	double getPos();
	void addToPos(double a);
	bool aprochToPos(double a, double pas);
	
	private :
	int _pin;
    Servo _s;
    double _pos;
	bool _attachState;
	int _min;
	int _max;
};
	
	
class MultiServo {
	
	public:
	MultiServo(int nbServo);
	MultiServo(int nbServo, int* pins);
	int getNbServo();
	void init(int pins[]);
	void setInstantPos(double* pos);
	void setPos(double* pos);
	void update(int d, double pas);
	void getPos(double* pos);
	UpgradeServo getServo(int id);
	
	private:
	int _nbServo;
	UpgradeServo* _s;
	double* _tarjetPos;
	
};


    
#endif