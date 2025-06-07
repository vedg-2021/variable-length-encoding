#include<stdio.h>
#include "run_this.h"

int main(){
	// long long b8 = 12345696969;
	// long long b8 = 2;
	// long long b8 = 67000;
	// long long b8 = 155;
	// long long b8 = 142300;
	// long long b8 = 60909000600;
	// long long b8 = 600346520;
	long long b8 = 0xf1f2f3f4f5f6f7f8;
	char *in = &b8;
	char *out = NULL;
	decode(encodeSeq(in, out));
	return 0;
}
