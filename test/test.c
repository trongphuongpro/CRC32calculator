#include <stdio.h>
#include <string.h>
#include "crc32.h"


int main() {
	const char *data[5] = {"codelungtung.com", "nguyentrongphuong", 
					"mr.trongphuongpro@gmail.com", "ntppro", "trongphuongpro"};

	for (uint8_t i = 0; i < 5; i++) {
		crc32_t crc = crc32_compute(data[i], strlen(data[i]));
		printf("CRC32: %#x\n", crc);
		printf("Check: %d\n", crc32_selfcheck(data[i], strlen(data[i]), crc));
	}
}