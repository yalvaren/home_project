/**
 *    @file
 *    @brief    This file contains the definition of commonly used Macros and Enumerations
 *
 *  
 *
 *   @copyright  Copyright 2007-. Whirlpool Corporation. All rights reserved - CONFIDENTIAL
 */
#ifndef C_EXTENSIONS_H
    #define C_EXTENSIONS_H

//=====================================================================================================================
//-------------------------------------- PUBLIC (Extern Variables, Constants & Defines) -------------------------------
//=====================================================================================================================
//---------------------------------------------------------------------------------------------------------------------
//--------------------------------------------- STANDARD SYSTEM DEFINITIONS -------------------------------------------
//---------------------------------------------------------------------------------------------------------------------

typedef enum _BOOL_TYPE
{
    FALSE           = 0,
    TRUE            = 1
} BOOL_TYPE;

typedef BOOL_TYPE T_BOOL;

typedef enum _ON_OFF_TYPE
{
    OFF             = 0,
    ON              = 1
} ON_OFF_TYPE;

typedef enum _PASS_FAIL_TYPE
{
    FAIL            = 0,
    PASS            = 1
} PASS_FAIL_TYPE;

#define OK              ((PASS_FAIL_TYPE)1)

typedef enum _COMPLETE_TYPE
{
    INCOMPLETE      = 0,
    COMPLETE        = 1
} COMPLETE_TYPE;

typedef enum _ACTIVE_TYPE
{
    INACTIVE        = 0,
    ACTIVE          = 1
} ACTIVE_TYPE;


#ifndef ENABLED
	#define ENABLED   		1
#endif //ENABLED

#ifndef DISABLED
	#define DISABLED  		0
#endif //DISABLED

#ifndef NULL
	#define NULL 			(void *)0
#endif //NULL

#ifndef UNAVAILABLE
	#define UNAVAILABLE 	10
#endif //UNAVAILABLE

#ifndef AVAILABLE
	#define AVAILABLE 		11
#endif //AVAILABLE

//---------------------------------------------------------------------------------------------------------------------
//------------------- --------------------------BYTE AND WORD ACCESS --------------------------------------------------
//---------------------------------------------------------------------------------------------------------------------

#define LOWORD(mem)         (unsigned short)((mem) & 0xFFFFU)   ///< This macro is for extracting lower word from a double word type of data
#define LOBYTE(mem)         (unsigned char)((mem) & 0xFFU)      ///< This macro is for extracting lower byte from the word type of data
#define HIWORD(mem) 		(unsigned short)(((unsigned long)(mem) >> 16U ) & 0xFFFFU)  ///< This macro is for extracting higher word from a double word type of data
#define HIBYTE(mem) 		(unsigned char)(((unsigned short)(mem) >> 8U) & 0xFFU)      ///<This macro is for extracting higher byte from a word type of data
//---------------------------------------------------------------------------------------------------------------------
//--------------------------------------------- BIT MANIPULATION ------------------------------------------------------
//---------------------------------------------------------------------------------------------------------------------

#define BIT_TEST(mem,bit)               ((mem)&(1UL<<(bit)))    ///< This macro is used to perform test on bit of the data
#define BIT_SET(mem,bit)                ((mem)|=(1UL<<(bit)))   ///< This macro is used to set the bit of the data
#define BIT_CLR(mem,bit)                ((mem)&=~(1UL<<(bit)))  ///< This macro is used to clear the bit of the data
#define BIT_TOGGLE(mem,bit)             ((mem)^=(1UL<<(bit)))   ///< This macro is used to toggle the bit of the data
#define BIT_STORAGE_SIZE(num_of_bits)   ((size_t)(((num_of_bits) + 7U) / 8U)) ///< this macro returns the number of bytes needed to store the amount bits requested.


#define BYTES_REQUIRED(bits)            ((unsigned char)(((bits)+7)>>3))///< Macro to convert bits to bytes with minimal calculation (in case it must be at run time).
//---------------------------------------------------------------------------------------------------------------------
//--------------------------------------------- DATA ALIAS ------------------------------------------------------------
//---------------------------------------------------------------------------------------------------------------------
typedef unsigned char       uint8;
typedef unsigned short int  uint16;
typedef unsigned long int   uint32;

#ifndef __CSMC__
    typedef unsigned long long  uint64;
#endif

