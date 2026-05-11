#[cfg(feature = "serde")]
use serde::{Deserialize, Serialize};



// Corresponds to py_bus_interfaces__msg__ImuData

// This struct is not documented.
#[allow(missing_docs)]

#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct ImuData {

    // This member is not documented.
    #[allow(missing_docs)]
    pub sample_id: i32,


    // This member is not documented.
    #[allow(missing_docs)]
    pub accel_x: f32,


    // This member is not documented.
    #[allow(missing_docs)]
    pub accel_y: f32,


    // This member is not documented.
    #[allow(missing_docs)]
    pub accel_z: f32,


    // This member is not documented.
    #[allow(missing_docs)]
    pub temp: f32,


    // This member is not documented.
    #[allow(missing_docs)]
    pub gyro_x: f32,


    // This member is not documented.
    #[allow(missing_docs)]
    pub gyro_y: f32,


    // This member is not documented.
    #[allow(missing_docs)]
    pub gyro_z: f32,

}



impl Default for ImuData {
  fn default() -> Self {
    <Self as rosidl_runtime_rs::Message>::from_rmw_message(super::msg::rmw::ImuData::default())
  }
}

impl rosidl_runtime_rs::Message for ImuData {
  type RmwMsg = super::msg::rmw::ImuData;

  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> {
    match msg_cow {
      std::borrow::Cow::Owned(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
        sample_id: msg.sample_id,
        accel_x: msg.accel_x,
        accel_y: msg.accel_y,
        accel_z: msg.accel_z,
        temp: msg.temp,
        gyro_x: msg.gyro_x,
        gyro_y: msg.gyro_y,
        gyro_z: msg.gyro_z,
      }),
      std::borrow::Cow::Borrowed(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
      sample_id: msg.sample_id,
      accel_x: msg.accel_x,
      accel_y: msg.accel_y,
      accel_z: msg.accel_z,
      temp: msg.temp,
      gyro_x: msg.gyro_x,
      gyro_y: msg.gyro_y,
      gyro_z: msg.gyro_z,
      })
    }
  }

  fn from_rmw_message(msg: Self::RmwMsg) -> Self {
    Self {
      sample_id: msg.sample_id,
      accel_x: msg.accel_x,
      accel_y: msg.accel_y,
      accel_z: msg.accel_z,
      temp: msg.temp,
      gyro_x: msg.gyro_x,
      gyro_y: msg.gyro_y,
      gyro_z: msg.gyro_z,
    }
  }
}


// Corresponds to py_bus_interfaces__msg__UwbData

// This struct is not documented.
#[allow(missing_docs)]

#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct UwbData {

    // This member is not documented.
    #[allow(missing_docs)]
    pub x: f32,


    // This member is not documented.
    #[allow(missing_docs)]
    pub y: f32,


    // This member is not documented.
    #[allow(missing_docs)]
    pub ts: f64,

}



impl Default for UwbData {
  fn default() -> Self {
    <Self as rosidl_runtime_rs::Message>::from_rmw_message(super::msg::rmw::UwbData::default())
  }
}

impl rosidl_runtime_rs::Message for UwbData {
  type RmwMsg = super::msg::rmw::UwbData;

  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> {
    match msg_cow {
      std::borrow::Cow::Owned(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
        x: msg.x,
        y: msg.y,
        ts: msg.ts,
      }),
      std::borrow::Cow::Borrowed(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
      x: msg.x,
      y: msg.y,
      ts: msg.ts,
      })
    }
  }

  fn from_rmw_message(msg: Self::RmwMsg) -> Self {
    Self {
      x: msg.x,
      y: msg.y,
      ts: msg.ts,
    }
  }
}


// Corresponds to py_bus_interfaces__msg__DriverStatus

// This struct is not documented.
#[allow(missing_docs)]

#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct DriverStatus {

    // This member is not documented.
    #[allow(missing_docs)]
    pub stamp: builtin_interfaces::msg::Time,


    // This member is not documented.
    #[allow(missing_docs)]
    pub source: std::string::String,


    // This member is not documented.
    #[allow(missing_docs)]
    pub rc_steering_us: i32,


    // This member is not documented.
    #[allow(missing_docs)]
    pub rc_throttle_us: i32,


    // This member is not documented.
    #[allow(missing_docs)]
    pub commanded_speed_kmh: f32,


    // This member is not documented.
    #[allow(missing_docs)]
    pub commanded_steering_deg: f32,


    // This member is not documented.
    #[allow(missing_docs)]
    pub applied_speed_kmh: f32,


    // This member is not documented.
    #[allow(missing_docs)]
    pub applied_steering_deg: f32,


    // This member is not documented.
    #[allow(missing_docs)]
    pub batt_voltage: f32,


    // This member is not documented.
    #[allow(missing_docs)]
    pub batt_pct: f32,


    // This member is not documented.
    #[allow(missing_docs)]
    pub raw_line: std::string::String,

}



