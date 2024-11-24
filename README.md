# TCP Password Generator

## Overview
This repository contains the implementation of a **university exam project**, which consists of two interrelated components: a **client** project and a **server** project. Together, they form a TCP-based application for generating random passwords. 

The client sends requests specifying the type and length of the desired password, while the server processes the request, generates the password, and sends it back to the client.

---

## Features

### Client
- Validates user input for password type and length.
- Sends requests to the server via TCP.
- Receives and displays the generated password.

### Server
- Handles requests from multiple clients (up to `QLEN + 1` simultaneous connections).
- Generates random passwords based on client specifications.
- Supports multiple password types: numeric, alphabetic, mixed, and secure.

---

## Password Types
The following password types can be requested:
- **Numeric (n):** Digits only (e.g., 123456).
- **Alphabetic (a):** Lowercase letters only (e.g., abcdef).
- **Mixed (m):** Lowercase letters and digits (e.g., abc123).
- **Secure (s):** Combination of uppercase, lowercase, digits, and special characters (e.g., Abc@123).

### Constraints
- Password length must be between **6** and **32** characters.

---

## Project Structure
This project is divided into two main components, which work together to fulfill the assignment requirements:

### Client Project
```plaintext
client/
├── main_client.c     # Client-side logic
├── protocol.h        # Shared protocol definitions
├── function.c        # Client utility functions (e.g., input validation)
└── function.h        # Header for client utilities
```
### Server Project
```plaintext
server/
├── main_server.c     # Server-side logic
├── protocol.h        # Shared protocol definitions
├── psw_function.c    # Password generation logic
└── psw_function.h    # Header for password generation
```

### Authors:
- Bruno Giuseppe
- Giordano Angelo
