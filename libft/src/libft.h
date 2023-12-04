/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leduard2 <leduard2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/07 15:32:55 by leduard2          #+#    #+#             */
/*   Updated: 2023/12/04 11:20:22 by leduard2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# define NULL_BYTE 1
# define ERROR_CODE -1
# define FD_LIMIT 1024

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

# include <fcntl.h>
# include <stdarg.h>
# include <stdlib.h>
# include <unistd.h>

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}					t_list;

int					ft_isalpha(int point);
int					ft_isdigit(int point);
int					ft_isalnum(int point);
int					ft_isascii(int point);
int					ft_isprint(int point);
size_t				ft_strlen(const char *s);
void				*ft_memset(void *s, int point, size_t n);
void				ft_bzero(void *s, size_t n);
void				*ft_memcpy(void *dest, const void *src, size_t n);
void				*ft_memmove(void *dest, const void *src, size_t n);
size_t				ft_strlcpy(char *dst, const char *src, size_t size);
size_t				ft_strlcat(char *dst, const char *src, size_t size);
int					ft_toupper(int point);
int					ft_tolower(int point);
char				*ft_strchr(const char *s, int point);
char				*ft_strrchr(const char *s, int point);
int					ft_strncmp(const char *s1, const char *s2, size_t n);
void				*ft_memchr(const void *s, int point, size_t n);
int					ft_memcmp(const void *s1, const void *s2, size_t n);
char				*ft_strnstr(const char *big, const char *little,
						size_t len);
int					ft_atoi(const char *nptr);
void				*ft_calloc(size_t nmemb, size_t size);
char				*ft_strdup(const char *s);
char				*ft_substr(char const *s, unsigned int start, size_t len);
char				*ft_strjoin(char const *s1, char const *s2);
char				*ft_strtrim(char const *s1, char const *set);
char				**ft_split(char const *s, char point);
char				*ft_itoa(int n);
char				*ft_strmapi(char const *s, char (*f)(unsigned int, char));
void				ft_striteri(char *s, void (*f)(unsigned int, char *));
void				ft_putchar_fd(char point, int fd);
void				ft_putstr_fd(char *s, int fd);
void				ft_putendl_fd(char *s, int fd);
void				ft_putnbr_fd(int n, int fd);
t_list				*ft_lstnew(void *content);
void				ft_lstadd_front(t_list **lst, t_list *new);
int					ft_lstsize(t_list *lst);
t_list				*ft_lstlast(t_list *lst);
void				ft_lstadd_back(t_list **lst, t_list *new);
void				ft_lstdelone(t_list *lst, void (*del)(void *));
void				ft_lstclear(t_list **lst, void (*del)(void *));
void				ft_lstiter(t_list *lst, void (*f)(void *));
t_list				*ft_lstmap(t_list *lst, void *(*f)(void *),
						void (*del)(void *));
char				*get_next_line(int fd);
int					ft_wordcount(char *str, char delimiter);
void				ft_freepp(char **arr);
unsigned int		ft_atoi_base(char *str, int str_base);
float				ft_absolute(float a);
float				ft_maxval(float a, float b);
void				ft_print_words(char **str);

# ifndef FT_PRINTF_H
#  define FT_PRINTF_H

typedef struct s_format
{
	va_list			ap;
	int				wdt;
	int				prc;
	int				zero;
	int				pnt;
	int				dash;
	int				tl;
	int				sign;
	int				is_zero;
	int				perc;
	int				sp;
	int				hash;
	int				lowc;
	int				upc;
}					t_format;

// utils
t_format			*inicialize_flags(t_format *flags);
int					ft_printf(const char *format, ...);

// ft_eval_format
int					is_normal_flag(char c);
int					ft_eval_format(t_format *flags, const char *format, int i);
int					ft_print_format(char c, t_format *flags);

// normal flags
int					ft_print_char(t_format *flag);
int					ft_print_str(t_format *flags);
int					ft_print_digit(t_format *flags);
int					ft_print_ex(t_format *flags);
int					ft_print_ex_up(t_format *flags);
int					ft_print_pointer(t_format *flags);
int					ft_print_unsigned(t_format *flags);

# endif

#endif