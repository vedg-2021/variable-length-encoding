#include<stdio.h>
#include<math.h>

unsigned char read_bit(unsigned char *arr, unsigned char from_msb){
	int block_pos = from_msb/8;
	int bit_pos = from_msb%8;
	unsigned char t = 1 << (8 - bit_pos - 1);
	return arr[block_pos] & t;
}

unsigned char read_num(unsigned char* arr, unsigned char from_msb, int number_of_bits_to_read){
	unsigned char output;
	unsigned char end_bit = from_msb + number_of_bits_to_read - 1;
	int start_block = from_msb/8;
	int end_block = end_bit/8;
	int bit_pos = from_msb%8;
	unsigned char mask = ~0;
	unsigned char temp_char = arr[start_block];

	if(start_block == end_block){
		mask = mask << number_of_bits_to_read;
		mask = ~mask;
		temp_char = temp_char >> (8 - ((end_bit%8) + 1));
		output = temp_char & mask;
	} else{
		mask = mask << (((start_block + 1) * 8) - from_msb);
        mask = ~mask;
        unsigned char temp_char_2 = temp_char & mask;
        temp_char_2 = temp_char_2 << (number_of_bits_to_read - (((start_block + 1) * 8) - from_msb));
        temp_char = arr[end_block];
        temp_char = temp_char >> (8 - (number_of_bits_to_read - (((start_block + 1) * 8) - from_msb)));
        temp_char_2 = temp_char_2 | temp_char;
        output = temp_char_2;
	}
	return output;
}


unsigned long long read_ll_num(unsigned char* arr, unsigned char from_msb, int number_of_bits_to_read){
	unsigned long long output = 0;
	int start_block = from_msb/8;
	unsigned char end_bit = from_msb + number_of_bits_to_read - 1;
	int end_block = end_bit/8;
	unsigned char mask = ~0;
	unsigned char temp_char = arr[start_block];
	if(start_block == end_block){
		temp_char = temp_char >> ((8 * (start_block + 1)) - end_bit - 1);
		mask = mask << (end_bit - from_msb + 1);
		mask = ~mask;
		output = temp_char & mask;
	} else{
        mask = mask >> (8 - ((8 * (start_block + 1)) - from_msb));
        output = temp_char & mask;
        from_msb = from_msb + ((8 * (start_block + 1)) - from_msb);
        start_block++;
        while(start_block < end_block){
            mask = ~0;
            temp_char = arr[start_block] & mask;
            output = output << 8;
            output = output | temp_char;
            start_block++;
            from_msb += 8;
        }
        temp_char = arr[start_block];
        temp_char = temp_char >> (8 - (end_bit - from_msb + 1));
        output = output << (end_bit - from_msb + 1);
        output = output | temp_char;
	}
	return output;
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
    // unsigned int end_block = (double) ceil((double)(from_msb + in_bits - 1) / 8);
    unsigned int end_block = (from_msb + in_bits - 1) / 8;

    
    if(start_block == end_block) {
        unsigned char temp_char = (unsigned char) og_num;
        temp_char = temp_char << ((8 - (from_msb % 8)) - in_bits);
        arr[start_block] = arr[start_block] | temp_char;
    } else{
        unsigned long long temp_num = og_num;
        unsigned int in_bits_temp = in_bits;
        unsigned int bits_empty = (8 - (from_msb % 8));
        unsigned char temp_char;
        temp_num = temp_num >> (in_bits_temp - bits_empty);
        temp_char = 0 | temp_num;
        arr[start_block] = arr[start_block] | temp_char;
        from_msb = from_msb + bits_empty;
        in_bits_temp = in_bits_temp - bits_empty;

        start_block++;

        while(start_block < end_block){
            temp_num = og_num;
            bits_empty = (8 - (from_msb % 8));
            temp_num = temp_num >> (in_bits_temp - bits_empty);
            temp_char = 0 | temp_num;
            arr[start_block] = arr[start_block] | temp_char;
            from_msb = from_msb + bits_empty;
            in_bits_temp = in_bits_temp - bits_empty;
            start_block++;
        }

        temp_num = og_num;
        bits_empty = (8 - (from_msb % 8));
        temp_char = 0 | temp_num;
        temp_char = temp_char << (8 - in_bits_temp);
        arr[end_block] = arr[end_block] | temp_char;
    }

    return;
}

void printSeqence(unsigned char *arr, unsigned int size)
{
    int i = 0;
    printf("printing encoded sequence: \n");
    while (i < size)
    {
        printf("%u\t", arr[i++]);
    }
    return;
}
