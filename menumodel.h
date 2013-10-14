#ifndef MENUMODEL_H
#define MENUMODEL_H

#include <QObject>
#include <QtCore/QAbstractItemModel>
#include <QDebug>

class menumodel;

extern menumodel* backmodel;
extern menumodel* forwardmodel;

class menumodel : public QAbstractItemModel
{
    Q_OBJECT
    QVector<QString> _items;
    QHash<int, QByteArray> _roles;
    QString _name;
public:
    explicit menumodel(QString);

    /* concats [reverse(v)] end [_items] */
    void addItems(QVector<QString> &v) {
        beginInsertRows(QModelIndex(), 0, v.count()-1);
        foreach (const QString& s, v) {
            _items.push_front(s);
        }
        endInsertRows();
    }

    Q_INVOKABLE void drop(int n) {
        menumodel* dest = (this == backmodel) ? forwardmodel : backmodel;
        QVector<QString> ans;
        qDebug() << _items;
        beginRemoveRows(QModelIndex(), 0, n-1); // doesn't work
        for (int i=0; i<n; i++) {
            ans.push_back(_items.at(0));
            _items.pop_front();
        }
        endRemoveRows();
        qDebug() << _items;

        dest->addItems(ans);
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
