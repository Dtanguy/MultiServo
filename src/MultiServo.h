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
	void setPosAdd(double a);
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
	void init(int pins[]);	
	
	void setBrutPos(double pos[]);
	void setBrutPosAll(double pos);
	
	void setPos(double pos[]);
	void setPos(int id, double pos);
	void setPosAdd(int id, double pos);
	void getPos(double pos[]);	
	char* getPosChar();
	
	void update(int d, double pas);
	void updateOnce(double pas);
	
	int size();
	UpgradeServo getServo(int id);
	
	private:
	int _nbServo = 0;
	UpgradeServo _s[50];
	double _tarjetPos[50];
	
};

    
#endif