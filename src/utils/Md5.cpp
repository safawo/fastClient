#include <utils/Md5.hpp>
#include <QDebug>
#include <math.h>


/* Operate define */
#define F(x, y, z) (((x)&(y))|((~x)&(z)))
#define G(x, y, z) (((x)&(z))|((y)&(~z)))
#define H(x, y, z) ((x)^(y)^(z))
#define I(x, y, z) ((y)^((x)|(~z)))

/*
    ROTATE_LEFT rotates x left n bits.
*/
#define ROTATE_LEFT(x, n) (((x) << (n)) | ((x) >> (32-(n))))

/*
    r specifies the per-round shift amounts
*/

const int MD5::r[64] = {
    7, 12, 17, 22,  7, 12, 17, 22,  7, 12, 17, 22,  7, 12, 17, 22,
    5,  9, 14, 20,  5,  9, 14, 20,  5,  9, 14, 20,  5,  9, 14, 20,
    4, 11, 16, 23,  4, 11, 16, 23,  4, 11, 16, 23,  4, 11, 16, 23,
    6, 10, 15, 21,  6, 10, 15, 21,  6, 10, 15, 21,  6, 10, 15, 21
};


//const uint32 MD5::k[64] = {
//    0xd76aa478, 0xe8c7b756, 0x242070db, 0xc1bdceee,
//    0xf57c0faf, 0x4787c62a, 0xa8304613, 0xfd469501,
//    0x698098d8, 0x8b44f7af, 0xffff5bb1, 0x895cd7be,
//    0x6b901122, 0xfd987193, 0xa679438e, 0x49b40821,

//    0xf61e2562, 0xc040b340, 0x265e5a51, 0xe9b6c7aa,
//    0xd62f105d, 0x02441453, 0xd8a1e681, 0xe7d3fbc8,
//    0x21e1cde6, 0xc33707d6, 0xf4d50d87, 0x455a14ed,
//    0xa9e3e905, 0xfcefa3f8, 0x676f02d9, 0x8d2a4c8a,

//    0xfffa3942, 0x8771f681, 0x6d9d6122, 0xfde5380c,
//    0xa4beea44, 0x4bdecfa9, 0xf6bb4b60, 0xbebfbc70,
//    0x289b7ec6, 0xeaa127fa, 0xd4ef3085, 0x04881d05,
//    0xd9d4d039, 0xe6db99e5, 0x1fa27cf8, 0xc4ac5665,

//    0xf4292244, 0x432aff97, 0xab9423a7, 0xfc93a039,
//    0x655b59c3, 0x8f0ccc92, 0xffeff47d, 0x85845dd1,
//    0x6fa87e4f, 0xfe2ce6e0, 0xa3014314, 0x4e0811a1,
//    0xf7537e82, 0xbd3af235, 0x2ad7d2bb, 0xeb86d391
//};

uint32 MD5::k[64] = {0};

const byte MD5::PADDING[64] = { 0x80 };

const char MD5::HEX[16] = {
    '0', '1', '2', '3',
    '4', '5', '6', '7',
    '8', '9', 'a', 'b',
    'c', 'd', 'e', 'f'
};

MD5::MD5()
{
    reset();
}

//MD5::MD5(const MD5 &)
//{

//}

//MD5& MD5::operator=(const MD5&)
//{

//}

MD5::MD5(const QString &str)
{
    reset();
    update(str);
}

MD5::MD5(const void *input, size_t length)
{
    reset();
    update(input, length);
}

MD5::MD5(std::ifstream &in)
{
    reset();
    update(in);
}

void MD5::reset()
{
    _finished = false;


    /*Initial Key*/
    //Use binary integer part of the sines of integers as constants:
    /*
        for i from 0 to 63
            k[i] := floor(abs(sin(i + 1)) ¡Á 2^32)
    */
    for(int i=0; i<64; i++)
        k[i] = floor(fabs(sin(double(i+1)))*pow((double)2,32));

    /* reset number of bits. */
    _count[0] = _count[1] = 0;
    /* Load magic initialization constants. */
    /*
        //Initialize variables:
        var int _state[0] := 0x67452301
        var int _state[1] := 0xEFCDAB89
        var int _state[2] := 0x98BADCFE
        var int _state[3] := 0x10325476
    */
    _state[0] = 0x67452301;
    _state[1] = 0xefcdab89;
    _state[2] = 0x98badcfe;
    _state[3] = 0x10325476;



}

const byte* MD5::digest()
{
    if (!_finished)
    {
        _finished = true;
        final();
    }

    return _digest;
}

void MD5::update(const void *input, size_t length)
{
    update((const byte*)input, length);
}

void MD5::update(const QString &str)
{
    update((const byte*)str.toLatin1().data(), str.length());
}

void MD5::update(std::ifstream &in)
{
    if (!in)
    {
        return;
    }

    std::streamsize length;
    char buffer[BUFFER_SIZE];
    while (!in.eof())
    {
        in.read(buffer, BUFFER_SIZE);
        length = in.gcount();
        if (length > 0)
        {
            update(buffer, length);
        }
    }
    in.close();
}

