// This file will implement a Runge-Kutta Solver.

#ifndef _FILE_RUNGE_KUTTA_4_HPP_
#define _FILE_RUNGE_KUTTA_4_HPP_


// In order to solve a equation user should implement a class which
// provide a `operator +=` to implement a integral and
// a `operator()` to get diff item.

// _T to specify a type which means the accuracy.
template <typename template_type> class st_rlc_resonance
{
  public:
    typedef template_type _T;

  public:
    _T uc;
    _T il;

  public:
    st_rlc_resonance() : uc(0), il(0)
    {
    }

    // ctor & dtor
    st_rlc_resonance(_T uc, _T il) : uc(uc), il(il)
    {
    }

  public:
    st_rlc_resonance operator*(const _T &num) const
    {
        return st_rlc_resonance(uc * num, il * num);
    }

    st_rlc_resonance operator+(const st_rlc_resonance &num) const
    {
        return st_rlc_resonance(uc + num.uc, il + num.il);
    }

    st_rlc_resonance &operator+=(const st_rlc_resonance &&num)
    {
        this->uc = this->uc + num.uc;
        this->il = this->il + num.il;
        return *this;
    }
};

template <typename template_type> class diff_rlc_resonance
{
  public:
    typedef typename template_type _T;
    typedef typename st_rlc_resonance<_T> _st;

  public:
    _T *U_in;

  public:
    // system parameters
    _T C;
    _T L;
    _T R;

  public:
    void bind(_T *U_in)
    {
        this->U_in = U_in;
    }

    _st operator()(const _st &st)
    {
        _st diff;
        diff.uc = st.il / C;
        diff.il = -st.uc / L - R / L * st.il + (*U_in) / L;

        return diff;
    }
};

// _T    is a number which has +-*/ calculation
// _diff owns a operator() to give a differential result
// _st   owns a operator+ to provide a integral process
template <typename _diff, typename _T = typename _diff::_T> class RungeKutta
{
  public:
    typedef typename _diff::_st _st;

  public:
    _T time;

    _T dt;
    _T half_dt;
    _diff diff;
    _st st;

  public:
    RungeKutta(_T _dt) : dt(_dt), half_dt(_dt * 0.5), time(0),diff(){};

    _st &operator()()
    {
        _st k1 = diff(st);
        _st k2 = diff(st + k1 * half_dt);
        _st k3 = diff(st + k2 * half_dt);
        _st k4 = diff(st + k3 * dt);

        time += dt;
        st += (k1 + k2 * 2.0 + k3 * 2.0 + k4) * (dt / 6.0);
        return st;
    }
};




#endif // _FILE_RUNGE_KUTTA_4_HPP_
