#include "musickgartistsimilarrequest.h"
#include "musickgqueryinterface.h"

MusicKGArtistSimilarRequest::MusicKGArtistSimilarRequest(QObject *parent)
    : MusicSimilarRequest(parent)
{

}

void MusicKGArtistSimilarRequest::startToSearch(const QString &text)
{
    if(!m_manager)
    {
        return;
    }

    TTK_LOGGER_INFO(QString("%1 startToSearch %2").arg(getClassName()).arg(text));
    deleteAll();

    const QUrl &musicUrl = MusicUtils::Algorithm::mdII(KG_ARTIST_SIMILAR_URL, false).arg(text);
    m_interrupt = true;

    QNetworkRequest request;
    request.setUrl(musicUrl);
    request.setRawHeader("User-Agent", MusicUtils::Algorithm::mdII(KG_UA_URL, ALG_UA_KEY, false).toUtf8());
    MusicObject::setSslConfiguration(&request);

    m_reply = m_manager->get(request);
    connect(m_reply, SIGNAL(finished()), SLOT(downLoadFinished()));
    connect(m_reply, SIGNAL(error(QNetworkReply::NetworkError)), SLOT(replyError(QNetworkReply::NetworkError)));
}

void MusicKGArtistSimilarRequest::downLoadFinished()
{
    if(!m_reply || !m_manager)
    {
        deleteAll();
        return;
    }

    TTK_LOGGER_INFO(QString("%1 downLoadFinished").arg(getClassName()));
    m_interrupt = false;

    if(m_reply->error() == QNetworkReply::NoError)
    {
        const QString html(m_reply->readAll());
        QRegExp regx("class=\"pic\" onclick=.*_src=\"([^\"]+).*href=\"(.*)\">(.*)</a></strong>");
        regx.setMinimal(true);

        int pos = html.indexOf(regx);
        while(pos != -1)
        {
            if(m_interrupt) return;

            MusicResultsItem info;
            QRegExp idrx("/(\\d+)");
            if(regx.cap(2).indexOf(idrx) != -1)
            {
                info.m_id = idrx.cap(1);
            }
            info.m_coverUrl = regx.cap(1);
            info.m_name = regx.cap(3);
            info.m_updateTime.clear();
            Q_EMIT createSimilarItem(info);

            pos += regx.matchedLength();
            pos = regx.indexIn(html, pos);
        }
    }

    Q_EMIT downLoadDataChanged(QString());
    deleteAll();
}
