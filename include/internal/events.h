#ifndef INTERNAL_EVENTS_H
#define INTERNAL_EVENTS_H

#define BITFIELD_CHECK(field,mask) ((field) & (mask))
#define BITFIELD_SET(field,mask) ((field) |= (mask))
#define BITFIELD_CLEAR(field,mask) ((field) &= ~(mask))

typedef enum gm_ButtonEventType_e
{
    GM_BUTTONEVENT_NONE = 0,
    GM_BUTTONEVENT_DOWN,
    GM_BUTTONEVENT_UP,

}   gm_ButtonEventType_t;

int gm_initializeInputStateArray();

void gm_destroyEventData();

#endif