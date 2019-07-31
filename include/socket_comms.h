//
// Created by Timothy Findlay on 2019-07-28.
//

#ifndef HTTPSECURE_SOCKET_SEND_H
#define HTTPSECURE_SOCKET_SEND_H

#include <sys/socket.h>
#include "dencrypt.h"

/**
 * @brief Sends fixed command to switch on a TP-Link Smart Switch
 * @param device_ip IP address of the TP Link Smart Switch eg. 10.10.10.10
 */
static void switch_on(const char *device_ip)
{
    // Setup static input/command to issues to the device
    const char command[] = "{\"system\":{\"set_relay_state\":{\"state\":1}}}";
    int network_socket;

    // Configure the network socket type to use
    network_socket = socket(AF_INET, SOCK_STREAM, 0);

    // Configure the server object /w port to connect to
    struct sockaddr_in server_address;
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(9999);
    server_address.sin_addr.s_addr = inet_addr(device_ip);

    // Make the connection
    int connection_status = connect(network_socket, (struct sockaddr *) &server_address, sizeof(server_address));

    // Check it connected before doing anything else
    if(connection_status == 0) {

        // Calculate the size of the payload
        size_t payload_size = strlen(command) + sizeof(unsigned int);

        // Prepare the payload to send...
        unsigned char *payload = (unsigned char *)calloc(payload_size, sizeof(unsigned char));
        encrypt(command, payload, strlen(command));

        // Send to the switch
        send(network_socket, payload, payload_size, 0);

        // TODO call recv() to check the TP Link switch got the message

    } else {
        Serial.println("Error connecting");
    }

    close(network_socket);
}

/**
 * @brief Sends fixed command to switch off a TP-Link Smart Switch
 * @param device_ip IP address of the TP Link Smart Switch eg. 10.10.10.10
 */
static void switch_off(const char *device_ip)
{
    // Setup static input/command to issues to the device
    const char command[] = "{\"system\":{\"set_relay_state\":{\"state\":0}}}";
    int network_socket;

    // Configure the network socket type to use
    network_socket = socket(AF_INET, SOCK_STREAM, 0);

    // Configure the server object /w port to connect to
    struct sockaddr_in server_address;
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(9999);
    server_address.sin_addr.s_addr = inet_addr(device_ip);

    // Make the connection
    int connection_status = connect(network_socket, (struct sockaddr *) &server_address, sizeof(server_address));

    // Check it connected before doing anything else
    if(connection_status == 0) {

        // Calculate the size of the payload
        size_t payload_size = strlen(command)+ sizeof(unsigned int);

        // Prepare the payload to send...
        unsigned char *payload = (unsigned char *)calloc(payload_size, sizeof(unsigned char));
        encrypt(command, payload, strlen(command));

        // Send to the switch
        send(network_socket, payload, payload_size, 0);

        // TODO call recv() to check the TP Link switch got the message

    } else {
        Serial.println("Error connecting");
    }

    close(network_socket);
}

#endif //HTTPSECURE_SOCKET_SEND_H
