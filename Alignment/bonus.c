#include <stdio.h>

#pragma pack(4)
struct MyStruct1 {
    char a;
    int b;
    double c;
};
#pragma pack()

#pragma pack(2)
struct MyStruct2 {
    char a;
    int b;
    double c;
};
#pragma pack()

int main() {
    struct MyStruct1 ms1;
    struct MyStruct2 ms2;

    printf("sizeof(ms1) = %lu\n", sizeof(ms1));
    printf("sizeof(ms2) = %lu\n", sizeof(ms2));

    printf("ms1.a at %p\n", &(ms1.a));
    printf("ms1.b at %p\n", &(ms1.b));
    printf("ms1.c at %p\n", &(ms1.c));
    printf("ms2.a %p\n", &(ms2.a));
    printf("ms2.b %p\n", &(ms2.b));
    printf("ms2.c %p\n", &(ms2.c));

    return 0;
}