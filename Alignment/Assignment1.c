#include <stdio.h>

int main() {
    int a = 5;
    char c = 'a';
    double b = 1.2;
    short s = 5;

    printf("Integer at %p with size %lu: ", &a, sizeof(a));
    printf("Char at %p with size %lu: ", &c, sizeof(c));
    printf("Double at %p with size %lu: ", &b, sizeof(b));
    printf("Short at %p with size %lu: ", &s, sizeof(s));

    return 0;
}