// (c) Copyright 2008-2015 by Texas Instruments Inc.  All rights reserved.

//------------------------------------------------------------------------------
// winint.h
//
// Windows integer types.  This file supplies an alternate definition of
// common Windows types as an aid to porting code originally developed on
// Windows to other OS'.  In particular, this would be used when the public
// APIs are defined in terms of these Windows types.  Otherwise, it would
// be preferred to remove the Windows types altogether.
//------------------------------------------------------------------------------

#ifndef WININT_H
#define WININT_H

#include "stdint.h"

// Windows provides a definition for NULL
#ifndef NULL
#define NULL 0
#endif

// Windows BOOL is defined as an int
typedef int BOOL;
#define FALSE 0
#define TRUE  1

// Common Windows integer types
typedef uint32_t DWORD;
typedef int16_t  WORD;
typedef int32_t  INT;
typedef uint32_t UINT;
typedef uint32_t UINT32;

#endif // WININT_H

// End of File

