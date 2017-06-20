// 2.1.  The ChaCha Quarter Round 
// https://tools.ietf.org/html/rfc7539#section-2.1  確認用プログラム
#include<stdio.h>

int main(){
	unsigned int a = 0x11111111;
    unsigned int b = 0x01020304;
    unsigned int c = 0x77777777;
    unsigned int d = 0x01234567;
    c = c + d;
	b = b ^ c;
    b = b << 7;

	// 2.1.  The ChaCha Quarter Round Check
	printf("0x%08x\n", a);
	printf("0x%08x\n", b);
	printf("0x%08x\n", c);
	printf("0x%08x\n", d);

}
