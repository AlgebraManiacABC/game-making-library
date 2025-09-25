#include "color.h"

bool gm_ColorEquals(gm_Color_t colorA, gm_Color_t colorB)
{
	return (colorA.r == colorB.r) &&
		(colorA.g == colorB.g) &&
		(colorA.b == colorB.b) &&
		(colorA.a == colorB.a);
}
