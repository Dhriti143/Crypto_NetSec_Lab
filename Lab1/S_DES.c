#include <stdio.h>
#include <math.h>

// Function to perform circular shift on an array
void circularShift(int arr[], int size) {
    int temp = arr[0];
    for (int i = 0; i < size - 1; i++) {
        arr[i] = arr[i + 1];
    }
    arr[size - 1] = temp;
}

// Function to generate round keys
void keyGeneration(int key[], int key1[], int key2[]) {
    // Permutation on the original key to get a new key
    int newkey[10] = {key[2], key[4], key[1], key[6], key[3], key[9], key[0], key[8], key[7], key[5]};
    int left[5], right[5];

    for (int i = 0; i < 5; i++) {
        left[i] = newkey[i];
    }
    for (int i = 0; i < 5; i++) {
        right[i] = newkey[i + 5];
    }

    // Circular shift on the left and right parts
    circularShift(left, 5);
    circularShift(right, 5);

    // Combine the shifted left and right parts to form the first round key
    for (int i = 0; i < 10; i++) {
        if (i < 5) {
            newkey[i] = left[i];
        } else {
            newkey[i] = right[i - 5];
        }
    }

    key1[0] = newkey[5]; key1[1] = newkey[2]; key1[2] = newkey[6]; key1[3] = newkey[3];
    key1[4] = newkey[7]; key1[5] = newkey[4]; key1[6] = newkey[9]; key1[7] = newkey[8];

    // Perform double circular shift on left and right parts
    circularShift(left, 5); circularShift(left, 5);
    circularShift(right, 5); circularShift(right, 5);

    // Combine the shifted left and right parts to form the second round key
    for (int i = 0; i < 10; i++) {
        if (i < 5) {
            newkey[i] = left[i];
        } else {
            newkey[i] = right[i - 5];
        }
    }

    key2[0] = newkey[5]; key2[1] = newkey[2]; key2[2] = newkey[6];
    key2[3] = newkey[3]; key2[4] = newkey[7]; key2[5] = newkey[4];
    key2[6] = newkey[9]; key2[7] = newkey[8];
}

// Function to convert decimal to binary
void decimalToBinary(int decimal, int binary[]) {
    int i;
    for(i = 0; decimal > 0; i++) {
        binary[i] = decimal % 2;
        decimal = decimal / 2;
    }
}

// Function to perform substitution using S-box
void substitution(int arr[], int sbox[][4], int result[]) {
    int row = (arr[0] << 1) + arr[3];
    int col = (arr[1] << 1) + arr[2];
    int value = sbox[row][col];

    result[1] = value % 2;
    value /= 2;
    result[0] = value % 2;
}

// Function to perform the Fiestel function
void function1(int arr[], int key[]) {
    int l[4], r[4];
    for (int i = 0; i < 4; i++) {
        l[i] = arr[i];
        r[i] = arr[i + 4];
    }

    int ep[] = {4, 1, 2, 3, 2, 3, 4, 1};
    for (int i = 0; i < 8; i++) {
        ep[i] = r[(ep[i] - 1)];
    }

    for (int i = 0; i < 8; i++) {
        ep[i] = key[i] ^ ep[i];
    }

    int xorL[4], xorR[4];
    for (int i = 0; i < 4; i++) {
        xorL[i] = ep[i];
        xorR[i] = ep[i + 4];
    }

    int sbox0[4][4] = {{1, 0, 3, 2},
                       {3, 2, 1, 0},
                       {0, 2, 1, 3},
                       {3, 1, 3, 2}};

    int sbox1[4][4] = {{0, 1, 2, 3},
                       {2, 0, 1, 3},
                       {3, 0, 1, 0},
                       {2, 1, 0, 3}};

    int result1[2], result2[2];

    substitution(xorL, sbox0, result1);
    substitution(xorR, sbox1, result2);

    int permutation[4];
    permutation[0] = result1[1];
    permutation[1] = result2[1];
    permutation[2] = result2[0];
    permutation[3] = result1[0];

    for (int i = 0; i < 4; i++) {
        arr[i] = l[i] ^ permutation[i];
    }

    for (int i = 0; i < 4; i++) {
        arr[i + 4] = r[i];
    }
}

