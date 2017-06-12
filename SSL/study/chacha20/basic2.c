// 2.1.1.  Test Vector for the ChaCha Quarter Round
#include<stdio.h>

// ちょっと汚い書き方
// case1〜case4をすべて実行して本来はquarterRoundが全て実行されたことになる。今回はそのうちの1つの値を検証するだけ。
void quarterRound(unsigned int *a,unsigned int *b,unsigned int *c,unsigned int *d, int num){

    unsigned int add;
	switch(num){
	case 1:
		*a += *b;
		*d ^= *a;
		add = *d >> (32 - 16);
		*d <<=  16;
		*d += add;
	case 2:
		*c += *d;
		*b ^= *c;
		add = *b >> (32 - 12);
		*b <<=  12;
		*b += add;
	case 3:
		*a += *b;
		*d ^= *a;
		add = *d >> (32 - 8);
		*d <<=  8;
		*d += add;
	case 4:
		*c += *d;
		*b ^= *c;
		add = *b >> (32 - 7);
		*b = *b << 7;
		*b += add;
	}
	return;
}

int main(){
	unsigned int a = 0x11111111;
    unsigned int b = 0x01020304;
    unsigned int c = 0x9b8d6f43;
    unsigned int d = 0x01234567;

	// 以下の4つをまとめてquarterRoundという。今回はそのうちの1つの値のチェック
	quarterRound(&a, &b, &c, &d, 1);
//	quarterRound(&a, &b, &c, &d, 2);
//	quarterRound(&a, &b, &c, &d, 3);
//	quarterRound(&a, &b, &c, &d, 4);

	printf("a=0x%08x\n", a);
	printf("b=0x%08x\n", b);
	printf("c=0x%08x\n", c);
	printf("d=0x%08x\n", d);

}
