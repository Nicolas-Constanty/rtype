//
// Created by gaspar_q on 12/1/16.
//

#include <Network/UDP/ReceptionStatus.hpp>
#include <iostream>

int main()
{
    Network::UDP::ReceptionStatus<unsigned short>   status;

    std::cout << "Max short: " << std::numeric_limits<unsigned short>::max() << std::endl;

    std::cout << "===Empty===" << std::endl;
    std::cout << status << std::endl;
    std::cout << "===Receive 16===" << std::endl;
    status.Receiving(16);
    std::cout << status << std::endl;
    std::cout << "===Receive 7===" << std::endl;
    status.Receiving(7);
    std::cout << status << std::endl;
    std::cout << "===Receive 13, 14, 15===" << std::endl;
    status.Receiving(13);
    status.Receiving(14);
    status.Receiving(15);
    std::cout << status << std::endl;
    std::cout << "===Receive 20===" << std::endl;
    status.Receiving(20);
    std::cout << status << std::endl;
    std::cout << "===Receive 4, 10===" << std::endl;
    status.Receiving(4);
    status.Receiving(10);
    std::cout << status << std::endl;
    try
    {
        std::cout << "===Receive 1===" << std::endl;
        status.Receiving(1);
    }
    catch (std::out_of_range const &err)
    {
        std::cerr << "Index out of range: " << err.what() << std::endl;
    }
    for (unsigned short i = 25, max = std::numeric_limits<unsigned short>::max(); i < max; i+=5)
        status.Receiving(i);
    std::cout << "===Receive on limits===" << std::endl;
    std::cout << status << std::endl;
    std::cout << "===Receive 2===" << std::endl;
    status.Receiving(2);
    std::cout << status << std::endl;
    std::cout << "===Receive 6===" << std::endl;
    status.Receiving(6);
    std::cout << status << std::endl;

    std::cout << "===Check set===" << std::endl;
    std::cout << std::boolalpha << "2: " << status.IsSet(2) << std::endl;
    std::cout << std::boolalpha << "6: " << status.IsSet(6) << std::endl;
    std::cout << std::boolalpha << "65530: " << status.IsSet(65530) << std::endl;
    std::cout << std::boolalpha << "3: " << status.IsSet(3) << std::endl;
    std::cout << std::boolalpha << "65535: " << status.IsSet(65535) << std::endl;

    std::cout << std::endl << "======================================================" << std::endl << std::endl;

    Network::UDP::ReceptionStatus<uint16_t, uint32_t>   status1;

    std::cout << status1 << std::endl;
    status1.Receiving(4);
    status1.Receiving(5);
    status1.Receiving(12);
    status1.Receiving(20);
    status1.Receiving(30);
    status1.Receiving(24);
    status1.Receiving(6);
    status1.Receiving(41);
    std::cout << status1 << std::endl;

    std::cout << status1.sliceAt(30) << std::endl;

    status1.reset();

    status1.Receiving(0);

    std::cout << status1 << std::endl;
    std::cout << status1.sliceAt(0) << std::endl;
    status1.IsSet(1);
    status1.Receiving(1);
    status1.Receiving(2);
    std::cout << status1 << std::endl;
    std::cout << status1.sliceAt(1) << std::endl;
    status1.IsSet(1);
    return 0;
}