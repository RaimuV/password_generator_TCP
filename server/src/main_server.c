/* TCP SERVER */

/*
 * AUTHORS: Angelo Giordano, (802019)Giuseppe Bruno (798106).
 */

#if defined WIN32
    #include <winsock.h> // Windows socket library
#else
    #include <string.h>    // Standard string operations (e.g., memset)
    #include <unistd.h>    // For UNIX system calls like close
    #include <sys/types.h> // For system data types
    #include <sys/socket.h> // For socket-related functions
    #include <arpa/inet.h>  // For inet_addr() function to convert IP addresses
    #include <netinet/in.h> // For sockaddr_in structure definition
    #include <netdb.h>      // For network-related functions
    #define closesocket close // Define closesocket as close for UNIX-like systems
#endif

#include <stdio.h> // Standard I/O for printf and error messages
#include <ctype.h> // For character classification functions (e.g., isalpha, isdigit)
#include "protocol.h"  // Custom header for protocol constants (e.g., PROTO_PORT)
#include "psw_function.h" // Custom header for password generation logic

// Function to clean up Winsock on Windows systems
void clearwinsock() {
#if defined WIN32
    WSACleanup(); // Clean up Winsock library in Windows systems
#endif
}

// Function to handle error messages and display them
void errorhandler(const char *errorMessage) {
    printf("%s", errorMessage); // Print the error message
}

// Function to initialize Winsock for Windows systems
int initialize_winsock() {
#if defined WIN32
    WSADATA wsa_data;
    int result = WSAStartup(MAKEWORD(2, 2), &wsa_data);
    if (result != NO_ERROR) {
        printf("Error at WSAStartup()\n");
        return 0; // Return failure if Winsock initialization fails
    }
#endif
    return 1; // Success for other systems
}

// Main server function
int main(int argc, char *argv[]) {
    // Disable buffering for stdout to immediately print messages to the console
    setbuf(stdout, NULL);

    // Initialize random number generation for password creation
    initialize_random(); // A function to seed the random number generator

    // Initialize Winsock (only on Windows)
    if (!initialize_winsock()) {
        return -1; // Exit if Winsock initialization fails on Windows
    }

    // Create the server socket for accepting client connections
    int my_socket = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (my_socket < 0) {
        errorhandler("Socket creation failed.\n");
        clearwinsock(); // Clean up Winsock if applicable
        return -1;
    }

    // Set the server address settings (bind to localhost)
    struct sockaddr_in sad;
    memset(&sad, 0, sizeof(sad)); // Zero out the sockaddr_in structure
    sad.sin_family = AF_INET;        // Use IPv4 addressing
    sad.sin_addr.s_addr = inet_addr("127.0.0.1");  // Localhost
    sad.sin_port = htons(PROTO_PORT);               // Use the defined port

    // Bind the socket to the specified address and port
    if (bind(my_socket, (struct sockaddr*) &sad, sizeof(sad)) < 0) {
        errorhandler("Bind failed.\n");
        closesocket(my_socket);
        clearwinsock();
        return -1;
    }

    // Set the socket to listen for incoming connections
    if (listen(my_socket, QLEN) < 0) {
        errorhandler("Listen failed.\n");
        closesocket(my_socket);
        clearwinsock();
        return -1;
    }

    printf("Server is listening...\n");

    // Accept client connections in a loop
    struct sockaddr_in cad;    // Structure to hold client address
    int client_socket;         // Client socket descriptor for communication

    // Define the client length (different for Windows and UNIX-like systems)
#if defined WIN32
    int client_len = sizeof(cad);  // Use int for client length on Windows
#else
    socklen_t client_len = sizeof(cad);  // Use socklen_t for client length on UNIX-like systems
#endif

    // Main loop for accepting client connections
    while (1) {
        printf("\nWaiting for a client to connect...\n");

        // Accept a new connection from a client
        if ((client_socket = accept(my_socket, (struct sockaddr*) &cad, &client_len)) < 0) {
            errorhandler("Accept failed.\n");
            closesocket(client_socket);
            clearwinsock();
            return 0;
        }

        // Print client connection details
        printf("New connection from %s:%d\n", inet_ntoa(cad.sin_addr), ntohs(cad.sin_port));

        // Handle password generation and communication with the client
        while (1) {
            msg m;

            // Receive the message from the client
            if (recv(client_socket, (char*)&m, sizeof(msg), 0) <= 0) {
                printf("Connection closed by client or recv failed.\n");
                break; // Exit if the connection is closed or receiving fails
            }

            printf("Received request - psw_type: %c, psw_length: %d\n", m.psw_type, m.psw_length);

            // Check if the client requested to quit ('q')
            if (m.psw_type == 'q') {
                printf("Client requested to quit. Closing connection...\n");
                break; // Exit the loop when client sends 'q'
            }

            // Generate the password based on the received message
            char password[MAX_PASSWORD_LENGTH + 1];
            generate_password(m.psw_type, m.psw_length, password); // Password generation logic

            // Send the generated password back to the client
            if (send(client_socket, password, sizeof(password), 0) != sizeof(password)) {
                errorhandler("Send failed. Sent a different number of bytes than expected.\n");
                closesocket(client_socket);
                break;
            }
        }

        closesocket(client_socket); // Close the client socket after handling the client
        printf("Connection closed. Server is still listening...\n");
    }

    // Close the server socket when done
    closesocket(my_socket);
    clearwinsock();  // Clean up Winsock if applicable
    return 0; // End of main function
}
