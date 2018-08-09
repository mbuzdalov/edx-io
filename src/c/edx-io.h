#ifndef __EDX_IO_H__
#define __EDX_IO_H__
#define _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_DEPRECATE

#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Initializes the library. Should be called before all other functions.
 */
void edx_open();

/**
 * De-initializes the library. Should be called after all other functions.
 */
void edx_close();

/**
 * Reads the next signed int32. If it fails, exits the program.
 */
int edx_next_i32();

/**
 * Reads the next signed int64. If it fails, exits the program.
 */
long long edx_next_i64();

/**
 * Reads the next double. If it fails, exits the program.
 */
double edx_next_double();

/**
 * Reads at most (max_length - 1) symbols of the next whitespace-free token.
 * Returns the length of the token.
 */
int edx_next_bounded(char *dest, int max_length);

/**
 * Reads the next whitespace-free token.
 */
char *edx_next_unbounded();

/**
 * Prints the given unsigned int32 value.
 */
void edx_print_ui32(unsigned value);

/**
 * Prints the given unsigned int32 value and puts a newline after it.
 */
void edx_println_ui32(unsigned value);

/**
 * Prints the given signed int32 value.
 */
void edx_print_i32(int value);

/**
 * Prints the given signed int32 value and puts a newline after it.
 */
void edx_println_i32(int value);

/**
 * Prints the given unsigned int64 value.
 */
void edx_print_ui64(unsigned long long value);

/**
 * Prints the given unsigned int64 value and puts a newline after it.
 */
void edx_println_ui64(unsigned long long value);

/**
 * Prints the given signed int64 value.
 */
void edx_print_i64(long long value);

/**
 * Prints the given signed int64 value and puts a newline after it.
 */
void edx_println_i64(long long value);

/**
 * Prints the given double value.
 */
void edx_print_double(double value);

/**
 * Prints the given double value and puts a newline after it.
 */
void edx_println_double(double value);

/**
 * Prints the given character.
 */
void edx_print_char(char value);

/**
 * Prints the given character and puts a newline after it.
 */
void edx_println_char(char value);

/**
 * Prints the given string.
 */
void edx_print(char const *string);

/**
 * Prints the given string and puts a newline ('\n') after it.
 */
void edx_println(char const *string);

/**
 * Prints the text using the given format string and other arguments.
 * Usual conventions apply.
 */
int edx_printf(char const *fmt_string, ...);

/**
 * THIS IS AN UNSAFE PART. DON'T USE IT UNLESS YOU REALLY KNOW HOW IT WORKS.
 *
 * Reads a non-whitespace token and returns a pointer to it.
 *
 * The memory which the token occupies is guaranteed to remain intact in subsequent calls.
 * This memory can be READ-ONLY.
 *
 * Depending on an implementation, you may or may not require to call "free" on the pointer
 * when it is no longer needed.
 *
 * The token may or may NOT end with a zero character '\0'. However, the implementation
 * will try its best to add this zero character. The length of the token is also returned.
 *
 * The idea of this function is to avoid copying when possible.
 *
 * All arguments may be NULL, in which case the value is not filled.
 */
char *edx_unsafe_read_token(size_t *length, int *ends_with_zero, int *must_be_freed);

#ifdef __cplusplus
}
#endif

#endif
