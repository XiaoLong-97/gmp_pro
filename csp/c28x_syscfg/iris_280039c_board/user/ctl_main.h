#ifndef _FILE_CTL_MAIN_H_
#define _FILE_CTL_MAIN_H_

#ifdef __cplusplus
extern "C"
{
#endif

void ctl_init(void);
void ctl_mainloop(void);

GMP_STATIC_INLINE void ctl_dispatch(void)
{
}

#ifdef __cplusplus
}
#endif

#endif // _FILE_CTL_MAIN_H_
