// ****************************************************************************
//
//                             Random number generator
//
// ****************************************************************************

#ifndef _RAND_H
#define _RAND_H

#include <stdint.h>
#include <stdbool.h>

// random generator seed
extern uint32_t RandSeed;

// shift random generator seed
void RandShift();

// randomize random generator from ROSC counter
bool RandInitSeed();

// generate random number in full range
uint8_t RandU8();
uint16_t RandU16();
uint32_t RandU32();
inline int8_t RandS8() { return (int8_t)RandU8(); }
inline int16_t RandS16() { return (int16_t)RandU16(); }
inline int32_t RandS32() { return (int32_t)RandU32(); }

// generate float random number in range 0 (including) to 1 (excluding)
float RandFloat();

// generate double random number in range 0 (including) to 1 (excluding)
double RandDouble();

// generate random number in range 0 to MAX (including)
uint8_t RandU8Max(uint8_t max);
uint16_t RandU16Max(uint16_t max);
uint32_t RandU32Max(uint32_t max);
int8_t RandS8Max(int8_t max);
int16_t RandS16Max(int16_t max);
int32_t RandS32Max(int32_t max);

// generate decimal random number in range 0 (including) to MAX (excluding)
float RandFloatMax(float max);
double RandDoubleMax(double max);

// generate random number in range MIN to MAX (including)
// If MIN > MAX, then number is generated out of interval.
uint8_t RandU8MinMax(uint8_t min, uint8_t max);
uint16_t RandU16MinMax(uint16_t min, uint16_t max);
uint32_t RandU32MinMax(uint32_t min, uint32_t max);
int8_t RandS8MinMax(int8_t min, int8_t max);
int16_t RandS16MinMax(int16_t min, int16_t max);
int32_t RandS32MinMax(int32_t min, int32_t max);
float RandFloatMinMax(float min, float max);
double RandDoubleMinMax(double min, double max);

#endif // _RAND_H