// Function to perform encryption
void encryption(int key1[], int key2[], int plaintext[], int ciphertext[]) {
    int ip[8] = {plaintext[1], plaintext[5], plaintext[2], plaintext[0], plaintext[3], plaintext[7], plaintext[4], plaintext[6]};

    function1(ip, key1);

    int l[4], r[4];
    for (int i = 0; i < 4; i++) {
        l[i] = ip[i];
        r[i] = ip[i + 4];
    }
    for (int i = 0; i < 4; i++) {
        ip[i] = r[i];
        ip[i + 4] = l[i];
    }

    function1(ip, key2);

    int ip_inv[] = { 3, 0, 2, 4, 6, 1, 7, 5};
    for (int i = 0; i < 8; i++) {
        ciphertext[i] = ip[(ip_inv[i])];
    }
}

// Function to perform decryption
void decryption(int key1[], int key2[], int ciphertext[], int decipher[]) {
    int ip[8] = {ciphertext[1], ciphertext[5], ciphertext[2], ciphertext[0], ciphertext[3], ciphertext[7], ciphertext[4], ciphertext[6]};
    
    function1(ip, key2);
    int l[4], r[4];
    for (int i = 0; i < 4; i++) {
        l[i] = ip[i];
        r[i] = ip[i + 4];
    }
    for (int i = 0; i < 4; i++) {
        ip[i] = r[i];
        ip[i + 4] = l[i];
    }
    
    function1(ip, key1);

    int ip_inv[] = { 4, 1, 3, 5, 7, 2, 8, 6};
    for (int i = 0; i < 8; i++) {
        decipher[i] = ip[(ip_inv[i] - 1)];
    }
}

// Function to convert binary to decimal
int binaryToDecimal(int binary[], int size) {
    int decimal = 0;
    
    for (int i = 0; i < size; i++) {
        decimal += binary[i] * pow(2, size - 1 - i);
    }
    
    return decimal;
}

// Main function
int main() {
    int binary[7], key[10] = {0}, key1[8] = {0}, key2[8];
    char a;

    // Getting a key from the user
    printf("Enter key (1 letter only): ");
    scanf("%c", &a);

    // Converting the key to binary
    decimalToBinary((int)a, binary);

    // Setting the key with proper arrangement
    for (int i = 0; i < 7; i++) {
        key[i + 3] = binary[(6 - i)];
    }
    

    // Generating round keys using the provided key
    keyGeneration(key, key1, key2);

    // Getting a plaintext from the user
    int plaintext[8] = {0};
    char text;
    printf("Enter plaintext (1 letter): ");
    scanf(" %c", &text);

    // Converting the plaintext to binary
    decimalToBinary((int)text, binary);

    // Setting the plaintext with proper arrangement
    for (int i = 0; i < 7; i++) {
        plaintext[i + 1] = binary[(6 - i)];
    }

    // Encrypting the plaintext
    int ciphertext[8] = {0};
    encryption(key1, key2, plaintext, ciphertext);

    printf("Key - ");
    for (int i = 0; i < 10; i++) {
        printf("%d ", key[i]);
    }
        printf("\n");
    printf("Key 1 - ");
    for (int i = 0; i < 8; i++) {
        printf("%d ", key1[i]);
    }
    printf("\n");
    printf("Key 2 - ");
    for (int i = 0; i < 8; i++) {
        printf("%d ", key2[i]);
    }

    // Converting the ciphertext to decimal and printing the result
    int cipher = binaryToDecimal(ciphertext, 8);
    printf("\nCiphertext - %c\n", (char)cipher);

    // Decrypting the ciphertext
    int decipher[8] = {0};
    decryption(key1, key2, ciphertext, decipher);

    // Converting the decrypted text to decimal and printing the result
    int decrypt = binaryToDecimal(decipher, 8);
    printf("Decrypted text - %c\n", (char)decrypt);

    return 0;
}
