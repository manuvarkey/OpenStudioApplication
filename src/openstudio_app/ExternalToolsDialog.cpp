/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) 2008-2019, Alliance for Sustainable Energy, LLC, and other contributors. All rights reserved.
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

#include "./ExternalToolsDialog.hpp"

#include "../model_editor/Utilities.hpp"

#include <openstudio/src/utilities/core/Path.hpp>

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QDialogButtonBox>
#include <QPushButton>
#include <QFileDialog>
#include <QDir>

// TODO: temp
#include <QDebug>

#include <iostream>


namespace openstudio {

ExternalToolsDialog::ExternalToolsDialog(openstudio::path t_dviewPath)
  : QDialog()
{
  auto mainLayout = new QVBoxLayout();
  setLayout(mainLayout);

  auto title = new QLabel("Change External Tools");
  title->setObjectName("H1");
  mainLayout->addWidget(title);

  // Dview
  auto dviewLayout = new QHBoxLayout();
  mainLayout->addLayout(dviewLayout);
  dviewLayout->addWidget(new QLabel("Path to DView"));

  m_dviewPathLineEdit = new QLineEdit(this);
  m_dviewPathLineEdit->setText(QString::fromStdString(toString(t_dviewPath)));
  dviewLayout->addWidget(m_dviewPathLineEdit);

  QPushButton * changeDviewButton = new QPushButton("Change");
  connect(changeDviewButton, &QPushButton::clicked, this, [this]{ ExternalToolsDialog::onChangeClicked(m_dviewPathLineEdit, "DView"); });



  auto otherToolLayout = new QHBoxLayout();
  mainLayout->addLayout(otherToolLayout);
  otherToolLayout->addWidget(new QLabel("Path to Another Tool"));

  m_otherToolPathLineEdit = new QLineEdit(this);
  otherToolLayout->addWidget(m_otherToolPathLineEdit);
  QPushButton * changeOtherButton = new QPushButton("Change");
  connect(changeOtherButton, &QPushButton::clicked, this, [this]{ ExternalToolsDialog::onChangeClicked(m_otherToolPathLineEdit, "openstudio"); });

  // Buttons Ok/Cancel
  auto buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok
                                   | QDialogButtonBox::Cancel);
  mainLayout->addWidget(buttonBox);

  connect(buttonBox, &QDialogButtonBox::accepted, this, &QDialog::accept);
  connect(buttonBox, &QDialogButtonBox::rejected, this, &QDialog::reject);

}

void ExternalToolsDialog::onChangeClicked(QLineEdit * t_lineEdit, QString toolName) {

  qDebug() << toolName + QString(" (") + toolName + QString("*.exe)");
  qDebug() << toolName;

#if defined _WIN32
  QString filter = toolName + QString(" (") + toolName + QString("*.exe)");
#elif defined Q_OS_DARWIN
  // TODO: definitely not going to work! Thanks Apple!
  QString filter = toolName + QString(" (") + toolName + QString("*.app)");
#else
  QString filter = toolName;
#endif

  auto fileName = QFileDialog::getOpenFileName(nullptr,
      tr("Select Path to ") + toolName, QDir().homePath(), filter);

  if( ! fileName.isNull() ) {
    t_lineEdit->setText(fileName);
  }
}

openstudio::path ExternalToolsDialog::dviewPath() const {
  return openstudio::toPath(m_dviewPathLineEdit->text());
}

openstudio::path ExternalToolsDialog::otherToolPath() const {
  return openstudio::toPath(m_otherToolPathLineEdit->text());
}

} // openstudio
