#ifndef MAIN_WIFI_APP_H
#define MAIN_WIFI_APP_H

#include "esp_netif.h"

// WiFi application settings
#define WIFI_AP_SSID                "ESP32_AP"
#define WIFI_AP_PASSWORD            "123456789"
#define WIFI_AP_CHANNEL             1
#define  WIFI_AP_SSID_HIDDEN        0 // 0: Visible, 1: Hidden
#define WIFI_AP_MAX_CONNECTIONS     4 //AP maximum connections
#define WIFI_AP_BEACON_INTERVAL     100 // Beacon interval in milliseconds
#define WIFI_AP_IP                  "192.168.0.1" // AP default IP
#define WIFI_AP_GATEWAY             "192.168.0.1" // AP default gateway
#define WIFI_AP_NETMASK             "255.255.255.0" // AP default netmask
#define WIFI_AP_BANDWIDTH           WIFI_BW_HT20 // AP bandwidth 20MHz 
#define WIFI_STA_POWER_SAVE         WIFI_PS_NONE // STA power save mode - Power save disabled
#define MAX_SSID_LENGTH             32 // Maximum SSID length - IEEE 802.11 standard
#define MAX_PASSWORD_LENGTH         64 // Maximum password length - IEEE 802.11 standard
#define MAX_CONNECTION_RETRIES      5  // Maximum connection retries on disconnection

// Netwoerk interfaces for the Station and Access Point
extern esp_netif_t* esp_netif_sta;
extern esp_netif_t* esp_netif_ap;


/**
 * Message IDs for the Wifi application task
 * 
 */
typedef enum wifi_app_msg
{
    WIFI_APP_MSG_START_HTTP_SERVER = 0,
    WIFI_APP_MSG_CONNECTING_FROM_HTTP_SERVER,
    WIFI_APP_MSG_STA_CONNECTED_GOT_IP,

} wifi_app_msg_e;

/**
 *  Structure for the messagem queue
 */
typedef struct wifi_app_queue_message
{
    wifi_app_msg_e msgID; // Message ID
} wifi_app_queue_message_t;

/**
 * Sends a message to the Wifi application task queue
 * @param msgID Message ID from wifi_app_msg_e
 * @return pdTrRUE if the message was sent successfully, pdFALSE otherwise
 */

BaseType_t wifi_app_send_message(wifi_app_msg_e msgID);
/**
 * Starts the WIFi RTOS tast
 */

void wifi_app_start(void);

#endif /* MAIN_WIFI_APP_H */