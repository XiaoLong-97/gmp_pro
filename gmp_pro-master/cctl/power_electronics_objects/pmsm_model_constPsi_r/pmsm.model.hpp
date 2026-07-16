#ifndef _FILE_PMSM_MODEL_H_
#define _FILE_PMSM_MODEL_H_

// denominator = (Ld*Lq + Ld*iq*pd_qq + Lq*id*pd_dd + id*iq*pd_dd*pd_qq - id*iq*pd_dq*pd_qd);
// numerator = invA .* denominator;

// % pIdq =
// % (id*pd_dq*(-Hq))/(denominator) - ((Lq + iq*pd_qq)*(-Hd))/(denominator)
// % (iq*pd_qd*(-Hd))/(denominator) - ((Ld + id*pd_dd)*(-Hq))/(denominator)
template <typename template_type> class st_pmsm_motor 
{
public:
    typedef template_type _T;
public:
    _T id;       // 直轴电流（stator direct current）
    _T iq;       // 交轴电流（stator quadrature current）
    _T omega_e; // 电角速度
    _T theta; // 磁链角度

public://definition
    st_pmsm_motor(): id(0), iq(0), omega_e(0), theta(0){}
    st_pmsm_motor(_T Ld, _T Lq, _T id, _T iq, _T omega_e, _T theta): id(0), iq(0), omega_e(0), theta(0){}

public://operator
    st_pmsm_motor operator*(const _T &num) const
    {
        return st_im_motor(id * num, iq * num, omega_e * num, theta * num);
    }

    st_pmsm_motor operator+(const st_pmsm_motor &num) const
    {
        return st_im_motor(id * num.id, iq * num.iq, omega_e * num.omega_e,
                           theta * num.theta);
    }

    st_pmsm_motor &operator+=(const st_pmsm_motor &&num)
    {
        this->id = this->id + num.id;
        this->iq = this->iq + num.iq;

        this->omega_e = this->omega_e + num.omega_e;
        this->theta = this->theta + num.theta;

        return *this;
    }
};

template <typename template_type> class diff_pmsm_motor
{
public:
    typedef typename template_type _T;
    typedef typename st_pmsm_motor<_T> _st;
public://input
    _T *usa, *usb, *usc;
    _T *torque_load;
public://output
    _T usa, usb, usc;
    _T torque;
    _T isa, isb, isc;
public://parameter
    _T Rs;
    _T PsiR;
    _T damping;
    _T J;
    uint16_t pole_pair;
public://parameters from the table
    _T Ld, Lq;
    _T partial_Ld_partial_theta, partial_Lq_partial_theta;
    _T partial_Ld_partial_id, partial_Ld_partial_iq;
    _T partial_Lq_partial_id, partial_Lq_partial_iq;
private:
    // private const
    const _T k_alpha = _T(2.0 / 3.0);      // 2/3
    const _T k_beta = _T(1.0 / sqrt(3.0)); // 1/sqrt(3)
    const _T k_gamma = _T(1.0 / 3.0);      // 1/3
    const _T k_zeta = _T(sqrt(3) / 2.0);   // sqrt(3)/2
public:
    diff_pmsm_motor(): usa(0), usb(0), usc(0), torque(0), Rs(0), Ld(0), Lq(0), PsiR(0), damping(0), J(0), pole_pair(1){}
public:
    void bind(_T *usa, _T *usb, _T *usc, _T *t_load)
    {
        this->usa = usa;
        this->usb = usb;
        this->usc = usc;
        this->torque_load = torque_load;
    }
    void set_param(_st state, _T Rs, _T Ld, _T Lq, _T PsiR, _T damping, _T J, uint16_t pp)
    {
        this->Rs = Rs;
        this->Ld = Ld;
        this->Lq = Lq;
        this->PsiR = PsiR;
        this->damping = damping;
        this->J = J;
        this->pole_pair = pp;
        update_param_fromtable(state);
    }
    // !!! todo
    void update_param_fromtable(_st state)
    {

    }

public:
    _st operator()(const _st &state)
    {
        _st diff;
        // temp
        _T Hd, Hq;
        _T denominator;

        // park transform
        _T vs_alpha, vs_beta;
        _T vsd, vsq;
        

        // stator abc to static coordination
        // tex:
        //   $$i_\alpha = 2/3\times i_a - 1/3 \times i_b - 1/3 \times i_c $$
        vs_alpha = k_alpha * ((*usa) - ((*usb) + (*usc)) / 2);
        // tex:
        //   $$i_\beta = \sqrt{3}/3\times i_b - \sqrt{3}/3\times i_c $$
        vs_beta = k_beta * ((*usb) - (*usc));

        // coordination rotation
        _T sin_theta = sin(state.theta);
        _T cos_theta = cos(state.theta);

        // tex:
        //  $$i_d = i_\alpha \times cos\;(\theta) + i_\beta \times sin\;(\theta) $$
        vsd = vs_alpha * cos_theta + vs_beta * sin_theta;
        // tex:
        //$$i_q = - i_\alpha \times sin\;(\theta) + i_\beta \times cos\;(\theta)$$
        vsq = -vs_alpha * sin_theta + vs_beta * cos_theta;

        // denominator of invA
        denominator = 1/(Ld*Lq \
                        + Ld*state.iq*partial_Lq_partial_iq \
                        + Lq*state.id*partial_Ld_partial_id \
                        + state.id*state.iq*partial_Ld_partial_id*partial_Lq_partial_iq \
                        - state.id*state.iq*partial_Ld_partial_iq*partial_Lq_partial_id);

        Hd = vsd - (state.id * (Rs + state.omega_e*partial_Ld_partial_theta) - state.omega_e * state.iq * Lq);
        Hq = vsq - (state.iq * (Rs + state.omega_e*partial_Lq_partial_theta) + state.omega_e * (state.id*Ld + PsiR));

        diff.id = Hd*denominator*(Lq+state.iq*partial_Lq_partial_iq) - Hq*denominator*state.id*partial_Ld_partial_iq;
        diff.iq = Hq*denominator*(Ld+state.id*partial_Ld_partial_id) - Hd*denominator*state.iq*partial_Lq_partial_id;

        // mechanical
        // CHECK!!!
        torque = 3/2 * pole_pair * ((PsiR + state.id*Ld) * state.iq - state.iq * Lq * state.id);
        diff.omega_e = (torque - (*torque_load) - damping * state.omega_e / pole_pair) / J * pole_pair;
        diff.theta = state.omega_e / pole_pair;

        // output isa,b,c
        _T outis_alpha = state.id * cos_theta - state.iq * sin_theta;
        _T outis_beta = state.id * sin_theta + state.iq * cos_theta;

        // CHECK!!!
        isa = outis_alpha;
        isb = -outis_alpha / 2 + outis_beta * k_zeta;
        isc = -outis_alpha / 2 - outis_beta * k_zeta;

        return diff;
    }
}





#endif // _FILE_PMSM_MODEL_H_