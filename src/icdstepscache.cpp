/****************************************************************************
**
** Copyright (C) 2018 N7 Space sp. z o. o.
** Contact: http://n7space.com
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

#include "icdstepscache.h"

#include <projectexplorer/project.h>
#include <projectexplorer/session.h>

#include "buildicdstep.h"

using namespace Asn1Acn::Internal;

ICDStepsCache::ICDStepsCache(QObject *parent)
    : QObject(parent)
{
    connect(ProjectExplorer::SessionManager::instance(),
            &ProjectExplorer::SessionManager::aboutToRemoveProject,
            this,
            &ICDStepsCache::onAboutToRemoveProject);
}

void ICDStepsCache::add(const QString &id, BuildICDStep *step)
{
    m_steps.insert(id, step);
}

BuildICDStep *ICDStepsCache::get(const QString &id) const
{
    return m_steps.contains(id) ? m_steps.value(id) : nullptr;
}

void ICDStepsCache::onAboutToRemoveProject(ProjectExplorer::Project *p)
{
    m_steps.remove(p->displayName());
}
