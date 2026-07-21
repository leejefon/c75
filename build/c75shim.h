/*
 * c75shim.h - force-included into every program.
 *
 * These programs were written for Turbo C / Dev-C++ on Windows. This header
 * fills in the pieces the browser doesn't have: conio's raw-key input, the
 * handful of windows.h calls, and the DOS-isms (system("cls"), backslash
 * paths, gets()).
 */
#ifndef C75_SHIM_H
#define C75_SHIM_H

/*
 * These are pulled in for every program on purpose. Many of the sources call
 * time(), sqrt() or strcpy() without including the header, which the old
 * compiler waved through as an implicit int-returning declaration. On wasm a
 * wrong signature links to a stub that traps at runtime, so the real
 * prototypes have to be in scope.
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>
#include <ctype.h>

/* --- implemented in JS (see build/lib_c75.js) ------------------------- */

/* Reads one key straight from the terminal, bypassing stdin, the way conio's
   getch() reads the console on Windows. Blocks until a key is pressed. */
extern int c75_getch(void);
extern int c75_kbhit(void);
extern void c75_sleep(int ms);

/* Plays a tone at freq Hz for dur ms and blocks until it finishes, the way
   Win32 Beep() does. Used by program 54 to play a melody. */
extern void c75_beep(int freq, int dur);

/* --- implemented in c75shim.c ----------------------------------------- */

const char *c75_fixpath(const char *p);
FILE *c75_fopen(const char *p, const char *m);
int c75_system(const char *cmd);
char *c75_gets(char *s);
void c75_setcolor(unsigned short attr);
int c75_messagebox(const char *text, const char *caption);

/* A couple of programs pop a MessageBox for input errors. There is no window
   to put it in, so it is drawn into the terminal instead. Declared here rather
   than in windows.h because both callers rely on an implicit declaration. */
#define MB_OK 0
#define MB_OKCANCEL 1
#define MB_ICONERROR 16
#define MB_ICONWARNING 48
#define MB_ICONINFORMATION 64
#define IDOK 1

static inline int MessageBox(void *hwnd, const char *text, const char *caption,
                             unsigned int type)
{
    (void)hwnd; (void)type;
    return c75_messagebox(text, caption);
}

/* conio.h, for the files that call these without including anything */
static inline int getch(void) { return c75_getch(); }
static inline int kbhit(void) { return c75_kbhit(); }
static inline int getche(void)
{
    int c = c75_getch();
    putchar(c);
    fflush(stdout);
    return c;
}

/* MinGW's sleep() forwarded to the Win32 Sleep(), so it took milliseconds.
   The calls here — sleep(15), sleep(1200) — are written for that. POSIX
   sleep() counts seconds, which would stall these for twenty minutes. */
#define sleep(ms) c75_sleep((int)(ms))

/* DOS paths ("text\\record.dat") and the removed-in-C11 gets() */
#define fopen(p, m) c75_fopen((p), (m))
#define remove(p) remove(c75_fixpath(p))
#define system(c) c75_system(c)
#define gets(s) c75_gets(s)

#endif
