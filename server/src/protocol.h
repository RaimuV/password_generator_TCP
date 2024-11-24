/*TCP SERVER PROTOCOL*/

#ifndef PROTOCOL_H_INCLUDED
#define PROTOCOL_H_INCLUDED

#define PROTO_PORT 60000
#define BUFFER_SIZE 64
#define QLEN 4 //(the server will support a number of clients equal to the value of qlen + 1. In this way it will support a maximum of 5 clients)

typedef struct {
    char psw_type;
    int psw_length;
} msg;

#endif // PROTOCOL_H_INCLUDED
