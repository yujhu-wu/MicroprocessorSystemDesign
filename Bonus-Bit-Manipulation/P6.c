//P6-Reversing the Order of an Integer's Bits
#include <stdio.h>
#include <math.h>

int main()
{
    unsigned int num;
    int r[32] = {0};

    while(scanf("%u", &num) != EOF) {
        long long unsigned int sum = 0;
        int cnt = 32;
        int j = 0;
        printf("Before bits are reversed:\n");
        printf("%u = ", num);

        for(int i = 0; i < 32; ++i) {
            r[i] = (num >> i) & 0x01;
        }
        for(int i = 31; i >= 0; --i) {
            if(cnt % 8 == 0 && cnt != 32) printf(" ");
            printf("%d", r[i]);
            --cnt;
        }
        printf(" \n\n");

        cnt = 32;
        printf("After bits are reversed:\n");

        for(int i = 31; i >= 0; --i) {
            sum += r[j] * pow(2.0, i);
            ++j;
        }
        printf("%llu = ", sum);

        for(int i = 0; i < 32; ++i) {
            if(cnt % 8 == 0 && cnt != 32) printf(" ");
            printf("%d", r[i]);
            --cnt;
        }
        printf(" \n");
    }
    return 0;
}
