#[cfg(feature = "serde")]
use serde::{Deserialize, Serialize};



// Corresponds to rm_interfaces__msg__Armor

// This struct is not documented.
#[allow(missing_docs)]

#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct Armor {

    // This member is not documented.
    #[allow(missing_docs)]
    pub number: std::string::String,


    // This member is not documented.
    #[allow(missing_docs)]
    pub type_: std::string::String,


    // This member is not documented.
    #[allow(missing_docs)]
    pub distance_to_image_center: f32,


    // This member is not documented.
    #[allow(missing_docs)]
    pub pose: geometry_msgs::msg::Pose,

}



impl Default for Armor {
  fn default() -> Self {
    <Self as rosidl_runtime_rs::Message>::from_rmw_message(super::msg::rmw::Armor::default())
  }
}

impl rosidl_runtime_rs::Message for Armor {
  type RmwMsg = super::msg::rmw::Armor;

  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> {
    match msg_cow {
      std::borrow::Cow::Owned(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
        number: msg.number.as_str().into(),
        type_: msg.type_.as_str().into(),
        distance_to_image_center: msg.distance_to_image_center,
        pose: geometry_msgs::msg::Pose::into_rmw_message(std::borrow::Cow::Owned(msg.pose)).into_owned(),
      }),
      std::borrow::Cow::Borrowed(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
        number: msg.number.as_str().into(),
        type_: msg.type_.as_str().into(),
      distance_to_image_center: msg.distance_to_image_center,
        pose: geometry_msgs::msg::Pose::into_rmw_message(std::borrow::Cow::Borrowed(&msg.pose)).into_owned(),
      })
    }
  }

  fn from_rmw_message(msg: Self::RmwMsg) -> Self {
    Self {
      number: msg.number.to_string(),
      type_: msg.type_.to_string(),
      distance_to_image_center: msg.distance_to_image_center,
      pose: geometry_msgs::msg::Pose::from_rmw_message(msg.pose),
    }
  }
}


// Corresponds to rm_interfaces__msg__Armors

// This struct is not documented.
#[allow(missing_docs)]

#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct Armors {

    // This member is not documented.
    #[allow(missing_docs)]
    pub header: std_msgs::msg::Header,


    // This member is not documented.
    #[allow(missing_docs)]
    pub armors: Vec<super::msg::Armor>,

}



impl Default for Armors {
  fn default() -> Self {
    <Self as rosidl_runtime_rs::Message>::from_rmw_message(super::msg::rmw::Armors::default())
  }
}

impl rosidl_runtime_rs::Message for Armors {
  type RmwMsg = super::msg::rmw::Armors;

  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> {
    match msg_cow {
      std::borrow::Cow::Owned(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
        header: std_msgs::msg::Header::into_rmw_message(std::borrow::Cow::Owned(msg.header)).into_owned(),
        armors: msg.armors
          .into_iter()
          .map(|elem| super::msg::Armor::into_rmw_message(std::borrow::Cow::Owned(elem)).into_owned())
          .collect(),
      }),
      std::borrow::Cow::Borrowed(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
        header: std_msgs::msg::Header::into_rmw_message(std::borrow::Cow::Borrowed(&msg.header)).into_owned(),
        armors: msg.armors
          .iter()
          .map(|elem| super::msg::Armor::into_rmw_message(std::borrow::Cow::Borrowed(elem)).into_owned())
          .collect(),
      })
    }
  }

  fn from_rmw_message(msg: Self::RmwMsg) -> Self {
    Self {
      header: std_msgs::msg::Header::from_rmw_message(msg.header),
      armors: msg.armors
          .into_iter()
          .map(super::msg::Armor::from_rmw_message)
          .collect(),
    }
  }
}


// Corresponds to rm_interfaces__msg__Target

// This struct is not documented.
#[allow(missing_docs)]

