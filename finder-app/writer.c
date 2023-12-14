#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <syslog.h>

int main(int argc, char *argv[])
{
    int fd = 0;
    char *filename = NULL;
    char *string = NULL;
    int writeret = 0;

    if(argc != 3)
    {
        printf("Error: Please provide two arguments\n");
        fprintf(stderr, "Usage: %s <filename> <string>\n", argv[0]);
        exit(1);
    }
    filename = argv[1];
    string = argv[2];
    openlog(argv[0], LOG_PID | LOG_CONS, LOG_USER);
    syslog(LOG_DEBUG, "Writing '%s' to '%s'", string, filename);
    fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0664);
    if (fd == -1)
    {
        syslog(LOG_ERR, "Failed to open file '%s': %m", filename);
        close(fd);
        exit(1);
    }
    writeret = write(fd, string, strlen(string));
    if(writeret == -1)
    {
        syslog(LOG_ERR, "Failed to write to file '%s': %m", filename);
        close(fd);
        exit(1);
    }
    syslog(LOG_DEBUG, "Successfully wrote to file '%s'", filename);
    close(fd);
    closelog();

    return 0;
}