#include <iostream>
#include <string>

struct Conf {
   int TIMESTEPS;
   int MAX_POPULATION;
   int MAX_DEATHS;
   int MIN_DEATH_AGE;
   int MAX_DEATH_AGE;
   int MAX_HUNGER;
   int BREEDING_DISTANCE;
   int MUNCHING_DISTANCE;
   int PREGNANCY_PERIOD;
   int SPAWN_RADIUS;
   int INITIAL_PREDATORS;
   int INITIAL_PREY;
};

std::string create_output_path(const char* output_path);

void run_simulation(const char* output_path);

void display_params();

void edit_param(std::string param_name, int new_val);

void print_file(std::string file_path);