#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct Target {

    // This member is not documented.
    #[allow(missing_docs)]
    pub header: std_msgs::msg::Header,


    // This member is not documented.
    #[allow(missing_docs)]
    pub tracking: bool,


    // This member is not documented.
    #[allow(missing_docs)]
    pub id: std::string::String,


    // This member is not documented.
    #[allow(missing_docs)]
    pub armors_num: i32,


    // This member is not documented.
    #[allow(missing_docs)]
    pub position: geometry_msgs::msg::Point,


    // This member is not documented.
    #[allow(missing_docs)]
    pub velocity: geometry_msgs::msg::Vector3,


    // This member is not documented.
    #[allow(missing_docs)]
    pub yaw: f64,


    // This member is not documented.
    #[allow(missing_docs)]
    pub v_yaw: f64,


    // This member is not documented.
    #[allow(missing_docs)]
    pub radius_1: f64,


    // This member is not documented.
    #[allow(missing_docs)]
    pub radius_2: f64,


    // This member is not documented.
    #[allow(missing_docs)]
    pub d_za: f64,


    // This member is not documented.
    #[allow(missing_docs)]
    pub d_zc: f64,


    // This member is not documented.
    #[allow(missing_docs)]
    pub yaw_diff: f64,


    // This member is not documented.
    #[allow(missing_docs)]
    pub position_diff: f64,

}



impl Default for Target {
  fn default() -> Self {
    <Self as rosidl_runtime_rs::Message>::from_rmw_message(super::msg::rmw::Target::default())
  }
}

impl rosidl_runtime_rs::Message for Target {
  type RmwMsg = super::msg::rmw::Target;

  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> {
    match msg_cow {
      std::borrow::Cow::Owned(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
        header: std_msgs::msg::Header::into_rmw_message(std::borrow::Cow::Owned(msg.header)).into_owned(),
        tracking: msg.tracking,
        id: msg.id.as_str().into(),
        armors_num: msg.armors_num,
        position: geometry_msgs::msg::Point::into_rmw_message(std::borrow::Cow::Owned(msg.position)).into_owned(),
        velocity: geometry_msgs::msg::Vector3::into_rmw_message(std::borrow::Cow::Owned(msg.velocity)).into_owned(),
        yaw: msg.yaw,
        v_yaw: msg.v_yaw,
        radius_1: msg.radius_1,
        radius_2: msg.radius_2,
        d_za: msg.d_za,
        d_zc: msg.d_zc,
        yaw_diff: msg.yaw_diff,
        position_diff: msg.position_diff,
      }),
      std::borrow::Cow::Borrowed(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
        header: std_msgs::msg::Header::into_rmw_message(std::borrow::Cow::Borrowed(&msg.header)).into_owned(),
      tracking: msg.tracking,
        id: msg.id.as_str().into(),
      armors_num: msg.armors_num,
        position: geometry_msgs::msg::Point::into_rmw_message(std::borrow::Cow::Borrowed(&msg.position)).into_owned(),
        velocity: geometry_msgs::msg::Vector3::into_rmw_message(std::borrow::Cow::Borrowed(&msg.velocity)).into_owned(),
      yaw: msg.yaw,
      v_yaw: msg.v_yaw,
      radius_1: msg.radius_1,
      radius_2: msg.radius_2,
      d_za: msg.d_za,
      d_zc: msg.d_zc,
      yaw_diff: msg.yaw_diff,
      position_diff: msg.position_diff,
      })
    }
  }

  fn from_rmw_message(msg: Self::RmwMsg) -> Self {
    Self {
      header: std_msgs::msg::Header::from_rmw_message(msg.header),
      tracking: msg.tracking,
      id: msg.id.to_string(),
      armors_num: msg.armors_num,
      position: geometry_msgs::msg::Point::from_rmw_message(msg.position),
      velocity: geometry_msgs::msg::Vector3::from_rmw_message(msg.velocity),
      yaw: msg.yaw,
      v_yaw: msg.v_yaw,
      radius_1: msg.radius_1,
      radius_2: msg.radius_2,
      d_za: msg.d_za,
      d_zc: msg.d_zc,
      yaw_diff: msg.yaw_diff,
      position_diff: msg.position_diff,
    }
  }
}


// Corresponds to rm_interfaces__msg__RuneTarget

// This struct is not documented.
#[allow(missing_docs)]

#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct RuneTarget {

    // This member is not documented.
    #[allow(missing_docs)]
    pub header: std_msgs::msg::Header,


    // This member is not documented.
    #[allow(missing_docs)]
    pub pts: [super::msg::Point2d; 5],


    // This member is not documented.
    #[allow(missing_docs)]
    pub is_lost: bool,


    // This member is not documented.
    #[allow(missing_docs)]
    pub is_big_rune: bool,

}



