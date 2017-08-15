// basic3を入力できるようにしたか
#include<stdio.h>
#include<string.h>  // strtok, strlen
#include<stdlib.h>  // atoi
#include<math.h>    // floor

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

unsigned int convertLittleEndian(unsigned int x){
	return ((x >> 24) & 0xff)  | (((x >> 16) & 0xff) << 8) | ((x >> 8) & 0xff) << 16 | ((x & 0xff) << 24);
}

void getKey(char* key, unsigned int* copyAry){

   char* token;
   token = strtok(key, ":" );

   int i = 0;
   unsigned int hash[4] = {0};
   while ( token != NULL ){
	  hash[i%4] = atoi(token);
   	  if( 3 == i % 4 ) {
	  	*copyAry = (hash[0] & 0xff)  | ((hash[1] & 0xff) << 8) | ((hash[2] & 0xff ) << 16) | (hash[3] & 0xff) << 24;
		printf("%08x\n", *copyAry);
		copyAry++;
	  }
	  i++;
      token = strtok( NULL, ":" );
   }

   // TODO: 残り部分
   if( i % 4 != 0){
   }

}

int main(){

	unsigned int constant[4] = { 0x61707865,  0x3320646e,  0x79622d32,  0x6b206574 };
	unsigned int count = 0x00000001;
	unsigned int nonce[3] = {0x09000000,  0x4a000000,  0x00000000};
	unsigned int state[VSIZE];

	unsigned int copyAry[8];
	char keystr[] = "00:01:02:03:04:05:06:07:08:09:0a:0b:0c:0d:0e:0f:10:11:12:13:14:15:16:17:18:19:1a:1b:1c:1d:1e:1f";
	char plaintext[] = "Ladies and Gentlemen of the class of '99: If I could offer you only one tip for the future, sunscreen would be it.";

	unsigned int textlength;
	textlength = strlen(plaintext);

	// 平文を16進数出力して確認する
	//for(int i = 0; plaintext[i] != '\0'; i++){
	//	printf("%02X ", plaintext[i]);
	//}

	getKey(keystr, copyAry);
	//printState(copyAry);

	// FIXME: やっつけ
	state[0] = constant[0];
	state[1] = constant[1];
	state[2] = constant[2];
	state[3] = constant[3];

	// もっときれいにかきたい
	state[4] = copyAry[0];
	state[5] = copyAry[1];
	state[6] = copyAry[2];
	state[7] = copyAry[3];
	state[8] = copyAry[4];
	state[9] = copyAry[5];
	state[10] = copyAry[6];
	state[11] = copyAry[7];

	state[12] = count;
	state[13] = nonce[0];
	state[14] = nonce[1];
	state[15] = nonce[2];
	printState(state);


	unsigned int current[VSIZE];
	for(int i=0;i<VSIZE;++i){
		current[i] = state[i];
	}

	for(int j = 0; j < floor(strlen(plaintext)/64) -1; j++){
		unsigned int tmpstate[VSIZE];
		for(int i=0;i<VSIZE;++i){
			tmpstate[i] = current[i];
		}
		tmpstate[12] += j;   // for counter

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

		// 2.3.2.  Test Vector for the ChaCha20 Block Function:  CheckPoint1
		//printState(tmpstate);

		// add original value
		for (int i = 0; i < VSIZE; ++i){
			tmpstate[i] += current[i];
		}

		// 2.3.2.  Test Vector for the ChaCha20 Block Function:  CheckPoint2
		//printState(tmpstate);

		// 2.3.2.  Test Vector for the ChaCha20 Block Function:  CheckPoint3
		// convert into little endian
		//for (int i = 0; i < VSIZE; ++i){
		//	printf("%02x ", tmpstate[i] & 0xff);
		//	printf("%02x ", (tmpstate[i] >> 8) & 0xff);
		//	printf("%02x ", (tmpstate[i] >> 16) & 0xff);
		//	printf("%02x ", (tmpstate[i] >> 24) & 0xff);
		//	if( (i+1) % 4 == 0) printf("\n");
		//}
		//printf("\n");
	}

	//int j = 0; 
	//for(int i = 0; plaintext[i] != '\0'; i++){
	//	printf("%02x ", plaintext[i] ^ state[j%16]);
	//	j++;
	//	if(j == 16) j = 0;
	//}

}
