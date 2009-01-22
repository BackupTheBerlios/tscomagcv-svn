//
// comag_meta.h
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
#define _COMAG_META_H

#include <cstring>
#include <iostream>
#include <exception>

using namespace std;

namespace comag {

    class meta {

    public:

	class failure : public exception {

	public:
	    explicit failure(const string& __str) : _M_msg( __str ) { 
		_extended_valid = false;
	    };
	    virtual ~failure() throw() {};
	    virtual const char* what() const throw() { return _M_msg.data(); };
	    const unsigned char *extended_what() const throw() { 
		return _extended_valid ? _extended : NULL;
	    };
	    void extend(const unsigned char buffer[112]);

	private:
	    string _M_msg;
	    unsigned char _extended[112];
	    bool _extended_valid;
	};

	typedef struct {
	    unsigned short hour;
	    unsigned short minute;
	    unsigned short second;
	} time;
	
	typedef struct {
	    unsigned short year;
	    unsigned short month;
	    unsigned short day;
	    unsigned short wday;
	} date;

	typedef enum { TT_STATION = 2, TT_TRANSMISSION = 8 } enum_title;
	typedef enum { S_TV = 0, S_RADIO = 1 } enum_service;

	meta(void);
	meta(unsigned short title_type=TT_STATION,
	     std::string title=std::string(),
	     time *start_time=NULL,
	     date *start_date=NULL,
	     time *duration=NULL,
	     unsigned int packets=0,
	     unsigned int pid=0,
	     unsigned int timer=0,
	     unsigned short service=S_TV);
	meta(const meta &m);
	meta(const meta *m);
	meta(const unsigned char *buffer);
	meta(std::istream &s);

	void read(std::istream &s);
	void write(std::ostream &s);
	void reset(const unsigned char *buffer = NULL);// size of buffer has to be at least 112

	enum_title gettitle_type() { return title_type; }
	std::string gettitle() { return title; }
	time getstart_time() { return start_time; }
	date getstart_date() { return start_date; }
	time getduration() { return duration; }
	enum_service getservice() { return service; }
	unsigned int getpid() { return pid; }
	unsigned long gettimer() { return timer; }
	unsigned int getpackets() { return packets; }
	const unsigned char *data();

     private:
	unsigned char _data[112];
	enum_title title_type;
	std::string title;
	time start_time;
	date start_date;
	unsigned int packets;
	time duration;
	enum_service service;
	unsigned int pid;
	unsigned long timer;

	friend ostream& operator<< (ostream &os, meta &m);
    };

}

#endif
