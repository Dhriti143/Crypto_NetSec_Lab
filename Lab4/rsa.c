// word message encryption and decrption 

#include <stdio.h>
#include <math.h>
#include <string.h>

// Function to find the greatest common divisor (GCD)
long gcd(long a, long b) {
    if (b == 0)
        return a;
    return gcd(b, a % b);
}

// Function to find extended GCD and modular inverse
long gcdExtended(long a, long b, long* x, long* y) {
    if (a == 0) {
        *x = 0;
        *y = 1;
        return b;
    }

    long x1, y1;
    long g = gcdExtended(b % a, a, &x1, &y1);
    *x = y1 - (b / a) * x1;
    *y = x1;

    return g;
}

// Function to calculate modular exponentiation (to handle large numbers)
long long power(long long x, unsigned long long y, long long p) {
    long long res = 1;
    x = x % p;

    while (y > 0) {
        if (y & 1)
            res = (res * x) % p;
        y = y >> 1;
        x = (x * x) % p;
    }
    return res;
}

// Function to find modular inverse
long modInverse(long a, long m) {
    long x, y;
    gcdExtended(a, m, &x, &y);
    return (x % m + m) % m;
}

// Function to encrypt a message
void encrypt(char message[], long e, long n, long encrypted[]) {
    int len = strlen(message);

    for (int i = 0; i < len; i++) {
        encrypted[i] = power(message[i], e, n);
        printf("%ld ", encrypted[i]);
    }
    printf("\n");
}

// Function to decrypt a message
void decrypt(long encrypted[], int len, long d, long n, long decrypted[]) {
    // printf("%d\n",len);
    for (int i = 0; i < len; i++) {
        // printf("%d\n",i);
        decrypted[i] = (char)(power(encrypted[i], d, n));
    }
    decrypted[len] = '\0';
    for (int i=0; i<len; i++){
        printf("%c",decrypted[i]);
    }
}

int main() {
    long p, q;
    printf("Enter two prime numbers (p q): ");
    scanf("%ld %ld", &p, &q);

    long n = p * q;
    long phi_n = (p - 1) * (q - 1);
    long e, d;

    // Finding e such that 1 < e < phi_n and gcd(e, phi_n) = 1
    for (e = 2; e < phi_n; e++) {
        if (gcd(e, phi_n) == 1) {
            break;
        }
    }

    // Calculating d
    d = modInverse(e, phi_n);

    printf("Public key (e, n): (%ld, %ld)\n", e, n);
    printf("Private key (d, n): (%ld, %ld)\n", d, n);

    char message[100];
    printf("Enter message to encrypt: ");
    scanf("%s", message);

    int len = strlen(message);
    long encrypted[len], decrypted[len+1];

    printf("Encrypted message: ");
    encrypt(message, e, n, encrypted);

    printf("Decrypted message: ");
    decrypt(encrypted, len, d, n, decrypted);

    return 0;
}
