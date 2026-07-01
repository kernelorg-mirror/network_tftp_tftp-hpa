SRCROOT = ..
VERSION = $(shell cat ../version)

-include ../config/MCONFIG
include ../MRULES

OBJS = tftpsubs.$(O) signal.$(O) xmalloc.$(O) xstrdup.$(O) progname.$(O)
LIB  = libcommon.a

all: $(LIB)

$(LIB): $(OBJS)
	-rm -f $(LIB)
	$(AR) $(LIB) $(OBJS)
	$(RANLIB) $(LIB)

$(OBJS): tftpsubs.h

install:

clean:
	rm -f *.o *.obj *.exe $(LIB)

distclean: clean
	rm -f *~
