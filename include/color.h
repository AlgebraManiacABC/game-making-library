#ifndef COLOR_H
#define COLOR_H

typedef struct gm_Color_s
{
	float r, g, b, a;

}	gm_Color;

static const gm_Color GM_COLOR_BLACK = { 0.0, 0.0, 0.0, 0.0 };
static const gm_Color GM_COLOR_WHITE = { 1.0, 1.0, 1.0, 1.0 };

bool gm_ColorEquals(gm_Color, gm_Color);

#endif
