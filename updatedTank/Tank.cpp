  /*
    Name: Ydidiya Assefa, NSHE 2001132517, section 1001, Assignment #5
    Description: produce a program that uses pointers to make char move
    Input: random value to pick a fish
    Output: swimming fishes in the tank 
*/
#include "Fish.h"
#include <iomanip> //For drawing the Tank
#include <cstdlib> //Used to flush the Tank
#include <iostream>

using namespace std;

//Updates the Tank by updating all of the Fish in it in the order that they entered the Tank. This function is implemented for you already.
void Tank::update()
{
	//Update all the fish in the Tank (Make them swim)
	  for (Fish* fish : fishList)
	 	fish->swim(this);   	// Let it swim
}

//Adds a fish to the Tank
void Tank::addFish(Fish *fish)
{
	//Add the fish to the tankArr using the fish's x and y positions
	//Add the Fish to the fishList vector
	int x = fish->getXPos();
	int y = fish->getYPos();
	tankArr[y][x] = fish;
	fishList.push_back(fish);
}

//Attempts to move the fish by the given amount in the x and y directions
 void Tank::moveFish(Fish *fish, int xMove, int yMove)
{
    //Find the positions that the fish wants to move to and it's current positions
    int oldXPos = fish->getXPos(); //Previous x position of the fish
    int oldYPos = fish->getYPos(); //Previous y position of the fish
    int newXPos = oldXPos + xMove; //Desired x position to move the fish to
    int newYPos = oldYPos + yMove; //Desired y position to move the fish to



    // check if fish goes out of bounds
    if ( newXPos<0||newXPos >= width || newYPos<0||newYPos >= height)
    {
        fish->onWallCollision();//execute when out of bounds
        return;
    }
    else if (tankArr[newYPos][newXPos]==NULL)// check if the new pos is open
    {
        tankArr[oldYPos][oldXPos] = NULL;//make the old null 
        tankArr[newYPos][newXPos] = fish;//fill in the new one
        fish->setPosition(newXPos, newYPos);//set position


    }
    else if (tankArr[newYPos][newXPos]->getDrawChar() == 'W')// if you run into wall fish
    {
        fish->onWallCollision();//excute the wall fish collision
    }
}

//Draws the tank and all of the fish inside of it. This is a helper function implemented for you.
void Tank::drawTank()
{
//Clear the screen
#ifdef _WIN32
	system("CLS");
#else
	cout << "\033[2J\033[1;1H";
#endif

	int i, j;
	cout << "|" << setfill('^') << setw(width + 1) << "|" << endl; //Draw the top of the tank
	for (i = 0; i < height; i++)
	{
		cout << "|"; //Draw the left wall of the tank
		for (j = 0; j < width; j++)
		{
			if (tankArr[i][j] != NULL) //If the space is not empty, draw the fish there
				cout << tankArr[i][j]->getDrawChar();
			else //Else if the space is empty, draw a blank space
				cout << " ";
		}
		cout << "|" << endl; //Draw the right wall of the tank
	}
	cout << "|" << setfill('_') << setw(width + 1) << "|" << endl; //Draw the bottom of the tank
}

//Constructor for the Tank
Tank::Tank(int width, int height)
{
	//Set the width and height members
	this->width = width;
	this->height = height;

	//Allocate the 2D array based on the width and height
	int i, j; //Iteration variables
			  
			  // Allocate all of the rows first
			  // Allocate the columns in each row next and initialize all the pointers to NULL
 tankArr=new TankObject**[height];
	for ( i = 0; i < height; i++)
	{
		// allocate the row pointers in this loop
			tankArr[i]=new TankObject*[width];
			for(j=0;j<width;j++)
			{
tankArr[i][j]=NULL;//allocate columns
			}
	}
}

//Destructor for the Tank
Tank::~Tank()
{
//Go through and deallocate all of the fish in the fishList. Then deallocate the 2D tankArr array
	//Deallocate each fish from the fishList
	//Deallocate each of the rows
	//Deallocate the column that held all of the rows
for(int i=0;i<fishList.size();i++)
{
	delete fishList[i];
}//deallocate members of fishlist
	for(int i=0; i<height;i++)
	{ 
		if(tankArr!=NULL)
		delete[]tankArr[i];
	}
		delete [] tankArr;
	tankArr=NULL;
 
}