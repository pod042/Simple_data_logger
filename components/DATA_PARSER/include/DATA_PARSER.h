/*
    Component: DATA_PARSER
    Author: Rafael J. Scholtz
    Date: 23/08/2022
    Contents: Functions to serialize data from structs into a buffer to be
    transmitted by sockets. This is an app-level library.
*/

// --- Includes --- //
#include "lwip/sockets.h"

// --- Defines --- //
// Each buffer has an ID to tell variable configurations
// e.g.: type of sample and bit size. Max ID size is 1 byte
#define DP_MAX_BUFFER_ID_SIZE 1

// Can be altered for tests
// 200 implies that, for 7 bytes per time/sample -> ~1400 bytes payload
#define DP_MAX_SAMPLE_BUFFER_SIZE 200 


// --- DATA TYPES --- //

// Message type enum - holds up to 1 byte (not as right now though)
typedef enum
{
    // 8 bits samples - starts at 0
    REF_8_BITS = 0,
    VOLTAGE_8_BITS,
    CURRENT_8_BITS,
    CONTROL_ACTION_8_BITS,
    // 16 bits samples
    REF_16_BITS,
    VOLTAGE_16_BITS,
    CURRENT_16_BITS,
    CONTROL_ACTION_16_BITS,
    NUM_OF_SAMPLE_TYPES
}DP_BUFFER_ID_TYPE;

// Sample buffer
typedef struct
{
    /* data */
    DP_BUFFER_ID_TYPE BUFFER_ID;
    uint8_t SAMPLE_BUFFER[DP_MAX_SAMPLE_BUFFER_SIZE];
}DP_SAMPLE_BUFFER_TYPE;

// --- Public functions --- //

// Serialize functions
unsigned char * DP_serialize_buffer(unsigned char *buffer_ptr, DP_SAMPLE_BUFFER_8_BITS_TYPE * buffer_8_bits);
//unsigned char * DP_serialize_16_bit_buffer(unsigned char *buffer_ptr, DP_SAMPLE_BUFFER_16_BITS_TYPE * buffer_16_bits);

// ============ TEST FUNCTION ============== //
void ARRAY_INIT(void);

// Utility functions (gather other functions in 1)

// This function currently only sends pre-defined structs (buffers)
int DP_send_payload(int sock);


// --- Ignore record --- //

//void test();

/*
// 16 bit sample buffer with label
typedef struct
{
    char VARIABLE_LABEL[DP_MAX_VARIABLE_CHAR_NAME_SIZE];
    unsigned char SAMPLE_BYTE_NUMBER;
    uint16_t SAMPLE_BUFFER[DP_MAX_SAMPLE_BUFFER_SIZE];
}DP_SAMPLE_BUFFER_16_BITS_TYPE;
*/