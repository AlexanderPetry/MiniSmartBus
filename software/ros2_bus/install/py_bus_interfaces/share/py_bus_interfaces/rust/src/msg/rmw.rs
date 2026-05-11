#[cfg(feature = "serde")]
use serde::{Deserialize, Serialize};


#[link(name = "py_bus_interfaces__rosidl_typesupport_c")]
extern "C" {
    fn rosidl_typesupport_c__get_message_type_support_handle__py_bus_interfaces__msg__ImuData() -> *const std::ffi::c_void;
}

#[link(name = "py_bus_interfaces__rosidl_generator_c")]
extern "C" {
    fn py_bus_interfaces__msg__ImuData__init(msg: *mut ImuData) -> bool;
    fn py_bus_interfaces__msg__ImuData__Sequence__init(seq: *mut rosidl_runtime_rs::Sequence<ImuData>, size: usize) -> bool;
    fn py_bus_interfaces__msg__ImuData__Sequence__fini(seq: *mut rosidl_runtime_rs::Sequence<ImuData>);
    fn py_bus_interfaces__msg__ImuData__Sequence__copy(in_seq: &rosidl_runtime_rs::Sequence<ImuData>, out_seq: *mut rosidl_runtime_rs::Sequence<ImuData>) -> bool;
}

// Corresponds to py_bus_interfaces__msg__ImuData
#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]


// This struct is not documented.
#[allow(missing_docs)]

#[repr(C)]
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
    unsafe {
      let mut msg = std::mem::zeroed();
      if !py_bus_interfaces__msg__ImuData__init(&mut msg as *mut _) {
        panic!("Call to py_bus_interfaces__msg__ImuData__init() failed");
      }
      msg
    }
  }
}

impl rosidl_runtime_rs::SequenceAlloc for ImuData {
  fn sequence_init(seq: &mut rosidl_runtime_rs::Sequence<Self>, size: usize) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { py_bus_interfaces__msg__ImuData__Sequence__init(seq as *mut _, size) }
  }
  fn sequence_fini(seq: &mut rosidl_runtime_rs::Sequence<Self>) {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { py_bus_interfaces__msg__ImuData__Sequence__fini(seq as *mut _) }
  }
  fn sequence_copy(in_seq: &rosidl_runtime_rs::Sequence<Self>, out_seq: &mut rosidl_runtime_rs::Sequence<Self>) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { py_bus_interfaces__msg__ImuData__Sequence__copy(in_seq, out_seq as *mut _) }
  }
}

impl rosidl_runtime_rs::Message for ImuData {
  type RmwMsg = Self;
  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> { msg_cow }
  fn from_rmw_message(msg: Self::RmwMsg) -> Self { msg }
}

impl rosidl_runtime_rs::RmwMessage for ImuData where Self: Sized {
  const TYPE_NAME: &'static str = "py_bus_interfaces/msg/ImuData";
  fn get_type_support() -> *const std::ffi::c_void {
    // SAFETY: No preconditions for this function.
    unsafe { rosidl_typesupport_c__get_message_type_support_handle__py_bus_interfaces__msg__ImuData() }
  }
}


#[link(name = "py_bus_interfaces__rosidl_typesupport_c")]
extern "C" {
    fn rosidl_typesupport_c__get_message_type_support_handle__py_bus_interfaces__msg__UwbData() -> *const std::ffi::c_void;
}

#[link(name = "py_bus_interfaces__rosidl_generator_c")]
extern "C" {
    fn py_bus_interfaces__msg__UwbData__init(msg: *mut UwbData) -> bool;
    fn py_bus_interfaces__msg__UwbData__Sequence__init(seq: *mut rosidl_runtime_rs::Sequence<UwbData>, size: usize) -> bool;
    fn py_bus_interfaces__msg__UwbData__Sequence__fini(seq: *mut rosidl_runtime_rs::Sequence<UwbData>);
    fn py_bus_interfaces__msg__UwbData__Sequence__copy(in_seq: &rosidl_runtime_rs::Sequence<UwbData>, out_seq: *mut rosidl_runtime_rs::Sequence<UwbData>) -> bool;
}

