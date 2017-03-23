/* $Id: ecrypt-nls.c 388 2005-04-28 21:04:09Z mwp $ */
/* Ecrypt API wrapper for NLS */

/*
THIS SOFTWARE IS PROVIDED ``AS IS'' AND ANY EXPRESS OR IMPLIED
WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE AND AGAINST
INFRINGEMENT ARE DISCLAIMED.  IN NO EVENT SHALL THE AUTHOR OR
CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

#include "ecrypt-sync-ae.h"

#if (ECRYPT_VARIANT == 1)
#include "nlsref.c"
#else
#include "nlsfast.c"
#endif

void
ECRYPT_init(void)
{
}

void
ECRYPT_keysetup(ECRYPT_ctx* ctx, const u8* key, u32 keysize, u32 ivsize)
{
	nls_key(&ctx->ctx, (UCHAR *)key, (keysize + 7) / 8);
	ctx->ivsize = (ivsize + 7) / 8;
}

void
ECRYPT_ivsetup(ECRYPT_ctx* ctx, const u8* iv)
{
	nls_nonce(&ctx->ctx, (UCHAR *)iv, ctx->ivsize);
}

void
ECRYPT_encrypt_bytes(ECRYPT_ctx* ctx,
	const u8* plaintext, u8* ciphertext, u32 msglen)
{
	memmove(ciphertext, plaintext, msglen);
	nls_stream(&ctx->ctx, (UCHAR *)ciphertext, msglen);
}

void
ECRYPT_decrypt_bytes(ECRYPT_ctx* ctx,
	const u8* ciphertext, u8* plaintext, u32 msglen)
{
	memmove(plaintext, ciphertext, msglen);
	nls_stream(&ctx->ctx, (UCHAR *)plaintext, msglen);
}

void
ECRYPT_keystream_bytes(ECRYPT_ctx* ctx, u8* keystream, u32 length)
{
	memset (keystream, 0, length);
	nls_stream(&ctx->ctx, (UCHAR *)keystream, length);
}       

void
ECRYPT_AE_keysetup(ECRYPT_AE_ctx* ctx, const u8* key, u32 keysize,
	u32 ivsize, u32 macsize)
{
	nls_key(&ctx->ctx.ctx, (UCHAR *)key, (keysize + 7) / 8);
	ctx->ctx.ivsize = (ivsize + 7) / 8;
	ctx->macctx.macsize = (macsize + 7) / 8;
}

void
ECRYPT_AE_ivsetup(ECRYPT_AE_ctx* ctx, const u8* iv)
{
	nls_nonce(&ctx->ctx.ctx, (UCHAR *)iv, ctx->ctx.ivsize);
}

void
ECRYPT_AE_encrypt_bytes(ECRYPT_AE_ctx* ctx,
	const u8* plaintext, u8* ciphertext, u32 msglen)
{
	memmove(ciphertext, plaintext, msglen);
	nls_encrypt(&ctx->ctx.ctx, (UCHAR *)ciphertext, msglen);
}

void
ECRYPT_AE_decrypt_bytes(ECRYPT_AE_ctx* ctx,
	const u8* ciphertext, u8* plaintext, u32 msglen)
{
	memmove(plaintext, ciphertext, msglen);
	nls_decrypt(&ctx->ctx.ctx, (UCHAR *)plaintext, msglen);
}

void
ECRYPT_AE_authenticate_bytes(ECRYPT_AE_ctx* ctx, const u8* aad, u32 aadlen)
{
	nls_maconly(&ctx->ctx.ctx, (UCHAR *)aad, aadlen);
}

void
ECRYPT_AE_finalize(ECRYPT_AE_ctx* ctx, u8* mac)
{
	nls_finish(&ctx->ctx.ctx, (UCHAR *)mac, ctx->macctx.macsize);
}

#ifdef TEST_MAIN
/*
 * Test the API.
 */
