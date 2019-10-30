#include <system_error>
#include "UDevDevice.h"

UDev::UDev()
{
    this->udev = udev_new();

    if (this->udev == NULL)
    {
        throw std::system_error(-errno, std::system_category(), "Failed to create udev context");
    }
}

UDev::~UDev()
{
    udev_unref(udev);
}

std::unique_ptr<UDevDevice> UDev::DeviceFromSyspath(const std::string &syspath)
{
    struct udev_device *device = udev_device_new_from_syspath(this->udev, syspath.c_str());

    if (device == NULL)
    {
        throw std::system_error(errno, std::system_category(), "Failed to create device");
    }

    return std::unique_ptr<UDevDevice>(new UDevDevice(device));
}
