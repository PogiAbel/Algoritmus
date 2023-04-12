#include <stdlib.h>
#include <stdio.h>

typedef struct Topic {
    char* topic_name;
    char* message;
    struct Topic* next;
} Topic;

void subscribe(Topic* topic, void (*callback)(char*)){
    while (topic != NULL) {
        callback(topic->message);
        topic = topic->next;
    }
}

void publish(Topic* topic, char* message){
    while (topic != NULL) {
        topic->message = message;
        topic = topic->next;
    }
}

void print_message(char* message){
    printf("%s\n", message);
}

int main(int argc, char const *argv[])
{
    // Example usage of topic and publish/subscribe
    Topic topic1;
    topic1.topic_name = "topic1";
    topic1.message = "message1";
    topic1.next = NULL;

    Topic topic2;
    topic2.topic_name = "topic2";
    topic2.message = "message2";
    topic2.next = NULL;

    topic1.next = &topic2;

    void (*callback)(char*) = print_message;
    subscribe(&topic1, callback);

    publish(&topic1, "message3");
    subscribe(&topic1, callback);

    return 0;
}
