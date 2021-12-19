//
// Created by workstation on 12/14/21.
//

#include <linux/kernel.h>
#include <linux/crypto.h>
#include <linux/string.h>
#include <linux/err.h>
#include <linux/slab.h>
#include <linux/wait.h>
#include <linux/sched.h>
#include <linux/cpu.h>

#include <linux/compress-interface.h>

/*
 * allocate new ci_strm structure with ->tfm initialized by
 * backend, return NULL on error
 */
static struct crypto_comp *ci_alloc(void)
{
	ci_tfm = crypto_alloc_comp("lz4", 0, 0);

	if (!ci_tfm) {
		printk("unable to allocate tfm ");
	}

	return ci_tfm;
}
/**
 * Compression wrapper to compress with
 * @param src src pointer of data
 * @param src_len Length to consider of src
 * @param dst The destination to write compressed data to, The size of compressed
 * data can be greater than compressed because of padding. Suggested size is 2x of src
 * @param dst_len The size of whole dst but the library will modify this pointer to actual
 * size of compressed dst
 * @return
 */
int ci_compress(char *src, unsigned int src_len, char *dst,
		unsigned int *dst_len)
{
	printk("compression starting");
	if (!src) {
		printk("src is null");
	}

	if (!src_len) {
		printk("srclen is null");
	}

	if (!dst) {
		printk("dst is null");
	}

	if (!dst_len) {
		printk("dst_len is null");
	}

	if (!ci_tfm) {
		printk("unable to allocate tfm ");
		ci_tfm = ci_alloc();
	}
	int result = crypto_comp_compress(ci_tfm, src, src_len, dst, dst_len);

	if (result == 0) {
		printk("compression is successful");
	} else {
		printk("compression is not successful %d", result);
	}

	return result;
}
/**
 * Decompression Function wrapper.
 * @param src Pointer to src
 * @param src_len Length of src to consier
 * @param dst Memory to write decompressed data to, usually higher then srd
 * @param dst_len The true size of the whole dst, but the library  will modify this to actual
 * decompressed length
 * @return
 */
int ci_decompress(char *src, unsigned int src_len, char *dst, unsigned int *dst_len)
{
	printk("decompression starting");
	if (!src) {
		printk("src is null");
	}
	if (!src_len) {
		printk("srclen is null");
	}
	if (!dst) {
		printk("dst is null");
	}

	if (!dst_len) {
		printk("dst_len is null");
	}

	if (!ci_tfm) {
		printk("unable to allocate tfm ");
		ci_tfm = ci_alloc();
	}
	int result = crypto_comp_decompress(ci_tfm, src, src_len, dst, dst_len);
	if (result == 0) {
		printk("decompression is successful");
	} else {
		printk("decompression is not successful %d", result);
	}
	return result;
}

/**
 * This is just a test system call for compression testing.
 * No need to cleanup this properly, useful when seems a problem in
 * compression/decompression
 * @return
 */
