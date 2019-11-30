#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include "crc32.h"

static crc32_t crc32Table[256];


uint8_t reflect(uint8_t number) {
	uint8_t result = 0;
	for (uint8_t i = 0; i < 8; i++) {
		result = (result << 1) + ((number >> i) & 1);
	}
	return result;
}


void crc32_init() {
	crc32_t remainder;
	for (int data = 0; data < 256; data++) {
		remainder = data;
		for (uint8_t bit = 0; bit < 8; bit++) {
			if (remainder & 1)
				remainder = (remainder >> 1) ^ CRC32POLY_REVERSE;
			else
				remainder >>= 1;
		}
		crc32Table[data] = remainder;
	}
}


crc32_t crc32_compute(const void *data, uint32_t len) {
	uint8_t *msg = (uint8_t*)data;
	crc32_t remainder = 0xFFFFFFFF;
	
	for (uint32_t i = 0; i < len; i++) {
		remainder = crc32Table[msg[i] ^ (remainder & 0xFF)] ^ (remainder >> 8);
	}
	
	return ~remainder;
}


int crc32_selfcheck(const void *data, uint32_t len, crc32_t crc) {
	uint8_t *msg = (uint8_t*)calloc(len + 4, 1);
	crc = ~crc;

	memcpy(msg, data, len);
	memcpy(msg+len, &crc, 4);

	int ret = crc32_check(msg, len+4);

	free(msg);

	return ret;
}


int crc32_check(const void *data, uint32_t len) {
	crc32_t ret = ~crc32_compute(data, len);

	if (ret == 0)
		return 0;

	return -1;
}