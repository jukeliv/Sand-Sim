#define SPEED 1

#define WIDTH 100
#define HEIGHT 100

#include "sim.h"

#include "tigr.h"

#include <stdlib.h>
#include <stdio.h>

Tigr* screen;

int sandState = 1;

int main(void)
{
    screen = tigrWindow(WIDTH, HEIGHT, "fluid 0.0v", TIGR_2X);
    while(!tigrClosed(screen))
    {
	int mouseX = 0;
	int mouseY = 0;
	int button = 0;
	tigrMouse(screen, &mouseX, &mouseY, &button);
	
	char c = tigrReadChar(screen);
	if(c == '1')
	    sandState = 1;
	else if(c == '2')
	    sandState = 2;

	if(button && mouseX >= 0 && mouseY >= 0)
	{
	    if(mouseX < WIDTH && mouseY <= HEIGHT)
	    {
		if(button == 1)
		    box[indexPos(mouseX, mouseY)] = sandState;
	    	else if(button == 4)
		    box[indexPos(mouseX, mouseY)] = 0;
	    }
	}

	for(int i = 0; i < SPEED; ++i)
	{
	    sim_step();
	}
	for(int y = 0; y < HEIGHT; ++y)
	{
	    for(int x = 0; x < WIDTH; ++x)
	    {
		int b = box[indexPos(x, y)];
		if(b == 1)
		    tigrPlot(screen, x, y, tigrRGB(250, 250, 0));
		else if(b == 2)
		    tigrPlot(screen, x, y, tigrRGB(150, 150, 25));
		else if(b == 0)
		    tigrPlot(screen, x, y, tigrRGB(220, 220, 255));
	    }
	}
	tigrUpdate(screen);
    }
}
