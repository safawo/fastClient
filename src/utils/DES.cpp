#include <utils/DES.hpp>

#include <QDebug>
#include <QFile>
#include <string>


// initial permutation IP
const int DES::IP_Table[] =
{
    58, 50, 42, 34, 26, 18, 10, 2,  60, 52, 44, 36, 28, 20, 12, 4,
    62, 54, 46, 38, 30, 22, 14, 6,  64, 56, 48, 40, 32, 24, 16, 8,
    57, 49, 41, 33, 25, 17, 9,  1,  59, 51, 43, 35, 27, 19, 11, 3,
    61, 53, 45, 37, 29, 21, 13, 5,  63, 55, 47, 39, 31, 23, 15, 7,
};

// final permutation IP^-1
const int DES::IPR_Table[] =
{
    40, 8, 48, 16, 56, 24, 64, 32, 39, 7, 47, 15, 55, 23, 63, 31,
    38, 6, 46, 14, 54, 22, 62, 30, 37, 5, 45, 13, 53, 21, 61, 29,
    36, 4, 44, 12, 52, 20, 60, 28, 35, 3, 43, 11, 51, 19, 59, 27,
    34, 2, 42, 10, 50, 18, 58, 26, 33, 1, 41, 9, 49, 17, 57, 25
};

// Expand array
const int DES::E_Table[48] =
{
    32,1,2,3,4,5,
    4,5,6,7,8,9,
    8,9,10,11,12,13,
    12,13,14,15,16,17,
    16,17,18,19,20,21,
    20,21,22,23,24,25,
    24,25,26,27,28,29,
    28,29,30,31,32,1
};

// P-Transform
const int DES::P_Table[32] =
{
    16,7,20,21,
    29,12,28,17,
    1,15,23,26,
    5,18,31,10,
    2,8,24,14,
    32,27,3,9,
    19,13,30,6,
    22,11,4,25
};

// PC1 in keyBuild
const int DES::PC1_Table[56] =
{
    57,49,41,33,25,17,9,
    1,58,50,42,34,26,18,
    10,2,59,51,43,35,27,
    19,11,3,60,52,44,36,
    63,55,47,39,31,33,15,
    7,62,54,46,38,30,22,
    14,6,61,53,45,37,29,
    21,13,5,28,20,12,4
};

// PC2 in keyBuild
const int DES::PC2_Table[48] =
{
    14,17,11,24,1,5,
    3,28,15,6,21,10,
    23,19,12,4,26,8,
    16,7,27,20,13,2,
    41,52,31,37,47,55,
    30,40,51,45,33,48,
    44,49,39,56,34,53,
    46,42,50,36,29,32
};

// number left rotations of pc1
const int DES::LOOP_Table[16] =
{
    1,1,2,2,2,2,2,2,1,2,2,2,2,2,2,1
};

//S-Box
const int DES::S_Box[8][4][16] =
{
    {
        {14,4,13,1,2,15,11,8,3,10,6,12,5,9,0,7},
        {0,15,7,4,14,2,13,1,10,6,12,11,9,5,3,8},
        {4,1,14,8,13,6,2,11,15,12,9,7,3,10,5,0},
        {15,12,8,2,4,9,1,7,5,11,3,14,10,0,6,13}
    },
    {
        {15,1,8,14,6,11,3,4,9,7,2,13,12,0,5,10},
        {3,13,4,7,15,2,8,14,12,0,1,10,6,9,11,5},
        {0,14,7,11,10,4,13,1,5,8,12,6,9,3,2,15},
        {13,8,10,1,3,15,4,2,11,6,7,12,0,5,14,9}
    },
    {
        {10,0,9,14,6,3,15,5,1,13,12,7,11,4,2,8},
        {13,7,0,9,3,4,6,10,2,8,5,14,12,11,15,1},
        {13,6,4,9,8,15,3,0,11,1,2,12,5,10,14,7},
        {1,10,13,0,6,9,8,7,4,15,14,3,11,5,2,12}
    },
    {
        {7,13,14,3,0,6,9,10,1,2,8,5,11,12,4,15},
        {13,8,11,5,6,15,0,3,4,7,2,12,1,10,14,9},
        {10,6,9,0,12,11,7,13,15,1,3,14,5,2,8,4},
        {3,15,0,6,10,1,13,8,9,4,5,11,12,7,2,14}
    },
    {
        {2,12,4,1,7,10,11,6,8,5,3,15,13,0,14,9},
        {14,11,2,12,4,7,13,1,5,0,15,10,3,9,8,6},
        {4,2,1,11,10,13,7,8,15,9,12,5,6,3,0,14},
        {11,8,12,7,1,14,2,13,6,15,0,9,10,4,5,3}
    },
    {
        {12,1,10,15,9,2,6,8,0,13,3,4,14,7,5,11},
        {10,15,4,2,7,12,9,5,6,1,13,14,0,11,3,8},
        {9,14,15,5,2,8,12,3,7,0,4,10,1,13,11,6},
        {4,3,2,12,9,5,15,10,11,14,1,7,6,0,8,13}
    },
    {
        {4,11,2,14,15,0,8,13,3,12,9,7,5,10,6,1},
        {13,0,11,7,4,9,1,10,14,3,5,12,2,15,8,6},
        {1,4,11,13,12,3,7,14,10,15,6,8,0,5,9,2},
        {6,11,13,8,1,4,10,7,9,5,0,15,14,2,3,12}
    },
    {
        {13,2,8,4,6,15,11,1,10,9,3,14,5,0,12,7},
        {1,15,13,8,10,3,7,4,12,5,6,11,0,14,9,2},
        {7,11,4,1,9,12,14,2,0,6,10,13,15,3,5,8},
        {2,1,14,7,4,10,8,13,15,12,9,0,3,5,6,11}
    }
};



