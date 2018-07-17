#ifndef APIMANAGER_H
#define APIMANAGER_H

#include <QObject>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <unordered_map>

class ApiCall;

class ApiCaller
{
public:
    ApiCaller(QNetworkAccessManager* nam);
    void addCall(int id, ApiCall* apiCall);
    void removeCall(int id);
    void call(QUrl url, QObject* source, const char* callback);
    int generateId();
    QNetworkAccessManager* getNAM();

private:
    std::unordered_map<int,ApiCall*> m_apiMap;
    int m_counter;
    QNetworkAccessManager* m_nam;
};


class ApiCall : public QObject
{
    Q_OBJECT
public:
    ApiCall(QUrl url,QObject* source,const char* callback, int id, ApiCaller* caller);
    void get();

signals:
    void sendReply(QNetworkReply* reply);

public slots:
    void forwardReply();

private:
    ApiCaller* m_caller;
    int m_id;
    QUrl m_url;
    QNetworkRequest m_request;
    QNetworkReply* m_reply;
    QObject* m_source;
    const char* m_callback;

};

#endif // APIMANAGER_H
