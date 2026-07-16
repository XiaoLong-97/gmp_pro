
// Debug method: Ctrl + Alt + P, attach to Program, select Matlab

// Compile Command:
// mex '-I"E:\lib\gmp_pro"' '-I"E:\lib\gmp_pro\third_party"' MEXFunction_UDP.cpp

#include "mex.hpp"
#include "mexAdapter.hpp"
#include <codecvt>
#include <fstream>
#include <locale>
#include <memory>
#include <stdint.h>
#include <string>
#include <vector>

// Need to define WIN32 because each version of windows has slightly different ways of handling networking
#include <SDKDDKVer.h>

// ASIO library
#define ASIO_STANDALONE
#include <boost/asio.hpp>

using udp = boost::asio::ip::udp;

// json library
#include <nlohmann/json.hpp>

// udp helper
#include <tools/gmp_sil/udp_helper/asio_udp_helper.hpp>

using json = nlohmann::json;

using matlab::data::ArrayType;

class MexFunction : public matlab::mex::Function
{
  private:
    std::shared_ptr<matlab::engine::MATLABEngine> matlabPtr;

    // BOOST::ASIO
    boost::system::error_code ecVAR;
    boost::asio::io_context context;

    std::string target_ip;

    uint32_t recv_port;
    uint32_t trans_port;
    uint32_t cmd_recv_port;
    uint32_t cmd_trans_port;

    asio_udp_helper *udp_helper;

  public:
    // ctor
    MexFunction()
    {
        matlabPtr = getEngine();
        matlab_print("UDP Server helper: Ready!\r\n");
        udp_helper = nullptr;
    }

    // dtor
    ~MexFunction()
    {
        matlab_print("UDP Server helper: Bye!\r\n");

        if (udp_helper != nullptr)
        {
            udp_helper->release_connect();
            delete udp_helper;
            udp_helper = nullptr;
        }
    }

    // Helper function to print output string on MATLAB command prompt.
    void matlab_print(std::string str)
    {
        matlab::data::ArrayFactory factory;
        matlabPtr->feval(u"fprintf", 0, std::vector<matlab::data::Array>({factory.createScalar(str.c_str())}));
    }

    // Helper function to print error output on MATLAB command prompt.
    // After calling this function, MATLAB will exit the process running, in another word, the lib will exit.
    void matlab_error(std::string str)
    {
        matlab::data::ArrayFactory factory;
        matlabPtr->feval(u"error", 0, std::vector<matlab::data::Array>({factory.createScalar(str.c_str())}));
    }

