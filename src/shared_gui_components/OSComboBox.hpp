/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) 2020-2020, OpenStudio Coalition and other contributors. All rights reserved.
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

#ifndef SHAREDGUICOMPONENTS_OSCOMBOBOX_HPP
#define SHAREDGUICOMPONENTS_OSCOMBOBOX_HPP

#include "FieldMethodTypedefs.hpp"
#include "OSConcepts.hpp"

#include "OSGridController.hpp"  // Needed for DataSource

#include <openstudio/nano/nano_signal_slot.hpp>  // Signal-Slot replacement
#include <openstudio/model/Model.hpp>
#include <openstudio/model/ModelObject.hpp>

#include <openstudio/utilities/idf/WorkspaceObject.hpp>

#include <QComboBox>
#include <QList>

#include <vector>

namespace openstudio {

class OSComboBoxDataSource : public QObject, public Nano::Observer
{
  Q_OBJECT

 public:
  virtual ~OSComboBoxDataSource() {}

  virtual int numberOfItems() = 0;

  virtual QString valueAt(int i) = 0;

 signals:

  void itemChanged(int);

  void itemAdded(int);

  void itemRemoved(int);
};

class OSObjectListCBDS : public OSComboBoxDataSource
{
  Q_OBJECT

 public:
  OSObjectListCBDS(const IddObjectType& type, const model::Model& model);

  OSObjectListCBDS(const std::vector<IddObjectType>& types, const model::Model& model);

  virtual ~OSObjectListCBDS() {}

  int numberOfItems() override;

  QString valueAt(int i) override;

 protected:
  bool m_allowEmptySelection;

 private slots:

  void onObjectAdded(const WorkspaceObject&, const openstudio::IddObjectType& type, const openstudio::UUID& uuid);

  void onObjectWillBeRemoved(const WorkspaceObject&, const openstudio::IddObjectType& type, const openstudio::UUID& uuid);

  void onObjectChanged();

 private:
  void initialize();

  std::vector<IddObjectType> m_types;

  model::Model m_model;

  QList<WorkspaceObject> m_workspaceObjects;
};

class OSComboBox2 : public QComboBox, public Nano::Observer
{
  Q_OBJECT
 public:
  OSComboBox2(QWidget* parent = nullptr, bool editable = false);

  virtual ~OSComboBox2();

  void enableClickFocus();

  void disableClickFocus();

  bool hasData();

  void setLocked(bool locked);

  // interface for direct bind
  template <typename ChoiceType>
  void bind(model::ModelObject& modelObject, std::function<std::string(ChoiceType)> toString, std::function<std::vector<ChoiceType>()> choices,
            std::function<ChoiceType()> getter, std::function<bool(ChoiceType)> setter, boost::optional<NoFailAction> reset = boost::none,
            boost::optional<BasicQuery> isDefaulted = boost::none) {
    m_modelObject = modelObject;
    m_choiceConcept =
      std::shared_ptr<ChoiceConcept>(new RequiredChoiceConceptImpl<ChoiceType>(toString, choices, getter, setter, reset, isDefaulted));
    clear();
    completeBind();
  }

  // interface for direct bind
  template <typename ChoiceType>
  void bind(model::ModelObject& modelObject, std::function<std::string(ChoiceType)> toString, std::function<std::vector<ChoiceType>()> choices,
            std::function<boost::optional<ChoiceType>()> getter, std::function<bool(ChoiceType)> setter,
            boost::optional<NoFailAction> reset = boost::none) {
    m_modelObject = modelObject;
    m_choiceConcept = std::shared_ptr<ChoiceConcept>(new OptionalChoiceConceptImpl<ChoiceType>(toString, choices, getter, setter, reset));
    clear();
    completeBind();
  }

