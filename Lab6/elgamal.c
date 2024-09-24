#include <stdio.h>

// Function to perform efficient exponentiation (a^b mod c)
int eff_exp(int a, int b, int c) {
    int res = 1;
    while (b > 0) {
        if (b % 2 == 1) {
            res = (res * a) % c;
        }
        a = (a * a) % c;
        b = b / 2;
    }
    return res;
}

// Function to perform Euclidean algorithm to find modular multiplicative inverse
int euclid(int n, int b, int t1, int t2) {
    if (b == 1 && n % b == 0) {
        return t2;
    } else if (n % b == 0) {
        return 0;
    } else {
        int q = n / b;
        int x = b;
        int y = n % b;
        int temp = t2;
        t2 = t1 - (q * t2);
        return euclid(x, y, temp, t2);
    }
}

// Function to calculate ciphertext component 1 (c1)
int c1(int a, int k, int p) {
    return eff_exp(a, k, p);
}

// Function to calculate ciphertext component 2 (c2)
int c2(int b, int k, int m, int p) {
    int c3 = eff_exp(b, k, p);
    return (c3 * m) % p;
}

// Function to perform decryption
int dec(int c1, int c2, int d, int p) {
    d = p - 1 - d; // Compute the private key for decryption
    int temp = eff_exp(c1, d, p);
    return (temp * c2) % p;
}

int main() {
    // Key generation
    int p = 107; // Prime number
    int a = 2;   // Primitive root
    int d = 67;  // Private key
    int d_pub = eff_exp(a, d, p); // Compute the public key
    printf("Public key: %d\n", d_pub);

    // Encryption
    int k = 45; // Random key

    int m; // Plaintext message
    printf("Enter message: ");
    scanf("%d",&m);

    // Encryption
    int c_1 = c1(a, k, p); // Compute c1
    int c_2 = c2(d_pub, k, m, p); // Compute c2
    printf("Ciphertext components:\n");
    printf("c1: %d\n", c_1);
    printf("c2: %d\n", c_2);

    // Decryption
    int e = dec(c_1, c_2, d, p); // Decrypt ciphertext
    printf("Decrypted message (e): %d\n", e);
    
    return 0;
}