DES::DES()
{
}

DES::~DES()
{

}

void DES::ByteToBit(Bit *Out, const unsigned char *In, int bits)
{
    for(int i = 0; i < bits; ++i)
        Out[i] = (In[i>>3]>>(7 - (i&7))) & 1;
}

void DES::BitToByte(unsigned char *Out, const Bit *In, int bits)
{
    memset(Out, 0, bits>>3);

    for(int i = 0; i < bits; ++i)
        Out[i>>3] |= In[i]<<(7 - (i&7));
}

void DES::RotateL(Bit *In, int len, int loop)
{
    Bit Tmp[256];

    memcpy(Tmp, In, loop);
    memcpy(In, In+loop, len-loop);
    memcpy(In+len-loop, Tmp, loop);
}

void DES::Xor(Bit *InA, const Bit *InB, int len)
{
    for(int i = 0; i < len; ++i)
        InA[i] ^= InB[i];

}

void DES::Transform(Bit *Out, Bit *In, const int *Table, int len)
{
    bool Tmp[256];

    for(int i=0; i<len; ++i)
        Tmp[i] = In[ Table[i]-1 ];

    memcpy(Out, Tmp, len);
}

void DES::S_func(Bit Out[], const Bit In[])
{
    for(int i=0,j,k; i<8; ++i,In+=6,Out+=4)
    {
        j = (In[0]<<1) + In[5];
        k = (In[1]<<3) + (In[2]<<2) + (In[3]<<1) + In[4]; //��֯SID�±�

        for(int l=0; l<4; ++l)                               //����Ӧ4bit��ֵ
            Out[l] = (S_Box[i][j][k]>>(3 - l)) & 1;
    }
}

void DES::F_func(Bit In[32], const Bit Ki[48])
{
    bool MR[48];

    Transform(MR, In, E_Table, 48);
    Xor(MR, Ki, 48);
    S_func(In, MR);
    Transform(In, In, P_Table, 32);
}

bool DES::RunPad(int nType, const unsigned char *In, unsigned datalen, unsigned char *Out, unsigned &padlen)
{
    if (nType < PAD_ISO_1 || nType > PAD_PKCS_7)
        return false;

    if (In == NULL || datalen < 0 || Out == NULL)
        return false;
    int res = (datalen & 0x00000007);

    if (res == 0)
    {
        padlen = datalen;
        memcpy(Out, In, datalen);
        return true;
    }

    padlen	=	(datalen+8-res);
    memcpy(Out,In,datalen);

    if(nType	==	PAD_ISO_1)
    {
        memset(Out+datalen,0x00,8-res);
    }
    else if(nType	==	PAD_ISO_2)
    {
        memset(Out+datalen,0x80,1);
        memset(Out+datalen,0x00,7-res);
    }
    else if(nType	==	PAD_PKCS_7)
    {
        memset(Out+datalen,0x00,8-res);
    }
    else
    {
        return false;
    }

    return true;
}

void DES::SetSubKey(PSubKey pSubKey, const unsigned char Key[])
{
    bool K[64], *KL=&K[0], *KR=&K[28];
    ByteToBit(K, Key, 64);
    Transform(K, K, PC1_Table, 56);
    for(int i=0; i<16; ++i) {
        RotateL(KL, 28, LOOP_Table[i]);
        RotateL(KR, 28, LOOP_Table[i]);
        Transform((*pSubKey)[i], K, PC2_Table, 48);
    }
}

