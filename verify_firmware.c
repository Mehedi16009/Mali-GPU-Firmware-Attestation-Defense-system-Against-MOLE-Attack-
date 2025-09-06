
#include <stdio.h>
#include <stdlib.h>
#include <openssl/evp.h>
#include <openssl/pem.h>

int verify_ecdsa(const char *pubkey_path, const char *firmware_path, const char *sig_path) {
    FILE *fpub = fopen(pubkey_path, "r");
    if (!fpub) { perror("fopen pubkey"); return -1; }
    EVP_PKEY *pkey = PEM_read_PUBKEY(fpub, NULL, NULL, NULL);
    fclose(fpub);
    if (!pkey) { fprintf(stderr, "Failed to read public key\n"); return -2; }

    FILE *f = fopen(firmware_path, "rb");
    fseek(f, 0, SEEK_END); long flen = ftell(f); fseek(f, 0, SEEK_SET);
    unsigned char *data = malloc(flen); fread(data, 1, flen, f); fclose(f);

    FILE *fs = fopen(sig_path,"rb");
    fseek(fs, 0, SEEK_END); long slen = ftell(fs); fseek(fs, 0, SEEK_SET);
    unsigned char *sig = malloc(slen); fread(sig, 1, slen, fs); fclose(fs);

    EVP_MD_CTX *mdctx = EVP_MD_CTX_new();
    int ok = 0;
    if (EVP_DigestVerifyInit(mdctx, NULL, EVP_sha256(), NULL, pkey) == 1) {
        if (EVP_DigestVerify(mdctx, sig, slen, data, flen) == 1) {
            ok = 1;
            printf("Verification: OK\n");
        } else {
            printf("Verification: FAILED\n");
        }
    }
    EVP_MD_CTX_free(mdctx);
    EVP_PKEY_free(pkey);
    free(data); free(sig);
    return ok ? 0 : 1;
}

int main(int argc, char **argv) {
    if (argc != 4) {
        fprintf(stderr, "Usage: %s pub.pem firmware.bin firmware.sig\n", argv[0]);
        return 2;
    }
    return verify_ecdsa(argv[1], argv[2], argv[3]);
}
