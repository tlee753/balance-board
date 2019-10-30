#include <xwiimote.h>
#include <poll.h>

class XWiiIface
{
    public:
        explicit XWiiIface(const std::string &path);
        ~XWiiIface();
        bool HasBalanceBoard();
        bool EnableBalanceBoard();
        void Dispatch(unsigned int mask, struct xwii_event *event);
        void Disconnect();

    private:
        struct xwii_iface* device;
        std::string address;
        struct pollfd fds[1];
        bool sentDisconnect = false;
};
