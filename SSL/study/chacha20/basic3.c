// 2.3.2.  Test Vector for the ChaCha20 Block Function
// https://tools.ietf.org/html/rfc7539#section-2.3.2 確認用プログラム
#include<stdio.h>

#define VSIZE 16

void QUARTERROUND(unsigned int *a, unsigned int *b, unsigned int *c, unsigned int *d){

	// 1st round
    *a += *b;
    *d ^= *a;
	*d = (*d << 16) | (*d >> 16);   // 32-16=16
    
	// 2nd
    *c += *d; 
    *b ^= *c; 
	*b = (*b << 12) | (*b >> 20);   // 32-12=20
    
	// 3rd
    *a += *b; 
    *d ^= *a; 
	*d = (*d <<  8) | (*d >> 24);   // 32-8=24
    
	// 4th
    *c += *d; 
    *b ^= *c; 
	*b = (*b <<  7) | (*b >> 25);   // 32-7=25
    
    return;
}

void printState(unsigned int *state){
	for(int j = 0; j < 4; j++){
		for(int i = 0; i < 4; i++){
			printf("0x%08x \t", *(&state[i+j*4]));
		}
		printf("\n");
	}
}

int main(){

	unsigned int state[VSIZE] = {
       0x61707865,  0x3320646e,  0x79622d32,  0x6b206574,
       0x03020100,  0x07060504,  0x0b0a0908,  0x0f0e0d0c,
       0x13121110,  0x17161514,  0x1b1a1918,  0x1f1e1d1c,
       0x00000001,  0x09000000,  0x4a000000,  0x00000000,
	};

	unsigned int current[VSIZE];
	for(int i=0;i<VSIZE;++i){
		current[i] = state[i];
	}

	// 20 round(10 column round and 10 diagonal round)
	for(int i = 0; i < 10; i++){
		// column round
		QUARTERROUND(&state[0], &state[4], &state[8],  &state[12]);
		QUARTERROUND(&state[1], &state[5], &state[9],  &state[13]);
		QUARTERROUND(&state[2], &state[6], &state[10], &state[14]);
		QUARTERROUND(&state[3], &state[7], &state[11], &state[15]);

		// diagonal round
		QUARTERROUND(&state[0], &state[5], &state[10], &state[15]);
		QUARTERROUND(&state[1], &state[6], &state[11], &state[12]);
		QUARTERROUND(&state[2], &state[7], &state[8],  &state[13]);
		QUARTERROUND(&state[3], &state[4], &state[9],  &state[14]);
	}

	// 2.3.2.  Test Vector for the ChaCha20 Block Function:  CheckPoint1
	//printState(state);

	// add original value
	for (int i = 0; i < VSIZE; ++i){
		state[i] += current[i];
	}

	// 2.3.2.  Test Vector for the ChaCha20 Block Function:  CheckPoint2
	printState(state);

	// 2.3.2.  Test Vector for the ChaCha20 Block Function:  CheckPoint3
	// convert into little endian
	for (int i = 0; i < VSIZE; ++i){
		printf("%02x ", state[i] & 0xff);
		printf("%02x ", (state[i] >> 8) & 0xff);
		printf("%02x ", (state[i] >> 16) & 0xff);
		printf("%02x ", (state[i] >> 24) & 0xff);
		if( (i+1) % 4 == 0) printf("\n");
	}
	printf("\n");

}
