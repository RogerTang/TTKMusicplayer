#ifndef MUSICWEBMUSICRADIOLISTVIEW_H
#define MUSICWEBMUSICRADIOLISTVIEW_H

/* =================================================
 * This file is part of the TTK Music Player project
 * Copyright (c) 2015 - 2017 Greedysky Studio
 * All rights reserved!
 * Redistribution and use of the source code or any derivative
 * works are strictly forbiden.
   =================================================*/

#include <QListWidget>
#include "musicglobaldefine.h"

class QNetworkCookieJar;
class MusicRadioChannelThread;
class MusicWebMusicRadioWidget;

/*! @brief The class of the web music radio list widget.
 * @author Greedysky <greedysky@163.com>
 */
class MUSIC_TOOL_EXPORT MusicWebMusicRadioListView : public QListWidget
{
    Q_OBJECT
public:
    /*!
     * Object contsructor.
     */
    explicit MusicWebMusicRadioListView(QWidget *parent = 0);

    ~MusicWebMusicRadioListView();

    /*!
     * Get class object name.
     */
    static QString getClassName();
    /*!
     * To init list items.
     */
    void initListItems();

public Q_SLOTS:
    /*!
     * Radio list item has clicked.
     */
    void itemHasClicked(QListWidgetItem *item);
    /*!
     * Add radio list into list widget.
     */
    void addListWidgetItem();

protected:
    QNetworkCookieJar *m_cookJar;
    MusicRadioChannelThread *m_getChannelThread;
    MusicWebMusicRadioWidget *m_musicRadio;

};

#endif // MUSICWEBMUSICRADIOLISTVIEW_H
