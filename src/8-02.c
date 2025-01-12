// Exercise 8-2.
// Rewrite fopen and _fillbuf with fields instead of explicit bit
// operations. Compare code size and execution speed.

// Exercise 8-3.
// Design and write _flushbuf, fflush, and fclose.

// see: https://www.man7.org/linux/man-pages/man0/unistd.h.0p.html
#include <unistd.h> // universal std.h (POSIX definitions)
#include <fcntl.h> // open(char *name, mode, perms);
#include <stdlib.h>


// #define NULL 0
#define EOF (-1)
#define BUFSIZ 1024
#define OPEN_MAX 20 // max #files open at once

typedef struct _iobuf {
	int cnt;
	char *ptr;
	char *base;
	int flag;
	int fd;

} FILE;
extern FILE _iob[OPEN_MAX];


enum _flags {
_READ = 01,
_WRITE = 02,
_UNBUF = 04,
_EOF = 010,
_ERR = 020
};

FILE _iob[OPEN_MAX] = { /* stdin, stdout, stderr: */
{ 0, (char *) 0, (char *) 0, _READ, 0},
{ 0, (char *) 0, (char *) 0, _WRITE, 1},
{ 0, (char *) 0, (char *) 0, _WRITE | _UNBUF, 2}
};

#define stdin (&_iob[0])
#define stdout (&_iob[1])
#define stderr (&_iob[2])

int _fillbuf(FILE *);
int _flushbuf(int, FILE *);

#define feof (((p)->flag & _EOF) != 0)
#define ferror (((p)->flag & _ERR) != 0)
#define fileno ((p)->fd)

#define getc(p)  (--(p)->cnt >= 0				\
		  ? (unsigned char) *(p)->ptr++ : _fillbuf(p))
#define putc(x,p)  (--(p)->cnt >= 0				\
		    ? *(p)->ptr++ = (x) : _flushbuf((x), p))
#define getchar()  getc(stdin)
#define putchar(x) putc((x), stdout);

#define PERMS 0666  // RW for owner, group, others


/* fopen: open file, return file ptr */
FILE *fopen(char *name, char *mode)
{
	int fd;
	FILE *fp;

	if (*mode != 'r' && *mode != 'w' && *mode != 'a')
		return NULL;
	for (fp = _iob; fp < _iob + OPEN_MAX; fp++)
		if ((fp->flag & (_READ | _WRITE)) == 0)
			break;    /* found free slot */
	if (fp >= _iob + OPEN_MAX)
		return NULL;

	if (*mode == 'w')
		fd = creat(name, PERMS);
	else if (*mode == 'a') {
		if ((fd = open(name, O_WRONLY, 0)) == -1)
			fd = creat(name, PERMS);
		lseek(fd, 0L, 2); // '2' means go to end of file
	} else
		fd = open(name, O_RDONLY, 0);
	if (fd == -1)  /* couldn't access name */
		return NULL;
	fp->fd = fd;
	fp->cnt = 0;
	fp->base = NULL;
	fp->flag = (*mode == 'r') ? _READ : _WRITE;
	return fp;
}

/* _fillbuf: allocate and fill input buffer */
int _fillbuf(FILE *fp)
{
	int bufsize;

	if ((fp->flag&(_READ|_EOF|_ERR)) != _READ)
		return EOF;
	bufsize = (fp->flag & _UNBUF) ? 1 : BUFSIZ;
	if (fp->base == NULL) // no buffer yet
		if ((fp->base = (char *) malloc(bufsize)) == NULL)
			return EOF;  // can't get buffer
	fp->ptr = fp->base;
	fp->cnt = read(fp->fd, fp->ptr, bufsize);
	if (--fp->cnt < 0) {
		if (fp->cnt == -1)
			fp->flag |= _EOF;
		else
			fp->flag |= _ERR;
		fp->cnt = 0;
		return EOF;
	}
	return (unsigned char) *fp->ptr++;
}

int main()
{
	int c = getchar();

	return 0;
}
