#ifndef CHECKSUM_MD5
#define CHECKSUM_MD5

#include <Windows.h>
#include <cstdio>

#define MD5_DIGEST_LENGTH 16  // 16 bytes == 128 bit digest

// MD5 Hash
typedef struct{
	unsigned int	buf[ 4 ];
    unsigned int	bits[ 2 ];
    unsigned char	in[ 64 ];
}MD5Context_t;

extern void			MD5Init( MD5Context_t *context );
extern void			MD5Update( MD5Context_t *context, unsigned char const *buf, unsigned int len );
extern void			MD5Final( unsigned char digest[ MD5_DIGEST_LENGTH ], MD5Context_t *context );
extern char*		MD5_Print( unsigned char digest[ MD5_DIGEST_LENGTH ] );
extern void			MD5Transform(unsigned int buf[4], unsigned int const in[16]);
extern unsigned int	MD5_PseudoRandom(unsigned int nSeed);

#endif