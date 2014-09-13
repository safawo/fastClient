#ifndef Think_Utils_CommonFunction
#define Think_Utils_CommonFunction

#include <QtCore/QDate>
#include <QtCore/QTime>
#include <QtCore/QString>
#include <utils/UtilsDll.hpp>


//����ĳλΪ1
#define BIT_SET(a,b) ((a) |= (1<<(b)))

//��ĳλ��Ϊ0
#define BIT_CLEAR(a,b) ((a) &= ~(1<<(b)))

//����ĳλ
#define BIT_FLIP(a,b) ((a) ^= (1<<(b)))

//���ĳλ
#define BIT_CHECK(a,b) ((a) & (1<<(b)))

//����һ�������壬���������ͺ��ַ��͵�ת������������Ƭ���϶�д
typedef union
{ 
    unsigned short uValue; 
    unsigned char sz[2]; 
} INT2CHAR;

Utils_API void String2Bit(QString& strSrc, unsigned char* pBit);
Utils_API unsigned char MergeLiftRC(unsigned char uLiftRcId);
Utils_API void ParseStrTime(QString& str, QDate& d, QTime& t);
Utils_API void UC2Str(unsigned char* pszSrc, int iNum, QString& strDst);
Utils_API void Str2UC(QString& strSrc, unsigned char* pszDst, int iNum);
Utils_API unsigned char TimePC2Dev(int iTime);
Utils_API int TimeDev2PC(unsigned char uTime);


#endif