impl Default for RuneTarget {
  fn default() -> Self {
    <Self as rosidl_runtime_rs::Message>::from_rmw_message(super::msg::rmw::RuneTarget::default())
  }
}

impl rosidl_runtime_rs::Message for RuneTarget {
  type RmwMsg = super::msg::rmw::RuneTarget;

  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> {
    match msg_cow {
      std::borrow::Cow::Owned(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
        header: std_msgs::msg::Header::into_rmw_message(std::borrow::Cow::Owned(msg.header)).into_owned(),
        pts: msg.pts
          .map(|elem| super::msg::Point2d::into_rmw_message(std::borrow::Cow::Owned(elem)).into_owned()),
        is_lost: msg.is_lost,
        is_big_rune: msg.is_big_rune,
      }),
      std::borrow::Cow::Borrowed(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
        header: std_msgs::msg::Header::into_rmw_message(std::borrow::Cow::Borrowed(&msg.header)).into_owned(),
        pts: msg.pts
          .iter()
          .map(|elem| super::msg::Point2d::into_rmw_message(std::borrow::Cow::Borrowed(elem)).into_owned())
          .collect::<Vec<_>>()
          .try_into()
          .unwrap(),
      is_lost: msg.is_lost,
      is_big_rune: msg.is_big_rune,
      })
    }
  }

  fn from_rmw_message(msg: Self::RmwMsg) -> Self {
    Self {
      header: std_msgs::msg::Header::from_rmw_message(msg.header),
      pts: msg.pts
        .map(super::msg::Point2d::from_rmw_message),
      is_lost: msg.is_lost,
      is_big_rune: msg.is_big_rune,
    }
  }
}


// Corresponds to rm_interfaces__msg__Point2d

// This struct is not documented.
#[allow(missing_docs)]

#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct Point2d {

    // This member is not documented.
    #[allow(missing_docs)]
    pub x: f32,


    // This member is not documented.
    #[allow(missing_docs)]
    pub y: f32,

}



impl Default for Point2d {
  fn default() -> Self {
    <Self as rosidl_runtime_rs::Message>::from_rmw_message(super::msg::rmw::Point2d::default())
  }
}

impl rosidl_runtime_rs::Message for Point2d {
  type RmwMsg = super::msg::rmw::Point2d;

  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> {
    match msg_cow {
      std::borrow::Cow::Owned(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
        x: msg.x,
        y: msg.y,
      }),
      std::borrow::Cow::Borrowed(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
      x: msg.x,
      y: msg.y,
      })
    }
  }

  fn from_rmw_message(msg: Self::RmwMsg) -> Self {
    Self {
      x: msg.x,
      y: msg.y,
    }
  }
}


// Corresponds to rm_interfaces__msg__GimbalCmd

// This struct is not documented.
#[allow(missing_docs)]

#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct GimbalCmd {

    // This member is not documented.
    #[allow(missing_docs)]
    pub header: std_msgs::msg::Header,


    // This member is not documented.
    #[allow(missing_docs)]
    pub pitch: f64,


    // This member is not documented.
    #[allow(missing_docs)]
    pub yaw: f64,


    // This member is not documented.
    #[allow(missing_docs)]
    pub yaw_diff: f64,


    // This member is not documented.
    #[allow(missing_docs)]
    pub pitch_diff: f64,


    // This member is not documented.
    #[allow(missing_docs)]
    pub distance: f64,


    // This member is not documented.
    #[allow(missing_docs)]
    pub fire_advice: bool,

}



impl Default for GimbalCmd {
  fn default() -> Self {
    <Self as rosidl_runtime_rs::Message>::from_rmw_message(super::msg::rmw::GimbalCmd::default())
  }
}

