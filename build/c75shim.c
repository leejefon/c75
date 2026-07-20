#include "c75shim.h"

/* the macros below would otherwise recurse into these wrappers */
#undef fopen
#undef remove
#undef system
#undef gets

#include <ctype.h>

/* Turns a DOS path into a POSIX one: "text\\record.dat" -> "text/record.dat".
   Also drops a leading ".\" or drive letter, which a couple of files use. */
const char *c75_fixpath(const char *p)
{
    static char buf[512];
    size_t i = 0, j = 0;

    if (!p) return "";
    if (isalpha((unsigned char)p[0]) && p[1] == ':') i = 2;
    if (p[i] == '.' && (p[i + 1] == '\\' || p[i + 1] == '/')) i += 2;

    for (; p[i] && j < sizeof(buf) - 1; i++)
        buf[j++] = (p[i] == '\\') ? '/' : p[i];
    buf[j] = '\0';
    return buf;
}

FILE *c75_fopen(const char *p, const char *m)
{
    return fopen(c75_fixpath(p), m);
}

char *c75_gets(char *s)
{
    if (!fgets(s, 4096, stdin)) return NULL;
    s[strcspn(s, "\r\n")] = '\0';
    return s;
}

/* Windows console attribute -> ANSI SGR. The bit order differs: Windows packs
   blue-green-red-intensity, ANSI counts red-green-blue. */
void c75_setcolor(unsigned short attr)
{
    static const int map[8] = { 0, 4, 2, 6, 1, 5, 3, 7 };
    int fg = attr & 7, fgb = (attr >> 3) & 1;
    int bg = (attr >> 4) & 7, bgb = (attr >> 7) & 1;

    printf("\033[%dm\033[%dm", (fgb ? 90 : 30) + map[fg], (bgb ? 100 : 40) + map[bg]);
    fflush(stdout);
}

/* Draws the message box inline. It does not wait for a click: every caller
   here follows it with its own prompt, so blocking would ask twice. */
int c75_messagebox(const char *text, const char *caption)
{
    printf("\n\033[97;44m [ %s ] \033[0m\n", caption ? caption : "Message");
    for (const char *p = text; p && *p; p++) {
        if (*p == '\n') fputs("\n ", stdout);
        else fputc(*p, stdout);
    }
    fputs("\n", stdout);
    fflush(stdout);
    return IDOK;
}

static int hexval(char c)
{
    if (c >= '0' && c <= '9') return c - '0';
    if (c >= 'a' && c <= 'f') return c - 'a' + 10;
    if (c >= 'A' && c <= 'F') return c - 'A' + 10;
    return -1;
}

static int prefix(const char *s, const char *p)
{
    while (*p) {
        if (tolower((unsigned char)*s++) != tolower((unsigned char)*p++)) return 0;
    }
    return 1;
}

/*
 * The only shell commands these programs use are the DOS console ones. Each
 * maps onto something the JS terminal understands:
 *
 *   cls                     -> clear screen
 *   pause                   -> print the prompt, wait for a key
 *   title X                 -> OSC 0 (window title)
 *   mode con cols=X lines=Y -> OSC 77 (resize, handled by the terminal)
 *   color 0f                -> background/foreground pair
 *   mode con cp select=437  -> already how output is decoded; ignored
 */
int c75_system(const char *cmd)
{
    if (!cmd) return 1;
    while (*cmd == ' ') cmd++;

    if (prefix(cmd, "cls")) {
        fputs("\033[2J\033[H", stdout);
    } else if (prefix(cmd, "pause")) {
        fputs("Press any key to continue . . . ", stdout);
        fflush(stdout);
        c75_getch();
        fputc('\n', stdout);
    } else if (prefix(cmd, "title ")) {
        printf("\033]0;%s\007", cmd + 6);
    } else if (prefix(cmd, "color ")) {
        int bg = hexval(cmd[6]), fg = hexval(cmd[7]);
        if (bg >= 0 && fg >= 0) c75_setcolor((unsigned short)((bg << 4) | fg));
    } else if (prefix(cmd, "mode con")) {
        const char *c = strstr(cmd, "cols="), *l = strstr(cmd, "lines=");
        int cols = c ? atoi(c + 5) : 0, lines = l ? atoi(l + 6) : 0;
        if (cols || lines) printf("\033]77;%d;%d\007", cols, lines);
    }

    fflush(stdout);
    return 0;
}

/* Unbuffered stdout, so a prompt is always on screen before input blocks. */
__attribute__((constructor)) static void c75_init(void)
{
    setvbuf(stdout, NULL, _IONBF, 0);
}
