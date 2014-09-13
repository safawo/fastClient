#include "CommonFunction.h"
#include "QtCore/QStringList"


void String2Bit(QString& strSrc, unsigned char* pBit)
{
	unsigned char ucTemp = 0X00;
	int iCnt = 0;
	int iRow = 0;
	for(int i=0; i<strSrc.size(); i++)
	{
		iCnt = i%8;
		iRow = i/8;
		if ('1' == strSrc[i])
		{
			BIT_SET(ucTemp, 7-iCnt);
		}

		if (iCnt == 7)
		{
			pBit[iRow] = ucTemp;
			ucTemp = 0x00;
		}
	}
}

unsigned char MergeLiftRC(unsigned char uLiftRcId)
{
	return (0x01 << (uLiftRcId-1));
}

void ParseStrTime(QString& str, QDate& d, QTime& t)
{
    if (str.isEmpty())
    {
        return;
    }
	str = str.trimmed();
	QStringList lst1 = str.split(' ', QString::SkipEmptyParts);
	QString strDate = lst1.at(0);
	QString strTime = lst1.at(1);

	QStringList lst2 = strDate.split('-', QString::SkipEmptyParts);
	QStringList lst3 = strTime.split(':', QString::SkipEmptyParts);

	d.setDate(lst2[0].toInt(), lst2[1].toInt(), lst2[2].toInt());
	t.setHMS(lst3[0].toInt(), lst3[1].toInt(), 0);
}

void UC2Str(unsigned char* pszSrc, int iNum, QString& strDst)
{
	for (int i=0; i<iNum; i++)
	{
		char cTemp1 = (((pszSrc[i])&0XF0)>>4)|0X40;
		char cTemp2 = (pszSrc[i]&0X0F)|0X40;
		strDst += cTemp1;
		strDst += cTemp2;
	}
}

void Str2UC(QString& strSrc, unsigned char* pszDst, int iNum)
{
	if (strSrc.size()<2*iNum)
	{
		return;
	}

    unsigned char* pTemp = pszDst;

	for(int i=0; i< iNum; i++)
	{
		unsigned char ucTemp1 = strSrc[2*i].toLatin1();
		unsigned char ucTemp2 = strSrc[2*i+1].toLatin1();
		*(pTemp++) = ((ucTemp1&0X0F)<<4)|(ucTemp2&0X0F);
	}
}

unsigned char TimePC2Dev(int iTime)
{
    unsigned char uTime = 0x00;
    if ((0<iTime)&&(iTime<100))
    {
        int iDiv = iTime/10;
        int iRem = iTime%10;

        uTime = iDiv &0xff;
        uTime = (uTime << 4)|(iRem & 0xff);
    }

    return uTime;

}

int TimeDev2PC(unsigned char uTime)
{
    unsigned char uHigh = uTime & 0xf0;
    unsigned char uLow = uTime & 0x0f;

    int j = (uHigh>>4) & 0x0f;
    int t = uLow;
    return (j*10+t);
}