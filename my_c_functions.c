#include "my_c_functions.h"

char* my_strcpy(char* dst, char* src)
{
	int	i = 0;

	while (src[i])
	{
		dst[i] = src[i];
		i += 1;
	}
	dst[i] = '\0';
	return (dst);
}

char* my_strdup(char* param_1)
{
    char* str_copy;
 
    int length = my_strlen(param_1);
    str_copy = malloc((length + 1) * sizeof(char));
    int i = 0;
    while (i < length)
    {
        str_copy[i] = param_1[i];
        i++;
    }
    str_copy[i] = '\0';
    return str_copy;
}

char* combine_strings(char* first_string, char* second_string)
{
    char* return_val = malloc((my_strlen(first_string) + my_strlen(second_string) + 1) * sizeof(char));
    int i = 0;
    while (first_string[i] != '\0')
    {
        return_val[i] = first_string[i];
        i++;
    }
    int j = 0;
    while (second_string[j] != '\0')
    {
        return_val[i] = second_string[j];
        j++;
        i++;
    }
    return_val[i] = '\0';
    return return_val;
}

int my_strlen(char* string)
{
    int i = 0;
    while(string[i] != '\0')
    {
        i++;
    }
    return i;
}

int my_recursive_pow(int base, int exponent)
{
    int return_val;
    if (exponent == 0)
    {
        return_val = 1;
    }
    else
    {
        return_val = base * my_recursive_pow(base, exponent - 1);
    }
    return return_val;
}

int my_atoi_base(char* str, int str_base)
{
    int return_val = 0; //This holds the return value
    int i = 0; //This will store the count of characters that are integers
    if (str[i] == '-') //This is to catch if the number is negative
    {
        i++;
    }
    if (str[i] <= 47 || str[i] >= 58) //This is to check if the current character is an integer, otherwise 
    {
        return return_val;
    }
    while (str[i] > 47 && str[i] < 58)
    {
        i++;
    }
    int index = i - 1; //This is used to iterate from the last integer character to the first integer character
    for (int j = 0; j < i; j++)
    {
        if (str[index] == '-')
        {
            return_val = return_val * -1;
        }
        else
        {
            return_val = return_val + (str[index] - 48) * my_recursive_pow(str_base, j);
            index--;
        }
    }
    return return_val;
}

int my_isdigit(int c)
{
    return (c >= '0' && c <= '9');
}

//return 1 if string is numeric, otherwise return 0
int my_str_is_numeric(char* str)
{
    int i;

    i = 0;
    while (str[i])
        if (!my_isdigit(str[i++]))
            return (0);
    return (1);
}

void my_putchar(char c)
{
    write(1, &c, 1);
}

void my_putnbr(int nb)
{
    if (nb < 0)
    {
        nb = -nb;
        my_putchar('-');
    }
    if (nb < 10)
        my_putchar(nb + '0');
    else
    {
        my_putnbr(nb / 10);
        my_putnbr(nb % 10);
    }
}

void my_putstr(char* param_1)
{
    int i = 0;
    while(param_1[i] != '\0')
    {
        write(1,&param_1[i],1);
        i++;
    }
}

char* reverse_string(char* param_1)
{
    int length = my_strlen(param_1);    
    char* return_val = malloc(length + 1); //length is increased by 1 to allow for the null character
    for (int i = 0; i < (length / 2); i++)
    {
        char storage = param_1[i];
        return_val[i] = param_1[length - i - 1];
        return_val[length - i - 1] = storage;
    }
    return_val[length] = '\0';
    return return_val;
}

char hex_to_char (int num, char base)
{
    char return_val;
    if (num == 15)
    {
        if (base == 'X')
        {
            return_val = 'F';
        }
        else if (base == 'x')
        {
            return_val = 'f';
        }
        
    }
    else if (num == 14)
    {
        if (base == 'X')
        {
            return_val = 'E';
        }
        else if (base == 'x')
        {
            return_val = 'e';
        }
    }
    else if (num == 13)
    {
        if (base == 'X')
        {
            return_val = 'D';
        }
        else if (base == 'x')
        {
            return_val = 'd';
        }
    }
    else if (num == 12)
    {
        if (base == 'X')
        {
            return_val = 'C';
        }
        else if (base == 'x')
        {
            return_val = 'c';
        }
    }
    else if (num == 11)
    {
        if (base == 'X')
        {
            return_val = 'B';
        }
        else if (base == 'x')
        {
            return_val = 'b';
        }
    }
    else if (num == 10)
    {
        if (base == 'X')
        {
            return_val = 'A';
        }
        else if (base == 'x')
        {
            return_val = 'a';
        }
    }
    else
    {
        return_val = num + '0';
    }
    return return_val;
}

