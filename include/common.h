#ifndef INF_DRAW_COMMON_H_
#define INF_DRAW_COMMON_H_

struct d_point_t
{
 float x; float y;
};

float min(float,float); 
float max(float,float);

#define LINE_WIDTH 2
#define DRAW_PERIOD 10 //milliseconds

#endif
