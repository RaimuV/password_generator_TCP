/* TCP CLIENT */

/*
 * AUTHORS: Angelo Giordano, (802019)Giuseppe Bruno (798106).
 */


#if defined WIN32
#include <winsock.h>  // Windows-specific socket headers
#define SHUT_WR 1      // Define SHUT_WR for Windows (since Windows uses numeric values)
#else
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <netdb.h>
#define closesocket close
#endif

#include <stdio.h>
#include "protocol.h"
#include "function.h"

// Cleanup function for Winsock
void clearwinsock() {
#if defined WIN32
    WSACleanup();
#endif
}

// Error handler
void errorhandler(const char *errorMessage) {
    printf("%s", errorMessage);
}

// Initialize Winsock (Windows)
int initialize_winsock() {
#if defined WIN32
    WSADATA wsa_data;
    if (WSAStartup(MAKEWORD(2, 2), &wsa_data) != 0) {
        printf("Error at WSAStartup()\n");
        return -1;
    }
#endif
    return 0;
}

// Create a socket
int create_socket() {
    int c_socket = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (c_socket < 0) {
        errorhandler("Socket creation failed.\n");
        return -1;
    }
    return c_socket;
}

// Connect to the server
int setup_connection(int c_socket) {
    struct sockaddr_in sad;
    memset(&sad, 0, sizeof(sad));
    sad.sin_family = AF_INET;
    sad.sin_addr.s_addr = inet_addr("127.0.0.1");
    sad.sin_port = htons(PROTO_PORT);

    if (connect(c_socket, (struct sockaddr *)&sad, sizeof(sad)) < 0) {
        errorhandler("Connection failed.\n");
        closesocket(c_socket);
        return -1;
    }
    return 0;
}

// User input
int get_user_input(char *psw_type, int *psw_length) {
    int input_check;
    do {
        input_check = read_input(psw_type, psw_length);
        if (input_check == 0) {
            printf("Invalid input. Please try again.\n");
        } else if (*psw_type == 'q') {
            return 1; // Quit
        }
    } while (input_check == 0);
    return 0;
}

// Send password request
int send_password_request(int c_socket, char psw_type, int psw_length) {
    msg m;
    m.psw_type = psw_type;
    m.psw_length = psw_length;
    if (send(c_socket, (char *)&m, sizeof(m), 0) != sizeof(m)) {
        errorhandler("Failed to send request.\n");
        return -1;
    }
    return 0;
}

// Receive password
int receive_generated_password(int c_socket, char *password) {
    printf("\nWaiting for server response...\n");
    if (recv(c_socket, password, MAX_PASSWORD_LENGTH + 1, 0) <= 0) {
        errorhandler("Connection closed prematurely.\n");
        return -1;
    }
    return 0;
}

// Cleanup
void client_cleanup(int c_socket) {
    shutdown(c_socket, SHUT_WR); // Inform server we're done sending
    closesocket(c_socket);
    clearwinsock();
}

// Main
int main() {
    if (initialize_winsock() < 0)
        return -1;

    int c_socket = create_socket();
    if (c_socket < 0)
        return -1;

    if (setup_connection(c_socket) < 0)
        return -1;

    while (1) {
        char psw_type;
        int psw_length = -1;

        if (get_user_input(&psw_type, &psw_length)) {
            printf("Client is exiting.\n");
            client_cleanup(c_socket);
            return 0;
        }

        if (send_password_request(c_socket, psw_type, psw_length) < 0) {
            client_cleanup(c_socket);
            return -1;
        }

        char password[MAX_PASSWORD_LENGTH + 1];
        if (receive_generated_password(c_socket, password) < 0) {
            client_cleanup(c_socket);
            return -1;
        }

        printf("\nGenerated password: %s\n\n", password);
    }

    client_cleanup(c_socket);
    return 0;
}
