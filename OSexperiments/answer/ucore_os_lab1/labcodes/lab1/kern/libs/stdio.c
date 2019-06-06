#include <defs.h>
#include <stdio.h>
#include <console.h>

/* HIGH level console I/O */

/* *
 * cputch - writes a single character @c to stdout, and it will
 * increace the value of counter pointed by @cnt.
 * */
static void
cputch(int c, int *cnt) {
    cons_putc(c);
    (*cnt) ++;
}

// Extra added code for LAB1 CHALLENGE 1 !
/* *
 * cputch_user - writes a single character @c to stdout, and it will
 * increace the value of counter pointed by @cnt.
 * This function doesn't access hardware directly. Instead, it uses int 80h
 * to perform a system call.
 * */
static void
cputch_user(int c, int* cnt) {
    __asm__ volatile("movl %0, %%eax;"  :: "r"(c) );
    __asm__ volatile("int $0x80");
    (*cnt) ++;
}

/* *
 * vcprintf - format a string and writes it to stdout
 *
 * The return value is the number of characters which would be
 * written to stdout.
 *
 * Call this function if you are already dealing with a va_list.
 * Or you probably want cprintf() instead.
 * */
int
vcprintf(const char *fmt, va_list ap) {
    int cnt = 0;
    // Extra added code for LAB1 CHALLENGE 1 !
    volatile uint16_t currentCodeSegment;
    __asm__ volatile ("mov %%cs, %0;" : "=m"(currentCodeSegment));
    if((currentCodeSegment & 3) == 0) {
        vprintfmt((void*)cputch, &cnt, fmt, ap);
    }
    else {
        vprintfmt((void*)cputch_user, &cnt, fmt, ap);
    }
    return cnt;
}

/* *
 * cprintf - formats a string and writes it to stdout
 *
 * The return value is the number of characters which would be
 * written to stdout.
 * */
int
cprintf(const char *fmt, ...) {
    va_list ap;
    int cnt;
    va_start(ap, fmt);
    cnt = vcprintf(fmt, ap);
    va_end(ap);
    return cnt;
}

/* cputchar - writes a single character to stdout */
void
cputchar(int c) {
    cons_putc(c);
}

/* *
 * cputs- writes the string pointed by @str to stdout and
 * appends a newline character.
 * */
int
cputs(const char *str) {
    int cnt = 0;
    char c;
    while ((c = *str ++) != '\0') {
        cputch(c, &cnt);
    }
    cputch('\n', &cnt);
    return cnt;
}

/* getchar - reads a single non-zero character from stdin */
int
getchar(void) {
    int c;
    while ((c = cons_getc()) == 0)
        /* do nothing */;
    return c;
}
