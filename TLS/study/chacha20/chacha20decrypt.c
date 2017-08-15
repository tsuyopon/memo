// chacha20.cの出力結果が複合して照合するプログラム(基本的にはchacha20.cと同じです。vimdiffするといいかも)
//  plaintextはべた書きでchacha20.cの結果を記載している。
//
// Implementation chacha20 about "2.4.  The ChaCha20 Encryption Algorithm" in RFC7539.
#include<stdio.h>
#include<string.h>  // strtok, strlen
#include<stdlib.h>  // atoi
#include<math.h>    // ceil

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

	unsigned int constant[4] = { 0x61707865,  0x3320646e,  0x79622d32,  0x6b206574 };
	unsigned int key[8] = { 0x03020100,  0x07060504,  0x0b0a0908,  0x0f0e0d0c, 0x13121110,  0x17161514,  0x1b1a1918,  0x1f1e1d1c };
	unsigned int count = 0x00000001;
	unsigned int nonce[3] = {0x00000000,  0x4a000000,  0x00000000};
	unsigned int state[VSIZE];

	char keystr[] = "00:01:02:03:04:05:06:07:08:09:0a:0b:0c:0d:0e:0f:10:11:12:13:14:15:16:17:18:19:1a:1b:1c:1d:1e:1f";
//	char plaintext[] = "Ladies and Gentlemen of the class of '99: If I could offer you only one tip for the future, sunscreen would be it.";
	unsigned char plaintext[] = {
		0x6e, 0x2e, 0x35, 0x9a, 0x25, 0x68, 0xf9, 0x80, 0x41, 0xba, 0x07, 0x28, 0xdd, 0x0d, 0x69, 0x81, 
		0xe9, 0x7e, 0x7a, 0xec, 0x1d, 0x43, 0x60, 0xc2, 0x0a, 0x27, 0xaf, 0xcc, 0xfd, 0x9f, 0xae, 0x0b, 
		0xf9, 0x1b, 0x65, 0xc5, 0x52, 0x47, 0x33, 0xab, 0x8f, 0x59, 0x3d, 0xab, 0xcd, 0x62, 0xb3, 0x57, 
		0x16, 0x39, 0xd6, 0x24, 0xe6, 0x51, 0x52, 0xab, 0x8f, 0x53, 0x0c, 0x35, 0x9f, 0x08, 0x61, 0xd8, 
		0x07, 0xca, 0x0d, 0xbf, 0x50, 0x0d, 0x6a, 0x61, 0x56, 0xa3, 0x8e, 0x08, 0x8a, 0x22, 0xb6, 0x5e, 
		0x52, 0xbc, 0x51, 0x4d, 0x16, 0xcc, 0xf8, 0x06, 0x81, 0x8c, 0xe9, 0x1a, 0xb7, 0x79, 0x37, 0x36, 
		0x5a, 0xf9, 0x0b, 0xbf, 0x74, 0xa3, 0x5b, 0xe6, 0xb4, 0x0b, 0x8e, 0xed, 0xf2, 0x78, 0x5e, 0x42, 
		0x87, 0x4d
	};

	unsigned int textlength;
	textlength = strlen((char*)plaintext);

	// 平文を16進数出力して確認する(for debug)
	//for(int i = 0; plaintext[i] != '\0'; i++){
	//	printf("%02X ", plaintext[i]);
	//}

	// FIXME: 配列の入れ方が雑
	state[0] = constant[0];
	state[1] = constant[1];
	state[2] = constant[2];
	state[3] = constant[3];

	state[4] = key[0];
	state[5] = key[1];
	state[6] = key[2];
	state[7] = key[3];
	state[8] = key[4];
	state[9] = key[5];
	state[10] = key[6];
	state[11] = key[7];

	state[12] = count;
	state[13] = nonce[0];
	state[14] = nonce[1];
	state[15] = nonce[2];
	//printState(state);

	unsigned int current[VSIZE];
	for(int i=0;i<VSIZE;++i){
		current[i] = state[i];
	}

	for(int j = 0; j <= ceil(strlen((char*)plaintext)/64); j++){
		unsigned int tmpstate[VSIZE] = {0};
		for(int i=0;i<VSIZE;++i){
			tmpstate[i] = current[i];
		}
		tmpstate[12] += j;           // for counter
		current[12] = tmpstate[12];  // update current[12] as original number

		// 20 round(10 column round and 10 diagonal round)
		for(int i = 0; i < 10; i++){
			// column round
			QUARTERROUND(&tmpstate[0], &tmpstate[4], &tmpstate[8],  &tmpstate[12]);
			QUARTERROUND(&tmpstate[1], &tmpstate[5], &tmpstate[9],  &tmpstate[13]);
			QUARTERROUND(&tmpstate[2], &tmpstate[6], &tmpstate[10], &tmpstate[14]);
			QUARTERROUND(&tmpstate[3], &tmpstate[7], &tmpstate[11], &tmpstate[15]);

			// diagonal round
			QUARTERROUND(&tmpstate[0], &tmpstate[5], &tmpstate[10], &tmpstate[15]);
			QUARTERROUND(&tmpstate[1], &tmpstate[6], &tmpstate[11], &tmpstate[12]);
			QUARTERROUND(&tmpstate[2], &tmpstate[7], &tmpstate[8],  &tmpstate[13]);
			QUARTERROUND(&tmpstate[3], &tmpstate[4], &tmpstate[9],  &tmpstate[14]);
		}

		// 2.3.2.  Test Vector for the ChaCha20 Block Function:  CheckPoint1 (for debug)
		//printState(tmpstate);

		// add original value with tmpstate
		for (int i = 0; i < VSIZE; ++i){
			tmpstate[i] += current[i];
		}

		// 2.3.2.  Test Vector for the ChaCha20 Block Function:  CheckPoint2 (for debug)
		//printState(tmpstate);

		// 2.3.2.  Test Vector for the ChaCha20 Block Function:  CheckPoint3 (for debug)
		// convert into little endian
		//for (int i = 0; i < VSIZE; ++i){
		//	printf("%02x ", tmpstate[i] & 0xff);
		//	printf("%02x ", (tmpstate[i] >> 8) & 0xff);
		//	printf("%02x ", (tmpstate[i] >> 16) & 0xff);
		//	printf("%02x ", (tmpstate[i] >> 24) & 0xff);
		//	if( (i+1) % 4 == 0) printf("\n");
		//}
		//printf("\n");

		// processing xor between plaintext and state. Break processing if exceeded plaintext string length.
		for (int i = 0; i < VSIZE; ++i){
			for(int k = 0; k < 4; k++){
				if( strlen((char*)plaintext) <= j*64 + i*4 + k ){
					goto exit;
				}
				// XOR with original
//				printf("%02x ", plaintext[j*64+i*4+k] ^ ((tmpstate[i] >> (8*k)) & 0xff));
				printf("%c", plaintext[j*64+i*4+k] ^ ((tmpstate[i] >> (8*k)) & 0xff));
			}
			if( i % 4 == 3) printf("\n");
		}
		printf("\n");
	}

	exit:
		printf("\n");
		return 0;
}
