#ifndef MUSICDOWNLOADQUERYBDALBUMTHREAD_H
#define MUSICDOWNLOADQUERYBDALBUMTHREAD_H

/* =================================================
 * This file is part of the TTK Music Player project
 * Copyright (c) 2015 - 2017 Greedysky Studio
 * All rights reserved!
 * Redistribution and use of the source code or any derivative
 * works are strictly forbiden.
   =================================================*/

#include "musicdownloadbdinterface.h"
#include "musicdownloadquerythreadabstract.h"

/*! @brief The class to baidu query album download data from net.
 * @author Greedysky <greedysky@163.com>
 */
class MUSIC_NETWORK_EXPORT MusicDownLoadQueryBDAlbumThread : public MusicDownLoadQueryThreadAbstract,
                                                             private MusicDownLoadBDInterface
{
    Q_OBJECT
public:
    /*!
     * Object contsructor.
     */
    explicit MusicDownLoadQueryBDAlbumThread(QObject *parent = 0);

    /*!
     * Get class object name.
     */
    static QString getClassName();

    /*!
     * Start to Search data from name and type.
     */
    virtual void startToSearch(QueryType type, const QString &album) override;
    /*!
     * Start to Search data from name and type.
     */
    void startToSearch(const QString &album);

public Q_SLOTS:
    /*!
     * Download data from net finished.
     */
    virtual void downLoadFinished() override;

};

#endif // MUSICDOWNLOADQUERYBDALBUMTHREAD_H
