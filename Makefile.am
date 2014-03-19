LIBREFMEM_LIBRARY_VERSION=1:0:0

TESTS = test/test-refmem

AM_CFLAGS = -I./include

lib_LTLIBRARIES = librefmem-1.la
librefmem_1_la_SOURCES = refmem-1/refmem.c
librefmem_1_la_LDFLAGS = -version-info $(LIBREFMEM_LIBRARY_VERSION)

library_includedir = $(includedir)/refmem-1
library_include_HEADERS = refmem-1/refmem.h

include test/include.am
