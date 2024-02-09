# Extended Euclidean Algorithm in C
This section of the Crypto_NetSec_Lab repository contains the implementation of the Extended Euclidean Algorithm in the C programming language. 
The Extended Euclidean Algorithm is used to find inverse of a number.

## Files
 - extended_euclidean.c :-
The main C file containing the implementation of the Extended Euclidean Algorithm.
Prompts the user to enter two integers so that inverse is calculated.

## How to Run
1. **Clone the Repository:**
  ```bash
  git clone https://github.com/Dhriti143/Crypto_NetSec_Lab.git
  cd Crypto_NetSec_Lab/Lab3
  ```

2. **Compile the Code:**
  ```bash
  gcc extended_euclidean.c -o extended_euclidean -lm
  ```
3. **Run the Program:**
   ```bash
   ./extended_euclidean
   ```
4. Follow the prompts to enter two integers.
5. **Output**
The program will display the inverse of a number mod n if exists.

## Example Usage
  Assuming the user enters integers a = 5 and n = 7, the program may produce output like this:
  ```bash
  a: 5
  n: 27
  11 is inverse of 5 mod 27
  ```
## Contribution
Contributions and improvements to the code are welcome! If you find any issues or have suggestions, please open an issue or create a pull request.

## License
This project is licensed under the **MIT License**.
