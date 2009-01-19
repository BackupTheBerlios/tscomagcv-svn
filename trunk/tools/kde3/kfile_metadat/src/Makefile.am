## Makefile.am for folder file meta info plugin

INCLUDES = $(all_includes) -I$(top_srcdir)/../../source

# these are the headers for your project
noinst_HEADERS   = kfile_metadat.h

kde_module_LTLIBRARIES = kfile_metadat.la

kfile_metadat_la_SOURCES = kfile_metadat.cpp $(abs_top_sourcedir()/../source/.libs/comag_meta.o
kfile_metadat_la_LDFLAGS = $(all_libraries) -module $(KDE_PLUGIN)
kfile_metadat_la_LIBADD = $(LIB_KIO) $(top_srcdir)/../../source/comag_meta.o

# let automoc handle all of the meta source files (moc)
METASOURCES = AUTO

services_DATA = kfile_metadat.desktop
servicesdir = $(kde_servicesdir)

messages: rc.cpp
	$(EXTRACTRC) `find . -name \*.ui -o -name \*.rc` > rc.cpp
	$(XGETTEXT) *.cpp -o $(podir)/kfile_metadat.pot
