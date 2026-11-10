#include <libVescCan/VESC.h>

#include <math.h>
#include <stdio.h>
#include <string.h>

/* Keep checks active in Release builds, where assert() may be disabled. */
static unsigned checks;
static unsigned failures;

#define CHECK(condition) do { \
    ++checks; \
    if (!(condition)) { \
        fprintf(stderr, "%s:%d: %s\n", __FILE__, __LINE__, #condition); \
        ++failures; \
    } \
} while (0)

static void check_near(float actual, float expected)
{
    CHECK(fabsf(actual - expected) < 0.00001f);
}

static VESC_RawFrame make_raw(unsigned command, unsigned length,
                              const uint8_t *payload)
{
    VESC_RawFrame frame = {0};
    frame.vescID = 0x92U;
    frame.command = (VESC_Command_t)command;
    frame._reserved = 0x8000U;
    frame.can_dlc = (uint8_t)length;
    memcpy(frame.rawData, payload, length);
    return frame;
}

static void check_raw(const VESC_RawFrame *frame, unsigned command,
                      unsigned length, const uint8_t *payload)
{
    CHECK(frame->vescID == 0x92U);
    CHECK(frame->command == command);
    CHECK(frame->_reserved == 0x8000U);
    CHECK(frame->can_dlc == length);
    CHECK(frame->_pad0 == 0U);
    CHECK(frame->_res0 == 0U);
    CHECK(frame->_res1 == 0U);
    CHECK(memcmp(frame->rawData, payload, length) == 0);
    for (unsigned i = length; i < 8U; ++i)
        CHECK(frame->rawData[i] == 0U);
}

/* Literal bytes independently specify command IDs, sizes and signed encoding. */
static void test_status9_vectors(void)
{
    const VESC_Status_9 input = {
        .vescID = 0x92U, .voltage = 23.64f, .current = -1.25f,
        .temperature = -12.8f, .charge = 67.9f,
        .minutesToTarget = 255U, .batteryStatus = 0xFFU, .safetyStatus = 0xA5U
    };
    const uint8_t bytes[8] = {236U, 67U, 0xFBU, 0x1EU, 0xF4U, 255U, 0xFFU, 0xA5U};
    VESC_RawFrame encoded;
    memset(&encoded, 0xCC, sizeof(encoded));
    CHECK(VESC_convertStatus9ToRaw(&encoded, &input));
    check_raw(&encoded, 31U, 8U, bytes);

    /* Decode a literal wire vector, not the result of the encoder above. */
    const VESC_RawFrame literal = make_raw(31U, 8U, bytes);
    VESC_Status_9 decoded = {0};
    CHECK(VESC_convertRawToStatus9(&decoded, &literal));
    CHECK(decoded.vescID == 0x92U);
    check_near(decoded.voltage, 23.6f);
    check_near(decoded.current, -1.25f);
    check_near(decoded.temperature, -12.0f);
    check_near(decoded.charge, 67.0f);
    CHECK(decoded.minutesToTarget == 255U);
    CHECK(decoded.batteryStatus == 0xFFU);
    CHECK(decoded.safetyStatus == 0xA5U);

    const struct {
        VESC_Status_9 input;
        uint8_t bytes[8];
    } vectors[] = {
        {{.vescID = 0x92U, .voltage = 25.5f, .current = 32.767f,
          .temperature = 127.0f, .charge = 100.0f, .minutesToTarget = 254U,
          .batteryStatus = 0xFFU, .safetyStatus = 0xFFU},
         {255U, 100U, 0x7FU, 0xFFU, 0x7FU, 254U, 0xFFU, 0xFFU}},
        {{.vescID = 0x92U, .voltage = 0.0f, .current = -32.768f,
          .temperature = -128.0f, .charge = 0.0f},
         {0U, 0U, 0x80U, 0U, 0x80U, 0U, 0U, 0U}},
        {{.vescID = 0x92U, .voltage = 12.25f, .current = 0.0005f,
          .temperature = 0.99f, .charge = 50.9f, .minutesToTarget = 253U,
          .batteryStatus = 0x81U, .safetyStatus = 0x7EU},
         {123U, 50U, 0U, 1U, 0U, 253U, 0x81U, 0x7EU}},
        {{.vescID = 0x92U, .current = -0.0005f, .temperature = -0.99f},
         {0U, 0U, 0xFFU, 0xFFU, 0U, 0U, 0U, 0U}}
    };
    for (unsigned i = 0; i < sizeof(vectors) / sizeof(vectors[0]); ++i) {
        memset(&encoded, 0xCC, sizeof(encoded));
        CHECK(VESC_convertStatus9ToRaw(&encoded, &vectors[i].input));
        check_raw(&encoded, 31U, 8U, vectors[i].bytes);
    }

    const uint8_t lower[8] = {0U, 0U, 0x80U, 0U, 0x80U, 0U, 0U, 0U};
    const uint8_t upper[8] = {255U, 100U, 0x7FU, 0xFFU, 0x7FU, 254U, 0xFFU, 0xFFU};
    VESC_RawFrame raw = make_raw(31U, 8U, lower);
    CHECK(VESC_convertRawToStatus9(&decoded, &raw));
    check_near(decoded.current, -32.768f);
    check_near(decoded.temperature, -128.0f);
    raw = make_raw(31U, 8U, upper);
    CHECK(VESC_convertRawToStatus9(&decoded, &raw));
    check_near(decoded.voltage, 25.5f);
    check_near(decoded.current, 32.767f);
    check_near(decoded.temperature, 127.0f);
    check_near(decoded.charge, 100.0f);
}

