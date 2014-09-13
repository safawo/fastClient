#ifndef Think_Utils_Fast_MsgBox
#define Think_Utils_Fast_MsgBox

#include <utils/UtilsDll.hpp>
#include <utils/Common.hpp>

class Utils_API FastMsgBox  
{
public:
    virtual void information(QString const& infoMsg, QString const& informative) = 0;
    virtual bool question(QString const& questMsg, QString informative) = 0; 
    virtual bool warning(QString const& warnMsg, QString informative) = 0;
    virtual void error(QString const& errorMsg, QString informative) = 0;

    virtual void information(QString const& infoMsg) = 0;
    virtual bool question(QString const& questMsg) = 0; 
    virtual bool warning(QString const& warnMsg) = 0; 
    virtual void error(QString const& errorMsg) = 0;  

    virtual void operateSuccess() = 0; 
     
    virtual ~FastMsgBox(){};

     
};

#endif

Utils_API FastMsgBox& msgBox();  