/*
 *
 * RC4を使ってストリーム暗号を使って暗号化、そして複合する。
 *
 * 以下はプログラムを動作したサンプルプログラム
 * 第１引数にはkeyを第２引数には暗号化したいplaintextを入力する
 * $ ./a.out hoge fdsafdsafsda
 * Cypering plaintext using RC4
 * E22BFC31155FDD771D94165A

 * Decypering plaintext using RC4
 * fdsafdsafsda
 *
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define N 256   // 2^8

void swap(unsigned char *a, unsigned char *b) {
    int tmp = *a;
    *a = *b;
    *b = tmp;
}

// Key Scheduling Algorithm 
int KSA(char *key, unsigned char *S) {

    int len = strlen(key);
    int j = 0;

    for(int i = 0; i < N; i++)
        S[i] = i;

    for(int i = 0; i < N; i++) {
        j = (j + S[i] + key[i % len]) % N;

        swap(&S[i], &S[j]);
    }

    return 0;
}

// Pseudo-Random Generator Algorithm 
int PRGA(unsigned char *S, char *plaintext, unsigned char *ciphertext) {

    int i = 0;
    int j = 0;

    for(size_t n = 0, len = strlen(plaintext); n < len; n++) {
        i = (i + 1) % N;
        j = (j + S[i]) % N;

        swap(&S[i], &S[j]);
        int rnd = S[(S[i] + S[j]) % N];

        ciphertext[n] = rnd ^ plaintext[n];

    }

    return 0;
}

int RC4(char *key, char *plaintext, unsigned char *ciphertext) {

    unsigned char S[N];
    KSA(key, S);

    PRGA(S, plaintext, ciphertext);

    return 0;
}

int main(int argc, char *argv[]) {

    if(argc < 3) {
        printf("Usage: %s <key> <plaintext>", argv[0]);
        return -1;
    }

    unsigned char *ciphertext = malloc(sizeof(int) * strlen(argv[2]));

    RC4(argv[1], argv[2], ciphertext);

    // Cyper
    printf("Cypering plaintext using RC4\n");
    for(size_t i = 0, len = strlen(argv[2]); i < len; i++)
        printf("%02hhX", ciphertext[i]);
	printf("\n\n");

	// Decyper
    printf("Decypering plaintext using RC4\n");
    RC4(argv[1], (char*)ciphertext, ciphertext);             // 今度はRC4関数にはcypertextを入れる
    for(size_t i = 0, len = strlen(argv[2]); i < len; i++)
        printf("%c", ciphertext[i]);
	printf("\n");

    return 0;
}
