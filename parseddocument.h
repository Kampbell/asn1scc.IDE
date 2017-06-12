/****************************************************************************
**
** Copyright (C) 2017 N7 Mobile sp. z o. o.
** Contact: http://n7mobile.com/Space
**
** This file is part of ASN.1/ACN Plugin for QtCreator.
**
** Plugin was developed under a programme and funded by
** European Space Agency.
**
** This Plugin is free software: you can redistribute it and/or modify
** it under the terms of the GNU General Public License as published by
** the Free Software Foundation, either version 3 of the License, or
** (at your option) any later version.
**
** This Plugin is distributed in the hope that it will be useful,
** but WITHOUT ANY WARRANTY; without even the implied warranty of
** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
** GNU General Public License for more details.
**
** You should have received a copy of the GNU General Public License
** along with this program.  If not, see <http://www.gnu.org/licenses/>.
**
****************************************************************************/

#pragma once

#include <QString>
#include <QList>

#include "data/modules.h"
#include "data/definitions.h"

#include "parsedtreenode.h"

namespace Asn1Acn {
namespace Internal {

class ParsedDocument
{
public:
    ParsedDocument();
    ParsedDocument(const QString &filePath, int revision, const QStringList &list);
    ParsedDocument(const QString &filePath,
                   int revision,
                   std::unique_ptr<Data::Modules> parsedData);

    int getRevision() const;
    void bindParsedTreeNode(ParsedTreeNode::ParsedTreeNodePtr node);

private:
    void bindParsedTreeNodeWithStubbedData(ParsedTreeNode::ParsedTreeNodePtr node);
    void bindParsedTreeNodeWithParsedData(ParsedTreeNode::ParsedTreeNodePtr node);

    QString m_filePath;
    int m_revision;

    // TODO: m_wordList is temporal, as single words are used as data stubs
    QStringList m_wordList;
    std::unique_ptr<Data::Modules> m_parsedData;
};

} // namespace Internal
} // namespace Asn1Acn