  // Interface for direct bind with two model objects, for eg to set the Schedule of a modelObject (`bind<model::Schedule, model::Class>`)
  // This is similar to the way OSGridController uses a template to create a ComboBoxOptionalChoiceImpl (same signature for the getter/setter etc)
  // For an example of usage refer to ../openstudio_lib/SimSettingsView.hpp.
  template <typename ChoiceType, typename DataSourceType>
  void bind(model::ModelObject& modelObject, std::function<std::string(const ChoiceType&)> toString,
            std::function<std::vector<ChoiceType>(DataSourceType*)> choices, std::function<boost::optional<ChoiceType>(DataSourceType*)> getter,
            std::function<bool(DataSourceType*, ChoiceType)> setter, boost::optional<std::function<void(DataSourceType*)>> reset = boost::none,
            const boost::optional<DataSource>& t_source = boost::none, bool editable = false) {
    m_modelObject = modelObject;

    std::shared_ptr<DataSourceType> dataSource = std::shared_ptr<DataSourceType>(new DataSourceType(modelObject.cast<DataSourceType>()));

    boost::optional<NoFailAction> resetAction;
    if (reset) {
      resetAction = std::bind(reset.get(), dataSource.get());
    }

    m_choiceConcept = std::make_shared<OptionalChoiceSaveDataSourceConceptImpl<ChoiceType, DataSourceType>>(
      dataSource, toString, std::bind(choices, dataSource.get()), std::bind(getter, dataSource.get()),
      std::bind(setter, dataSource.get(), std::placeholders::_1), resetAction, editable);

    clear();
    completeBind();
  }

  // interface for OSGridController bind
  void bind(const model::ModelObject& modelObject, std::shared_ptr<ChoiceConcept> choiceConcept) {
    m_modelObject = modelObject;
    m_choiceConcept = choiceConcept;
    clear();
    completeBind();
  }

  // Bind to an OSComboBoxDataSource
  void bind(std::shared_ptr<OSComboBoxDataSource> dataSource);

  void unbind();

 protected:
  bool event(QEvent* e) override;

 signals:

  void inFocus(bool inFocus, bool hasData);

 public slots:
  // Need to make that public for dependent dropdowns...
  void onChoicesRefreshTrigger();

 private slots:

  void onModelObjectChanged();

  void onModelObjectRemoved(const Handle& handle);

  void onCurrentIndexChanged(const QString& text);

  void onEditTextChanged(const QString& text);

  void onDataSourceChange(int);

  void onDataSourceAdd(int);

  void onDataSourceRemove(int);

 private:
  void updateStyle();

  std::shared_ptr<OSComboBoxDataSource> m_dataSource;

  boost::optional<model::ModelObject> m_modelObject;
  std::shared_ptr<ChoiceConcept> m_choiceConcept;
  std::vector<std::string> m_values;

  bool m_hasClickFocus = false;
  bool m_focused = false;
  bool m_locked = false;

  void completeBind();
};

/**
 * OSComboBox is a derived class of QComboBox that is made to easily bind to an OpenStudio
 * model choice field.
 *
 * Alternatively, a OSComboBoxDataSource can be set to provide data to OSComoboBox.
 **/
// class OSComboBox : public QComboBox, public Nano::Observer {
//   Q_OBJECT

//  public:

//   OSComboBox( QWidget * parent = nullptr );

//   virtual ~OSComboBox() {}

//   void bind(model::ModelObject & modelObject, const char * property);

//   void unbind();

//   void setDataSource(std::shared_ptr<OSComboBoxDataSource> dataSource);

//  protected:

//   bool event( QEvent * e ) override;

//  private slots:

//   void onDataSourceChange(int);

//   void onDataSourceAdd(int);

//   void onDataSourceRemove(int);

//   void onModelObjectChanged();

//   void onModelObjectRemoved(const Handle& handle);

//   void onCurrentIndexChanged(const QString & text);

//  private:

//   std::shared_ptr<OSComboBoxDataSource> m_dataSource;

//   boost::optional<model::ModelObject> m_modelObject;

//   std::string m_property;

//   std::vector<std::string> m_values;
// };

}  // namespace openstudio

#endif  // SHAREDGUICOMPONENTS_OSCOMBOBOX_HPP
