#include "Schrittmotor.h"
#include <wiringPi.h>

Schrittmotor::Schrittmotor(int A, int B, int C, int D)
{
	pinA = A;
	pinB = B;
	pinC = C;
	pinD = D;
	pinMode(pinA, OUTPUT);
	pinMode(pinB, OUTPUT);
	pinMode(pinC, OUTPUT);
	pinMode(pinD, OUTPUT);
	digitalWrite(pinA, LOW);
	digitalWrite(pinB, LOW);
	digitalWrite(pinC, LOW);
	digitalWrite(pinD, LOW);
}

Schrittmotor::~Schrittmotor()
{
}

void Schrittmotor::StepLeft(void) {
	// Step 1
	digitalWrite(pinD, HIGH);
	delayMicroseconds(MOTORDELAYTIME);
	digitalWrite(pinD, LOW);
	// Step 2
	digitalWrite(pinD, HIGH);
	digitalWrite(pinC, HIGH);
	delayMicroseconds(MOTORDELAYTIME);
	digitalWrite(pinD, LOW);
	digitalWrite(pinC, LOW);
	// Step 3
	digitalWrite(pinC, HIGH);
	delayMicroseconds(MOTORDELAYTIME);
	digitalWrite(pinC, LOW);
	// Step 4
	digitalWrite(pinB, HIGH);
	digitalWrite(pinC, HIGH);
	delayMicroseconds(MOTORDELAYTIME);
	digitalWrite(pinB, LOW);
	digitalWrite(pinC, LOW);
	// Step 5
	digitalWrite(pinB, HIGH);
	delayMicroseconds(MOTORDELAYTIME);
	digitalWrite(pinB, LOW);
	// Step 6
	digitalWrite(pinA, HIGH);
	digitalWrite(pinB, HIGH);
	delayMicroseconds(MOTORDELAYTIME);
	digitalWrite(pinA, LOW);
	digitalWrite(pinB, LOW);
	// Step 7
	digitalWrite(pinA, HIGH);
	delayMicroseconds(MOTORDELAYTIME);
	digitalWrite(pinA, LOW);
	// Step 8
	digitalWrite(pinD, HIGH);
	digitalWrite(pinA, HIGH);
	delayMicroseconds(MOTORDELAYTIME);
	digitalWrite(pinD, LOW);
	digitalWrite(pinA, LOW);
}

void Schrittmotor::StepRight() {
	// Step 8
	digitalWrite(pinD, HIGH);
	digitalWrite(pinA, HIGH);
	delayMicroseconds(MOTORDELAYTIME);
	digitalWrite(pinD, LOW);
	digitalWrite(pinA, LOW);
	// Step 7
	digitalWrite(pinA, HIGH);
	delayMicroseconds(MOTORDELAYTIME);
	digitalWrite(pinA, LOW);
	// Step 6
	digitalWrite(pinA, HIGH);
	digitalWrite(pinB, HIGH);
	delayMicroseconds(MOTORDELAYTIME);
	digitalWrite(pinA, LOW);
	digitalWrite(pinB, LOW);
	// Step 5
	digitalWrite(pinB, HIGH);
	delayMicroseconds(MOTORDELAYTIME);
	digitalWrite(pinB, LOW);
	// Step 4
	digitalWrite(pinB, HIGH);
	digitalWrite(pinC, HIGH);
	delayMicroseconds(MOTORDELAYTIME);
	digitalWrite(pinB, LOW);
	digitalWrite(pinC, LOW);
	// Step 3
	digitalWrite(pinC, HIGH);
	delayMicroseconds(MOTORDELAYTIME);
	digitalWrite(pinC, LOW);
	// Step 2
	digitalWrite(pinD, HIGH);
	digitalWrite(pinC, HIGH);
	delayMicroseconds(MOTORDELAYTIME);
	digitalWrite(pinD, LOW);
	digitalWrite(pinC, LOW);
	// Step 1
	digitalWrite(pinD, HIGH);
	delayMicroseconds(MOTORDELAYTIME);
	digitalWrite(pinD, LOW);

}

void Schrittmotor::StepLeftSequenz()
{
	for (int i = 0; i < 8; i++) {
		digitalWrite(pinA, seq[i][0]);
		digitalWrite(pinB, seq[i][1]);
		digitalWrite(pinC, seq[i][2]);
		digitalWrite(pinD, seq[i][3]);
		delayMicroseconds(MOTORDELAYTIME);
		digitalWrite(pinA, LOW);
		digitalWrite(pinB, LOW);
		digitalWrite(pinC, LOW);
		digitalWrite(pinD, LOW);
	}
}

void Schrittmotor::StepRightSequenz()
{
	for (int i = 7; i >= 0; i--) {
		digitalWrite(pinA, seq[i][0]);
		digitalWrite(pinB, seq[i][1]);
		digitalWrite(pinC, seq[i][2]);
		digitalWrite(pinD, seq[i][3]);
		delayMicroseconds(MOTORDELAYTIME);
		digitalWrite(pinA, LOW);
		digitalWrite(pinB, LOW);
		digitalWrite(pinC, LOW);
		digitalWrite(pinD, LOW);
	}
}
