/* See LICENSE for license details. */
#pragma once

#include <stdint.h>
#include <time.h>
#include <sys/types.h>
#include <X11/Xatom.h>
#include <X11/Xlib.h>
#include <X11/cursorfont.h>
#include <X11/keysym.h>
#include <X11/Xft/Xft.h>
#include <X11/XKBlib.h>
#include <X11/Xresource.h>

/* Arbitrary sizes */
#define UTF_INVALID   0xFFFD
#define UTF_SIZ       4
#define ESC_BUF_SIZ   (128*UTF_SIZ)
#define ESC_ARG_SIZ   16
#define STR_BUF_SIZ   ESC_BUF_SIZ
#define STR_ARG_SIZ   ESC_ARG_SIZ
/* size of title stack */
#define TITLESTACKSIZE 8

/* macros */
#define MIN(a, b)		((a) < (b) ? (a) : (b))
#define MAX(a, b)		((a) < (b) ? (b) : (a))
#define LEN(a)			(sizeof(a) / sizeof(a)[0])
#define BETWEEN(x, a, b)	((a) <= (x) && (x) <= (b))
#define DIVCEIL(n, d)		(((n) + ((d) - 1)) / (d))
#define DEFAULT(a, b)		(a) = (a) ? (a) : (b)
#define LIMIT(x, a, b)		(x) = (x) < (a) ? (a) : (x) > (b) ? (b) : (x)
#define ATTRCMP(a, b)		((a).mode != (b).mode || (a).fg != (b).fg || (a).bg != (b).bg)
#define TIMEDIFF(t1, t2)	((t1.tv_sec-t2.tv_sec)*1000 + (t1.tv_nsec-t2.tv_nsec)/1E6)
#define MODBIT(x, set, bit)	((set) ? ((x) |= (bit)) : ((x) &= ~(bit)))

#define TRUECOLOR(r,g,b)	(1 << 24 | (r) << 16 | (g) << 8 | (b))
#define IS_TRUECOL(x)		(1 << 24 & (x))
#define TLINE(y)  ((y) < term.scr ? term.hist[(((y) + term.histi - term.scr + histsize + 1) % histsize)] : term.line[(y) - term.scr])

#define ISNULL(x) ((x==NULL) ? 1 : 0)

enum glyph_attribute {
	ATTR_NULL       = 0,
	ATTR_BOLD       = 1 << 0,
	ATTR_FAINT      = 1 << 1,
	ATTR_ITALIC     = 1 << 2,
	ATTR_UNDERLINE  = 1 << 3,
	ATTR_BLINK      = 1 << 4,
	ATTR_REVERSE    = 1 << 5,
	ATTR_INVISIBLE  = 1 << 6,
	ATTR_STRUCK     = 1 << 7,
	ATTR_WRAP       = 1 << 8,
	ATTR_WIDE       = 1 << 9,
	ATTR_WDUMMY     = 1 << 10,
  ATTR_SIXEL      = 1 << 11,
  ATTR_BOXDRAW    = 1 << 12,
	ATTR_BOLD_FAINT = ATTR_BOLD | ATTR_FAINT,
};

enum selection_mode {
	SEL_IDLE = 0,
	SEL_EMPTY = 1,
	SEL_READY = 2
};

enum selection_type {
	SEL_REGULAR = 1,
	SEL_RECTANGULAR = 2
};

enum selection_snap {
	SNAP_WORD = 1,
	SNAP_LINE = 2
};

typedef unsigned char uchar;
typedef unsigned int uint;
typedef unsigned long ulong;
typedef unsigned short ushort;

typedef uint_least32_t Rune;

#define Glyph Glyph_
typedef struct {
	Rune u;           /* character code */
	ushort mode;      /* attribute flags */
	uint32_t fg;      /* foreground  */
	uint32_t bg;      /* background  */
} Glyph;

typedef Glyph *Line;

typedef union {
	int i;
	uint ui;
	float f;
	const void *v;
  const char *s;
} Arg;

typedef struct _ImageList {
  struct _ImageList *next, *prev;
  unsigned char *pixels;
  void *pixmap;
  int width;
  int height;
  int x;
  int y;
  int should_delete;
} ImageList;

typedef struct {
  Glyph attr; /* current char attributes */
  int x;
  int y;
  char state;
} TCursor;

/* Internal representation of the screen */
typedef struct {
  int row;      /* nb row */
  int col;      /* nb col */
  Line *line;   /* screen */
  Line *alt;    /* alternate screen */
  Line *hist;   /* history buffer */
  int histi;    /* history index */
  int scr;      /* scroll back */
  int *dirty;   /* dirtyness of lines */
  TCursor c;    /* cursor */
  int ocx;      /* old cursor col */
  int ocy;      /* old cursor row */
  int top;      /* top    scroll limit */
  int bot;      /* bottom scroll limit */
  int mode;     /* terminal mode flags */
  int esc;      /* escape state flags */
  char trantbl[4]; /* charset table translation */
  int charset;  /* current charset */
  int icharset; /* selected charset for sequence */
  int *tabs;
  Rune lastc;   /* last printed char outside of sequence, 0 if control */
  ImageList *images; /* sixel images */
  ImageList *images_alt; /* sixel images for alternate screen */
} Term;

