# c

## memcpy内存重叠问题

memcpy 是一个用于内存拷贝的函数，它按字节逐个复制源内存块中的数据到目标内存块。当源和目标内存块出现重叠时，memcpy 的行为是未定义的，这意味着它可能产生意想不到的结果。

具体来说，当源内存和目标内存有重叠时，可能会发生以下两种情况之一：

源内存在目标内存之前：这种情况下，memcpy 可能会将源内存中的数据覆盖掉目标内存中的部分数据，导致数据损坏。

目标内存在源内存之前：这种情况下，memcpy 可能会将源内存中的数据复制到目标内存之前的位置，覆盖掉尚未被复制的数据，同样导致数据损坏。

为了避免这种问题，应该使用 memmove 函数代替 memcpy。memmove 能够处理内存重叠的情况，确保数据正确地从源内存复制到目标内存。

总之，当进行内存拷贝时，如果存在内存重叠的情况，应该使用 memmove 函数而不是 memcpy 函数，以确保数据的正确性。

'''
void* memcopy(void* dest, const void* src, size_t n) {
    unsigned char* d = (unsigned char*)dest;
    const unsigned char* s = (const unsigned char*)src;

    if (d >= s && d < s + n) {
        // 源内存与目标内存有重叠，从后往前复制
        d += n;
        s += n;
        while (n--)
            *--d = *--s;
    }
    else {
        // 源内存与目标内存没有重叠，从前往后复制
        while (n--)
            *d++ = *s++;
    }

    return dest;
}
'''
