//
// Created by Timothy Findlay on 2019-07-22.
//
// Using esp_http_client from:
//   https://docs.espressif.com/projects/esp-idf/en/latest/api-reference/protocols/esp_http_client.html
// Code:
//   https://github.com/espressif/esp-idf/blob/d7e659df2/components/esp_http_client/include/esp_http_client.h
// Status:
//   Cannot mix framework "arduino" + "espidf"
//

#ifndef HTTPSECURE_HTTP_POST_H
#define HTTPSECURE_HTTP_POST_H

static void send_https()
{
    // Configure connection
    esp_http_client_config_t config = {
            .url = "https://www.howsmyssl.com",
            .cert_pem = howsmyssl_com_root_cert_pem_start,
    };

    // Initialise the handler
    esp_http_client_handle_t client = esp_http_client_init(&config);

    // Establish the connection
    esp_err_t err = esp_http_client_perform(client);

    if (err == ESP_OK) {
        ESP_LOGI(TAG, "Status = %d, content_length = %d",
                 esp_http_client_get_status_code(client),
                 esp_http_client_get_content_length(client));
    } else {
        ESP_LOGI(TAG, "Status = %d", esp_err_to_name(err));
    }

    // Cleanup
    esp_http_client_cleanup(client);
}

#endif //HTTPSECURE_HTTP_POST_H
