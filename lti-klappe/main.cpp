#include <wiringPi.h>
#include <mcp23017.h>
#include <iostream>
#include <string>
#include "Schrittmotor.h"

#define ENDSCHALTER_L 75
#define ENDSCHALTER_R 74
#define LED_ENDSCHALTER_L 0
#define LED_ENDSCHALTER_R 2

#define MOT_PIN_A 81
#define MOT_PIN_B 80
#define MOT_PIN_C 79
#define MOT_PIN_D 78

#define MAXSTEPS 137

using namespace std;

void setStatusLed(void) {
//	cout << "in SetStatusLed\n";
	if(digitalRead(ENDSCHALTER_L)) {
		digitalWrite(LED_ENDSCHALTER_L,HIGH);
//		cout << "Endschalter_L Pin: " << ENDSCHALTER_L << " ist HIGH\n";
	}
	else {
		digitalWrite(LED_ENDSCHALTER_L,LOW);
//		cout << "Endschalter_L Pin: " << ENDSCHALTER_L << " ist LOW\n";
	}	
		
	if(digitalRead(ENDSCHALTER_R)) {
		digitalWrite(LED_ENDSCHALTER_R,HIGH);
//		cout << "Endschalter_R Pin: " << ENDSCHALTER_R << " ist HIGH\n";
	}
	else {
		digitalWrite(LED_ENDSCHALTER_R,LOW);
//		cout << "Endschalter_R Pin: " << ENDSCHALTER_R << " ist LOW\n";
	}
}


int main(int argc, char *argv[])
{
	string action;
	int x = 0;

	if(argc<2) {
	    cout << "Aufruf: lti_klappe innen bzw. lti_klappe aussen\n";
	    cout << "innen -> die Klappe in den Raum wird geoeffnet (Abluft in den Keller)\n";
	    cout << "aussen -> die Klappe nach aussen wird geoeffnet (Abluft zum Fenster hinaus)\n";
		cout << "status -> gibt 0 fuer innen und 1 fuer aussen zurueck, 99 wenn der Status nicht ermittelt werden konnte\n";
	    return 99;
	}

	wiringPiSetup();
	mcp23017Setup(70,0x20);
	pinMode(LED_ENDSCHALTER_L, OUTPUT);
	pinMode(LED_ENDSCHALTER_R, OUTPUT);
	pinMode(ENDSCHALTER_L, INPUT);
	pinMode(ENDSCHALTER_R, INPUT);
	
	Schrittmotor Motor(MOT_PIN_A,MOT_PIN_B,MOT_PIN_C,MOT_PIN_D);

	digitalWrite(LED_ENDSCHALTER_L,LOW);
	digitalWrite(LED_ENDSCHALTER_R,LOW);
	
	setStatusLed();

	action = argv[1];
	
	if(action == "innen") {
		while (digitalRead(ENDSCHALTER_L) != HIGH && x<=MAXSTEPS) {
//			cout << "in innen\n";
			Motor.StepLeft();
			setStatusLed();
			x++;
		}
		if (digitalRead(ENDSCHALTER_L) == LOW && x>= MAXSTEPS) {
//			cout << "Fehler bei lti_klappe innen\n";
			x=0;
			while (true) {
				digitalWrite(LED_ENDSCHALTER_L, HIGH);
				delay(1000);
				digitalWrite(LED_ENDSCHALTER_L, LOW);
				delay(1000);
			}
		}

		if (digitalRead(ENDSCHALTER_L) == HIGH) {
			digitalWrite(LED_ENDSCHALTER_L, HIGH);
//			cout << "Steps: " << steps << endl;
			return 0;
		}
	}

	if (action == "aussen") {
		while (digitalRead(ENDSCHALTER_R) != HIGH && x<=MAXSTEPS) {
			Motor.StepRight();
			x++;
			setStatusLed();
		}
		if (digitalRead(ENDSCHALTER_R) == LOW && x>=MAXSTEPS) {
//			cout << "Fehler bei lti_klappe aussen\n";
			x=0;
			while (true) {
				digitalWrite(LED_ENDSCHALTER_R, HIGH);
				delay(1000);
				digitalWrite(LED_ENDSCHALTER_R, LOW);
				delay(1000);
			}
		}
		if (digitalRead(ENDSCHALTER_R) == HIGH) {
			digitalWrite(LED_ENDSCHALTER_R, HIGH);
//			cout << "Steps: " << steps << endl;
			return 0;
		}
	}

	if (action == "status") {
		if (digitalRead(ENDSCHALTER_L) == HIGH) {
			cout << "0\n";
			return 0;
		}
		if (digitalRead(ENDSCHALTER_R) == HIGH) {
			cout << "1\n";
			return 1;
		}
		cout << "99\n";
		return 99;
    }
   	return 0;
}
