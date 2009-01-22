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

/**
 * comag is a namespace used for the classes handling the data formats of 
 * the COMAG PVR 2/100CI.
 */
namespace comag {


/**
 * meta is a class which provides handling for the file ``meta.dat''.
 *
 * @author Markus Kohm
 * @since 0.1
 */
    class meta {

    public:

	/**
	 * Some methods of class meta throws exceptions on error.
	 * The exception class is derived from the standard exceptions but
         * was extended by addional information.
	 *
	 * @author Markus Kohm
	 * @since 0.1
	 */
	class failure : public exception {

	public:
	    explicit failure(const string& __str) : _M_msg( __str ) { 
		_extended_valid = false;
	    };
	    virtual ~failure() throw() {};
	    virtual const char* what() const throw() { return _M_msg.data(); };

	    /**
	     * Set up the extended information.
	     *
	     * @param  Currently the data of the ``meta.dat'' file intended
	     *         to be used as extended information.
	     */
	    void extend(const unsigned char buffer[112]);

	    /**
	     * Get the extended information.
	     *
	     * @returns NULL if the extended information is not valid 
             *          (was not set up), otherwise a 112 byte buffer
             *          with the extended information.
	     */
	    const unsigned char *extended_what() const throw() { 
		return _extended_valid ? _extended : NULL;
	    };

	private:
	    string _M_msg;
	    unsigned char _extended[112];// To save the extended information.
	    bool _extended_valid;        // Is _extended valid?
	};

	/**
	 * The time at ``meta.dat'' is saved in hour, minute, and second.
	 * We use this type to represent it.
	 */
	typedef struct {
	    unsigned short hour;   // 0..23
	    unsigned short minute; // 0..59
	    unsigned short second; // 0..59
	} time;
	
        /**
	 * The date at ``meta.dat'' is represented in year, month, day, 
	 * and the day of the week. We use this type to represent it.
	 */
	typedef struct {
	    unsigned short year;  // with century e.g. 2009
	    unsigned short month; // 1..12
	    unsigned short day;   // 1..31
	    unsigned short wday;  // 0..6 (0 = Sun, 1 = Mon, ..., 6 = Sat)
	} date;

	/**
	 * The title at ``meta.dat'' may be either the name of a station or 
	 * the name of the transmission.
	 */
	typedef enum { TT_STATION = 2, TT_TRANSMISSION = 8 } enum_title;

	/**
	 * The service of a record may be either TV or RADIO.
	 */
	typedef enum { S_TV = 0, S_RADIO = 1 } enum_service;

	/**
	 * Constructors: The meta information may be constructed from the 
	 * scratch, by copy, by buffer or by input stream.
	 */

	meta(void); // empty constructor
	meta(const meta &m); // copy constructor
	meta(const meta *m); // copy constructor
	
	/**
	 * Construction by many valid information.
	 *
	 * @param title_type has to be one of @ref enum_title. Default is 
         *                   TT_STATION.
	 * @param title only the first 61 characters are used for the title.
	 * @param start_time A pointer to a @ref time. If the pointer is NULL
	 *                   current GMT will be used.
	 * @param start_date A pointer to @ref date. If the pointer is NULL
	 *                   current GMT will be used.
	 * @param duration   A pointer to a @ref time. This is not realy a 
	 *                   time but a duration: the duration of the stream.
	 *                   If the pointer is NULL, duration would be 0.
	 * @param packets    The number of Comag info packets at the whole 
	 *                   stream.
	 * @param pid        The ID of the recorded program.
	 * @param timer      The timer number used for the recording.
	 * @param service    A @ref enum_service.
	 */
	meta(unsigned short title_type=TT_STATION,
	     std::string title=std::string(),
	     time *start_time=NULL,
	     date *start_date=NULL,
	     time *duration=NULL,
	     unsigned int packets=0,
	     unsigned int pid=0,
	     unsigned int timer=0,
	     unsigned short service=S_TV);

	/**
	 * Construction by buffer
	 *
	 * @param buffer   A pointer to at least 112 bytes with valid 
	 *                 ``meta.dat'' information. If the pointer is NULL
	 *                 you will get same result like from empty 
	 *                 constructor.
	 * @exceptions failure if the buffer data is not valid. The extended 
	 *                     information will be a copy of the first 
	 *                     112 bytes from buffer.
	 */
	meta(const unsigned char *buffer);

	/**
	 * Construction by stream
	 *
	 * @param s       Read the data from a standard input stream.
	 * @exceptions failure if the data is not valid. The extended
	 *                     information will be a copy of the first
	 *                     112 bytes from the stream.
	 *             io-exceptions may be thrown also.
	 */
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
