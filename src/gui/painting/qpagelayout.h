/****************************************************************************
**
** Copyright (C) 2014 John Layt <jlayt@kde.org>
** Contact: https://www.qt.io/licensing/
**
** This file is part of the QtGui module of the Qt Toolkit.
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

#ifndef QPAGELAYOUT_H
#define QPAGELAYOUT_H

#include <QtGui/qtguiglobal.h>
#include <QtCore/qsharedpointer.h>
#include <QtCore/qstring.h>
#include <QtCore/qmargins.h>

#include <QtGui/qpagesize.h>

QT_BEGIN_NAMESPACE

class QPageLayoutPrivate;
class QMarginsF;

class Q_GUI_EXPORT QPageLayout
{
public:

    // NOTE: Must keep in sync with QPageSize::Unit and QPrinter::Unit
    enum Unit {
        Millimeter,
        Point,
        Inch,
        Pica,
        Didot,
        Cicero
    };

    enum Orientation {
        Portrait,
        Landscape
    };

    enum Mode {
        StandardMode,  // Paint Rect includes margins
        FullPageMode   // Paint Rect excludes margins
    };

    QPageLayout();
    QPageLayout(const QPageSize &pageSize, Orientation orientation,
                const QMarginsF &margins, Unit units = Point,
                const QMarginsF &minMargins = QMarginsF(0, 0, 0, 0));
    QPageLayout(const QPageLayout &other);
    QT_MOVE_ASSIGNMENT_OPERATOR_IMPL_VIA_PURE_SWAP(QPageLayout)
    QPageLayout &operator=(const QPageLayout &other);
    ~QPageLayout();

    void swap(QPageLayout &other) noexcept { d.swap(other.d); }

    bool isEquivalentTo(const QPageLayout &other) const;

    bool isValid() const;

    void setMode(Mode mode);
    Mode mode() const;

    void setPageSize(const QPageSize &pageSize,
                     const QMarginsF &minMargins = QMarginsF(0, 0, 0, 0));
    QPageSize pageSize() const;

    void setOrientation(Orientation orientation);
    Orientation orientation() const;

    void setUnits(Unit units);
    Unit units() const;

    bool setMargins(const QMarginsF &margins);
    bool setLeftMargin(qreal leftMargin);
    bool setRightMargin(qreal rightMargin);
    bool setTopMargin(qreal topMargin);
    bool setBottomMargin(qreal bottomMargin);

    QMarginsF margins() const;
    QMarginsF margins(Unit units) const;
    QMargins marginsPoints() const;
    QMargins marginsPixels(int resolution) const;

    void setMinimumMargins(const QMarginsF &minMargins);
    QMarginsF minimumMargins() const;
    QMarginsF maximumMargins() const;

    QRectF fullRect() const;
    QRectF fullRect(Unit units) const;
    QRect fullRectPoints() const;
    QRect fullRectPixels(int resolution) const;

    QRectF paintRect() const;
    QRectF paintRect(Unit units) const;
    QRect paintRectPoints() const;
    QRect paintRectPixels(int resolution) const;

private:
    friend class QPageLayoutPrivate;
    bool equals(const QPageLayout &other) const;

    friend inline bool operator==(const QPageLayout &lhs, const QPageLayout &rhs)
    { return lhs.equals(rhs); }
    friend inline bool operator!=(const QPageLayout &lhs, const QPageLayout &rhs)
    { return !lhs.equals(rhs); }

    QExplicitlySharedDataPointer<QPageLayoutPrivate> d;
};

Q_DECLARE_SHARED(QPageLayout)

#ifndef QT_NO_DEBUG_STREAM
Q_GUI_EXPORT QDebug operator<<(QDebug dbg, const QPageLayout &pageLayout);
#endif

QT_END_NAMESPACE

QT_DECL_METATYPE_EXTERN(QPageLayout, Q_GUI_EXPORT)
QT_DECL_METATYPE_EXTERN_TAGGED(QPageLayout::Unit, QPageLayout__Unit, Q_GUI_EXPORT)
QT_DECL_METATYPE_EXTERN_TAGGED(QPageLayout::Orientation, QPageLayout__Orientation, Q_GUI_EXPORT)

#endif // QPAGELAYOUT_H
