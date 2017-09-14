#ifndef QNPUTPOLICY_H
#define QNPUTPOLICY_H

/* =================================================
 * This file is part of the TTK Music Player project
 * Copyright (c) 2015 - 2017 Greedysky Studio
 * All rights reserved!
 * Redistribution and use of the source code or any derivative
 * works are strictly forbiden.
   =================================================*/

#include <QObject>
#include "musicprivate.h"
#include "musicextrasglobaldefine.h"

class QNMac;
class QNPutPolicyPrivate;

/*! @brief The namespace of the qiniu policy.
 * @author Jemy Graw <jemygraw@gmail.com>
 */
class MUSIC_EXTRAS_EXPORT QNPutPolicy
{
public:
    /*!
     * Object contsructor.
     */
    QNPutPolicy(const QString &scope);

    /*!
     * Transfer data to json.
     */
    QByteArray toJSON(bool compact = true);
    /*!
     * Make uplaod token.
     */
    QString makeUploadToken(const QNMac *mac = 0);
    /*!
     * Make download token.
     */
    QString makeDownloadToken(const QNMac *mac = 0);

    /*!
     * Get scope.
     */
    QString getScope() const;
    /*!
     * Set scope.
     */
    void setScope(const QString &value);

    /*!
     * Get deadline.
     */
    qint32 getDeadline() const;
    /*!
     * Set deadline.
     */
    void setDeadline(qint32 value);

    /*!
     * Get insert only.
     */
    quint16 getInsertOnly() const;
    /*!
     * Set insert only.
     */
    void setInsertOnly(quint16 value);

    /*!
     * Get save key.
     */
    QString getSaveKey() const;
    /*!
     * Set save key.
     */
    void setSaveKey(const QString &value);

    /*!
     * Get end user.
     */
    QString getEndUser() const;
    /*!
     * Set end user.
     */
    void setEndUser(const QString &value);

    /*!
     * Get file size limit.
     */
    qint32 getFSizeLimit() const;
    /*!
     * Set file size limit.
     */
    void setFSizeLimit(qint32 value);

    /*!
     * Get detect mime.
     */
    qint16 getDetectMime() const;
    /*!
     * Set detect mime.
     */
    void setDetectMime(qint16 value);

    /*!
     * Get mime limit.
     */
    QString getMimeLimit() const;
    /*!
     * Set mime limit.
     */
    void setMimeLimit(const QString &value);

    /*!
     * Get call back url.
     */
    QString getCallbackUrl() const;
    /*!
     * Set call back url.
     */
    void setCallbackUrl(const QString &value);

    /*!
     * Get call back host.
     */
    QString getCallbackHost() const;
    /*!
     * Set call back host.
     */
    void setCallbackHost(const QString &value);

    /*!
     * Get call back body.
     */
    QString getCallbackBody() const;
    /*!
     * Set call back body.
     */
    void setCallbackBody(const QString &value);

    /*!
     * Get call back fetch key.
     */
    qint16 getCallbackFetchKey() const;
    /*!
     * Set call back fetch key.
     */
    void setCallbackFetchKey(qint16 value);

    /*!
     * Get return url.
     */
    QString getReturnUrl() const;
    /*!
     * Set return url.
     */
    void setReturnUrl(const QString &value);

    /*!
     * Get return body.
     */
    QString getReturnBody() const;
    /*!
     * Set return body.
     */
    void setReturnBody(const QString &value);

    /*!
     * Get persistent ops.
     */
    QString getPersistentOps() const;
    /*!
     * Set persistent ops.
     */
    void setPersistentOps(const QString &value);

    /*!
     * Get persistent notify url.
     */
    QString getPersistentNotifyUrl() const;
    /*!
     * Set persistent notify url.
     */
    void setPersistentNotifyUrl(const QString &value);

    /*!
     * Get persistent pipe line.
     */
    QString getPersistentPipeline() const;
    /*!
     * Set persistent pipe line.
     */
    void setPersistentPipeline(const QString &value);


private:
    TTK_DECLARE_PRIVATE(QNPutPolicy)

};

#endif // QNPUTPOLICY_H
