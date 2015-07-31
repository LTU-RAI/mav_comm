/*
 * Copyright 2015 Fadri Furrer, ASL, ETH Zurich, Switzerland
 * Copyright 2015 Michael Burri, ASL, ETH Zurich, Switzerland
 * Copyright 2015 Markus Achtelik, ASL, ETH Zurich, Switzerland
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0

 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

// Common conversion functions between geometry messages, Eigen types, and yaw.

#ifndef MAV_MSGS_COMMON_H
#define MAV_MSGS_COMMON_H

#include <Eigen/Core>
#include <geometry_msgs/Point.h>
#include <geometry_msgs/Quaternion.h>
#include <geometry_msgs/Vector3.h>

namespace mav_msgs {

inline Eigen::Vector3d vector3FromMsg(const geometry_msgs::Vector3& msg) {
  return Eigen::Vector3d(msg.x, msg.y, msg.z);
}

inline Eigen::Vector3d vector3FromPointMsg(const geometry_msgs::Point& msg) {
  return Eigen::Vector3d(msg.x, msg.y, msg.z);
}

inline Eigen::Quaterniond quaternionFromMsg(const geometry_msgs::Quaternion& msg) {
  return Eigen::Quaterniond(msg.w, msg.x, msg.y, msg.z);
}

/**
 * \brief Extracts the yaw part from a quaternion, using RPY / euler (z-y'-z'') angles.
 * RPY rotates about the fixed axes in the order x-y-z,
 * which is the same as euler angles in the order z-y'-x''.
 */
double yawFromQuaternion(const Eigen::Quaterniond& q) {
  return atan2(2.0 * (q.w() * q.z() + q.x() * q.y()),
               1.0 - 2.0 * (q.y() * q.y() + q.z() * q.z()));
}

inline Eigen::Quaterniond quaternionFromYaw(double yaw) {
  return Eigen::Quaterniond(Eigen::AngleAxisd(yaw, Eigen::Vector3d::UnitZ()));
}

inline void setQuaternionMsgFromYaw(double yaw, geometry_msgs::Quaternion* msg) {
  assert(msg != NULL);
  Eigen::Quaterniond q_yaw = quaternionFromYaw(yaw);
  msg->x = q_yaw.x();
  msg->y = q_yaw.y();
  msg->z = q_yaw.z();
  msg->w = q_yaw.w();
}

inline void setAngularVelocityMsgFromYawRate(double yaw_rate, geometry_msgs::Vector3* msg) {
  assert(msg != NULL);
  msg->z = yaw_rate;
}

}  // namespace mav_msgs

#endif  // MAV_MSGS_COMMON_H
