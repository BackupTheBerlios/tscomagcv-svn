# This spec file was generated by KDevelop 
# Please report any problem to KDevelop Team <kdevelop-devel@kdevelop.org> 
# Thanks to Matthias Saou for his explanations on http://freshrpms.net/docs/fight.html

Name: kfile_metadat
Version: 0.1
Release: 2
Vendor: KOMA
License: GPL
Summary: comag meta.dat KFile Plugin
Group: System/GUI/KDE
Packager: Markus Kohm
BuildRoot:  %{_tmppath}/%{name}-buildroot 
Source: %{name}-%{version}.tar.gz

%description
This is a early BETA of a KFile plugin for KDE 3.
For meta.dat files from COMAG PVR2/100CI it extends the file information
menu of e.g. Konqueror with the meta infos from the file.

%prep
%setup

%build
WANT_AUTOCONF_2_5="1" WANT_AUTOMAKE_1_6="1" LC_MESSAGES="C" LC_TYPE="C" gmake -f Makefile.cvs
./configure
make

%install
rm -rf %{buildroot}
%makeinstall

%clean
rm -rf %{buildroot}

%post -p /sbin/ldconfig
%postun -p /sbin/ldconfig
%files
%defattr(-, root, root)
%doc AUTHORS COPYING ChangeLog NEWS README TODO
/opt/kde3/lib/kde3/kfile_metadat*
/opt/kde3/share/doc/HTML/en/kfile_metadat/
/opt/kde3/share/locale/*/LC_MESSAGES/kfile_metadat.mo
/opt/kde3/share/services/kfile_metadat.desktop
/opt/kde3/share/mimelnk/application/x-comag.desktop

%changelog
* Tue Jan 20 2009 Markus Kohm <mjk at users.berlios.de>
- Fixed: x-coma.desktop missing
