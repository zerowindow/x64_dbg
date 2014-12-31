#ifndef UPDATECHECKER_H
#define UPDATECHECKER_H

#include <QNetworkAccessManager>

class UpdateChecker : public QNetworkAccessManager
{
    Q_OBJECT
public:
    UpdateChecker(QWidget* parent);
    void checkForUpdates();

private slots:
    void finishedSlot(QNetworkReply* reply);

private:
    QWidget* mParent;

};

#endif // UPDATECHECKER_H
