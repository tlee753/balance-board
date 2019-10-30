#include <memory>
#include <libudev.h>

class UDevDevice;

class UDev
{
    public:
        UDev();
        ~UDev();
        std::unique_ptr<UDevDevice> DeviceFromSyspath(const std::string &syspath);

    private:
        struct udev *udev;
};
