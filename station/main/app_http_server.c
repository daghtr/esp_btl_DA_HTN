#include "app_http_server.h"
#include <esp_wifi.h>
#include <esp_event.h>
#include <esp_log.h>
#include <esp_system.h>
#include <sys/param.h>
#include "esp_netif.h"
#include <esp_http_server.h>

/* A simple example that demonstrates how to create GET and POST
 * handlers for the web server.
*/

/* dia chi bat dau va dia chi ket thuc cua noi dung hinh anh */
extern const uint8_t index_html_start[] asm("_binary_webserver_html_start");
extern const uint8_t index_html_end[] asm("_binary_webserver_html_end");

static const char *TAG = "example";
static httpd_handle_t server = NULL;    // static de chi cho phep dung trong file .c nay k cho dung ra ben ngoai

/* An HTTP GET handler */
static esp_err_t http_get_handler(httpd_req_t *req)
{
    char*  buf;
    size_t buf_len;

    /* Send response with custom headers and body set as the */
    /* string passed in user context */
    httpd_resp_set_type(req, "text/html");
    
    /* const char* resp_str = (const char*) "ESP32 Response";
    httpd_resp_send(req, resp_str, strlen(resp_str)); */

    const char* resp_str = (const char*) index_html_start;
    httpd_resp_send(req, resp_str, index_html_end - index_html_start);

    return ESP_OK;
}

static const httpd_uri_t http_get = {
    .uri       = "/get",
    .method    = HTTP_GET,
    .handler   = http_get_handler,
    /* Let's pass response string in user */
    /* context to demonstrate it's usage */
    .user_ctx  = "Hello World!"
};

/* An HTTP GET handler */
static esp_err_t dht11_handler(httpd_req_t *req)
{
    char res[100] = "";
    float temp = 50.25;
    float hum = 80.91;
    // float temp = dht
    sprintf(res, "{\"Temperature\": \"%.02f\", \"Humidity\": \"%.02f\"}", temp, hum);
    httpd_resp_send(req, res, strlen(res));
    return ESP_OK;
}

static const httpd_uri_t http_dht11 = {
    .uri       = "/dht11",
    .method    = HTTP_GET,
    .handler   = dht11_handler,
    /* Let's pass response string in user */
    /* context to demonstrate it's usage */
    .user_ctx  = "Hello World!"
};

/* An HTTP POST handler */
static esp_err_t http_post_handler(httpd_req_t *req)
{
    char buf[100];
    int ret, data_length = req->content_len;

    // while (data_length > 0) {
        /* Read the data for the request */
        httpd_req_recv(req, buf, data_length);
        /* Log data received */
        ESP_LOGI(TAG, "Data recv: %s", buf);
    // }

    // End response
    httpd_resp_send_chunk(req, NULL, 0);
    return ESP_OK;
}

static const httpd_uri_t http_post = {
    .uri       = "/post",
    .method    = HTTP_POST,
    .handler   = http_post_handler,
    .user_ctx  = NULL
};

/* An HTTP POST handler */
static esp_err_t sw1_handler(httpd_req_t *req)
{
    char buf[100];
    int ret, data_length = req->content_len;

    // while (data_length > 0) {
        /* Read the data for the request */
        httpd_req_recv(req, buf, data_length);
        /* Log data received */
        ESP_LOGI(TAG, "Data recv: %s", buf);
    // }

    // End response
    httpd_resp_send_chunk(req, NULL, 0);
    return ESP_OK;
}

static const httpd_uri_t http_sw1 = {
    .uri       = "/sw1",
    .method    = HTTP_POST,
    .handler   = sw1_handler,
    .user_ctx  = NULL
};

/* This handler allows the custom error handling functionality to be
 tested from client side. For that, when a PUT request 0 is sent to
 URI /ctrl, the /hello and /echo URIs are unregistered and following
 custom error handler http_404_error_handler() is registered.
 Afterwards, when /hello or /echo is requested, this custom error
 handler is invoked which, after sending an error message to client,
 either closes the underlying socket (when requested URI is /echo)
 or keeps it open (when requested URI is /hello). This allows the
 client to infer if the custom error handler is functioning as expected
 by observing the socket state.
*/
// esp_err_t http_404_error_handler(httpd_req_t *req, httpd_err_code_t err)
// {
//     if (strcmp("/hello", req->uri) == 0) {
//         httpd_resp_send_err(req, HTTPD_404_NOT_FOUND, "/hello URI is not available");
//         /* Return ESP_OK to keep underlying socket open */
//         return ESP_OK;
//     } else if (strcmp("/echo", req->uri) == 0) {
//         httpd_resp_send_err(req, HTTPD_404_NOT_FOUND, "/echo URI is not available");
//         /* Return ESP_FAIL to close underlying socket */
//         return ESP_FAIL;
//     }
//     /* For any other URI send 404 and close socket */
//     httpd_resp_send_err(req, HTTPD_404_NOT_FOUND, "Some 404 error message");
//     return ESP_FAIL;
// }

void start_webserver(void)
{
    httpd_config_t config = HTTPD_DEFAULT_CONFIG();
    config.lru_purge_enable = true;

    // Start the httpd server
    ESP_LOGI(TAG, "Starting server on port: '%d'", config.server_port);
    if (httpd_start(&server, &config) == ESP_OK) {
        // Set URI handlers
        ESP_LOGI(TAG, "Registering URI handlers");
        httpd_register_uri_handler(server, &http_get);
        httpd_register_uri_handler(server, &http_post);
        httpd_register_uri_handler(server, &http_dht11);
        httpd_register_uri_handler(server, &http_sw1);
    }
}

void stop_webserver(void)
{
    // Stop the httpd server
    httpd_stop(server);
}
