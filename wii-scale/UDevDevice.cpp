#include <system_error>
#include "UDevDevice.h"

UDevDevice::UDevDevice(struct udev_device *device)
{
    if (device == NULL)
    {
        throw std::invalid_argument("device is NULL");
    }

    this->device = device;
}

UDevDevice::~UDevDevice()
{
    udev_device_unref(this->device);
}

std::unique_ptr<UDevDevice> UDevDevice::GetParent()
{
    struct udev_device *parent = udev_device_get_parent(this->device);

    if (parent == NULL)
    {
        throw std::system_error(errno, std::system_category(), "Failed to find parent");
    }

    // Increment parent ref count so it isn't freed with child object
    udev_device_ref(this->device);

    return std::unique_ptr<UDevDevice>(new UDevDevice(parent));
}

std::string UDevDevice::GetAttrValue(const std::string &name)
{
    const char *attrVal = udev_device_get_sysattr_value(this->device, name.c_str());

    if (attrVal != NULL)
    {
        return std::string(attrVal);
    }
    else
    {
        return std::string();
    }
}
