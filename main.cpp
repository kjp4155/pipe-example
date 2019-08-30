#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> 

int main () {
    int x;
    int fromChild[2], fromParent[2];
    pipe(fromChild);
    pipe(fromParent);

    if ( fork() == 0 ) { // child
        dup2(fromParent[0], STDIN_FILENO);
        dup2(fromChild[1], STDOUT_FILENO);
        char* argv[1] = {0};
        // execvp("./adder", argv);
        system("python addmodule.py");
    }

    else { // parent
        int SIZE = 64;
        char buffer[SIZE];

        for (int i = 0; i < 10; i++) {
            int x = i;
            sprintf(buffer, "%d\n", x);
            write(fromParent[1], buffer, 2);
            printf("Send %d to adder\n", x);
            int nbytes = read(fromChild[0], buffer, SIZE);
            buffer[nbytes] = 0;
            printf("Return: %s\n", buffer);
        }
        
    }
}