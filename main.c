#include "tigr.h"
#include <stdlib.h>
#include <stdio.h>

#if __linux__
#include <unistd.h>
#define wait(s) sleep(s)
#else
#include <windows.h>
#define wait(s) Sleep(s*1000)
#endif

#define WIDTH 200
#define HEIGHT 200

char box[HEIGHT*WIDTH] = {0};

inline int indexPos(int x, int y)
{
    return y * HEIGHT + x;
}

void step()
{
    for(int y = HEIGHT; y >= 0; --y)
    {
	for(int x = 0; x < WIDTH; ++x)
	{

	    if(!box[indexPos(x, y)])
		continue;

	    if(y+1 >= HEIGHT)
		continue;
	    else if(!box[indexPos(x, y+1)])
	    {
		box[indexPos(x, y+1)] = 1;
		box[indexPos(x, y)] = 0;
		continue;
	    }

	    if(x+1 >= WIDTH)
		continue;
	    else if(!box[indexPos(x+1, y+1)])
	    {
		box[indexPos(x+1, y+1)] = 1;
		box[indexPos(x, y)] = 0;
	    }

	    if(x-1 <= 0)
		continue;
	    else if(!box[indexPos(x-1, y+1)])
	    {
		box[indexPos(x-1, y+1)] = 1;
		box[indexPos(x, y)] = 0;
	    }
	}
    }
}

Tigr* screen;

int main(void)
{
    screen = tigrWindow(WIDTH, HEIGHT, "fluid 0.0v", TIGR_2X);
    while(!tigrClosed(screen))
    {
	int mouseX = 0;
	int mouseY = 0;
	int button = 0;
	tigrMouse(screen, &mouseX, &mouseY, &button);

	if(button && mouseX >= 0 && mouseY >= 0)
	{
	    if(mouseX < WIDTH && mouseY <= HEIGHT)
	    {
		if(button == 1)
		    box[indexPos(mouseX, mouseY)] = 1;
	    	else if(button == 4)
		    box[indexPos(mouseX, mouseY)] = 0;
	    }
	}

	step();
	for(int y = 0; y < HEIGHT; ++y)
	{
	    for(int x = 0; x < WIDTH; ++x)
	    {
		int b = box[indexPos(x, y)];
		if(b)
		    tigrPlot(screen, x, y, tigrRGB(150, 150, 0));
		if(!b)
		    tigrPlot(screen, x, y, tigrRGB(220, 220, 255));
	    }
	}
	tigrUpdate(screen);
    }
}
