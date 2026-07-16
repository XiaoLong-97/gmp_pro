

#include <tools/gmp_sil/udp_helper/asio_udp_helper.hpp>
#include <iostream>
#include <stdlib.h>

int main()
{
    std::cout << "[GMP] Hello World!\n";

    asio_udp_helper *helper = asio_udp_helper::parse_network_config("network.json");

    if (helper == nullptr)
    {
        std::cout << "Cannot create ASIO Helper.\r\n" << std::endl;
        exit(1);
    }

    // Connect to Simulink Model
    helper->connect_to_target();

    // enable this program acknowledge "Stop" Command from Simulink
    helper->server_ack_cmd();

    // Message buffer
    double tx[3] = {0};
    double rx[3] = {0};

    // Send the first message to enable the Simulink model.
    helper->send_msg((char *)tx, sizeof(tx));

    for (int i = 0; i < 1000; i++)
    {
        // Receive message from Simulink
        if (helper->recv_msg((char *)rx, sizeof(rx)))
        {
            std::cout << "receive complete." << std::endl;
            system("@pause");
            exit(0);
        }

        // operation here
        tx[0] = rx[1];
        tx[1] = sin(rx[0]);
        tx[2] = rx[0];

        // Send message to simulink
        helper->send_msg((char *)tx, sizeof(tx));
    }

    delete helper;
}
