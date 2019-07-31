//
// Created by Timothy Findlay on 2019-07-30.
//

#include <HTTPClient.h>

#ifndef HTTPSECURE_HTTP_LOG_H
#define HTTPSECURE_HTTP_LOG_H

/**
 * Function to log events to a remote HTTP web service (eg. Logz.io)
 * @param serverAddress IP/Host name to connect to
 * @param port TCP Port to use
 * @param uri Query string, such was token id
 * @param message_type Added the the URI to indicate the type of log entry
 * @param payload JSON payload to be sent in the body
 */
static void http_log(const char* serverAddress, int port, const char* uri, char* message_type, char* payload)
{
    HTTPClient httpClient;

    // Prepare the full URL based on the type and token which goes into the query string
    char *full_url = (char *)calloc(19 + strlen(serverAddress) + strlen(uri) + strlen(message_type), sizeof(char));
    sprintf(full_url, "http://%s:%d/%s&type=%s",serverAddress, port, uri, message_type);

    httpClient.begin(full_url);
    httpClient.addHeader("Content-Type", "application/json");

    // Send the request
    int result_code = httpClient.POST(payload);

    // Check the result code
    if(result_code != 200) {
        Serial.print("Attempted URL:");
        Serial.println(full_url);

        Serial.print("Error sending, response Code: ");
        Serial.println(result_code);

        Serial.print("Response:");
        Serial.println(httpClient.getString());
    }

    // Clean up after sending
    httpClient.end();
    free(full_url);
}

/**
 * Helper method to assemble a standard message based on input parameters
 * @param ts Timestamp of when the event is captured
 * @param ip_string Our IP address to identify the source of the logged entry
 * @param dbValue sound level observed
 * @return Text string containing JSON data from parameters passed in
 */
static char* prepare_payload(char* ts, const char* ip_string, float dbValue) {

    // Prepare a JSON payload to send to a HTTP end point
    // Allocate:
    //   50 for the fixed text
    //   ip_string
    //   ts
    //   5 for dbvalue
    char *jsonPayload = (char *)calloc(55 + strlen(ip_string) + strlen(ts), sizeof(char));
    sprintf(jsonPayload, "{ \"captured_at\": \"%s\", \"ip_address\": \"%s\", \"level\": %.1f }", ts, ip_string, dbValue);
    return jsonPayload;
}

#endif //HTTPSECURE_HTTP_LOG_H
