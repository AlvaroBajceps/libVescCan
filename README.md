# VESC CAN-Bus Communication

Modified for our ([Raptors PŁ](https://raptors.p.lodz.pl/)) needs  
Original document can be found [here](https://github.com/vedderb/bldc/blob/master/documentation/comm_can.md).  
Original document regarding Cubemars - [cubemars manual](https://www.cubemars.com/images/file/20240611/1718085712815162.pdf) 

## Timeout

By default there is a timeout that stops the motor when nothing has been received on the CAN-bus for more than 0.5 seconds. The timeout value can be changed. Setting it to 0 disables the timeout, but it is strongly recommended to not disable it in case something goes wrong with the communication link.  

To prevent timeouts it is recommended to keep sending the desired commands over and over at a fixed rate, e.g. 50 Hz.  

<!---
your comment goes here
and here
## Configuration
### Adressing
This mode can be accessed by setting `1` on 16th bit:

| **B28 - B17** | **B16** | **B15 - B8** | **B7 - B0** |
|-----------|--------|----------|---------|
| Unused | 1 | Setting ID | VESC ID |

> Default VESC ID is 0x00

> All CAN-commands have 4 data bytes which represent the argument for the commands as a 32-bit big endian signed number

### Configuration Commands

The following commands are available:

| **Command Name** | **Comm ID** | **Description** | **Range** |
|------|------|------|------|
| SETTING_VESC_ID | 0 | Setting up device ID | 0x00 - 0xFF |
| SETTING_STEPPER_TORQUE | 1 | Stepper driver max torque | 0x00 - 0xFF |
| SETTING_STEPPER_BREAKING_TORQUE | 2 | Stepper driver max breaking torque <br/> Setting `0` turns motor OFF when angle is reached | 0x00 - 0xFF |
| SETTING_STEPPER_GEAR_RATIO | 3 | Gear ratio for motor | 0x00 - 0xFFF |
| SETTING_STEPPER_STEP_MODE | 4 | Full Step => 0x00, Half Step => 0x08,	1/4th Step => 0x10 | 0x00, 0x08, 0x10 |
| SETTING_STEPPER_MAX_RPM | 5 | Self explanatory. `0` \- no limit | 0x00 - 0xFFF |
| SETTING_DIRECTION | 6 | `0` \- Clockwise; `1` \- Counter-clockwise | 0x00 - 0x01 |
| SETTING_LAST_STATE | 7 | Last driver state. <br/> `0` \- Off; `1` \- On | 0x00 - 0x01 |
| SETTING_ENCODER_ZERO_POS | 8 | Calibrated encoder zero-pos | 0x00000000 - 0xFFFFFFFF `(float)` |
| SETTING_ERR_ENCODER_REVS | 9 | Encoder revolutions count from zero-pos | 0x00000000 - 0xFFFFFFFF |

### Example
The command to set VESC ID has command id 0. The CAN-frame for setting the ID to 0x60 on VESC ID 0x00 would look like the following:

| **ID** | **B0** | **B1** | **B2** | **B3** |
|----|----|----|----|----|
| 0x010000 | 0x00 | 0x00 | 0x00 | 0x60 |

-->

## VESC Mode

The VESC CAN-mode supports basic commands that fit in a single CAN-frame as well as everything in https://github.com/vedderb/bldc/blob/master/comm/commands.c by splitting up the commands into multiple frames. The basic commands are described in this document.  

For a full and precise description of the protocol it is best to look at the source code https://github.com/vedderb/bldc/blob/master/comm/comm_can.c.

### Frame Format

The VESC CAN-frames all use 29-bit extended IDs. The ID of the receiver as well as the command ID is embedded in the extended ID of the CAN-frame as:

| **B28 - B16** | **B15 - B8** | **B7 - B0** |
|-----------|----------|---------|
| Unused | Command ID | VESC ID |

The data bytes in the CAN-frame depend on the command.

### Command (simple) Frames

All simple CAN-commands have 4 data bytes which represent the argument for the commands as a 32-bit big endian signed number with scaling.  

> Example:   
> The command VESC_COMMAND_SET_CURRENT has command id 1 and scaling 1000. The CAN-frame for setting the current to 51 A on VESC ID 23 would look like the following:  
> 
> | **ID** | **B0** | **B1** | **B2** | **B3** |
> |----|----|----|----|----|
> | 0x0117 | 0x00 | 0x00 | 0xC7 | 0x38 |

The following simple commands are available:

> Note:  
> Availability states VESC CAN-Bus devices capable of receiving given type of command.  

| **Command Name** | **Comm ID** | **Scaling** | **Unit** | **Description** | **Range** | **Availability** |
|------------|------------|---------|------|-------------|-------|--|
| VESC_COMMAND_SET_DUTY | 0 | 100000 | % / 100 | Duty Cycle | \-1.0 to 1.0 | BLDC, Cubemars |
| VESC_COMMAND_SET_CURRENT | 1 | 1000 | A | Motor Current | \-MOTOR_MAX to MOTOR_MAX | BLDC, Cubemars |
| VESC_COMMAND_SET_CURRENT_BRAKE | 2 | 1000 | A | Braking Current | \-MOTOR_MAX to MOTOR_MAX | BLDC, Cubemars |
| VESC_COMMAND_SET_RPM | 3 | 1 | RPM | RPM | \-MAX_RPM to MAX_RPM | BLDC, Cubemars |
| VESC_COMMAND_SET_POS | 4 | 1000000 | Degrees |  | 0 to 360 | BLDC, Cubemars* & Steppers |
| VESC_COMMAND_SET_ORIGIN | 5 | N/A | `VESC_SetOrigin_Command` | Uses `commandDataExB` | N/A | Cubemars |
| VESC_COMMAND_SET_POS_SPEED_LOOP | 6 | N/A | N/A | Uses `commandDataEx_{0,1,2}` | N/A | Cubemars |
| VESC_COMMAND_SET_CURRENT_REL | 10 | 100000 | % / 100 |  | \-1.0 to 1.0 | BLDC |
| VESC_COMMAND_SET_CURRENT_BRAKE_REL | 11 | 100000 | % / 100 |  | \-1.0 to 1.0 | BLDC |
| VESC_COMMAND_SET_CURRENT_HANDBRAKE | 12 | 1000 | A |  | \-MOTOR_MAX to MOTOR_MAX | BLDC |
| VESC_COMMAND_SET_CURRENT_HANDBRAKE_REL | 13 | 100000 | % / 100 |  | \-1.0 to 1.0 | BLDC |

> \* VESC_COMMAND_SET_POS for Cubemars is supported but not scaled correctly. Apply 1/100 of value to Cubemars. (Details in #10)

#### **VESC_COMMAND_SET_POS_SPEED_LOOP**

Well, this one isn't that simple..

| **Byte** | **Data** | **Unit** | **Scale** | **Availability** |
|------|------|------|-------|---------|
| B0 - B3 | Position | Deg | 10000 | Cubemars |
| B4 - B5 | Speed | ERPM | 0.1 | Cubemars |
| B6 - B7 | Acceleration | ERPM/s² | 0.1 | Cubemars |

### Status Frames

Status frames are sent continously by design. Each VESC CAN-Bus device can send any number of status frames at any (preferably constant) rate

> Note for BLDC:  
> To receive motor status (RPM, Voltage, Current etc.) status commands have to be activated.  
> Using two rates is useful for not congesting the bus with messages that are not needed as often, which can be sent at a lower rate.  

There are 10 different status messages available with the following data:

> Note:  
> Availability states VESC CAN-Bus devices capable of sending given type of status.  

| **Command Name** | **Command Id** | **Content** | **Availability** |
|--------------|------------|---------|---------|
| VESC_COMMAND_STATUS_1 | 9 | ERPM, Current | BLDC & Stepper |
| VESC_COMMAND_STATUS_2 | 14 | Ah Used, Ah Charged | BLDC |
| VESC_COMMAND_STATUS_3 | 15 | Wh Used, Wh Charged | BLDC |
| VESC_COMMAND_STATUS_4 | 16 | Temp Fet, Temp Motor, Current In, PID position | BLDC |
| VESC_COMMAND_STATUS_5 | 27 | Tachometer, Voltage In | BLDC |
| VESC_COMMAND_STATUS_6 | 28 | ADC1, ADC2, ADC3, PPM | BLDC |
| VESC_COMMAND_STATUS_7 | 29 | Precise Position | Stepper |
| VESC_COMMAND_STATUS_8 | 30 | WeightA, WeightB, WeightC, Ph, Distance | Probe |
| VESC_COMMAND_STATUS_9 | 31 | Voltage, Current, Temperature, Charge, Status | Hotswap |
| VESC_COMMAND_STATUS_10 | 32 | MCU States | ROS (ros-core) |
| VESC_COMMAND_STATUS_11 | 41 | Cubemars status | Cubemars |

The content of the status messages is encoded as follows:

#### **VESC_COMMAND_STATUS_1**

| **Byte** | **Data** | **Unit** | **Scale** | **Availability** |
|------|------|------|-------|---------|
| B0 - B3 | ERPM | RPM | 1 | BLDC & Stepper |
| B4 - B5 | Current | A | 10 | BLDC & Stepper |
| B6 - B7 | Duty Cycle | % / 100 | 1000 | BLDC |

#### **VESC_COMMAND_STATUS_2**

| **Byte** | **Data** | **Unit** | **Scale** | **Availability** |
|------|------|------|-------|---------|
| B0 - B3 | Amp Hours | Ah | 10000 | BLDC |
| B4 - B7 | Amp Hours Chg | Ah | 10000 | BLDC |

#### **VESC_COMMAND_STATUS_3**

| **Byte** | **Data** | **Unit** | **Scale** | **Availability** |
|------|------|------|-------|---------|
| B0 - B3 | Watt Hours | Wh | 10000 | BLDC |
| B4 - B7 | Watt Hours Chg | Wh | 10000 | BLDC |

#### **VESC_COMMAND_STATUS_4**

| **Byte** | **Data** | **Unit** | **Scale** | **Availability** |
|------|------|------|-------|---------|
| B0 - B1 | Temp FET | DegC | 10 | BLDC |
| B2 - B3 | Temp Motor | DegC | 10 | BLDC |
| B4 - B5 | Current In | A | 10 | BLDC |
| B6 - B7 | PID Pos | Deg | 50 | BLDC |

#### **VESC_COMMAND_STATUS_5**

| **Byte** | **Data** | **Unit** | **Scale** | **Availability** |
|------|------|------|-------|---------|
| B0 - B3 | Tachometer | EREV | 6 | BLDC |
| B4 - B5 | Volts In | V | 10 | BLDC |

#### **VESC_COMMAND_STATUS_7**

| **Byte** | **Data** | **Unit** | **Scale** | **Availability** |
|------|------|------|-------|---------|
| B0 - B3 | PrecisePos | Deg | 1000000 | Stepper |

#### **VESC_COMMAND_STATUS_8**

| **Byte** | **Data** | **Unit** | **Scale** | **Range** | **Availability** |
|------|------|------|-------|---------|---------|
| B0 - B1 | WeightA  | grams | 10 | 0:3276.7 g | Probe |
| B2 - B3 | WeightB  | grams | 10 | 0:3276.7 g | Probe |
| B4 - B5 | WeightC  | grams | 10 | 0:3276.7 g | Probe |
| B6      | Ph       | ph    | 10  | 0:25.5 | Probe |
| B7      | Distance | cm    | 1   | 0:255 | Probe |

#### **VESC_COMMAND_STATUS_9**

| **Byte** | **Data**                                               | **Unit**   | **Scale**    | **Range**         | **Availability**     |
|----------|--------------------------------------------------------|------------|--------------|-------------------|----------------------|
| B0 - B1  | Voltage                                                | V          | 1000         | 0:65.5 V          | Hotswap              |
| B2 - B3  | Current ( `+` &larr; charging, `–` &larr; discharging) | A          | 1000         | -32.768:32.767 A  | Hotswap              |
| B4       | Temperature                                            | deg C      | 1            | -128:127 deg C    | Hotswap              |
| B5       | Charge                                                 | %          | 1            | 0:100 %           | Hotswap              |
| B6       | Battery Status                                         | ENUM       | N/A          | N/A               | Hotswap              |
| B7       | Hotswap Status (hotswap master control): <br/><ul><li>b0 -> `hotswap_master` </li><li>b1 -> `hotswap_slaveA`</li><li>b2 -> `hotswap_slaveB`</li><li>b3 -> `drive_stop`</li><li>b4 -> `hotswap_gpio1`</li><li>b5 -> `hotswap_gpio2`</li><li>b6 -> `hotswap_gpio3`</li><li>b7 -> `hotswap_gpio4`</li></ul> | N/A         | N/A       | N/A            | Hotswap              |

#### **VESC_COMMAND_STATUS_10**
> Note:  
> Properly described [here](https://github.com/wisniax/RoverControlApp/wiki#-mqtt-rover-status)  

| **Byte** | **Data** | **Unit** | **Scale** | **Availability** |
|------|------|------|-------|---------|
| B0 | Flags: <br/><ul><li>b0 -> Pad Connected</li><li>b1 -> Motor Cut-Off button</li></ul> | N/A | N/A | ROS |
| B1 | Communication State | `VESC_Status_10_CommunicationState` | N/A | ROS |
| B2 | Control Mode   | `VESC_Status_10_ControlMode` | N/A | ROS |

#### **VESC_COMMAND_STATUS_11**

| **Byte** | **Data** | **Unit** | **Scale** | **Availability** |
|------|------|------|-------|---------|
| B0 - B1 | Position | Deg | 10 | Cubemars |
| B2 - B3 | Speed | ERPM | 0.1 | Cubemars |
| B4 - B5 | Current | A | 100 | Cubemars |
| B6 | Motor Temp | DegC | 1 | Cubemars |
| B7 | Error Code | `VESC_Status_11_ErrorCode` | N/A | Cubemars |

## Frequently Asked Questions (FAQ)

**What happens when sending commands outside of range?**
- When sending commands outside of range they will be truncated at the range limit. For example, if the maximum braking current is set to 50A and VESC_COMMAND_SET_CURRENT_BRAKE is sent with 60A the value will be truncated and 50A will be used.
