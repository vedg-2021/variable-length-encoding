#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int cal_bits(long long og_num);
void printSeqence(unsigned char *arr, unsigned int size);
void store_seq(unsigned char *arr, unsigned int from_msb, unsigned char to_store, unsigned char in_bits);
void store_num(unsigned char *arr, unsigned int from_msb, unsigned long long og_num);

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
    printf("retrieved original number = %llu\n", *og_num);

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

int main()
{

    unsigned long long b8 = 0xf1f2f3f4f5f6f7f8;
    // unsigned long long b8 = 736969696969;
    // unsigned long long b8 = 0xffffffffffffffff;
    // unsigned long long b8 = 0;
    // unsigned long long b8 = 7994;
    // unsigned long long b8 = 218694;
    unsigned char *in = (unsigned char *)&b8;
    unsigned char *out;
    // printf("original number = %llu\n", b8);
    // printf("original number in hex = 0x%016llx\n", b8);
    encodeSeq(in, out);
    printf("\n");
    return 0;
}

int cal_bits(long long og_num)
{
    int output = 0;
    unsigned long long temp = og_num;

    while (temp > 2)
    {
        output++;
        temp = (double)ceil(log2((double)temp + 1));
        output = output + (int)temp;
    }

    output += 3;

    return output;
}

void store_seq(unsigned char *arr, unsigned int from_msb, unsigned char to_store, unsigned char in_bits)
{
    unsigned int start_block = from_msb / 8;
    unsigned int end_block = (from_msb + in_bits - 1) / 8;
    unsigned char temp_char;

    if (start_block == end_block)
    {
        to_store = to_store << ((((start_block + 1) * 8) - from_msb) - in_bits);
        arr[start_block] = arr[start_block] | to_store;
    }
    else
    {
        temp_char = to_store;
        temp_char = temp_char >> (in_bits - (((start_block + 1) * 8) - from_msb));
        arr[start_block] = arr[start_block] | temp_char;
        to_store = to_store << (8 - (in_bits - (((start_block + 1) * 8) - from_msb)));
        arr[end_block] = arr[end_block] | to_store;
    }

    return;
}

void store_num(unsigned char *arr, unsigned int from_msb, unsigned long long og_num)
{
    unsigned char in_bits = (double) ceil(log2((double)og_num + 1));
    unsigned int start_block = from_msb / 8;
    unsigned int end_block = (double) ceil((double)(from_msb + in_bits) / 8);
    unsigned long long temp_num = og_num >> (in_bits - ((start_block + 1) * 8 - from_msb));
    unsigned char temp_char = 0;
    unsigned int x = (in_bits - ((start_block + 1) * 8 - from_msb)), byte = 1;

    temp_char = temp_char | temp_num;
    arr[start_block] = arr[start_block] | temp_char;
    start_block = start_block + 1;

    while ((start_block < end_block-1))
    {   
        temp_num = og_num;
        temp_char = 0;
        x = x - 8;
        temp_num = temp_num >> x;
        temp_char = temp_char | temp_num;
        arr[start_block] = arr[start_block] | temp_char;
        start_block = start_block + 1;
    }

    temp_num = og_num;
    temp_char = 0;
    temp_char = temp_char | og_num;
    temp_char = temp_char << (8 - x);
    end_block--;
    arr[end_block] = arr[end_block] | temp_char;

    return;
}

void printSeqence(unsigned char *arr, unsigned int size)
{
    int i = 0;
    while (i < size)
    {
        printf("%u\t", arr[i++]);
    }
    return;
}
