class BlueZDevice
{
    public:
        explicit BlueZDevice(const std::string &address, const std::string &name);
        void Disconnect();

    private:
        std::string path;
};
