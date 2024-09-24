#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

// Structure to hold a point (x, y)
typedef struct {
    int x;
    int y;
} Point;

// Function to generate random coefficients for polynomial
int* generateCoefficients(int secret, int k, int prime) {
    srand(time(NULL));
    int* coefficients = (int*)malloc(k * sizeof(int));
    coefficients[0] = secret;
    for (int i = 1; i < k; i++) {
        coefficients[i] = rand() % prime;
    }
    return coefficients;
}

// Function to evaluate polynomial at given x
int evaluatePolynomial(int* coefficients, int k, int x, int prime) {
    int result = 0;
    for (int i = 0; i < k; i++) {
        result += coefficients[i] * pow(x, i);
        result %= prime;
    }
    return result;
}

// Function to calculate modular inverse
int modInverse(int a, int m) {
    a = a % m;
    for (int x = 1; x < m; x++) {
        if ((a * x) % m == 1) return x;
    }
    return -1; // If modular inverse doesn't exist
}

// Function to perform Shamir Secret Sharing
Point* shamirSecretSharing(int secret, int k, int n, int prime) {
    Point* shares = (Point*)malloc(n * sizeof(Point));
    int* coefficients = generateCoefficients(secret, k - 1, prime);
    
    for (int i = 1; i <= n; i++) {
        shares[i - 1].x = i;
        shares[i - 1].y = evaluatePolynomial(coefficients, k, i, prime);
    }
    
    free(coefficients);
    return shares;
}

// Function to recover secret using Lagrange interpolation
int recoverSecret(Point* shares, int k, int prime) {
    int secret = 0;
    for (int i = 0; i < k; i++) {
        int num = 1, den = 1;
        for (int j = 0; j < k; j++) {
            if (i != j) {
                num *= -shares[j].x;
                num %= prime;
                den *= (shares[i].x - shares[j].x);
                den %= prime;
            }
        }
        int inv = modInverse(den, prime);
        int term = (shares[i].y * num * inv) % prime;
        secret = (prime + secret + term) % prime;
    }
    return secret;
}

int main() {
    int secret, k, n, prime;
    
    printf("Enter the secret: ");
    scanf("%d", &secret);
    
    printf("Enter the minimum number of shares required to reconstruct the secret (k): ");
    scanf("%d", &k);
    
    printf("Enter the total number of shares to generate (n): ");
    scanf("%d", &n);
    
    printf("Enter a prime number (to use as modulus): ");
    scanf("%d", &prime);
    
    // Perform Shamir Secret Sharing
    Point* shares = shamirSecretSharing(secret, k, n, prime);
    
    // Output shares
    printf("\nShares:\n");
    for (int i = 0; i < n; i++) {
        printf("Share %d: (%d, %d)\n", i + 1, shares[i].x, shares[i].y);
    }
    
    // Recover secret from subset of shares
    int recoveredSecret = recoverSecret(shares, k, prime);
    
    // Output results
    printf("\nOriginal Secret: %d\n", secret);
    printf("Recovered Secret: %d\n", recoveredSecret);
    
    // Free allocated memory
    free(shares);
    
    return 0;
}
