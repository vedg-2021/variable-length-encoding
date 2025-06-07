#ifndef MY_FUNCTIONS_H
#define MY_FUNCTIONS_H

unsigned char read_bit(unsigned char *arr, unsigned char from_msb);
unsigned char read_num(unsigned char *arr, unsigned char from_msb, int number_of_bits_to_read);
unsigned long long read_ll_num(unsigned char* arr, unsigned char from_msb, int number_of_bits_to_read);
int cal_bits(long long og_num);
void printSeqence(unsigned char *arr, unsigned int size);
void store_seq(unsigned char *arr, unsigned int from_msb, unsigned char to_store, unsigned char in_bits);
void store_num(unsigned char *arr, unsigned int from_msb, unsigned long long og_num);


#endif
