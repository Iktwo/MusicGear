#ifndef DOWNLOADER_H
#define DOWNLOADER_H

#include <QObject>
#include <QDateTime>
#include <QMap>
#include <QVariantMap>

//! Downloader class.

/*!
Downloader class provides functions to download files using http.
*/

class QNetworkReply;
class QNetworkAccessManager;
class Downloader : public QObject
{
    Q_OBJECT
public:
    explicit Downloader(QObject *parent = 0);
    ~Downloader();

    static QString DownloadUrl;

public slots:
    void downloadSong(const QString &name, const QString &url);
    void download(const QString &urlString);
    void search(const QString &term);
    void downloadFinished(QNetworkReply *reply);

signals:
    void songFound(const QString &title, const QString &group, const QString &length,
                    const QString &comment, const QString &code);

    void decodedUrl(const QString &code, const QString &url);
    void searchEnded();
    void songDownloaded(const QString &url);
    void serverError();
    void searchHasMoreResults(const QString &url);

private:
    QNetworkAccessManager *m_netAccess;
    QMap<QString, QString> m_subdirs;
    QVariantMap m_songsToDownload;
    QNetworkReply *m_nreply;

private slots:
    QString decodeHtml(const QString &html);
    void downloadProgressChanged(qint64 bytesReceived, qint64 bytesTotal);
};

#endif // DOWNLOADER_H
