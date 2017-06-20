#include <stdio.h>
/*
Output should be:
EB 9F 77 81 B7 34 CA 72 A7
*/

// Key Scheduling Algorithm 
// Input: state - the state used to generate the keystream
//        key - Key to use to initialize the state 
//        len - length of key in bytes  
void ksa(unsigned char state[], unsigned char key[], int len)
{
   int i,j=0,t; 
   
   for (i=0; i < 256; ++i)
      state[i] = i; 
   for (i=0; i < 256; ++i) {
      j = (j + state[i] + key[i % len]) % 256; 
      t = state[i]; 
      state[i] = state[j]; 
      state[j] = t; 
   }   
}

// Pseudo-Random Generator Algorithm 
// Input: state - the state used to generate the keystream 
//        out - Must be of at least "len" length
//        len - number of bytes to generate 
void prga(unsigned char state[], unsigned char out[], int len)
{  
   int i=0,j=0,x,t; 
   unsigned char key; 
   
   for (x=0; x < len; ++x)  {
      i = (i + 1) % 256; 
      j = (j + state[i]) % 256; 
      t = state[i]; 
      state[i] = state[j]; 
      state[j] = t; 
      out[x] = state[(state[i] + state[j]) % 256];
   }   
}  

int main() 
{
   unsigned char state[256],key[]={"Key"},stream[1024]; 
   int len=9,idx; 
   
   ksa(state,key,3); 
   prga(state,stream,len); 
   
   for (idx=0; idx < len; idx++) 
      printf("%02X ",stream[idx]); 
   
   return 0; 
}

