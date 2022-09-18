#include <unistd.h>
#include <stdio.h>
#include <iostream>
#include <string.h>
#include <getopt.h>
#include "app.h"

#define CWD_BUF_SIZE 64


void print_help()
{
	std::cout << "Here is some help..." << std::endl;
}

void print_params()
{
	extern int TIMESTEPS;
	extern int MUNCHING_DISTANCE;
	std::cout << std::endl;
	std::cout << "TIMESTEPS: " << TIMESTEPS << std::endl;
	std::cout << "MUNCHING_DISTANCE: " << MUNCHING_DISTANCE << std::endl;
	std::cout << std::endl;
}

int string_to_int(char *arg) {
	int counter = 0;
	char *arg_cpy = arg;
	while (*arg_cpy) {
		counter++;
		arg_cpy++;
	}

	int multiplier = 1;
	int total = 0;
	int x;
	for (int i = counter-1; i >= 0; i--) {
		x = arg[i] - '0';
		total += x * multiplier;
		multiplier *= 10;
	}
	return total;
}

int main(int argc, char** argv)
{


	if (argc < 2) {
		print_help();
		exit(0);
	}

	int c;
	int option_index = 0;
	const char *optstring = "hp";
	static struct option long_options[] = {
		{"TIMESTEPS", required_argument, 0, 't'},
		{"MUNCHING_DISTANCE", required_argument, 0, 'm'},
	};



	/* Command is terrarium run */
	if (strcmp(argv[1], "run") == 0) {
		int is_print_params = 0;

		while ((c = getopt_long(argc, argv, optstring, long_options, &option_index)) != -1) {
			switch (c) {
				case 'h':
					print_help();
					exit(0);
					break;
				case 'p':
					// set a variable in order to print the params (once they have all been set)
					is_print_params = 1;
					break;
				case 't':
					extern int TIMESTEPS;
					TIMESTEPS = string_to_int(optarg);
					break;
				case 'm':
					break;
				default:
					break;
			}
		}
		if (is_print_params) {
			print_params();
		}
		std::cout << "Preparing to run simulation..." << std::endl;
		const char* output_path_arg = "output.dat";
		run_simulation(output_path_arg);
		exit(0);
	}


	while ((c = getopt(argc, argv, optstring)) != -1) {
		switch (c) {
			case 'h':
				print_help();
				break;
			case 'p':
				print_params();
				break;
			default:
				break;
		}
	}

	return 1;
}
