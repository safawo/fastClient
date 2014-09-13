#ifndef Think_Utils_DES
#define Think_Utils_DES 

typedef bool Bit;
typedef bool (*PSubKey)[16][48];

//���ܽ���
enum
{
    ENCRYPT	= 0,	//! ����
    DECRYPT			//! ����
};

//DES�㷨��ģʽ
enum
{
    ECB		=	0,	//! ECBģʽ
    CBC				//! CBCģʽ
};

//Pad����ģʽ
enum
{
    PAD_ISO_1 =	0,	//! ISO_1��䣺���ݳ��Ȳ���8���صı�������0x00���㣬���Ϊ8���صı�������8��0x00
    PAD_ISO_2,		//! ISO_2��䣺���ݳ��Ȳ���8���صı�������0x80,0x00..���㣬���Ϊ8���صı�������0x80,0x00..0x00
    PAD_PKCS_7		//! PKCS7��䣺���ݳ��ȳ�8����Ϊn,��(8-n)����Ϊ8�ı���
};

class QString;
class QFile;

class DES
{
public:
    DES();
    ~DES();

private:
    static const int IP_Table[64];
    static const int IPR_Table[64];
    static const int E_Table[48];
    static const int P_Table[32];
    static const int PC1_Table[56];
    static const int PC2_Table[48];
    static const int LOOP_Table[16];
    static const int S_Box[8][4][16];

    unsigned keylen;

private:
    static void ByteToBit(Bit *Out, const unsigned char *In, int bits);
    static void BitToByte(unsigned char *Out, const Bit *In, int bits);
    static void RotateL(Bit *In, int len, int loop);
    static void Xor(Bit *InA, const Bit *InB, int len);
    static void Transform(Bit *Out, Bit *In, const int *Table, int len);
    static void S_func(Bit Out[32], const Bit In[48]);
    static void F_func(Bit In[], const Bit Ki[]);

    bool RunPad(int nType, const unsigned char* In,
        unsigned datalen, unsigned char* Out, unsigned& padlen);
    void SetSubKey(PSubKey pSubKey, const unsigned char Key[8]);
    //void Encode(char Out[8], const char In[8], const PSubKey pSubKey);
    //void Decode(char Out[8], const char In[8], const PSubKey pSubKey);
    void DES_Unit(unsigned char Out[8], const unsigned char In[8], const PSubKey pSubKey, bool Type);

    bool RunDes(bool bType,bool bMode,const unsigned char* In,
        unsigned char* Out,unsigned datalen,const unsigned char* Key,unsigned keylen);

public:
    void FileDesEncode(QFile *fin, QFile *fout, unsigned char *key);
    void FileDesDecode(QFile *fin, QFile *fout, unsigned char *key);

    QString RunDesEncode(const QString In, const QString Key);
    QString RunDesDecode(const QString In, const QString Key);

    bool RunDesEncode(const unsigned char* In, unsigned char* Out, const unsigned char* Key,
        unsigned datalen = 8, unsigned keylen = 8, bool bMode = ECB);
    bool RunDesDecode(const unsigned char *In, unsigned char *Out, const unsigned char *Key,
        unsigned datalen = 8, unsigned keylen = 8, bool bMode = ECB);

};




#endif 
