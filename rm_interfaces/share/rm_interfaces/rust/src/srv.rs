#[cfg(feature = "serde")]
use serde::{Deserialize, Serialize};




// Corresponds to rm_interfaces__srv__SetMode_Request

// This struct is not documented.
#[allow(missing_docs)]

#[allow(non_camel_case_types)]
#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct SetMode_Request {
    /// 0:自瞄红 1:自瞄蓝 2:小符红 3:小符蓝 4：大符红 5：大符蓝
    pub mode: u8,

}



impl Default for SetMode_Request {
  fn default() -> Self {
    <Self as rosidl_runtime_rs::Message>::from_rmw_message(super::srv::rmw::SetMode_Request::default())
  }
}

impl rosidl_runtime_rs::Message for SetMode_Request {
  type RmwMsg = super::srv::rmw::SetMode_Request;

  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> {
    match msg_cow {
      std::borrow::Cow::Owned(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
        mode: msg.mode,
      }),
      std::borrow::Cow::Borrowed(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
      mode: msg.mode,
      })
    }
  }

  fn from_rmw_message(msg: Self::RmwMsg) -> Self {
    Self {
      mode: msg.mode,
    }
  }
}


// Corresponds to rm_interfaces__srv__SetMode_Response

// This struct is not documented.
#[allow(missing_docs)]

#[allow(non_camel_case_types)]
#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct SetMode_Response {
    /// indicate successful run of triggered service
    pub success: bool,

    /// informational, e.g. for error messages
    pub message: std::string::String,

}



impl Default for SetMode_Response {
  fn default() -> Self {
    <Self as rosidl_runtime_rs::Message>::from_rmw_message(super::srv::rmw::SetMode_Response::default())
  }
}

impl rosidl_runtime_rs::Message for SetMode_Response {
  type RmwMsg = super::srv::rmw::SetMode_Response;

  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> {
    match msg_cow {
      std::borrow::Cow::Owned(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
        success: msg.success,
        message: msg.message.as_str().into(),
      }),
      std::borrow::Cow::Borrowed(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
      success: msg.success,
        message: msg.message.as_str().into(),
      })
    }
  }

  fn from_rmw_message(msg: Self::RmwMsg) -> Self {
    Self {
      success: msg.success,
      message: msg.message.to_string(),
    }
  }
}


// Corresponds to rm_interfaces__srv__RunHandEyeCalibration_Request

// This struct is not documented.
#[allow(missing_docs)]

#[allow(non_camel_case_types)]
#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct RunHandEyeCalibration_Request {

    // This member is not documented.
    #[allow(missing_docs)]
    pub structure_needs_at_least_one_member: u8,

}



impl Default for RunHandEyeCalibration_Request {
  fn default() -> Self {
    <Self as rosidl_runtime_rs::Message>::from_rmw_message(super::srv::rmw::RunHandEyeCalibration_Request::default())
  }
}

impl rosidl_runtime_rs::Message for RunHandEyeCalibration_Request {
  type RmwMsg = super::srv::rmw::RunHandEyeCalibration_Request;

  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> {
    match msg_cow {
      std::borrow::Cow::Owned(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
        structure_needs_at_least_one_member: msg.structure_needs_at_least_one_member,
      }),
      std::borrow::Cow::Borrowed(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
      structure_needs_at_least_one_member: msg.structure_needs_at_least_one_member,
      })
    }
  }

  fn from_rmw_message(msg: Self::RmwMsg) -> Self {
    Self {
      structure_needs_at_least_one_member: msg.structure_needs_at_least_one_member,
    }
  }
}


// Corresponds to rm_interfaces__srv__RunHandEyeCalibration_Response

// This struct is not documented.
#[allow(missing_docs)]

#[allow(non_camel_case_types)]
#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct RunHandEyeCalibration_Response {

    // This member is not documented.
    #[allow(missing_docs)]
    pub success: bool,


    // This member is not documented.
    #[allow(missing_docs)]
    pub yaml_path: std::string::String,

}



impl Default for RunHandEyeCalibration_Response {
  fn default() -> Self {
    <Self as rosidl_runtime_rs::Message>::from_rmw_message(super::srv::rmw::RunHandEyeCalibration_Response::default())
  }
}

impl rosidl_runtime_rs::Message for RunHandEyeCalibration_Response {
  type RmwMsg = super::srv::rmw::RunHandEyeCalibration_Response;

  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> {
    match msg_cow {
      std::borrow::Cow::Owned(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
        success: msg.success,
        yaml_path: msg.yaml_path.as_str().into(),
      }),
      std::borrow::Cow::Borrowed(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
      success: msg.success,
        yaml_path: msg.yaml_path.as_str().into(),
      })
    }
  }

  fn from_rmw_message(msg: Self::RmwMsg) -> Self {
    Self {
      success: msg.success,
      yaml_path: msg.yaml_path.to_string(),
    }
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