// Corresponds to py_bus_interfaces__msg__UwbData
#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]


// This struct is not documented.
#[allow(missing_docs)]

#[repr(C)]
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
    unsafe {
      let mut msg = std::mem::zeroed();
      if !py_bus_interfaces__msg__UwbData__init(&mut msg as *mut _) {
        panic!("Call to py_bus_interfaces__msg__UwbData__init() failed");
      }
      msg
    }
  }
}

impl rosidl_runtime_rs::SequenceAlloc for UwbData {
  fn sequence_init(seq: &mut rosidl_runtime_rs::Sequence<Self>, size: usize) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { py_bus_interfaces__msg__UwbData__Sequence__init(seq as *mut _, size) }
  }
  fn sequence_fini(seq: &mut rosidl_runtime_rs::Sequence<Self>) {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { py_bus_interfaces__msg__UwbData__Sequence__fini(seq as *mut _) }
  }
  fn sequence_copy(in_seq: &rosidl_runtime_rs::Sequence<Self>, out_seq: &mut rosidl_runtime_rs::Sequence<Self>) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { py_bus_interfaces__msg__UwbData__Sequence__copy(in_seq, out_seq as *mut _) }
  }
}

impl rosidl_runtime_rs::Message for UwbData {
  type RmwMsg = Self;
  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> { msg_cow }
  fn from_rmw_message(msg: Self::RmwMsg) -> Self { msg }
}

impl rosidl_runtime_rs::RmwMessage for UwbData where Self: Sized {
  const TYPE_NAME: &'static str = "py_bus_interfaces/msg/UwbData";
  fn get_type_support() -> *const std::ffi::c_void {
    // SAFETY: No preconditions for this function.
    unsafe { rosidl_typesupport_c__get_message_type_support_handle__py_bus_interfaces__msg__UwbData() }
  }
}


#[link(name = "py_bus_interfaces__rosidl_typesupport_c")]
extern "C" {
    fn rosidl_typesupport_c__get_message_type_support_handle__py_bus_interfaces__msg__DriverStatus() -> *const std::ffi::c_void;
}

#[link(name = "py_bus_interfaces__rosidl_generator_c")]
extern "C" {
    fn py_bus_interfaces__msg__DriverStatus__init(msg: *mut DriverStatus) -> bool;
    fn py_bus_interfaces__msg__DriverStatus__Sequence__init(seq: *mut rosidl_runtime_rs::Sequence<DriverStatus>, size: usize) -> bool;
    fn py_bus_interfaces__msg__DriverStatus__Sequence__fini(seq: *mut rosidl_runtime_rs::Sequence<DriverStatus>);
    fn py_bus_interfaces__msg__DriverStatus__Sequence__copy(in_seq: &rosidl_runtime_rs::Sequence<DriverStatus>, out_seq: *mut rosidl_runtime_rs::Sequence<DriverStatus>) -> bool;
}

// Corresponds to py_bus_interfaces__msg__DriverStatus
#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]


// This struct is not documented.
#[allow(missing_docs)]

#[repr(C)]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct DriverStatus {

    // This member is not documented.
    #[allow(missing_docs)]
    pub stamp: builtin_interfaces::msg::rmw::Time,


    // This member is not documented.
    #[allow(missing_docs)]
    pub source: rosidl_runtime_rs::String,


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
    pub raw_line: rosidl_runtime_rs::String,

}



impl Default for DriverStatus {
  fn default() -> Self {
    unsafe {
      let mut msg = std::mem::zeroed();
      if !py_bus_interfaces__msg__DriverStatus__init(&mut msg as *mut _) {
        panic!("Call to py_bus_interfaces__msg__DriverStatus__init() failed");
      }
      msg
    }
  }
}

