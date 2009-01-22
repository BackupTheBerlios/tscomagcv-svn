//
// comag_meta.cpp
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

#ifndef _COMAG_META_H
#include "comag_meta.h"
#endif

#include <ctime>
#include <cstring>
#include <iomanip>

namespace comag {

    void meta::failure::extend(const unsigned char buffer[112]) {
	memcpy( _extended, buffer, 112);
	_extended_valid = true;
    };

    void meta::reset(const unsigned char *buffer /* = NULL */) {
	if ( buffer == NULL ) {
	    memset( _data, 0, 112 );
	    memcpy(_data, "\x05\x00\x72\x6a\x07", 5);
	    _data[0x64] = 0x01;
	    time_t rawtime;
	    std::time( &rawtime );
	    tm *t = std::gmtime( &rawtime );
	    title_type = TT_STATION;
	    start_time.hour   = t->tm_hour;
	    start_time.minute = t->tm_min;
	    start_time.second = t->tm_sec;
	    start_date.year   = t->tm_year + 1900;
	    start_date.month  = t->tm_mon + 1;
	    start_date.day    = t->tm_mday;
	    start_date.wday   = t->tm_wday;
	    duration.hour     = 0;
	    duration.minute   = 0;
	    duration.second   = 0;
	    packets = 0;
	    service = S_TV;
	    pid = 0;
	    timer = 0L;
	} else {
	    memcpy( _data, buffer, 112 );
	    if ( memcmp( buffer,"\x05\x00\x72\x6a\x07\x00\x00\x00\x00\x00\x00\x00", 
			 12 ) ||
		 buffer[0x4e] || 
		 buffer[0x55] || buffer[0x56] || buffer[0x57] ||
		 buffer[0x5f] ||
		 buffer[0x61] || buffer[0x62] || buffer[0x63] ||
		 ( buffer[0x64] != 0x01 ) ||
		 buffer[0x65] || buffer[0x66] || buffer[0x67] ||
		 buffer[0x6a] || buffer[0x6b]
		) {
		failure e( "Header or reserved bytes not valid" );
		e.extend( _data );
		throw e;
	    }
	    switch( buffer[12] ) {
		case TT_TRANSMISSION:
		    title_type = TT_TRANSMISSION;
		    break;
		case TT_STATION:
		    title_type = TT_STATION;
		    break;
		default:
		    failure e( "Station type is neither TRANSMISSION nor STATION" );
		    e.extend( _data );
		    throw e;
	    }
	    title = std::string( (char *)(buffer + 0x0d), 62 );
	    if ( ( ( start_time.hour   = buffer[0x4b] ) > 24 ) ||
		 ( ( start_time.minute = buffer[0x4c] ) > 59 ) ||
		 ( ( start_time.second = buffer[0x4d] ) > 60 ) ) {
		failure e( "Start time not valid" );
		e.extend( _data );
		throw e;
	    }
	    if ( ( ( start_date.year = buffer[0x50] | (buffer[0x51] << 8) ) < 1900 ) ||
		 ( start_date.year > 9999 ) ||
		 ( ( start_date.month = buffer[0x52] ) < 1 ) ||
		 ( start_date.month > 12 ) ||
		 ( ( start_date.day = buffer[0x53] ) < 1 ) ||
		 ( start_date.day > 31 ) ||
		 ( ( start_date.wday = buffer[0x54] ) > 6 ) ) {
		failure e( "Start date not valid" );
		e.extend( _data );
		throw e;
	    }
	    packets = buffer[0x58] | (buffer[0x59] << 8) | 
		(buffer[0x5a] << 16) | (buffer[0x5b] << 24);
	    if ( ( ( duration.hour   = buffer[0x5c] ) > 24 ) ||
		 ( ( duration.minute = buffer[0x5d] ) > 59 ) ||
		 ( ( duration.second = buffer[0x5e] ) > 60 ) ) {
		failure e( "Start time not valid" );
		e.extend( _data );
		throw e;
	    }
	    switch( buffer[0x60] ) {
		case S_TV:
		    service = S_TV;
		    break;
		case S_RADIO:
		    service = S_RADIO;
		    break;
		default:
		    failure e( "Service is neither TV nor RADIO" );
		    e.extend( _data );
		    throw e;
	    }
	    pid = buffer[0x68] | (buffer[0x69] << 8);
	    timer = buffer[0x6c] | (buffer[0x6d] << 8) | 
		(buffer[0x6e] << 16) | (buffer[0x6f] << 24);
	}	    
    }
    
    meta::meta(
	unsigned short title_type,
	std::string title,
	time *start_time,
	date *start_date,
	time *duration,
	unsigned int packets,
	unsigned int pid,
	unsigned int timer,
	unsigned short service
	) 
    {
	reset();
	this->title_type = ( title_type == TT_TRANSMISSION ) ? TT_TRANSMISSION : TT_STATION;
	this->title = title;
	if ( start_time ) {
	    this->start_time.hour = start_time->hour;
	    this->start_time.minute = start_time->minute;
	    this->start_time.second = start_time->second;
	}
	if ( start_date ) {
	    this->start_date.year = start_date->year;
	    this->start_date.month = start_date->month;
	    this->start_date.day = start_date->day;
	    this->start_date.wday = start_date->wday;
	}
	if ( duration ) {
	    this->duration.hour = duration->hour;
	    this->duration.minute = duration->minute;
	    this->duration.second = duration->second;
	}
	this->packets = packets;
	this->service = ( service == S_RADIO ) ? S_RADIO : S_TV;
	this->pid     = pid;
	this->timer   = timer;
    }
    
    meta::meta(void) {
	reset();
    }
    
