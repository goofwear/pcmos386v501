/*
;,fs
;******** $.
;,fe
=====================================================================
               (c) copyright 1992, the software link inc.
                       all rights reserved

 module name:        ulopclwn.c
 creation date:      04/01/92
 revision date:      
 author:             mjs
 description:        ulib module

======================================================================

mjs 04/01/92	created this module

=======================================================================
*/

#include <stdlib.h>
#include <dos.h>
#include <malloc.h>

#include <asmtypes.h>
#include "ulib.h"

/*======================================================================
;,fs
; wintype ul_open_window(byte xl,byte yt,byte xr,byte yb,byte vattr1,byte vattr2,byte boxtype)
; 
; in:	
;
; out:	
;
;,fe
========================================================================*/
wintype ul_open_window(byte xl,byte yt,byte xr,byte yb,byte vattr1,byte vattr2,byte boxtype) {

  wintype win;
  word retval;

  if((win = (wintype) _fmalloc(sizeof(twin))) == NULL) {
    return(NULL);
    }
  if((win->winptr = _fmalloc((xr-xl+1)*(yb-yt+1)*2)) == NULL) {
    _ffree(win);
    return(NULL);
    }
  win->xl = xl;
  win->yt = yt;
  win->xr = xr;
  win->yb = yb;
  retval = ul_get_cursor();
  win->x_coord = retval & 0xff;
  win->y_coord = retval >> 8;
  ul_save_window(xl,yt,xr,yb,win->winptr);
  ul_clr_box(xl,yt,xr,yb,vattr1);

  ul_draw_box(xl,yt,xr,yb,vattr2,boxtype);
  return(win);
  }

/*======================================================================
;,fs
; void ul_close_window(wintype win)
; 
; in:	
;
; out:	
;
;,fe
========================================================================*/
void ul_close_window(wintype win) {

  ul_restore_window(win->xl,win->yt,win->xr,win->yb,win->winptr);
  ul_set_cursor(win->x_coord,win->y_coord);
  _ffree(win->winptr);
  _ffree(win);
  }

