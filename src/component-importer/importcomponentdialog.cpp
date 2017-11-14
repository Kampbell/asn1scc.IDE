/****************************************************************************
**
** Copyright (C) 2017 N7 Mobile sp. z o. o.
** Contact: http://n7mobile.pl/Space
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

#include "importcomponentdialog.h"

#include <QWidget>
#include <QDir>

#include <coreplugin/icore.h>

#include <utils/qtcassert.h>

#include <projectexplorer/session.h>
#include <projectexplorer/project.h>
#include <projectexplorer/projectnodes.h>

using namespace Asn1Acn::Internal::ComponentImporter;

ImportComponentDialog::ImportComponentDialog(QWidget *parent)
    : QDialog(parent)
    , m_libraries(Settings::load<Settings::Libraries>())
{
    m_ui.setupUi(this);

    setAttribute(Qt::WA_DeleteOnClose);
    connect(Core::ICore::instance(), &Core::ICore::coreAboutToClose, this, &QWidget::close);

    connect(m_libraries.get(), &Settings::Libraries::changed, this, &ImportComponentDialog::refreshPaths);
    connect(m_ui.builtInRadio, &QRadioButton::toggled, this, &ImportComponentDialog::builtInRadioToggled);

    connect(m_ui.buttonBox, &QDialogButtonBox::accepted, this, &ImportComponentDialog::accept);
    connect(m_ui.buttonBox, &QDialogButtonBox::rejected, this, &QDialog::reject);

    m_ui.builtInRadio->setChecked(true);
}

void ImportComponentDialog::refreshPaths()
{
    if (!m_ui.builtInRadio->isChecked())
        return;

    m_ui.builtInCombo->clear();

    const auto detectedPaths = m_libraries->detectedLibPaths();
    const auto manualPaths = m_libraries->manualLibPaths();

    m_ui.builtInCombo->addItems(detectedPaths);
    m_ui.builtInCombo->addItems(manualPaths);
}

void ImportComponentDialog::builtInRadioToggled(bool checked)
{
    if (checked)
        refreshPaths();
    else
        m_ui.builtInCombo->clear();
}

void ImportComponentDialog::accept()
{
    if (m_ui.builtInRadio->isChecked())
        addFilesFromDirectory(m_ui.builtInCombo->currentText());
    else if (m_ui.customRadio->isChecked())
        addFilesFromDirectory(m_ui.asn1sccPathChooser->path());

    QDialog::accept();
}

void ImportComponentDialog::addFilesFromDirectory(const QString &directoryPath)
{
    const auto paths = pathsInDirectory(directoryPath);
    addPathsToProject(paths);
}

QStringList ImportComponentDialog::pathsInDirectory(const QString &directoryPath)
{
    QDir dir(directoryPath);
    QTC_ASSERT(dir.exists() == true, return {});

    QStringList filters;
    filters << "*.asn" << "*.asn1" << "*.acn";
    dir.setNameFilters(filters);

    const auto names = dir.entryList();

    QStringList paths;
    for (const auto &name : names)
        paths << dir.filePath(name);

    return paths;
}

void ImportComponentDialog::addPathsToProject(const QStringList &paths)
{
    const auto project = ProjectExplorer::SessionManager::startupProject();
    if (project == nullptr)
        return;

    project->rootProjectNode()->addFiles(paths);
}

