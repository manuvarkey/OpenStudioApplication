/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) 2020-2023, OpenStudio Coalition and other contributors. All rights reserved.
*
*  Redistribution and use in source and binary forms, with or without modification, are permitted provided that the
*  following conditions are met:
*
*  (1) Redistributions of source code must retain the above copyright notice, this list of conditions and the following
*  disclaimer.
*
*  (2) Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following
*  disclaimer in the documentation and/or other materials provided with the distribution.
*
*  (3) Neither the name of the copyright holder nor the names of any contributors may be used to endorse or promote products
*  derived from this software without specific prior written permission from the respective party.
*
*  (4) Other than as required in clauses (1) and (2), distributions in any form of modifications or other derivative works
*  may not use the "OpenStudio" trademark, "OS", "os", or any other confusingly similar designation without specific prior
*  written permission from Alliance for Sustainable Energy, LLC.
*
*  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDER(S) AND ANY CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES,
*  INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
*  DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER(S), ANY CONTRIBUTORS, THE UNITED STATES GOVERNMENT, OR THE UNITED
*  STATES DEPARTMENT OF ENERGY, NOR ANY OF THEIR EMPLOYEES, BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
*  EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF
*  USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
*  STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF
*  ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
***********************************************************************************************************************/

#include "StartupMenu.hpp"
#include "OpenStudioApp.hpp"
#include <QMenu>

namespace openstudio {

StartupMenu::StartupMenu(QWidget* parent) : QMenuBar(parent) {

  // File menu
  m_fileMenu = new QMenu(tr("&File"), this);
  auto* newAction = new QAction(tr("&New"), this);
  newAction->setShortcut(QKeySequence(QKeySequence::New));
  auto* loadFileAction = new QAction(tr("&Open"), this);
  loadFileAction->setShortcut(QKeySequence(QKeySequence::Open));
  auto* exitAction = new QAction(tr("E&xit"), this);
  exitAction->setShortcut(QKeySequence(QKeySequence::Quit));

  auto* importMenu = new QMenu(tr("Import"), this);
  auto* action = new QAction(tr("IDF"), this);
  importMenu->addAction(action);
  connect(action, &QAction::triggered, this, &StartupMenu::importClicked, Qt::QueuedConnection);
  action = new QAction(tr("gbXML"), this);
  importMenu->addAction(action);
  connect(action, &QAction::triggered, this, &StartupMenu::importgbXMLClicked, Qt::QueuedConnection);
  action = new QAction(tr("SDD"), this);
  importMenu->addAction(action);
  connect(action, &QAction::triggered, this, &StartupMenu::importSDDClicked, Qt::QueuedConnection);
  action = new QAction(tr("IFC"), this);
  importMenu->addAction(action);
  connect(action, &QAction::triggered, this, &StartupMenu::importIFCClicked, Qt::QueuedConnection);

  connect(loadFileAction, &QAction::triggered, this, &StartupMenu::loadFileClicked, Qt::QueuedConnection);
  connect(newAction, &QAction::triggered, this, &StartupMenu::newClicked, Qt::QueuedConnection);
  connect(exitAction, &QAction::triggered, this, &StartupMenu::exitClicked, Qt::QueuedConnection);
  m_fileMenu->addAction(newAction);
  m_fileMenu->addAction(loadFileAction);
  m_fileMenu->addSeparator();
  m_fileMenu->addMenu(importMenu);
  m_fileMenu->addSeparator();
  m_fileMenu->addAction(exitAction);

  addMenu(m_fileMenu);

  // Help menu
  m_helpMenu = new QMenu(tr("&Help"), this);

  addMenu(m_helpMenu);

  auto* helpAction = new QAction(tr("OpenStudio &Help"), this);

  connect(helpAction, &QAction::triggered, this, &StartupMenu::helpClicked, Qt::QueuedConnection);
  m_helpMenu->addAction(helpAction);

  action = new QAction(tr("Check For &Update"), this);
  m_helpMenu->addAction(action);
  connect(action, &QAction::triggered, this, &StartupMenu::checkForUpdateClicked, Qt::QueuedConnection);

  action = new QAction(tr("Debug Webgl"), this);
  m_helpMenu->addAction(action);
  connect(action, &QAction::triggered, this, &StartupMenu::debugWebglClicked, Qt::QueuedConnection);

  action = new QAction(tr("&About"), this);
  m_helpMenu->addAction(action);
  connect(action, &QAction::triggered, this, &StartupMenu::aboutClicked, Qt::QueuedConnection);
}

}  // namespace openstudio