    meta::meta(const meta *m) {
        memcpy( _data, m->_data, 112 );
	title_type        = m->title_type;
	start_time.hour   = m->start_time.hour;
	start_time.minute = m->start_time.minute;
	start_time.second = m->start_time.second;
	start_date.year   = m->start_date.year;
	start_date.month  = m->start_date.month;
	start_date.day    = m->start_date.day;
	start_date.wday   = m->start_date.wday;
	duration.hour     = m->duration.hour;
	duration.minute   = m->duration.minute;
	duration.second   = m->duration.second;
	packets           = m->packets;
	service           = m->service;
	pid               = m->pid;
	timer             = m->timer;
    }
    
    meta::meta(const meta &m) {
        memcpy( _data, m._data, 112 );
	title_type        = m.title_type;
	start_time.hour   = m.start_time.hour;
	start_time.minute = m.start_time.minute;
	start_time.second = m.start_time.second;
	start_date.year   = m.start_date.year;
	start_date.month  = m.start_date.month;
	start_date.day    = m.start_date.day;
	start_date.wday   = m.start_date.wday;
	duration.hour     = m.duration.hour;
	duration.minute   = m.duration.minute;
	duration.second   = m.duration.second;
	packets           = m.packets;
	service           = m.service;
	pid               = m.pid;
	timer             = m.timer;
    }

    meta::meta(std::istream &s) {
	reset();
	read(s);
    };

    const unsigned char * meta::data(void) {
	_data[12] = title_type;
	strncpy( (char *)_data + 0x0d, title.data(), 62 );
	_data[0x4b] = start_time.hour;
	_data[0x4c] = start_time.minute;
	_data[0x4d] = start_time.second;
	_data[0x50] = start_date.year & 0xff;
	_data[0x51] = (start_date.year >> 8) & 0xff;
	_data[0x52] = start_date.month;
	_data[0x53] = start_date.day;
	_data[0x54] = start_date.wday;
	_data[0x58] = packets & 0xff;
	_data[0x59] = (packets >> 8) & 0xff;
	_data[0x5a] = (packets >> 16) & 0xff;
	_data[0x5b] = (packets >> 24) & 0xff;
	_data[0x5c] = duration.hour;
	_data[0x5d] = duration.minute;
	_data[0x5e] = duration.second;
	_data[0x60] = service;
	_data[0x68] = pid & 0xff;
	_data[0x69] = ( pid >> 8 ) & 0xff;
	_data[0x6c] = timer & 0xff;
	_data[0x6d] = ( timer >> 8 ) & 0xff;
	_data[0x6e] = ( timer >> 16 ) & 0xff;
	_data[0x6f] = ( timer >> 24 ) & 0xff;
	return _data;
    }

    void meta::write(std::ostream &o) {
        data(); // update the data buffer
	o.exceptions( std::ostream::eofbit |
		      std::ostream::failbit |
		  std::ostream::badbit ); // throw every problem
	o.write( (const char *)_data, 112 );
    }
    
    meta::meta(const unsigned char *buffer) {
	reset( buffer );
    }

    void meta::read(std::istream &s) {
	unsigned char buffer[112];
	s.exceptions( std::istream::eofbit | 
		      std::istream::failbit | 
		      std::istream::badbit ); // Throw every problem
	s.read( (char *)buffer, 112 );
	reset( buffer );
    }
    
    ostream& operator<< (ostream &os, meta &m) {
	const char *dayof[7] = { "Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat" };
	return os << left << setw(20) << "title_type: "
		  << ( ( m.gettitle_type() == meta::TT_TRANSMISSION ) ? 
		       "transmission" : "sender" ) 
		  << " (0x" << hex << setfill('0') << right << setw(2) << (int)m.gettitle_type() << ")\n"
		  << left << setw(20) << setfill(' ') << "title:" << setw(0) << m.gettitle() << "\n"
		  << left << setw(20) << setfill(' ') <<  "start_time:"
		  << dec << setfill('0') << right << setw(2) << m.getstart_time().hour
		  << setw(1) << ":"
		  << setw(2) << m.getstart_time().minute
		  << setw(1) << ":"
		  << setw(2) << m.getstart_time().second << endl
		  << left << setw(20) << setfill(' ') <<  "start_date:"
		  << setw(4) << dayof[m.getstart_date().wday]
		  << right << setw(4) << setfill('0') << m.getstart_date().year
		  << setw(1) << "-"
		  << setw(2) << m.getstart_date().month
		  << setw(1) << "-"
		  << setw(2) << m.getstart_date().day << endl
		  << left << setw(20) << setfill(' ') <<  "duration:"
		  << dec << setfill('0') << right << setw(2) << m.getduration().hour
		  << setw(1) << ":"
		  << setw(2) << m.getduration().minute
		  << setw(1) << ":"
		  << setw(2) << m.getduration().second << endl
		  << left << setw(20) << setfill(' ') <<  "comag packets:"
		  << setw(0) << m.getpackets()
		  << endl
		  << left << setw(20) << setfill(' ') <<  "service:"
		  << setw(0) << ( ( m.getservice() == meta::S_TV ) ? 
				  "TV" : "Radio" ) 
		  << " (0x" << hex << right << setw(2) << setfill('0') << m.getservice() << ")\n"
		  << left << setw(20) << setfill(' ') <<  "Program-ID:"
		  << dec << setw(0) << m.getpid()
		  << " (0x" << hex << right << setw(4) << setfill('0' ) << m.getpid() << ")\n"
		  << left << setw(20) << setfill(' ') <<  "timer:"
		  << dec << setw(0) << m.gettimer()
		  << endl;
    }
}
