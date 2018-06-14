#include "SDL.h"
 
int main(int argc, char **argv)
{
  if(SDL_Init(SDL_INIT_VIDEO) &lt; 0)
   SDL_Log("Can't init %s", SDL_GetError());
  SDL_CreateWindow("Hi mundo!", 100, 100, 800, 600, 0);
  SDL_Delay(2000);<br />  return 0;
}