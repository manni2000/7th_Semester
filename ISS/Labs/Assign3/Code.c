#include <stdio.h>
#include <string.h>

// Define the S-box and permutation function
unsigned char S_box[16] = {0xE, 0x4, 0xD, 0x1, 0x2, 0xF, 0xB, 0x8, 0x3, 0xA, 0x6, 0xC, 0x5, 0x9, 0x0, 0x7};
unsigned char P_box[8] = {0x1, 0x4, 0x5, 0x7, 0x3, 0x6, 0x2, 0x8};

// Define the round-key mixing function
void round_key_mixing(unsigned char *block, unsigned char *key) {
    for (int i = 0; i < 8; i++) {
        block[i] ^= key[i];
    }
}

// Define the substitution function
void substitution(unsigned char *block) {
    for (int i = 0; i < 8; i++) {
        block[i] = S_box[block[i]];
    }
}

// Define the inverse substitution function
void inverse_substitution(unsigned char *block) {
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 16; j++) {
            if (block[i] == S_box[j]) {
                block[i] = j;
                break;
            }
        }
    }
}

// Define the permutation function
void permutation(unsigned char *block) {
    unsigned char temp[8];
    for (int i = 0; i < 8; i++) {
        temp[i] = block[P_box[i] - 1];
    }
    memcpy(block, temp, 8);
}

// Define the inverse permutation function
void inverse_permutation(unsigned char *block) {
    unsigned char temp[8];
    for (int i = 0; i < 8; i++) {
        temp[P_box[i] - 1] = block[i];
    }
    memcpy(block, temp, 8);
}

// Define the key schedule function
void key_schedule(unsigned char *key, unsigned char round_keys[][8]) {
    for (int round = 0; round < 5; round++) {
        for (int i = 0; i < 8; i++) {
            round_keys[round][i] = key[round * 4 + i];
        }
    }
}

// Define the encryption function
void encrypt(unsigned char *plaintext, unsigned char round_keys[][8]) {
    unsigned char block[8];
    memcpy(block, plaintext, 8);

    for (int round = 0; round < 4; round++) {
        round_key_mixing(block, round_keys[round]);
        substitution(block);
        permutation(block);
    }
    round_key_mixing(block, round_keys[4]);

    memcpy(plaintext, block, 8);
}

// Define the decryption function
void decrypt(unsigned char *ciphertext, unsigned char round_keys[][8]) {
    unsigned char block[8];
    memcpy(block, ciphertext, 8);

    round_key_mixing(block, round_keys[4]);
    for (int round = 3; round >= 0; round--) {
        inverse_permutation(block);
        inverse_substitution(block);
        round_key_mixing(block, round_keys[round]);
    }

    memcpy(ciphertext, block, 8);
}

// Define the ECB mode function
void ecb_mode(unsigned char *plaintext, unsigned char *key, int length, int encrypt_flag) {
    unsigned char round_keys[5][8];
    key_schedule(key, round_keys);

    for (int i = 0; i < length; i += 8) {
        if (encrypt_flag) {
            encrypt(plaintext + i, round_keys);
        } else {
            decrypt(plaintext + i, round_keys);
        }
    }
}

// Define the CBC mode function
void cbc_mode(unsigned char *plaintext, unsigned char *key, unsigned char *iv, int length, int encrypt_flag) {
    unsigned char round_keys[5][8];
    key_schedule(key, round_keys);

    unsigned char previous[8];
    memcpy(previous, iv, 8);

    for (int i = 0; i < length; i += 8) {
        if (encrypt_flag) {
            for (int j = 0; j < 8; j++) {
                plaintext[i + j] ^= previous[j];
            }
            encrypt(plaintext + i, round_keys);
            memcpy(previous, plaintext + i, 8);
        } else {
            unsigned char temp[8];
            memcpy(temp, plaintext + i, 8);
            decrypt(plaintext + i, round_keys);
            for (int j = 0; j < 8; j++) {
                plaintext[i + j] ^= previous[j];
            }
            memcpy(previous, temp, 8);
        }
    }
}

// Define the OFB mode function
void ofb_mode(unsigned char *plaintext, unsigned char *key, unsigned char *iv, int length, int encrypt_flag) {
    unsigned char round_keys[5][8];
    key_schedule(key, round_keys);

    unsigned char previous[8];
    memcpy(previous, iv, 8);

    for (int i = 0; i < length; i += 8) {
        encrypt(previous, round_keys);
        for (int j = 0; j < 8; j++) {
            plaintext[i + j] ^= previous[j];
        }
    }
}

int main() {
    unsigned char plaintext[8] = {0x1, 0x2, 0x3, 0x4, 0x5, 0x6, 0x7, 0x8};
    unsigned char key[24] = {0x1, 0x2, 0x3, 0x4, 0x5, 0x6, 0x7, 0x8, 0x9, 0xA, 0xB, 0xC, 0xD, 0xE, 0xF, 0x0, 0x1, 0x2, 0x3, 0x4, 0x5, 0x6, 0x7, 0x8};
    unsigned char iv[8] = {0x1, 0x2, 0x3, 0x4, 0x5, 0x6, 0x7, 0x8};

    printf("Original plaintext: ");
    for (int i = 0; i < 8; i++) {
        printf("%x ", plaintext[i]);
    }
    printf("\n");

    ecb_mode(plaintext, key, 8, 1);
    printf("ECB mode encrypted: ");
    for (int i = 0; i < 8; i++) {
        printf("%x ", plaintext[i]);
    }
    printf("\n");

    ecb_mode(plaintext, key, 8, 0);
    printf("ECB mode decrypted: ");
    for (int i = 0; i < 8; i++) {
        printf("%x ", plaintext[i]);
    }
    printf("\n");

    cbc_mode(plaintext, key, iv, 8, 1);
    printf("CBC mode encrypted: ");
    for (int i = 0; i < 8; i++) {
        printf("%x ", plaintext[i]);
    }
    printf("\n");

    cbc_mode(plaintext, key, iv, 8, 0);
    printf("CBC mode decrypted: ");
    for (int i = 0; i < 8; i++) {
        printf("%x ", plaintext[i]);
    }
    printf("\n");

    ofb_mode(plaintext, key, iv, 8, 1);
    printf("OFB mode encrypted: ");
    for (int i = 0; i < 8; i++) {
        printf("%x ", plaintext[i]);
    }
    printf("\n");

    ofb_mode(plaintext, key, iv, 8, 0);
    printf("OFB mode decrypted: ");
    for (int i = 0; i < 8; i++) {
        printf("%x ", plaintext[i]);
    }
    printf("\n");

    return 0;
}