void DES::DES_Unit(unsigned char Out[], const unsigned char In[], const PSubKey pSubKey, bool Type)
{
    bool M[64], tmp[32], *Li=&M[0], *Ri=&M[32];
    ByteToBit(M, In, 64);
    Transform(M, M, IP_Table, 64);
    if( Type == ENCRYPT )
    {
        for(int i=0; i<16; ++i)
        {
            memcpy(tmp, Ri, 32);		//Ri[i-1] ����
            F_func(Ri, (*pSubKey)[i]);	//Ri[i-1]����ת����SBox���ΪP
            Xor(Ri, Li, 32);			//Ri[i] = P XOR Li[i-1]
            memcpy(Li, tmp, 32);		//Li[i] = Ri[i-1]
        }
    }
    else
    {
        for(int i=15; i>=0; --i)
        {
            memcpy(tmp, Ri, 32);		//Ri[i-1] ����
            F_func(Ri, (*pSubKey)[i]);	//Ri[i-1]����ת����SBox���ΪP
            Xor(Ri, Li, 32);			//Ri[i] = P XOR Li[i-1]
            memcpy(Li, tmp, 32);		//Li[i] = Ri[i-1]
        }
    }
    RotateL(M,64,32);					//Ri��Li��λ����M
    Transform(M, M, IPR_Table, 64);		//���������ת��
    BitToByte(Out, M, 64);				//��֯���ַ�
}

QString DES::RunDesEncode(const QString In, const QString Key)
{
    unsigned datalen = (In.length()/9+1)*8;
    unsigned keylen = ((Key.length()/9)+1)*8 < 24 ? ((Key.length()/9)+1)*8 : 24;
    unsigned char *out = (unsigned char *)malloc(datalen);

    //qDebug()<<In.length();
    //qDebug()<<datalen<<keylen;

    RunDes(ENCRYPT, ECB, (unsigned char *)In.toLatin1().data(), out, datalen, (unsigned char *)Key.toLatin1().data(), keylen);
    return  QString((char *)out);
}

/*
    keylen = 8;
    datalen = 8;
*/
void DES::FileDesEncode(QFile *fin, QFile *fout, unsigned char *key)
{
    unsigned char input[8];
    unsigned char output[8];

    if(fin->open(QIODevice::ReadOnly)&&fout->open(QIODevice::ReadWrite))
    {
        while(!fin->atEnd())
        {
            memset((void *)input,0,8);
            fin->read((char*)input, 8);
            RunDesEncode(input, output, key);
            fout->write((char*)output,8);
        }
    }

    fin->close();
    fout->close();
}

/*
    keylen = 8;
    datalen = 8;
*/
void DES::FileDesDecode(QFile *fin, QFile *fout, unsigned char *key)
{
    unsigned char input[8];
    unsigned char output[8];

    if(fin->open(QIODevice::ReadOnly)&&fout->open(QIODevice::ReadWrite))
    {
        while(!fin->atEnd())
        {
            memset((void *)input,0,8);
            fin->read((char*)input, 8);
            RunDesDecode(input, output, key);
            fout->write((char*)output,8);
        }
    }

    fin->close();
    fout->close();
}


QString DES::RunDesDecode(const QString In, const QString Key)
{
    unsigned datalen = (In.length()/9+1)*8;
    unsigned keylen = ((Key.length()/9)+1)*8 < 24 ? ((Key.length()/9)+1)*8 : 24;
    unsigned char *out = (unsigned char *)malloc(datalen);

    RunDes(DECRYPT, ECB, (unsigned char *)In.toLatin1().data(), out, datalen, (unsigned char *)Key.toLatin1().data(), keylen);
    return  QString((char *)out);
}

bool DES::RunDesEncode(const unsigned char *In, unsigned char *Out, const unsigned char *Key,
                       unsigned datalen, unsigned keylen, bool bMode)
{
    return RunDes(ENCRYPT, bMode, In, Out, datalen, Key, keylen);
}

bool DES::RunDesDecode(const unsigned char* In, unsigned char* Out, const unsigned char* Key,
                       unsigned datalen, unsigned keylen, bool bMode)
{
    return RunDes(DECRYPT, bMode, In, Out, datalen, Key, keylen);
}

