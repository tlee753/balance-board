#include <memory>
#include <libudev.h>
#include "UDev.h"

class UDevDevice
{
    public:
        ~UDevDevice();
        std::unique_ptr<UDevDevice> GetParent();
        std::string GetAttrValue(const std::string &name);

    private:
        explicit UDevDevice(struct udev_device *device);
        struct udev_device *device;

    friend std::unique_ptr<UDevDevice> UDev::DeviceFromSyspath(const std::string &syspath);
};