impl rosidl_runtime_rs::Message for GimbalCmd {
  type RmwMsg = super::msg::rmw::GimbalCmd;

  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> {
    match msg_cow {
      std::borrow::Cow::Owned(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
        header: std_msgs::msg::Header::into_rmw_message(std::borrow::Cow::Owned(msg.header)).into_owned(),
        pitch: msg.pitch,
        yaw: msg.yaw,
        yaw_diff: msg.yaw_diff,
        pitch_diff: msg.pitch_diff,
        distance: msg.distance,
        fire_advice: msg.fire_advice,
      }),
      std::borrow::Cow::Borrowed(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
        header: std_msgs::msg::Header::into_rmw_message(std::borrow::Cow::Borrowed(&msg.header)).into_owned(),
      pitch: msg.pitch,
      yaw: msg.yaw,
      yaw_diff: msg.yaw_diff,
      pitch_diff: msg.pitch_diff,
      distance: msg.distance,
      fire_advice: msg.fire_advice,
      })
    }
  }

  fn from_rmw_message(msg: Self::RmwMsg) -> Self {
    Self {
      header: std_msgs::msg::Header::from_rmw_message(msg.header),
      pitch: msg.pitch,
      yaw: msg.yaw,
      yaw_diff: msg.yaw_diff,
      pitch_diff: msg.pitch_diff,
      distance: msg.distance,
      fire_advice: msg.fire_advice,
    }
  }
}


// Corresponds to rm_interfaces__msg__ChassisCmd

// This struct is not documented.
#[allow(missing_docs)]

#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct ChassisCmd {

    // This member is not documented.
    #[allow(missing_docs)]
    pub header: std_msgs::msg::Header,


    // This member is not documented.
    #[allow(missing_docs)]
    pub is_spining: bool,


    // This member is not documented.
    #[allow(missing_docs)]
    pub is_navigating: bool,


    // This member is not documented.
    #[allow(missing_docs)]
    pub twist: geometry_msgs::msg::Twist,

}



impl Default for ChassisCmd {
  fn default() -> Self {
    <Self as rosidl_runtime_rs::Message>::from_rmw_message(super::msg::rmw::ChassisCmd::default())
  }
}

impl rosidl_runtime_rs::Message for ChassisCmd {
  type RmwMsg = super::msg::rmw::ChassisCmd;

  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> {
    match msg_cow {
      std::borrow::Cow::Owned(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
        header: std_msgs::msg::Header::into_rmw_message(std::borrow::Cow::Owned(msg.header)).into_owned(),
        is_spining: msg.is_spining,
        is_navigating: msg.is_navigating,
        twist: geometry_msgs::msg::Twist::into_rmw_message(std::borrow::Cow::Owned(msg.twist)).into_owned(),
      }),
      std::borrow::Cow::Borrowed(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
        header: std_msgs::msg::Header::into_rmw_message(std::borrow::Cow::Borrowed(&msg.header)).into_owned(),
      is_spining: msg.is_spining,
      is_navigating: msg.is_navigating,
        twist: geometry_msgs::msg::Twist::into_rmw_message(std::borrow::Cow::Borrowed(&msg.twist)).into_owned(),
      })
    }
  }

  fn from_rmw_message(msg: Self::RmwMsg) -> Self {
    Self {
      header: std_msgs::msg::Header::from_rmw_message(msg.header),
      is_spining: msg.is_spining,
      is_navigating: msg.is_navigating,
      twist: geometry_msgs::msg::Twist::from_rmw_message(msg.twist),
    }
  }
}


// Corresponds to rm_interfaces__msg__DebugLight

// This struct is not documented.
#[allow(missing_docs)]

#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct DebugLight {

    // This member is not documented.
    #[allow(missing_docs)]
    pub center_x: i32,


    // This member is not documented.
    #[allow(missing_docs)]
    pub is_light: bool,


    // This member is not documented.
    #[allow(missing_docs)]
    pub ratio: f32,


    // This member is not documented.
    #[allow(missing_docs)]
    pub angle: f32,

}



impl Default for DebugLight {
  fn default() -> Self {
    <Self as rosidl_runtime_rs::Message>::from_rmw_message(super::msg::rmw::DebugLight::default())
  }
}

impl rosidl_runtime_rs::Message for DebugLight {
  type RmwMsg = super::msg::rmw::DebugLight;

  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> {
    match msg_cow {
      std::borrow::Cow::Owned(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
        center_x: msg.center_x,
        is_light: msg.is_light,
        ratio: msg.ratio,
        angle: msg.angle,
      }),
      std::borrow::Cow::Borrowed(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
      center_x: msg.center_x,
      is_light: msg.is_light,
      ratio: msg.ratio,
      angle: msg.angle,
      })
    }
  }

  fn from_rmw_message(msg: Self::RmwMsg) -> Self {
    Self {
      center_x: msg.center_x,
      is_light: msg.is_light,
      ratio: msg.ratio,
      angle: msg.angle,
    }
  }
}


