#include <stdio.h>
#include <stdint.h>
#include <string.h>

// A completely new struct for demonstration
typedef struct {
    uint32_t magic_number; // 4 bytes for a signature
    uint8_t flags;         // 1 byte for status flags
    char message[32];      // 32 bytes for the data message
} DataMessage;

// A new function to serialize the DataMessage struct
void pack_message(const DataMessage *msg, uint8_t *output_buffer) {
    // Pack the magic number (4 bytes)
    memcpy(output_buffer, &(msg->magic_number), sizeof(msg->magic_number));

    // Pack the flags (1 byte)
    memcpy(output_buffer + sizeof(msg->magic_number), &(msg->flags), sizeof(msg->flags));

    // Pack the message string (32 bytes)
    memcpy(output_buffer + sizeof(msg->magic_number) + sizeof(msg->flags), msg->message, sizeof(msg->message));
}

int main() {
    DataMessage myMessage = {
        .magic_number = 0x12345678,
        .flags = 0x01,
        .message = "Sending a message from a new program!"
    };

    // Allocate a buffer large enough for the new struct
    uint8_t output_buffer[sizeof(DataMessage)] = {0};
    
    // Call the new serialization function
    pack_message(&myMessage, output_buffer);

    printf("Serialized Data (Hex):\n");
    for (size_t i = 0; i < sizeof(DataMessage); i++) {
        printf("%02x ", output_buffer[i]);
    }
    printf("\n");

    return 0;
}