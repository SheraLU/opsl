#ifndef CODESPLTYPES_H
#define CODESPLTYPES_H

#include <c_base.h>
#include <c_misc.h>
#include <c_sync.h>
#include <c_collection.h>
#include <c_field.h>
#include <v_copyIn.h>

#include "ccpp_code.h"


extern c_metaObject __code_CodeData__load (c_base base);

extern const char *CodeData_Code_metaDescriptor[];
extern const int CodeData_Code_metaDescriptorArrLength;
extern const int CodeData_Code_metaDescriptorLength;
extern c_metaObject __CodeData_Code__load (c_base base);
struct _CodeData_Code ;
extern  v_copyin_result __CodeData_Code__copyIn(c_base base, const struct CodeData::Code *from, struct _CodeData_Code *to);
extern  void __CodeData_Code__copyOut(const void *_from, void *_to);
struct _CodeData_Code {
    c_long coderID;
    c_string uploadTime;
    c_string fileName;
    c_string codeContent;
};

#undef OS_API
#endif
