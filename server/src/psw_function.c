/*
 * AUTHORS: Angelo Giordano, (802019)Giuseppe Bruno (798106).
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "psw_function.h"

// Main password generation function
// Takes the type of password (type) and the desired length (length),
// and generates the password by calling the appropriate generation function.
void generate_password(char type, int length, char* password) {
    switch (type) {
        case 'n':
            // If type is 'n', generate a numeric password.
            generate_numeric(length, password);
            break;
        case 'a':
            // If type is 'a', generate an alphabetical password (lowercase).
            generate_alpha(length, password);
            break;
        case 'm':
            // If type is 'm', generate a mixed password (letters and digits).
            generate_mixed(length, password);
            break;
        case 's':
            // If type is 's', generate a secure password (letters, digits, and symbols).
            generate_secure(length, password);
            break;
        default:
            // If an invalid type is given, print an error message and set password to empty.
            printf("Invalid password type!\n");
            password[0] = '\0'; // Clear the password array
            break;
    }
}

// Initializes the random number generator using the current time
// The srand function seeds the random number generator, ensuring different sequences of random numbers each time the program runs.
void initialize_random() {
    srand(time(NULL)); // Initialize the random number generator using the current time as the seed
}

// Generates a numeric password consisting of digits (0-9)
void generate_numeric(int length, char* password) {
    const char digits[] = "0123456789"; // Available characters (digits)
    int num_characters = sizeof(digits) - 1; // Total number of characters in the digits array (10 characters)

    // Generate 'length' number of random digits and store them in 'password'
    for (int i = 0; i < length; i++) {
        password[i] = digits[rand() % num_characters]; // Choose a random digit from the array
    }
    password[length] = '\0'; // Null-terminate the password string
}

// Generates an alphabetical password consisting of lowercase letters (a-z)
void generate_alpha(int length, char* password) {
    const char letters[] = "abcdefghijklmnopqrstuvwxyz"; // Available characters (lowercase letters)
    int num_characters = sizeof(letters) - 1; // Total number of characters in the letters array (26 characters)

    // Generate 'length' number of random letters and store them in 'password'
    for (int i = 0; i < length; i++) {
        password[i] = letters[rand() % num_characters]; // Choose a random letter from the array
    }
    password[length] = '\0'; // Null-terminate the password string
}

// Generates a mixed password consisting of both lowercase letters (a-z) and digits (0-9)
void generate_mixed(int length, char* password) {
    const char mixed[] = "abcdefghijklmnopqrstuvwxyz0123456789"; // Available characters (letters and digits)
    int num_characters = sizeof(mixed) - 1; // Total number of characters in the mixed array (36 characters)

    // Generate 'length' number of random characters (letters or digits) and store them in 'password'
    for (int i = 0; i < length; i++) {
        password[i] = mixed[rand() % num_characters]; // Choose a random character from the mixed array
    }
    password[length] = '\0'; // Null-terminate the password string
}

// Generates a secure password consisting of uppercase letters, lowercase letters, digits, and symbols
void generate_secure(int length, char* password) {
    const char secure[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789!@#$%^&*()"; // Available characters (letters, digits, and symbols)
    int num_characters = sizeof(secure) - 1; // Total number of characters in the secure array (72 characters)

    // Generate 'length' number of random characters (letters, digits, or symbols) and store them in 'password'
    for (int i = 0; i < length; i++) {
        password[i] = secure[rand() % num_characters]; // Choose a random character from the secure array
    }
    password[length] = '\0'; // Null-terminate the password string
}
