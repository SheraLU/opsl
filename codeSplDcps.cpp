#include "codeSplDcps.h"
#include "ccpp_code.h"

#include <v_copyIn.h>
#include <v_topic.h>
#include <os_stdlib.h>
#include <string.h>
#include <os_report.h>

v_copyin_result
__CodeData_Code__copyIn(
    c_base base,
    const struct ::CodeData::Code *from,
    struct _CodeData_Code *to)
{
    v_copyin_result result = V_COPYIN_RESULT_OK;
    (void) base;

    to->coderID = (c_long)from->coderID;
#ifdef OSPL_BOUNDS_CHECK
    if(from->uploadTime){
        to->uploadTime = c_stringNew_s(base, from->uploadTime);
        if(to->uploadTime == NULL) {
            result = V_COPYIN_RESULT_OUT_OF_MEMORY;
        }
    } else {
        OS_REPORT (OS_ERROR, "copyIn", 0,"Member 'CodeData::Code.uploadTime' of type 'c_string' is NULL.");
        result = V_COPYIN_RESULT_INVALID;
    }
#else
    to->uploadTime = c_stringNew_s(base, from->uploadTime);
    if(to->uploadTime == NULL) {
        result = V_COPYIN_RESULT_OUT_OF_MEMORY;
    }
#endif
#ifdef OSPL_BOUNDS_CHECK
    if(from->fileName){
        to->fileName = c_stringNew_s(base, from->fileName);
        if(to->fileName == NULL) {
            result = V_COPYIN_RESULT_OUT_OF_MEMORY;
        }
    } else {
        OS_REPORT (OS_ERROR, "copyIn", 0,"Member 'CodeData::Code.fileName' of type 'c_string' is NULL.");
        result = V_COPYIN_RESULT_INVALID;
    }
#else
    to->fileName = c_stringNew_s(base, from->fileName);
    if(to->fileName == NULL) {
        result = V_COPYIN_RESULT_OUT_OF_MEMORY;
    }
#endif
#ifdef OSPL_BOUNDS_CHECK
    if(from->codeContent){
        to->codeContent = c_stringNew_s(base, from->codeContent);
        if(to->codeContent == NULL) {
            result = V_COPYIN_RESULT_OUT_OF_MEMORY;
        }
    } else {
        OS_REPORT (OS_ERROR, "copyIn", 0,"Member 'CodeData::Code.codeContent' of type 'c_string' is NULL.");
        result = V_COPYIN_RESULT_INVALID;
    }
#else
    to->codeContent = c_stringNew_s(base, from->codeContent);
    if(to->codeContent == NULL) {
        result = V_COPYIN_RESULT_OUT_OF_MEMORY;
    }
#endif
    return result;
}

void
__CodeData_Code__copyOut(
    const void *_from,
    void *_to)
{
    const struct _CodeData_Code *from = (const struct _CodeData_Code *)_from;
    struct ::CodeData::Code *to = (struct ::CodeData::Code *)_to;
    to->coderID = (::DDS::Long)from->coderID;
    to->uploadTime = DDS::string_dup(from->uploadTime ? from->uploadTime : "");
    to->fileName = DDS::string_dup(from->fileName ? from->fileName : "");
    to->codeContent = DDS::string_dup(from->codeContent ? from->codeContent : "");
}

