#include <QtGui/QGuiApplication>
#include <QtQuick/qquickview.h>
#include <QtQml/QQmlEngine>
#include <QtQml/QQmlComponent>
#include <QtQml/QQmlContext>
#include "menumodel.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    QQmlEngine engine;
    QQmlComponent component(&engine);

    QQmlContext *ctxt = engine.rootContext();
    menumodel *m = new menumodel();
    ctxt->setContextProperty("backModel", m);

    component.loadUrl(QUrl("main.qml"));
    foreach (QQmlError s, component.errors()) {
        qDebug () << s.toString();
        return 1;
    }
    QObject *topLevel = component.create(ctxt);
    QQuickWindow *window = qobject_cast<QQuickWindow*>(topLevel);
    QObject::connect(&engine,SIGNAL(quit()),&app,SLOT(quit()) );
    window->show();

    return app.exec();
}
