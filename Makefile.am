LIBREFMEM_LIBRARY_VERSION=1:0:0

lib_LTLIBRARIES = librefmem-1.la
librefmem_1_la_SOURCES = refmem/refmemm.c \
                         refmem/refmemm_allocator.c \
                         refmem/refmemm_allocator_system.c
librefmem_1_la_LDFLAGS = -version-info $(LIBREFMEM_LIBRARY_VERSION)

library_includedir = $(includedir)/refmem-1
library_include_HEADERS = refmem/refmemm.h refmem/refmem_atomic.h refmem/refmem_object.h

include test/include.am
