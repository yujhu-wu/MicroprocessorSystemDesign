# 位元運算加分題(6題)

> 微處理機系統 · 加分題 · [回到目錄](../README.md)

- **語言**：C

練習以位元運算(`&`、`|`、`<<`、`>>`、遮罩)處理整數，是控制暫存器與I/O的基礎。

## P1. 數字半位元組分割

將輸入的無號整數依每4個位元(nibble)切割並輸出。

[P1.c](P1.c)

```c
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
```

## P2. 數字系統轉換

以位元移位與遮罩，將整數轉成二進位、八進位、十六進位輸出。

[P2.c](P2.c)

```c
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
```

## P3. 檢查數字特定位元

檢查輸入數字的特定位元是否為1。

[P3.c](P3.c)

```c
//P3-檢查數字特定位元
#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 1000  // 設定陣列的最大大小

int main()
{
    int num;
    long long int num_;
    int cnt = 1;
    int check = 0;
    int check_cnt = 0;
    int v[MAX_SIZE];   // 用於存放輸入的數字
    int v_size = 0;    // 用來追踪陣列 v 的大小

    // 讀取數字並加入陣列，如果已存在則不加入
    while(scanf("%d", &num) == 1) {
        if(num == -1) break;  // 結束輸入

        // 檢查數字是否已存在於陣列中
        int found = 0;
        for(int i = 0; i < v_size; ++i) {
            if(v[i] == num) {
                found = 1;
                break;
            }
        }

        // 如果未找到則加入陣列
        if(!found) {
            v[v_size++] = num;
        }
    }

    // 冒泡排序，只執行一次交換
    for(int i = 0; i < v_size-1; ++i) {
        if(v[i] > v[i+1]) {
            int temp = v[i];
            v[i] = v[i+1];
            v[i+1] = temp;
        }
    }

    // 輸出排序後的數字
    for(int i = 0; i < v_size; ++i) {
        printf("%d ", v[i]);
    }
    printf("\n");

    // 處理每個輸入的 num_，並檢查其位元狀態
    while(scanf("%lld", &num_) == 1) {
        printf("Case %d: %lld\n", cnt, num_);

        // 檢查 num_ 的每個 v[i] 位元是否為 1
        for(int i = 0; i < v_size; ++i) {
            check = (num_ >> v[i]) & 0x01;  // 檢查 num_ 在 v[i] 位的值
            if(check == 1) ++check_cnt;
        }

        // 檢查所有位元是否都是 1
        if(check_cnt == v_size) {
            printf("true(all bits 1)\n");
        } else {
            printf("false(all bits 1)\n");
        }

        // 檢查是否存在至少一個 1 的位元
        if(check_cnt > 0 && check_cnt <= v_size) {
            printf("true(exist bits 1)\n");
        } else {
            printf("false(exist bits 1)\n");
        }

        ++cnt;
        check_cnt = 0;  // 重置計數器以便下一個輸入
    }

    return 0;
}
```

## P4. Packing Characters into an Integer

利用位元移位與OR，把多個字元打包進一個整數。

[P4.c](P4.c)

```c
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
```

## P5. Unpacking Characters from an Integer

利用遮罩與位元移位，從整數中取出被打包的字元。

[P5.c](P5.c)

```c
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
```

## P6. Reversing the Order of an Integer's Bits

將整數的位元順序反轉。

[P6.c](P6.c)

```c
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
```

