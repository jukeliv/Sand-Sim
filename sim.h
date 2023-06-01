#ifndef SIM_H_
#define SIM_H_

/*
   0 - VOID
   1 - SAND
   2 - STATIC SAND
*/

char box[HEIGHT*WIDTH] = {0};

inline int indexPos(int x, int y)
{
    return y * HEIGHT + x;
}

void sim_step()
{
   for(int y = HEIGHT; y >= 0; --y)
    {
	for(int x = 0; x < WIDTH; ++x)
	{

	    if(!box[indexPos(x, y)] || box[indexPos(x, y)] == 2)
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
	    else if(!box[indexPos(x+1, y+1)] && !box[indexPos(x+1, y)])
	    {
		box[indexPos(x+1, y+1)] = 1;
		box[indexPos(x, y)] = 0;
	    }

	    if(x-1 <= 0)
		continue;
	    else if(!box[indexPos(x-1, y+1)] && !box[indexPos(x-1, y)])
	    {
		box[indexPos(x-1, y+1)] = 1;
		box[indexPos(x, y)] = 0;
	    }
	}
    }

}

#endif //SIM_H_
