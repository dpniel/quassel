#ifndef QMLUIACCOUNTMODEL_H_
#define QMLUIACCOUNTMODEL_H_

#include "coreaccountmodel.h"
#include "clientsettings.h"
#include "client.h"

#include <QSortFilterProxyModel>

class QmlUiAccountModel : public QSortFilterProxyModel
{
    Q_OBJECT

    Q_PROPERTY(int lastAccountId READ lastAccountId WRITE setAccountId NOTIFY lastAccountIdChanged)
    // QML ListModel
    Q_PROPERTY(int count READ count NOTIFY countChanged)

public:
    QmlUiAccountModel(QObject *parent = 0);

    enum {
        AccountIdRole = Qt::UserRole,
        AccountNameRole,
        HostnameRole,
        UserRole,
        PasswordRole,
        PortRole,
        UseSecureConnectionRole,
        // TODO: Proxy
    };

    // QAbstractListModel
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
    QHash<int, QByteArray>roleNames() const;
    // QML ListModel
    Q_INVOKABLE int count() { return rowCount(); }

Q_SIGNALS:
    void lastAccountIdChanged();
    void countChanged();

protected:

protected slots:

private:
    CoreAccountSettings settings;
    inline int lastAccountId() { return settings.lastAccount().toInt(); }
    void setAccountId(int accountId) {
        if (lastAccountId() == accountId)
            return;
        Client::coreConnection()->disconnectFromCore();
        Client::coreConnection()->connectToCore(accountId);
    }
};

#endif