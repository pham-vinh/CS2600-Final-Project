#include <mosquitto.h>
#include <stdio.h>


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
	while(1) {
		int result = mosquitto_loop(client, -1, 1);

		if (result) {
			fprintf(stderr, "Error: %s\n", mosquitto_strerror(result));
			break;
		}
	}
	// testing with a key stroke to send message to esp

	if (kbhit() && getch() == ' ') {
		mosquitto_publish(client, NULL, "esp32/led", 1, "1", 0, false);
	}
	return 0;
}
