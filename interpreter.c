#include "interpreter.h"

static size_t file_size(FILE *fp) {
	fseek(fp, 0, SEEK_END);
	size_t sz = (size_t)ftell(fp);
	rewind(fp);
	return sz;
}
static char to_printable_ascii(char a) {
	return (32 <= a && a < 127) ? a : 32;
}

unsigned char* getCode(size_t* cp) {
	FILE* fp = fopen(srcfile, "r");
	if (!fp) {
		fprintf(stderr, "Error: %s\n", FILE_NOT_FOUND);
		exit(261);
	}
	unsigned char* codePtr = malloc(codeSize == 0 ? (file_size(fp) * 2) : codeSize * sizeof(char));
	if (codePtr == nullptr) {
		fclose(fp);
		fprintf(stderr, "Error: %s\n", MEM_APPLIC_FAILED);
		exit(262);
	}
	*cp = 0;
	int filechar;
	bool is_instruction = true;
	while ((filechar = fgetc(fp)) != EOF) {
		if (is_instruction) {
			switch (filechar) {
				case '+':
					if (*cp >= 2 && (codePtr[(*cp)-2] == '+' && codePtr[(*cp)-1] != 255)) {
						codePtr[*cp-1]++;
					} else {
						codePtr[(*cp)++] = filechar;
						codePtr[(*cp)++] = 1;
					}
				break;
				case '-':
					if (*cp >= 2 && (codePtr[(*cp)-2] == '-' && codePtr[(*cp)-1] != 255)) {
						codePtr[*cp-1]++;
					} else {
						codePtr[(*cp)++] = filechar;
						codePtr[(*cp)++] = 1;
					}
				break;
				case '>':
					if (*cp >= 2 && (codePtr[(*cp)-2] == '>' && codePtr[(*cp)-1] != 255)) {
						codePtr[*cp-1]++;
					} else {
						codePtr[(*cp)++] = filechar;
						codePtr[(*cp)++] = 1;
					}
				break;
				case '<':
					if (*cp >= 2 && (codePtr[(*cp)-2] == '<' && codePtr[(*cp)-1] != 255)) {
						codePtr[*cp-1]++;
					} else {
						codePtr[(*cp)++] = filechar;
						codePtr[(*cp)++] = 1;
					}
				break;
				case '[':
					codePtr[(*cp)++] = filechar;
				break;
				case ']':
					codePtr[(*cp)++] = filechar;
				break;
				case '.':
					codePtr[(*cp)++] = filechar;
				break;
				case ',':
					codePtr[(*cp)++] = filechar;
				break;
				case '\\':
					is_instruction = false;
				break;
			}
		} else {
			is_instruction = true;
		}
	}
	codePtr[*cp] = 0;
	fclose(fp);
	return codePtr;
}

void interpret() {
	size_t code_size;
	unsigned char* codePtr = getCode(&code_size);
	char* memPtr = calloc(memorySize , sizeof(char));
	if (memPtr == nullptr) {
		free(codePtr);
		fprintf(stderr, "Error: %s\n", MEM_APPLIC_FAILED);
		exit(263);
	}
	size_t* stackPtr = malloc(stackSize * sizeof(size_t));
	if (stackPtr == nullptr) {
		free(codePtr);
		free(memPtr);
		fprintf(stderr, "Error: %s\n", MEM_APPLIC_FAILED);
		exit(264);
	}
	char* mp = memPtr;
	size_t* sp = stackPtr;
	size_t* mode = nullptr;
	for (size_t pc = 0; pc < code_size; pc++) {
		if (pc >= code_size || mp < memPtr || mp >= memPtr + memorySize || sp < stackPtr || sp > stackPtr + stackSize) {
			fprintf(stderr, "Error: %s\n", ILLEGAL_MEMORY);
			exit(1);
		}
		if (debug_print) {
			printf("pc: %ld\n", pc);
			printf("code: ");
			for (size_t i = 0; i < code_size; i++) {
				if (i == pc) printf("{");
				if (codePtr[i] == '+' ||
					codePtr[i] == '-' ||
					codePtr[i] == '>' ||
					codePtr[i] == '<'
				) {
					printf("%c%d ", codePtr[i], codePtr[i+1]);
					if (i == pc) printf("} ");
					if (i+1 < code_size) i++;
				} else if (
					codePtr[i] == '[' ||
					codePtr[i] == ']' ||
					codePtr[i] == '.' ||
					codePtr[i] == ','
				) {
					printf("%c ", codePtr[i]);
					if (i == pc) printf("} ");
				}
			}
			printf("\n");
		}
		if (codePtr[pc] == ']') {
			sp--;
			if (mode != nullptr) {
				if (mode == sp) mode = nullptr;
			}
		}
		if (mode == nullptr) switch (codePtr[pc]) {
			case '+':
				(*mp) += codePtr[++pc];
			break;
			case '-':
				(*mp) -= codePtr[++pc];
			break;
			case '>':
				mp += codePtr[++pc];
			break;
			case '<':
				mp -= codePtr[++pc];
			break;
			case '.':
				Output(*mp);
			break;
			case ',':
				*mp = Input();
			break;
			case '[':
				*sp = pc;
			break;
			case ']':
				if ((*mp) != 0) pc = *sp;
			break;
		}
		if (codePtr[pc] == '[') {
			if (mode == nullptr) {
				if ((*mp) == 0) mode = sp;
			}
			sp++;
		}
		if (debug_printmem) {
			char mems[9] = {0};
			for (int i = 0; i < 9; i++) {
				char* address = mp+i-4;
				mems[i] = (address >= memPtr && address < memPtr + memorySize ) ? *address : 0;
			}
			printf("\nmem ptr: %ld / %p\n", mp - memPtr, mp);
			printf("|%d|%d|%d|%d (%d) %d|%d|%d|%d|\n",
				mems[0], mems[1], mems[2], mems[3], mems[4], mems[5], mems[6], mems[7], mems[8]
			);
			printf("|%c|%c|%c|%c (%c) %c|%c|%c|%c|\n",
				to_printable_ascii(mems[0]),
				to_printable_ascii(mems[1]),
				to_printable_ascii(mems[2]),
				to_printable_ascii(mems[3]),
				to_printable_ascii(mems[4]),
				to_printable_ascii(mems[5]),
				to_printable_ascii(mems[6]),
				to_printable_ascii(mems[7]),
				to_printable_ascii(mems[8])
			);
		}
		if (debug) {
			(void)getchar();
		}
	}
	free(codePtr);
	free(memPtr);
	free(stackPtr);
}