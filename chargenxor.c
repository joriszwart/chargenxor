#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
	FILE *chargen, *customfont, *output;
	unsigned int offset = 0;
	unsigned char in1, in2, out;

	if(argc < 3) {
		printf("chargenxor v1.0 - xor a custom CBM font with the default chargen font for better compression\n\n");
		printf("Usage: chargenxor <customfont> <outputfile>\n");
		return EXIT_SUCCESS;
	}

	if((chargen = fopen("chargen", "rb")) == NULL) {
		perror("cannot open 'chargen'");
		return EXIT_FAILURE;
	}

	if((customfont = fopen(argv[1], "rb")) == NULL) {
		perror("cannot open input file");
		return EXIT_FAILURE;
	}

	if((output = fopen(argv[2], "wb")) == NULL) {
		perror("cannot open output file");
		return EXIT_FAILURE;
	}

	/* transform the file */
	printf("offset | chargen | custom font | result\n");
	while(fread(&in1, sizeof(in1), 1, customfont) > 0) {
		if(fread(&in2, sizeof(in2), 1, chargen) == 0) {
			perror("cannot read from chargen file");
		}

		out = in1 ^ in2;

		printf(" $%04x |    %02x   |      %02x     |   %02x\n", offset++, (unsigned int)in2, (unsigned int)in1, (unsigned int)out);

		fwrite(&out, sizeof(out), 1, output);
	}

	fclose(chargen);
	fclose(customfont);
	fclose(output);

	return EXIT_SUCCESS;
}
