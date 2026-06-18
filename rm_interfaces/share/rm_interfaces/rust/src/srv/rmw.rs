#[cfg(feature = "serde")]
use serde::{Deserialize, Serialize};



#[link(name = "rm_interfaces__rosidl_typesupport_c")]
extern "C" {
    fn rosidl_typesupport_c__get_message_type_support_handle__rm_interfaces__srv__SetMode_Request() -> *const std::ffi::c_void;
}

#[link(name = "rm_interfaces__rosidl_generator_c")]
extern "C" {
    fn rm_interfaces__srv__SetMode_Request__init(msg: *mut SetMode_Request) -> bool;
    fn rm_interfaces__srv__SetMode_Request__Sequence__init(seq: *mut rosidl_runtime_rs::Sequence<SetMode_Request>, size: usize) -> bool;
    fn rm_interfaces__srv__SetMode_Request__Sequence__fini(seq: *mut rosidl_runtime_rs::Sequence<SetMode_Request>);
    fn rm_interfaces__srv__SetMode_Request__Sequence__copy(in_seq: &rosidl_runtime_rs::Sequence<SetMode_Request>, out_seq: *mut rosidl_runtime_rs::Sequence<SetMode_Request>) -> bool;
}

// Corresponds to rm_interfaces__srv__SetMode_Request
#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]


// This struct is not documented.
#[allow(missing_docs)]

#[allow(non_camel_case_types)]
#[repr(C)]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct SetMode_Request {
    /// 0:自瞄红 1:自瞄蓝 2:小符红 3:小符蓝 4：大符红 5：大符蓝
    pub mode: u8,

}



impl Default for SetMode_Request {
  fn default() -> Self {
    unsafe {
      let mut msg = std::mem::zeroed();
      if !rm_interfaces__srv__SetMode_Request__init(&mut msg as *mut _) {
        panic!("Call to rm_interfaces__srv__SetMode_Request__init() failed");
      }
      msg
    }
  }
}

impl rosidl_runtime_rs::SequenceAlloc for SetMode_Request {
  fn sequence_init(seq: &mut rosidl_runtime_rs::Sequence<Self>, size: usize) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { rm_interfaces__srv__SetMode_Request__Sequence__init(seq as *mut _, size) }
  }
  fn sequence_fini(seq: &mut rosidl_runtime_rs::Sequence<Self>) {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { rm_interfaces__srv__SetMode_Request__Sequence__fini(seq as *mut _) }
  }
  fn sequence_copy(in_seq: &rosidl_runtime_rs::Sequence<Self>, out_seq: &mut rosidl_runtime_rs::Sequence<Self>) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { rm_interfaces__srv__SetMode_Request__Sequence__copy(in_seq, out_seq as *mut _) }
  }
}

impl rosidl_runtime_rs::Message for SetMode_Request {
  type RmwMsg = Self;
  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> { msg_cow }
  fn from_rmw_message(msg: Self::RmwMsg) -> Self { msg }
}

impl rosidl_runtime_rs::RmwMessage for SetMode_Request where Self: Sized {
  const TYPE_NAME: &'static str = "rm_interfaces/srv/SetMode_Request";
  fn get_type_support() -> *const std::ffi::c_void {
    // SAFETY: No preconditions for this function.
    unsafe { rosidl_typesupport_c__get_message_type_support_handle__rm_interfaces__srv__SetMode_Request() }
  }
}


#[link(name = "rm_interfaces__rosidl_typesupport_c")]
extern "C" {
    fn rosidl_typesupport_c__get_message_type_support_handle__rm_interfaces__srv__SetMode_Response() -> *const std::ffi::c_void;
}

#[link(name = "rm_interfaces__rosidl_generator_c")]
extern "C" {
    fn rm_interfaces__srv__SetMode_Response__init(msg: *mut SetMode_Response) -> bool;
    fn rm_interfaces__srv__SetMode_Response__Sequence__init(seq: *mut rosidl_runtime_rs::Sequence<SetMode_Response>, size: usize) -> bool;
    fn rm_interfaces__srv__SetMode_Response__Sequence__fini(seq: *mut rosidl_runtime_rs::Sequence<SetMode_Response>);
    fn rm_interfaces__srv__SetMode_Response__Sequence__copy(in_seq: &rosidl_runtime_rs::Sequence<SetMode_Response>, out_seq: *mut rosidl_runtime_rs::Sequence<SetMode_Response>) -> bool;
}

// Corresponds to rm_interfaces__srv__SetMode_Response
#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]


// This struct is not documented.
#[allow(missing_docs)]

#[allow(non_camel_case_types)]
#[repr(C)]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct SetMode_Response {
    /// indicate successful run of triggered service
    pub success: bool,

    /// informational, e.g. for error messages
    pub message: rosidl_runtime_rs::String,

}



impl Default for SetMode_Response {
  fn default() -> Self {
    unsafe {
      let mut msg = std::mem::zeroed();
      if !rm_interfaces__srv__SetMode_Response__init(&mut msg as *mut _) {
        panic!("Call to rm_interfaces__srv__SetMode_Response__init() failed");
      }
      msg
    }
  }
}

