//
// Created by workstation on 12/14/21.
//
#include <linux/lz4.h>

#ifndef LINUX_COMPRESS_INTERFACE_H
#define LINUX_COMPRESS_INTERFACE_H
//struct ci_strm {
//	/* compression/decompression buffer */
//	void *buffer;
//	struct crypto_comp *tfm;
//};

struct crypto_comp *ci_tfm;

//int zcomp_compress(struct ci_strm *zstrm,
//		   char *src, unsigned int *dst_len);
//
//int zcomp_decompress(struct ci_strm *zstrm,
//		     char *src, unsigned int src_len, void *dst);

int ci_compress(char *src, unsigned int src_len, char *dst,
		unsigned int *dst_len);
int ci_decompress(char *src, unsigned int src_len, char *dst,
		  unsigned int *dst_len);

#endif //LINUX_COMPRESS_INTERFACE_H
