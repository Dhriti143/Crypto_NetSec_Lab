#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int gcd(int a, int b) {
    if (b == 0)
        return a;
    return gcd(b, a % b);
}

// Function to perform modular exponentiation (x^y mod n)
int mod_exp(int x, int y, int n) {
    int result = 1;
    x = x % n;
    while (y > 0) {
        if (y & 1)
            result = (result * x) % n;
        y = y >> 1;
        x = (x * x) % n;
    }
    return result;
}

int main() {
    int p, q, n;
    printf("Enter two prime numbers (p q): ");
    scanf("%d %d", &p, &q);
    n = p * q;
    int phi_n = (p - 1) * (q - 1);

    int e, d;
    // Selecting e such that gcd(e, phi_n) = 1
    for (e = 2; e < phi_n && gcd(e, phi_n) != 1; e++);

    // Calculate N = [log2(n) + 1]
    int N = (int)(log2(n)) + 1;

    // Selecting r and k such that r + k = N
    int r = N / 2;
    int k = N - r;

    // Selecting a random seed xo of bitlength r
    int xo = rand() % (int)pow(2, r);

    int m; // Length of the pseudorandom sequence
    printf("Enter the length of the pseudorandom sequence (m): ");
    scanf("%d", &m);

    printf("Generating pseudorandom sequence of length %d...\n", m);
    
    // Generating the pseudorandom sequence
    int *sequence = (int *)malloc(sizeof(int) * m);
    int xi = xo;
    for (int i = 0; i < m; i++) {
        int yi = mod_exp(xi, e, n); // Encryption using RSA

        // Extracting the output bits
        int vi = yi % n;
        int zi = yi >> (N - k);

        sequence[i] = (vi << k) | zi;

        // Updating xi for the next iteration
        xi = sequence[i];
    }

    // Output the generated sequence
    printf("Generated sequence:\n");
    for (int i = 0; i < m; i++) {
        printf("%d\n", sequence[i]);
    }

    free(sequence); // Freeing allocated memory

    return 0;
}
