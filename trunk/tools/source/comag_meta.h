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
 * @namespace comag
 * @brief namespace for COMAG PVR 2/100CI
 *
 * comag is a namespace used for the classes handling the data formats of 
 * the COMAG PVR 2/100CI.
 */
namespace comag {


/**
 * @class meta
 *
 * meta is a class which provides handling for the file ``meta.dat''.
 *
 * @author Markus Kohm
 * @since 0.1
 */
    class meta {

    public:

	/**
	 * @class failure
	 * @brief exception thown by class meta
	 *
	 * Some methods of class meta throws exceptions on error.
	 * The exception class is derived from the standard exceptions but
         * was extended by addional information.
	 *
	 * @author Markus Kohm
	 * @since 0.1
	 */
	class failure : public exception {

	public:
	    /**
	     * inherited constructor
	     *
	     * @param __str the reason for the exception.
	     */
	    explicit failure(const string& __str) : _M_msg( __str ) { 
		_extended_valid = false;
	    };
	    /**
	     * default virtual destructor
	     */
	    virtual ~failure() throw() {};
	    /**
	     * overloaded virtual method to ask for the reason of the exception
	     */
	    virtual const char* what() const throw() { return _M_msg.data(); };

	    /**
	     * Set up the extended information.
	     *
	     * @param buffer Currently the data of the ``meta.dat'' file 
	     *               intended to be used as extended information.
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
	    unsigned char _extended[112];///< To save the extended information.
	    bool _extended_valid;        ///< Is _extended valid?
	};

	/**
	 * The time at ``meta.dat'' is saved in hour, minute, and second.
	 * We use this type to represent it.
	 */
	typedef struct {
	    unsigned short hour;   ///< 0..23
	    unsigned short minute; ///< 0..59
	    unsigned short second; ///< 0..59
	} time;
	
        /**
	 * The date at ``meta.dat'' is represented in year, month, day, 
	 * and the day of the week. We use this type to represent it.
	 */
	typedef struct {
	    unsigned short year;  ///< with century e.g. 2009
	    unsigned short month; ///< 1..12
	    unsigned short day;   ///< 1..31
	    unsigned short wday;  ///< 0..6 (0 = Sun, 1 = Mon, ..., 6 = Sat)
	} date;

	/**
	 * @typedef enum_title
	 *
	 * The title at ``meta.dat'' may be either the name of a station or 
	 * the name of the transmission.
	 */
	typedef enum { 
	    TT_STATION = 2, ///< title is title of station or was set manual
	    TT_TRANSMISSION = 8 ///< title is title of transmission e.g. movie
	} enum_title;

	/**
	 * @typedef enum_service
	 *
	 * The service of a record may be either TV or RADIO.
	 */
	typedef enum { 
	    S_TV = 0, ///< record is a TV transmission e.g. a movie
	    S_RADIO = 1 ///< record is a RADIO transmission
	} enum_service;

	/********************************************************************
	 * Constructors: The meta information may be constructed from the 
	 * scratch, by copy, by buffer or by input stream.
	 ********************************************************************/

	/**
	 * Constructor: create new meta information with initial default 
	 *              values.
	 */
	meta(void);

	/**
	 * Constructor: Copy of another meta information by reference
	 *
	 * @param m  the meta information, that should be used for the new one
	 */
	meta(const meta &m);

	/**
	 * Constructor: Copy of another meta information by pointer
	 *
	 * @param m  pointer to the meta information, that should be used for 
	 *           the new one
	 */
	meta(const meta *m);
	
	/**
	 * Constructor: by many valid information.
	 *
	 * @param title_type has to be one of enum_title. Default is 
         *                   TT_STATION.
	 * @param title only the first 61 characters are used for the title.
	 * @param start_time A pointer to a time. If the pointer is NULL
	 *                   current GMT will be used.
	 * @param start_date A pointer to date. If the pointer is NULL
	 *                   current GMT will be used.
	 * @param duration   A pointer to a time. This is not realy a 
	 *                   %time but a duration: the duration of the stream.
	 *                   If the pointer is NULL, duration would be 0.
	 * @param packets    The number of Comag info packets at the whole 
	 *                   stream.
	 * @param pid        The ID of the recorded program.
	 * @param timer      The timer number used for the recording.
	 * @param service    A enum_service.
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
	 * @exception failure if the buffer data is not valid. The extended 
	 *                     information will be a copy of the first 
	 *                     112 bytes from buffer.
	 */
	meta(const unsigned char *buffer);

	/**
	 * Construction by stream
	 *
	 * @param s       Read the data binary from this standard input stream.
	 * @exception failure if the data is not valid. The extended
	 *                     information will be a copy of the first
	 *                     112 bytes from the stream.
	 * @exception istream::failure  may be thrown also, if read 
	 *                              errors occur.
	 */
	meta(std::istream &s);

	/**
	 * read meta information binary (raw) from a standard input stream.
	 *
	 * @param s       Read the data from this standard input stream.
	 * @exception failure if the data is not valid. The extended
	 *                     information will be a copy of the first
	 *                     112 bytes from the stream.
	 * @exception istream::failure  may be thrown also, if read 
	 *                              errors occur.
	 */	 
	void read(std::istream &s);

	/**
	 * write meta information binary (raw) to a standard output stream.
	 *
	 * @param s    The stream to write to.
	 * @exception ostream::failure  may be thrown also, if read 
	 *                              errors occur.
	 */	 
	void write(std::ostream &s);

	/**
	 * Set the meta information by the data of a buffer or to default 
	 * initial values.
	 *
	 * @param buffer pointer to a buffer of at least 112 byte or NULL. If
	 *               buffer is NULL, the meta information will be set to
	 *               initial default values.
	 * @exception failure if the data is not valid. The extended
	 *                     information will be a copy of the first
	 *                     112 bytes from the stream.
	 */
	void reset(const unsigned char *buffer = NULL);// size of buffer has to be at least 112

	enum_title gettitle_type() { return title_type; }///< get the title type
	std::string gettitle() { return title; }///< get the title of the record
	time getstart_time() { return start_time; }///< get the start time (UTC)
	date getstart_date() { return start_date; }///< get the start date (UTC)
	time getduration() { return duration; }///< get the duration of the record
	enum_service getservice() { return service; }///< get the recorded service type
	unsigned int getpid() { return pid; }///< get the program ID of the recorded transmission
	unsigned long gettimer() { return timer; }///< get the timer used for the record
	unsigned int getpackets() { return packets; }///< get the number of Comag info packets at the record

	/**
	 * Get a current snapshot of the raw data of the meta information.
	 * This is only valid at the time of call and may change at later usage
	 * of the method.
	 * @note This method will be also used internal. So if you need the
	 *       binary data unchanged, you should copy it immediately.
	 */
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

	/**
	 * @brief Output operator friend to std::ostream
	 *
	 * Output the meta information to the stream. The output will be 
	 * done in ascii mode. Use write to output the binary data of the 
	 * meta information.
	 *
	 * @param os the output stream to write to
	 * @param m  the meta information to be written
	 */
	friend ostream& operator<< (ostream &os, meta &m);
    };

}

#endif
