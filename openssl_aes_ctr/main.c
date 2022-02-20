#include <openssl/evp.h>
#include <openssl/err.h>

#include <assert.h>
#include <stdio.h>
#include <stdbool.h>

// hexdump prints @data as hex up to @len bytes.
// Prints a newline after every @cols bytes.
static void hexdump (const unsigned char* data, int len, int cols) {
    if (cols == 0) {
        cols = 16;
    }
    for (int i = 0; i < len; i++) {
        printf ("%02x", data[i]);
        if ((i+1) % cols == 0) {
            printf ("\n");
        }
    }
    printf ("\n");
}

static void print_openssl_error (const char* prefix) {
    char buf[120];
    unsigned long errcode = ERR_get_error ();
    if (errcode == 0) {
        printf ("%s: No error code.\n", prefix);
        return;
    }
    printf ("%s: %s\n", prefix, ERR_error_string (errcode, buf));
}

static bool aes256_ctr_encrypt (const unsigned char* key, const unsigned char* iv, const unsigned char* plaintext, int plaintext_len, unsigned char *output, int* output_len) {
    EVP_CIPHER_CTX* ctx = EVP_CIPHER_CTX_new ();

    if (!EVP_EncryptInit_ex (ctx, EVP_aes_256_ctr(), NULL /* engine */, key, iv)) {
        print_openssl_error ("Error in EVP_EncryptInit_ex");
        return false;
    }

    *output_len = 0;

    int outl;
    if (!EVP_EncryptUpdate (ctx, output, &outl, plaintext, plaintext_len)) {
        print_openssl_error ("Error in EVP_EncryptUpdate");
        return false;
    }
    *output_len += outl;

    if (!EVP_EncryptFinal_ex (ctx, output, &outl)) {
        print_openssl_error ("Error in EVP_EncryptFinal_ex");
        return false;
    }
    *output_len += outl;

    EVP_CIPHER_CTX_free (ctx);
    return true;
}

int main () {
    const unsigned char key[] = "\x60\x3d\xeb\x10\x15\xca\x71\xbe\x2b\x73\xae\xf0\x85\x7d\x77\x81\x1f\x35\x2c\x07\x3b\x61\x08\xd7\x2d\x98\x10\xa3\x09\x14\xdf\xf4"; // 32 bytes.
    const unsigned char iv[] = "\xf0\xf1\xf2\xf3\xf4\xf5\xf6\xf7\xf8\xf9\xfa\xfb\xfc\xfd\xfe\xff"; // 16 bytes.
    // plaintext from SP 800-38A F.5.5:
    const unsigned char plaintext[] = "\x6b\xc1\xbe\xe2\x2e\x40\x9f\x96\xe9\x3d\x7e\x11\x73\x93\x17\x2a\xae\x2d\x8a\x57\x1e\x03\xac\x9c\x9e\xb7\x6f\xac\x45\xaf\x8e\x51\x30\xc8\x1c\x46\xa3\x5c\xe4\x11\xe5\xfb\xc1\x19\x1a\x0a\x52\xef\xf6\x9f\x24\x45\xdf\x4f\x9b\x17\xad\x2b\x41\x7b\xe6\x6c\x37\x10";
    unsigned char output[1024];
    int output_len;

    assert (sizeof(key) == 32 + 1 /* + 1 is for trailing NULL */);
    assert (sizeof(iv) == 16 + 1 /* + 1 is for trailing NULL */);
    assert (sizeof(plaintext) == 64 + 1 /* + 1 is for trailing NULL */);

    if (!aes256_ctr_encrypt (key, iv, plaintext, 64, output, &output_len)) {
        printf ("Error in aes256_ctr_encrypt\n");
        return EXIT_FAILURE;
    }

    hexdump (output, output_len, 0);

    /* Q: Is padding applied?
     * A: This test suggests not. The output only has one byte. */
    if (!aes256_ctr_encrypt (key, iv, plaintext, 1, output, &output_len)) {
        printf ("Error in aes256_ctr_encrypt\n");
        return EXIT_FAILURE;
    }

    hexdump (output, output_len, 0);
    assert (output_len == 1);
    return EXIT_SUCCESS;
}
