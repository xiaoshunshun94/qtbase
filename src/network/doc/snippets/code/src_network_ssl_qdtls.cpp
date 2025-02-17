/****************************************************************************
**
** Copyright (C) 2018 The Qt Company Ltd.
** Contact: https://www.qt.io/licensing/
**
** This file is part of the documentation of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:BSD$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see https://www.qt.io/terms-conditions. For further
** information use the contact form at https://www.qt.io/contact-us.
**
** BSD License Usage
** Alternatively, you may use this file under the terms of the BSD license
** as follows:
**
** "Redistribution and use in source and binary forms, with or without
** modification, are permitted provided that the following conditions are
** met:
**   * Redistributions of source code must retain the above copyright
**     notice, this list of conditions and the following disclaimer.
**   * Redistributions in binary form must reproduce the above copyright
**     notice, this list of conditions and the following disclaimer in
**     the documentation and/or other materials provided with the
**     distribution.
**   * Neither the name of The Qt Company Ltd nor the names of its
**     contributors may be used to endorse or promote products derived
**     from this software without specific prior written permission.
**
**
** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
** "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
** LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
** A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
** OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
** SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
** LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
** DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
** THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
** (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
** OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE."
**
** $QT_END_LICENSE$
**
****************************************************************************/

using namespace Qt::StringLiterals;
//! [0]
// A client initiates a handshake:
QUdpSocket clientSocket;
QDtls clientDtls;
clientDtls.setPeer(address, port, peerName);
clientDtls.doHandshake(&clientSocket);

// A server accepting an incoming connection; address, port, clientHello are
// read by QUdpSocket::readDatagram():
QByteArray clientHello(serverSocket.pendingDatagramSize(), Qt::Uninitialized);
QHostAddress address;
quin16 port = {};
serverSocket.readDatagram(clientHello.data(), clientHello.size(), &address, &port);

QDtls serverDtls;
serverDtls.setPeer(address, port);
serverDtls.doHandshake(&serverSocket, clientHello);

// Handshake completion, both for server and client:
void DtlsConnection::continueHandshake(const QByteArray &datagram)
{
    if (dtls.doHandshake(&udpSocket, datagram)) {
        // Check handshake status:
        if (dtls.handshakeStatus() == QDlts::HandshakeComplete) {
            // Secure DTLS connection is now established.
        }
    } else {
        // Error handling.
    }
}

//! [0]

//! [1]
DtlsClient::DtlsClient()
{
    // Some initialization code here ...
    connect(&clientDtls, &QDtls::handshakeTimeout, this, &DtlsClient::handleTimeout);
}

void DtlsClient::handleTimeout()
{
    clientDtls.handleTimeout(&clientSocket);
}
//! [1]

//! [2]
// Sending an encrypted datagram:
dtlsConnection.writeDatagramEncrypted(&clientSocket, "Hello DTLS server!");

// Decryption:
QByteArray encryptedMessage(dgramSize);
socket.readDatagram(encryptedMessage.data(), dgramSize);
const QByteArray plainText = dtlsConnection.decryptDatagram(&socket, encryptedMessage);
//! [2]

//! [3]
DtlsClient::~DtlsClient()
{
    clientDtls.shutdown(&clientSocket);
}
//! [3]

//! [4]
auto config = QSslConfiguration::defaultDtlsConfiguration();
config.setDtlsCookieVerificationEnabled(false);
// Some other customization ...
dtlsConnection.setDtlsConfiguration(config);
//! [4]

//! [5]
if (!dtls.doHandshake(&socket, dgram)) {
    if (dtls.dtlsError() == QDtlsError::PeerVerificationError)
        dtls.abortAfterError(&socket);
}
//! [5]

//! [6]
QList<QSslCertificate> cert = QSslCertificate::fromPath("server-certificate.pem"_L1);
QSslError error(QSslError::SelfSignedCertificate, cert.at(0));
QList<QSslError> expectedSslErrors;
expectedSslErrors.append(error);

QDtls dtls;
dtls.ignoreVerificationErrors(expectedSslErrors);
dtls.doHandshake(udpSocket);
//! [6]

