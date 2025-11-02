#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <mqueue.h>
#include <errno.h>

int main(void) {
    const char *queue_name = "/mq0001";
    const char *message = "Hello from sender!";

    // Open or create the queue for writing
    mqd_t mqdes = mq_open(queue_name, O_CREAT | O_WRONLY, 0666, NULL);
    if (mqdes == (mqd_t)-1) {
        perror("mq_open failed");
        return EXIT_FAILURE;
    }

    // Send the message
    if (mq_send(mqdes, message, strlen(message), 0) == -1) {
        perror("mq_send failed");
        mq_close(mqdes);
        return EXIT_FAILURE;
    }

    printf("Sent: \"%s\"\n", message);

    mq_close(mqdes);
    return EXIT_SUCCESS;
}
