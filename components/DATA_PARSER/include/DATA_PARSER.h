/*
    Component: DATA_PARSER
    Author: Rafael J. Scholtz
    Date: 15/08/2022
    Contents: Functions to serialize data from structs into a buffer to be
    transmitted by sockets. This is an app-level library.
*/

// --- Defines -- //
#define MAX_VARIABLE_CHAR_NAME_SIZE 5

// Can be altered for tests
// 200 implies that, for 7 bytes per time/sample -> ~1400 bytes payload
#define MAX_SAMPLE_BUFFER_SIZE 200 


// --- DATA TYPES --- //
// 8 bit sample buffer with label
typedef struct
{
    /* data */
    char VARIABLE_LABEL[MAX_VARIABLE_CHAR_NAME_SIZE];
    int8_t SAMPLE_BUFFER[MAX_SAMPLE_BUFFER_SIZE];
}SAMPLE_BUFFER_8_BITS_TYPE;

// 16 bit sample buffer with label
typedef struct
{
    /* data */
    char VARIABLE_LABEL[MAX_VARIABLE_CHAR_NAME_SIZE];
    int8_t SAMPLE_BUFFER[MAX_SAMPLE_BUFFER_SIZE];
}SAMPLE_BUFFER_16_BITS_TYPE;

// --- Ignore register --- //

//void test();
