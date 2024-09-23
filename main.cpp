#include <cstdint>
#include <iostream>
#include <libusb-1.0/libusb.h>
#include <cstring>

int main() 
{
    //initializing variables
    libusb_context *context = nullptr;
    libusb_init_option options;
    libusb_config_descriptor *config;
    libusb_device **list = nullptr;
    libusb_device_handle *device_handle = nullptr;

    ssize_t device_count;
    int num_options;
    int *configuration;
    
    //for error handling
    int result;

    // INITIALIZE
    //result = libusb_init_context(&context, (libusb_init_option*)&options, num_options);
    result = libusb_init(&context);

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

    // Desired device 
    uint16_t vendor_id = 0x04e8;
    uint16_t product_id = 0x6860;
    const uint8_t interface = 2;


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
        if (vendor_id == desc.idVendor && product_id == desc.idProduct)
        {

            result = libusb_open(device, &device_handle);

            if (result < 0)
            {
                std::cerr << "[!] - Failed to open the deivce... " << libusb_error_name(result) << std::endl;
            }

            //result = libusb_set_configuration(device_handle, configuration);
            result = libusb_set_auto_detach_kernel_driver(device_handle, 1);

            if (result < 0)
            {
                std::cerr << "[!] - Failed to set configuration... " << libusb_error_name(result) << std::endl;
            }
            else 
            {
                std::cout << "[*] - Enabled" << std::endl;
            }

            result = libusb_claim_interface(device_handle, interface);

            if (result < 0)
            {
                std::cerr << "[!] - Failed ... " << libusb_error_name(result) << std::endl;
            }
            else 
            {
                std::cout << "[*] - Claim was successful!" << std::endl;
            }

            // Data to send
            unsigned char data_to_send[] = "hello";
            int actual_length;
            int timeout = 1000; // Timeout in milliseconds

            // Sending data
            result = libusb_bulk_transfer(device_handle, 0x02, data_to_send, sizeof(data_to_send) - 1, &actual_length, timeout);
            if (result < 0) {
                std::cerr << "[!] - Failed to send data: " << libusb_error_name(result) << std::endl;
            } else {
                std::cout << "[*] - Sent " << actual_length << " bytes: " << data_to_send << std::endl;
            }

            libusb_release_interface(device_handle, interface);
        }
        

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
