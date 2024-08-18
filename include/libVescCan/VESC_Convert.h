#ifndef VESC_Convert_h_
#define VESC_Convert_h_

#include <libVescCan/VESC_Defines.h>
#include <libVescCan/VESC_Consts.h>
#include <libVescCan/VESC_Structs.h>
#include <libVescCan/VESC_Endian.h>

#define _VESC_WriteRawData16(rawf,off,in,scale) *( (int16_t*)&rawf->rawData[off] ) = VESC_htobe16( (int16_t)(in * ((float)scale)) )
#define _VESC_WriteRawData32(rawf,off,in,scale) *( (int32_t*)&rawf->rawData[off] ) = VESC_htobe32( (int32_t)(in * ((float)scale)) )
#define _VESC_WriteRawData64(rawf,off,in,scale) *( (int64_t*)&rawf->rawData[off] ) = VESC_htobe64( (int64_t)(in * ((float)scale)) )

#define _VESC_ReadRawData16(dst,rawf,off,scale) dst = VESC_be16toh(*((int16_t*)&rawf->rawData[off])) / ((float)scale)
#define _VESC_ReadRawData32(dst,rawf,off,scale) dst = VESC_be32toh(*((int32_t*)&rawf->rawData[off])) / ((float)scale)
#define _VESC_ReadRawData64(dst,rawf,off,scale) dst = VESC_be64toh(*((int64_t*)&rawf->rawData[off])) / ((float)scale)

//****
// to VESC_RawFrame
//****

#ifndef __cplusplus //c++ lacks support for C11 _Generic
#define VESC_convertXToRaw(out, in) _Generic((in), \
    const VESC_CommandFrame*:VESC_convertCmdToRaw, \
    const VESC_Status_1*:VESC_convertStatus1ToRaw, \
    const VESC_Status_2*:VESC_convertStatus2ToRaw, \
    const VESC_Status_3*:VESC_convertStatus3ToRaw, \
    const VESC_Status_4*:VESC_convertStatus4ToRaw, \
    const VESC_Status_5*:VESC_convertStatus5ToRaw, \
    const VESC_Status_6*:VESC_convertStatus6ToRaw, \
    const VESC_Status_7*:VESC_convertStatus7ToRaw, \
    VESC_CommandFrame*:VESC_convertCmdToRaw, \
    VESC_Status_1*:VESC_convertStatus1ToRaw, \
    VESC_Status_2*:VESC_convertStatus2ToRaw, \
    VESC_Status_3*:VESC_convertStatus3ToRaw, \
    VESC_Status_4*:VESC_convertStatus4ToRaw, \
    VESC_Status_5*:VESC_convertStatus5ToRaw, \
    VESC_Status_6*:VESC_convertStatus6ToRaw, \
    VESC_Status_7*:VESC_convertStatus7ToRaw \
)(out,in)
#endif

bool VESC_convertCmdToRaw(VESC_RawFrame* out, const VESC_CommandFrame* in);

bool VESC_convertStatus1ToRaw(VESC_RawFrame* out, const VESC_Status_1* in);

bool VESC_convertStatus2ToRaw(VESC_RawFrame* out, const VESC_Status_2* in);

bool VESC_convertStatus3ToRaw(VESC_RawFrame* out, const VESC_Status_3* in);

bool VESC_convertStatus4ToRaw(VESC_RawFrame* out, const VESC_Status_4* in);

bool VESC_convertStatus5ToRaw(VESC_RawFrame* out, const VESC_Status_5* in);

bool VESC_convertStatus6ToRaw(VESC_RawFrame* out, const VESC_Status_6* in);

bool VESC_convertStatus7ToRaw(VESC_RawFrame* out, const VESC_Status_7* in);


//****
// from VESC_RawFrame
//****

#ifndef __cplusplus //c++ lacks support for C11 _Generic
#define VESC_convertRawToX(out, in) _Generic((out), \
    VESC_CommandFrame*:VESC_convertRawToCmd, \
    VESC_Status_1*:VESC_convertRawToStatus1, \
    VESC_Status_2*:VESC_convertRawToStatus2, \
    VESC_Status_3*:VESC_convertRawToStatus3, \
    VESC_Status_4*:VESC_convertRawToStatus4, \
    VESC_Status_5*:VESC_convertRawToStatus5, \
    VESC_Status_6*:VESC_convertRawToStatus6, \
    VESC_Status_7*:VESC_convertRawToStatus7 \
)(out,in)
#endif

bool VESC_convertRawToCmd(VESC_CommandFrame* out, const VESC_RawFrame* in);

bool VESC_convertRawToStatus1(VESC_Status_1* out, const VESC_RawFrame* in);

bool VESC_convertRawToStatus2(VESC_Status_2* out, const VESC_RawFrame* in);

bool VESC_convertRawToStatus3(VESC_Status_3* out, const VESC_RawFrame* in);

bool VESC_convertRawToStatus4(VESC_Status_4* out, const VESC_RawFrame* in);

bool VESC_convertRawToStatus5(VESC_Status_5* out, const VESC_RawFrame* in);

bool VESC_convertRawToStatus6(VESC_Status_6* out, const VESC_RawFrame* in);

bool VESC_convertRawToStatus7(VESC_Status_7* out, const VESC_RawFrame* in);

#endif //VESC_Convert_h_