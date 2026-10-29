//P5: Unpacking Characters from an Integer
#include <stdio.h>

void toBinary(unsigned int num)
{
    int bit[32] = {0};
    int cnt = 1;

    for (int i = 0; i < 32; ++i) {
        bit[i] = (num >> i) & 0x01;
    }

    for (int i = 31; i >= 0; --i) {
        printf("%d", bit[i]);
        if (cnt % 8 == 0) printf(" ");
        ++cnt;
    }
    printf("\n");
}

int main()
{
    unsigned int num;
    unsigned int ans = 0;

    if (scanf("%u", &num) != 1) {
        printf("Error: Failed to read input.\n");
        return 1;
    }

    printf("The packed character representation is:\n");
    printf("%u = ", num);

    toBinary(num);
    printf("\n");

    ans = num & 0xFF000000;
    ans >>= 24;
    printf("%u = ", ans);
    toBinary(ans);

    ans = num & 0xFF0000;
    ans >>= 16;
    printf("%u = ", ans);
    toBinary(ans);

    ans = num & 0xFF00;
    ans >>= 8;
    printf("%u = ", ans);
    toBinary(ans);

    ans = num & 0xFF;
    printf("%u = ", ans);
    toBinary(ans);

    return 0;
}