/*
    MD5 block update operation. Continues an MD5 message-digest
    operation, processing another message block, and updating the
    context.
*/
void MD5::update(const byte *input, size_t length)
{
    uint32 i, index, partLen;

    _finished = false;

    /* Compute number of bytes mod 64 */
    index = (uint32)((_count[0] >> 3) & 0x3f);//0x3f = 63

    /* update number of bits */
    if ((_count[0] += ((uint32)length << 3)) < ((uint32)length << 3))
    {
        ++_count[1];

    }
    _count[1] += ((uint32)length >> 29);

    //qDebug()<<_count[0]<<_count[1];

    partLen = 64 - index;

    /* transform as many times as possible. */
    if (length >= partLen)
    {

        memcpy(&_buffer[index], input, partLen);
        transform(_buffer);

        for (i = partLen; i + 63 < length; i += 64)
        {
            transform(&input[i]);
        }
        index = 0;

    }
    else
    {
        i = 0;
    }

    /* Buffer remaining input */
    memcpy(&_buffer[index], &input[i], length - i);
}

/*
    MD5 finalization. Ends an MD5 message-_digest operation, writing the
    the message _digest and zeroizing the context.
*/
void MD5::final()
{
    byte bits[8];
    uint32 oldState[4];
    uint32 oldCount[2];
    uint32 index, padLen;

    /* Save current state and count. */
    memcpy(oldState, _state, 16);
    memcpy(oldCount, _count, 8);

    /* Save number of bits */
    encode(_count, bits, 8);

    /* Pad out to 56 mod 64. */
    index = (uint32)((_count[0] >> 3) & 0x3f);
    padLen = (index < 56) ? (56 - index) : (120 - index);
    update(PADDING, padLen);

    /* Append length (before padding) */
    update(bits, 8);

    /* Store state in digest */
    encode(_state, _digest, 16);

    /* Restore current state and count. */
    memcpy(_state, oldState, 16);
    memcpy(_count, oldCount, 8);
}

void MD5::transform(const byte block[64])
{

    /*
        //Initialize hash value for this chunk:
        var int a := _state[0]
        var int b := _state[1]
        var int c := _state[2]
        var int d := _state[3]
    */
    uint32 a = _state[0], b = _state[1], c = _state[2], d = _state[3];
    uint32 temp;
    uint32 w[16];
    uint32 f;
    int i;
    int g;

    /*
        break chunk into sixteen 32-bit little-endian words w[i], 0 ¡Ü i ¡Ü 64
    */
    decode(block, w, 64);

    /*
    //Main loop:
    for i from 0 to 63
        if 0 ¡Ü i ¡Ü 15 then
            f := (b and c) or ((not b) and d)
            g := i
        else if 16 ¡Ü i ¡Ü 31
            f := (d and b) or ((not d) and c)
            g := (5¡Ái + 1) mod 16
        else if 32 ¡Ü i ¡Ü 47
            f := b xor c xor d
            g := (3¡Ái + 5) mod 16
        else if 48 ¡Ü i ¡Ü 63
            f := c xor (b or (not d))
            g := (7¡Ái) mod 16

        temp := d
        d := c
        c := b
        b := leftrotate((a + f + k[i] + w[g]),r[i]) + b
        a := temp
    Next i
    */
    for(i=0; i<64; i++)
    {
        if(i>=0 && i<16)
        {
            f = F(b, c, d);
            g = i;
        }
        else if(i>=16 && i<32)
        {
            f = G(b, c, d);
            g = (5*i + 1)%16;
        }
        else if(i>=32 && i<48)
        {
            f = H(b, c, d);
            g = (3*i + 5)%16;
        }
        else if(i>=48 && i<64)
        {
            f = I(b, c, d);
            g = (7*i)%16;
        }

        temp = d;
        d = c;
        c = b;
        b = ROTATE_LEFT((a + f + k[i] + w[g]), r[i]) + b;
        a = temp;

    }

    /*
        //Add this chunk's hash to result so far:
        _state[0] := _state[0] + a
        _state[1] := _state[1] + b
        _state[2] := _state[2] + c
        _state[3] := _state[3] + d
    */
    _state[0] += a;
    _state[1] += b;
    _state[2] += c;
    _state[3] += d;
}

/*
    Encodes input (ulong) into output (byte). Assumes length is a multiple of 4.
*/
void MD5::encode(const uint32 *input, byte *output, size_t length)
{
    for (size_t i = 0, j = 0; j < length; ++i, j += 4)
    {
        output[j]= (byte)(input[i] & 0xff);
        output[j + 1] = (byte)((input[i] >> 8) & 0xff);
        output[j + 2] = (byte)((input[i] >> 16) & 0xff);
        output[j + 3] = (byte)((input[i] >> 24) & 0xff);
    }
}

/*
    Decodes input (byte) into output (ulong). Assumes length is a multiple of 4.
*/
void MD5::decode(const byte *input, uint32 *output, size_t length)
{
    for (size_t i = 0, j = 0; j < length; ++i, j += 4)
    {
        output[i] = ((uint32)input[j]) | (((uint32)input[j + 1]) << 8) |
                (((uint32)input[j + 2]) << 16) | (((uint32)input[j + 3]) << 24);
    }
}

/* Convert byte array to hex string. */
QString MD5::bytesToHexString(const byte *input, size_t length)
{
    QString str;
    str.reserve(length << 1);//fine tuning QString's memory usage

    for (size_t i = 0; i < length; ++i) {
        int temp = input[i];
        int a = temp / 16;
        int b = temp % 16;
        str.append(HEX[a]);
        str.append(HEX[b]);
    }

    return str;
}

/* Convert digest to string value */
QString MD5::toString()
{
    return bytesToHexString(digest(), 16);
}



