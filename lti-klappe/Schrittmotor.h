#ifndef	__Schrittmotor_H__
#define	__Schrittmotor_H__

#define MOTORDELAYTIME 5000

class Schrittmotor
{
public:
	Schrittmotor(int A,int B,int C,int D);
	~Schrittmotor();
	void StepLeft(void);
	void StepRight(void);
	void StepLeftSequenz(void);
	void StepRightSequenz(void);

private:
	int pinA, pinB, pinC, pinD;  // die 4 GPIO des Motortreibers

	int seq[8][4] = {			// die Schaltsequenz fuer den Motor
		{ 0,0,0,1 },
		{ 0,0,1,1 },
		{ 0,0,1,0 },
		{ 0,1,1,0 },
		{ 0,1,0,0 },
		{ 1,1,0,0 },
		{ 1,0,0,0 },
		{ 1,0,0,1 },
	};

};

#endif

