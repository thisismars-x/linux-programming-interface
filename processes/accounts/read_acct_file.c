#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/acct.h>
#include <errno.h>
#include <time.h>

#define acctfile "./pacct"

int main() {
    int fd = open(acctfile, O_RDONLY);
    if (fd == -1) {
        perror("Failed to open accounting file");
        return 1;
    }

    struct acct record;
    ssize_t bytes_read;

    while ((bytes_read = read(fd, &record, sizeof(struct acct))) == sizeof(struct acct)) {
        printf("---------------------------\n");
        printf("Command name                :  %s\n", record.ac_comm);
        printf("Exit code                   :  %d\n", record.ac_exitcode);
        printf("Average memory used         :  %dkB\n", record.ac_mem);
        printf("Minor/Major page faults     :  %d/%d\n", record.ac_minflt, record.ac_majflt);
        printf("Number of swaps             :  %d\n", record.ac_swaps);
    }

    return 0;
}

