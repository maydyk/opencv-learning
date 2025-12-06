#include "opencv2/opencv.hpp"
#include "opencv2/core/ocl.hpp"
#include <ranges>

using namespace std;
using namespace cv;
using namespace cv::ocl;

int main()
{
    if (!haveOpenCL()) {
        cout << "OpenCL is not available." << std::endl;
        return -1;
    }

    vector<PlatformInfo> info;
    getPlatfomsInfo(info);
    cout << "Platforms available: " << info.size() << endl;

    ranges::for_each(info, [](const PlatformInfo& sdk) {
        cout << "\n******SDK*******" << endl;
        cout << "Name: " << sdk.name() << endl;
        cout << "Vendor: " << sdk.vendor() << endl;
        cout << "Version: " << sdk.version() << endl;
        cout << "Number of devices: " << sdk.deviceNumber() << endl;

        for (int i=0; i<sdk.deviceNumber(); i++){
            if (sdk.deviceNumber()<1) {
                cout << "Unknown device" << endl;
                return;
            }

            Device device;
            sdk.getDevice(device,i);
            cout << "\n\n*********************\n Device " << i+1 << endl;

            cout << "Vendor ID: " << device.vendorID() << endl;
            cout << "Vendor name: " << device.vendorName() << endl;
            cout << "Name: " << device.name() << endl;
            cout << "Driver version: " << device.driverVersion() << endl;
            if (device.isAMD()) cout << "Is an AMD device" << endl;
            if (device.isIntel()) cout << "Is a Intel device" << endl;
            cout << "Global Memory size: " << device.globalMemSize() << endl;
            cout << "Memory cache size: " << device.globalMemCacheSize() << endl;
            cout << "Memory cache type: " << device.globalMemCacheType() << endl;
            cout << "Local Memory size: " << device.localMemSize() << endl;
            cout << "Local Memory type: " << device.localMemType() << endl;
            cout << "Max Clock frequency: " << device.maxClockFrequency() << endl;
        }
    });

    return 0;
}

