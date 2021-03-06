//////////////////////////////////////////////////////////////////////////////
// Program Name: videoLookupInfoList.h
// Created     : Jul. 19, 2011
//
// Copyright (c) 2011 Robert McNamara <rmcnamara@mythtv.org>
//
// This library is free software; you can redistribute it and/or
// modify it under the terms of the GNU Lesser General Public
// License as published by the Free Software Foundation; either
// version 2.1 of the License, or at your option any later version of the LGPL.
//
// This library is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
// Lesser General Public License for more details.
//
// You should have received a copy of the GNU Lesser General Public
// License along with this library.  If not, see <http://www.gnu.org/licenses/>.
//
//////////////////////////////////////////////////////////////////////////////

#ifndef VIDEOLOOKUPINFOLIST_H_
#define VIDEOLOOKUPINFOLIST_H_

#include <QVariantList>

#include "serviceexp.h"
#include "datacontracthelper.h"

#include "videoLookupInfo.h"

namespace DTC
{

class SERVICE_PUBLIC VideoLookupList : public QObject
{
    Q_OBJECT
    Q_CLASSINFO( "version", "1.0" );

    // We need to know the type that will ultimately be contained in
    // any QVariantList or QVariantMap.  We do his by specifying
    // A Q_CLASSINFO entry with "<PropName>_type" as the key
    // and the type name as the value

    Q_CLASSINFO( "VideoLookups_type", "DTC::VideoLookup");

    Q_PROPERTY( int          Count          READ Count           WRITE setCount          )
    Q_PROPERTY( QDateTime    AsOf           READ AsOf            WRITE setAsOf           )
    Q_PROPERTY( QString      Version        READ Version         WRITE setVersion        )
    Q_PROPERTY( QString      ProtoVer       READ ProtoVer        WRITE setProtoVer       )

    Q_PROPERTY( QVariantList VideoLookups READ VideoLookups DESIGNABLE true )

    PROPERTYIMP       ( int         , Count           )
    PROPERTYIMP       ( QDateTime   , AsOf            )
    PROPERTYIMP       ( QString     , Version         )
    PROPERTYIMP       ( QString     , ProtoVer        )

    PROPERTYIMP_RO_REF( QVariantList, VideoLookups )

    public:

        static void InitializeCustomTypes()
        {
            qRegisterMetaType< VideoLookupList  >();
            qRegisterMetaType< VideoLookupList* >();

            VideoLookup::InitializeCustomTypes();
        }

    public:

        VideoLookupList(QObject *parent = 0)
            : QObject( parent ),
              m_Count         ( 0      )
        {
        }

        VideoLookupList( const VideoLookupList &src )
        {
            Copy( src );
        }

        void Copy( const VideoLookupList &src )
        {
            m_Count         = src.m_Count          ;
            m_AsOf          = src.m_AsOf           ;
            m_Version       = src.m_Version        ;
            m_ProtoVer      = src.m_ProtoVer       ;

            CopyListContents< VideoLookup >( this, m_VideoLookups, src.m_VideoLookups );
        }

        VideoLookup *AddNewVideoLookup()
        {
            // We must make sure the object added to the QVariantList has
            // a parent of 'this'

            VideoLookup *pObject = new VideoLookup( this );
            m_VideoLookups.append( QVariant::fromValue<QObject *>( pObject ));

            return pObject;
        }

};

} // namespace DTC

Q_DECLARE_METATYPE( DTC::VideoLookupList  )
Q_DECLARE_METATYPE( DTC::VideoLookupList* )

#endif