int
main()
{
	const char *key = "test key 128bits";
	const char nonce[] = {0, 0, 0, 0};

	const char zero_vector[] = {
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	};

	#define ENCRYPT_BYTES 1000020
	const char encrypt_start_vector[] = {
		0x8a, 0xad, 0x39, 0xfd, 0x4a, 0xfa, 0xeb, 0xde, 0x05, 0xb7,
		0x27, 0x8e, 0x4a, 0xe3, 0xdf, 0xa9, 0x66, 0xc2, 0x1c, 0x52
	};
	const char encrypt_end_vector [] = {
		0x94, 0x46, 0x32, 0x50, 0xb1, 0x36, 0x9f, 0xa2, 0x7e, 0x63,
		0x2b, 0x05, 0x8c, 0xdd, 0x13, 0x1a, 0xa1, 0x11, 0xca, 0xad
	};

	#define MAC_BYTES 100
	const char mac_vector [] = {
		0x52, 0xf7, 0x11, 0x7f, 0x5b, 0x0c, 0x33, 0xde, 0x87, 0x61,
		0xab, 0xb6, 0xb5, 0xe4, 0xea, 0x91, 0x46, 0xf7, 0x78, 0xe0
	};

	ECRYPT_ctx ctx;
	ECRYPT_AE_ctx ae_ctx;
	char buffer[ENCRYPT_BYTES];
	char mac[sizeof(mac_vector)];
	int failures = 0;

#	define REPORT(name, predicate) (\
		(predicate)\
			? (printf ("%s: passed\n", (name)), 1)\
			: (printf ("%s: failed\n", (name)), 0)\
	)

	ECRYPT_init();

	/* encryption only */
	ECRYPT_keysetup(&ctx, key, strlen(key), sizeof(nonce));
	ECRYPT_ivsetup(&ctx, nonce);
	memset(buffer, 0, ENCRYPT_BYTES);
	ECRYPT_encrypt_bytes (&ctx, buffer, buffer, ENCRYPT_BYTES);
	failures += !REPORT ("encrypt only",
		memcmp (buffer, encrypt_start_vector,
			sizeof(encrypt_start_vector)) == 0
		&& memcmp (buffer + ENCRYPT_BYTES - sizeof(encrypt_end_vector),
			encrypt_end_vector, sizeof(encrypt_end_vector)) == 0);

	/* decryption only */
	ECRYPT_ivsetup(&ctx, nonce);
	ECRYPT_decrypt_bytes (&ctx, buffer, buffer, ENCRYPT_BYTES);
	failures += !REPORT ("decrypt only",
		memcmp (buffer, zero_vector, sizeof(zero_vector)) == 0
		&& memcmp (buffer + ENCRYPT_BYTES - sizeof(zero_vector),
			zero_vector, sizeof(zero_vector)) == 0);

	/* mac only */
	ECRYPT_AE_keysetup(&ae_ctx, key, strlen(key), sizeof(nonce),
		sizeof(mac));
	ECRYPT_AE_ivsetup(&ae_ctx, nonce);
	memset(buffer, 0, MAC_BYTES);
	ECRYPT_AE_authenticate_bytes(&ae_ctx, buffer, MAC_BYTES);
	ECRYPT_AE_finalize(&ae_ctx, mac);
	failures += !REPORT ("mac only",
		memcmp (mac, mac_vector, sizeof(mac_vector)) == 0);

	/* encrypt and mac */
	ECRYPT_AE_ivsetup(&ae_ctx, nonce);
	memset(buffer, 0, MAC_BYTES);
	ECRYPT_AE_encrypt_bytes(&ae_ctx, buffer, buffer, MAC_BYTES);
	ECRYPT_AE_finalize(&ae_ctx, mac);
	failures += !REPORT ("encrypt+mac",
		memcmp (buffer, encrypt_start_vector,
			sizeof(encrypt_start_vector)) == 0
		&& memcmp (mac, mac_vector, sizeof(mac_vector)) == 0);

	/* decrypt and mac */
	ECRYPT_AE_ivsetup(&ae_ctx, nonce);
	ECRYPT_AE_decrypt_bytes(&ae_ctx, buffer, buffer, MAC_BYTES);
	ECRYPT_AE_finalize(&ae_ctx, mac);
	failures += !REPORT ("decrypt+mac",
		memcmp (buffer, zero_vector, sizeof(zero_vector)) == 0
		&& memcmp (mac, mac_vector, sizeof(mac_vector)) == 0);

	return (failures);
}
#endif /* TEST_MAIN */
