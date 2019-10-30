#include <system_error>
#include <cstring>
#include <xwiimote.h>
#include "XWiiIface.h"
#include "UDevDevice.h"
#include "BlueZDevice.h"

XWiiIface::XWiiIface(const std::string &path)
{
    int ret = xwii_iface_new(&device, path.c_str());

    if (ret)
    {
        throw std::system_error(-ret, std::system_category(), "Failed to connect to device " + path);
    }

    // Set up the pollfd structure ready for poll() in ::Dispatch
    memset(fds, 0, sizeof(fds));
    fds[0].fd = xwii_iface_get_fd(device);
    fds[0].events = POLLIN;

    UDev udev;
    std::unique_ptr<UDevDevice> board = udev.DeviceFromSyspath(path);
    std::unique_ptr<UDevDevice> parent = board->GetParent();
    this->address = parent->GetAttrValue("address");
}

XWiiIface::~XWiiIface()
{
    xwii_iface_unref(device);
}

bool XWiiIface::HasBalanceBoard()
{
    return xwii_iface_available(device) & XWII_IFACE_BALANCE_BOARD;
}

bool XWiiIface::EnableBalanceBoard()
{
    if (!HasBalanceBoard())
    {
        return false;
    }

    int ret = xwii_iface_open(device, XWII_IFACE_BALANCE_BOARD);

    if (ret)
    {
        throw std::system_error(-ret, std::system_category(), "Failed to enable Balance Board");
    }

    return true;
}

void XWiiIface::Dispatch(unsigned int mask, struct xwii_event *event)
{
    for (;;)
    {
        // Block until an event is ready to be consumed
        int ret = poll(fds, (sizeof(fds) / sizeof(fds[0])), -1);

        if (ret < 0)
        {
            throw std::system_error(-ret, std::system_category(), "Polling for events failed");
        }

        for (;;)
        {
            ret = xwii_iface_dispatch(device, event, sizeof(*event));

            if (ret == -EAGAIN)
            {
                break;
            }

            if (ret)
            {
                throw std::system_error(-ret, std::system_category(), "Read failed");
            }

            if (event->type & mask)
            {
                return;
            }
        }
    }
}

void XWiiIface::Disconnect()
{
    if (!this->sentDisconnect)
    {
        BlueZDevice bluez(this->address, "Nintendo RVL-WBC-01");
        bluez.Disconnect();

        this->sentDisconnect = true;
    }
}
