#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include "bit_functions/bit_functions.h"

long long decode(char *out){
	unsigned long long output = 23;
	unsigned char final = (read_bit(out, 3) == 0) ? 0 : 1;
	unsigned char bit_pos;
	unsigned char bits_to_read = 2;
	unsigned char from_msb = 1;
	unsigned char num;

	while(final == 0){
		num = read_num(out, from_msb, bits_to_read);
		from_msb = from_msb + bits_to_read + 1;		// now looking at bit just after the is_final bit
		bits_to_read = num;
		final = (read_bit(out, (from_msb + bits_to_read)) == 0) ? 0 : 1;
	}
	output = read_ll_num(out, from_msb, num);
	printf("retrieved long long number in hex = 0x%016llx\n", output);
	printf("retrieved long long number = %llu\n", output);
	return output;
}

int main(){
	// unsigned char out[] = {155, 160, 60, 124, 188, 253, 61, 125, 189, 254, 32};
	// unsigned char out[] = {154, 53, 243, 168};
	// unsigned char out[] = {88};
	// unsigned char out[] = {155, 160, 63, 255, 255, 255, 255, 255, 255, 255, 224};
	unsigned char out[] = {154, 164, 213, 145, 160};
	long long og_num = decode(out);
	return 0;
}
