#ifndef Think_Utils_Fast_MsgBuff
#define Think_Utils_Fast_MsgBuff

#include <utils/UtilsDll.hpp>  

#include <utils/FastMsgInfo.hpp>

class Utils_API FastMsgBuff
{ 
public: 
    virtual void reLoad() = 0;

    virtual FastMsgInfo const& getMsg(QString const& msgId) const = 0;

};

Utils_API FastMsgBuff& msgBuff();  

#endif
