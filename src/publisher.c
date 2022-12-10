#include "hivemq/client/mqtt_client.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ADDRESS		"tcp://your-server-hostname-or-ip-address:1883"
#define CLIENTID	"Publisher"
#define TOPIC		"led"
#define PAYLOAD		"on"
#define QOS			1
#define TIMEOUT		10000L

int main(int argc, char* argv[])
{
    mqtt::client* client;
    mqtt::connect_options conn_opts;
    mqtt::message pubmsg;

    client = new mqtt::client(ADDRESS, CLIENTID);
    client->connect(conn_opts);

    if (argc > 1 && strcmp(argv[1], "on") == 0) {
        pubmsg.set_payload(PAYLOAD);
        pubmsg.set_qos(QOS);
        client->publish(TOPIC, pubmsg);
    }

    printf("Message '%s' with QoS %d sent to topic '%s'.\n", PAYLOAD, QOS, TOPIC);

    client->disconnect();
    delete client;

    return EXIT_SUCCESS;
}
