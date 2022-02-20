NIST SP 800-38A includes test cases for AES-256 CTR mode in F.5.5 and F.5.6.

# Verify F.5.5 with OpenSSL

```
F.5.5 CTR-AES256.Encrypt
Key 603deb1015ca71be2b73aef0857d7781
    1f352c073b6108d72d9810a30914dff4
Init. Counter f0f1f2f3f4f5f6f7f8f9fafbfcfdfeff
Block #1
Input Block f0f1f2f3f4f5f6f7f8f9fafbfcfdfeff
Output Block 0bdf7df1591716335e9a8b15c860c502
Plaintext 6bc1bee22e409f96e93d7e117393172a
Ciphertext 601ec313775789a5b7a7f504bbf3d228
Block #2
Input Block f0f1f2f3f4f5f6f7f8f9fafbfcfdff00
Output Block 5a6e699d536119065433863c8f657b94
Plaintext ae2d8a571e03ac9c9eb76fac45af8e51
Ciphertext f443e3ca4d62b59aca84e990cacaf5c5
Block #3
Input Block f0f1f2f3f4f5f6f7f8f9fafbfcfdff01
Output Block 1bc12c9c01610d5d0d8bd6a3378eca62
Plaintext 30c81c46a35ce411e5fbc1191a0a52ef
Ciphertext 2b0930daa23de94ce87017ba2d84988d
Block #4
Input Block f0f1f2f3f4f5f6f7f8f9fafbfcfdff02
Output Block 2956e1c8693536b1bee99c73a31576b6
Plaintext f69f2445df4f9b17ad2b417be66c3710
Ciphertext dfc9c58db67aada613c2dd08457941a6
```

Concatenate all Plaintext blocks into a file, plaintext.hex.
```
$ cat plaintext.hex
6bc1bee22e409f96e93d7e117393172aae2d8a571e03ac9c9eb76fac45af8e5130c81c46a35ce411e5fbc1191a0a52eff69f2445df4f9b17ad2b417be66c3710
```
Convert to binary.
```
xxd -r plaintext.hex plaintext.bin
```

Encrypt with OpenSSL CLI.

```
openssl enc -aes-256-ctr \
    -K 603deb1015ca71be2b73aef0857d77811f352c073b6108d72d9810a30914dff4 \
    -iv f0f1f2f3f4f5f6f7f8f9fafbfcfdfeff \
    -v \
    -in plaintext.bin \
    -out ciphertext.bin
```

Print out the ciphertext. Verify it matches the Ciphertext blocks in the test.
```
xxd -g 0 ciphertext.bin
```
