#ifndef MQTT_CLIENT_CONFIG_H_
#define MQTT_CLIENT_CONFIG_H_

#include "cy_mqtt_api.h"

/*******************************************************************************
* Macros
********************************************************************************/

/***************** MQTT CLIENT CONNECTION CONFIGURATION MACROS *****************/
/* MQTT Broker/Server address and port used for the MQTT connection. */
#define MQTT_BROKER_ADDRESS               "io.adafruit.com"
#define MQTT_PORT                         1883

/* Set this macro to 1 if a secure (TLS) connection to the MQTT Broker is
 * required to be established, else 0.
 */
#define MQTT_SECURE_CONNECTION            ( 0 )

/* Configure the user credentials to be sent as part of MQTT CONNECT packet */
#define MQTT_USERNAME                     "wesvr"
#define MQTT_PASSWORD                     "aio_ngkQ76L7NevMFM5bPGfSIkhdGwOm"


/********************* MQTT MESSAGE CONFIGURATION MACROS **********************/
/* The MQTT topics to be used by the publisher and subscriber. */
#define MQTT_PUB_TOPIC                    "ledstatus"
#define MQTT_SUB_TOPIC                    "wesvr/feeds/led"

/* Set the QoS that is associated with the MQTT publish, and subscribe messages.
 * Valid choices are 0, 1, and 2. Other values should not be used in this macro.
 */
#define MQTT_MESSAGES_QOS                 ( 1 )

/* Configuration for the 'Last Will and Testament (LWT)'. It is an MQTT message
 * that will be published by the MQTT broker if the MQTT connection is
 * unexpectedly closed. This configuration is sent to the MQTT broker during
 * MQTT connect operation and the MQTT broker will publish the Will message on
 * the Will topic when it recognizes an unexpected disconnection from the client.
 *
 * If you want to use the last will message, set this macro to 1 and configure
 * the topic and will message, else 0.
 */
#define ENABLE_LWT_MESSAGE                ( 0 )
#if ENABLE_LWT_MESSAGE
    #define MQTT_WILL_TOPIC_NAME          MQTT_PUB_TOPIC "/will"
    #define MQTT_WILL_MESSAGE             ("MQTT client unexpectedly disconnected!")
#endif

/* MQTT messages which are published on the MQTT_PUB_TOPIC that controls the
 * device (user LED in this example) state in this code example.
 */
#define MQTT_DEVICE_ON_MESSAGE            "ON"
#define MQTT_DEVICE_OFF_MESSAGE           "OFF"


/******************* OTHER MQTT CLIENT CONFIGURATION MACROS *******************/
/* A unique client identifier to be used for every MQTT connection. */
#define MQTT_CLIENT_IDENTIFIER            "psoc6-mqtt-client"

/* The timeout in milliseconds for MQTT operations in this example. */
#define MQTT_TIMEOUT_MS                   ( 5000 )

/* The keep-alive interval in seconds used for MQTT ping request. */
#define MQTT_KEEP_ALIVE_SECONDS           ( 60 )

/* Every active MQTT connection must have a unique client identifier. If you
 * are using the above 'MQTT_CLIENT_IDENTIFIER' as client ID for multiple MQTT
 * connections simultaneously, set this macro to 1. The device will then
 * generate a unique client identifier by appending a timestamp to the
 * 'MQTT_CLIENT_IDENTIFIER' string. Example: 'psoc6-mqtt-client5927'
 */
#define GENERATE_UNIQUE_CLIENT_ID         ( 1 )

/* The longest client identifier that an MQTT server must accept (as defined
 * by the MQTT 3.1.1 spec) is 23 characters. However some MQTT brokers support
 * longer client IDs. Configure this macro as per the MQTT broker specification.
 */
#define MQTT_CLIENT_IDENTIFIER_MAX_LEN    ( 23 )

/* As per Internet Assigned Numbers Authority (IANA) the port numbers assigned
 * for MQTT protocol are 1883 for non-secure connections and 8883 for secure
 * connections. In some cases there is a need to use other ports for MQTT like
 * port 443 (which is reserved for HTTPS). Application Layer Protocol
 * Negotiation (ALPN) is an extension to TLS that allows many protocols to be
 * used over a secure connection. The ALPN ProtocolNameList specifies the
 * protocols that the client would like to use to communicate over TLS.
 *
 * This macro specifies the ALPN Protocol Name to be used that is supported
 * by the MQTT broker in use.
 * Note: For AWS IoT, currently "x-amzn-mqtt-ca" is the only supported ALPN
 *       ProtocolName and it is only supported on port 443.
 *
 * Uncomment the below line and specify the ALPN Protocol Name to use this
 * feature.
 */
// #define MQTT_ALPN_PROTOCOL_NAME           "x-amzn-mqtt-ca"

/* Server Name Indication (SNI) is extension to the Transport Layer Security
 * (TLS) protocol. As required by some MQTT Brokers, SNI typically includes the
 * hostname in the Client Hello message sent during TLS handshake.
 *
 * Specify the SNI Host Name to use this extension
 * as specified by the MQTT Broker.
 */
