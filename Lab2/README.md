# Brute Force Attack on S-DES in C
This section of the Crypto_NetSec_Lab repository focuses on the implementation of a Brute Force Attack on the Simplified Data Encryption Standard (S-DES) in the C programming language. 
The attack aims to recover the key used in the encryption process by systematically trying all possible keys.

## Files
 - bruteforce_sdes.c :- 
The main C file containing the implementation of the brute force attack on S-DES.
Uses input plaintext and ciphertext pairs from the input.txt file.
Outputs the discovered key (if any) and the time taken for the brute force attack.
 - input.txt :-
Contains input plaintext and ciphertext pairs in the format: plaintext ciphertext (character pairs).

## How to Run
1. **Clone the Repository:**
  ```bash
  git clone https://github.com/Dhriti143/Crypto_NetSec_Lab.git
  cd Crypto_NetSec_Lab/Lab2
  ```
2. **Compile the Code:**
  ```bash
  gcc bruteforce_sdes.c -o bruteforce_sdes -lm
  ```
3. **Run the Brute Force Attack:**
  ```bash
  ./bruteforce_sdes
  ```
4. **Output**
The program will display the following information:
 - If a key is discovered during the brute force attack, it will be printed.
 - The time taken for the brute force attack will be displayed.

## Example Usage
input.txt file contains the following pair:
  ```bash
  a z
  L l
  K 7
  Z a
  B B
  ```

Running the brute force attack program may produce output like this:
  ```bash
  Key -> a
  Brute Force time taken: 0.006000 seconds
  ```

## Contribution
Contributions and improvements to the code are welcome! If you find any issues or have suggestions, please open an issue or create a pull request.

## License
This project is licensed under the **MIT License**.