// Corresponds to rm_interfaces__msg__DebugLights

// This struct is not documented.
#[allow(missing_docs)]

#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct DebugLights {

    // This member is not documented.
    #[allow(missing_docs)]
    pub data: Vec<super::msg::DebugLight>,

}



impl Default for DebugLights {
  fn default() -> Self {
    <Self as rosidl_runtime_rs::Message>::from_rmw_message(super::msg::rmw::DebugLights::default())
  }
}

impl rosidl_runtime_rs::Message for DebugLights {
  type RmwMsg = super::msg::rmw::DebugLights;

  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> {
    match msg_cow {
      std::borrow::Cow::Owned(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
        data: msg.data
          .into_iter()
          .map(|elem| super::msg::DebugLight::into_rmw_message(std::borrow::Cow::Owned(elem)).into_owned())
          .collect(),
      }),
      std::borrow::Cow::Borrowed(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
        data: msg.data
          .iter()
          .map(|elem| super::msg::DebugLight::into_rmw_message(std::borrow::Cow::Borrowed(elem)).into_owned())
          .collect(),
      })
    }
  }

  fn from_rmw_message(msg: Self::RmwMsg) -> Self {
    Self {
      data: msg.data
          .into_iter()
          .map(super::msg::DebugLight::from_rmw_message)
          .collect(),
    }
  }
}


// Corresponds to rm_interfaces__msg__DebugArmor

// This struct is not documented.
#[allow(missing_docs)]

#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct DebugArmor {

    // This member is not documented.
    #[allow(missing_docs)]
    pub center_x: i32,


    // This member is not documented.
    #[allow(missing_docs)]
    pub type_: std::string::String,


    // This member is not documented.
    #[allow(missing_docs)]
    pub light_ratio: f32,


    // This member is not documented.
    #[allow(missing_docs)]
    pub center_distance: f32,


    // This member is not documented.
    #[allow(missing_docs)]
    pub angle: f32,

}



impl Default for DebugArmor {
  fn default() -> Self {
    <Self as rosidl_runtime_rs::Message>::from_rmw_message(super::msg::rmw::DebugArmor::default())
  }
}

impl rosidl_runtime_rs::Message for DebugArmor {
  type RmwMsg = super::msg::rmw::DebugArmor;

  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> {
    match msg_cow {
      std::borrow::Cow::Owned(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
        center_x: msg.center_x,
        type_: msg.type_.as_str().into(),
        light_ratio: msg.light_ratio,
        center_distance: msg.center_distance,
        angle: msg.angle,
      }),
      std::borrow::Cow::Borrowed(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
      center_x: msg.center_x,
        type_: msg.type_.as_str().into(),
      light_ratio: msg.light_ratio,
      center_distance: msg.center_distance,
      angle: msg.angle,
      })
    }
  }

  fn from_rmw_message(msg: Self::RmwMsg) -> Self {
    Self {
      center_x: msg.center_x,
      type_: msg.type_.to_string(),
      light_ratio: msg.light_ratio,
      center_distance: msg.center_distance,
      angle: msg.angle,
    }
  }
}


// Corresponds to rm_interfaces__msg__DebugArmors

// This struct is not documented.
#[allow(missing_docs)]

#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct DebugArmors {

    // This member is not documented.
    #[allow(missing_docs)]
    pub data: Vec<super::msg::DebugArmor>,

}



impl Default for DebugArmors {
  fn default() -> Self {
    <Self as rosidl_runtime_rs::Message>::from_rmw_message(super::msg::rmw::DebugArmors::default())
  }
}

impl rosidl_runtime_rs::Message for DebugArmors {
  type RmwMsg = super::msg::rmw::DebugArmors;

  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> {
    match msg_cow {
      std::borrow::Cow::Owned(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
        data: msg.data
          .into_iter()
          .map(|elem| super::msg::DebugArmor::into_rmw_message(std::borrow::Cow::Owned(elem)).into_owned())
          .collect(),
      }),
      std::borrow::Cow::Borrowed(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
        data: msg.data
          .iter()
          .map(|elem| super::msg::DebugArmor::into_rmw_message(std::borrow::Cow::Borrowed(elem)).into_owned())
          .collect(),
      })
    }
  }

  fn from_rmw_message(msg: Self::RmwMsg) -> Self {
    Self {
      data: msg.data
          .into_iter()
          .map(super::msg::DebugArmor::from_rmw_message)
          .collect(),
    }
  }
}


