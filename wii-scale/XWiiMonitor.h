#include "XWiiIface.h"
#include <memory>

class XWiiMonitor
{
    public:
        XWiiMonitor();
        ~XWiiMonitor();
        std::unique_ptr<XWiiIface> Poll();

    private:
        struct xwii_monitor* monitor;
};
