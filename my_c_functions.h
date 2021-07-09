#ifndef my_c_functions_H
#define my_c_functions_H

#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

#define OCT 8
#define DEC 10
#define HEX 12

char* my_strcpy(char* dst, char* src);

char* my_strdup(char* param_1);

char* combine_strings(char* first_string, char* second_string);

int my_strlen(char* string);

int my_recursive_pow(int base, int exponent);

int my_atoi_base(char* str, int str_base);

void my_putstr(char* param_1);

char* reverse_string(char* param_1);

char hex_to_char (int num, char base);

char* my_itoa_base(int value, int base);

int my_strcmp(char* param_1, char* param_2);

void null_filler_pointer(void* pointer, int length);

void split_string_word(char* destination_string, char** source_string, char delimiter);

int delimiter_count(char* source_string, char delimiter);

// char** split_string(char* og_source_string, char delimiter);

void free_string_array(char** string_array, int string_count);

int space_validator(char* source_string);

void my_putchar(char c);

void my_putnbr(int nb);

int my_isdigit(int c);

int my_str_is_numeric(char* str);

int nbr_inbase(char c, int base);

int	my_isalpha(int c);

#endif