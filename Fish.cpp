#include "Fish.h"

//******************* VertiFish function implementations *******************
//Flips direction on collision with a wall and changes drawing char
void VertiFish::onWallCollision()
{
    int x = 0;
    int y = 0;
    bool direction = !facingUp;
    VertiFish verticalFish(x, y, direction);
}

//Moves the fish either up or down every frame, depending on which direction it is facing
void VertiFish::swim(Tank *tank)
{
  
    Fish *fish;
    int xMove = 0;
    int yMove = 0;

    
    // as long as height of tank not reached swim vertical
    for (int i = 0; i < tank->getTankHeight(); i++)
    {
        tank->moveFish(fish, xMove, yMove + i);
    }
}

//******************* HorizontaFish function implementations *******************
//Turns around on collision with a wall and changes drawing char
 
void HorizontaFish::onWallCollision()
{
    int x = 0;
    int y = 0;
    bool direction = !facingRight;
    HorizontaFish horizontalFish(x, y, direction);
}

//Moves the fish either right or left every frame depending on the direction it is facing
void HorizontaFish::swim(Tank *tank)
{
    Fish *fish;
    int xMove = 0;
    int yMove = 0;
    // as long as height of tank not reached swim vertical
    for (int i = 0; i < tank->getTankWidth(); i++)
    {
        tank->moveFish(fish, xMove + i, yMove);
    }
}

//******************* WallFish function implementations *******************
void WallFish::onWallCollision()
{ /*Do nothing. This needs to exist for WallFish to not be abstract */
}
void WallFish::swim(Tank *)
{ /*Do nothing. This needs to exist for WallFish to not be abstract */
}