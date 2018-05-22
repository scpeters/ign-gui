/*
 * Copyright (C) 2017 Open Source Robotics Foundation
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 */

#include <QQmlContext>
#include <QQuickStyle>
#include <QQuickWidget>

#include <ignition/common/Console.hh>
#include "ignition/gui/Dock.hh"
#include "ignition/gui/Plugin.hh"
#include "ignition/gui/TitleBar.hh"

using namespace ignition;
using namespace gui;

/////////////////////////////////////////////////
Dock::Dock()
{
  this->setTitleBarWidget(new TitleBar());
}

/////////////////////////////////////////////////
void Dock::closeEvent(QCloseEvent *_e)
{
  // Set child free
  auto plugin = this->findChild<Plugin *>();
  if (!plugin)
  {
    ignerr << "I lost my child" << std::endl;
  }
  else
  {
    // Notify everyone so the one responsible for the plugin deletes it
    this->Closing();

    // Set child free so we don't delete it with us
    plugin->setParent(nullptr);
  }

  QDockWidget::closeEvent(_e);
}

/////////////////////////////////////////////////
void Dock::SetWidget(QWidget *_widget)
{
  auto layout = new QVBoxLayout();
  layout->addWidget(_widget);

  auto quick = new QQuickWidget();
  quick->setResizeMode(QQuickWidget::SizeRootObjectToView);
  quick->setSource(QUrl("qrc:dock.qml"));
  quick->setLayout(layout);

  this->setWidget(quick);
}