// Corresponds to rm_interfaces__msg__DebugRuneAngle

// This struct is not documented.
#[allow(missing_docs)]

#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct DebugRuneAngle {

    // This member is not documented.
    #[allow(missing_docs)]
    pub header: std_msgs::msg::Header,


    // This member is not documented.
    #[allow(missing_docs)]
    pub data: f64,

}



impl Default for DebugRuneAngle {
  fn default() -> Self {
    <Self as rosidl_runtime_rs::Message>::from_rmw_message(super::msg::rmw::DebugRuneAngle::default())
  }
}

impl rosidl_runtime_rs::Message for DebugRuneAngle {
  type RmwMsg = super::msg::rmw::DebugRuneAngle;

  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> {
    match msg_cow {
      std::borrow::Cow::Owned(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
        header: std_msgs::msg::Header::into_rmw_message(std::borrow::Cow::Owned(msg.header)).into_owned(),
        data: msg.data,
      }),
      std::borrow::Cow::Borrowed(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
        header: std_msgs::msg::Header::into_rmw_message(std::borrow::Cow::Borrowed(&msg.header)).into_owned(),
      data: msg.data,
      })
    }
  }

  fn from_rmw_message(msg: Self::RmwMsg) -> Self {
    Self {
      header: std_msgs::msg::Header::from_rmw_message(msg.header),
      data: msg.data,
    }
  }
}


// Corresponds to rm_interfaces__msg__Measurement

// This struct is not documented.
#[allow(missing_docs)]

#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct Measurement {

    // This member is not documented.
    #[allow(missing_docs)]
    pub x1: f64,


    // This member is not documented.
    #[allow(missing_docs)]
    pub y1: f64,


    // This member is not documented.
    #[allow(missing_docs)]
    pub z1: f64,


    // This member is not documented.
    #[allow(missing_docs)]
    pub yaw1: f64,


    // This member is not documented.
    #[allow(missing_docs)]
    pub x2: f64,


    // This member is not documented.
    #[allow(missing_docs)]
    pub y2: f64,


    // This member is not documented.
    #[allow(missing_docs)]
    pub z2: f64,


    // This member is not documented.
    #[allow(missing_docs)]
    pub yaw2: f64,

}



impl Default for Measurement {
  fn default() -> Self {
    <Self as rosidl_runtime_rs::Message>::from_rmw_message(super::msg::rmw::Measurement::default())
  }
}

impl rosidl_runtime_rs::Message for Measurement {
  type RmwMsg = super::msg::rmw::Measurement;

  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> {
    match msg_cow {
      std::borrow::Cow::Owned(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
        x1: msg.x1,
        y1: msg.y1,
        z1: msg.z1,
        yaw1: msg.yaw1,
        x2: msg.x2,
        y2: msg.y2,
        z2: msg.z2,
        yaw2: msg.yaw2,
      }),
      std::borrow::Cow::Borrowed(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
      x1: msg.x1,
      y1: msg.y1,
      z1: msg.z1,
      yaw1: msg.yaw1,
      x2: msg.x2,
      y2: msg.y2,
      z2: msg.z2,
      yaw2: msg.yaw2,
      })
    }
  }

  fn from_rmw_message(msg: Self::RmwMsg) -> Self {
    Self {
      x1: msg.x1,
      y1: msg.y1,
      z1: msg.z1,
      yaw1: msg.yaw1,
      x2: msg.x2,
      y2: msg.y2,
      z2: msg.z2,
      yaw2: msg.yaw2,
    }
  }
}


// Corresponds to rm_interfaces__msg__JudgeSystemData

// This struct is not documented.
#[allow(missing_docs)]

#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct JudgeSystemData {

    // This member is not documented.
    #[allow(missing_docs)]
    pub game_status: u8,


    // This member is not documented.
    #[allow(missing_docs)]
    pub remaining_time: i16,


    // This member is not documented.
    #[allow(missing_docs)]
    pub blood: i16,


    // This member is not documented.
    #[allow(missing_docs)]
    pub outpost_hp: i16,


    // This member is not documented.
    #[allow(missing_docs)]
    pub operator_command: super::msg::OperatorCommand,

}



