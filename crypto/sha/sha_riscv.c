/*
 * Copyright 2023 The OpenSSL Project Authors. All Rights Reserved.
 *
 * Licensed under the Apache License 2.0 (the "License").  You may not use
 * this file except in compliance with the License.  You can obtain a copy
 * in the file LICENSE in the source distribution or at
 * https://www.openssl.org/source/license.html
 */

#include <stdlib.h>
#include <string.h>

#include <openssl/opensslconf.h>
#include <openssl/sha.h>
#include "crypto/riscv_arch.h"

void sha256_block_data_order_zvbb_zvknha_or_zvknhb(void *ctx, const void *in, size_t num);
void sha256_block_data_order_c(void *ctx, const void *in, size_t num);
void sha256_block_data_order(SHA256_CTX *ctx, const void *in, size_t num);

void sha256_block_data_order(SHA256_CTX *ctx, const void *in, size_t num)
{
    if (RISCV_HAS_ZVBB() && (RISCV_HAS_ZVKNHA() || RISCV_HAS_ZVKNHB()) && riscv_vlen() >= 128) {
        sha256_block_data_order_zvbb_zvknha_or_zvknhb(ctx, in, num);
    } else {
        sha256_block_data_order_c(ctx, in, num);
    }
}

void sha512_block_data_order_zvbb_zvknhb(void *ctx, const void *in, size_t num);
void sha512_block_data_order_c(void *ctx, const void *in, size_t num);
void sha512_block_data_order(SHA512_CTX *ctx, const void *in, size_t num);

void sha512_block_data_order(SHA512_CTX *ctx, const void *in, size_t num)
{
    if (RISCV_HAS_ZVBB_AND_ZVKNHB() && riscv_vlen() >= 256) {
        sha512_block_data_order_zvbb_zvknhb(ctx, in, num);
    } else {
        sha512_block_data_order_c(ctx, in, num);
    }
}
