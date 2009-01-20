## Makefile.am for folder file meta info plugin

INCLUDES = $(all_includes)

# these are the headers for your project
noinst_HEADERS   = kfile_metadat.h

kde_module_LTLIBRARIES = kfile_metadat.la

kfile_metadat_la_SOURCES = kfile_metadat.cpp
kfile_metadat_la_LDFLAGS = $(all_libraries) -module $(KDE_PLUGIN)
kfile_metadat_la_LIBADD = $(LIB_KIO) comag_meta.o

# let automoc handle all of the meta source files (moc)
METASOURCES = AUTO

services_DATA = kfile_metadat.desktop
servicesdir = $(kde_servicesdir)

mimeservice_DATA = x-comag.desktop
mimeservicedir = $(kde_mimedir)/application

messages: rc.cpp
	$(EXTRACTRC) `find . -name \*.ui -o -name \*.rc` > rc.cpp
	$(XGETTEXT) *.cpp -o $(podir)/kfile_metadat.pot
