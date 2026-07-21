/* Just enough of windows.h for the console calls these programs make. */
#ifndef C75_WINDOWS_H
#define C75_WINDOWS_H

#include "c75shim.h"

typedef void *HANDLE;
typedef unsigned short WORD;
typedef unsigned long DWORD;
typedef int BOOL;

#define STD_INPUT_HANDLE ((DWORD)-10)
#define STD_OUTPUT_HANDLE ((DWORD)-11)
#define STD_ERROR_HANDLE ((DWORD)-12)
#define TRUE 1
#define FALSE 0

typedef struct { short X, Y; } COORD;
typedef struct { DWORD dwSize; BOOL bVisible; } CONSOLE_CURSOR_INFO;

static inline HANDLE GetStdHandle(DWORD n) { (void)n; return (HANDLE)1; }

static inline BOOL SetConsoleTextAttribute(HANDLE h, WORD attr)
{
    (void)h;
    c75_setcolor(attr);
    return TRUE;
}

/* The terminal draws its own caret; showing/hiding it is a no-op here. */
static inline BOOL SetConsoleCursorInfo(HANDLE h, const CONSOLE_CURSOR_INFO *i)
{
    (void)h; (void)i;
    return TRUE;
}

static inline BOOL SetConsoleTitle(const char *t)
{
    printf("\033]0;%s\007", t);
    fflush(stdout);
    return TRUE;
}

static inline BOOL SetConsoleCursorPosition(HANDLE h, COORD c)
{
    (void)h;
    printf("\033[%d;%dH", c.Y + 1, c.X + 1);
    fflush(stdout);
    return TRUE;
}

static inline void Sleep(DWORD ms) { c75_sleep((int)ms); }

static inline BOOL Beep(DWORD freq, DWORD dur)
{
    c75_beep((int)freq, (int)dur);
    return TRUE;
}

#endif
