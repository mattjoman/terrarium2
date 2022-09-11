#include <iostream>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <future>
#include <chrono>
#include <thread>
#include <string>
#include <cstring>
#include <map>
#include "../core/simulation.h"
#include "../share/config.h"
#include "app.h"

std::string OUTPUT_PATH;

int is_dir(const char *path)
{
   struct stat statbuf;
   if (stat(path, &statbuf) != 0)
       return 0;
   return S_ISDIR(statbuf.st_mode);
}


std::string create_output_path(const char* output_path)
{
	std::string new_path;
	switch (output_path[0]) {
		case '/':
		{
			new_path = output_path;
			if (is_dir(output_path)) {
				if (new_path.back() != '/') {
					new_path += '/';
				}
				new_path += "output.dat";
			}
			break;
		}
		default:
		{
			char cwd[64];
			getcwd(cwd, sizeof(cwd));
			new_path += cwd;
			new_path += '/';
			new_path += output_path;
			char new_path_array[new_path.size()+1];
			strcpy(new_path_array, new_path.c_str());

			if (is_dir(new_path_array)) {
				if (new_path.back() != '/') {
					new_path += '/';
				}
				new_path += "output.dat";
			}
			break;
		}
	}
	return new_path;
}



void run_simulation(const char* output_path_arg)
{
	/* Process the output path */
	OUTPUT_PATH = create_output_path(output_path_arg);
	std::cout << OUTPUT_PATH << std::endl;

	// in shared memory:
	bool *is_finished = new bool(false);
	int *current_timestep = new int(0);
	int *current_population = new int(0);
	int *cum_population = new int(0);

	// promise and future
	std::promise<int> sim_exit_code;
	std::future<int> sim_exit_code_future = sim_exit_code.get_future();
	
	// start simulation
	std::thread sim_thread(simulation, std::move(sim_exit_code), is_finished, current_timestep, current_population, cum_population);
	
	std::cout << std::endl;
	extern int TIMESTEPS;
	while (!*is_finished) {
		std::cout << "Timestep: " << *current_timestep << "/" << TIMESTEPS << "\tPopulation: " << *current_population << "\r" << std::flush;
		std::this_thread::sleep_for(std::chrono::milliseconds(5));
	}

	int exit = sim_exit_code_future.get();
	sim_thread.join();

	/* Review the simulation */
	std::cout << std::endl;
	switch (exit) {
	case 0:
		std::cout << "Exit code 0: Simulation completed successfully." << std::endl;
		break;
	case 1:
		std::cout << "Exit code 1: Simulation stopped early due to high population." << std::endl;
		break;
	case 2:
		std::cout << "Exit code 2: Simulation stopped early because everything died." << std::endl;
		break;
	default:
		break;
	}
	std::cout << std::endl;

	/* Clean up heap variables */
	delete is_finished;
	delete current_timestep;
	delete current_population;
	delete cum_population;
}


void display_params()
{
	std::cout << "Here are the params" << std::endl;
}


void edit_param(std::string param_name, int new_value)
{
	return;
}

void print_file(std::string file_path)
{
	std::fstream file;
	file.open(file_path, std::ios::in);
	if (file.is_open())
	{
		std::string line;
		while (getline(file, line))
		{
			std::cout << line << std::endl;
		}
	}
}
