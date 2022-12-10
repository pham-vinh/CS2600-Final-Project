#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hivemq/client/mqtt_client.h"


#define ADDRESS "tcp://localhost:1883"
#define CLIENTID "Publisher"
#define TOPIC "led"
#define PAYLOAD "on"
#define QOS 1
#define TIMEOUT 10000L

const char *broker_host = "test.mosquitto.org";
const int broker_port = 1883;

struct mosquitto *client;

int main(int argc, char const *argv[])
{
	
	// init Mosquitto client
	mosquitto_lib_init();

	client = mosquitto_new("publisher", true, NULL);
	mosquitto_connect(client, broker_host, broker_port, 0);

	while(1) {
		int result = mosquitto_loop(client, -1, 1);

		if(result) {
			fprintf(stderr, "Error: %s\n", mosquitto_strerror(result));
			break;
		}
	}

	if (getchar() == ' ') {
		mosquitto_publish(client, NULL, "esp/led", 1, "1", 0, false);
	}


	mosquitto_disconnect(client);
	mosquitto_lib_cleanup();

	return 0;
}