asmlinkage long compress_for_extent(void)
{
	printk("Hello world 1\n");
	//	struct ci_strm *ciStrm = ci_strm_alloc();
	//	printk("ci stream allocated");
	char *src = kmalloc(sizeof(char) * PAGE_SIZE, GFP_KERNEL);
	char *src_static =
		"Lorem Ipsum is simply dummy text of the printing and typesetting industry. Lorem Ipsum has been the industry's standard dummy text ever since the 1500s, when an unknown printer took a galley of type and scrambled it to make a type specimen book. It has survived not only five centuries, but also the leap into electronic typesetting, remaining essentially unchanged. It was popularised in the 1960s with the release of Letraset sheets containing Lorem Ipsum passages, and more recently with desktop publishing software like Aldus PageMaker including versions of Lorem Ipsum.It is a long established fact that a reader will be distracted by the readable content of a page when looking at its layout. The point of using Lorem Ipsum is that it has a more-or-less normal distribution of letters, as opposed to using 'Content here, content here', making it look like readable English. Many desktop publishing packages and web page editors now use Lorem Ipsum as their default model text, and a search for 'lorem ipsum' will uncover many web sites still in their infancy. Various versions have evolved over the years, sometimes by accident, sometimes on purpose (injected humour and the like).Contrary to popular belief, Lorem Ipsum is not simply random text. It has roots in a piece of classical Latin literature from 45 BC, making it over 2000 years old. Richard McClintock, a Latin professor at Hampden-Sydney College in Virginia, looked up one of the more obscure Latin words, consectetur, from a Lorem Ipsum passage, and going through the cites of the word in classical literature, discovered the undoubtable source. Lorem Ipsum comes from sections 1.10.32 and 1.10.33 of \"de Finibus Bonorum et Malorum\" (The Extremes of Good and Evil) by Cicero, written in 45 BC. This book is a treatise on the theory of ethics, very popular during the Renaissance. The first line of Lorem Ipsum, \"Lorem ipsum dolor sit amet..\", comes from a line in section 1.10.32.\"Sed ut perspiciatis unde omnis iste natus error sit voluptatem accusantium doloremque laudantium, totam rem aperiam, eaque ipsa quae ab illo inventore veritatis et quasi architecto beatae vitae dicta sunt explicabo. Nemo enim ipsam voluptatem quia voluptas sit aspernatur aut odit aut fugit, sed quia consequuntur magni dolores eos qui ratione voluptatem sequi nesciunt. Neque porro quisquam est, qui dolorem ipsum quia dolor sit amet, consectetur, adipisci velit, sed quia non numquam eius modi tempora incidunt ut labore et dolore magnam aliquam quaerat voluptatem. Ut enim ad minima veniam, quis nostrum exercitationem ullam corporis suscipit laboriosam, nisi ut aliquid ex ea commodi consequatur? Quis autem vel eum iure reprehenderit qui in ea voluptate velit esse quam nihil molestiae consequatur, vel illum qui dolorem eum fugiat quo voluptas nulla pariatur? \"But I must explain to you how all this mistaken idea of denouncing pleasure and praising pain was born and I will give you a complete account of the system, and expound the actual teachings of the great explorer of the truth, the master-builder of human happiness. No one rejects, dislikes, or avoids pleasure itself, because it is pleasure, but because those who do not know how to pursue pleasure rationally encounter consequences that are extremely painful. Nor again is there anyone who loves or pursues or desires to obtain pain of itself, because it is pain, but because occasionally circumstances occur in which toil and pain can procure him some greatNo one rejects, dislikes, or avoids pleasure itself, because it is pleasure, but because those who do not know how to pursue pleasure rationally encounter consequences that are extremely painful. Nor again is there anyone who loves or pursues or desires to obtain pain of itself, because it is pain, but because occasionally circumstances occur in which toil and pain can procure him some greatNo one rejects, dislikes, or avoids pleasure itself, because it is pleasure, but because those who do not know how to pursue pleasure rationally encounter consequences that are extremely painful. Nor again fsadfdsfdsgdsgdsgds";
	if (!src) {
		printk("unable to allocate src ");
	}
	printk("src stream allocated");
	char *dst = kmalloc(sizeof(char) * PAGE_SIZE * 3, GFP_KERNEL);
	if (!dst) {
		printk("unable to allocate dst");
	}
	unsigned int dst_len = PAGE_SIZE * 2;
	unsigned int orig_len = PAGE_SIZE * 2;
	printk("dst stream allocated");
	char *orig = kmalloc(sizeof(char) * PAGE_SIZE * 3, GFP_KERNEL);
	if (!orig) {
		printk("unable to allocate orig ");
	}
	printk("orig stream allocated");
	unsigned int src_len = strlen(src_static);
	int i;
	//	for (i = 0; i < src_len; i++) {
	//		printk("src is %d %d", i, src[i]);
	//		src[i] = src_static[i];
	//	}
	//	for (i = 0; i < src_len; i=i+5) {
	//		printk("src is %d %d",i,src_len);
	//		src[i] ='a';
	//		src[i+1] ='b';
	//		src[i+2] ='c';
	//		src[i+3] ='d';
	//		src[i+4] ='e';
	//	}

	//	for (i = 0; i < src_len; i++) {
	printk("printing src %s", src);
	//	}
	printk("src intialized stream allocated %p %p checked", src, dst);
	////struct ci_strm *zstrm,  void *src,  int src_len,
	//		 void *dst,  int *dst_len
	//	int ret = ci_compress(ciStrm, (void*)src, src_len, (void*)dst, &dst_len);
	int ret = ci_compress((char *)src, src_len, (char *)dst,
			      &dst_len);
	printk("compression done");
	//	printk((const char *)ret);
	printk("going for decompression");
	printk("length of decom chars is %d %d", dst_len, strlen(dst));
	//	for (i = 0; i < dst_len; i++) {
	//		printk("printing compress char %c ", dst[i]);
	//	}
	ret = ci_decompress((char *)dst, dst_len, (char *)orig, &orig_len);
	printk("orig len is %d", orig_len);

	printk("printing orig %s", orig);

	printk("Hello world 2\n");
	return 0;
}
