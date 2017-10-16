#ifndef __EDX_IO_H__
#define __EDX_IO_H__

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
 * Prints the given signed int32 value.
 */
void edx_print_i32(int value);

/**
 * Prints the given signed int32 value and puts a newline after it.
 */
void edx_println_i32(int value);

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
void edx_print(char *string);

/**
 * Prints the given string and puts a newline ('\n') after it.
 */
void edx_println(char *string);

/**
 * Prints the text using the given format string and other arguments.
 * Usual conventions apply.
 */
int edx_printf(char *fmt_string, ...);

#endif
