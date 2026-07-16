/**
 * @file sch.hpp
 * @author Javnson (javnson@zju.edu.cn)
 * @brief
 * @version 0.1
 * @date 2024-09-30
 *
 * @copyright Copyright GMP(c) 2024
 *
 */

#ifndef _FILE_SCH_HPP_
#define _FILE_SCH_HPP_

// singleton
class scheduler_t
{
  public:
    // ctor & dtor
    scheduler_t()
    {
    }

  public:
    // utilities

  protected:
    // members
    uint32_t slice_size;
    uint32_t current_slice_pos;

    // task queue
};

// Scheduling Control block
class scb_t
{
  public:
    // ctor & dtor

  public:
    // utilities

  protected:
    // members
    // dynamic_prior

    //	static_prior
};

#endif // _FILE_SCH_HPP_
