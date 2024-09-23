#include <iostream>
#include <libusb-1.0/libusb.h>
//initializing variables
libusb_context *context = nullptr;
libusb_init_option options;
libusb_device **list = nullptr;
libusb_device_handle *device_handle = nullptr;
ssize_t device_count;
int num_options;
int *configuration;

//for error handling
int result;

// USB DEVICE
uint16_t vendor_id = 0x04e8;
uint16_t product_id = 0x6860;
const uint8_t interface = 2;

// USER CHOICE
ssize_t choice;


void check(int info, std::string message)
{
    if (info < 0)
    {
        std::cerr << "[!] Failed to " << message << "... " << libusb_error_name(info) << std::endl;
    }
    else 
    {
        std::cout << "[*] - " << message << " was successful!" << std::endl;
    }
}
