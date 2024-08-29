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

#ifndef OPENSTUDIO_SCHEDULEFILEINSPECTORVIEW_HPP
#define OPENSTUDIO_SCHEDULEFILEINSPECTORVIEW_HPP

#include "ModelObjectInspectorView.hpp"
#include <openstudio/model/ScheduleFile.hpp>

class QLineEdit;
class QPlainTextEdit;

namespace openstudio {

class OSLineEdit2;
class OSIntegerEdit2;
class OSComboBox2;
class OSSwitch2;

class ScheduleFileInspectorView : public ModelObjectInspectorView
{
  Q_OBJECT

 public:
  ScheduleFileInspectorView(const openstudio::model::Model& model, QWidget* parent = nullptr);

  virtual ~ScheduleFileInspectorView() = default;

 protected:
  virtual void onClearSelection() override;

  virtual void onSelectModelObject(const openstudio::model::ModelObject& modelObject) override;

  virtual void onUpdate() override;

 private:
  void createLayout();

  void attach(openstudio::model::ScheduleFile& sch);

  void detach();

  void refresh();

  void refreshContent();

  boost::optional<model::ScheduleFile> m_sch;

  OSLineEdit2* m_nameEdit = nullptr;
  QLineEdit* m_filePath = nullptr;
  OSIntegerEdit2* m_columnNumber = nullptr;
  OSIntegerEdit2* m_rowstoSkipatTop = nullptr;
  OSIntegerEdit2* m_numberofHoursofData = nullptr;
  OSComboBox2* m_columnSeparator = nullptr;
  OSSwitch2* m_interpolatetoTimestep = nullptr;
  OSComboBox2* m_minutesperItem = nullptr;
  OSSwitch2* m_adjustScheduleforDaylightSavings = nullptr;
  OSSwitch2* m_translateFileWithRelativePath = nullptr;

  QLineEdit* m_numLines = nullptr;
  QPlainTextEdit* m_contentLines = nullptr;
  QStringList m_lines;
};

}  // namespace openstudio

#endif  // OPENSTUDIO_SCHEDULEFILEINSPECTORVIEW_HPP
