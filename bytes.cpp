#include <stdio.h>
#include <assert.h>
#include <string>

// Print the values at *ptr byte by byte
template <class T>
void write_bytes_seq(const T *ptr) {
    uint8_t *ptr_i = (uint8_t*)ptr;
    printf("%lu:", sizeof(T));
    // print each byte
    for(int i=0; i < sizeof(T); i++) {
        // print the first 4 bits
        printf("%x", ptr_i[i] >> 4);
        // print the second 4 bits
        printf("%x", ptr_i[i] & 0xf);
    }
}

template <class T>
void pptr_seq(const char *lbl, T *ptr) {
    // print label
    printf("S %s: ", lbl);

    // print hex value
    write_bytes_seq(ptr);
    printf(" | 0x%016llx", (u_int64_t)ptr);

    printf("\n");
}

// Print the value at *ptr
template <class T>
void write_bytes(const T *ptr) {
    char fmt[8] = "%";
    sprintf(fmt+strlen(fmt), "0%lux", 2 * sizeof(T));
    printf("%lu:", sizeof(T));
    printf(fmt, *ptr);
}

template <class T>
void pptr(const char *lbl, T *ptr) {
    // print label
    printf("N %s: ", lbl);

    // print hex value
    write_bytes(ptr);
    printf(" | 0x%016llx", (u_int64_t)ptr);

    printf("\n");
}

#define WTYPE uint32_t
#define SHIFT 1

int main(int argc, char **argv) {
    // allocate 8 bytes on the stack
    uint64_t buf = 0;

    // make a 4 byte int pointer to the 0-3rd bytes of buf
    WTYPE *good = (WTYPE*)&buf;
    pptr_seq("init", good);
    pptr("init", good);
    printf("\n");

    // make sure *good is aligned on a 4 byte boundary
    assert(0 == (uint64_t)good % sizeof(uint32_t));

    // write a value to 'good' and read it back
    *good = 0x12345678;
    pptr_seq("good", good);
    pptr("good", good);
    printf("\n");

    // make a 4 byte int pointer to the first 1-4th (misaligned)
    WTYPE *bad = (WTYPE*)((uint64_t)good + SHIFT);

    // make sure *bad is misaligned by 1 byte
    assert(SHIFT == (uint64_t)bad % sizeof(uint32_t));

    // write a value to 'bad' and read it back
    *bad = 0x90abcdef;
    pptr_seq("bad", bad);
    pptr("bad", bad);
    printf("\n");

    pptr_seq("good2", good);
    pptr("good2", good);
    printf("\n");
}
