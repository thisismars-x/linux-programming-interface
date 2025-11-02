#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <mqueue.h>
#include <errno.h>

int main(void) {
    const char *queue_name = "/mq0001";

    // Open or create the queue for reading
    mqd_t mqdes = mq_open(queue_name, O_CREAT | O_RDONLY, 0666, NULL);
    if (mqdes == (mqd_t)-1) {
        perror("mq_open failed");
        return EXIT_FAILURE;
    }

    // Get queue attributes
    struct mq_attr attr;
    if (mq_getattr(mqdes, &attr) == -1) {
        perror("mq_getattr failed");
        mq_close(mqdes);
        return EXIT_FAILURE;
    }

    // Allocate message buffer
    char *msg = calloc(attr.mq_msgsize + 1, sizeof(char));
    if (!msg) {
        perror("calloc failed");
        mq_close(mqdes);
        return EXIT_FAILURE;
    }

    // Wait and receive message
    ssize_t bytes = mq_receive(mqdes, msg, attr.mq_msgsize, NULL);
    if (bytes == -1) {
        perror("mq_receive failed");
        free(msg);
        mq_close(mqdes);
        return EXIT_FAILURE;
    }

    msg[bytes] = '\0'; // Null terminate
    printf("Received: \"%s\"\n", msg);

    free(msg);
    mq_close(mqdes);

    // Optional cleanup — uncomment when done testing:
    // mq_unlink(queue_name);

    return EXIT_SUCCESS;
}
