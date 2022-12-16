#include <stdio.h>
#include <stdlib.h>
#include <mosquitto.h>


int main(int argc, char* argv[])
{

    int rc;

    struct mosquitto * mosq;
    
    mosquitto_lib_init();

    mosq = mosquitto_new("publisher-test", true, NULL);
    
    rc = mosquitto_connect(mosq, "test.mosquitto.org", 1883, 60);

    if (rc != 0) {
        printf("Client could not connect to broker! Error Code: %d\n", rc);
        mosquitto_destroy(mosq);
        return -1;
    }

    printf("We are now connected to the broker!\n");

    // has to be a pointer for any type
    mosquitto_publish(mosq, NULL, "ESP32/input", 6, "Hello", 0, false);
    
    mosquitto_disconnect(mosq);
    mosquitto_destroy(mosq);

    mosquitto_lib_cleanup();
    return EXIT_SUCCESS;
}