#ifndef QUICKITEMWITHMODEL_H
#define QUICKITEMWITHMODEL_H

#include <QAbstractListModel>
#include <QQuickItem>

class ItemModel :  public QAbstractListModel {
    Q_OBJECT
public:
    explicit ItemModel(QObject *parent=nullptr);
    ItemModel(ItemModel&& /* unused */) = delete;
    ItemModel& operator=(ItemModel&& /* unused */) = delete;
    ~ItemModel() override = default;

    // Methods used by QML to get model attributes
    QHash<int, QByteArray> roleNames() const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;

    enum class Role : int {
        ItemModelRole = Qt::UserRole + 1
    };

private:
    Q_DISABLE_COPY(ItemModel)
};


class QuickItemWithModel : public QQuickItem
{
    Q_OBJECT

    Q_PROPERTY(QString title READ title CONSTANT)
    Q_PROPERTY(ItemModel* itemModel READ itemModel NOTIFY itemModelChanged)

    QString title_;
    ItemModel itemModel_;

public:
    explicit QuickItemWithModel(QQuickItem *parent = nullptr);
    virtual ~QuickItemWithModel() = default;

    QString title() const;
    ItemModel* itemModel();

    void setTitle(const QString& newTitle);

signals:
    void itemModelChanged();
    void notificationText(QVariant notifyText);

public slots:
    void itemModelSelected(QString itemName);

private:
};


#endif // QUICKITEMWITHMODEL_H
