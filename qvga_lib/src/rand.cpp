// ****************************************************************************
//
//                             Random number generator
//
// ****************************************************************************

#include "qvga/rand.h"
#include "hardware/structs/rosc.h"

// random generator seed
uint32_t RandSeed;

// shift random generator seed
void RandShift()
{
	RandSeed = RandSeed*214013 + 2531011;
}

// randomize random generator from ROSC counter
bool RandInitSeed()
{
	int i;
	for (i = 32; i > 0; i--) RandSeed = (RandSeed << 1) | (rosc_hw->randombit & 1);
	i = (RandU8() & 0x1f) + 5;
	for (; i > 0; i--) RandShift();
	return true;
}

// random auto init
bool RandAutoInit = RandInitSeed();

// ============================================================================
//                  generate random number in full range
// ============================================================================

uint8_t RandU8()
{
	RandShift();
	return (uint8_t)(RandSeed >> 24);
}

uint16_t RandU16()
{
	RandShift();
	return (uint16_t)(RandSeed >> 16);
}

uint32_t RandU32()
{
	RandShift();
	uint32_t k = RandSeed;
	RandShift();
	return (k & 0xffff0000) | (RandSeed >> 16);
}

// ============================================================================
//     generate float random number in range 0 (including) to 1 (excluding)
// ============================================================================

float RandFloat()
{
	RandShift();
	return (float)(RandSeed >> (32-24))*(1.0f/0x1000000);
}

// ============================================================================
//    generate double random number in range 0 (including) to 1 (excluding)
// ============================================================================

double RandDouble()
{
	RandShift();
	return (double)RandSeed*(1.0/0x100000000ULL);
}

// ============================================================================
//         generate random number in range 0 to MAX (including)
// ============================================================================

uint8_t RandU8Max(uint8_t max)
{
	uint8_t res;
	uint8_t mask;

	// zero maximal value
	if (max == 0) return 0;

	// prepare mask
	res = 0xff;
	do {
		mask = res;
		res >>= 1;
	} while (res >= max);

	// generate random number
	do {
		res = RandU8() & mask;
	} while (res > max);

	return res;
}

uint16_t RandU16Max(uint16_t max)
{
	uint16_t res;
	uint16_t mask;

	// zero maximal value
	if (max == 0) return 0;

	// prepare mask
	res = 0xffff;
	do {
		mask = res;
		res >>= 1;
	} while (res >= max);

	// generate random number
	do {
		res = RandU16() & mask;
	} while (res > max);

	return res;
}

uint32_t RandU32Max(uint32_t max)
{
	uint32_t res;
	uint32_t mask;

	// zero maximal value
	if (max == 0) return 0;

	// prepare mask
	res = 0xffffffff;
	do {
		mask = res;
		res >>= 1;
	} while (res >= max);

	// generate random number
	do {
		res = RandU32() & mask;
	} while (res > max);

	return res;
}

int8_t RandS8Max(int8_t max)
{
	if (max >= 0)
		return (int8_t)RandU8Max((uint8_t)max);
	else
		return -(int8_t)RandU8Max((uint8_t)-max);
}

int16_t RandS16Max(int16_t max)
{
	if (max >= 0)
		return (int16_t)RandU16Max((uint16_t)max);
	else
		return -(int16_t)RandU16Max((uint16_t)-max);
}

int32_t RandS32Max(int32_t max)
{
	if (max >= 0)
		return (int32_t)RandU32Max((uint32_t)max);
	else
		return -(int32_t)RandU32Max((uint32_t)-max);
}

// ============================================================================
//   generate float random number in range 0 (including) to MAX (excluding)
// ============================================================================

float RandFloatMax(float max) { return RandFloat() * max; }

// ============================================================================
//   generate double random number in range 0 (including) to MAX (excluding)
// ============================================================================

double RandDoubleMax(double max) { return RandDouble() * max; }

// ============================================================================
//        generate random number in range MIN to MAX (including)
// ============================================================================
// If MIN > MAX, then number is generated out of interval.

uint8_t RandU8MinMax(uint8_t min, uint8_t max)
{
	return RandU8Max(max - min) + min;
}

uint16_t RandU16MinMax(uint16_t min, uint16_t max)
{
	return RandU16Max(max - min) + min;
}

uint32_t RandU32MinMax(uint32_t min, uint32_t max)
{
	return RandU32Max(max - min) + min;
}

int8_t RandS8MinMax(int8_t min, int8_t max)
{
	return (int8_t)RandU8Max(max - min) + min;
}

int16_t RandS16MinMax(int16_t min, int16_t max)
{
	return (int16_t)RandU16Max(max - min) + min;
}

int32_t RandS32MinMax(int32_t min, int32_t max)
{
	return (int32_t)RandU32Max(max - min) + min;
}

float RandFloatMinMax(float min, float max)
{
	return RandFloatMax(max - min) + min;
}

double RandDoubleMinMax(double min, double max)
{
	return RandDoubleMax(max - min) + min;
}
