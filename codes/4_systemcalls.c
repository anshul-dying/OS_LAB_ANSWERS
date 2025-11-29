#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>

int main()
{
    pid_t pid = fork();

    if(pid==0)
    {
        printf("Child Process\n");
        int fd = open("test.txt", O_CREAT | O_WRONLY, 0644);
        write(fd, "Hello System calls\n", 20);
        close(fd);
    }
    else
    {
        wait(NULL);
        printf("Patent Process Reading File:\n");

        int fd = open("test.txt", O_RDONLY);
        char buffer[50];
        read(fd, buffer, 50);
        printf("%s\n", buffer);
        close(fd);
    }

    return 0;
}