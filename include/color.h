#ifndef COLOR_H
#define COLOR_H

#include <stdbool.h>

typedef struct gm_Color_s
{
	float r, g, b, a;

}	gm_Color_t;

#define GM_COLOR_BLACK ((gm_Color_t){0.0f,0.0f,0.0f,1.0f})
#define GM_COLOR_WHITE ((gm_Color_t){1.0f,1.0f,1.0f,1.0f})

bool gm_ColorEquals(gm_Color_t, gm_Color_t);

#endif
