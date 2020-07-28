/*
 * Copyright (C) 2020 Open Source Robotics Foundation
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
#ifndef IGNITION_GUI_PLOTTINGINTERFACE_HH_
#define IGNITION_GUI_PLOTTINGINTERFACE_HH_

#include <QObject>
#include <QTimer>
#include <QString>
#include <QVariant>

#include <google/protobuf/message.h>
#include <google/protobuf/descriptor.h>

#include <map>
#include <set>
#include <string>
#include <memory>

#include <ignition/transport/Node.hh>
#include <ignition/transport/MessageInfo.hh>
#include <ignition/transport/Publisher.hh>


namespace ignition
{
namespace gui
{
class Field
{
  /// \brief Constructor
  public: Field();

  /// \brief Set the field Value
  /// \param[in] _value the set value
  public: void SetValue(const double _value);

  /// \brief Get the field value
  /// \return value of the field
  public: double Value() const;

  /// \brief Register a chart that plot that field
  /// \param[in] _chart chart ID to be registered
  public: void AddChart(int _chart);

  /// \brief UnRegister a chart from plotting that field
  public: void RemoveChart(int _chart);

  /// \brief size of registered charts
  /// \return charts size
  public: int ChartCount();

  /// \brief Get all registered charts to that field
  /// \return set of registered charts
  public: std::set<int> &Charts();

  /// \brief value of that field
  private: double value;

  /// \brief Registered Charts to that field
  private: std::set<int> charts;
};

class Topic
{
  /// \brief Constructor
  public: explicit Topic(std::string _name);

  /// \brief get topic name
  public: std::string Name();

  /// \brief Register a chart to a field
  /// \param[in] _fieldPath model path to the field as an ID
  public: void Register(std::string _fieldPath, int _chart);

  /// \brief remove field from the topic
  public: void UnRegister(std::string _fieldPath, int _chart);

  /// \brief size of registered fields
  /// \return fields size
  public: int FieldCount();

  /// \brief get the registered topics
  /// \return topics list
  public: std::map<std::string, Field*> &Fields();
  /// \brief callback to subscribe to that topic
  /// \param[in] _msg the published msg from the topic
  public: void Callback(const google::protobuf::Message &_msg);

  /// \brief check the plotable types and get data from reflection
  private: double PlotData(const google::protobuf::Message &_msg,
                           const google::protobuf::FieldDescriptor *field);

  /// \brief topic name
  private: std::string name;

  /// \brief Plotting fields to update its values
  private: std::map<std::string, Field*> fields;
};

class TransportPrivate;

/// \brief handle Transport Topics Subscribing for one object(Chart)
class Transport
{
  /// \brief Constructor
  public: Transport();

  /// \brief Destructor
  public: ~Transport();

  /// \brief unsubscribe/deattatch a field from a certain chart
  /// \param[in] _topic topic name
  /// \param[in] _fieldPath field path ID
  /// \param[in] _chart chart ID
  public: void Unsubscribe(std::string _topic,
                           std::string _fieldPath,
                           int _chart);

  /// \brief subscribe/attatch a field from a certain chart
  /// \param[in] _topic topic name
  /// \param[in] _fieldPath field path ID
  /// \param[in] _chart chart ID
  public: void Subscribe(std::string _topic,
                         std::string _fieldPath,
                         int _chart);

  /// \brief is the topic exist in the transport network
  /// \param[in] _topic topic name
  /// \return True if found in the transport, False if not found
  public: bool TopicFound(const std::string &_topic);

  /// \brief get the registered topics
  /// \return topics list
  public: const std::map<std::string, Topic*> &Topics();

  private: std::unique_ptr<TransportPrivate> dataPtr;
};

class PlottingIfacePrivate;

/// \brief Plotting Interface
/// Responsible for plotting transport msgs-fields
/// Used by TransportPlotting Plugin & GazeboPlotting Plugin
/// Accepts dragged items from TopicViewer Plugin & ComponentInspector Plugin
class PlottingInterface : public QObject
{
  Q_OBJECT

  /// \brief update the plotting each timeout of the timer
  public slots: void UpdateGui();

  /// \brief Constructor
  public: explicit PlottingInterface();

  /// \brief Destructor
  public: ~PlottingInterface();

  /// \brief subscribe to a field to plotted on a chart
  /// \brief param[in] _topic the topic that includes that field
  /// \brief param[in] _fieldPath path to the field to reach it from the msg
  /// \brief param[in] _chart chart id to be attached to that field
  public slots: void subscribe(QString _topic,
                               QString _fieldPath,
                               int _chart);

  /// \brief unsubscribe from a field and deattach it from a chart
  /// \brief param[in] _topic the topic that includes that field
  /// \brief param[in] _fieldPath path to the field to reach it from the msg
  /// \brief param[in] _chart chart id to be deattached to that field
  public slots: void unsubscribe(QString _topic,
                                 QString _fieldPath,
                                 int _chart);

  /// \brief set the plotting time
  /// \param[in] _timeout the timeout to update the plot
  public: Q_INVOKABLE void setSimTime(double _timeout);

  /// \brief plot a point to a chart
  /// \param[in] _chart chart ID
  /// \param[in] _fieldID field path ID
  /// \param[in] _x x coordinates of the plot point
  /// \param[in] _y y coordinates of the plot point
  signals: void plot(int _chart, QString _fieldID, double _x, double _y);

  /// \brief signal to move the chart aka scroll it to the right
  signals: void moveChart();

  /// \brief slot to to lestin to a timer to emit moveChart signal
  public slots: void moveCharts();

  /// \brief Private data member.
  private: std::unique_ptr<PlottingIfacePrivate> dataPtr;

  /// \brief configration of the timer
  private: void InitTimer();
};

}
}

#endif