static void check_status9_rejected(const VESC_Status_9 *input)
{
    VESC_RawFrame output;
    unsigned char before[sizeof(output)];
    memset(&output, 0xA5, sizeof(output));
    memcpy(before, &output, sizeof(output));
    CHECK(!VESC_convertStatus9ToRaw(&output, input));
    CHECK(memcmp(&output, before, sizeof(output)) == 0);
}

static void test_status9_rejection(void)
{
    const VESC_Status_9 valid = {
        .vescID = 0x92U, .voltage = 12.0f, .current = 1.0f,
        .temperature = 20.0f, .charge = 50.0f
    };
    const float invalid[4][5] = {
        {-0.01f, 25.51f, NAN, INFINITY, -INFINITY},
        {-32.769f, 32.768f, NAN, INFINITY, -INFINITY},
        {-128.01f, 127.01f, NAN, INFINITY, -INFINITY},
        {-0.01f, 100.01f, NAN, INFINITY, -INFINITY}
    };
    for (unsigned field = 0; field < 4U; ++field) {
        for (unsigned value = 0; value < 5U; ++value) {
            VESC_Status_9 input = valid;
            switch (field) {
            case 0U: input.voltage = invalid[field][value]; break;
            case 1U: input.current = invalid[field][value]; break;
            case 2U: input.temperature = invalid[field][value]; break;
            default: input.charge = invalid[field][value]; break;
            }
            check_status9_rejected(&input);
        }
    }
    check_status9_rejected(NULL);
    CHECK(!VESC_convertStatus9ToRaw(NULL, &valid));
    CHECK(!VESC_convertStatus9ToRaw(NULL, NULL));

    const uint8_t bytes[8] = {120U, 50U, 0U, 0U, 20U, 255U, 0xFFU, 0xFFU};
    VESC_RawFrame raw = make_raw(31U, 8U, bytes);
    VESC_Status_9 output;
    unsigned char before[sizeof(output)];
    memset(&output, 0xA5, sizeof(output));
    memcpy(before, &output, sizeof(output));
    CHECK(!VESC_convertRawToStatus9(NULL, &raw));
    CHECK(!VESC_convertRawToStatus9(&output, NULL));
    CHECK(memcmp(&output, before, sizeof(output)) == 0);
    for (unsigned length = 0; length < 16U; ++length) {
        if (length == 8U)
            continue;
        raw.can_dlc = (uint8_t)length;
        CHECK(!VESC_convertRawToStatus9(&output, &raw));
        CHECK(memcmp(&output, before, sizeof(output)) == 0);
    }
    raw.can_dlc = 8U;
    raw.command = (VESC_Command_t)43U;
    CHECK(!VESC_convertRawToStatus9(&output, &raw));
    CHECK(memcmp(&output, before, sizeof(output)) == 0);
    raw.command = (VESC_Command_t)31U;
    for (unsigned soc = 101U; soc <= 255U; ++soc) {
        raw.rawData[1] = (uint8_t)soc;
        CHECK(!VESC_convertRawToStatus9(&output, &raw));
        CHECK(memcmp(&output, before, sizeof(output)) == 0);
    }
}

