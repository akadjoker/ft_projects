/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djoker <djoker@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/03 16:18:20 by lrosa-do          #+#    #+#             */
/*   Updated: 2024/11/14 08:11:33 by djoker           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
#define LIBFT_H

#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include "ft_rbt.h"

#ifndef BUFFER_SIZE
#define BUFFER_SIZE 20
#endif

#ifndef MAX_FD
#define MAX_FD 10
#endif

void *ft_calloc(size_t count, size_t size);
void ft_bzero(void *s, size_t n);
void *ft_memset(void *b, int c, size_t len);
void *ft_memcpy(void *dst, const void *src, size_t n);
void *ft_memccpy(void *dst, const void *src, int c, size_t n);
void *ft_memmove(void *dst, const void *src, size_t len);
void *ft_memchr(const void *s, int c, size_t n);
int ft_memcmp(const void *s1, const void *s2, size_t n);

void ft_skip_space(const char *str, int *i);
void ft_skip_spacenl(const char *str, int *i);
void ft_skip_char(const char *str, int *i, char c);
void ft_skip_chars(const char *str, int *i, char *base);

int ft_isalpha(int c);
int ft_isdigit(int c);
int ft_isalnum(int c);
int ft_isascii(int c);
int ft_isprint(int c);
int ft_toupper(int c);
int ft_tolower(int c);
int ft_isupper(int c);
int ft_islower(int c);
int ft_chrcount(int c, char *str);
int ft_chrindex(int c, char *str);

void ft_strdel(char **s);
char *ft_strnew(int size);
void *ft_freetab(char **tab);
size_t ft_strlen(const char *s);
char *ft_strchr(const char *s, int c);
char *ft_strrchr(const char *s, int c);
int ft_strncmp(const char *s1, const char *s2, size_t n);
int ft_strcmp(const char *s1, const char *s2);
char *ft_strncpy(char *dst, const char *src, size_t len);
size_t ft_strlcpy(char *dst, const char *src, size_t dstsize);
size_t ft_strlcat(char *dst, const char *src, size_t dstsize);
char *ft_strnstr(const char *haystack, const char *needle, size_t len);
char *ft_strdup(const char *s1);
char *ft_substr(char const *s, unsigned int start, size_t len);
char *ft_strjoin(char const *s1, char const *s2);
char *ft_strjoinf(char *s1, int f1, char *s2, int f2);
char *ft_strtrim(char const *s1, char const *set);
char **ft_split(char const *s, char c);
char *ft_strmapi(char const *s, char (*f)(unsigned int, char));
int join_newstr(char **str, const char *src);
int get_next_line(int fd, char **line);

char *ft_itoa(int n);
char *ft_utoa(unsigned int n);
char *ft_utox(unsigned int n);
char *ft_utobx(unsigned int n);
char *ft_ltoa(long n);
char *ft_ultoa(unsigned long int n);
char *ft_ultox(unsigned long int n);
int ft_atoi(const char *str);

int ft_nbrlen(long n);
int ft_hexlen(long n);
int ft_baselen(long n, int base);
int ft_power(int nbr, int pow);

long ft_pow(int base, int power);

void ft_putstr(char *s);
void ft_putchar_fd(char c, int fd);
void ft_putstr_fd(char *s, int fd);
void ft_putendl_fd(char *s, int fd);
void ft_putnbr_fd(int n, int fd);

#endif