impl Default for DriverStatus {
  fn default() -> Self {
    <Self as rosidl_runtime_rs::Message>::from_rmw_message(super::msg::rmw::DriverStatus::default())
  }
}

impl rosidl_runtime_rs::Message for DriverStatus {
  type RmwMsg = super::msg::rmw::DriverStatus;

  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> {
    match msg_cow {
      std::borrow::Cow::Owned(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
        stamp: builtin_interfaces::msg::Time::into_rmw_message(std::borrow::Cow::Owned(msg.stamp)).into_owned(),
        source: msg.source.as_str().into(),
        rc_steering_us: msg.rc_steering_us,
        rc_throttle_us: msg.rc_throttle_us,
        commanded_speed_kmh: msg.commanded_speed_kmh,
        commanded_steering_deg: msg.commanded_steering_deg,
        applied_speed_kmh: msg.applied_speed_kmh,
        applied_steering_deg: msg.applied_steering_deg,
        batt_voltage: msg.batt_voltage,
        batt_pct: msg.batt_pct,
        raw_line: msg.raw_line.as_str().into(),
      }),
      std::borrow::Cow::Borrowed(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
        stamp: builtin_interfaces::msg::Time::into_rmw_message(std::borrow::Cow::Borrowed(&msg.stamp)).into_owned(),
        source: msg.source.as_str().into(),
      rc_steering_us: msg.rc_steering_us,
      rc_throttle_us: msg.rc_throttle_us,
      commanded_speed_kmh: msg.commanded_speed_kmh,
      commanded_steering_deg: msg.commanded_steering_deg,
      applied_speed_kmh: msg.applied_speed_kmh,
      applied_steering_deg: msg.applied_steering_deg,
      batt_voltage: msg.batt_voltage,
      batt_pct: msg.batt_pct,
        raw_line: msg.raw_line.as_str().into(),
      })
    }
  }

  fn from_rmw_message(msg: Self::RmwMsg) -> Self {
    Self {
      stamp: builtin_interfaces::msg::Time::from_rmw_message(msg.stamp),
      source: msg.source.to_string(),
      rc_steering_us: msg.rc_steering_us,
      rc_throttle_us: msg.rc_throttle_us,
      commanded_speed_kmh: msg.commanded_speed_kmh,
      commanded_steering_deg: msg.commanded_steering_deg,
      applied_speed_kmh: msg.applied_speed_kmh,
      applied_steering_deg: msg.applied_steering_deg,
      batt_voltage: msg.batt_voltage,
      batt_pct: msg.batt_pct,
      raw_line: msg.raw_line.to_string(),
    }
  }
}


// Corresponds to py_bus_interfaces__msg__DriverCommand

// This struct is not documented.
#[allow(missing_docs)]

#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct DriverCommand {

    // This member is not documented.
    #[allow(missing_docs)]
    pub speed_kmh: f32,


    // This member is not documented.
    #[allow(missing_docs)]
    pub steering_deg: f32,

}



impl Default for DriverCommand {
  fn default() -> Self {
    <Self as rosidl_runtime_rs::Message>::from_rmw_message(super::msg::rmw::DriverCommand::default())
  }
}

impl rosidl_runtime_rs::Message for DriverCommand {
  type RmwMsg = super::msg::rmw::DriverCommand;

  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> {
    match msg_cow {
      std::borrow::Cow::Owned(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
        speed_kmh: msg.speed_kmh,
        steering_deg: msg.steering_deg,
      }),
      std::borrow::Cow::Borrowed(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
      speed_kmh: msg.speed_kmh,
      steering_deg: msg.steering_deg,
      })
    }
  }

  fn from_rmw_message(msg: Self::RmwMsg) -> Self {
    Self {
      speed_kmh: msg.speed_kmh,
      steering_deg: msg.steering_deg,
    }
  }
}


