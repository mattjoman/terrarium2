#include "config.h"
#include <fstream>
#include <sstream>
#include <string>
#include <map>
#include <vector>
#include <string.h>

#include <iostream>
#include <unistd.h>


/* Globals */
int TIMESTEPS         = 50;
int MAX_POPULATION    = 1000;
int MAX_DEATHS        = 1000;
int MIN_DEATH_AGE     = 5;
int MAX_DEATH_AGE     = 10;
int MAX_HUNGER        = 3;
int BREEDING_DISTANCE = 2;
int MUNCHING_DISTANCE = 4;
int PREGNANCY_PERIOD  = 3;
int SPAWN_RADIUS      = 15;
int INITIAL_PREDATORS = 7;
int INITIAL_PREY      = 7;
