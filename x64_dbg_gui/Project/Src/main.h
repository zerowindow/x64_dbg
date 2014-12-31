#ifndef MAIN_H
#define MAIN_H

#include <QApplication>
#include <QAbstractEventDispatcher>
#include <QMessageBox>
#include "Bridge.h"
#include "Configuration.h"
#include "MainWindow.h"
#if QT_VERSION >= QT_VERSION_CHECK(5,0,0)
#include <QAbstractNativeEventFilter>
#endif

class MyApplication : public QApplication
{
public:
    MyApplication(int & argc, char** argv);
    bool notify(QObject* receiver, QEvent* event);
    bool winEventFilter(MSG* message, long* result);
#if QT_VERSION < QT_VERSION_CHECK(5,0,0)
    static bool globalEventFilter(void* message);
#endif
};

int main(int argc, char* argv[]);

#if QT_VERSION >= QT_VERSION_CHECK(5,0,0)
class x64GlobalFilter : public QAbstractNativeEventFilter
{
public:
    virtual bool nativeEventFilter(const QByteArray &, void* message, long*) Q_DECL_OVERRIDE
    {
        return DbgWinEventGlobal((MSG*)message);
    }
};
#endif // QT_VERSION

#endif // MAIN_H
