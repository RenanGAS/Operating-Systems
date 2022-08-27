#include <unistd.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    // write(fd, &buffer, bytes) 
    // fd: file descriptor

    write(1, "\nHello world!\n\n", 16); // 1: terminal; 13: número de caracteres

    exit(0);
}