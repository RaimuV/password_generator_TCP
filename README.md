# password_generator_TCP
A simple client-server password generator application written in C.

**Authors:** Angelo Giordano, Giuseppe Bruno (Matricole: 802019, 798106)

## Overview
This project implements a TCP-based client-server application for generating random passwords. The client requests a password by specifying its type and length, and the server responds with a randomly generated password. The application supports various password types, such as numeric, alphabetic, mixed, and secure passwords.

---

## Features
- **Client:** 
  - Input validation for password type and length.
  - Sends requests to the server for password generation.
  - Receives and displays the generated password.

- **Server:** 
  - Accepts multiple clients (supports up to `QLEN + 1` clients).
  - Generates random passwords based on the client's request.
  - Supports secure, numeric, alphabetic, and mixed password types.

---

## Password Types
The following types of passwords can be requested:
- **Numeric (n):** Digits only (e.g., 123456).
- **Alphabetic (a):** Lowercase letters only (e.g., abcdef).
- **Mixed (m):** Lowercase letters and digits (e.g., abc123).
- **Secure (s):** Combination of uppercase letters, lowercase letters, digits, and special characters (e.g., Abc@123).

### Constraints
- Password length must be between **6** and **32** characters.

---

## Project Structure
```plaintext
.
├── main_client.c     # Client-side logic
├── main_server.c     # Server-side logic
├── protocol.h        # Shared protocol definitions (e.g., structures, constants)
├── function.c        # Client utility functions (e.g., input validation)
├── function.h        # Header for client utilities
├── psw_function.c    # Server-side password generation logic
├── psw_function.h    # Header for server-side password generation
└── README.md         # Project documentation
```