impl Default for JudgeSystemData {
  fn default() -> Self {
    <Self as rosidl_runtime_rs::Message>::from_rmw_message(super::msg::rmw::JudgeSystemData::default())
  }
}

impl rosidl_runtime_rs::Message for JudgeSystemData {
  type RmwMsg = super::msg::rmw::JudgeSystemData;

  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> {
    match msg_cow {
      std::borrow::Cow::Owned(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
        game_status: msg.game_status,
        remaining_time: msg.remaining_time,
        blood: msg.blood,
        outpost_hp: msg.outpost_hp,
        operator_command: super::msg::OperatorCommand::into_rmw_message(std::borrow::Cow::Owned(msg.operator_command)).into_owned(),
      }),
      std::borrow::Cow::Borrowed(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
      game_status: msg.game_status,
      remaining_time: msg.remaining_time,
      blood: msg.blood,
      outpost_hp: msg.outpost_hp,
        operator_command: super::msg::OperatorCommand::into_rmw_message(std::borrow::Cow::Borrowed(&msg.operator_command)).into_owned(),
      })
    }
  }

  fn from_rmw_message(msg: Self::RmwMsg) -> Self {
    Self {
      game_status: msg.game_status,
      remaining_time: msg.remaining_time,
      blood: msg.blood,
      outpost_hp: msg.outpost_hp,
      operator_command: super::msg::OperatorCommand::from_rmw_message(msg.operator_command),
    }
  }
}


// Corresponds to rm_interfaces__msg__OperatorCommand

// This struct is not documented.
#[allow(missing_docs)]

#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct OperatorCommand {

    // This member is not documented.
    #[allow(missing_docs)]
    pub is_retreating: u8,


    // This member is not documented.
    #[allow(missing_docs)]
    pub is_drone_avoiding: u8,


    // This member is not documented.
    #[allow(missing_docs)]
    pub is_outpost_attacking: u8,

}



impl Default for OperatorCommand {
  fn default() -> Self {
    <Self as rosidl_runtime_rs::Message>::from_rmw_message(super::msg::rmw::OperatorCommand::default())
  }
}

impl rosidl_runtime_rs::Message for OperatorCommand {
  type RmwMsg = super::msg::rmw::OperatorCommand;

  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> {
    match msg_cow {
      std::borrow::Cow::Owned(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
        is_retreating: msg.is_retreating,
        is_drone_avoiding: msg.is_drone_avoiding,
        is_outpost_attacking: msg.is_outpost_attacking,
      }),
      std::borrow::Cow::Borrowed(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
      is_retreating: msg.is_retreating,
      is_drone_avoiding: msg.is_drone_avoiding,
      is_outpost_attacking: msg.is_outpost_attacking,
      })
    }
  }

  fn from_rmw_message(msg: Self::RmwMsg) -> Self {
    Self {
      is_retreating: msg.is_retreating,
      is_drone_avoiding: msg.is_drone_avoiding,
      is_outpost_attacking: msg.is_outpost_attacking,
    }
  }
}


// Corresponds to rm_interfaces__msg__SerialReceiveData

// This struct is not documented.
#[allow(missing_docs)]

#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct SerialReceiveData {

    // This member is not documented.
    #[allow(missing_docs)]
    pub header: std_msgs::msg::Header,


    // This member is not documented.
    #[allow(missing_docs)]
    pub mode: u8,


    // This member is not documented.
    #[allow(missing_docs)]
    pub bullet_speed: f32,


    // This member is not documented.
    #[allow(missing_docs)]
    pub roll: f32,


    // This member is not documented.
    #[allow(missing_docs)]
    pub yaw: f32,


    // This member is not documented.
    #[allow(missing_docs)]
    pub pitch: f32,


    // This member is not documented.
    #[allow(missing_docs)]
    pub judge_system_data: super::msg::JudgeSystemData,

}



impl Default for SerialReceiveData {
  fn default() -> Self {
    <Self as rosidl_runtime_rs::Message>::from_rmw_message(super::msg::rmw::SerialReceiveData::default())
  }
}

