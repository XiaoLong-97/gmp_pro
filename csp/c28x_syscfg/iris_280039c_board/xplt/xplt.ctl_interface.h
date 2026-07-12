#ifndef _FILE_CTL_INTERFACE_H_
#define _FILE_CTL_INTERFACE_H_

#ifdef __cplusplus
extern "C"
{
#endif

/* The power-supply application is serviced by scheduled tasks, not by the
   former high-frequency training controller. Keep the GMP hooks inert. */
GMP_STATIC_INLINE void ctl_input_callback(void)
{
}

GMP_STATIC_INLINE void ctl_output_callback(void)
{
}

#ifdef __cplusplus
}
#endif

#endif // _FILE_CTL_INTERFACE_H_
