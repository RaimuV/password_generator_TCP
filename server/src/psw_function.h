/*
 * AUTHORS: Angelo Giordano, (802019)Giuseppe Bruno (798106).
 */

#ifndef PSW_FUNCTION_H_INCLUDED  // Ensure this file is included only once
#define PSW_FUNCTION_H_INCLUDED

// Defines the minimum and maximum length for the generated passwords
#define MIN_PASSWORD_LENGTH 6    // Minimum length of the password
#define MAX_PASSWORD_LENGTH 32   // Maximum length of the password

// Function prototypes: These declare the functions that are defined elsewhere (e.g., in `psw_function.c`)

// Initializes the random number generator, typically used for generating random password characters
void initialize_random();

// Main function to generate a password based on the requested type and length.
// 'type' specifies the type of password ('n' for numeric, 'a' for alpha, etc.)
// 'length' specifies the desired length of the generated password
// 'password' is the output string where the generated password will be stored
void generate_password(char type, int length, char* password);

// Specific password generation functions for each password type:

// Generates a numeric password containing only digits (0-9)
void generate_numeric(int length, char* password);

// Generates an alphabetic password containing only lowercase letters (a-z)
void generate_alpha(int length, char* password);

// Generates a mixed password containing both lowercase letters (a-z) and digits (0-9)
void generate_mixed(int length, char* password);

// Generates a secure password containing uppercase letters (A-Z), lowercase letters (a-z), digits (0-9), and special characters
void generate_secure(int length, char* password);

#endif // PSW_FUNCTION_H_INCLUDED
