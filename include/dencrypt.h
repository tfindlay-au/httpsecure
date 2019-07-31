//
//    FILE: Dencrypt.cpp
//  AUTHOR: Timothy Findlay
// VERSION: 0.1
// PURPOSE: Provide Encrypt / Decrypt functions for TP Link Smart Switch HS-100
//

#ifndef HTTPSECURE_DENCRYPT_H
#define HTTPSECURE_DENCRYPT_H

#include <assert.h>

/** @brief Decryption of TP-Link Smart Home Protocol XOR Autokey Cipher with starting key = 171
 * @param Buffer with encrypted message.
 * @param Buffer to store the result (JSON string)
 * @param Length of incoming and outgoing(*) data
 * @retval address of output buffer.
 *
 * @note incoming data can contain null and non-printable values.
 * @note outgoing data must allow space for a null terminator and so must
 *  be one byte longer (at minimum) than the incoming data.
 * @note the encrypted portion of the buffer skips 4 bytes of the payload.
 *  This procedure expects the starting address of the encrypted data, not the start of the payload.
 *
 */
static char * decrypt(const unsigned char* inBuf, char* outBuf, size_t len)
{
    unsigned char        key = 171;
    unsigned char        a;
    int                  i;

    assert(outBuf != NULL);
    assert(inBuf != NULL);

    outBuf = (char *) realloc(outBuf, len);

    for(i=0; i<(int)len; i++) {

        // Take each character and XOR with the key
        a = (unsigned char)(key ^ inBuf[i]);

        // Set the key to be the value of this character
        key = inBuf[i];

        // Store this character in the output buffer
        outBuf[i] = (char)a;
    }
    outBuf[i] = '\0';
    return outBuf;
}

/** @brief Encryption of TP-Link Smart Home Protocol XOR Autokey Cipher with starting key = 171
 * @param Buffer with plain text (JSON) string.
 * @param Buffer to store the result (Binary data, not null terminated.)
 * @param Length of incoming and outgoing data (not counting the null terminator in the incoming data.) size_t is 4 bytes on ESP32
 * @retval address of output buffer.
 *
 * @note outgoing data can contain null and non-printable values.
 * @note The first 4 bytes of the pay load is an unsigned int value with the size of the payload
 */
static unsigned char * encrypt(const char* inBuf, unsigned char* outBuf, size_t len)
{
    unsigned char        key = 171;
    unsigned char        a;
    int                  i;

    // Convert big endian to little endian 2a 00 00 00 -> 00 00 00 2a
    unsigned int padChar = __builtin_bswap32((unsigned int)len);

    // TODO What the frig is this! Optimize!
    outBuf[0] = ((unsigned char*) (&padChar))[0];
    outBuf[1] = ((unsigned char*) (&padChar))[1];
    outBuf[2] = ((unsigned char*) (&padChar))[2];
    outBuf[3] = ((unsigned char*) (&padChar))[3];

    // Iterate over the length of the input
    for(i=0; i<(int)len; i++) {

        // Take each character and XOR with the key
        a = key ^ (unsigned char)inBuf[i];

        // Set the key to be the value of this character
        key = a;

        // Store this character in the output buffer
        outBuf[i + sizeof(unsigned int)] = a;
    }
    return outBuf;
}

// END OF FILE

#endif //HTTPSECURE_DENCRYPT_H
