#include <iostream>
#include <cstring>
using namespace std;
static const int LEN = 1004;    //最多存储位数
int a[LEN], b[LEN], c[LEN];
//清空存储字符串
void clear(int a[]){
    for (int i = 0; i < LEN; ++i) {
        a[i] = 0;
    }
}
//读入字符串
void read(int a[]){
    static char s[LEN + 1];
    scanf("%s", s);

    clear(a);

    int len = strlen(s);
    for (int i = 0; i < len; ++i) {
        a[len - 1 - i] = s[i] - '0';
    }
}
//输出字符串
void print(int a[]){
    int i;
    for (i = LEN - 1; i >= 1; --i) {
        if(a[i] != 0) break;
    }
    for (; i >= 0; --i) {
        putchar(a[i] + '0');
    }
    putchar('\n');
}
//加法运算
void add(int a[], int b[], int c[]){
    clear(c);
    for(int i = 0; i < LEN - 1; ++i){
        c[i] += a[i] + b[i];
        if(c[i] >= 10){
            c[i + 1] += 1;
            c[i] -= 10;
        }
    }
}
//减法运算
void sub(int a[], int b[], int c[]){
    clear(c);
    for (int i = 0; i < LEN - 1; ++i) {
        c[i] += a[i] - b[i];
        if(c[i] < 0){
            c[i + 1] -= 1;
            c[i] += 10;
        }
    }
}
//高精度-单精度乘法
void mul_short(int a[], int b, int c[]){
    clear(c);

    for (int i = 0; i < LEN - 1; ++i) {
        c[i] += a[i] * b;
        if(c[i] >= 10){
            c[i + 1] += c[i] / 10;
            c[i] %= 10;
        }
    }
}
//高精度-高精度乘法
void mul(int a[], int b[], int c[]){
    clear(c);

    for (int i = 0; i < LEN - 1; ++i) {
        //结果位上每一位c[i + j] = a[i] + b[j]
        for (int j = 0; j <= i; ++j) {
            c[i] += a[j] * b[i - j];
        }

        if(c[i] >= 10){
            c[i + 1] += c[i] / 10;
            c[i] %= 10;
        }
    }
}
//被除数a以下标last_dg为最低位，是否可以再减去除数b而保持非负
//len是除数b的长度，避免重复计算
bool greater_eq(int a[], int b[], int last_dg, int len){
    //有可能被除数剩余部分比除数长，这个情况下最多多出1位，故如此判断即可
    if(a[last_dg + len] != 0) return true;
    //从高到低，逐位比较
    for (int i = len - 1; i >= 0; --i) {
        if(a[last_dg + i] > b[i]) return true;
        if(a[last_dg + i] < b[i]) return false;
    }
    //相等情况也是可以的
    return true;
}

void div(int a[], int b[], int c[], int d[]){
    clear(c);
    clear(d);
    //找到第一位非0的
    int la, lb;
    for (la = LEN - 1; la > 0; --la) {
        if(a[la - 1] != 0) break;
    }
    for(lb = LEN - 1; lb > 0; --lb){
        if(b[lb - 1] != 0) break;
    }

    if(lb == 0){
        puts("><");
        return;
    }   //除数不能为0

    //c是商
    //d是被除数的剩余部分，算法结束后自然成为余数
    for (int i = 0; i < la; ++i) {
        d[i] = a[i];
    }
    for (int i = la - lb; i >= 0; --i) {
        //计算商的第i位
        while(greater_eq(d, b, i, lb)){
            //若可以减，则减
            //这是一个高精度减法
            for (int j = 0; j < lb; ++j) {
                d[i + j] -= b[i];
                if(d[i + j] < 0){
                    d[i + j + 1] -= 1;
                    d[i + j] += 10;
                }
            }
            //使商的这一位增加1
            c[i] += 1;
            //返回循环开头，重新检查
        }
    }
}