impl rosidl_runtime_rs::SequenceAlloc for DriverStatus {
  fn sequence_init(seq: &mut rosidl_runtime_rs::Sequence<Self>, size: usize) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { py_bus_interfaces__msg__DriverStatus__Sequence__init(seq as *mut _, size) }
  }
  fn sequence_fini(seq: &mut rosidl_runtime_rs::Sequence<Self>) {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { py_bus_interfaces__msg__DriverStatus__Sequence__fini(seq as *mut _) }
  }
  fn sequence_copy(in_seq: &rosidl_runtime_rs::Sequence<Self>, out_seq: &mut rosidl_runtime_rs::Sequence<Self>) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { py_bus_interfaces__msg__DriverStatus__Sequence__copy(in_seq, out_seq as *mut _) }
  }
}

impl rosidl_runtime_rs::Message for DriverStatus {
  type RmwMsg = Self;
  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> { msg_cow }
  fn from_rmw_message(msg: Self::RmwMsg) -> Self { msg }
}

impl rosidl_runtime_rs::RmwMessage for DriverStatus where Self: Sized {
  const TYPE_NAME: &'static str = "py_bus_interfaces/msg/DriverStatus";
  fn get_type_support() -> *const std::ffi::c_void {
    // SAFETY: No preconditions for this function.
    unsafe { rosidl_typesupport_c__get_message_type_support_handle__py_bus_interfaces__msg__DriverStatus() }
  }
}


#[link(name = "py_bus_interfaces__rosidl_typesupport_c")]
extern "C" {
    fn rosidl_typesupport_c__get_message_type_support_handle__py_bus_interfaces__msg__DriverCommand() -> *const std::ffi::c_void;
}

#[link(name = "py_bus_interfaces__rosidl_generator_c")]
extern "C" {
    fn py_bus_interfaces__msg__DriverCommand__init(msg: *mut DriverCommand) -> bool;
    fn py_bus_interfaces__msg__DriverCommand__Sequence__init(seq: *mut rosidl_runtime_rs::Sequence<DriverCommand>, size: usize) -> bool;
    fn py_bus_interfaces__msg__DriverCommand__Sequence__fini(seq: *mut rosidl_runtime_rs::Sequence<DriverCommand>);
    fn py_bus_interfaces__msg__DriverCommand__Sequence__copy(in_seq: &rosidl_runtime_rs::Sequence<DriverCommand>, out_seq: *mut rosidl_runtime_rs::Sequence<DriverCommand>) -> bool;
}

// Corresponds to py_bus_interfaces__msg__DriverCommand
#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]


// This struct is not documented.
#[allow(missing_docs)]

#[repr(C)]
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
    unsafe {
      let mut msg = std::mem::zeroed();
      if !py_bus_interfaces__msg__DriverCommand__init(&mut msg as *mut _) {
        panic!("Call to py_bus_interfaces__msg__DriverCommand__init() failed");
      }
      msg
    }
  }
}

impl rosidl_runtime_rs::SequenceAlloc for DriverCommand {
  fn sequence_init(seq: &mut rosidl_runtime_rs::Sequence<Self>, size: usize) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { py_bus_interfaces__msg__DriverCommand__Sequence__init(seq as *mut _, size) }
  }
  fn sequence_fini(seq: &mut rosidl_runtime_rs::Sequence<Self>) {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { py_bus_interfaces__msg__DriverCommand__Sequence__fini(seq as *mut _) }
  }
  fn sequence_copy(in_seq: &rosidl_runtime_rs::Sequence<Self>, out_seq: &mut rosidl_runtime_rs::Sequence<Self>) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { py_bus_interfaces__msg__DriverCommand__Sequence__copy(in_seq, out_seq as *mut _) }
  }
}

impl rosidl_runtime_rs::Message for DriverCommand {
  type RmwMsg = Self;
  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> { msg_cow }
  fn from_rmw_message(msg: Self::RmwMsg) -> Self { msg }
}

impl rosidl_runtime_rs::RmwMessage for DriverCommand where Self: Sized {
  const TYPE_NAME: &'static str = "py_bus_interfaces/msg/DriverCommand";
  fn get_type_support() -> *const std::ffi::c_void {
    // SAFETY: No preconditions for this function.
    unsafe { rosidl_typesupport_c__get_message_type_support_handle__py_bus_interfaces__msg__DriverCommand() }
  }
}


