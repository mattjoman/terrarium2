#include <unistd.h>
#include <stdio.h>
#include <iostream>
#include <string.h>
#include "app.h"

#define CWD_BUF_SIZE 64



int main(int argc, char** argv)
{

	if (argc < 2) {
		/* Run help function */
		std::cout << "Invalid, here's some help..." << std::endl;
		exit(0);
	}

	if (strcmp(argv[1], "run") == 0) {
		/* Command is terrarium run */
		std::cout << "Preparing to run simulation..." << std::endl;

		/* Prepare and run the simulation... */
		const char* output_path_arg = "output.dat";
		run_simulation(output_path_arg);
		exit(0);
	}

	std::cout << "Invalid arguments" << std::endl;

	/* Command is terrarium (don't run) */

	return 1;
}
