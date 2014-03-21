LIBREFMEM_LIBRARY_VERSION=1:0:0

lib_LTLIBRARIES = librefmem-1.la
librefmem_1_la_SOURCES = refmem/refmem.c refmem/refmem_atomic.c refmem/refmem_allocator_default.c
librefmem_1_la_LDFLAGS = -version-info $(LIBREFMEM_LIBRARY_VERSION)

library_includedir = $(includedir)/refmem-1
library_include_HEADERS = refmem/refmem.h refmem/refmem_atomic.h

include test/include.am
