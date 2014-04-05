LIBREFMEM_LIBRARY_VERSION=1:0:0

lib_LTLIBRARIES = librefmem-1.la
librefmem_1_la_SOURCES = refmem-1/refmemm.c \
                         refmem-1/refmemm_allocator.c \
                         refmem-1/refmemm_allocator_system.c
librefmem_1_la_LDFLAGS = -version-info $(LIBREFMEM_LIBRARY_VERSION)

library_includedir = $(includedir)/refmem-1
library_include_HEADERS = refmem-1/refmemm.h refmem-1/refmem_atomic.h refmem-1/refmem.h refmem-1/refmemm_allocator.h 

include test/include.am
