/*
 *  Multi2Sim
 *  Copyright (C) 2012  Rafael Ubal (ubal@ece.neu.edu)
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */

#ifndef DRIVER_OPENGL_OPENGL_H
#define DRIVER_OPENGL_OPENGL_H


/*
 * OPENGL system call interface
 *
 * NOTE: any additional function added to this interface should be implemented
 * both in 'opengl.c' and 'opengl-missing.c' to allow for correct compilation on
 * systems lacking the OpenGL and GLUT libraries.
 */

#define x86_opengl_debug(...) debug(x86_opengl_debug_category, __VA_ARGS__)
extern int x86_opengl_debug_category;

void x86_opengl_init(void);
void x86_opengl_done(void);

struct x86_ctx_t;
int x86_opengl_call(struct x86_ctx_t *ctx);


#endif

