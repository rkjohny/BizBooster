/**
 * Author: Rezaul Karim
 * Email: rkjohny@gmail.com
 *
 * Copyright (C) 2017 Rezaul Karim (rkjohny@gmail.com) all rights reserved.
 *
 * The information contained here-in is the property of Rezaul Karim and is not to be
 * disclosed or used without prior written permission of Rezaul Karim. This copyright
 * extends to all media in which this information may be preserved including
 * magnetic storage, computer print-out or visual display.
 */

#ifndef CRUXDB_CONSTANT_H_PP
#define CRUXDB_CONSTANT_H_PP

#define WT_DBO

#define DBO_CONFIG_FILE_NAME "cruxdb.properties"
#define DB_HOST "db.host"
#define DB_NAME "db.name"
#define DB_USER_NAME "db.user.name"
#define DB_USER_PASSWORD "db.user.password"


#define NEXT_DM_VERSION_KEY "next.dm.version"


#define COLUMN_ID "id"
#define COLUMN_VERSION "version"
#define COLUMN_STATUS "status"
#define COLUMN_DATE_CREATED "date_created"
#define COLUMN_DATE_LAST_UPDATED "date_last_updated"
#define COLUMN_CREATED_BY "created_by"
#define COLUMN_LAST_UPDATED_BY "last_updated_by"


#define DEFAULT_LOG_IN_PROVIDER "loginname"

// 30 seconds
#define MAX_SESSION_MANAGER_THREAD_SLEEP_IN_SEC 30

// 30 minutes
#define DEFAULT_SESSION_TIME_OUT_IN_MSC (30 * 60 * 60)


#endif