    // Entry Point
    void operator()(matlab::mex::ArgumentList outputs, matlab::mex::ArgumentList inputs)
    {

        // matlab_print({"MEX Function Hello World!\r\n"});

        // input parameters:
        // Operation string
        // Parameters
        //
        if (inputs[0].getType() != ArrayType::MATLAB_STRING)
        {
            matlab_error("First parameter is a command string.\r\n");
        }

        matlab::data::String cmd_in = std::move(inputs[0][0]);

        matlab::data::ArrayFactory factory;

#if defined DEBUG
        matlab_print("Command received: ");
        matlabPtr->feval(u"fprintf", 0, std::vector<matlab::data::Array>({factory.createScalar(cmd_in.c_str())}));
        matlab_print("\r\n");
#endif // DEBUG

        // Welcome Command
        // ("Hello")
        if (cmd_in == u"Hello")
        {
            matlab_print("Welcome to GMP Simulink SIL & PIL Simulation Tool kits.\r\n");
            return;
        }
        // ("config_network","ip_addr", output_port, input_port, output_cmd_port, input_cmd_port)
        else if (cmd_in == u"config_network")
        {
            checkArgumentsConfigNetwork(outputs, inputs);

            // ip addr
            matlab::data::String target_address = std::move(inputs[1][0]);

            // output port is the first element
            matlab::data::TypedArray<double> target_output_port = std::move(inputs[2]);

            // input port is the second element
            matlab::data::TypedArray<double> target_input_port = std::move(inputs[3]);

            // output command port
            matlab::data::TypedArray<double> cmd_output_port = std::move(inputs[4]);

            // input command port
            matlab::data::TypedArray<double> cmd_input_port = std::move(inputs[5]);

            std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> unicode_enc;

            // reg all the communication parameters

            // record all linking informations
            try
            {
                target_ip = unicode_enc.to_bytes(std::wstring((wchar_t *)target_address.c_str()));
            }
            catch (const std::exception &e)
            {
                std::cerr << e.what() << std::endl;
            }
            recv_port = (uint32_t)target_output_port[0];
            trans_port = (uint32_t)target_input_port[0];
            cmd_recv_port = (uint32_t)cmd_output_port[0];
            cmd_trans_port = (uint32_t)cmd_input_port[0];

            // json file objects
            json network_config;

            // save json file
            network_config["target_address"] = target_ip;
            network_config["receive_port"] = recv_port;
            network_config["transmit_port"] = trans_port;
            network_config["command_recv_port"] = cmd_recv_port;
            network_config["command_trans_port"] = cmd_trans_port;

            matlab_print("\r\n [INFO] network config .json is generated.\r\n");

            // show json content
            std::stringstream json_src;
            json_src << network_config;

            matlabPtr->feval(u"fprintf", 0, std::vector<matlab::data::Array>({factory.createScalar(json_src.str())}));

            matlab_print("\r\n \r\n");

            // create .json file and save config
            std::fstream network_json_file("network.json", std::fstream::in | std::fstream::out);
            // network_json_file.clear();

            if (!network_json_file.is_open())
            {
                matlab_print("[WARN] Cannot create or open `network.json`, .json file is not generated.");
            }
            else
            {
                network_json_file << network_config;
                network_json_file.close();
                matlab_print("[INFO] .json file is generated.");
            }

            // Create UDP Helper Object
            if (udp_helper != nullptr)
            {
                free(udp_helper);
            }

            udp_helper = new asio_udp_helper(target_ip, recv_port, trans_port, cmd_recv_port, cmd_trans_port);
            if (udp_helper == nullptr)
            {
                matlab_error("Cannot create a UDP helper Object.\r\n");
            }

            return;
        }
        //("link_network")
        else if (cmd_in == u"link_network")
        {
            if (udp_helper == nullptr)
            {
                matlab_error("Connection has not created.\r\n");
            }

            udp_helper->connect_to_target();

            return;
        }
        //("release_network")
        else if (cmd_in == u"release_network")
        {
            if (udp_helper != nullptr)
            {
                udp_helper->release_connect();
                delete udp_helper;
                udp_helper = nullptr;
            }

            return;
        }
        //("send_msg", bytes_array)
        else if (cmd_in == u"send_msg")
        {
            if (inputs[1].getType() != ArrayType::INT8)
            {
                matlab_error("The second parameter should be a byte array");
            }

            matlab::data::TypedArray<int8_t> msg = std::move(inputs[1]);

            char *msg_content = new char[msg.getNumberOfElements() + 16];
            uint32_t i = 0;

            for (auto iter = msg.begin(); iter != msg.end(); iter++)
                msg_content[i++] = *iter;

            if (udp_helper == nullptr)
            {
                matlab_error("Connection has not created.\r\n");
            }

            udp_helper->send_msg(msg_content, uint32_t(msg.getNumberOfElements()));

            delete[] msg_content;

            return;
        }
        // ("recv_msg", bytes_array)
        else if (cmd_in == u"recv_msg")
        {
            if (inputs[1].getType() != ArrayType::DOUBLE)
            {
                matlab_error("The second parameter should be the length to be receive");
            }

            if (udp_helper == nullptr)
            {
                matlab_error("Connection has not created.\r\n");
            }

            matlab::data::TypedArray<double> input_len = std::move(inputs[1]);

            size_t target_length = size_t(*input_len.begin());

            if (target_length == 0)
                return;

            char *msg_content = new char[target_length + 16];

            udp_helper->recv_msg(msg_content, uint32_t(target_length));

            matlab::data::TypedArray<int8_t> output = factory.createArray<int8_t>({1, target_length});

            for (size_t i = 0; i < target_length; ++i)
                output[0][i] = int8_t(msg_content[i]);

            outputs[0] = std::move(output);

            delete[] msg_content;

            return;
        }
        // ("send_cmd", bytes_array)
        else if (cmd_in == u"send_cmd")
        {
            if (inputs[1].getType() != ArrayType::INT8)
            {
                matlab_error("The second parameter should be a byte array");
            }

            if (udp_helper == nullptr)
            {
                matlab_error("Connection has not created.\r\n");
            }

            matlab::data::TypedArray<int8_t> msg = std::move(inputs[1]);

            char *msg_content = new char[msg.getNumberOfElements() + 16];
            uint32_t i = 0;

            for (auto iter = msg.begin(); iter != msg.end(); iter++)
                msg_content[i++] = *iter;

            udp_helper->send_cmd(msg_content, uint32_t(msg.getNumberOfElements()));

            delete[] msg_content;

            return;
        }
        // ("recv_cmd", bytes_array)
        else if (cmd_in == u"recv_cmd")
        {
            //if (inputs[1].getType() != ArrayType::DOUBLE)
            //{
            //    matlab_error("The second parameter should be the length to be receive");
            //}

            //if (udp_helper == nullptr)
            //{
            //    matlab_error("Connection has not created.\r\n");
            //}

            //matlab::data::TypedArray<double> input_len = std::move(inputs[1]);

            //size_t target_length = size_t(*input_len.begin());

            //if (target_length == 0)
            //    return;

            //char *msg_content = new char[target_length + 16];

            //udp_helper->recv_cmd(msg_content, (uint32_t)target_length);

            //matlab::data::TypedArray<int8_t> output = factory.createArray<int8_t>({1, target_length});

            //for (size_t i = 0; i < target_length; ++i)
            //    output[0][i] = int8_t(msg_content[i]);

            //outputs[0] = std::move(output);

            //delete[] msg_content;

            //return;
            matlab_error("This function isn't support in this version of mex helper.");

        }
        //("get_target_ip")
        else if (cmd_in == u"get_target_ip")
        {
            if (udp_helper == nullptr)
            {
                matlab_print("[INFO] Network Handle has released.\r\n");
                return;
            }
            else
            {
                if (udp_helper == nullptr)
                {
                    matlab_error("Connection has not created.\r\n");
                }

                outputs[0] = std::move(factory.createScalar(udp_helper->ip_addr.c_str()));
                return;
            }
        }
        //("get_recv_port")
        else if (cmd_in == u"get_recv_port")
        {
            if (udp_helper == nullptr)
            {
                matlab_print("[INFO] Network Handle has released.\r\n");
                return;
            }
            else
            {
                if (udp_helper == nullptr)
                {
                    matlab_error("Connection has not created.\r\n");
                }

                matlab::data::TypedArray<double> output = factory.createScalar<double>(udp_helper->recv_port);
                outputs[0] = std::move(output);
                return;
            }
        }
        //("get_tran_port")
        else if (cmd_in == u"get_tran_port")
        {
            if (udp_helper == nullptr)
            {
                matlab_print("[INFO] Network Handle has released.\r\n");
                return;
            }
            else
            {
                if (udp_helper == nullptr)
                {
                    matlab_error("Connection has not created.\r\n");
                }

                matlab::data::TypedArray<double> output = factory.createScalar<double>(udp_helper->trans_port);
                outputs[0] = std::move(output);
                return;
            }
        }
        //("get_recv_cmd_port")
        else if (cmd_in == u"get_recv_cmd_port")
        {
            if (udp_helper == nullptr)
            {
                matlab_print("[INFO] Network Handle has released.\r\n");
                return;
            }
            else
            {
                if (udp_helper == nullptr)
                {
                    matlab_error("Connection has not created.\r\n");
                }

                matlab::data::TypedArray<double> output = factory.createScalar<double>(udp_helper->cmd_recv_port);
                outputs[0] = std::move(output);
                return;
            }
        }
        //("get_tran_cmd_port")
        else if (cmd_in == u"get_tran_cmd_port")
        {
            if (udp_helper == nullptr)
            {
                matlab_print("[INFO] Network Handle has released.\r\n");
                return;
            }
            else
            {
                if (udp_helper == nullptr)
                {
                    matlab_error("Connection has not created.\r\n");
                }

                matlab::data::TypedArray<double> output = factory.createScalar<double>(udp_helper->cmd_trans_port);
                outputs[0] = std::move(output);
                return;
            }
        }
        else
        {
            matlab_error("Unknown command.\r\n");
        }

        /*checkArguments(outputs, inputs);

        double multiplier = inputs[0][0];
        matlab::data::TypedArray<double> in = std::move(inputs[1]);
        arrayProduct(in, multiplier);
        outputs[0] = std::move(in);*/
    }