typedef signed char         sint8;
typedef signed short int    sint16;
typedef signed long int     sint32;

#ifndef __CSMC__
    typedef signed long long    sint64;
#endif

typedef float               float32;
typedef double              float64;


//---------------------------------------------------------------------------------------------------------------------
//--------------------------------------------- CTAssert ------------------------------------------------------------
//---------------------------------------------------------------------------------------------------------------------

#ifndef CT_ASSERT   // to ensure it is not defined by the application somewhere else
    /**
     * Compile-time check to see if test condition is valid or not.
     *
     * This macro, after expansion of the helper macros, generates a compile-time error if the test is invalid. This error
     * will be your compiler's flavor of "invalid array dimension"; if you see this error at the place where you're doing
     * the test, you will know the test failed. \see _CTASSERT() and __CTASSERT().
     *
     * @param test - the logical test that is to be checked for validity.
     *
     * Usage: CT_ASSERT(<logical_text>);
     *
     * Example: CT_ASSERT((NUM_OF_ITEMS <= 255) && (sizeof(buffer) >= NUM_OF_ITEMS));
     *
     * @note
     *      - Macro only works for compile-time checking.  Run-time checks will not work.
     *      - This can only work where it is legal to declare a variable. Thus, for example, you
     *        cannot use it in a function after a line of executable code.
     */
    #define CT_ASSERT(test)              _CTASSERT(__LINE__, test)

    /**
     * First-level support macro, designed to work with CT_ASSERT(). It is not intended for direct use in your code.
     *
     * The purpose for this macro is solely and exclusively for the expansion of the __LINE__ argument passed by
     * CT_ASSERT(). The ANSI standard stipulates that when macros are concatenated,  the concatenation happens first, and
     * then the expansion; this means that this macro converts "__LINE__" to a numerical value, which is then passed to the
     * next macro. Without this intermediate macro, the end symbol would be "_CtAssert__LINE__[]", which is not the unique
     * symbol desired.
     *
     * @param UniqueId - a unique identifier, which is used to form the name of the external array.
     * @param test - the logical test that is to be checked for validity.
     */
    #define _CTASSERT(UniqueId, test)   __CTASSERT(UniqueId, test)

    /**
     * Second-level support macro, designed to work with CT_ASSERT(). It is not intended for direct use in your code.
     *
     * This macro uses the unique identifier passed to it, as part of the declaration of an external array. It then uses the
     * \b logical test as the size of the array. If the test is valid, it will evaluate to "1", and so the compiler will
     * see a declaration of an external array of size 1. If the test is invalid, the compiler will see a declaration of an
     * external array of size 0, which is not legal, and will cause a compilation error. Please note that the error emitted,
     * which should relate to invalid array dimension, will not relate to the thing being tested; the user should know that
     * when he receives this error, that the test was invalid.
     *
     * Please note that this macro relies on an intermediate macro, located between the API that is to be used in the source
     * code, and this macro, to properly expand all preprocessor symbols. In particular, if the symbol __LINE__ is used, it
     * must be expanded to a line number before being passed to this macro. Without the expansion, this macro will form a
     * symbol name of "_CtAssert__LINE__[]", which is not unique if the CT_ASSERT() macro is used multiple times within the
     * same source file.
     *
     * @param UniqueId - a unique identifier, which is used to form the name of the external array.
     * @param test - the logical test that is to be checked for validity.
     *
     * @note Regarding the suppressed PC-Lint warnings:
     * - The 506, suppresses "Constant value Boolean".
     * - The 515, suppresses "Symbol 'x' has arg. count conflict". The placement here is a convenience, as this frequently
     *   happens with keyword "defined()" which is used in quite a few modules.
     * - The #752, suppresses a "local declarator 'Symbol' (Location) not referenced" warning, caused because we
     *   declare an external symbol and then make no reference to it.
     * - The 762, suppresses "Redundantly declared symbol 'Symbol' previously declared at <Location>" which can
     *   happen if, for example, you would place multiple CT_ASSERT() statements on the same line, or if the same check
     *   appeared at the same line number in two different files.
     * - The 18, suppresses "redeclared w/ different size"
     */
    #define __CTASSERT(UniqueId, test)    /*lint -e{506} -e{515} --e{752} -e{762} -e{18}*/extern unsigned char _CtAssert##UniqueId[(test)]

#endif



#endif //C_EXTENSIONS_H


