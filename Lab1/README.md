# S-DES Implementation in C

## Introduction
This repository contains a simple implementation of the Simplified Data Encryption Standard (S-DES) in the C programming language. 
S-DES is a simplified version of the Data Encryption Standard (DES), designed for educational purposes.

## S-DES Overview
S-DES operates on 8-bit blocks of plaintext, using a 10-bit key to produce an 8-bit block of ciphertext. 
The key is expanded and permuted to create subkeys for each round. The S-DES algorithm consists of an initial permutation, a complex substitution-permutation network, and a final permutation.

## Usage

1. **Clone the Repository:**
   ```bash
   git clone https://github.com/Dhriti143/Crypto_NetSec_Lab.git
   cd Crypto_NetSec_Lab
   cd Lab1
   ```
2. **Compile the Code:**
   ```bash
   gcc sdes.c -o sdes
   ```
3. **Run the Program:**
   ```bash
   ./sdes
   ```
4. **Input Format:**
 - The program prompts for a single character for key as wll as plaintext.
 - Follow the on-screen instructions to enter the required inputs.
  
 
 Example:
 The program will display the 10 bit key, subkeys(key1 and key2) and the final encrypted as well as decrypted result.
 ```bash
    Enter key (1 letter only): a
    Enter plaintext (1 letter): a
    Key - 0 0 0 1 1 0 0 0 0 1 
    Key 1 - 0 0 0 1 0 0 1 0 
    Key 2 - 0 0 0 1 1 0 0 0 
    Ciphertext - z
    Decrypted text - a
```

## Directory Structure
 - sdes.c: Main source code file containing the S-DES implementation.
 - README.md: Documentation providing information on usage and implementation details.

## Contributions
Contributions are welcome! If you find issues or have enhancements, please open an issue or create a pull request.

## License
This project is licensed under the **MIT License**.

Feel free to customize this README file further based on your specific implementatio