bool DES::RunDes(bool bType,bool bMode,const unsigned char *In,
        unsigned char *Out,unsigned datalen,const unsigned char *Key,unsigned keylen)
{
    //�ж�����Ϸ���
    if(!(In && Out && Key && datalen && keylen>=8))
    {
        return false;
    }

    unsigned char* inbuf = new unsigned char[datalen + 8];
    
    memset(inbuf, 0x00, sizeof(inbuf));
    memcpy(inbuf, In, datalen);
    unsigned char* tempBuf;
    unsigned padlen = datalen;
    //ֻ����8�������������㳤���Լ����
    if(datalen & 0x00000007)
    {
        if (!RunPad(PAD_PKCS_7, In, datalen, inbuf, padlen))
        {
            delete []inbuf; 
            return false;
        }    
        tempBuf = inbuf;
    }
    else
    {
        tempBuf = inbuf;
    }

    bool m_SubKey[3][16][48];		//��Կ
    //���첢����SubKeys
    char nKey	=	(keylen>>3)>=3 ? 3: (keylen>>3);
    for(int i=0;i<nKey;i++)
    {
        SetSubKey(&m_SubKey[i],&Key[i<<3]);
    }

    if(bMode == ECB)	//ECBģʽ
    {
        if(nKey == 1)	//��Key
        {
            for(int i=0,j = padlen>>3;i<j;++i,Out+=8,tempBuf+=8)
            {
                DES_Unit(Out,tempBuf,&m_SubKey[0],bType);
            }
        }
        else
        if(nKey == 2)	//3DES 2Key
        {
            for(int i=0,j = padlen>>3;i<j;++i,Out+=8,tempBuf+=8)
            {
                DES_Unit(Out,tempBuf,&m_SubKey[0],bType);
                DES_Unit(Out,Out,&m_SubKey[1],!bType);
                DES_Unit(Out,Out,&m_SubKey[0],bType);
            }
        }
        else			//3DES 3Key
        {
            for(int i=0,j=padlen>>3;i<j;++i,Out+=8,tempBuf+=8)
            {
                DES_Unit(Out,tempBuf,&m_SubKey[bType? 2 : 0],bType);
                DES_Unit(Out,Out,&m_SubKey[1],!bType);
                DES_Unit(Out,Out,&m_SubKey[bType? 0 : 2],bType);
            }
        }
    }
    else				//CBCģʽ
    {
        unsigned char cvec[8] = "";	//Ťת����
        unsigned char cvin[8] = ""; //�м����

        if(nKey == 1)	//��Key
        {
            for(int i=0,j=padlen>>3;i<j;++i,Out+=8,tempBuf+=8)
            {
                if(bType == ENCRYPT)
                {
                    for(int j=0;j<8;++j)		//��������Ťת�������
                    {
                        cvin[j]	= tempBuf[j] ^ cvec[j];
                    }
                }
                else
                {
                    memcpy(cvin,tempBuf,8);
                }

                DES_Unit(Out,cvin,&m_SubKey[0],bType);

                if(bType == ENCRYPT)
                {
                    memcpy(cvec,Out,8);			//������趨ΪŤת����
                }
                else
                {
                    for(int j=0;j<8;++j)		//�������Ťת�������
                    {
                        Out[j]	=	Out[j] ^ cvec[j];
                    }
                    memcpy(cvec,cvin,8);			//�������趨ΪŤת����
                }
            }
        }
        else
        if(nKey == 2)	//3DES CBC 2Key
        {
            for(int i=0,j=padlen>>3;i<j;++i,Out+=8,tempBuf+=8)
            {
                if(bType == ENCRYPT)
                {
                    for(int j=0;j<8;++j)		//��������Ťת�������
                    {
                        cvin[j]	=	tempBuf[j] ^ cvec[j];
                    }
                }
                else
                {
                    memcpy(cvin,tempBuf,8);
                }

                DES_Unit(Out,cvin,&m_SubKey[0],bType);
                DES_Unit(Out,Out,&m_SubKey[1],!bType);
                DES_Unit(Out,Out,&m_SubKey[0],bType);

                if(bType == ENCRYPT)
                {
                    memcpy(cvec,Out,8);			//������趨ΪŤת����
                }
                else
                {
                    for(int j=0;j<8;++j)		//�������Ťת�������
                    {
                        Out[j]	=	Out[j] ^ cvec[j];
                    }
                    memcpy(cvec,cvin,8);			//�������趨ΪŤת����
                }
            }
        }
        else			//3DES CBC 3Key
        {
            for(int i=0,j=padlen >>3;i<j;++i,Out+=8,tempBuf+=8)
            {
                if(bType ==	ENCRYPT)
                {
                    for(int j=0;j<8;++j)		//��������Ťת�������
                    {
                        cvin[j]	= tempBuf[j] ^ cvec[j];
                    }
                }
                else
                {
                    memcpy(cvin,tempBuf,8);
                }

                DES_Unit(Out,cvin,&m_SubKey[bType ? 2 : 0],bType);
                DES_Unit(Out,Out,&m_SubKey[1],!bType);
                DES_Unit(Out,Out,&m_SubKey[bType ? 0 : 2],bType);

                if(bType == ENCRYPT)
                {
                    memcpy(cvec,Out,8);			//������趨ΪŤת����
                }
                else
                {
                    for(int j=0;j<8;++j)		//�������Ťת�������
                    {
                        Out[j] = Out[j] ^ cvec[j];
                    }
                    memcpy(cvec,cvin,8);			//�������趨ΪŤת����
                }
            }
        }
    }

    delete []inbuf; 

    return true;
}








