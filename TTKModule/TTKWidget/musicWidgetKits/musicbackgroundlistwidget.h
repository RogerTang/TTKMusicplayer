#ifndef MUSICBACKGROUNDLISTWIDGET_H
#define MUSICBACKGROUNDLISTWIDGET_H

/* =================================================
 * This file is part of the TTK Music Player project
 * Copyright (c) 2015 - 2017 Greedysky Studio
 * All rights reserved!
 * Redistribution and use of the source code or any derivative
 * works are strictly forbiden.
   =================================================*/

#include <QLabel>
#include <QGridLayout>
#include "musicuiobject.h"
#include "musicbackgroundconfigmanager.h"

#define CURRENT_ITEMS_COUNT         47

/*! @brief The class of the background list item.
 * @author Greedysky <greedysky@163.com>
 */
class MUSIC_WIDGET_EXPORT MusicBackgroundListItem : public QLabel
{
    Q_OBJECT
public:
    /*!
     * Object contsructor.
     */
    explicit MusicBackgroundListItem(QWidget *parent = 0);

    /*!
     * Get class object name.
     */
    static QString getClassName();

    /*!
     * Set item file name.
     */
    inline void setFileName(const QString &name) { m_name = name; }
    /*!
     * Get item file name.
     */
    inline QString getFileName() const { return m_name; }
    /*!
     * Set item file name.
     */
    inline void setFilePath(const QString &path) { m_path = path; }
    /*!
     * Get item file name.
     */
    inline QString getFilePath() const { return m_path; }

    /*!
     * Update pix image.
     */
    void updatePixImage();
    /*!
     * Update pix image.
     */
    void updatePixImage(const MusicBackgroundImage &image);
    /*!
     * Current item contains or not.
     */
    bool contains(const MusicSkinConfigItem &item) const;

    /*!
     * Select the current item.
     */
    void setSelect(bool s);
    /*!
     * Get current selected item state.
     */
    inline bool isSelect() const { return m_isSelected; }

    /*!
     * Select the current item enable or not.
     */
    void setSelectEnable(bool s);
    /*!
     * Get current selected item state.
     */
    inline bool isSelectEnable() const { return m_selectedMask; }

    /*!
     * Close option set the current item.
     */
    void setCloseEnable(bool s);
    /*!
     * Get close option set the current item.
     */
    inline bool isCloseEnable() const { return m_closeSet; }

    /*!
     * Show title name set the current item.
     */
    void setShowNameEnable(bool s);
    /*!
     * Get show title name set the current item.
     */
    inline bool isShowNameEnable() const { return m_showNameMask; }

Q_SIGNALS:
    /*!
     * Current item close clicked.
     */
    void closeClicked(MusicBackgroundListItem *item);
    /*!
     * Current item clicked.
     */
    void itemClicked(MusicBackgroundListItem *item);

protected:
    /*!
     * Override the widget event.
     */
    virtual void mousePressEvent(QMouseEvent *event) override;
    virtual void leaveEvent(QEvent *event) override;
    virtual void enterEvent(QEvent *event) override;
    virtual void paintEvent(QPaintEvent *event) override;

    bool m_printMask, m_isSelected, m_selectedMask;
    bool m_closeMask, m_closeSet, m_showNameMask;
    QString m_name, m_path;
    MusicSkinConfigItem m_imageInfo;

};


/*! @brief The class of the background list widget.
 * @author Greedysky <greedysky@163.com>
 */
class MUSIC_WIDGET_EXPORT MusicBackgroundListWidget : public QWidget
{
    Q_OBJECT
public:
    /*!
     * Object contsructor.
     */
    explicit MusicBackgroundListWidget(QWidget *parent = 0);

    ~MusicBackgroundListWidget();

    /*!
     * Get class object name.
     */
    static QString getClassName();

    /*!
     * Select current item by name when the widget show.
     */
    void setCurrentItemName(const QString &name);

    /*!
     * Clear select state.
     */
    void clearSelectState();
    /*!
     * Clear All Items.
     */
    void clearAllItems();

    /*!
     * Create item by name and path.
     */
    void createItem(const QString &name, const QString &path, bool state);
    /*!
     * Create item by icon.
     */
    void createItem(const QString &icon, bool state);
    /*!
     * Update item by backgroud image.
     */
    void updateItem(const MusicBackgroundImage &image, const QString &path);

    /*!
     * Current item contains or not.
     */
    bool contains(const QString &name) const;
    /*!
     * Current item contains or not.
     */
    bool contains(const MusicBackgroundImage &image) const;

    /*!
     * Current item index at container.
     */
    int find(MusicBackgroundListItem *item) const;
    /*!
     * Find item by name.
     */
    MusicBackgroundListItem* find(const QString &name) const;
    /*!
     * Find item by image.
     */
    MusicBackgroundListItem* find(const MusicBackgroundImage &image) const;

    /*!
     * Update lasted item state.
     */
    void updateLastedItem();

    /*!
     * Item count.
     */
    inline int count() const { return m_items.count(); }

Q_SIGNALS:
    /*!
     * Current item clicked.
     */
    void itemClicked(const QString &name);

private Q_SLOTS:
    /*!
     * Current item close clicked.
     */
    void itemCloseClicked(MusicBackgroundListItem *item);
    /*!
     * Current item has clicked.
     */
    void itemHasClicked(MusicBackgroundListItem *item);

protected:
    QGridLayout *m_layout;
    MusicBackgroundListItem *m_currentItem;
    QList<MusicBackgroundListItem*> m_items;

};

#endif // MUSICBACKGROUNDLISTWIDGET_H
