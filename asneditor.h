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

#include <texteditor/texteditor.h>

#include "editor.h"

#include "asnoverviewmodel.h"

namespace Asn1Acn {
namespace Internal {

class AsnEditor : public TextEditor::BaseTextEditor
{
    Q_OBJECT

public:
    explicit AsnEditor();
};

class AsnEditorFactory : public TextEditor::TextEditorFactory
{
public:
    explicit AsnEditorFactory();
};

class AsnEditorWidget : public EditorWidget
{
    Q_OBJECT

public:
    explicit AsnEditorWidget();

    void finalizeInitialization() override;

    AsnOverviewModel *getOverviewModel() const;

protected:
    Link findLinkAt(const QTextCursor &,
                    bool resolveTarget = true,
                    bool inNextSplit = false) override;

private:
    void onAsnDocumentUpdated(const QTextDocument &document);

    AsnOverviewModel *m_model;
};

} // namespace Internal
} // namespace Asn1Acn
