#ifndef Think_Utils_Common
#define Think_Utils_Common

#define NULL       0
#define NULL_STR   ""
#define NULL_INT   0
#define NULL_BOOL  false

#define NULL_QSTR   QString("")

#define ASCII_NUL            00
#define ASCII_STX            02
#define ASCII_ETX            03
#define ASCII_ACK            06
 
//密码1的初始密码，这个值是与硬件约定
#define    INITGUESTPASSWORD            0X88
#define    INITEMPLPASSWORD             0X66

//定义卡类型枚举
enum CARDTYPE
{
    InitType = 0,
    GUESTROOMCARD = 1,
    EMPLROOMCARD,
    EMPLCARD,
    PROGRAMCARD,
    FAILSAFECARD,
    PASSAGEMODECARD,
    LOCKOUTCARD,
    VOIDLISTCARD,
    CHECKOUTCARD,
    INITCARD,
    DATACARD,
	TIMESYNCCARD,
	SETTINGCARD
};

#define    GUESTROOMCARDTYPE           0xCC       //客人房卡的类型
#define    EMPLROOMCARDTYPE            0xEE       //员工房卡类型
#define    EMPLCARDTYPE               0x99       //员工卡类型
#define    PROGRAMCARDTYPE             0x88      //编程卡类型
#define    FAILSAFECARDTYPE            0x55      //备用卡类型
#define    PASSAGEMODECARDTYPE         0x11      //通道卡类型
#define    LOCKOUTCARDTYPE             0xBB      //封锁卡类型
#define    VOIDLISTCARDTYPE            0xAA      //void-list卡类型
#define    CHECKOUTCARDTYPE            0x90
#define    INITCARDTYPE               0xF8
#define    DATACARDTYPE               0x66      //数据卡，读取锁日志
#define    TIMESYNCCARDTYPE           0x77      //时钟校验卡
#define    SETTINGCARDTYPE            0x67


//字符序列，在生成随机密码时由随机数生成的序列号来选择
#define   SEQUENCEOFCHAR           "0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ"


const unsigned char KeyA[6] = {0x11,0x22,0x33,0x44,0x55};

//定义常用的错误码，方便前后台的交互，范围为0x00000000~0xFFFFFFFF
#define      ERROR_SUCCESS_HOTEL                          0X00000000
#define      ERROR_DISCONNECTFAILE_HOTEL                   0X00000001    //断开写卡器失败
#define      ERROR_CONNECTFAILE_HOTEL                      0X00000002    //连接写卡器失败
#define      ERROR_UNKNOWNERROR_HOTEL                      0X00000003    //未知错误
#define      ERROR_STORAGEERROR_HOTEL                      0X00000004    //存储空间溢出或未支持的PC值
#define      ERROR_STORAGELOCK_HOTEL                       0X00000005    //存储空间被锁定
#define      ERROR_POWERERROR_HOTEL                        0X00000006    //电力不足
#define      ERROR_GETGUESTROOMFAILE_HOTEL                  0X00000007    //查询客户房信息失败
#define      ERROR_ADDGUESTROOMFAILE_HOTEL                  0X00000008    //向后台插入客房checkin信息失败
#define      ERROR_GETUIIFAILE_HOTEL                       0X00000009    //获取UII失败
#define      ERROR_ENCODERFAILE_HOTEL                      0X0000000A    //读卡器执行命令失败
#define      ERROR_GETEMPLCARDFAILE_HOTEL                   0X0000000B    //查询员工房信息失败
#define      ERROR_GETUSERGROUPFAILE_HOTEL                  0X0000000C    //查询用户组信息失败
#define      ERROR_GETEMPLINFOFAILE_HOTEL                   0X0000000D    //查询员工信息失败
#define      ERROR_GETPROGRAMINFOFAILE_HOTEL                 0X0000000E   //查询编程卡信息失败
#define      ERROR_GETFAILSAFEINFOFAILE_HOTEL                0X0000000F   //查询备用卡信息失败
#define      ERROR_GETPASSAGEINFOFAILE_HOTEL                 0X00000010   //查询通道卡信息失败
#define      ERROR_GETEMPLOYEEINFOFAILE_HOTEL                0X00000011   //查询员工信息失败
#define      ERROR_EMPLINFOEMPTY_HOTEL                      0X00000012   //查询员工信息为空
#define      ERROR_CARDISNOTMANAGECARD_HOTEL                 0X00000013   //非管理卡
#define      ERROR_CARDISNOTGUESTCARD_HOTEL                  0X00000014  //非客人房卡
#define      ERROR_CARDISNOTEMPLROOMCARD_HOTEL               0X00000015  //非员工房卡
#define      ERROR_CARDISNOTSPECIALCARD_HOTEL                0X00000016  //非特殊卡

#endif

