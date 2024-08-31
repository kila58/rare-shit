#pragma once
#define IA 16807
#define IM 2147483647
#define IQ 127773
#define IR 2836
#define NTAB 32
#define NDIV (1+(IM-1)/NTAB)
#define MAX_RANDOM_RANGE 0x7FFFFFFFUL

#define AM (1.0/IM)
#define EPS 1.2e-7
#define RNMX (1.0-EPS)

#ifndef M_PI
#define M_PI            3.14159265358979323846  // matches value in gcc v2 math.h
#endif

#define M_PI_F          ((float)(M_PI))

class C_RandomA
{
private:
	int        m_idum;
	int        m_iy;
	int        m_iv[NTAB];
	int        GenerateRandomNumber(void);

public:
	void    SetSeed(int iSeed);
	float    RandomFloat(float flMinVal = 0.0f, float flMaxVal = 1.0f);
};
