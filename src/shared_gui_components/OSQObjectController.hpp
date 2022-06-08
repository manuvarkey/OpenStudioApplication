/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) 2020-2022, OpenStudio Coalition and other contributors. All rights reserved.
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

#ifndef SHAREDGUICOMPONENTS_OSQOBJECTCONTROLLER_HPP
#define SHAREDGUICOMPONENTS_OSQOBJECTCONTROLLER_HPP

#include <QObject>
#include <openstudio/nano/nano_signal_slot.hpp>  // Signal-Slot replacement

#include <vector>

namespace openstudio {

class OSQObjectController
  : public QObject
  , public Nano::Observer
{
  Q_OBJECT

 public:
  /** OSQObjectController manages the life cycle of dynamically allocated QObjects when they
   *  are not part of a parent child hierarchy.  This is the case for top level QWidgets
   *  owned by a controller.
   **/
  OSQObjectController();

  virtual ~OSQObjectController();

 protected:
  /** Registers the QObject so that its lifecycle is managed.
   *  When OSQObjectController is deleted the managed QObjects will safely be removed.
   **/
  void addQObject(QObject* object);

 private slots:

  void onObjectDestroyed(QObject* object = nullptr);

 private:
  std::vector<QObject*> m_objects;
};

}  // namespace openstudio

#endif  // SHAREDGUICOMPONENTS_OSQOBJECTCONTROLLER_HPP
