#include <stdio.h>
#include <stdlib.h>

#include <mosquitto.h>

void on_connect(struct mosquitto *mosq, void *obj, int rc) {
    printf("ID: %d\n", * (int *) obj);

    if (rc) {
        printf("Error with result code: %d\n", rc);
        exit(-1);
    }

    mosquitto_subscribe(mosq, NULL, "ESP32/input", 0);
}

void on_message(struct mosquitto *mosq, void *obj, const struct mosquitto message *msg) {
    printf("New message with topic %s: %s\n", msg->topic, (char *) msg->payload);
}

int main() {
    int rc. id = 12;

    mosquitto_lib_init();

    struct mosquitto *mosq;

    mosq = mosquitto_new("subscribe-test", true, &id);

    mosquitto_connect_callback_set(mosq, on_connect);
    mosquitto_message_callback_set(mosq, on_connect);


    return EXIT_SUCCESS;
}