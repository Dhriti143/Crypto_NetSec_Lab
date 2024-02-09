//brute force attack success

#include <stdio.h>
#include <time.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>

void decimalToBinary(int decimal, int binary[]) {
    int i;
    for(i = 0; decimal > 0; i++) {
        binary[i] = decimal % 2;
        decimal = decimal / 2;
    }
}

void circularShift(int arr[], int size) {
    int temp = arr[0];
    for (int i = 0; i < size - 1; i++) {
        arr[i] = arr[i + 1];
    }
    arr[size - 1] = temp;
}

int getKeySize(int k){
    int binaryKeySize;
    for(int i = 0; k > 0; i++) {
        binaryKeySize++;
        k = k / 2;
    }
    if (binaryKeySize>7){
        return binaryKeySize;
    }
    else{
        return 7;
    }
}

void keyGeneration(int k, int key1[], int key2[]) {
    
    int keySize = getKeySize(k);
    int key[10] = {0};
    int *binary = (int *)malloc(keySize * sizeof(int));
    memset(binary, 0, keySize * sizeof(int));
    
    decimalToBinary(k, binary);
    // Setting the key with proper arrangement
    for (int i = 0; i < keySize; i++) {
        key[10 - keySize + i] = binary[keySize - 1 - i];
    }

    int newkey[10] = {key[2], key[4], key[1], key[6], key[3], key[9], key[0], key[8], key[7], key[5]};
    int left[5], right[5];

    for (int i = 0; i < 5; i++) {
        left[i] = newkey[i];
    }
    for (int i = 0; i < 5; i++) {
        right[i] = newkey[i + 5];
    }

    circularShift(left, 5);
    circularShift(right, 5);

    for (int i = 0; i < 10; i++) {
        if (i < 5) {
            newkey[i] = left[i];
        } else {
            newkey[i] = right[i - 5];
        }
    }

    key1[0] = newkey[5]; key1[1] = newkey[2]; key1[2] = newkey[6]; key1[3] = newkey[3];
    key1[4] = newkey[7]; key1[5] = newkey[4]; key1[6] = newkey[9]; key1[7] = newkey[8];

    circularShift(left, 5); circularShift(left, 5);
    circularShift(right, 5); circularShift(right, 5);

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

void substitution(int arr[], int sbox[][4], int result[]) {
    int row = (arr[0] << 1) + arr[3];
    int col = (arr[1] << 1) + arr[2];
    int value = sbox[row][col];

    result[1] = value % 2;
    value /= 2;
    result[0] = value % 2;
}

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

void encryption(int k, int plaintext[], int ciphertext[]) {
    int key1[8] = {0}, key2[8];
    keyGeneration(k, key1, key2);
    
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

int binaryToDecimal(int binary[], int size) {
    int decimal = 0;
    
    for (int i = 0; i < size; i++) {
        decimal += binary[i] * pow(2, size - 1 - i);
    }
    
    return decimal;
}

int main() {
    int binary[7], num = 0, asciiValue;
    char givenText, givenCipher;
    FILE *keyFile, *temp, *input;
    clock_t t1, t2;
    t1 = clock();

    // add all keys in file
    keyFile = fopen("keys.txt", "w");
    for (int k = 0; k < (1 << 10); ++k) {
        num++;
        fprintf(keyFile, "%d\n", k);
    }
    fclose(keyFile);

    //All the plaintext and ciphertext pairs for chosen key is saved in 'input.txt' file
    input = fopen("input.txt","r");
    if (input == NULL) {
        printf("Error opening the file.\n");
        return 1;  // Exit with an error code
    }

    //main brute force
    while(num>1){
        // Take Input from text file
        //space after %c handles all the whitespace and newline characters
        fscanf(input, "%c %c ", &givenText, &givenCipher);
        //plaintext to binary
        int plaintext[8] = {0}, k;
        asciiValue = givenText;
        decimalToBinary(asciiValue, binary);
        for (int i = 0; i < 7; i++) {
            plaintext[i + 1] = binary[6 - i];
        }

        // read keys from file and perform task
        keyFile = fopen("keys.txt","r");
        temp = fopen("temp.txt","w");
        while(fscanf(keyFile, "%d", &k) == 1) {
            int ciphertext[8] = {0};
            encryption(k, plaintext, ciphertext);
            int cipher = binaryToDecimal(ciphertext, 8);
            char ctext = (char)cipher;
            if (ctext == givenCipher) {
                fprintf(temp, "%d\n", k);
            } else {
                num--;
            }
        }
        fclose(keyFile);
        fclose(temp);

        //update keys 
        keyFile = fopen("temp.txt","r");
        temp = fopen("keys.txt","w");
        while(fscanf(keyFile, "%d", &k) == 1) {
            fprintf(temp, "%d\n", k);
        }
        fclose(keyFile);
        fclose(temp);
    } 
    fclose(input); 
    t2 = clock();
    int finalKey;
    keyFile = fopen("keys.txt","r");
    while(fscanf(keyFile, "%d", &finalKey) == 1) {
        printf("Key -> %c", finalKey);
    }

    double time_taken = ((double)(t2 - t1)) / CLOCKS_PER_SEC;
    printf("\nBrute Force time taken: %f seconds\n", time_taken);  
    return 0;
}