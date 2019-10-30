#include <stdexcept>
#include <xwiimote.h>
#include "XWiiMonitor.h"

XWiiMonitor::XWiiMonitor()
{
    monitor = xwii_monitor_new(false, false);

    if (monitor == NULL)
    {
        throw std::runtime_error("Failed to create xwii_monitor");
    }
}

XWiiMonitor::~XWiiMonitor()
{
    xwii_monitor_unref(monitor);
}

std::unique_ptr<XWiiIface> XWiiMonitor::Poll()
{
    char *path = xwii_monitor_poll(monitor);

    if (path == NULL)
    {
        return nullptr;
    }

    std::unique_ptr<XWiiIface> iface(new XWiiIface(path));
    free(path);

    return iface;
}
