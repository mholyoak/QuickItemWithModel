#include <QuickItemWithModel.h>

#include <QGuiApplication>
#include <QObject>
#include <QQuickWindow>
#include <QQuickView>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QQmlProperty>

#include <iostream>

static QQuickItem* FindItemByName(QList<QObject*> nodes, const QString& name)
{
    for(int i = 0; i < nodes.size(); i++){
        auto curObj = nodes.at(i);
        if (curObj != nullptr)
        {
            if (curObj->objectName() == name)
            {
                return dynamic_cast<QQuickItem*>(curObj);
            }

            auto foundObj = curObj->findChild<QQuickItem*>(name);
            if (foundObj)
            {
                return foundObj;
            }
        }
    }

    return nullptr;
}

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;

    auto rootContext = engine.rootContext();
    QuickItemWithModel quickItem;

    quickItem.setTitle("New Menu");

    rootContext->setContextProperty("quickItem",
                                     &quickItem);

    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    if (engine.rootObjects().isEmpty())
        return -1;
    auto window = FindItemByName(engine.rootObjects(), "MainWindow");

    // connect our QML signal to our C++ slot
    QObject::connect(window, SIGNAL(itemSelectionChanged(QString)),
                         &quickItem, SLOT(itemModelSelected(QString)));

    QObject::connect(&quickItem, SIGNAL(notificationText(QVariant)),
                     window, SLOT(setNotificationText(QVariant)));

    return app.exec();
}
