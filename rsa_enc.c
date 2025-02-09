#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

// Function to compute gcd of two numbers (Euclidean Algorithm)
unsigned long long gcd(unsigned long long a, unsigned long long b) {
    while (b != 0) {
        unsigned long long temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

// Function to compute the modular inverse of a under modulo m using Extended Euclidean Algorithm
unsigned long long mod_inverse(unsigned long long a, unsigned long long m) {
    unsigned long long m0 = m, t, q;
    unsigned long long x0 = 0, x1 = 1;

    if (m == 1)
        return 0;

    while (a > 1) {
        // q is quotient
        q = a / m;
        t = m;
        
        // m is remainder now, process same as Euclid's algorithm
        m = a % m;
        a = t;
        t = x0;
        
        // Update x0 and x1
        x0 = x1 - q * x0;
        x1 = t;
    }

    // Make x1 positive
    if (x1 < 0)
        x1 += m0;

    return x1;
}

// Function to compute (base^exp) % mod using Modular Exponentiation
unsigned long long mod_exp(unsigned long long base, unsigned long long exp, unsigned long long mod) {
    unsigned long long result = 1;
    base = base % mod;
    
    while (exp > 0) {
        if (exp % 2 == 1)
            result = (result * base) % mod;

        exp = exp >> 1;
        base = (base * base) % mod;
    }

    return result;
}

// RSA Key Generation
void rsa_key_gen(unsigned long long *n, unsigned long long *e, unsigned long long *d) {
    // Choose two distinct large prime numbers p and q
    unsigned long long p = 61;  // Example prime number (small for simplicity)
    unsigned long long q = 53;  // Example prime number (small for simplicity)

    *n = p * q;  // n = p * q
    unsigned long long phi_n = (p - 1) * (q - 1);  // Euler's totient function: phi(n) = (p - 1)(q - 1)

    // Choose public exponent e such that 1 < e < phi_n and gcd(e, phi_n) = 1
    *e = 17;  // Common choice for e is 17 or 65537 (both are coprime with phi_n)

    // Compute private exponent d such that (d * e) % phi_n = 1
    *d = mod_inverse(*e, phi_n);
}

// RSA Encryption
unsigned long long rsa_encrypt(unsigned long long m, unsigned long long e, unsigned long long n) {
    return mod_exp(m, e, n);  // Ciphertext c = m^e % n
}

// RSA Decryption
unsigned long long rsa_decrypt(unsigned long long c, unsigned long long d, unsigned long long n) {
    return mod_exp(c, d, n);  // Decrypted message m = c^d % n
}

int main() {
    unsigned long long n, e, d;

    // Generate RSA keys
    rsa_key_gen(&n, &e, &d);

    printf("Public Key (n, e): (%llu, %llu)\n", n, e);
    printf("Private Key (n, d): (%llu, %llu)\n", n, d);

    // Encrypt a message
    unsigned long long message = 65;  // Example message (must be smaller than n)
    printf("Original Message: %llu\n", message);

    unsigned long long encrypted = rsa_encrypt(message, e, n);
    printf("Encrypted Message: %llu\n", encrypted);

    // Decrypt the message
    unsigned long long decrypted = rsa_decrypt(encrypted, d, n);
    printf("Decrypted Message: %llu\n", decrypted);

    return 0;
}