#define MQTT_SNI_HOSTNAME                 (MQTT_BROKER_ADDRESS)

/* A Network buffer is allocated for sending and receiving MQTT packets over
 * the network. Specify the size of this buffer using this macro.
 *
 * Note: The minimum buffer size is defined by 'CY_MQTT_MIN_NETWORK_BUFFER_SIZE'
 * macro in the MQTT library. Please ensure this macro value is larger than
 * 'CY_MQTT_MIN_NETWORK_BUFFER_SIZE'.
 */
#define MQTT_NETWORK_BUFFER_SIZE          ( 2 * CY_MQTT_MIN_NETWORK_BUFFER_SIZE )

/* Maximum MQTT connection re-connection limit. */
#define MAX_MQTT_CONN_RETRIES            (150u)

/* MQTT re-connection time interval in milliseconds. */
#define MQTT_CONN_RETRY_INTERVAL_MS      (2000)


/**************** MQTT CLIENT CERTIFICATE CONFIGURATION MACROS ****************/

/* Configure the below credentials in case of a secure MQTT connection. */
/* PEM-encoded client certificate */
#define CLIENT_CERTIFICATE      \
"-----BEGIN CERTIFICATE-----\n"\
"MIID5DCCAsygAwIBAgIBADANBgkqhkiG9w0BAQsFADCBkDELMAkGA1UEBhMCR0Ix\n"\
"FzAVBgNVBAgMDlVuaXRlZCBLaW5nZG9tMQ4wDAYDVQQHDAVEZXJieTESMBAGA1UE\n"\
"CgwJTW9zcXVpdHRvMQswCQYDVQQLDAJDQTEWMBQGA1UEAwwNbW9zcXVpdHRvLm9y\n"\
"ZzEfMB0GCSqGSIb3DQEJARYQcm9nZXJAYXRjaG9vLm9yZzAeFw0yNDExMTUwOTUz\n"\
"MTdaFw0yNTAyMTMwOTUzMTdaMIG9MQswCQYDVQQGEwJCRTEQMA4GA1UECAwHTGlt\n"\
"YnVyZzEQMA4GA1UEBwwHSGFzc2VsdDERMA8GA1UECgwIVUhhc3NlbHQxDzANBgNV\n"\
"BAsMBlNjaG9vbDE6MDgGA1UEAwwxRW1yZSBEYWcICAgIG1tDG1tDG1tDG1tDG1tD\n"\
"G1tDG1tDG1tDCAgICAgICAgICBtbQzEqMCgGCSqGSIb3DQEJARYbZGFnCAgIZGFn\n"\
"ZW1yZTAyQGhvdG1haWwuY29tMIIBIjANBgkqhkiG9w0BAQEFAAOCAQ8AMIIBCgKC\n"\
"AQEA8BBPpsxlvjtqGbtDHqiYhpp/WpCrTUT1SoZgQJdIM4m1XSzdBLXsRmMXje79\n"\
"YhqXIiCY7pafwsGgIgB7SZForklhWC9ePfhClkD5Y0SyxyX8ofMq9bEchpQ/KVa4\n"\
"7tDMoSAxrrrpUmG8vrCiWfrbUUAly10RveyvMCwi2JGn330gRBIjpKUEjcKyQsAc\n"\
"PpjbIwp/NgUIyvWzLz4YNBlPUUqoRKSYuvlPk07B7WcDbw6oGudvQZz4p2vOIH69\n"\
"OsHE8xb3U6N4k9hZkSCji+WN5IQf/Uj/MPn9onlWOKUVmR4Maej4SwIZZxp7nheN\n"\
"TuqixuEl9fChiJVgbdMtKbaSawIDAQABoxowGDAJBgNVHRMEAjAAMAsGA1UdDwQE\n"\
"AwIF4DANBgkqhkiG9w0BAQsFAAOCAQEAQV5I7gDB3UlNz1XstHVtv1SsJSNg5URV\n"\
"5RxaKkxU11gB5xeguA3CYR2X264Y0yZRLIN1PAlNgxTc/Q4dQE15xg4S6jfQe/MP\n"\
"UbYLEiQEyAv4s3xGJbXHub0DKJYtGAA0LQI4oUeU45lsf3gksqjHF9f5jjpxsFHQ\n"\
"Q3f18ohC/WEQ/b/m5C+epW5DVKqsJUq32zptX1rqndijbv6smpXVq9RzmaoKPxfL\n"\
"Cv34+pTz66h+oliNhMW1w06O+I1r41lq2/bsrNL+rMQvfzG9Y3NA3MmdTXXnX1FN\n"\
"OAGOZJXW7AcpI77LDNoyQVna9f5JSshq5i9NDsyejCbyg7cjBkn+tA==\n"\
"-----END CERTIFICATE-----"


