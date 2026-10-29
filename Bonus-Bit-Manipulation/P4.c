//P4: Packing Characters into an Integer
#include <stdio.h>
#include <math.h>

void toBinary(char word)
{
    int c[32] = {0};
    int cnt = 1;

    printf("%c:\n", word);
    unsigned int num = (unsigned int)word;
    printf("%u = ", num);
    for(int i = 0; i < 32; ++i) {
        c[i] = (num >> i) & 0x01;
    }
    for(int i = 31; i >= 0; --i) {
        printf("%d", c[i]);
        if(cnt % 8 == 0 && cnt != 32) printf(" ");
        ++cnt;
    }
    printf("\n");
}

void packCharacters(char c1, char c2, char c3, char c4)
{
    long long unsigned int sum = 0;
    int ans[32] = {0};
    int temp[8] = {0};
    int j = 0;
    int cnt = 1;
    int seven = 7;
    int cnt_ = 31;
    unsigned int num[4] = {(unsigned int)c1, (unsigned int)c2, (unsigned int)c3, (unsigned int)c4};

    printf("'%c' and '%c' and '%c' and '%c' packed in an unsigned int:\n", c1, c2, c3, c4);

    while(j != 4) {
        for(int i = 0; i < 8; ++i) {
            temp[i] = (num[j] >> i) & 0x01;
        }
        for(int i = 8 * j; i < 8 * (j + 1); ++i) {
            ans[i] = temp[seven--];
        }
        ++j;
        seven = 7;
    }

    for(int i = 0; i < 32; ++i) {
        if(ans[i] == 1) {
            sum += ans[i] * pow(2, cnt_);
        }
        --cnt_;
    }

    printf("%llu = ", sum);
    for(int i = 0; i < 32; ++i) {
        printf("%d", ans[i]);
        if(cnt % 8 == 0 && cnt != 32) printf(" ");
        ++cnt;
    }
    printf("\n");
}

int main()
{
    char c1, c2, c3, c4;

    if (scanf(" %c %c %c %c", &c1, &c2, &c3, &c4) != 4) {
        printf("Error: Failed to read input.\n");
        return 1;
    }

    toBinary(c1);
    toBinary(c2);
    toBinary(c3);
    toBinary(c4);
    packCharacters(c1, c2, c3, c4);

    return 0;
}