impl rosidl_runtime_rs::SequenceAlloc for SetMode_Response {
  fn sequence_init(seq: &mut rosidl_runtime_rs::Sequence<Self>, size: usize) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { rm_interfaces__srv__SetMode_Response__Sequence__init(seq as *mut _, size) }
  }
  fn sequence_fini(seq: &mut rosidl_runtime_rs::Sequence<Self>) {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { rm_interfaces__srv__SetMode_Response__Sequence__fini(seq as *mut _) }
  }
  fn sequence_copy(in_seq: &rosidl_runtime_rs::Sequence<Self>, out_seq: &mut rosidl_runtime_rs::Sequence<Self>) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { rm_interfaces__srv__SetMode_Response__Sequence__copy(in_seq, out_seq as *mut _) }
  }
}

impl rosidl_runtime_rs::Message for SetMode_Response {
  type RmwMsg = Self;
  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> { msg_cow }
  fn from_rmw_message(msg: Self::RmwMsg) -> Self { msg }
}

impl rosidl_runtime_rs::RmwMessage for SetMode_Response where Self: Sized {
  const TYPE_NAME: &'static str = "rm_interfaces/srv/SetMode_Response";
  fn get_type_support() -> *const std::ffi::c_void {
    // SAFETY: No preconditions for this function.
    unsafe { rosidl_typesupport_c__get_message_type_support_handle__rm_interfaces__srv__SetMode_Response() }
  }
}


#[link(name = "rm_interfaces__rosidl_typesupport_c")]
extern "C" {
    fn rosidl_typesupport_c__get_message_type_support_handle__rm_interfaces__srv__RunHandEyeCalibration_Request() -> *const std::ffi::c_void;
}

#[link(name = "rm_interfaces__rosidl_generator_c")]
extern "C" {
    fn rm_interfaces__srv__RunHandEyeCalibration_Request__init(msg: *mut RunHandEyeCalibration_Request) -> bool;
    fn rm_interfaces__srv__RunHandEyeCalibration_Request__Sequence__init(seq: *mut rosidl_runtime_rs::Sequence<RunHandEyeCalibration_Request>, size: usize) -> bool;
    fn rm_interfaces__srv__RunHandEyeCalibration_Request__Sequence__fini(seq: *mut rosidl_runtime_rs::Sequence<RunHandEyeCalibration_Request>);
    fn rm_interfaces__srv__RunHandEyeCalibration_Request__Sequence__copy(in_seq: &rosidl_runtime_rs::Sequence<RunHandEyeCalibration_Request>, out_seq: *mut rosidl_runtime_rs::Sequence<RunHandEyeCalibration_Request>) -> bool;
}

// Corresponds to rm_interfaces__srv__RunHandEyeCalibration_Request
#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]


// This struct is not documented.
#[allow(missing_docs)]

#[allow(non_camel_case_types)]
#[repr(C)]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct RunHandEyeCalibration_Request {

    // This member is not documented.
    #[allow(missing_docs)]
    pub structure_needs_at_least_one_member: u8,

}



impl Default for RunHandEyeCalibration_Request {
  fn default() -> Self {
    unsafe {
      let mut msg = std::mem::zeroed();
      if !rm_interfaces__srv__RunHandEyeCalibration_Request__init(&mut msg as *mut _) {
        panic!("Call to rm_interfaces__srv__RunHandEyeCalibration_Request__init() failed");
      }
      msg
    }
  }
}

impl rosidl_runtime_rs::SequenceAlloc for RunHandEyeCalibration_Request {
  fn sequence_init(seq: &mut rosidl_runtime_rs::Sequence<Self>, size: usize) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { rm_interfaces__srv__RunHandEyeCalibration_Request__Sequence__init(seq as *mut _, size) }
  }
  fn sequence_fini(seq: &mut rosidl_runtime_rs::Sequence<Self>) {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { rm_interfaces__srv__RunHandEyeCalibration_Request__Sequence__fini(seq as *mut _) }
  }
  fn sequence_copy(in_seq: &rosidl_runtime_rs::Sequence<Self>, out_seq: &mut rosidl_runtime_rs::Sequence<Self>) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { rm_interfaces__srv__RunHandEyeCalibration_Request__Sequence__copy(in_seq, out_seq as *mut _) }
  }
}

impl rosidl_runtime_rs::Message for RunHandEyeCalibration_Request {
  type RmwMsg = Self;
  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> { msg_cow }
  fn from_rmw_message(msg: Self::RmwMsg) -> Self { msg }
}

impl rosidl_runtime_rs::RmwMessage for RunHandEyeCalibration_Request where Self: Sized {
  const TYPE_NAME: &'static str = "rm_interfaces/srv/RunHandEyeCalibration_Request";
  fn get_type_support() -> *const std::ffi::c_void {
    // SAFETY: No preconditions for this function.
    unsafe { rosidl_typesupport_c__get_message_type_support_handle__rm_interfaces__srv__RunHandEyeCalibration_Request() }
  }
}


