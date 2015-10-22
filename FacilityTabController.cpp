/**********************************************************************
*  Copyright (c) 2008-2015, Alliance for Sustainable Energy.  
*  All rights reserved.
*  
*  This library is free software; you can redistribute it and/or
*  modify it under the terms of the GNU Lesser General Public
*  License as published by the Free Software Foundation; either
*  version 2.1 of the License, or (at your option) any later version.
*  
*  This library is distributed in the hope that it will be useful,
*  but WITHOUT ANY WARRANTY; without even the implied warranty of
*  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
*  Lesser General Public License for more details.
*  
*  You should have received a copy of the GNU Lesser General Public
*  License along with this library; if not, write to the Free Software
*  Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
**********************************************************************/

#include "FacilityTabController.hpp"

#include "BuildingInspectorView.hpp"
#include "FacilityExteriorEquipmentGridView.hpp"
#include "FacilityShadingGridView.hpp"
#include "FacilityStoriesGridView.hpp"
#include "FacilityTabView.hpp"

namespace openstudio {

FacilityTabController::FacilityTabController(bool isIP, const model::Model& model)
  : MainTabController(new FacilityTabView()),
  m_model(model),
  m_isIP(isIP)
{
  mainContentWidget()->addSubTab("Building", BUILDING);
  mainContentWidget()->addSubTab("Stories", STORIES);
  mainContentWidget()->addSubTab("Shading", SHADING);
  mainContentWidget()->addSubTab("Exterior Equipment", EXTERIOR_EQUIPMENT);

  setSubTab(0);
}

void FacilityTabController::toggleUnits(bool displayIP)
{
}

void FacilityTabController::setSubTab(int index)
{
  switch (index){
  case 0:
  {
    auto buildingInspectorView = new BuildingInspectorView(m_isIP, m_model);
    connect(this, &FacilityTabController::toggleUnitsClicked, buildingInspectorView, &BuildingInspectorView::toggleUnitsClicked);
    connect(buildingInspectorView, &BuildingInspectorView::dropZoneItemClicked, this, &FacilityTabController::dropZoneItemClicked);
    connect(this->mainContentWidget(), &MainTabView::tabSelected, this, &FacilityTabController::setSubTab);
    this->mainContentWidget()->setSubTab(buildingInspectorView);
    break;
  }
  case 1:
  {
    auto facilityStoriesGridView = new FacilityStoriesGridView(m_isIP, m_model);
    connect(this, &FacilityTabController::toggleUnitsClicked, facilityStoriesGridView, &FacilityStoriesGridView::toggleUnitsClicked);
    connect(facilityStoriesGridView, &FacilityStoriesGridView::dropZoneItemSelected, this, &FacilityTabController::dropZoneItemSelected);
    connect(this->mainContentWidget(), &MainTabView::tabSelected, this, &FacilityTabController::setSubTab);
    this->mainContentWidget()->setSubTab(facilityStoriesGridView);
    break;
  }
  case 2:
  {
    auto facilityShadingGridView = new FacilityShadingGridView(m_isIP, m_model);
    connect(this, &FacilityTabController::toggleUnitsClicked, facilityShadingGridView, &FacilityShadingGridView::toggleUnitsClicked);
    connect(facilityShadingGridView, &FacilityShadingGridView::dropZoneItemSelected, this, &FacilityTabController::dropZoneItemSelected);
    connect(this->mainContentWidget(), &MainTabView::tabSelected, this, &FacilityTabController::setSubTab);
    this->mainContentWidget()->setSubTab(facilityShadingGridView);
    break;
  }
  case 3:
  {
    auto facilityExteriorEquipmentGridView = new FacilityExteriorEquipmentGridView(m_isIP, m_model);
    connect(this, &FacilityTabController::toggleUnitsClicked, facilityExteriorEquipmentGridView, &FacilityExteriorEquipmentGridView::toggleUnitsClicked);
    connect(facilityExteriorEquipmentGridView, &FacilityExteriorEquipmentGridView::dropZoneItemSelected, this, &FacilityTabController::dropZoneItemSelected);
    connect(this->mainContentWidget(), &MainTabView::tabSelected, this, &FacilityTabController::setSubTab);
    this->mainContentWidget()->setSubTab(facilityExteriorEquipmentGridView);
    break;
  }
  default:
    OS_ASSERT(false);
    break;
  }
}

} // openstudio
