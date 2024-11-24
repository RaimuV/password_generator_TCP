/*
 * AUTHORS: Angelo Giordano, (802019)Giuseppe Bruno (798106).
 */

#ifndef FUNCTION_H_INCLUDED
#define FUNCTION_H_INCLUDED

#define MIN_PASSWORD_LENGTH 6  // Minimum allowed password length
#define MAX_PASSWORD_LENGTH 32 // Maximum allowed password length

// Function prototypes
void show_menu();               // Function to show the menu to the user
int read_input(char* type, int* length);  // Function to read and validate user input
void print_password(const char* password);  // Function to print the generated password

#endif // FUNCTION_H_INCLUDED
