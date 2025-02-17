/****************************************************************************
**
** Copyright (C) 2014 Governikus GmbH & Co. KG.
** Contact: https://www.qt.io/licensing/
**
** This file is part of the QtNetwork module of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:LGPL$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see https://www.qt.io/terms-conditions. For further
** information use the contact form at https://www.qt.io/contact-us.
**
** GNU Lesser General Public License Usage
** Alternatively, this file may be used under the terms of the GNU Lesser
** General Public License version 3 as published by the Free Software
** Foundation and appearing in the file LICENSE.LGPL3 included in the
** packaging of this file. Please review the following information to
** ensure the GNU Lesser General Public License version 3 requirements
** will be met: https://www.gnu.org/licenses/lgpl-3.0.html.
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU
** General Public License version 2.0 or (at your option) the GNU General
** Public license version 3 or any later version approved by the KDE Free
** Qt Foundation. The licenses are as published by the Free Software
** Foundation and appearing in the file LICENSE.GPL2 and LICENSE.GPL3
** included in the packaging of this file. Please review the following
** information to ensure the GNU General Public License requirements will
** be met: https://www.gnu.org/licenses/gpl-2.0.html and
** https://www.gnu.org/licenses/gpl-3.0.html.
**
** $QT_END_LICENSE$
**
****************************************************************************/

#ifndef QSSLPRESHAREDKEYAUTHENTICATOR_H
#define QSSLPRESHAREDKEYAUTHENTICATOR_H

#include <QtNetwork/qtnetworkglobal.h>
#include <QtCore/QString>
#include <QtCore/QSharedDataPointer>
#include <QtCore/QMetaType>

QT_REQUIRE_CONFIG(ssl);

QT_BEGIN_NAMESPACE

class QSslPreSharedKeyAuthenticatorPrivate;
class QSslPreSharedKeyAuthenticator
{
public:
    Q_NETWORK_EXPORT QSslPreSharedKeyAuthenticator();
    Q_NETWORK_EXPORT ~QSslPreSharedKeyAuthenticator();
    Q_NETWORK_EXPORT QSslPreSharedKeyAuthenticator(const QSslPreSharedKeyAuthenticator &authenticator);
    Q_NETWORK_EXPORT QSslPreSharedKeyAuthenticator &operator=(const QSslPreSharedKeyAuthenticator &authenticator);

    QSslPreSharedKeyAuthenticator &operator=(QSslPreSharedKeyAuthenticator &&other) noexcept { swap(other); return *this; }

    void swap(QSslPreSharedKeyAuthenticator &other) noexcept { d.swap(other.d); }

    Q_NETWORK_EXPORT QByteArray identityHint() const;

    Q_NETWORK_EXPORT void setIdentity(const QByteArray &identity);
    Q_NETWORK_EXPORT QByteArray identity() const;
    Q_NETWORK_EXPORT int maximumIdentityLength() const;

    Q_NETWORK_EXPORT void setPreSharedKey(const QByteArray &preSharedKey);
    Q_NETWORK_EXPORT QByteArray preSharedKey() const;
    Q_NETWORK_EXPORT int maximumPreSharedKeyLength() const;

private:
    Q_NETWORK_EXPORT bool isEqual(const QSslPreSharedKeyAuthenticator &other) const;

    friend class QTlsBackend;

    friend bool operator==(const QSslPreSharedKeyAuthenticator &lhs, const QSslPreSharedKeyAuthenticator &rhs)
    { return lhs.isEqual(rhs); }
    friend bool operator!=(const QSslPreSharedKeyAuthenticator &lhs, const QSslPreSharedKeyAuthenticator &rhs)
    { return !lhs.isEqual(rhs); }

    QSharedDataPointer<QSslPreSharedKeyAuthenticatorPrivate> d;
};


Q_DECLARE_SHARED(QSslPreSharedKeyAuthenticator)

QT_END_NAMESPACE

QT_DECL_METATYPE_EXTERN(QSslPreSharedKeyAuthenticator, Q_NETWORK_EXPORT)
QT_DECL_METATYPE_EXTERN_TAGGED(QSslPreSharedKeyAuthenticator*, QSslPreSharedKeyAuthenticator_ptr, Q_NETWORK_EXPORT)

#endif // QSSLPRESHAREDKEYAUTHENTICATOR_H
