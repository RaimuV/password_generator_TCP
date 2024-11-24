/*TCP CLIENT PROTOCOL*/
#ifndef PROTOCOL_H_INCLUDED
#define PROTOCOL_H_INCLUDED

#define PROTO_PORT 60000
#define BUFFER_SIZE 64

typedef struct {
    char psw_type;
    int psw_length;
} msg;

#endif // PROTOCOL_H_INCLUDED

