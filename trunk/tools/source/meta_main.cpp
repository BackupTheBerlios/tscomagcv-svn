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
//
// NOTE: This is only intended to test the library!
//

#include <comag_meta.h>
#include <iostream>
#include <cstring>
#include <iomanip>

int main( int argc, char** argv ) {
    bool bin = false;
    int retval = 0;
    comag::meta *md = NULL;
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

    try {
	md=new comag::meta(cin);
    }
    catch( comag::meta::failure e ) {
	cerr << "Failure processing input meta information: " << e.what() 
	     << endl;
	if ( e.extended_what() != NULL ) {
	    for ( int i = 0; i < 112; i += 16 ) {
		cerr << hex << setfill('0') << right << setw(2) << i << ":  ";
		for ( int j = 0; j < 16; j++ ) {
		    if ( j == 8 )
			cerr << " ";
		    cerr << hex << setfill('0') << right << setw(2)
			 << (int)(e.extended_what()[i+j])
			 << " ";
		}
		cerr << " |";
		for ( int j = 0; j < 16; j++ ) {
		    char b[2];
		    b[0] = ( ( e.extended_what()[i+j] < 31 ) ||
			     ( e.extended_what()[i+j] > 127 ) ) ? '.' 
			:(char)( e.extended_what()[i+j] );
		    b[1] = 0;
		    cerr << b;
		}
		cerr << "|" << endl;
	    }
	}
	retval = 1;
    }
    catch( istream::failure e ) {
	cerr << "Failure reading input stream: " << e.what() << endl;
    }
    if ( md ) {
	try {
	    if ( bin )
		md->write( cout );
	    else {
		cout << "meta.dat informations:" << endl;
		cout << *md;
	    }
	}
	catch( comag::meta::failure e ) {
	    cerr << "Failure processing output meta information: " << e.what() 
		 << endl;
	    retval = 1;
	}
	catch( ostream::failure e ) {
	    cerr << "Failure writing output stream: " << e.what() << endl;
	}
	delete md;
    }
    return retval;
}
