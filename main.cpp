#include <iostream>
#include <libusb-1.0/libusb.h>

int main() 
{
    libusb_context *context = nullptr;
    libusb_init_option options;
    libusb_device **list = nullptr;

    ssize_t device_count;
    int num_options;
    
    //for error handling
    int result;

    // INITIALIZE
    result = libusb_init_context(&context, (libusb_init_option*)&options, num_options);

    if (result < 0)
    {
        std::cerr << "[!] - Failed to initialize: " << libusb_error_name(result) << std::endl;
        libusb_exit(context);
        return 1;
    } 
    else 
    {
        std::cout << "[*] - Initialization was successful!" << std::endl;
    }

    // DETECT USB DEVIICES 
    device_count = libusb_get_device_list(context, &list);

    if (device_count < 0) 
    {
        std::cerr << "[!] - Failed to get devices: " << libusb_error_name(device_count) << std::endl;
        libusb_exit(context);
        return 1;
    }
    else 
    {
        std::cout << "[*] - Devices found: " << device_count << std::endl;
    }


    // GET DEVICE DESCRIPTORS 
    for (ssize_t i = 0; i < device_count; ++i)
    {
        libusb_device *device = list[i];
        libusb_device_descriptor desc;

        result = libusb_get_device_descriptor(device, &desc);

        if (result < 0)
        {
            std::cerr << "[!] - Failed to get device description: " << libusb_error_name(result) << std::endl;
            continue;
        }

        // MATCH THE DESIIRED USB DEVICE 
        

    } 



    // OPEN A CONNECTION TO THE DEVICE  


    // SET CONFIGURATION 

    
    // CLIAM AN INTERFACE 

    
    // TRANSFER DATA VIA BULK TRANSFER 


    // RELEASE THE INTERFACE AND CLOSE THE DEVICE
    libusb_free_device_list(list, 1);
    libusb_exit(context);

    return 0;
}
