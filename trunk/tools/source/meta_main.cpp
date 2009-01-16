//
// meta_main.cpp
// Copyright (c) Markus Kohm, 2009
//
// This program is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation; version 2 of the License.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program; if not, write to the Free Software
// Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
//


#include <comag_meta.h>
#include <iostream>
#include <cstring>

int main( int argc, char** argv ) {
    bool bin = false;
    for ( int i = 1; i < argc; i++ ) {
	if ( !strcmp( argv[i], "-a" ) || 
	     !strcmp( argv[i], "--ascii" ) ) {
	    bin=false;
	} else if ( !strcmp( argv[i], "-b" ) || 
		    !strcmp( argv[i], "--binary" ) ) {
	    bin=true;
	} else if ( !strcmp( argv[i], "-h" ) ||
		    !strcmp( argv[i], "--help" ) ) {
	    cout << "Usage: " << argv[0] 
		 << "[-a|--ascii] [-b|--binary] [-h|--help] < meta.dat" 
		 << endl;
	    cout << " -a|--ascii  write the meta.dat information in ascii mode to stdout"
		 << endl
		 << " -b|--bin    write the meta.dat information in bin mode to stdout"
		 << endl;
	    return 0;;
	}
    }

    comag::meta md(cin);
    if ( bin )
	md.write( cout );
    else {
	cout << "meta.dat informations:" << endl;
	cout << md;
    }
    return 0;
}
