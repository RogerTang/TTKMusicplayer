#ifndef MUSICDOWNLOADQUERYKWTHREAD_H
#define MUSICDOWNLOADQUERYKWTHREAD_H

/* =================================================
 * This file is part of the TTK Music Player project
 * Copyright (c) 2015 - 2017 Greedysky Studio
 * All rights reserved!
 * Redistribution and use of the source code or any derivative
 * works are strictly forbiden.
   =================================================*/

#include "musicdownloadkwinterface.h"
#include "musicdownloadquerythreadabstract.h"

/*! @brief The class to kuwo query download data from net.
 * @author Greedysky <greedysky@163.com>
 */
class MUSIC_NETWORK_EXPORT MusicDownLoadQueryKWThread : public MusicDownLoadQueryThreadAbstract,
                                                        private MusicDownLoadKWInterface
{
    Q_OBJECT
public:
    /*!
     * Object contsructor.
     */
    explicit MusicDownLoadQueryKWThread(QObject *parent = 0);

    /*!
     * Get class object name.
     */
    static QString getClassName();
    /*!
     * Start to search data from name and type.
     */
    virtual void startToSearch(QueryType type, const QString &text) override;

public Q_SLOTS:
    /*!
     * Download data from net finished.
     */
    virtual void downLoadFinished() override;

protected:
    /*!
     * Read mv info attribute from query results.
     */
    void readFromMusicMVInfoAttribute(MusicObject::MusicSongInformation *info, int bitrate,
                                      const QString &id, const QString &format);

};

#endif // MUSICDOWNLOADQUERYKWTHREAD_H
