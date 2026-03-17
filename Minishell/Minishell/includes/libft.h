/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlermo-j <mlermo-j@student.42malaga.c>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 15:08:50 by mlermo-j          #+#    #+#             */
/*   Updated: 2025/04/21 15:08:52 by mlermo-j         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>

# include <fcntl.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

typedef struct s_Index
{
	ssize_t		readed;
	size_t		i;
	size_t		j;
	size_t		jump;
	size_t		total;
}	t_Index;

typedef struct s_list
{
	void			*content;
	int				idx;			// current position
	int				target_idx;		// where it should go in stack A
	int				cost_a;			// rotations for A
	int				cost_b;			// rotations for B
	int				total_cost;
	int				is_cheapest;
	struct s_list	*next;
	struct s_list	*prev;
}					t_list;

/**
 * @brief Checks for an alphabetic character.
 * @param c Character to check
 * @return Non-zero value if c is an alphabetic character, otherwise 0
 */
int		ft_isalpha(int c);

/**
 * @brief Checks for an alphanumeric character.
 * @param c Character to check
 * @return Non-zero value if c is an alphanumeric character, otherwise 0
 */
int		ft_isalnum(int c);

/**
 * @brief Checks for an ASCII character.
 * @param c Character to check
 * @return Non-zero value if c is an ASCII character, otherwise 0
 */
int		ft_isascii(int c);

/**
 * @brief Checks for a printable character.
 * @param c Character to check
 * @return Non-zero value if c is a printable character, otherwise 0
 */
int		ft_isprint(int c);

/**
 * @brief Calculates the length of a string.
 * @param str String to calculate length
 * @return Length of the string
 */
size_t	ft_strlen(const char *str);

/**
 * @brief Fills the first n bytes of the memory area pointed to by s with the 
 * constant byte c.
 * @param s Pointer to the memory area
 * @param c Byte to fill
 * @param n Number of bytes to fill
 * @return Pointer to the memory area s
 */
void	*ft_memset(void *s, int c, size_t n);

/**
 * @brief Sets the first n bytes of the memory area pointed to by s to zero.
 * @param s Pointer to the memory area
 * @param n Number of bytes to set to zero
 * @return Pointer to the memory area s
 */
void	ft_bzero(void *s, size_t n);

/**
 * @brief Copies n bytes from memory area src to memory area dest.
 * The memory areas must not overlap.
 * @param dest Destination memory area
 * @param src Source memory area
 * @param n Number of bytes to copy
 * @return Pointer to the destination memory area dest
 */
void	*ft_memcpy(void *dest, const void *src, size_t n);

/**
 * @brief Copies n bytes from memory area src to memory area dest.
 * The memory areas may overlap.
 * @param dest Destination memory area
 * @param src Source memory area
 * @param n Number of bytes to copy
 * @return Pointer to the destination memory area dest
 */
void	*ft_memmove(void *dest, const void *src, size_t n);

/**
 * @brief Copies up to size - 1 characters from the string src to dst,
 * NUL-terminating the result if size is not 0.
 * @param dst Destination string
 * @param src Source string
 * @param size Size of the destination buffer
 * @return Total length of the string it tried to create
 */
size_t	ft_strlcpy(char *dst, const char *src, size_t size);

/**
 * @brief Appends the string src to the end of dst.
 * It will append at most size - strlen(dst) - 1 characters.
 * It will then NUL-terminate, unless size is 0 or the original dst string
 * was longer than size.
 * @param dst Destination string
 * @param src Source string
 * @param size Size of the destination buffer
 * @return Total length of the string it tried to create
 */
size_t	ft_strlcat(char *dst, const char *src, size_t size);

/**
 * @brief Checks for a digit (0 through 9).
 * @param c Character to check
 * @return Non-zero value if c is a digit, otherwise 0
 */
int		ft_isdigit(int c);

/**
 * @brief Converts a lowercase letter to uppercase.
 * @param c Character to convert
 * @return Converted uppercase character
 */
int		ft_toupper(int c);

/**
 * @brief Converts an uppercase letter to lowercase.
 * @param c Character to convert
 * @return Converted lowercase character
 */
int		ft_tolower(int c);

/**
 * @brief Locates the first occurrence of c (converted to a char) in 
 * the string s.
 * @param s String to search
 * @param c Character to locate
 * @return Pointer to the located character or NULL if not found
 */
char	*ft_strchr(const char *s, int c);

/**
 * @brief Locates the last occurrence of c (converted to a char) in the string s.
 * @param s String to search
 * @param c Character to locate
 * @return Pointer to the located character or NULL if not found
 */
char	*ft_strrchr(const char *s, int c);

/**
 * @brief Compares the first n bytes of s1 and s2.
 * @param s1 First string
 * @param s2 Second string
 * @param n Number of bytes to compare
 * @return An integer less than, equal to, or greater than zero if s1 is found,
 * respectively, to be less than, to match, or be greater than s2
 */
int		ft_strncmp(const char *s1, const char *s2, size_t n);

/**
 * @brief Scans the initial n bytes of the memory area pointed to by s for the
 * first instance of c.
 * @param s Pointer to the memory area
 * @param c Character to locate
 * @param n Number of bytes to scan
 * @return Pointer to the located byte or NULL if not found
 */
void	*ft_memchr(const void *s, int c, size_t n);

/**
 * @brief Compares the first n bytes of s1 and s2.
 * @param s1 First memory area
 * @param s2 Second memory area
 * @param n Number of bytes to compare
 * @return An integer less than, equal to, or greater than zero if s1 is found,
 * respectively, to be less than, to match, or be greater than s2
 */
int		ft_memcmp(const void *s1, const void *s2, size_t n);

