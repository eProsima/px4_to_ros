cmake_minimum_required(VERSION 3.5)

project(px4_msgs)

if(NOT WIN32)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -Wall -Wextra -Wpedantic")
endif()

find_package(ament_cmake REQUIRED)
find_package(builtin_interfaces REQUIRED)
find_package(rosidl_default_generators REQUIRED)

rosidl_generate_interfaces(px4_msgs
  msg/VehicleStatus.msg
  msg/SubsystemInfo.msg
  msg/InputRc.msg
  msg/OutputPwm.msg
  msg/BatteryStatus.msg
  msg/McVirtualRatesSetpoint.msg
  msg/ActuatorDirect.msg
  msg/FollowTarget.msg
  msg/SensorBaro.msg
  msg/FwPosCtrlStatus.msg
  msg/FenceVertex.msg
  #msg/TecsStatus.msg
  msg/LogMessage.msg
  msg/DistanceSensor.msg
  msg/UlogStream.msg
  msg/SensorAccel.msg
  msg/RcChannels.msg
  msg/FilteredBottomFlow.msg
  msg/PwmInput.msg
  msg/VehicleAttitude.msg
  msg/GeofenceResult.msg
  msg/Cpuload.msg
  #msg/EscStatus.msg
  msg/MountOrientation.msg
  msg/ParameterUpdate.msg
  #msg/TransponderReport.msg
  msg/VehicleGpsPosition.msg
  msg/QshellReq.msg
  msg/WindEstimate.msg
  msg/ManualControlSetpoint.msg
  msg/RcParameterMap.msg
  msg/Safety.msg
  msg/MultirotorMotorLimits.msg
  #msg/PositionSetpointTriplet.msg
  msg/SensorPreflight.msg
  msg/SensorCombined.msg
  msg/CommanderState.msg
  msg/SensorCorrection.msg
  msg/VehicleGlobalPosition.msg
  msg/Mission.msg
  #msg/SystemPower.msg
  msg/Ekf2Replay.msg
  msg/FwVirtualRatesSetpoint.msg
  msg/DebugKeyValue.msg
  msg/ActuatorArmed.msg
  #msg/FwVirtualAttitudeSetpoint.msg
  msg/TestMotor.msg
  msg/VtolVehicleStatus.msg
  msg/AdcReport.msg
  msg/TelemetryStatus.msg
  msg/Airspeed.msg
  msg/VehicleRatesSetpoint.msg
  msg/VehicleLocalPosition.msg
  msg/SatelliteInfo.msg
  msg/DifferentialPressure.msg
  msg/VisionPositionEstimate.msg
  msg/HomePosition.msg
  msg/ControlState.msg
  msg/AttPosMocap.msg
  msg/GpsDump.msg
  msg/ServorailStatus.msg
  msg/HilSensor.msg
  msg/MissionResult.msg
  #msg/McVirtualAttitudeSetpoint.msg
  msg/VehicleForceSetpoint.msg
  msg/VehicleLandDetected.msg
  msg/LowStack.msg
  msg/VehicleControlMode.msg
  msg/CameraTrigger.msg
  msg/ActuatorOutputs.msg
  #msg/Fence.msg
  msg/GpsInjectData.msg
  msg/ActuatorControls.msg
  msg/TimeOffset.msg
  msg/EscReport.msg
  msg/EstimatorStatus.msg
  msg/OffboardControlMode.msg
  msg/McAttCtrlStatus.msg
  msg/Ekf2Innovations.msg
  msg/VehicleAttitudeSetpoint.msg
  msg/SensorGyro.msg
  msg/PositionSetpoint.msg
  msg/VehicleRoi.msg
  msg/VehicleLocalPositionSetpoint.msg
  msg/MavlinkLog.msg
  msg/VehicleCommandAck.msg
  msg/VehicleCommand.msg
  msg/VehicleGlobalVelocitySetpoint.msg
  msg/UavcanParameterValue.msg
  msg/OpticalFlow.msg
  msg/CollisionReport.msg
  msg/SensorMag.msg
  msg/UlogStreamAck.msg
  msg/UavcanParameterRequest.msg
  DEPENDENCIES builtin_interfaces
)

ament_package()
