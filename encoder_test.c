#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

#include "encoder.h"

int main(int argc, char *argv[])
{
	int i;
	int j;
	int flag = 1;

	Data *d = malloc(sizeof(Data));
	if (d == NULL) {
		perror("Error creating data struct");
		return -1;
	}

	if (init_encoding(d, argc) < 0) {
		perror("Error during initialization");
		return -1;
	}

	if (argc < 2) {
		printf("Usage: %s <data_to_encode>\n", argv[0]);
		return -1;
	}

	/* Convert input arguments to binary and build binary array */
	for (i = 1; i < argc; i++) {
		for (j = 0; j < strlen(argv[i]); j++) {
			d->bin = conv_to_bin(argv[i][j], d->bin, 7);
			build_bin_array(d, 7, d->count);
			d->count += 8;
		}
	}

	/* Encode and print out data */
	encode_bin(d, flag);
	print_encoded_bin(d->count, d->encoded_bin);

	destroy(d);

	return 0;
}