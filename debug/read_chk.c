/* Copyright (C) 2005 Free Software Foundation, Inc.
   This file is part of the GNU C Library.

   The GNU C Library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Lesser General Public
   License as published by the Free Software Foundation; either
   version 2.1 of the License, or (at your option) any later version.

   The GNU C Library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Lesser General Public License for more details.

   You should have received a copy of the GNU Lesser General Public
   License along with the GNU C Library; if not, write to the Free
   Software Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA
   02111-1307 USA.  */

#include <unistd.h>
#include <sys/param.h>
#ifdef HAVE_INLINED_SYSCALLS
# include <errno.h>
# include <sysdep.h>
#endif


ssize_t
__read_chk (int fd, void *buf, size_t nbytes, size_t buflen)
{
  /* In case NBYTES is greater than BUFLEN, we read BUFLEN+1 bytes.
     This might overflow the buffer but the damage is reduced to just
     one byte.  And the program will terminate right away.  */
#ifdef HAVE_INLINED_SYSCALLS
  ssize_t n = INLINE_SYSCALL (read, 3, fd, buf, MIN (nbytes, buflen + 1));
#else
  ssize_t n = __read (fd, buf, MIN (nbytes, buflen + 1));
#endif
  if (n > 0 && (size_t) n > buflen)
    __chk_fail ();
  return n;
}