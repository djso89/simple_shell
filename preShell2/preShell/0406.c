#include <stdio.h>
#include <unistd.h>
#include <sys/types.h> // for getpid()

/**
 * main - execve example
 *
 * Return: Always 0.
 */
int main(void)
{
    pid_t pid;
    char *argv[] = {"/bin/ls", "-l", "/usr/", NULL}; // hint: argv very similar to av we created that takes user input...
													// as if user typed in shell: /bin/ls -l /usr/ (if they already had been seperated by spaces - associated array would look like *argv[] initiation line 11)
    printf("Before execve\n");
    pid = fork();
    printf("%d/n", pid); // demonstrate the pid after we fork 
    printf("PID: %d/n", getpid());

    if (execve(argv[0], argv, NULL) == -1) // int execve(const char *pathname, char *const argv[],char *const envp[]);
    {
        perror("Error:");
    }
    printf("After execve\n");
    return (0);
}
