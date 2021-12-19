//
// Created by workstation on 12/14/21.
//

/*
 * Test the stephen syscall (#329)
 */
#define _GNU_SOURCE
#include <unistd.h>
#include <sys/syscall.h>
#include <stdio.h>

/*
 * Put your syscall number here.
 */
#define compress_for_extent 548

int main(int argc, char **argv)
{
    printf("Making system call with");
    long res = syscall(compress_for_extent);
    printf("System call returned %ld.\n", res);
    return res;
}