#include <stdio.h>

int main(){
    int a=0xaaaaaaaa;
    a=a>>4;
    printf("%x",a);
}