/****************************************************************************
**
** Copyright (C) 2016 The Qt Company Ltd.
** Contact: https://www.qt.io/licensing/
**
** This file is part of Qt Creator.
**
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see https://www.qt.io/terms-conditions. For further
** information use the contact form at https://www.qt.io/contact-us.
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU
** General Public License version 3 as published by the Free Software
** Foundation with exceptions as appearing in the file LICENSE.GPL3-EXCEPT
** included in the packaging of this file. Please review the following
** information to ensure the GNU General Public License requirements will
** be met: https://www.gnu.org/licenses/gpl-3.0.html.
**
****************************************************************************/

#pragma once

#include <QFile>
#include <QTextDocument>

#include <projectexplorer/projectexplorer.h>
#include <projectexplorer/projectnodes.h>
#include <projectexplorer/projecttree.h>
#include <projectexplorer/project.h>

#include "parsedtree.h"
#include "parseddatastorage.h"

namespace Asn1Acn {
namespace Internal {

class ProjectWatcher : public QObject
{
    Q_OBJECT
public:
    ProjectWatcher();

private slots:
    void onProjectAdded(ProjectExplorer::Project *project);
    void onProjectRemoved(ProjectExplorer::Project *project);

    void onFilesAdded(ProjectExplorer::FolderNode *folder,
                      const QList<ProjectExplorer::FileNode *> &newFiles);
    void onFilesRemoved(ProjectExplorer::FolderNode *folder,
                        const QList<ProjectExplorer::FileNode *> &staleFiles);

    void onFolderRemoved(ProjectExplorer::FolderNode *parentFolder,
                         const QList<ProjectExplorer::FolderNode *> &staleFolders);

private:
    Utils::FileNameList filterValidPaths(QList<ProjectExplorer::FileNode *> fileNodes);

    void processFiles(const Utils::FileNameList &filePaths) const;
    void tryRemoveFiles(const Utils::FileNameList &filePaths) const;

    std::unique_ptr<QTextDocument> textDocumentFromPath(const QString &fileName) const;

    ParsedDataStorage *m_storage;
    ParsedTree *m_tree;
};

} // namespace Internal
} // namespace Asn1Acn
