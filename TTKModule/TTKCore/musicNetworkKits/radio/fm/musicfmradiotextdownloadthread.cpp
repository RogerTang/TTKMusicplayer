#include "musicfmradiotextdownloadthread.h"
#///QJson import
#include "qjson/parser.h"

MusicFMRadioTextDownLoadThread::MusicFMRadioTextDownLoadThread(const QString &url, const QString &save, MusicObject::DownloadType  type, QObject *parent)
    : MusicDownLoadThreadAbstract(url, save, type, parent)
{

}

void MusicFMRadioTextDownLoadThread::startToDownload()
{
    if(m_file && (!m_file->exists() || m_file->size() < 4))
    {
        if(m_file->open(QIODevice::WriteOnly | QIODevice::Truncate | QIODevice::Text))
        {
            m_timer.start(MT_S2MS);
            m_manager = new QNetworkAccessManager(this);

            QNetworkRequest request;
            request.setUrl(m_url);
#ifndef QT_NO_SSL
            connect(m_manager, SIGNAL(sslErrors(QNetworkReply*,QList<QSslError>)), SLOT(sslErrors(QNetworkReply*,QList<QSslError>)));
            MusicObject::setSslConfiguration(&request);
#endif
            m_reply = m_manager->get(request);
            connect(m_reply, SIGNAL(finished()), SLOT(downLoadFinished()));
            connect(m_reply, SIGNAL(error(QNetworkReply::NetworkError)), SLOT(replyError(QNetworkReply::NetworkError)));
            connect(m_reply, SIGNAL(downloadProgress(qint64, qint64)), SLOT(downloadProgress(qint64, qint64)));
        }
        else
        {
            Q_EMIT downLoadDataChanged("The fm radio text file create failed");
            TTK_LOGGER_ERROR(QString("%1 file create failed!").arg(getClassName()));
            deleteAll();
        }
    }
}

void MusicFMRadioTextDownLoadThread::downLoadFinished()
{
    if(!m_reply || !m_file)
    {
        deleteAll();
        return;
    }
    m_timer.stop();

    if(m_reply->error() == QNetworkReply::NoError)
    {
        QByteArray bytes = m_reply->readAll();
        QJson::Parser parser;
        bool ok;
        const QVariant &data = parser.parse(bytes, &ok);
        if(ok)
        {
            QByteArray lrcData;
            QVariantMap value = data.toMap();
            if(value.contains("lyric"))
            {
                lrcData = value["lyric"].toByteArray();
            }

            QTextStream outstream(m_file);
            outstream.setCodec("utf-8");
            outstream << lrcData << endl;
            m_file->close();
            TTK_LOGGER_INFO(QString("%1 download has finished!").arg(getClassName()));
        }
        else
        {
            TTK_LOGGER_ERROR(QString("%1 download file error!").arg(getClassName()));
            m_file->remove();
            m_file->close();
        }
    }

    Q_EMIT downLoadDataChanged(transferData());
    deleteAll();
}
