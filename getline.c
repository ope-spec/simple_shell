#include "shell.h"

/**
* read_input - Reads and buffers chained commands from input.
* @info: Parameter struct.
* @buffer: Address of the buffer where the commands will be stored.
* @buffer_len: Address of a variable to store the length of the buffer.
*
* Return: The number of bytes read from the input.
*/
ssize_t read_input(info_t *info, char **buffer, size_t *buffer_len)
{
ssize_t bytes_read = 0;
size_t buffer_size = 0;

if (!*buffer_len)
{
free(*buffer);
*buffer = NULL;
signal(SIGINT, sigintHandler);

#if USE_GETLINE
bytes_read = getline(buffer, &buffer_size, stdin);
#else
bytes_read = _getline(info, buffer, &buffer_size);
#endif

if (bytes_read > 0)
{
if ((*buffer)[bytes_read - 1] == '\n')
{
(*buffer)[bytes_read - 1] = '\0';
bytes_read--;
}
info->linecount_flag = 1;
remove_comments(*buffer);
build_history_list(info, *buffer, info->histcount++);
{
*buffer_len = bytes_read;
info->cmd_buffer = buffer;
}
}
}
return (bytes_read);
}


/**
* get_input - Gets a line of input from STDIN minus the newline character.
* @info: parameter struct
*
* Return: The number of bytes read.
*/
ssize_t get_input(info_t *info)
{
static char *buf;
static size_t i, j, len;
ssize_t bytes_read = 0;
char **buf_p = &(info->arg);
char *p;

_putchar(BUF_FLUSH);
bytes_read = read_input(info, &buf, &len);

if (bytes_read == -1)
return (-1);

if (len)
{
j = i;
p = buf + i;

check_chain(info, buf, &j, i, len);

while (j < len)
{
if (is_chain(info, buf, &j))
break;
j++;
}

i = j + 1;

if (i >= len)
{
i = len = 0;
info->cmd_buf_type = CMD_NORM;
}

*buf_p = p;
return (_strlen(p));
}

*buf_p = buf;
return (bytes_read);
}

/**
* read_buf - Reads a buffer of size i.
* @info: parameter struct
* @buf: Buffer to read into.
* @i: Size of the buffer.
*
* Return: The number of bytes read.
*/
ssize_t read_buf(info_t *info, char *buf, size_t *i)
{
ssize_t f = 0;

if (*i)
return (0);
f = read(info->readfd, buf, READ_BUF_SIZE);
if (f >= 0)
*i = f;
return (f);
}

/**
* _getline - Reads a line of input from STDIN.
* @info: parameter struct
* @ptr: Address of a pointer to buffer, preallocated or NULL.
* @length: Size of preallocated ptr buffer if not NULL.
*
* Return: The string read from input.
*/
int _getline(info_t *info, char **ptr, size_t *length)
{
static char buf[READ_BUF_SIZE];
static size_t i, len;
size_t k;
ssize_t f = 0, s = 0;
char *p = NULL, *new_ptr = NULL, *c;

p = *ptr;
if (p && length)
s = *length;
if (i == len)
i = len = 0;

f = read_buf(info, buf, &len);
if (f == -1 || (f == 0 && len == 0))
return (-1);

c = _strchr(buf + i, '\n');
k = c ? 1 + (unsigned int)(c - buf) : len;
new_ptr = _realloc(p, s, s ? s + k : k + 1);
if (!new_ptr)
return (p ? free(p), -1 : -1);

if (s)
_strncat(new_ptr, buf + i, k - i);
else
_strncpy(new_ptr, buf + i, k - i + 1);

s += k - i;
i = k;
p = new_ptr;

if (length)
*length = s;
*ptr = p;
return (s);
}

/**
* sigintHandler - Signal handler function that
* blocks the SIGINT signal.
* @sig_number: The signal number.
* Return: void
*/
void sigintHandler(__attribute__((unused))int sig_number)
{
_puts("\n");
_puts("$ ");
_putchar(BUF_FLUSH);
}
