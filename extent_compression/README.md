compile_kern.sh # Make sure make modules is enabled
copy_data_to_qemu.sh ./crypto/lz4.ko /root/
copy_data_to_qemu.sh ./lib/lz4/lz4_compress.ko /root/
run_qemu.sh

# After logging inside qemu vm
insmod lz4_compress.ko
insmod lz4.ko

# To Test just compression
copy_data_to_qemu.sh extent_compression/user-compress-test.c /root/ # On host
gcc user-compress-test.c # While inside qemu
./a.out  # While inside qemu

