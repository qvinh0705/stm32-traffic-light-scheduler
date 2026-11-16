#ifndef INC_TRAFFIC_LIGHT_H_
#define INC_TRAFFIC_LIGHT_H_

typedef enum { TL_OFF = 0, TL_RED, TL_AMBER, TL_GREEN } tl_color_t;

void traffic_set(int line, tl_color_t color);   // line = 1 hoặc 2

#endif
