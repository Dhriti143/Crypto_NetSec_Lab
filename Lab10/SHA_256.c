#include <stdio.h>
#include <stdint.h>
#include <string.h>

// Define macros for circular right shift (ROTR), SHA-256 functions (SIG0, SIG1, CH, MAJ)
#define ROTR(x, n) (((x) >> (n)) | ((x) << (32 - (n))))
#define SIG0(x) (ROTR(x, 2) ^ ROTR(x, 13) ^ ROTR(x, 22))
#define SIG1(x) (ROTR(x, 6) ^ ROTR(x, 11) ^ ROTR(x, 25))
#define CH(x, y, z) (((x) & (y)) ^ (~(x) & (z)))
#define MAJ(x, y, z) (((x) & (y)) ^ ((x) & (z)) ^ ((y) & (z)))

// Constants used in SHA-256 algorithm
static const uint32_t K[] = {
    // 64 constant values derived from the fractional parts of the cube roots of the first 64 prime numbers
    // These constants are used in the message schedule during hashing
    // These values are part of the SHA-256 specification and remain constant
    // They contribute to the non-linearity of the transformation process, enhancing security
    // This is one of the core components of the SHA-256 algorithm
    0x428a2f98, 0x71374491, 0xb5c0fbcf, 0xe9b5dba5,
    0x3956c25b, 0x59f111f1, 0x923f82a4, 0xab1c5ed5,
    0xd807aa98, 0x12835b01, 0x243185be, 0x550c7dc3,
    0x72be5d74, 0x80deb1fe, 0x9bdc06a7, 0xc19bf174,
    0xe49b69c1, 0xefbe4786, 0x0fc19dc6, 0x240ca1cc,
    0x2de92c6f, 0x4a7484aa, 0x5cb0a9dc, 0x76f988da,
    0x983e5152, 0xa831c66d, 0xb00327c8, 0xbf597fc7,
    0xc6e00bf3, 0xd5a79147, 0x06ca6351, 0x14292967,
    0x27b70a85, 0x2e1b2138, 0x4d2c6dfc, 0x53380d13,
    0x650a7354, 0x766a0abb, 0x81c2c92e, 0x92722c85,
    0xa2bfe8a1, 0xa81a664b, 0xc24b8b70, 0xc76c51a3,
    0xd192e819, 0xd6990624, 0xf40e3585, 0x106aa070,
    0x19a4c116, 0x1e376c08, 0x2748774c, 0x34b0bcb5,
    0x391c0cb3, 0x4ed8aa4a, 0x5b9cca4f, 0x682e6ff3,
    0x748f82ee, 0x78a5636f, 0x84c87814, 0x8cc70208,
    0x90befffa, 0xa4506ceb, 0xbef9a3f7, 0xc67178f2
};

// Function to perform SHA-256 hashing
void sha256(const uint8_t *message, uint32_t len, uint32_t hash[8]) {
    uint32_t w[64]; // Message schedule
    uint32_t a, b, c, d, e, f, g, h; // Working variables
    uint32_t t1, t2; // Temporary variables

    uint32_t *m = (uint32_t *)message; // Cast message pointer to uint32_t for easier manipulation

    // Initialize hash values
    // These values are defined by the SHA-256 specification and serve as the initial hash values
    hash[0] = 0x6a09e667;
    hash[1] = 0xbb67ae85;
    hash[2] = 0x3c6ef372;
    hash[3] = 0xa54ff53a;
    hash[4] = 0x510e527f;
    hash[5] = 0x9b05688c;
    hash[6] = 0x1f83d9ab;
    hash[7] = 0x5be0cd19;

    // Iterate over each block of 512 bits (64 bytes) in the message
    for (int i = 0; i < len / 64; i++) {
        memcpy(w, m + i * 16, 64); // Copy the block into the message schedule array w

        // Prepare the message schedule
        for (int j = 16; j < 64; j++) {
            w[j] = SIG1(w[j - 2]) + w[j - 7] + SIG0(w[j - 15]) + w[j - 16]; // Calculate w[j]
        }

        // Initialize working variables with current hash values
        a = hash[0];
        b = hash[1];
        c = hash[2];
        d = hash[3];
        e = hash[4];
        f = hash[5];
        g = hash[6];
        h = hash[7];

        // Perform the main hashing computation
        for (int j = 0; j < 64; j++) {
            t1 = h + SIG1(e) + CH(e, f, g) + K[j] + w[j]; // Calculate temporary variables t1
            t2 = SIG0(a) + MAJ(a, b, c); // Calculate temporary variables t2
            h = g; // Update working variables
            g = f;
            f = e;
            e = d + t1;
            d = c;
            c = b;
            b = a;
            a = t1 + t2; // Update working variables
        }

        // Update hash values with the computed values
        hash[0] += a;
        hash[1] += b;
        hash[2] += c;
        hash[3] += d;
        hash[4] += e;
        hash[5] += f;
        hash[6] += g;
        hash[7] += h;
    }
}

// Main function to demonstrate SHA-256 hashing
int main() {
    uint32_t hash[8]; // Array to store the final hash value
    const char *message = "Dhriti Shah"; // Message to hash
    sha256((uint8_t *)message, strlen(message), hash); // Call the sha256 function to compute the hash
    printf("SHA-256 hash of '%s':\n", message); // Print the message
    for (int i = 0; i < 8; i++) {
        printf("%08x", hash[i]); // Print each 32-bit word of the hash
    }
    printf("\n");
    return 0;
}
