#!/bin/sh
#
# buildrpm.sh
# Copyright (c) Markus Kohm, 2009
#

chmod -R u+w rpm
rm -r rpm
mkdir -p rpm/SPECS
mkdir -p rpm/SOURCES
mkdir -p rpm/SRPMS
mkdir -p rpm/RPMS
mkdir -p rpm/BUILD

version=`grep '^Version:' *.spec | ( read a v; echo $v )`
[ -z "$version" ] && echo "Cannot determine version" >2 && exit 1

cd rpm
tar xzf ../kfile_metadat-${version}.tar.gz || tar xzf ../kfile_metadat.tar.gz
[ -d kfile_metadat ] && mv kfile_metadat kfile_metadat-${version}
rm -f kfile_metadat-${version}/src/comag_meta.*
cp -L ../../../source/comag_meta.cpp \
    ../../../source/comag_meta.o \
    ../../../source/comag_meta.h \
    kfile_metadat-${version}/src \
    || ( echo "comag_meta.o or comag_meta.h not found" >&2 && exit 1 )
[ -f kfile_metadat-${version}/src/comag_meta.o ] && \
    touch kfile_metadat-${version}/src/comag_meta.o
chmod -R u+w kfile_metadat-${version}
find ./ -name .svn -type d -exec rm -r {} \;
tar czf SOURCES/kfile_metadat-${version}.tar.gz kfile_metadat-${version}

cd SPECS
ln -s ../../kfile_metadat.spec .
cd ..

rpmbuild -v -ba --clean ${SIGNRPM} \
    --define="_topdir ${PWD}" \
    ${PWD}/SPECS/kfile_metadat.spec

cd ..
find rpm/ -iname "*.rpm" -exec cp {} . \;