    // Real process Implement
    void arrayProduct(matlab::data::TypedArray<double> &inMatrix, double multiplier)
    {

        for (auto &elem : inMatrix)
        {
            elem *= multiplier;
        }
    }

    // Check Arguments for Matlab input
    void checkArguments(matlab::mex::ArgumentList outputs, matlab::mex::ArgumentList inputs)
    {

        std::shared_ptr<matlab::engine::MATLABEngine> matlabPtr = getEngine();
        matlab::data::ArrayFactory factory;

        if (inputs.size() != 2)
        {
            matlab_error({"Error Here."});

            matlab_print({"Two inputs required"});
        }

        if (inputs[0].getNumberOfElements() != 1)
        {
            matlabPtr->feval(
                u"error", 0,
                std::vector<matlab::data::Array>({factory.createScalar("Input multiplier must be a scalar")}));
        }

        if (inputs[0].getType() != matlab::data::ArrayType::DOUBLE ||
            inputs[0].getType() == matlab::data::ArrayType::COMPLEX_DOUBLE)
        {
            matlabPtr->feval(u"error", 0,
                             std::vector<matlab::data::Array>(
                                 {factory.createScalar("Input multiplier must be a noncomplex scalar double")}));
        }

        if (inputs[1].getType() != matlab::data::ArrayType::DOUBLE ||
            inputs[1].getType() == matlab::data::ArrayType::COMPLEX_DOUBLE)
        {
            matlabPtr->feval(
                u"error", 0,
                std::vector<matlab::data::Array>({factory.createScalar("Input matrix must be type double")}));
        }

        if (inputs[1].getDimensions().size() != 2)
        {
            matlabPtr->feval(
                u"error", 0,
                std::vector<matlab::data::Array>({factory.createScalar("Input must be m-by-n dimension")}));
        }
    }

    void checkArgumentsConfigNetwork(matlab::mex::ArgumentList outputs, matlab::mex::ArgumentList inputs)
    {
        if (inputs[1].getType() != ArrayType::MATLAB_STRING)
        {
            matlab_error("First parameter is a string which is a IP ADDRESS.\r\n");
        }

        if (inputs[2].getType() != matlab::data::ArrayType::DOUBLE)
        {
            matlab_error("Second parameter is the transmit port, is a number.\r\n");
        }

        if (inputs[3].getType() != matlab::data::ArrayType::DOUBLE)
        {
            matlab_error("Third parameter is the receive port, is a number.\r\n");
        }

        if (inputs[4].getType() != matlab::data::ArrayType::DOUBLE)
        {
            matlab_error("Forth parameter is the transmit port, is a number.\r\n");
        }

        if (inputs[5].getType() != matlab::data::ArrayType::DOUBLE)
        {
            matlab_error("Fifth parameter is the receive port, is a number.\r\n");
        }
    }

  private:
};
