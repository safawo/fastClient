#ifndef Think_Utils_Md5
#define Think_Utils_Md5 

#include <QString>
#include <fstream>

/* Type define */
typedef unsigned char byte;
typedef unsigned int uint32;

class MD5
{
public:
    MD5();
    MD5(const void* input, size_t length);
    MD5(const QString& str);
    MD5(std::ifstream& in);

private:
    uint32 _state[4];	/* state (ABCD) */
    uint32 _count[2];	/* number of bits, modulo 2^64 (low-order word first) */
    byte _buffer[64];	/* input buffer */
    byte _digest[16];	/* message digest */
    bool _finished;		/* calculate finished ? */

    static const int r[64];
    //static const uint32 k[ 64 ]; //key
    static uint32 k[64];
    static const byte PADDING[64];	/* padding for calculate */
    static const char HEX[16];
    enum { BUFFER_SIZE = 1024 };

private:
    void update(const byte* input, size_t length);
    void final();
    void transform(const byte block[64]);
    void encode(const uint32* input, byte* output, size_t length);
    void decode(const byte* input, uint32* output, size_t length);
    QString bytesToHexString(const byte* input, size_t length);

    /* class uncopyable */
    MD5(const MD5&);
    MD5& operator=(const MD5&);

public:
    void update(const void* input, size_t length);
    void update(const QString& str);
    void update(std::ifstream& in);
    const byte* digest();
    QString toString();
    void reset();
};

#endif  
