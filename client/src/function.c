/*
 * AUTHORS: Angelo Giordano, (802019)Giuseppe Bruno (798106).
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "function.h"

// Function to display the menu to the user
void show_menu() {
    printf("Type 'q' to quit.\n");
    printf("Available types:\n");
    printf("  n: Numeric password (digits only)\n");
    printf("  a: Alphabetic password (lowercase letters only)\n");
    printf("  m: Mixed password (lowercase letters and digits)\n");
    printf("  s: Secure password (uppercase, lowercase, digits, symbols)\n");
    printf("Length must be between %d and %d.\n", MIN_PASSWORD_LENGTH, MAX_PASSWORD_LENGTH);
    printf("\nEnter password type and length (e.g., n 8): ");
}

// Function to read and validate the user's input for password type and length
// Returns 1 if input is valid, 0 if invalid
int read_input(char* type, int* length) {
    /*
    return 1 -> valid string ( [char]<space>[int]<enter> OR [char]<enter> )
    return 0 -> invalid string
    */
    char buffer[50]; // Buffer to store the user input
    char input_type;
    int input_length;
    int tokens_read;

    show_menu();  // Display the menu

    // Read user input
    if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
        printf("Error reading input.\n");
        return 0;
    }

    // Remove any trailing newline character
    buffer[strcspn(buffer, "\n")] = '\0';

    // Try to parse the input into a character and an integer (type and length)
    tokens_read = sscanf(buffer, "%c %d", &input_type, &input_length);

    // Case 1: If input is a single character (e.g., 'q')
    if (tokens_read == 1) {
        // If the user typed 'q', it's a valid exit command
        if (input_type == 'q') {
            *type = 'q';
            return 1;  // Exit command received
        }

        // If the character is not a valid password type, reject input
        if (input_type != 'n' && input_type != 'a' && input_type != 'm' && input_type != 's') {
            printf("Invalid input. Use 'n', 'a', 'm', 's' (with length) or 'q' to quit.\n");
            return 0;
        }

        // If only a type is given, the length is mandatory
        printf("Length is required for types 'n', 'a', 'm', and 's'.\n");
        return 0;
    }

    // Case 2: If input contains both a type character and a length (e.g., 'n 8')
    if (tokens_read == 2) {
        // Check if the password type is valid
        if (input_type != 'n' && input_type != 'a' && input_type != 'm' && input_type != 's') {
            printf("Invalid password type. Use 'n', 'a', 'm', or 's'.\n");
            return 0;
        }

        // Check if the length is within valid bounds
        if (input_length < MIN_PASSWORD_LENGTH || input_length > MAX_PASSWORD_LENGTH) {
            printf("Invalid password length. Must be between %d and %d.\n", MIN_PASSWORD_LENGTH, MAX_PASSWORD_LENGTH);
            return 0;
        }

        // Valid input: set type and length
        *type = input_type;
        *length = input_length;
        return 1;  // Return success
    }

    // Invalid input format: user didn't provide a valid type and length
    printf("Invalid input format. Use: <type> <length> (e.g., n 8) or 'q' to quit.\n");
    return 0;  // Return failure
}

// Function to print the generated password
void print_password(const char* password) {
    if (password[0] != '\0') {  // Ensure the password is not empty
        printf("Generated password: %s\n", password);  // Print the password
    }
}
