/*
    Component: DATA_PARSER
    Author: Rafael J. Scholtz
    Date: 15/08/2022
    Contents: Functions to serialize data from structs into a buffer to be
    transmitted by sockets. This is an app-level library.
*/

// to do: need 2 structures (for 8 and 16 bit samples); note: instead of enum do an uchar for id
// and later assign internal control variables to control buffer allocation

#include <stdio.h>
#include "DATA_PARSER.h"

// --- Global variables --- //
// Payload of fixed size aranged in 1-byte chars
unsigned char DATA_PAYLOAD_BUFFER1[7*DP_MAX_SAMPLE_BUFFER_SIZE + 7*DP_MAX_BUFFER_ID_SIZE]; // Constant buffer to be transmitted
unsigned char * DATA_PAYLOAD_BUFFER_ptr = &DATA_PAYLOAD_BUFFER1[0];




// ======= START OF TEST CODE ======= //

// Dummy payloads
int8_t payload_8_bits[DP_MAX_SAMPLE_BUFFER_SIZE];
int16_t payload_16_bits[DP_MAX_SAMPLE_BUFFER_SIZE];

// Pre-defined dummy buffer structs
// 1 word samples

//  -> Buffer 1
DP_SAMPLE_BUFFER_TYPE BUFFER1_8_bits = {
    .BUFFER_ID = REF_8_BITS;
};


// 2 word samples

//  -> Buffer 2
DP_SAMPLE_BUFFER_TYPE BUFFER2_16_bits = {
    .BUFFER_ID = VOLTAGE_16_BITS;
};

//  -> Buffer 3
DP_SAMPLE_BUFFER_TYPE BUFFER3_16_bits = {
    .BUFFER_ID = CURRENT_16_BITS;
};

//  -> Buffer 4
DP_SAMPLE_BUFFER_TYPE BUFFER4_16_bits = {
    .BUFFER_ID = CONTROL_ACTION_16_BITS;
};


// Test function to initialize arrays
void ARRAY_INIT(void)
{
    // Dummy arrays
    //  -> 1 word as [0, 1, 2, ..., DP_MAX_SAMPLE_BUFFER_SIZE-1]
    for(int i = 0; i<DP_MAX_SAMPLE_BUFFER_SIZE; i++)
        payload_8_bits[i] = i;

    //  -> 2 word as [DP_MAX_SAMPLE_BUFFER_SIZE, ..., 3, 2, 1]
    for(int i = 0; i<DP_MAX_SAMPLE_BUFFER_SIZE; i++)
        payload_16_bits[i] = DP_MAX_SAMPLE_BUFFER_SIZE - i;

    // Initializes array separately
    for(int i = 0; i<DP_MAX_SAMPLE_BUFFER_SIZE; i++)
        BUFFER1_8_bits.SAMPLE_BUFFER[i] = payload_8_bits[i];

    // Initializes array separately
    for(int i = 0; i<DP_MAX_SAMPLE_BUFFER_SIZE; i++)
        BUFFER2_16_bits.SAMPLE_BUFFER[i] = payload_16_bits[i];

    // Initializes array separately
    for(int i = 0; i<DP_MAX_SAMPLE_BUFFER_SIZE; i++)
        BUFFER3_16_bits.SAMPLE_BUFFER[i] = 100 + payload_16_bits[i];

    // Initializes array separately
    for(int i = 0; i<DP_MAX_SAMPLE_BUFFER_SIZE; i++)
        BUFFER4_16_bits.SAMPLE_BUFFER[i] = 200 + payload_16_bits[i];
}


// ======= END OF TEST CODE ======= //






// --- Public functions --- //

// Function: DP_SERIALIZE_BUFFER
// Input:
// Output: 
// Description: Serializes struct of type DP_SAMPLE_BUFFER_8_BITS_TYPE in buffer pointed by buffer_ptr
unsigned char * DP_serialize_buffer(unsigned char *buffer_ptr, DP_SAMPLE_BUFFER_TYPE * buffer)
{
    // Sends buffer ID
    buffer_ptr[0] = buffer->BUFFER_ID;

    // Shifts pointer
    buffer_ptr += 1;

    // Sends actual data
    for(int i = 0; i<DP_MAX_SAMPLE_BUFFER_SIZE; i++)
        buffer_ptr[i] = buffer->SAMPLE_BUFFER[i];
    
    // Returns pointer
    return buffer_ptr + DP_MAX_SAMPLE_BUFFER_SIZE;
}



// Function: DP_send_payload
// Input:
// Output: returns -1 if error occured, otherwise returns the number of bytes sent
// Description: Serializes first the 1-byte buffer, then the 3 2-byte buffers
// Note: this function currently only supports sending pre-defined structs (buffers)
int DP_send_payload(int sock)
{
    // Returns buffer to the beginning
    DATA_PAYLOAD_BUFFER_ptr = &DATA_PAYLOAD_BUFFER1[0];
    
    // Serializes buffer 1 (8 bits)
    DATA_PAYLOAD_BUFFER_ptr = DP_serialize_8_bit_buffer(DATA_PAYLOAD_BUFFER_ptr,  &BUFFER1_8_bits);

    // Serializes buffer 2 (16 bits)
    DATA_PAYLOAD_BUFFER_ptr = DP_serialize_16_bit_buffer(DATA_PAYLOAD_BUFFER_ptr,  &BUFFER2_16_bits);

    // Serializes buffer 3 (16 bits)
    DATA_PAYLOAD_BUFFER_ptr = DP_serialize_16_bit_buffer(DATA_PAYLOAD_BUFFER_ptr,  &BUFFER3_16_bits);

    // Serializes buffer 4 (16 bits)
    DATA_PAYLOAD_BUFFER_ptr = DP_serialize_16_bit_buffer(DATA_PAYLOAD_BUFFER_ptr,  &BUFFER4_16_bits);

    // Sends the data
    int err = send(sock, DATA_PAYLOAD_BUFFER1, sizeof(DATA_PAYLOAD_BUFFER1), 0);
    return err;
}



// --- Ignore record --- //

/*
void test(void)
{
    printf("component test\n");
}
*/

/*


// Function: DP_SERIALIZE_16_BIT_BUFFER
// Input:
// Output: 
// Description: Serializes struct of type DP_SAMPLE_BUFFER_16_BITS_TYPE in buffer pointed by buffer_ptr
unsigned char * DP_serialize_16_bit_buffer(unsigned char *buffer_ptr, DP_SAMPLE_BUFFER_16_BITS_TYPE * buffer_16_bits)
{
    // Sends string of variable label
    for(int i = 0; i<DP_MAX_VARIABLE_CHAR_NAME_SIZE; i++){
        buffer_ptr[i] = buffer_16_bits->VARIABLE_LABEL[i];
    }    
    // Moves pointer
    buffer_ptr += DP_MAX_VARIABLE_CHAR_NAME_SIZE;

    // Sends sample byte number
    buffer_ptr[0] = buffer_16_bits->SAMPLE_BYTE_NUMBER;

    // Shifts pointer
    buffer_ptr += 1;

    // Sends actual 16 bit data
    for(int i = 0; i<DP_MAX_SAMPLE_BUFFER_SIZE; i++){
        // Sends 8 most significative bits first
        buffer_ptr[i] = buffer_16_bits->SAMPLE_BUFFER[i] >> 8;
        buffer_ptr+=1; // Shifts pointer
        // Sends 8 least significative bits last
        buffer_ptr[i] = buffer_16_bits->SAMPLE_BUFFER[i];
        buffer_ptr+=1; // Shifts pointer again
    }

    // Returns pointer
    return buffer_ptr;
}


*/