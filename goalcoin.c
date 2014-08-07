#include "goalcoin.h"
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <stdio.h>

#include "sha3/sph_blake.h"
#include "sha3/sph_groestl.h"
#include "sha3/sph_jh.h"
#include "sha3/sph_keccak.h"
#include "sha3/sph_skein.h"
#include "sha3/sph_whirlpool.h"

void goalcoin_hash(const char* input, char* output)
{
    sph_blake512_context     ctx_blake;
    sph_groestl512_context   ctx_groestl;
    sph_skein512_context     ctx_skein;
    sph_jh512_context        ctx_jh;
    sph_keccak512_context    ctx_keccak;
    sph_whirlpool_context    ctx_whirlpool1;

    //these uint512 in the c++ source of the client are backed by an array of uint32
    uint32_t hashA[16], hashB[16];

    sph_blake512_init(&ctx_blake);
    sph_blake512 (&ctx_blake, input, 80);
    sph_blake512_close (&ctx_blake, hashA);

    sph_groestl512_init(&ctx_groestl);
    sph_groestl512 (&ctx_groestl, hashA, 64);
    sph_groestl512_close(&ctx_groestl, hashB);

    sph_skein512_init(&ctx_skein);
    sph_skein512 (&ctx_skein, hashB, 64);
    sph_skein512_close (&ctx_skein, hashA);

    sph_jh512_init(&ctx_jh);
    sph_jh512 (&ctx_jh, hashA, 64);
    sph_jh512_close(&ctx_jh, hashB);

    sph_keccak512_init(&ctx_keccak);
    sph_keccak512 (&ctx_keccak, hashB, 64);
    sph_keccak512_close(&ctx_keccak, hashA);

    sph_whirlpool_init (&ctx_whirlpool1);
    sph_whirlpool (&ctx_whirlpool1, hashA, 64);
    sph_whirlpool_close(&ctx_whirlpool1, hashB);

    memcpy(output, hashB, 32);
}

