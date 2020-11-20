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
#ifndef IGNITION_GUI_GUIEVENTS_HH_
#define IGNITION_GUI_GUIEVENTS_HH_

#include <QEvent>
#include <utility>
#include <vector>
#include <ignition/math/Vector3.hh>

namespace ignition
{
  namespace gui
  {
    /// \brief Namespace for all events.
    namespace events
    {
      /// User defined events should start from QEvent::MaxUser and
      /// count down to avoid collision with ign-gazebo events

      /// \brief Event called in the render thread of a 3D scene.
      /// It's safe to make rendering calls in this event's callback.
      class Render : public QEvent
      {
        public: Render()
            : QEvent(kType)
        {
        }
        /// \brief Unique type for this event.
        static const QEvent::Type kType = QEvent::Type(QEvent::MaxUser);
      };

      /// \brief The class for sending and receiving custom snap value events.
      class SnapIntervals : public QEvent
      {
        /// \brief Constructor
        /// \param[in] _xyz XYZ snapping values.
        /// \param[in] _rpy RPY snapping values.
        /// \param[in] _scale Scale snapping values.
        public: SnapIntervals(
                    const math::Vector3d &_xyz,
                    const math::Vector3d &_rpy,
                    const math::Vector3d &_scale)
        : QEvent(kType), xyz(_xyz), rpy(_rpy), scale(_scale)
        {
        }
  
        /// \brief Get the XYZ snapping values.
        /// \return The XYZ snapping values.
        public: math::Vector3d XYZ() const
        {
          return this->xyz;
        }
  
        /// \brief Get the RPY snapping values.
        /// \return The RPY snapping values.
        public: math::Vector3d RPY() const
        {
          return this->rpy;
        }
  
        /// \brief Get the scale snapping values.
        /// \return The scale snapping values.
        public: math::Vector3d Scale() const
        {
          return this->scale;
        }
  
        /// \brief The QEvent representing a snap event occurrence.
        static const QEvent::Type kType = QEvent::Type(QEvent::User);
  
        /// \brief XYZ snapping values in meters, these values must be positive.
        private: math::Vector3d xyz;
  
        /// \brief RPY snapping values in degrees, these values must be positive.
        private: math::Vector3d rpy;
  
        /// \brief Scale snapping values - a multiplier of the current size,
        /// these values must be positive.
        private: math::Vector3d scale;
      };

      /// \brief Event called to spawn a preview model.
      /// Used by plugins that spawn models.
      class SpawnPreviewModel : public QEvent
      {
        /// \brief Constructor
        /// \param[in] _modelSdfString The model's SDF file as a string.
        public: explicit SpawnPreviewModel(std::string &_modelSdfString)
            : QEvent(kType), modelSdfString(_modelSdfString)
        {
        }
  
        /// \brief Unique type for this event.
        static const QEvent::Type kType = QEvent::Type(QEvent::User + 4);
  
        /// \brief Get the sdf string of the model.
        /// \return The model sdf string
        public: std::string ModelSdfString() const
        {
          return this->modelSdfString;
        }
  
        /// \brief The sdf string of the model to be previewed.
        std::string modelSdfString;
      };
  
      /// \brief Event called to spawn a preview resource, which takes the path
      /// to the SDF file. Used by plugins that spawn resources.
      class SpawnPreviewPath : public QEvent
      {
        /// \brief Constructor
        /// \param[in] _filePath The path to an SDF file.
        public: explicit SpawnPreviewPath(const std::string &_filePath)
            : QEvent(kType), filePath(_filePath)
        {
        }
  
        /// \brief Unique type for this event.
        static const QEvent::Type kType = QEvent::Type(QEvent::User + 5);
  
        /// \brief Get the path of the SDF file.
        /// \return The file path.
        public: std::string FilePath() const
        {
          return this->filePath;
        }
  
        /// \brief The path of SDF file to be previewed.
        std::string filePath;
      };
  
      /// \brief Event which is called to broadcast the 3D coordinates of a user's
      /// mouse hover within the scene.
      class HoverToScene : public QEvent
      {
        /// \brief Constructor
        /// \param[in] _point The point at which the mouse is hovering within the
        /// scene
        public: explicit HoverToScene(const math::Vector3d &_point)
            : QEvent(kType), point(_point)
        {
        }
  
        /// \brief Unique type for this event.
        static const QEvent::Type kType = QEvent::Type(QEvent::User + 6);
  
        /// \brief Get the point within the scene over which the user is hovering.
        /// \return The 3D point
        public: math::Vector3d Point() const
        {
          return this->point;
        }
  
        /// \brief The 3D point over which the user is hovering.
        private: math::Vector3d point;
      };
  
      /// \brief Event which is called to broadcast the 3D coordinates of a user's
      /// left click within the scene.
      class LeftClickToScene : public QEvent
      {
        /// \brief Constructor
        /// \param[in] _point The point which the user has left clicked within the
        /// scene
        public: explicit LeftClickToScene(const math::Vector3d &_point)
            : QEvent(kType), point(_point)
        {
        }
  
        /// \brief Unique type for this event.
        static const QEvent::Type kType = QEvent::Type(QEvent::User + 7);
  
        /// \brief Get the point within the scene that the user clicked.
        /// \return The 3D point.
        public: math::Vector3d Point() const
        {
          return this->point;
        }
  
        /// \brief The 3D point that the user clicked within the scene.
        private: math::Vector3d point;
      };
    }
  }
}

#endif  // IGNITION_GUI_GUIEVENTS_HH_
