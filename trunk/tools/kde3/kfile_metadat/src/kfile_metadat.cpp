/***************************************************************************
 *   Copyright (C) 2009 by Markus Kohm   *
 *   mkohm at users.berlios.de   *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 ***************************************************************************/


#include <config.h>
#include "kfile_metadat.h"
#include <comag_meta.h>
#include <fstream>
#include <sstream>

#include <kgenericfactory.h>
#include <qdatetime.h>
#include <qfile.h>
#include <qdatastream.h>
//#include <kio/global.h>

//#include <qfileinfo.h>
//#include <qdir.h>

typedef KGenericFactory<kfile_metadatPlugin> kfile_metadatFactory;

K_EXPORT_COMPONENT_FACTORY ( kfile_metadat, kfile_metadatFactory ( "kfile_metadat" ) )

kfile_metadatPlugin::kfile_metadatPlugin ( QObject *parent, const char *name,
        const QStringList &args )
        : KFilePlugin ( parent, name, args )
{
    //add the mimetype here - example:
    //KFileMimeTypeInfo* info = addMimeTypeInfo( "text/html" );
    KFileMimeTypeInfo* info = addMimeTypeInfo ( "application/x-comag" );

    // our new group
    KFileMimeTypeInfo::GroupInfo* group = 0L;
    group = addGroupInfo ( info, "Technical", i18n ( "Technical Details" ) );

    KFileMimeTypeInfo::ItemInfo* item;

    // our new items in the group
    item = addItemInfo ( group, "Title", i18n ( "Title" ), QVariant::String );
    item = addItemInfo ( group, "Title Type", i18n ( "Type of Title" ), QVariant::String );
#ifdef ENABLE_DATETIMETWOLINES
    item = addItemInfo ( group, "Start Time", i18n ( "Start Time" ), QVariant::Time );
    item = addItemInfo ( group, "Start Date", i18n ( "Start Date" ), QVariant::Date );
#else
    item = addItemInfo ( group, "Start Time", i18n ( "Recorded on" ), QVariant::DateTime );
#endif
    item = addItemInfo ( group, "Duration", i18n ( "Duration" ), QVariant::Time );
    item = addItemInfo ( group, "Packets", i18n ( "Packets" ), QVariant::UInt );
    item = addItemInfo ( group, "Service", i18n ( "Type of Service" ), QVariant::String );
    item = addItemInfo ( group, "PID", i18n ( "Programm-ID" ), QVariant::UInt );
    item = addItemInfo ( group, "Timer", i18n ( "Timer Number" ), QVariant::ULongLong );

}

bool kfile_metadatPlugin::readInfo ( KFileMetaInfo& info, uint what )
{
    bool readTech = false;
    // add your "calculations" here
    // if something goes wrong, "return false;"

    if ( what & ( KFileMetaInfo::Fastest |
                  KFileMetaInfo::DontCare |
                  KFileMetaInfo::TechnicalInfo ) )
        readTech = true;

    if ( info.path().isEmpty() ) // remote file cannot be handled
        return false;

    if ( readTech )
    {
        KFileMetaInfoGroup group = appendGroup ( info, "Technical" );
        char buffer[112];
        QFile qf ( info.path() );
        if ( ! qf.open ( IO_ReadOnly ) ||
                ( qf.readBlock ( buffer, 112 ) != 112 ) )
            return false; // File cannot be read --> no meta info
        qf.close();

        try
        {
            comag::meta m ( ( const unsigned char * ) buffer );

            appendItem ( group, "Title", QString ( m.gettitle() ) );
            appendItem ( group, "Title Type", ( m.gettitle_type() == comag::meta::TT_TRANSMISSION ) ?
                         i18n ( "Transmission" ) :
                         ( m.gettitle_type() == comag::meta::TT_STATION ) ?
                         i18n ( "Station" ) :
                         i18n ( "Unknown" ) );
#ifdef ENABLE_DATETIMETWOLINES
            appendItem ( group, "Start Time", QTime ( m.getstart_time().hour,
                         m.getstart_time().minute,
                         m.getstart_time().second ) );
            appendItem ( group, "Start Date", QDate ( m.getstart_date().year,
                         m.getstart_date().month,
                         m.getstart_date().day ) );
#else
            appendItem ( group, "Start Time", QDateTime ( QDate ( m.getstart_date().year,
                         m.getstart_date().month,
                         m.getstart_date().day ),
                         QTime ( m.getstart_time().hour,
                                 m.getstart_time().minute,
                                 m.getstart_time().second ) ) );
#endif
            appendItem ( group, "Duration", QTime ( m.getduration().hour,
                                                    m.getduration().minute,
                                                    m.getduration().second ) );
            appendItem ( group, "Packets", m.getpackets() );
            appendItem ( group, "Service", ( m.getservice() == comag::meta::S_RADIO ) ?
                         i18n ( "Radio" ) :
                         ( m.getservice() == comag::meta::S_TV ) ?
                         i18n ( "TV" ) : i18n ( "Unknown" ) );
            appendItem ( group, "PID", m.getpid() );
            appendItem ( group, "Timer", ( unsigned long long ) ( m.gettimer() ) );
        }
        catch ( ... )
        {
            return false; // Exceptions simply means: no meta info
        }
        // and finally display it!
        return true;
    }
    return false;
}

#include "kfile_metadat.moc"
