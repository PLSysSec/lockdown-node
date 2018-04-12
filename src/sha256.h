#ifndef SRC_SHA256_H_
#define SRC_SHA256_H_

#include <openssl/evp.h>

namespace node {

#define SHA256_STR_LEN 64

static char* SHA256(char* input, int len) {
  EVP_MD_CTX *mdctx;
  unsigned char md_value[EVP_MAX_MD_SIZE];
  unsigned int md_len;

  char* out_hash = (char*)malloc(SHA256_STR_LEN + 1);

  mdctx = EVP_MD_CTX_create();
  EVP_DigestInit_ex(mdctx, EVP_sha256(), NULL);
  EVP_DigestUpdate(mdctx, input, len);
  EVP_DigestFinal_ex(mdctx, md_value, &md_len);

  for (unsigned i = 0; i < md_len; i++) {
    sprintf(out_hash + (i*2), "%02x", md_value[i]);
  }
  out_hash[SHA256_STR_LEN] = '\0';

  EVP_MD_CTX_destroy(mdctx);

  return out_hash;
}
}  // namespace node

#endif  // SRC_SHA256_H_
