#include <QObject>
#include <memory>
#include "apimanager.h"
#include "mainwindow.h"


ApiCaller::ApiCaller(QNetworkAccessManager* nam)
    :m_nam(nam),m_counter(0)
{}

void ApiCaller::addCall(int id, ApiCall* apiCall)
{
    std::pair<int,ApiCall*> entry(id,apiCall);
    //qDebug() << apiCall;
    m_apiMap.insert(entry);
}


void ApiCaller::removeCall(int id)
{
    std::unordered_map<int,ApiCall*>::const_iterator it = m_apiMap.find(id);

    /*for (std::unordered_map<int,ApiCall*>::const_iterator i = m_apiMap.begin(); i != m_apiMap.end() ; i++)
    {
        qDebug() << i->first << i->second;
    }*/

    if (it != m_apiMap.end())
        delete it->second;
    /*else
        qDebug() << "error";*/

    m_apiMap.erase(id);
}


int ApiCaller::generateId()
{
    return m_counter++;
}

QNetworkAccessManager* ApiCaller::getNAM()
{
    return this->m_nam;
}


void ApiCaller::call(QUrl url, QObject* source, const char* callback)
{
    int id(generateId());
    ApiCall* apiCall = new ApiCall(url, source, callback,id,this);
    addCall(id,apiCall);
    apiCall->get();
    //qDebug() << m_apiMap.size();
}




ApiCall::ApiCall(QUrl url, QObject* source, const char* callback, int id, ApiCaller* caller)
    :m_url(url),m_source(source),m_callback(callback),m_id(id),m_caller(caller)
{
}


void ApiCall::forwardReply()
{
    QObject::connect(this, SIGNAL(sendReply(QNetworkReply*)), m_source, m_callback);
    emit sendReply(this->m_reply);
    this->m_caller->removeCall(this->m_id);
    //qDebug() << m_reply->error();
}


void ApiCall::get()
{
    m_request.setUrl(m_url);
    m_reply = m_caller->getNAM()->get(m_request);
    QObject::connect(m_reply, SIGNAL(finished()), this, SLOT(forwardReply()));
}
