#include <stdio.h>
#include <unistd.h>

int main() {
    int x = 0;
    while( true ){
        scanf("%d",&x);
        printf("%d\n",x+1);
        fflush(stdout);
    }
}