/**
 * @brief Locates the first occurrence of the null-terminated string little
 * in the string big, where not more than len characters are searched.
 * @param big String to search
 * @param little Substring to locate
 * @param len Maximum number of characters to search
 * @return Pointer to the beginning of the located substring or NULL 
 * if not found
 */
char	*ft_strnstr(const char *big, const char *little, size_t len);

/**
 * @brief Converts the initial portion of the string pointed to by nptr to int.
 * @param nptr String to convert
 * @return The converted integer value
 */
int		ft_atoi(const char *nptr);

/**
 * @brief Allocates memory for an array of nmemb elements of size bytes each
 * and returns a pointer to the allocated memory. The memory is set to zero.
 * @param nmemb Number of elements
 * @param size Size of each element
 * @return Pointer to the allocated memory
 */
void	*ft_calloc(size_t nmemb, size_t size);

/**
 * @brief Duplicates the string s by allocating memory and copying the content.
 * @param s String to duplicate
 * @return Pointer to the duplicated string
 */
char	*ft_strdup(const char *s);

/**
 * @brief Duplicates up to n characters of the string src by allocating memory
 * and copying the content.
 * @param src String to duplicate
 * @param n Maximum number of characters to duplicate
 * @return Pointer to the duplicated string
 */
char	*ft_strndup(const char *src, size_t n);

/**
 * @brief Extracts a substring from the string s.
 * @param s Source string
 * @param start Starting index of the substring
 * @param len Length of the substring
 * @return Pointer to the substring
 */
char	*ft_substr(char const *s, unsigned int start, size_t len);

/**
 * @brief Joins two strings into a new string.
 * @param s1 First string
 * @param s2 Second string
 * @return Pointer to the joined string
 */
char	*ft_strjoin(char const *s1, char const *s2);

/**
 * @brief Trims characters from the beginning and end of a string.
 * @param s1 Source string
 * @param set Characters to trim
 * @return Pointer to the trimmed string
 */
char	*ft_strtrim(char const *s1, char const *set);

/**
 * @brief Splits a string into an array of strings using a delimiter.
 * @param s Source string
 * @param c Delimiter character
 * @return Pointer to the array of strings
 */
char	**ft_split(char const *s, char c);

/**
 * @brief Converts an integer to a string.
 * @param n Integer to convert
 * @return Pointer to the converted string
 */
char	*ft_itoa(int n);

/**
 * @brief Applies a function to each character of a string to create
 * a new string.
 * @param s Source string
 * @param f Function to apply
 * @return Pointer to the new string
 */
char	*ft_strmapi(char const *s, char (*f)(unsigned int, char));

/**
 * @brief Applies a function to each character of a string.
 * @param s Source string
 * @param f Function to apply
 * @return Pointer to the joined string
 */
void	ft_striteri(char *s, void (*f)(unsigned int, char*));

/**
 * @brief Writes a character to a file descriptor.
 * @param c Character to write
 * @param fd File descriptor
 * @return void
 */
void	ft_putchar_fd(char c, int fd);

/**
 * @brief Writes a string to a file descriptor.
 * @param s String to write
 * @param fd File descriptor
 * @return void
 */
void	ft_putstr_fd(char *s, int fd);

/**
 * @brief Writes a string followed by a newline to a file descriptor.
 * @param s String to write
 * @param fd File descriptor
 * @return void
 */
void	ft_putendl_fd(char *s, int fd);

/**
 * @brief Writes an integer to a file descriptor.
 * @param n Integer to write
 * @param fd File descriptor
 * @return void
 */
void	ft_putnbr_fd(int n, int fd);

/**
 * @brief Creates a new list element.
 * @param content Content of the new element
 * @return Pointer to the new element
 */
t_list	*ft_lstnew(void *content);

/**
 * @brief Adds a new element at the beginning of a list.
 * @param lst Pointer to the list
 * @param new New element to add
 * @return Pointer to the modified list
 */
void	ft_lstadd_front(t_list **lst, t_list *new);

/**
 * @brief Returns the number of elements in a list.
 * @param lst Pointer to the list
 * @return Number of elements in the list
 */
int		ft_lstsize(t_list *lst);

/**
 * @brief Returns the last element of a list.
 * @param lst Pointer to the list
 * @return Pointer to the last element
 */
t_list	*ft_lstlast(t_list *lst);

/**
 * @brief Adds a new element at the end of a list.
 * @param lst Pointer to the list
 * @param new New element to add
 * @return Pointer to the modified list
 */
void	ft_lstadd_back(t_list **lst, t_list *new);

/**
 * @brief Deletes a single element from a list and frees the memory.
 * @param lst Pointer to the element to delete
 * @param del Function to delete the content
 * @return void
 */
void	ft_lstdelone(t_list *lst, void (*del)(void*));

/**
 * @brief Deletes and frees all elements of a list.
 * @param lst Pointer to the list
 * @param del Function to delete the content
 * @return void
 */
void	ft_lstclear(t_list **lst, void (*del)(void *));

/**
 * @brief Iterates over a list and applies a function to each element.
 * @param lst Pointer to the list
 * @param f Function to apply
 * @return void
 */
void	ft_lstiter(t_list *lst, void (*f)(void *));

/**
 * @brief Creates a new list by applying a function to each element 
 * of an existing list.
 * @param lst Pointer to the existing list
 * @param f Function to apply
 * @param del Function to delete the content in case of failure
 * @return Pointer to the new list
 */
t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *));

// ft_gnl_utils.c
int		ft_open(char *filename);
char	*read_line(int fd, char *stash);
char	*ft_free(char *buffer);
size_t	ft_strlen_char(const char *str, char c);
char	*update_stash(char *stash);

// ft_gnl.c
char	*extract_line(char *stash);
char	*get_next_line(int fd);

#endif
