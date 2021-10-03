//Assignment 5 : Virtual Aquarium Solution
//Author: Sam Black

#include <iostream>
#include <vector>
#include <cstdlib>
#include "Tank.h"
#include "Fish.h"

#ifdef _WIN32
#include <Windows.h>
#else
#include <time.h>
#include <unistd.h>
#endif

using namespace std;

//Constants for the size of the tank
const int TANK_WIDTH = 60;
const int TANK_HEIGHT = 12;

//Constants for drawing/ refresh rate
const unsigned int PROGRAM_DURATION = 100; //Approximate number of seconds that the program should run for
const unsigned int FPS = 15;
const unsigned long TOTAL_FRAMES = PROGRAM_DURATION * FPS;
const unsigned long SLEEP_TIME = 1000 / FPS;

int Fish::count = 0; //Initialize fish count to 0

void randomlyAddFish(Tank* tank, unsigned int, int fishCount = 10);

int main(int argc, char** argv)
{
    //Error check the command line arguments

    //Try to convert the seed to 
    int fishSeed = 16407; //Default seed for the aquarium
    if (argc == 2) //If the user specified a seed
    {
        try { fishSeed = atoi(argv[1]); }
        catch (exception& e)
        {
            cout << "Error, could not convert " << argv[1] << " to an int" << endl;
            return 1;
        }
    }
    else if (argc > 2)
    {
        cout << "ERROR: Usage is: ./virt_aqua [optional_seed]" << endl;
        return 1;
    }

    Tank* tank = new Tank(TANK_WIDTH, TANK_HEIGHT); //Create the fish Tank

    //***** Put all of the Fish into the Tank *****
    #ifndef _WIN32
        //int retVal;
        timespec sleepTime, remainingTime;
        sleepTime.tv_sec = 0;
        sleepTime.tv_nsec = 1000000 * SLEEP_TIME;
    #endif
    randomlyAddFish(tank, fishSeed);

    //DEBUG: You can add fish here to test if you'd like, just make sure to delete it when you're done
 
    unsigned long frameCounter = 0; //How many frames have passed
    while (frameCounter < TOTAL_FRAMES)
    {
        tank->update(); //Update all of the Fish in the Tank
        tank->drawTank(); //Draw the new Tank

        #ifdef _WIN32
        Sleep(SLEEP_TIME);
        #else
        //sleep(1);
        nanosleep(&sleepTime, &remainingTime);
        #endif
        frameCounter++; //Count this frame
    }

    //Deallocate the tank and all of the Fish in the Tank
    delete tank;

    return 0;
}

//Randomly fills the given tank with the amount of fish given and does not place fish on top of each other
void randomlyAddFish(Tank* tank, unsigned int seed, int fishCount)
{
    bool occupied[TANK_HEIGHT][TANK_WIDTH];
    int i, j;
    srand(seed); //Seed the random number generation

    //Initialize to all false
    for (i = 0; i < TANK_HEIGHT; i++)
        for (j = 0; j < TANK_WIDTH; j++)
            occupied[i][j] = false;

    //Go through and generate all of the fish
    int numToGenerate = TANK_WIDTH * TANK_HEIGHT / 2;
    numToGenerate = numToGenerate < fishCount ? numToGenerate : fishCount;

    int count = 0; //Count of how many fish were generated
    while (count < numToGenerate)
    {
        i = rand() % TANK_HEIGHT;
        j = rand() % TANK_WIDTH;

        while (occupied[i][j]) //Generate a new space while the currently generated space is filled with a fish
        {
            i = rand() % TANK_HEIGHT;
            j = rand() % TANK_WIDTH;
        }

        occupied[i][j] = true; //Mark that the generated space is occupied
        switch (rand() % 3) //Pick a random type of fish to generate
        {
            case 0:
                tank->addFish(new WallFish(j, i));
                break;
            case 1:
                tank->addFish(new HorizontaFish(j, i, rand() % 2 == 0));
                break;
            case 2:
                tank->addFish(new VertiFish(j, i, rand() % 2 == 0));
                break;
            default:
                tank->addFish(new HorizontaFish(j, i, rand() % 2 == 0));
                break;
        }

        count++;
    }
}
