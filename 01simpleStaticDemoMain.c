#include "graphics.h"
#include "ebentoak.h"
#include "soinua.h"
#include "text.h"
#include "imagen.h"
#include <stdio.h>
#include "Sarrera.h"
#define ERROR -1
int main(int argc, char * str[]) 
{
  if (sgHasieratu() == ERROR)
  {
    fprintf(stderr, "Unable to set 640x480 video: %s\n", SDL_GetError());
    return 0;
  }
  sarrera();
  sgItxi();
  return 0;
}

