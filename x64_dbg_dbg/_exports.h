#ifndef _EXPORTS_H
#define _EXPORTS_H

#include "_global.h"

#ifdef __cplusplus
extern "C"
{
#endif

DLL_EXPORT duint _dbg_memfindbaseaddr(duint addr, duint* size);
DLL_EXPORT bool _dbg_memread(duint addr, unsigned char* dest, duint size, duint* read);
DLL_EXPORT bool _dbg_memwrite(duint addr, const unsigned char* src, duint size, duint* written);
DLL_EXPORT bool _dbg_memmap(MEMMAP* memmap);
DLL_EXPORT bool _dbg_memisvalidreadptr(duint addr);
DLL_EXPORT bool _dbg_valfromstring(const char* string, duint* value);
DLL_EXPORT bool _dbg_isdebugging();
DLL_EXPORT bool _dbg_isjumpgoingtoexecute(duint addr);
DLL_EXPORT bool _dbg_addrinfoget(duint addr, SEGMENTREG segment, ADDRINFO* addrinfo);
DLL_EXPORT bool _dbg_addrinfoset(duint addr, ADDRINFO* addrinfo);
DLL_EXPORT int _dbg_bpgettypeat(duint addr);
DLL_EXPORT bool _dbg_getregdump(REGDUMP* regdump);
DLL_EXPORT bool _dbg_valtostring(const char* string, duint* value);
DLL_EXPORT int _dbg_getbplist(BPXTYPE type, BPMAP* list);
DLL_EXPORT uint _dbg_getbranchdestination(uint addr);
DLL_EXPORT bool _dbg_functionoverlaps(uint start, uint end);
DLL_EXPORT uint _dbg_sendmessage(DBGMSG type, void* param1, void* param2);

#ifdef __cplusplus
}
#endif

#endif // _EXPORTS_H
