#include <QuickItemWithModel.h>

#include <QGuiApplication>
#include <QObject>
#include <QQuickWindow>
#include <QQuickView>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QQmlProperty>

#include <iostream>

/*
static QQuickWindow* FindItemByName(QList<QObject*> nodes, const QString& name)
{
    for(int i = 0; i < nodes.size(); i++){
        // search for node
        auto curObj = nodes.at(i);
        if (curObj != nullptr)
        {
            auto curObj = nodes.value(i);
            std::cout << "node idName: " << curObj->objectName().toStdString() << " name " << nodes.at(i)->objectName().toStdString() << std::endl;
            if (nodes.at(i)->objectName() == name){
                return dynamic_cast<QQuickWindow*>(nodes.at(i));
            }
            // search in children
            else if (nodes.at(i)->children().size() > 0){
                QQuickWindow* item = FindItemByName(nodes.at(i)->children(), name);
                if (item)
                    return item;
            }
        }
    }
    // not found
    return nullptr;
}
*/

static QQuickItem* FindItemByName(QList<QObject*> nodes, const QString& name)
{
    for(int i = 0; i < nodes.size(); i++){
        // search for node
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
    // not found
    return nullptr;
}

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;

    qmlRegisterType<QuickItemWithModel>("name.holyoak", 1, 0, "QuickItemWithModel");

    auto rootContext = engine.rootContext();
    QuickItemWithModel quickItem;

    quickItem.setTitle("New Menu");

    rootContext->setContextProperty("quickItem",
                                     &quickItem);

    /*
    // Works - but hack to get window
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    if (engine.rootObjects().isEmpty())
        return -1;

    QObject *topLevel = engine.rootObjects().value(0);
    QQuickWindow *window = qobject_cast<QQuickWindow *>(topLevel);
    */

    /* Doesn't work
    QQmlComponent component(&engine, "qrc:/main.qml");
    QObject* object = component.create();

    QObject* topLevel = object->findChild<QObject*>("mainWinId");
    QQuickWindow *window = qobject_cast<QQuickWindow *>(topLevel);
    */

    // Doesn't work name is empty
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    if (engine.rootObjects().isEmpty())
        return -1;
    auto window = FindItemByName(engine.rootObjects(), "MainWindow");

    /*
     * Does not work
    QQmlComponent component(&engine, "qrc:/main.qml");
    QObject* object = component.create();
    auto topLevel = QQmlProperty::read(object, "mainWinId");
    QQuickWindow *window = topLevel.to;
    */

    /*
    // Does not work TRY 5?
    QQuickView quickView(&engine, nullptr);
    quickView.setSource(QUrl("qrc:/main.qml"));
    auto* object = quickView.rootObject();
    auto mainWinObj = object->findChild<QObject *>("mainWinId");
    auto window = qobject_cast<QQuickWindow*>(mainWinObj);
    */

    // connect our QML signal to our C++ slot
    QObject::connect(window, SIGNAL(itemSelectionChanged(QString)),
                         &quickItem, SLOT(itemModelSelected(QString)));

    QObject::connect(&quickItem, SIGNAL(notificationText(QVariant)),
                     window, SLOT(setNotificationText(QVariant)));

    // TRY 5? quickView.show();
    return app.exec();
}
