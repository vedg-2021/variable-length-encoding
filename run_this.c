#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include "bit_functions/bit_functions.h"

long long decode(char *out){
        unsigned long long output;
        unsigned char is_final = (read_bit(out, 2) == 0) ? 0 : 1;
        unsigned char bit_pos;
        unsigned char bits_to_read = 2;
        unsigned char from_msb = 0;
        unsigned char num;

        while(is_final == 0){
                num = read_num(out, from_msb, bits_to_read);
                from_msb = from_msb + bits_to_read + 1;         // now looking at bit just after the is_final bit
                bits_to_read = num;
                is_final = (read_bit(out, (from_msb + bits_to_read)) == 0) ? 0 : 1;
        }
        output = read_ll_num(out, from_msb, num);
        printf("\nretrieved long long number in hex = 0x%016llx\n", output);
        printf("retrieved long long number = %llu\n", output);
        return output;
}


char* encodeSeq(char *in, char *out)
{
    unsigned char step_array[50];
    int top = -1;
    unsigned int total_bits_required;
    unsigned int num_of_bytes, from_msb = 0;
    // retrieving original long long number pointed by char *in
    unsigned long long *og_num = (unsigned long long *)in;
    unsigned int temp = (double) ceil(log2((double)*og_num + 1));
    unsigned char to_store, in_bits = 2;

    total_bits_required = cal_bits(*og_num);

    // storing numbers in step_array
    step_array[++top] = temp;

    while (temp > 2)
    {
        temp = (double) ceil(log2(((double)temp + 1)));
        step_array[++top] = temp;

    }
    printf("encoding %llu\n", *og_num);

    // number of bytes required to store the encoded sequence
    num_of_bytes = (double) ceil(total_bits_required / 8.0);

    // allocate number of bytes
    out = calloc(num_of_bytes, sizeof(char));

    // store sequence
    while (top > -1)
    {   
        to_store = step_array[top];
        store_seq(out, from_msb, to_store, in_bits);
        from_msb = from_msb + in_bits + 1;
        in_bits = to_store;
        top--;
    }

    store_num(out, from_msb, *og_num); // storing the original number

    from_msb = from_msb + (double) ceil(log2((double)*og_num + 1));
    store_seq(out, from_msb, 1, 1);

    printSeqence(out, num_of_bytes);

    return out;
}