impl rosidl_runtime_rs::Message for SerialReceiveData {
  type RmwMsg = super::msg::rmw::SerialReceiveData;

  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> {
    match msg_cow {
      std::borrow::Cow::Owned(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
        header: std_msgs::msg::Header::into_rmw_message(std::borrow::Cow::Owned(msg.header)).into_owned(),
        mode: msg.mode,
        bullet_speed: msg.bullet_speed,
        roll: msg.roll,
        yaw: msg.yaw,
        pitch: msg.pitch,
        judge_system_data: super::msg::JudgeSystemData::into_rmw_message(std::borrow::Cow::Owned(msg.judge_system_data)).into_owned(),
      }),
      std::borrow::Cow::Borrowed(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
        header: std_msgs::msg::Header::into_rmw_message(std::borrow::Cow::Borrowed(&msg.header)).into_owned(),
      mode: msg.mode,
      bullet_speed: msg.bullet_speed,
      roll: msg.roll,
      yaw: msg.yaw,
      pitch: msg.pitch,
        judge_system_data: super::msg::JudgeSystemData::into_rmw_message(std::borrow::Cow::Borrowed(&msg.judge_system_data)).into_owned(),
      })
    }
  }

  fn from_rmw_message(msg: Self::RmwMsg) -> Self {
    Self {
      header: std_msgs::msg::Header::from_rmw_message(msg.header),
      mode: msg.mode,
      bullet_speed: msg.bullet_speed,
      roll: msg.roll,
      yaw: msg.yaw,
      pitch: msg.pitch,
      judge_system_data: super::msg::JudgeSystemData::from_rmw_message(msg.judge_system_data),
    }
  }
}


// Corresponds to rm_interfaces__msg__PlanGimbalCmd

// This struct is not documented.
#[allow(missing_docs)]

#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct PlanGimbalCmd {

    // This member is not documented.
    #[allow(missing_docs)]
    pub header: std_msgs::msg::Header,


    // This member is not documented.
    #[allow(missing_docs)]
    pub ref_yaw: f32,


    // This member is not documented.
    #[allow(missing_docs)]
    pub ref_yaw_vel: f32,


    // This member is not documented.
    #[allow(missing_docs)]
    pub ref_yaw_acc: f32,


    // This member is not documented.
    #[allow(missing_docs)]
    pub ref_pitch: f32,


    // This member is not documented.
    #[allow(missing_docs)]
    pub ref_pitch_vel: f32,


    // This member is not documented.
    #[allow(missing_docs)]
    pub ref_pitch_acc: f32,

}



impl Default for PlanGimbalCmd {
  fn default() -> Self {
    <Self as rosidl_runtime_rs::Message>::from_rmw_message(super::msg::rmw::PlanGimbalCmd::default())
  }
}

impl rosidl_runtime_rs::Message for PlanGimbalCmd {
  type RmwMsg = super::msg::rmw::PlanGimbalCmd;

  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> {
    match msg_cow {
      std::borrow::Cow::Owned(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
        header: std_msgs::msg::Header::into_rmw_message(std::borrow::Cow::Owned(msg.header)).into_owned(),
        ref_yaw: msg.ref_yaw,
        ref_yaw_vel: msg.ref_yaw_vel,
        ref_yaw_acc: msg.ref_yaw_acc,
        ref_pitch: msg.ref_pitch,
        ref_pitch_vel: msg.ref_pitch_vel,
        ref_pitch_acc: msg.ref_pitch_acc,
      }),
      std::borrow::Cow::Borrowed(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
        header: std_msgs::msg::Header::into_rmw_message(std::borrow::Cow::Borrowed(&msg.header)).into_owned(),
      ref_yaw: msg.ref_yaw,
      ref_yaw_vel: msg.ref_yaw_vel,
      ref_yaw_acc: msg.ref_yaw_acc,
      ref_pitch: msg.ref_pitch,
      ref_pitch_vel: msg.ref_pitch_vel,
      ref_pitch_acc: msg.ref_pitch_acc,
      })
    }
  }

  fn from_rmw_message(msg: Self::RmwMsg) -> Self {
    Self {
      header: std_msgs::msg::Header::from_rmw_message(msg.header),
      ref_yaw: msg.ref_yaw,
      ref_yaw_vel: msg.ref_yaw_vel,
      ref_yaw_acc: msg.ref_yaw_acc,
      ref_pitch: msg.ref_pitch,
      ref_pitch_vel: msg.ref_pitch_vel,
      ref_pitch_acc: msg.ref_pitch_acc,
    }
  }
}


