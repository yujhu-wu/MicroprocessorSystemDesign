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
