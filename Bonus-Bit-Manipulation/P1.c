//P1-數字半位元組分割
#include <stdio.h>
#include <stdlib.h>

int main()
{
    unsigned int num;
    int ans[8] = {0};
    int c = 1;

    while(scanf("%u", &num) != EOF) {
        printf("Case %d: %u\n", c, num);

        for(int i = 0; i < 8; ++i) {
            ans[i] = (num >> 4*i) & 0x0F;
        }
        for(int i = 7; i >= 0; --i) {
            printf("%X ", ans[i]);
        }
        printf("\n");
        ++c;
    }
    return 0;
}
