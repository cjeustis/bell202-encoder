#include <stdio.h>
#include <stdlib.h>

#include "encoder.h"

/* Initialize the struct */
int init_encoding(Data *d, int size)
{
	d->bin = (int *)malloc(size*sizeof(int));
	if (d->bin == NULL)
		return -1;

	d->encoded_bin = (int *)malloc(size*sizeof(int));
	if (d->encoded_bin == NULL)
		return -1;
	
	d->count = 0;
	d->num_i = 0;

	return 1;
}

/* Convert data to binary */
int *conv_to_bin(unsigned int val, int *retval, int size)
{
	int i, k;

	for (i = size; i >= 0; i--) {
		k = val >> i;
		if (k & 1) retval[i] = 1;
		else retval[i] = 0;
	}

	return retval;
}

/* Build binary array */
void build_bin_array(Data *d, int length, int position)
{
	int i;

	for (i = position; i < length+position; i++) {
		d->encoded_bin[i] = d->bin[i-position];
	}
}

/* Encode the binary data */
void encode_bin(Data *d, int flag)
{
	if (flag) {
		int i;
		int j;

		/* Encode binary - do bitstuffing */
		for (i = 0; i < d->count; i++) {
			if (d->encoded_bin[i] == 0) {
				d->num_i = 0;
			}
			else {
				d->num_i++;
				if (d->num_i == 5) {
					for (j = d->count; j >= i-1; j--) {
						d->encoded_bin[j+1] = d->encoded_bin[j];
					}
					d->encoded_bin[i+1] = 0;
					d->count++;
				}
			}
		}
	}
}

/* Print out the encoded data */
void print_encoded_bin(int count, int *bin)
{
	int i;
	char out = 's';

	printf("%c", out);
	for (i = 0; i < count; i++) {
		if (bin[i] == 0) {
			if (out == 's')
				out = 'm';
			else
				out = 's';
		}
		printf("%c", out);
	}
	printf("\n");
}

/* Free any reserved memory for struct */
void destroy(Data *d)
{
	if (d) {
		free(d);
	}
}