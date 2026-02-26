#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "typedef.h"
#include "error.h"
#include "setting.h"
#include "interpreter.h"

void version() {
	printf("version: %s\n",VERSION);
	exit(0);
}

void set_memsize(char* size) {
	int mem_size = atoi(size);
	if (mem_size == 0) {
		fprintf(stderr, "Error: %s\n", INVALID_VALUE);
		exit(257);
	}
	if (mem_size < MIN_MEM) {
		fprintf(stderr, "Error: %s\n", MEM_IS_TOO_SHORT);
		exit(258);
	}
	if (mem_size > MAX_MEM) {
		fprintf(stderr, "Error: %s\n", MEM_IS_TOO_LONG);
		exit(259);
	}
	memorySize = mem_size;
}

void set_stacksize(char* size) {
	int stack_size = atoi(size);
	if (stack_size == 0) {
		fprintf(stderr, "Error: %s\n", INVALID_VALUE);
		exit(266);
	}
	if (stack_size < MIN_STACK) {
		fprintf(stderr, "Error: %s\n", STACK_IS_TOO_SHORT);
		exit(267);
	}
	if (stack_size > MAX_STACK) {
		fprintf(stderr, "Error: %s\n", STACK_IS_TOO_LONG);
		exit(268);
	}
	stackSize = stack_size;
}

void set_codesize(char* size) {
	int code_size = atoi(size);
	if (code_size == 0) {
		fprintf(stderr, "Error: %s\n", INVALID_VALUE);
		exit(269);
	}
	codeSize = code_size;
}

int get_option_param(int* i, int argc) {
	int num = ++(*i);
	if (num >= argc) {
		fprintf(stderr, "Error: %s\n", NO_OPTION_PARAM);
		exit(265);
	}
	return num;
}

void help() {
	printf(
		"-V / --version         --- Get version number\n"
		"-H / --help            --- Get help\n"
		"-C / --auto-codesize   --- Automatically calculate code size\n"
		"-D / --debug           --- Toggle debug mode (step)\n"
		"-M / --debug-printmem  --- Toggle memory print\n"
		"-P / --debug-print     --- Print program execution status\n"
		"-O / --debug-print-outputbuffer\n"
		"                       --- Print output buffer\n"
		"-E / --execute         --- Read code directly from the command line\n"
		"-m / --mem       [int] --- Set the memory size\n"
		"-s / --stacksize [int] --- Set the stack size\n"
		"-c / --codesize  [int] --- Set the code buffer size\n"
		"-r / --debug-callsystem [string]\n"
		"                       --- Every time the code is executed,\n"
		"                           the system is called once.\n"
	);
	exit(0);
}

int main(int argc, char* argv[]) {
	for (int i = 1; i < argc; ++i) {
		if (argv[i][0] == '-') {
			switch (argv[i][1]) {
				case '-':
					if (strcmp(argv[i], "--version") == 0) version();
					
					else if (strcmp(argv[i], "--help") == 0)  help();
					
					else if (strcmp(argv[i], "--auto-codesize") == 0)
						auto_calc_codesize = !auto_calc_codesize;
					
					else if (strcmp(argv[i], "--debug") == 0)
						debug = !debug;
					
					else if (strcmp(argv[i], "--debug-printmem") == 0)
						debug_printmem = !debug_printmem;
					
					else if (strcmp(argv[i], "--debug-print") == 0)
						debug_print = !debug_print;
					
					else if (strcmp(argv[i], "--debug-print-outputbuffer") == 0)
						debug_print_outputbuffer = !debug_print_outputbuffer;
					
					else if (strcmp(argv[i], "--execute") == 0)
						is_inline_code = !is_inline_code;
					
					
					else if (strcmp(argv[i], "--mem") == 0)
						set_memsize(argv[get_option_param(&i, argc)]);
					
					else if (strcmp(argv[i], "--stacksize") == 0)
						set_stacksize(argv[get_option_param(&i, argc)]);
					
					else if (strcmp(argv[i], "--codesize") == 0)
						set_codesize(argv[get_option_param(&i, argc)]);
					
					else if (strcmp(argv[i], "--debug-callsystem") == 0)
						callsys = argv[get_option_param(&i, argc)];
					
					else
					{
						fprintf(stderr, "Error: %s\n", NOT_EXIST_OPTION);
						exit(256);
					}
				break;
				
				case 'V':
					version();
				break;
				
				case 'H':
					help();
				break;
				
				case 'C':
					auto_calc_codesize = !auto_calc_codesize;
				break;
				
				case 'D':
					debug = !debug;
				break;
				
				case 'M':
					debug_printmem = !debug_printmem;
				break;
				
				case 'P':
					debug_print = !debug_print;
				break;
				
				case 'O':
					debug_print_outputbuffer = !debug_print_outputbuffer;
				break;
				
				case 'E':
					is_inline_code = !is_inline_code;
				break;
				
				
				case 'm':
					set_memsize(argv[get_option_param(&i, argc)]);
				break;
				
				case 's':
					set_stacksize(argv[get_option_param(&i, argc)]);
				break;
				
				case 'c':
					set_codesize(argv[get_option_param(&i, argc)]);
				break;
				
				case 'r':
					callsys = argv[get_option_param(&i, argc)];
				break;
				
				default:
				fprintf(stderr, "Error: %s\n", NOT_EXIST_OPTION);
				exit(256);
			}
			
		} else if (exists_srcfile) {
			fprintf(stderr, "Error: %s\n", DUPLICATE_SRCFILE);
			exit(255);
		} else {
			srcfile = argv[i];
			exists_srcfile = true;
		}
	}
	if (!exists_srcfile) {
		fprintf(stderr, "Error: %s\n", NO_INPUTFILE);
		exit(260);
	}
	interpret();
	return 0;
}
