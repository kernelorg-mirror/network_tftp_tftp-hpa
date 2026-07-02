# SPDX-License-Identifier: BSD-3-Clause

#
# Extra functions which may not be available everywhere
#

SRCROOT = ..

-include ../config/MCONFIG
include ../MRULES

ifeq ($(LIBOBJS),)
all:
else
all:	libxtra.a
endif

install:

clean:
	-rm -f *.a *.o *.obj *.exe

distclean: clean
	-rm -f *~

libxtra.a: $(LIBOBJS)
	-rm -f libxtra.a
	$(AR) libxtra.a $(LIBOBJS)
	$(RANLIB) libxtra.a
