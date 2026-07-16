// RLC_solver.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <fstream>
#include <iostream>

#include <cctl/power_electronics_objects/mosfet/half_bridge_switch_model.hpp>

#include <cctl/power_electronics_objects/mosfet/3ph_bridge_switch_model.hpp>
#include <cctl/power_electronics_objects/motor_model/im.model.hpp>

#include <cctl/numerical_solver/runge_kutta_4.hpp>

#include <third_party/Eigen/Eigen.h>

using std::ofstream;

#if 0
int main()
{
    std::cout << "Hello World!\n";

    //diff_rlc_resonance<double> rlc_model;

    RungeKutta<diff_rlc_resonance<double>> rlc_model_rk(1e-7);

    rlc_model_rk.diff.C = 1e-4;
    rlc_model_rk.diff.L = 1e-3;
    rlc_model_rk.diff.R = 1;

    double Uin = 10;

    rlc_model_rk.diff.bind(&Uin);

    ofstream file("output.csv");

    for (size_t i = 0; i < 100000; ++i)
    {
        file << rlc_model_rk.time << ", " << rlc_model_rk.st.il << "," << rlc_model_rk.st.uc << std::endl;
        rlc_model_rk();
    }

    file.close();


}

#endif

#if 1
int main()
{
    std::cout << "Hello World!\n";

    // diff_rlc_resonance<double> rlc_model;

    RungeKutta<diff_rlc_resonance<double>> rlc_model_rk(1e-7);

    mdl_idel_half_bridge<double> hb;

    rlc_model_rk.diff.C = 1e-6;
    rlc_model_rk.diff.L = 1e-3;
    rlc_model_rk.diff.R = 4;

    hb.R_on = 10;
    
    
    double Ubus = 10;
    uint_fast8_t pwm;

    hb.bind(&Ubus, &rlc_model_rk.st.il, &pwm);
    rlc_model_rk.diff.bind(&hb.Ubridge);

    ofstream file("output.csv");

    for (size_t i = 0; i < 100000; ++i)
    {
        if (i % 100 < 50)
            pwm = 0;
        else
            pwm = 1;

        rlc_model_rk();
        hb();

        file << pwm << ", " << rlc_model_rk.time << ", " << rlc_model_rk.st.il << "," << rlc_model_rk.st.uc
             << std::endl;
    }

    file.close();
}

#endif

#if 0
int main()
{
    std::cout << "Hello World!\n";

    // diff_rlc_resonance<double> rlc_model;

    // RungeKutta<diff_rlc_resonance<double>> rlc_model_rk(1e-7);

    // rlc_model_rk.diff.C = 1e-6;
    // rlc_model_rk.diff.L = 1e-3;
    // rlc_model_rk.diff.R = 40;

    RungeKutta<diff_im_motor<double>> im_motor(1e-7);

    im_motor.diff.J = 0.05;
    im_motor.diff.damping = 0.005879;
    im_motor.diff.pole_pair = 2;
    im_motor.diff.Rs = 0.5968;
    im_motor.diff.Rr = 0.6258;
    im_motor.diff.Lm = 0.0354;
    im_motor.diff.Ls = im_motor.diff.Lm + 0.003495;
    im_motor.diff.Lr = im_motor.diff.Lm + 0.005473;

    im_motor.diff.update_state_matrix();

    mdl_idel_3ph_bridge<double> bridge;

    bridge.R_on = 0.1;

    double Ubus = 10;

    double im_load = 0;
    double im_ur = 0;

    double *bridge_current[3] = {
        &im_motor.diff.isa,
        &im_motor.diff.isb,
        &im_motor.diff.isc,
    };

    uint_fast8_t pwm[3] = {0, 0, 0};

    uint_fast8_t *bridge_pwm[3] = {&pwm[0], &pwm[1], &pwm[2]};

    bridge.bind(&Ubus, bridge_current, bridge_pwm);

    im_motor.diff.bind(&bridge.Ubridge[0], &bridge.Ubridge[1], &bridge.Ubridge[2], &im_ur, &im_ur, &im_ur, &im_load);

    ofstream file("output.csv");

    for (size_t i = 0; i < 100000; ++i)
    {
        for (size_t j = 0; j < 3; ++j)
        {
            if (i % 1000 < 500)
                pwm[j] = 0;
            else
                pwm[j] = 1;
        }

        im_motor();
        bridge();



        file << bridge.Ubridge[0] << ", " << bridge.Ubridge[1] << ", " << bridge.Ubridge[2] << ",";
        file << im_motor.diff.isa << ", " << im_motor.diff.isb << ", " << im_motor.diff.isc << ",";
        file << std::endl;

    }

    file.close();
}

#endif 
