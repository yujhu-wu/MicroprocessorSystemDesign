// P2-數字系統轉換
#include <stdio.h>
#include <stdlib.h>

void displayBinary(unsigned int value)
{
    int binaryDigits[32] = {0};

    for(int i = 0; i < 32; ++i) {
        binaryDigits[i] = (value >> i) & 0x01;
    }
    for(int i = 31; i >= 0; --i) {
        printf("%d", binaryDigits[i]);
    }
    printf("\n");
}

void displayOctal(unsigned int value)
{
    int octalDigits[12] = {0};

    for(int i = 0; i < 12; ++i) {
        if(i != 11) {
            octalDigits[i] = value & 0x07;
            value >>= 3;
        }
    }
    for(int i = 11; i >= 0; --i) {
        printf("%d", octalDigits[i]);
    }
    printf("\n");
}

void displayHexadecimal(unsigned int value)
{
    int hexDigits[8] = {0};

    printf("0x");
    for(int i = 0; i < 8; ++i) {
        hexDigits[i] = (value >> (4*i)) & 0x0F;
    }
    for(int i = 7; i >= 0; --i) {
        if(hexDigits[i] >= 10) {
            printf("%c", 'A' + (hexDigits[i] - 10));
        }
        else {
            printf("%d", hexDigits[i]);
        }
    }
    printf("\n");
}

int main()
{
    unsigned int inputValue;
    int caseNumber = 1;

    while(scanf("%u", &inputValue) != EOF) {
        printf("Case %d: %u\n", caseNumber, inputValue);
        displayBinary(inputValue);
        displayOctal(inputValue);
        displayHexadecimal(inputValue);
        ++caseNumber;
    }
    return 0;
}
