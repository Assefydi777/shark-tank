#include "Fish.h"

//******************* VertiFish function implementations *******************
//Flips direction on collision with a wall and changes drawing char
void VertiFish::onWallCollision() 
{ 

}

//Moves the fish either up or down every frame, depending on which direction it is facing
void VertiFish::swim(Tank* tank) 
{ 
   
}

//******************* HorizontaFish function implementations *******************
//Turns around on collision with a wall and changes drawing char
void HorizontaFish::onWallCollision() 
{
	
}

//Moves the fish either right or left every frame depending on the direction it is facing
void HorizontaFish::swim(Tank* tank) 
{
	
}

//******************* WallFish function implementations *******************
void WallFish::onWallCollision() { /*Do nothing. This needs to exist for WallFish to not be abstract */ }
void WallFish::swim(Tank*) { /*Do nothing. This needs to exist for WallFish to not be abstract */ }