/* Generic payloads are opaque; reserved values must survive unchanged. */
#define DEFINE_GENERIC_TEST(name, type, encode, decode, command_id, length) \
static void name(void) \
{ \
    const uint8_t payload[8] = {0xA5U, 0x5AU, 0xFFU, 0U, 15U, 0x80U, 0xE6U, 0xF8U}; \
    type input = {0}; \
    input.vescID = 0x92U; \
    memcpy(input.data, payload, length); \
    VESC_RawFrame encoded; \
    memset(&encoded, 0xCC, sizeof(encoded)); \
    CHECK(encode(&encoded, &input)); \
    check_raw(&encoded, command_id, length, payload); \
    VESC_RawFrame raw = make_raw(command_id, length, payload); \
    type output = {0}; \
    CHECK(decode(&output, &raw)); \
    CHECK(output.vescID == 0x92U); \
    CHECK(memcmp(output.data, payload, length) == 0); \
    unsigned char raw_before[sizeof(encoded)]; \
    memset(&encoded, 0xA5, sizeof(encoded)); \
    memcpy(raw_before, &encoded, sizeof(encoded)); \
    CHECK(!encode(&encoded, NULL)); \
    CHECK(memcmp(&encoded, raw_before, sizeof(encoded)) == 0); \
    CHECK(!encode(NULL, &input)); \
    CHECK(!encode(NULL, NULL)); \
    unsigned char before[sizeof(output)]; \
    memset(&output, 0xA5, sizeof(output)); \
    memcpy(before, &output, sizeof(output)); \
    CHECK(!decode(NULL, &raw)); \
    CHECK(!decode(&output, NULL)); \
    CHECK(memcmp(&output, before, sizeof(output)) == 0); \
    CHECK(!decode(NULL, NULL)); \
    for (unsigned dlc = 0; dlc < 16U; ++dlc) { \
        if (dlc == length) continue; \
        raw.can_dlc = (uint8_t)dlc; \
        CHECK(!decode(&output, &raw)); \
        CHECK(memcmp(&output, before, sizeof(output)) == 0); \
    } \
    raw.can_dlc = length; \
    raw.command = (VESC_Command_t)0U; \
    CHECK(!decode(&output, &raw)); \
    CHECK(memcmp(&output, before, sizeof(output)) == 0); \
}

DEFINE_GENERIC_TEST(test_set_config, VESC_SetConfig,
                    VESC_convertSetConfigToRaw, VESC_convertRawToSetConfig, 103U, 2U)
DEFINE_GENERIC_TEST(test_status13, VESC_Status_13,
                    VESC_convertStatus13ToRaw, VESC_convertRawToStatus13, 43U, 8U)
DEFINE_GENERIC_TEST(test_heartbeat, VESC_Heartbeat_Status,
                    VESC_convertHeartbeatStatusToRaw, VESC_convertRawToHeartbeatStatus, 235U, 2U)