#[link(name = "rm_interfaces__rosidl_typesupport_c")]
extern "C" {
    fn rosidl_typesupport_c__get_message_type_support_handle__rm_interfaces__srv__RunHandEyeCalibration_Response() -> *const std::ffi::c_void;
}

#[link(name = "rm_interfaces__rosidl_generator_c")]
extern "C" {
    fn rm_interfaces__srv__RunHandEyeCalibration_Response__init(msg: *mut RunHandEyeCalibration_Response) -> bool;
    fn rm_interfaces__srv__RunHandEyeCalibration_Response__Sequence__init(seq: *mut rosidl_runtime_rs::Sequence<RunHandEyeCalibration_Response>, size: usize) -> bool;
    fn rm_interfaces__srv__RunHandEyeCalibration_Response__Sequence__fini(seq: *mut rosidl_runtime_rs::Sequence<RunHandEyeCalibration_Response>);
    fn rm_interfaces__srv__RunHandEyeCalibration_Response__Sequence__copy(in_seq: &rosidl_runtime_rs::Sequence<RunHandEyeCalibration_Response>, out_seq: *mut rosidl_runtime_rs::Sequence<RunHandEyeCalibration_Response>) -> bool;
}

// Corresponds to rm_interfaces__srv__RunHandEyeCalibration_Response
#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]


// This struct is not documented.
#[allow(missing_docs)]

#[allow(non_camel_case_types)]
#[repr(C)]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct RunHandEyeCalibration_Response {

    // This member is not documented.
    #[allow(missing_docs)]
    pub success: bool,


    // This member is not documented.
    #[allow(missing_docs)]
    pub yaml_path: rosidl_runtime_rs::String,

}



impl Default for RunHandEyeCalibration_Response {
  fn default() -> Self {
    unsafe {
      let mut msg = std::mem::zeroed();
      if !rm_interfaces__srv__RunHandEyeCalibration_Response__init(&mut msg as *mut _) {
        panic!("Call to rm_interfaces__srv__RunHandEyeCalibration_Response__init() failed");
      }
      msg
    }
  }
}

impl rosidl_runtime_rs::SequenceAlloc for RunHandEyeCalibration_Response {
  fn sequence_init(seq: &mut rosidl_runtime_rs::Sequence<Self>, size: usize) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { rm_interfaces__srv__RunHandEyeCalibration_Response__Sequence__init(seq as *mut _, size) }
  }
  fn sequence_fini(seq: &mut rosidl_runtime_rs::Sequence<Self>) {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { rm_interfaces__srv__RunHandEyeCalibration_Response__Sequence__fini(seq as *mut _) }
  }
  fn sequence_copy(in_seq: &rosidl_runtime_rs::Sequence<Self>, out_seq: &mut rosidl_runtime_rs::Sequence<Self>) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { rm_interfaces__srv__RunHandEyeCalibration_Response__Sequence__copy(in_seq, out_seq as *mut _) }
  }
}

impl rosidl_runtime_rs::Message for RunHandEyeCalibration_Response {
  type RmwMsg = Self;
  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> { msg_cow }
  fn from_rmw_message(msg: Self::RmwMsg) -> Self { msg }
}

impl rosidl_runtime_rs::RmwMessage for RunHandEyeCalibration_Response where Self: Sized {
  const TYPE_NAME: &'static str = "rm_interfaces/srv/RunHandEyeCalibration_Response";
  fn get_type_support() -> *const std::ffi::c_void {
    // SAFETY: No preconditions for this function.
    unsafe { rosidl_typesupport_c__get_message_type_support_handle__rm_interfaces__srv__RunHandEyeCalibration_Response() }
  }
}






#[link(name = "rm_interfaces__rosidl_typesupport_c")]
extern "C" {
    fn rosidl_typesupport_c__get_service_type_support_handle__rm_interfaces__srv__SetMode() -> *const std::ffi::c_void;
}

// Corresponds to rm_interfaces__srv__SetMode
#[allow(missing_docs, non_camel_case_types)]
pub struct SetMode;

impl rosidl_runtime_rs::Service for SetMode {
    type Request = SetMode_Request;
    type Response = SetMode_Response;

    fn get_type_support() -> *const std::ffi::c_void {
        // SAFETY: No preconditions for this function.
        unsafe { rosidl_typesupport_c__get_service_type_support_handle__rm_interfaces__srv__SetMode() }
    }
}




#[link(name = "rm_interfaces__rosidl_typesupport_c")]
extern "C" {
    fn rosidl_typesupport_c__get_service_type_support_handle__rm_interfaces__srv__RunHandEyeCalibration() -> *const std::ffi::c_void;
}

// Corresponds to rm_interfaces__srv__RunHandEyeCalibration
#[allow(missing_docs, non_camel_case_types)]
pub struct RunHandEyeCalibration;

impl rosidl_runtime_rs::Service for RunHandEyeCalibration {
    type Request = RunHandEyeCalibration_Request;
    type Response = RunHandEyeCalibration_Response;

    fn get_type_support() -> *const std::ffi::c_void {
        // SAFETY: No preconditions for this function.
        unsafe { rosidl_typesupport_c__get_service_type_support_handle__rm_interfaces__srv__RunHandEyeCalibration() }
    }
}


