# VESC CAN-Bus Communication

Modified for our ([Raptors PL](https://raptors.p.lodz.pl/)) needs<br>
Original document can be found [here](https://github.com/vedderb/bldc/blob/master/documentation/comm_can.md).  
Original document regarding Cubemars - [cubemars manual](https://www.cubemars.com/images/file/20240611/1718085712815162.pdf) 

## Timeout

The motor-command timeout below is separate from the device-configuration behaviour described under SET_CONFIG.

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

The VESC CAN-frames use 29-bit extended IDs. The command ID and device ID are embedded in the extended ID as:

| **B28 - B16** | **B15 - B8** | **B7 - B0** |
|-----------|----------|---------|
| Unused | Command ID | VESC ID |

The identifier is `(command ID << 8) | device ID`. For commands, the device ID identifies the receiver; for status, it identifies the publisher or battery slot. Multi-byte integers are big-endian unless stated otherwise. Bit 0 is the least-significant bit.

Payload length and format depend on the command and device.

### Command (simple) Frames

Scalar motor commands carry a 32-bit big-endian signed argument with scaling. Commands with dedicated payloads, including SET_POS_SPEED_LOOP, MUX_CAMSEL, and SET_CONFIG, use the layouts below.

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
| VESC_COMMAND_SET_CONFIG | 103 / 0x67 | N/A | N/A | Two device-specific configuration bytes | DLC 2 | [Profiles](#vesc_command_set_config) |
| VESC_COMMAND_MUX_CAMSEL | 34 | N/A | Camera number | CameraSelect | N/A | Analog MUX |

> \* VESC_COMMAND_SET_POS for Cubemars is supported but not scaled correctly. Apply 1/100 of value to Cubemars. (Details in #10)

#### **VESC_COMMAND_SET_POS_SPEED_LOOP**

Well, this one isn't that simple..

| **Byte** | **Data** | **Unit** | **Scale** | **Availability** |
|------|------|------|-------|---------|
| B0 - B3 | Position | Deg | 10000 | Cubemars |
| B4 - B5 | Speed | ERPM | 0.1 | Cubemars |
| B6 - B7 | Acceleration | ERPM/s² | 0.1 | Cubemars |

#### **VESC_COMMAND_MUX_CAMSEL**

<table>
  <thead>
    <tr>
      <th>Byte</th>
      <th>Data</th>
      <th>Unit</th>
      <th>Scale</th>
      <th>Availability</th>
    </tr>
  </thead>
  <tbody>
    <tr>
      <td>B0</td>
      <td>CameraSelect</td>
      <td>Number</td>
      <td>1</td>
      <td>N/A</td>
    </tr>
  </tbody>
</table>

#### **VESC_COMMAND_SET_CONFIG**

Device-specific configuration. Payload length: **2 bytes**.

The latest valid settings from any supported interface remain active without a timeout. Reset behaviour is device-specific.

##### **HotSwap**

Receiver: **0x92**. CAN ID: **0x6792**.

<table>
  <thead>
    <tr>
      <th>Byte</th>
      <th>Data</th>
      <th>Unit</th>
      <th>Scale</th>
      <th>Availability</th>
    </tr>
  </thead>
  <tbody>
    <tr>
      <td>B0</td>
      <td>Control bits
        <details>
          <summary>Bit-map</summary>
          <ul>
            <li>b0 -> left_HS</li>
            <li>b1 -> center_HS</li>
            <li>b2 -> right_HS</li>
            <li>b3 -> AUTO</li>
            <li>b4 -> GPIO1 / S2 output level, if configured as output</li>
            <li>b5 -> resetLeftBattery</li>
            <li>b6 -> resetCenterBattery</li>
            <li>b7 -> resetRightBattery</li>
          </ul>
        </details>
      </td>
      <td>N/A</td>
      <td>N/A</td>
      <td>Hotswap</td>
    </tr>
    <tr>
      <td>B1</td>
      <td>eFuse enable (future): 0 = OFF, 1 = ON</td>
      <td>Boolean</td>
      <td>1</td>
      <td>Hotswap</td>
    </tr>
  </tbody>
</table>

With resistors: AUTO ignores manual HS bits; manual mode bypasses automatic battery checks. Without resistors, all HS remain enabled and individual switching is blocked.

B0 bits 0–4 and B1 set the complete desired state; zero means OFF/LOW.

GPIO1 and battery-reset requests are independent of AUTO.

Battery reset bits request one Device Reset (`0x0041`) attempt on a 0→1 edge; send zero to rearm. Fault clearance is not guaranteed.

On reset hotswap should start in automatic mode if resistors are present, if not start in all HS enabled (tournament mode).

##### **Analog MUX**

Receiver: **0xA0**. CAN ID: **0x67A0**.

<table>
  <thead>
    <tr>
      <th>Byte</th>
      <th>Data</th>
      <th>Unit</th>
      <th>Scale</th>
      <th>Availability</th>
    </tr>
  </thead>
  <tbody>
    <tr>
      <td>B0</td>
      <td>Settings
        <details>
          <summary>Bit-map</summary>
          <ul>
            <li>b0   -> state (powers state of cameras, disables vtx when 0; on when 1)</li>
            <li>b1-2 -> mode
              <ul>
                <li>[0b00] - all off</li>
                <li>[0b01] - selected on</li>
                <li>[0b10] - neighbours on</li>
                <li>[0b11] - all on</li>
              </ul>
              </li>
            <li>b3-7 -> reserved</li>
          </ul>
        </details>
      </td>
      <td>N/A</td>
      <td>N/A</td>
      <td>N/A</td>
    </tr>
    <tr>
      <td>B1</td>
      <td>VTX Config
        <details>
            <summary>Bit-map</summary>
            <ul>
              <li>b0-1 -> power
                <ul>
                  <li>[0b00] - 25 mW</li>
                  <li>[0b01] - 200 mW</li>
                  <li>[0b10] - 400 mW</li>
                  <li>[0b11] - 800 mW</li>
                </ul>
              </li>
              <li>b2-3 -> band
                <ul>
                  <li>[0b00] - A</li>
                  <li>[0b01] - B</li>
                  <li>[0b10] - F</li>
                  <li>[0b11] - R</li>
                </ul>
              </li>
              <li>b4-6 -> channel (0-7; depends on band)</li>
              <li>b7   -> reserved</li>
            </ul>
        </details>
      </td>
      <td>N/A</td>
      <td>N/A</td>
      <td>N/A</td>
    </tr>
  </tbody>
</table>

### Status Frames

Devices publish supported status frames periodically at suitable rates. HotSwap battery STATUS_9 is sent only for valid, fresh, in-range data; board status is scheduled independently of battery availability.

> Note for BLDC:  
> To receive motor status (RPM, Voltage, Current etc.) status commands have to be activated.  
> Using two rates is useful for not congesting the bus with messages that are not needed as often, which can be sent at a lower rate.  

There are 13 numbered status messages, plus MUX_STATUS and HEARTBEAT_STATUS:

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
| VESC_COMMAND_STATUS_9 | 31 | Voltage, SOC, Current, Temperature, Minutes to target, Battery Status, Safety/PF | HotSwap |
| VESC_COMMAND_STATUS_10 | 32 | MCU States | ROS (ros-core) |
| VESC_COMMAND_STATUS_11 | 41 | Cubemars status | Cubemars |
| VESC_COMMAND_STATUS_12 | 42 | Orientation quaternion (W, X, Y, Z) | IMU |
| VESC_COMMAND_STATUS_13 | 43 / 0x2B | Eight device-specific status bytes | [HotSwap profile](#hotswap-status_13) |
| VESC_COMMAND_MUX_STATUS | 35 | Settings.State, Settings.Mode, VtxConfig.Power, VtxConfig.Band, VtxConfig.Channel, Camera Select, Temp VTX, Temp Board | Analog MUX |
| VESC_COMMAND_HEARTBEAT_STATUS | 235 / 0xEB | Shared health/reset header and one device-specific byte | [Profiles](#vesc_command_heartbeat_status) |

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

Payload: **8 bytes**. Slot IDs (CAN IDs): left **0x90 (0x1F90)**, center **0x91 (0x1F91)**, right **0x92 (0x1F92)**.
<table>
  <thead>
    <tr>
      <th>Byte</th>
      <th>Data</th>
      <th>Unit</th>
      <th>Scale</th>
      <th>Range</th>
      <th>Availability</th>
    </tr>
  </thead>
  <tbody>
    <tr>
      <td>B0</td>
      <td>Voltage</td>
      <td>V</td>
      <td>10</td>
      <td>0–25.5 V</td>
      <td>Hotswap</td>
    </tr>
    <tr>
      <td>B1</td>
      <td>SOC</td>
      <td>%</td>
      <td>1</td>
      <td>0–100%</td>
      <td>Hotswap</td>
    </tr>
    <tr>
      <td>B2–B3</td>
      <td>Current (+ charging, − discharging)</td>
      <td>A</td>
      <td>1000</td>
      <td>−32.768 to +32.767 A</td>
      <td>Hotswap</td>
    </tr>
    <tr>
      <td>B4</td>
      <td>Temperature</td>
      <td>°C</td>
      <td>1</td>
      <td>−128 to +127 °C</td>
      <td>Hotswap</td>
    </tr>
    <tr>
      <td>B5</td>
      <td>Minutes to target
        <details>
          <summary>Values</summary>
          <ul>
            <li>0–253 -> minutes remaining</li>
            <li>254 -> at least 254 minutes</li>
            <li>255 -> unavailable</li>
          </ul>
        </details>
      </td>
      <td>min</td>
      <td>1</td>
      <td>0–255</td>
      <td>Hotswap</td>
    </tr>
    <tr>
      <td>B6</td>
      <td>Battery Status
        <details>
          <summary>Bit-map</summary>
          <ul>
            <li>b0 -> FD: fully discharged</li>
            <li>b1 -> FC: fully charged</li>
            <li>b2 -> DSG: discharging or resting</li>
            <li>b3 -> LOW_REMAINING: RCA or RTA</li>
            <li>b4 -> TCA: terminate charge alarm</li>
            <li>b5 -> TDA: terminate discharge alarm</li>
            <li>b6 -> OTA: overtemperature alarm</li>
            <li>b7 -> OCA: overcharged alarm</li>
          </ul>
        </details>
      </td>
      <td>N/A</td>
      <td>N/A</td>
      <td>N/A</td>
      <td>Hotswap</td>
    </tr>
    <tr>
      <td>B7</td>
      <td>Safety/PF Status
        <details>
          <summary>Bit-map</summary>
          <ul>
            <li>b0 -> Undervoltage: CUV, CUVC</li>
            <li>b1 -> Overvoltage: COV, COVL, CHGV</li>
            <li>b2 -> Discharge overcurrent/overload: OCD1, OCD2, OCDL, AOLD, AOLDL</li>
            <li>b3 -> Charge overcurrent: OCC1, OCC2, CHGC, PCHGC</li>
            <li>b4 -> Short circuit: ASCC, ASCCL, ASCD, ASCDL</li>
            <li>b5 -> Temperature fault: OTC, OTD, OTF, UTC, UTD</li>
            <li>b6 -> Charging-process fault: OC, PTO, CTO</li>
            <li>b7 -> Permanent failure: OperationStatus.PF, bit 12</li>
          </ul>
        </details>
      </td>
      <td>N/A</td>
      <td>N/A</td>
      <td>N/A</td>
      <td>Hotswap</td>
    </tr>
  </tbody>
</table>

Current: signed 16-bit big-endian. Temperature: signed 8-bit. Round voltage to 0.1 V and current to 1 mA; truncate temperature and SOC. Reject non-finite or out-of-range inputs.

B5 reports time to empty when DSG is set (including rest), otherwise time to full. Gauge `0xFFFF` maps to 255; finite estimates ≥254 minutes map to 254.

Status bits may coexist; safety groups OR their listed flags.

Send only valid, fresh, in-range data. Fault flags and unavailable time do not invalidate a sample. Receivers time out each battery independently; board frames do not refresh battery data.


#### **VESC_COMMAND_STATUS_10**
> Note:  
> Properly described [here](https://github.com/wisniax/RoverControlApp/wiki#-mqtt-rover-status)  

<table>
  <thead>
    <tr>
      <th>Byte</th>
      <th>Data</th>
      <th>Unit</th>
      <th>Scale</th>
      <th>Availability</th>
    </tr>
  </thead>
  <tbody>
    <tr>
      <td>B0</td>
      <td>Communication State</td>
      <td><code>VESC_Status_10_CommunicationState</code></td>
      <td>N/A</td>
      <td>ROS</td>
    </tr>
    <tr>
      <td>B1 - B2</td>
      <td>Control Mode
        <details>
            <summary>Bit-map</summary>
            <ul>
            <li>b0  -> ESTOP</li>
            <li>b1  -> STOP</li>
            <li>b2  -> CONFIG</li>
            <li>b3  -> DRIVE</li>
            <li>b4  -> ROBOTIC_ARM</li>
            <li>b5  -> DEEP_SAMPLER</li>
            <li>b6  -> SURFACE_SAMPLER</li>
            <li>b7  -> DRIVE_AUTONOMY</li>
            <li>b8  -> ROBOTIC_ARM_AUTONOMY</li>
            <li>b9  -> DEEP_SAMPLER_AUTONOMY</li>
            <li>b10 -> SURFACE_SAMPLER_AUTONOMY</li>
            </ul>
        </details>
      </td>
      <td>N/A</td>
      <td>N/A</td>
      <td>ROS</td>
    </tr>
  </tbody>
</table>

#### **VESC_COMMAND_STATUS_11**

| **Byte** | **Data** | **Unit** | **Scale** | **Availability** |
|------|------|------|-------|---------|
| B0 - B1 | Position | Deg | 10 | Cubemars |
| B2 - B3 | Speed | ERPM | 0.1 | Cubemars |
| B4 - B5 | Current | A | 100 | Cubemars |
| B6 | Motor Temp | DegC | 1 | Cubemars |
| B7 | Error Code | `VESC_Status_11_ErrorCode` | N/A | Cubemars |

#### **VESC_COMMAND_STATUS_12**

| **Byte** | **Data** | **Unit** | **Scale** | **Availability** |
|------|------|------|-------|---------|
| B0 - B1 | Quaternion W (`int16_t`) | Dimensionless | 32767 | IMU |
| B2 - B3 | Quaternion X (`int16_t`) | Dimensionless | 32767 | IMU |
| B4 - B5 | Quaternion Y (`int16_t`) | Dimensionless | 32767 | IMU |
| B6 - B7 | Quaternion Z (`int16_t`) | Dimensionless | 32767 | IMU |

#### **VESC_COMMAND_STATUS_13**

Device-specific status. Payload length: **8 bytes**.

##### **HotSwap STATUS_13**

Source: **0x92**. CAN ID: **0x2B92**. Sent once per second, independently of battery data.
<table>
  <thead>
    <tr>
      <th>Byte</th>
      <th>Data</th>
      <th>Unit</th>
      <th>Scale</th>
      <th>Range</th>
      <th>Availability</th>
    </tr>
  </thead>
  <tbody>
    <tr>
      <td>B0</td>
      <td>Hotswap Status
        <details>
          <summary>Bit-map</summary>
          <ul>
            <li>b0 -> left_HS enabled</li>
            <li>b1 -> center_HS enabled</li>
            <li>b2 -> right_HS enabled</li>
            <li>b3 -> AUTO active</li>
            <li>b4 -> S1 signal level (0 = LOW, 1 = HIGH)</li>
            <li>b5 -> GPIO1 / S2 signal level (0 = LOW, 1 = HIGH)</li>
            <li>b6 -> RESISTORS_PRESENT (0 = absent, 1 = present)</li>
            <li>b7 -> EFUSE_PRESENT (0 = absent, 1 = present)</li>
          </ul>
        </details>
      </td>
      <td>N/A</td>
      <td>N/A</td>
      <td>N/A</td>
      <td>Hotswap</td>
    </tr>
    <tr>
      <td>B1</td>
      <td>eFuse Status (future)</td>
      <td>TBD</td>
      <td>TBD</td>
      <td>TBD</td>
      <td>Hotswap</td>
    </tr>
    <tr>
      <td>B2</td>
      <td>Resistor Temperature, if present</td>
      <td>TBD</td>
      <td>TBD</td>
      <td>TBD</td>
      <td>Hotswap</td>
    </tr>
    <tr>
      <td>B3</td>
      <td>Left Battery Number</td>
      <td>Number</td>
      <td>1</td>
      <td>1–15; 255 = unavailable</td>
      <td>Hotswap</td>
    </tr>
    <tr>
      <td>B4</td>
      <td>Center Battery Number</td>
      <td>Number</td>
      <td>1</td>
      <td>1–15; 255 = unavailable</td>
      <td>Hotswap</td>
    </tr>
    <tr>
      <td>B5</td>
      <td>Right Battery Number</td>
      <td>Number</td>
      <td>1</td>
      <td>1–15; 255 = unavailable</td>
      <td>Hotswap</td>
    </tr>
    <tr>
      <td>B6</td>
      <td>Controller state (low nibble), left-battery state (high nibble)</td>
      <td>Enums below</td>
      <td>N/A</td>
      <td>Two 4-bit codes</td>
      <td>Hotswap</td>
    </tr>
    <tr>
      <td>B7</td>
      <td>Center-battery state (low nibble), right-battery state (high nibble)</td>
      <td>Enums below</td>
      <td>N/A</td>
      <td>Two 4-bit codes</td>
      <td>Hotswap</td>
    </tr>
  </tbody>
</table>

HS bits report applied enable outputs. Resistor/eFuse presence is captured at startup from S3/I2C1. eFuse status and resistor-temperature encodings remain TBD.

Battery numbers identify physical packs; 0 is reserved.

State bit-map:

| Bits | Field |
|---|---|
| B6 bits 0–3 | Controller state |
| B6 bits 4–7 | Left-battery state |
| B7 bits 0–3 | Center-battery state |
| B7 bits 4–7 | Right-battery state |

| Controller code | Meaning |
|---|---|
| 0 | INIT |
| 1 | FIXED_ALL_ON |
| 2 | MANUAL |
| 3 | AUTO_PRECHARGE |
| 4 | AUTO_RUNNING |
| 5 | AUTO_NO_ELIGIBLE |
| 6–15 | Reserved |

| Battery code | Meaning |
|---|---|
| 0 | UNKNOWN_NOT_ASSESSED |
| 1 | UNAVAILABLE |
| 2 | QUALIFYING |
| 3 | ELIGIBLE |
| 4 | WAITING_FOR_IDLE_CURRENT |
| 5 | WAITING_FOR_VOLTAGE |
| 6 | CONNECTED |
| 7 | FAULTED |
| 8–15 | Reserved |

States describe controller assessment; B0 reports HS outputs. ELIGIBLE means qualified, fresh and fault-free; current/voltage admission checks still apply.

Both are subject to change.

#### **VESC_COMMAND_MUX_STATUS**

Command **35 / 0x23**, DLC **7**. Its Settings and VTX Config bytes retain the Analog MUX profile layout.

<table>
  <thead>
    <tr>
      <th>Byte</th>
      <th>Data</th>
      <th>Unit</th>
      <th>Scale</th>
      <th>Availability</th>
    </tr>
  </thead>
  <tbody>
    <tr>
      <td>B0-B1</td>
      <td>See the <a href=#analog-mux>SET_CONFIG Analog MUX profile</a> Settings and VTX Config bytes</td>
      <td>N/A</td>
      <td>N/A</td>
      <td>N/A</td>
    </tr>
    <tr>
      <td>B2</td>
      <td>CameraSelect</td>
      <td>Number</td>
      <td>1</td>
      <td>N/A</td>
    </tr>
    <tr>
      <td>B3 - B4</td>
      <td>Temp VTX</td>
      <td>deg C</td>
      <td>10</td>
      <td>N/A</td>
    </tr>
    <tr>
      <td>B5 - B6</td>
      <td>Temp Board</td>
      <td>deg C</td>
      <td>10</td>
      <td>N/A</td>
    </tr>
  </tbody>
</table>

#### **VESC_COMMAND_HEARTBEAT_STATUS**

Payload length: **2 bytes**. B0 contains common status; B1 is device-specific.

| B0 bits | Meaning |
|---|---|
| 0 | OK |
| 1 | WARN |
| 2 | ERR |
| 3 | SPI_ERR |
| 4 | I2C_ERR |
| 5–7 | Latest reset-reason code |

Flags b0–b4 are independent.

| Reset code | Meaning |
|---|---|
| 0 | NO_RESET |
| 1 | WATCHDOG |
| 2 | BROWNOUT |
| 3 | SOFTWARE |
| 4 | NRST_PIN |
| 5–7 | Reserved |

Reports the latest reset cause; full power-off clears the record.

##### **HotSwap heartbeat**

Source: **0x92**. CAN ID: **0xEB92**. B1 uses the [HotSwap status byte](#hotswap-status_13).

Sent independently of battery data. Board heartbeat does not refresh battery timestamps.

## Frequently Asked Questions (FAQ)

**What happens when sending motor commands outside of range?**
- When sending commands outside of range they will be truncated at the range limit. For example, if the maximum braking current is set to 50A and VESC_COMMAND_SET_CURRENT_BRAKE is sent with 60A the value will be truncated and 50A will be used.
