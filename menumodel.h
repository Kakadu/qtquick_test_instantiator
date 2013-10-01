#ifndef MENUMODEL_H
#define MENUMODEL_H

#include <QObject>
#include <QtCore/QAbstractItemModel>
#include <QDebug>

class menumodel : public QAbstractItemModel
{
    Q_OBJECT
    QVector<QString> _items;
    QHash<int, QByteArray> _roles;

public:
    explicit menumodel();

    Q_INVOKABLE void drop(int n) {
        qDebug() << _items;
        beginRemoveRows(QModelIndex(), 0, n-1);
        for (int i=0; i<n; i++)
            _items.pop_front();
        endRemoveRows();
        qDebug() << _items;
    }
    Q_INVOKABLE void add(QString s) {
        beginInsertRows(QModelIndex(), 0, 0);
        _items.push_front(s);
        endInsertRows();
        qDebug() << "added " << s << "to model";
    }

    int rowCount(const QModelIndex & ) const {
        return _items.count();
    }

    virtual QHash<int, QByteArray> roleNames() const { return _roles; }
    virtual int columnCount(const QModelIndex &) const {
        return 1;
    }
    virtual bool hasChildren(const QModelIndex &) const {
        return rowCount(QModelIndex()) > 0;
    }
    virtual QModelIndex index(int row, int column, const QModelIndex &parent) const {
        Q_UNUSED(column);
        if (row>=0 && row<rowCount(parent))
            return createIndex(row,0);
        else
            return QModelIndex();
    }
    virtual QModelIndex parent(const QModelIndex &) const {
        return QModelIndex();
    }
    QVariant data (const QModelIndex & index, int role) const {
        int r = index.row();
        if ((r<0) || (r>=_items.count()))
            return QVariant::Invalid;

        switch (role) {
        case Qt::DisplayRole:
        case 555:
            return QVariant::fromValue(_items.at(r) );
        default:
            return QVariant();
        }
    }
signals:

public slots:

};

#endif // MENUMODEL_H