char* my_itoa_base(int value, int base)
{
	int len;
	long nbr;
	char* pointer;
	char* base_string = "0123456789ABCDEF";

	if (value == 0)
    {
        char* pointer = my_strdup("0");
        return pointer;
    }
	len = 0;
	nbr = value;
	while (nbr) //this loop sets the length of the string
	{
		nbr /= base;
		len += 1;
	}
	nbr = value;
	if (nbr < 0) //this increases the length of the string to add the '-' character
	{
		if (base == 10)
			len += 1;
		nbr *= -1;
	}
	if (!(pointer = (char *)malloc(sizeof(char) * len + 1)))
		return (NULL);
	pointer[len] = '\0'; //sets the last character to NULL
	while (nbr) //This loop fills the character string from the end to the beginning.
	{
		pointer[--len] = base_string[nbr % base];
		nbr /= base;
	}
	if (value < 0 && base == 10) //Sets the first character to '-' if the value is negative
		pointer[0] = '-';
    
    return (pointer);
}

int my_strcmp(char* param_1, char* param_2)
{
    int i = 0;
    while (param_1[i] != '\0' || param_2[i] != '\0')
    {
        int lex_diff = param_1[i] - param_2[i];
        if (lex_diff != 0)
        {
            return lex_diff;
        }
        i++;
    }
    return 0;
}

void null_filler_pointer(void* pointer, int length)
{
    char* index = pointer;
    int i = 0;
    while (i <= length)
    {
        index[i] = '\0';
        i++;
    }
}

void split_string_word(char* destination_string, char** source_string, char delimiter)
{
    int i = 0;
    while(source_string[0][i] != delimiter && i < my_strlen(source_string[0]))
    {
        destination_string[i] = source_string[0][i];
        i++;
    }
    destination_string[i] = '\0';
    source_string[0] = &source_string[0][i + 1];
}

int delimiter_count(char* source_string, char delimiter)
{
    int num_of_delim = 0;
    int i = 0;
    while(source_string[i] != '\0')
    {
        if (source_string[i] == delimiter)
        {
            num_of_delim++;
        }
        i++;
    }
    return num_of_delim;
}

char** split_string_array(char* og_source_string, char delimiter)
{
    char* source_string = my_strdup(og_source_string);
    char* source_string_start = source_string; //this variable stores the start location of source_string for freeing later

    int num_of_delim = delimiter_count(source_string, delimiter);
    int string_count = num_of_delim + 1; //The total number of split strings is equal to num_of_delim + 1

    char** return_array = malloc((string_count) * sizeof(char*));

    
    int k = 0; //index of string in retun_arrayf
    while (my_strlen(source_string) > 0)
    {
        int j = 0; //index of character in source_string
        while(source_string[j] != delimiter && j < my_strlen(source_string))
        {
            j++;
        }
        return_array[k] = malloc((j + 1) * sizeof(char));
        split_string_word(return_array[k], &source_string, delimiter);
        printf("\nsplit string = %s\n",return_array[k]);
        k++;
    }
    
    free(source_string_start);
    return return_array;
}

void free_string_array(char** string_array, int string_count)
{
    int i = 0;
    while (i < string_count)
    {
        free(string_array[i]);
        i++;
    }
    free(string_array);
}

//returns 0 if source_string is in compliance with Std. rules of the use of space otherwise return 1
//1. no space at the beggining or the end of the of the char*
//2. no consecutive use of the space character  
int space_validator(char* source_string)
{
    int i = 0;
    int len = my_strlen(source_string);

    if(source_string[i] == ' ' || source_string[len - 1] == ' ')
        return 1;

    while(source_string[i] != '\0')
    {
        if(source_string[i] == ' ' && source_string[i + 1] == ' ')
            return 1;
        
        i += 1;
    }

    return 0;
}

int nbr_inbase(char c, int base)
{
    if (base <= 10)
        return (c >= '0' && c <= '9');
    return ((c >= '0' && c <= '9') || (c >= 'A' && c <= ('A' + base - 10)) || \
    (c >= 'a' && c <= ('a' + base - 10)));
}

int	my_isalpha(int c)
{
	return ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z'));
}
