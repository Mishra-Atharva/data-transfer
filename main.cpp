#include <cstring>
#include <libusb-1.0/libusb.h>
#include "variables.h"

void send_data()
{
    unsigned char data_to_send[] = "THIS IS A DATA SEND TEST!";
    int actual_length;
    int timeout = 1000;

    //Sending the data 
    result = libusb_bulk_transfer(device_handle, 0x02, data_to_send, sizeof(data_to_send) - 1, &actual_length, timeout);
    check(result, "Sending data");
}

void open_and_claim(libusb_device *device)
{
    std::cout << "\n" << std::endl;
    // Opening the usb device
    result = libusb_open(device, &device_handle);
    check(result, "Opening connection to device");

    // Enabling auto detach
    result = libusb_set_auto_detach_kernel_driver(device_handle, 1);
    check(result, "Enabling Auto Detach");

    // Claiming interface 
    result = libusb_claim_interface(device_handle, interface);
    check(result, "Claiming Interface");

    send_data();
}

void setup_usb()
{
    // INITIALIZE
    //result = libusb_init_context(&context, (libusb_init_option*)&options, num_options);
    result = libusb_init(&context);
    check(result, "Initialization");

    // DETECT USB DEVIICES 
    device_count = libusb_get_device_list(context, &list);
    check(device_count, "Device detection");

    std::cout << "\n\n[ SELECT AVALIABLE DEVICE ]" << std::endl;

    // GET DEVICE DESCRIPTORS 
    for (ssize_t i = 0; i < device_count; ++i)
    {
        unsigned char information[256];
        libusb_device *device = list[i];
        libusb_device_descriptor desc;

        result = libusb_get_device_descriptor(device, &desc);
        if (result < 0)
        {
            continue;
        }

        result = libusb_open(device, &device_handle);
        if (result < 0)
        {
            continue;
        }

        if (desc.iManufacturer)
        {
            result = libusb_get_string_descriptor_ascii(device_handle, desc.iManufacturer, information, sizeof(information));
            if (result > 0)
            {
                std::cout <<  "[" << i << "] " << information << std::endl;
            }
        }

        libusb_close(device_handle);
    }

    // Getting user choice
    std::cout << "SELECT: ";
    std::cin >> choice;

    libusb_device *device = list[choice];

    result = libusb_open(device, &device_handle);

    while (result < 0)
    {
        std::cout << "PLEASE ENTER A CHOICE BASED ON THE AVALIABLE OPTIONS!\nSELECT: ";
        std::cin >> choice;
        device = list[choice];
        result = libusb_open(device, &device_handle);
    }
    libusb_close(device_handle);

    // Opening the selected device
    open_and_claim(device);
}

int main() 
{
    setup_usb();

    // OPEN A CONNECTION TO THE DEVICE  


    // SET CONFIGURATION 

    
    // CLIAM AN INTERFACE 

    
    // TRANSFER DATA VIA BULK TRANSFER 


    // RELEASE THE INTERFACE AND CLOSE THE DEVICE
    libusb_free_device_list(list, 1);
    libusb_exit(context);

    return 0;
}
