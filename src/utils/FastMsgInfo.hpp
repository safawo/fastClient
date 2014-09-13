#ifndef Think_Utils_Fast_MsgInfo
#define Think_Utils_Fast_MsgInfo

#include <utils/UtilsDll.hpp>  

class Utils_API FastMsgInfo
{ 
public:
    enum MsgLevel{
        Msg_INFO,
        Msg_WARN,
        Msg_ERROR,
        Msg_FATAL
    };
     
public: 
    virtual FastMsgInfo::MsgLevel const& getLevel() const = 0;
    
    virtual QString const& getId() const = 0;
    virtual QString const& getInfo() const = 0;

    virtual ~FastMsgInfo(){};

};

#endif
