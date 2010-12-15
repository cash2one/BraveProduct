
#ifndef SGDP_SDTYPE_H_20070601
#define SGDP_SDTYPE_H_20070601

//
// 1�ֽ��з�������
//
typedef signed char         INT8;

//
// 1�ֽ��޷�������
//
typedef unsigned char       UINT8;

//
// 2�ֽ��з�������
//
typedef signed short        INT16;

//
// 2�ֽ��޷�������
//
typedef unsigned short      UINT16;

//
// 4�ֽ��з�������
//
typedef signed int          INT32;

//
// 4�ֽ��޷�������
//
typedef unsigned int        UINT32;

//
// 8�ֽ��з�������
//
typedef signed long long    INT64;

//
// 8�ֽ��޷�������
//
typedef unsigned long long  UINT64;

//
// printf �еĸ�ʽ�ַ������壬����
// printf("The int64 number is: "FMT_I64, llNumber);
// printf("The uint64 number is: "FMT_U64, qwNumber);
// printf("The uint64 number is: "FMT_64X, qwNumber);
//
#ifdef WIN32
    #define FMT_I64 "%I64"
    #define FMT_U64 "%I64u"
    #define FMT_64X "%I64x"
#else
    #define FMT_I64 "%ll"
    #define FMT_U64 "%llu"
    #define FMT_64X "%llx"
#endif

#endif
