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
 
//����1�ĳ�ʼ���룬���ֵ����Ӳ��Լ��
#define    INITGUESTPASSWORD            0X88
#define    INITEMPLPASSWORD             0X66

//���忨����ö��
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

#define    GUESTROOMCARDTYPE           0xCC       //���˷���������
#define    EMPLROOMCARDTYPE            0xEE       //Ա����������
#define    EMPLCARDTYPE               0x99       //Ա��������
#define    PROGRAMCARDTYPE             0x88      //��̿�����
#define    FAILSAFECARDTYPE            0x55      //���ÿ�����
#define    PASSAGEMODECARDTYPE         0x11      //ͨ��������
#define    LOCKOUTCARDTYPE             0xBB      //����������
#define    VOIDLISTCARDTYPE            0xAA      //void-list������
#define    CHECKOUTCARDTYPE            0x90
#define    INITCARDTYPE               0xF8
#define    DATACARDTYPE               0x66      //���ݿ�����ȡ����־
#define    TIMESYNCCARDTYPE           0x77      //ʱ��У�鿨
#define    SETTINGCARDTYPE            0x67


//�ַ����У��������������ʱ����������ɵ����к���ѡ��
#define   SEQUENCEOFCHAR           "0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ"


const unsigned char KeyA[6] = {0x11,0x22,0x33,0x44,0x55};

//���峣�õĴ����룬����ǰ��̨�Ľ�������ΧΪ0x00000000~0xFFFFFFFF
#define      ERROR_SUCCESS_HOTEL                          0X00000000
#define      ERROR_DISCONNECTFAILE_HOTEL                   0X00000001    //�Ͽ�д����ʧ��
#define      ERROR_CONNECTFAILE_HOTEL                      0X00000002    //����д����ʧ��
#define      ERROR_UNKNOWNERROR_HOTEL                      0X00000003    //δ֪����
#define      ERROR_STORAGEERROR_HOTEL                      0X00000004    //�洢�ռ������δ֧�ֵ�PCֵ
#define      ERROR_STORAGELOCK_HOTEL                       0X00000005    //�洢�ռ䱻����
#define      ERROR_POWERERROR_HOTEL                        0X00000006    //��������
#define      ERROR_GETGUESTROOMFAILE_HOTEL                  0X00000007    //��ѯ�ͻ�����Ϣʧ��
#define      ERROR_ADDGUESTROOMFAILE_HOTEL                  0X00000008    //���̨����ͷ�checkin��Ϣʧ��
#define      ERROR_GETUIIFAILE_HOTEL                       0X00000009    //��ȡUIIʧ��
#define      ERROR_ENCODERFAILE_HOTEL                      0X0000000A    //������ִ������ʧ��
#define      ERROR_GETEMPLCARDFAILE_HOTEL                   0X0000000B    //��ѯԱ������Ϣʧ��
#define      ERROR_GETUSERGROUPFAILE_HOTEL                  0X0000000C    //��ѯ�û�����Ϣʧ��
#define      ERROR_GETEMPLINFOFAILE_HOTEL                   0X0000000D    //��ѯԱ����Ϣʧ��
#define      ERROR_GETPROGRAMINFOFAILE_HOTEL                 0X0000000E   //��ѯ��̿���Ϣʧ��
#define      ERROR_GETFAILSAFEINFOFAILE_HOTEL                0X0000000F   //��ѯ���ÿ���Ϣʧ��
#define      ERROR_GETPASSAGEINFOFAILE_HOTEL                 0X00000010   //��ѯͨ������Ϣʧ��
#define      ERROR_GETEMPLOYEEINFOFAILE_HOTEL                0X00000011   //��ѯԱ����Ϣʧ��
#define      ERROR_EMPLINFOEMPTY_HOTEL                      0X00000012   //��ѯԱ����ϢΪ��
#define      ERROR_CARDISNOTMANAGECARD_HOTEL                 0X00000013   //�ǹ���
#define      ERROR_CARDISNOTGUESTCARD_HOTEL                  0X00000014  //�ǿ��˷���
#define      ERROR_CARDISNOTEMPLROOMCARD_HOTEL               0X00000015  //��Ա������
#define      ERROR_CARDISNOTSPECIALCARD_HOTEL                0X00000016  //�����⿨

#endif

