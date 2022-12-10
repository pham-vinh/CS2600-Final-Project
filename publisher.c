#include <stdio.h>
#include "mosquitto.h"


// need broker information
const char* broker_host = "test.mosquitto.org";
const int broker_port = 1883;

// using mosquitto mqtt
struct mosquitto* client;

int main(int argc, char const *argv[])
{
	
	// init Mosquitto client
	mosquitto_lib_init();

	// will use mosquitto documentation
	client = mosquitto_new("publisher", true, NULL);
	mosquitto_connect(client, broker_host, broker_port, 0);


	// have a while loop to listen from the broker

	// testing with a key stroke to send message to esp

	return 0;
}