/* Purely graphic info */
typedef struct {
  int tw, th; /* tty width and height */
  int w, h; /* window width and height */
  int dynborder_h, dynborder_w; /* dynamic border size */
  int ch; /* char height */
  int cw; /* char width  */
  int cyo; /* char y offset */
  int mode; /* window state/mode flags */
  int cursor; /* cursor style */
} TermWindow;

typedef XftDraw *Draw;
typedef XftColor Color;
typedef XftGlyphFontSpec GlyphFontSpec;

typedef struct {
  Display *dpy;
  Colormap cmap;
  Window win;
  Drawable buf;
  GlyphFontSpec *specbuf; /* font spec buffer used for rendering */
  Atom xembed, wmdeletewin, netwmname, netwmiconname, netwmpid;
  Atom window_fullscreen, window_state, skip_taskbar, skip_pager;
  Atom taskbar_icon_atom, cardinal_atom;
  struct {
    XIM xim;
    XIC xic;
    XPoint spot;
    XVaNestedList spotlist;
  } ime;
  Draw draw;
  Visual *vis;
  XSetWindowAttributes attrs;
  int scr;
  int isfixed; /* is fixed geometry? */
  int depth; /* bit depth */
  int l, t; /* left and top offset */
  int gm; /* geometry mask */
} XWindow;

typedef struct {
  Atom xtarget;
  char *primary, *clipboard;
  struct timespec tclick1;
  struct timespec tclick2;
} XSelection;

/* Font structure */
#define Font Font_
typedef struct {
  int height;
  int width;
  int ascent;
  int descent;
  int badslant;
  int badweight;
  short lbearing;
  short rbearing;
  XftFont *match;
  FcFontSet *set;
  FcPattern *pattern;
} Font;

/* Drawing Context */
typedef struct {
  Color *col;
  size_t collen;
  Font font, bfont, ifont, ibfont;
  GC gc;
} DC;

typedef struct {
  int mode;
  int type;
  int snap;
  /*
   * Selection variables:
   * nb – normalized coordinates of the beginning of the selection
   * ne – normalized coordinates of the end of the selection
   * ob – original coordinates of the beginning of the selection
   * oe – original coordinates of the end of the selection
   */
  struct {
    int x, y;
  } nb, ne, ob, oe;

  int alt;
} Selection;

/* CSI Escape sequence structs */
/* ESC '[' [[ [<priv>] <arg> [;]] <mode> [<mode>]] */
typedef struct {
  char buf[ESC_BUF_SIZ]; /* raw string */
  size_t len;               /* raw string length */
  char priv;
  int arg[ESC_ARG_SIZ];
  int narg;              /* nb of args */
  char mode[2];
} CSIEscape;

/* STR Escape sequence structs */
/* ESC type [[ [<priv>] <arg> [;]] <mode>] ESC '\' */
typedef struct {
  char type;             /* ESC type ... */
  char *buf; /* raw string */
  size_t siz; /* allocation size */
  size_t len;               /* raw string length */
  char *args[STR_ARG_SIZ];
  int narg;              /* nb of args */
} STREscape;

typedef struct {
  uint b;
  uint mask;
  void (*func)(const Arg *);
  const Arg arg;
} MouseKey;

void die(const char *, ...);
void redraw(void);
void draw(void);

void iso14755(const Arg *);
void go_fullscreen(const Arg *);
void printscreen(const Arg *);
void printsel(const Arg *);
void sendbreak(const Arg *);
void externalpipe(const Arg *);
void toggleprinter(const Arg *);

int tattrset(int);
void tnew(int, int);
void tresize(int, int);
void tsetdirtattr(int);
void ttyhangup(void);
int ttynew(char *, char *, char *, char **);
size_t ttyread(void);
void ttyresize(int, int);
void ttywrite(const char *, size_t, int);

void resettitle(void);

void selclear(void);
void selinit(void);
void selstart(int, int, int);
void selextend(int, int, int, int);
int selected(int, int);
char *getsel(void);

void *xmalloc(size_t);
void *xrealloc(void *, size_t);
char *xstrdup(char *);

int isboxdraw(Rune);
ushort boxdrawindex(const Glyph *);
#ifdef XFT_VERSION
/* only exposed to x.c, otherwise we'll need Xft.h for the types */
void boxdraw_xinit(Display *, Colormap, XftDraw *, Visual *);
void drawboxes(int, int, int, int, XftColor *, XftColor *, const XftGlyphFontSpec *, int);
#endif

void kscrolldown(const Arg *);
void kscrollup(const Arg *);
void histfree(void);

size_t utf8encode(Rune, char *);

static int borderpx;

/* config.h globals */
extern char *utmp;
extern char *scroll;
extern char *stty_args;
extern char *vtiden;
extern wchar_t *worddelimiters;
extern int allowaltscreen;
extern int allowwindowops;
extern char *termname;
extern int boxdraw, boxdraw_bold, boxdraw_braille;
extern unsigned int tabspaces;
extern unsigned int defaultfg;
extern unsigned int defaultbg;
extern unsigned int defaultcs;
extern unsigned int alpha;
extern char *shell;
extern int borderperc;
extern unsigned int histsize;
extern MouseKey mkeys[];
extern int debug;
extern unsigned int max_lines_before_sixel_deallocation;
extern Term term;

/* Globals */
extern DC dc;
extern XWindow xw;
extern XSelection xsel;
extern TermWindow win;

void drawregion(int, int, int, int);
