#include "bfio.h"

char output_buffer[OUTPUT_BUFFER_MAX] = {0};
static size_t buffer_end = 0;
void bfOutput(char c) {
	if (buffer_end + 1 >= OUTPUT_BUFFER_MAX)
		bfClean();
	output_buffer[buffer_end++] = c;
	output_buffer[buffer_end] = 0;
}
char bfInput() {
	bfClean();
	return INPUT_FUNC();
}
void bfPrint() {
	PRINT_FUNC(output_buffer);
}
void bfClean() {
	bfPrint();
	buffer_end = 0;
	output_buffer[buffer_end] = 0;
}