static void test_opaque_values(void)
{
    for (unsigned value = 0; value <= 255U; ++value) {
        const uint8_t heartbeat_bytes[2] = {(uint8_t)value, 0xA5U};
        VESC_RawFrame raw = make_raw(235U, 2U, heartbeat_bytes);
        VESC_Heartbeat_Status heartbeat = {0};
        CHECK(VESC_convertRawToHeartbeatStatus(&heartbeat, &raw));
        CHECK(heartbeat.data[0] == value);
        CHECK(heartbeat.data[1] == 0xA5U);
        memset(&raw, 0xCC, sizeof(raw));
        CHECK(VESC_convertHeartbeatStatusToRaw(&raw, &heartbeat));
        check_raw(&raw, 235U, 2U, heartbeat_bytes);

        const uint8_t status_bytes[8] = {0xFFU, 0x80U, 0xFEU, 1U, 15U, 255U,
                                         (uint8_t)value, (uint8_t)(255U - value)};
        raw = make_raw(43U, 8U, status_bytes);
        VESC_Status_13 status = {0};
        CHECK(VESC_convertRawToStatus13(&status, &raw));
        CHECK(memcmp(status.data, status_bytes, 8U) == 0);
        memset(&raw, 0xCC, sizeof(raw));
        CHECK(VESC_convertStatus13ToRaw(&raw, &status));
        check_raw(&raw, 43U, 8U, status_bytes);
    }
}

static void test_mux_regression(void)
{
    const VESC_Mux_CamSel camera = {.vescID = 0x92U, .cameraSelect = 4U};
    const uint8_t camera_bytes[1] = {4U};
    VESC_RawFrame raw = {0};
    CHECK(VESC_convertMuxCamSelToRaw(&raw, &camera));
    check_raw(&raw, 34U, 1U, camera_bytes);
    raw = make_raw(34U, 1U, camera_bytes);
    VESC_Mux_CamSel camera_out = {0};
    CHECK(VESC_convertRawToMuxCamSel(&camera_out, &raw));
    CHECK(camera_out.vescID == 0x92U);
    CHECK(camera_out.cameraSelect == 4U);

    const VESC_Mux_Status status = {
        .vescID = 0x92U,
        .settings = {.state = true, .mode = VESC_MUX_MODE_NEIGHBOURS, ._reserved = 0x15U},
        .vtxConfig = {.power = VESC_MUX_POWER_800_MILIW, .band = VESC_MUX_BAND_B,
                      .channel = 6U, ._reserved = 1U},
        .cameraSelect = 4U, .vtxTemp = 42.5f, .boardTemp = -5.5f
    };
    const uint8_t bytes[7] = {0xADU, 0xE7U, 4U, 0x01U, 0xA9U, 0xFFU, 0xC9U};
    memset(&raw, 0, sizeof(raw));
    CHECK(VESC_convertMuxStatusToRaw(&raw, &status));
    check_raw(&raw, 35U, 7U, bytes);
    raw = make_raw(35U, 7U, bytes);
    VESC_Mux_Status decoded = {0};
    CHECK(VESC_convertRawToMuxStatus(&decoded, &raw));
    CHECK(decoded.vescID == 0x92U);
    CHECK(decoded.settings.state);
    CHECK(decoded.settings.mode == VESC_MUX_MODE_NEIGHBOURS);
    CHECK(decoded.settings._reserved == 0x15U);
    CHECK(decoded.vtxConfig.power == VESC_MUX_POWER_800_MILIW);
    CHECK(decoded.vtxConfig.band == VESC_MUX_BAND_B);
    CHECK(decoded.vtxConfig.channel == 6U);
    CHECK(decoded.vtxConfig._reserved == 1U);
    CHECK(decoded.cameraSelect == 4U);
    check_near(decoded.vtxTemp, 42.5f);
    check_near(decoded.boardTemp, -5.5f);
}

int main(void)
{
    test_status9_vectors();
    test_status9_rejection();
    test_set_config();
    test_status13();
    test_heartbeat();
    test_opaque_values();
    test_mux_regression();
    printf("%u codec checks, %u failures\n", checks, failures);
    return failures == 0U ? 0 : 1;
}
