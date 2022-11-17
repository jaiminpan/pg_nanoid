
MODULE_big = pg_nanoid
OBJS = pg_nanoid.o $(WIN32RES)

EXTENSION = pg_nanoid
DATA = pg_nanoid--1.0.0.sql pg_nanoid--unpackaged--1.0.0.sql

ifdef USE_PGXS
PG_CONFIG = pg_config
PGXS := $(shell $(PG_CONFIG) --pgxs)
include $(PGXS)
else
subdir = contrib/pg_nanoid
top_builddir = ../..
include $(top_builddir)/src/Makefile.global
include $(top_srcdir)/contrib/contrib-global.mk
endif
