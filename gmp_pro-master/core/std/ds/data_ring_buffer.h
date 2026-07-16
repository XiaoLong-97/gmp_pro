/**
 * @file data_ring_buffer.h
 * @author Javnson (javnson@zju.edu.cn)
 * @brief
 * @version 0.1
 * @date 2024-09-30
 *
 * @copyright Copyright GMP(c) 2024
 *
 */

#ifndef _FILE_BUFFER_H_
#define _FILE_BUFFER_H_

#ifdef __cplusplus
extern "C"
{
#endif //__cplusplus

// ring buffer
typedef struct _tag_gmp_ring_buffer_t
{
    data_gt *buffer; // ring of buffer
    size_gt length;  // buffer length

    size_gt write_pos; // write position
    size_gt read_pos;  // read position
} gmp_ring_buffer_t;



// initialization
gmp_stat_t init_ring_buffer(gmp_ring_buffer_t **buffer, size_gt length);

// release the ring buffer
void release_ring_buffer(gmp_ring_buffer_t *buf);

size_gt rb_size(gmp_ring_buffer_t *buf);

size_gt rb_capacity(gmp_ring_buffer_t *buf);

gmp_stat_t rb_push(gmp_ring_buffer_t *buf, data_gt dat);

data_gt rb_peek(gmp_ring_buffer_t *buf);

data_gt rb_pop(gmp_ring_buffer_t *buf);

void rb_empty(gmp_ring_buffer_t *buf);

size_gt rb_extract(gmp_ring_buffer_t *buf, void *dst, size_gt cap);

#ifdef __cplusplus
}
#endif //__cplusplus

#endif //_FILE_BUFFER_H_