/* PEM-encoded client private key */
#define CLIENT_PRIVATE_KEY          \
"-----BEGIN PRIVATE KEY-----\n"\
"MIIEvgIBADANBgkqhkiG9w0BAQEFAASCBKgwggSkAgEAAoIBAQDwEE+mzGW+O2oZ\n"\
"u0MeqJiGmn9akKtNRPVKhmBAl0gzibVdLN0EtexGYxeN7v1iGpciIJjulp/CwaAi\n"\
"AHtJkWiuSWFYL149+EKWQPljRLLHJfyh8yr1sRyGlD8pVrju0MyhIDGuuulSYby+\n"\
"sKJZ+ttRQCXLXRG97K8wLCLYkafffSBEEiOkpQSNwrJCwBw+mNsjCn82BQjK9bMv\n"\
"Phg0GU9RSqhEpJi6+U+TTsHtZwNvDqga529BnPina84gfr06wcTzFvdTo3iT2FmR\n"\
"IKOL5Y3khB/9SP8w+f2ieVY4pRWZHgxp6PhLAhlnGnueF41O6qLG4SX18KGIlWBt\n"\
"0y0ptpJrAgMBAAECggEAFF315rCxsxrcV2mH+hposlwk5jye4/PanGOGgq8IZ6L3\n"\
"zvtm7FGORbHThkMFSU+jNziCcRTjYgUbvmFsaaNGDn9YRxXhuNU5ZQEHMjEFD+38\n"\
"9Ip/wGTcht3IoWEOWJNAwSzM5PD4/vh0KHjY6qm59gyWCEkRn8ZBs2RojReHzBHq\n"\
"BLEw3So9FBG46bIbSD5cdsW00h6pkuCsb758qWPdNSQMPIJ/S3kekLKKxdq1FoR1\n"\
"11/iY8JgZyWGe4wJ7x6XwUmQlybdNR7P3j+8wxNTkFiN0cC/j/sHPv8zmpCeL04Y\n"\
"zLYaHc29pQMWpegrM9Fp5ztA77XEjjufev+IxA8auQKBgQD9KwuXffk+U9OIpVZp\n"\
"MVb97tEe2HaqEsepN4YNEr5WQzf2VZQDH+AE25g/nMwjGCRKO8Mzg5lqBTaSF5cx\n"\
"kJauqUONNq/X/M9hHr7VlvTMvy15ZDmzkuotOCrqopNj1vF9juiGXBHWVFYN+9+z\n"\
"QalhvrFjH6IyxczkjLgDAeh56QKBgQDyv72tE9uzRgtyyWeoxLJNzPuhTscJ3NNM\n"\
"lBxtNHgc4gesd7LIg5som+3v4jxuk0QxaxFGZufqvTjxTj4PF2S+rSdodAqzYie4\n"\
"IZy61cYVKgeBSEDYR6cLFDnXtfNVauWEtkutdkjw3JqPrJIWsH2etnCYdRRqWy5P\n"\
"kulAOm1hMwKBgQDvNBa1wp8XFtkNiTrGFYpeT6FjBZ/JPglMh1uvSoBwvP5JT76T\n"\
"3TArJtkJcbsnhY30Xdcn+zWfCOHw0z1V5YmZ6fAbowouh33iA8zHvuP5+MCcq+gh\n"\
"FbURmLpkC8w7T0HJIpftK1znJ7RPbiaFFotWAXlVcPQuCNp5L8RFgy4G0QKBgQDt\n"\
"y/c7PWDTVaKRZ8ssAMPKgytc8Zb5imFTeyP9tpCTeriZswhodMPiHB4SCEW67Hi5\n"\
"EHFzzgsSYRsPB96zWe9O+sDICiURZO4T6plmTVQmF24Sr30WYdq5d67SKWOeIYGF\n"\
"aC7qVh1OFk0ywZK6t1nXyFC0iLzfE0NioD/us03DEQKBgDGZBwvG9bAxsXcy7fjc\n"\
"Fu6lTbK5bKR1Ym8aGQQcgiQsVrHMcDG3q2GwvDNMcofhl2FzqXnDFg5s5BL86w7w\n"\
"05rsytIvUbrY9hv1F9z5yS8S96M1hV/W6t6Ej8nQTpN7FaVWMXiCglFq3syQ5vTF\n"\
"dBvR8C4taYD+BWrdBCn+mT/6\n"\
"-----END PRIVATE KEY-----"


/* PEM-encoded Root CA certificate */
#define ROOT_CA_CERTIFICATE     \
"-----BEGIN CERTIFICATE-----\n" \
"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\n" \
"-----END CERTIFICATE-----"



/******************************************************************************
* Global Variables
*******************************************************************************/
extern cy_mqtt_broker_info_t broker_info;
extern cy_awsport_ssl_credentials_t  *security_info;
extern cy_mqtt_connect_info_t connection_info;


#endif /* MQTT_CLIENT_CONFIG_H_ */
