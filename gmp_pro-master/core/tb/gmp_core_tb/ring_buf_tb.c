

#include <gmp_core.h>

#include <core/tb/gmp_core_tb.h>

// There're a lot of ring buffer test bench

void gmp_ringbuf_tb(void)
{
    // Create a bing buffer object

    static ringbuf_t rb;
    data_gt *dat = malloc(sizeof(data_gt) * 1024);

    // create a ring buffer
    gmp_init_ringbuf(&rb, dat, 1024);

    // calculate spare space
    gmp_base_print("The ring buffer has %d unit space, data_gt is %d bytes.\r\n", ringbuf_get_spare_size(&rb),
                   sizeof(data_gt));

    // push items
    gmp_base_print("push 1000 items in this array\r\n");

    for (size_gt i = 0; i < 1000; ++i)
    {
        ringbuf_put_item(&rb, i);
    }

    gmp_base_print("The ring buffer has %d unit spare space, data_gt is %d bytes, %d unit has alloc.\r\n",
                   ringbuf_get_spare_size(&rb), sizeof(data_gt), ringbuf_get_valid_size(&rb));

    size_gt N = 200;

    // pull them all
    for (size_gt i = 0; i < 1000; ++i)
    {
        if (i == N)
        {
            gmp_base_print("The %dth item is %d.\r\n", N, ringbuf_peek_item(&rb));
        }
        ringbuf_get_item(&rb);
    }

    // For now no item is in this ring buffer
    int32_t result = ringbuf_peek_item(&rb);
    if (result == -1)
    {
        gmp_base_print("ring buffer is null.\r\n");
    }

    // push a lot of items
    gmp_base_print("push 1500 exceed 1023 items.\r\n");
    for (size_gt i = 0; i < 1050; ++i)
    {
        ringbuf_put_item(&rb, i);
    }
    gmp_base_print("The ring buffer has %d unit spare space, data_gt is %d bytes, %d unit has alloc.\r\n",
                   ringbuf_get_spare_size(&rb), sizeof(data_gt), ringbuf_get_valid_size(&rb));

    gmp_base_print("Now the first item is %d, Now the last item is %d, when try again to push another item, the "
                   "function returns: %d.\r\n",
                   ringbuf_peek_item(&rb), ringbuf_peek_last_item(&rb), ringbuf_put_item(&rb, 1));

    // push a lot og items via warp
    gmp_base_print("continue push 1000 item using warp function.\r\n");
    for (size_gt i = 0; i < 1000; ++i)
    {
        ringbuf_put_item_warp(&rb, i);
    }
    gmp_base_print("The ring buffer has %d unit spare space, data_gt is %d bytes, %d unit has alloc.\r\n",
                   ringbuf_get_spare_size(&rb), sizeof(data_gt), ringbuf_get_valid_size(&rb));

    gmp_base_print("Now the first item is %d, Now the last item is %d, when try again to push another item, the "
                   "function returns: %d.\r\n",
                   ringbuf_peek_item(&rb), ringbuf_peek_last_item(&rb), ringbuf_put_item(&rb, 1));

    // using memcpy function to copy out the buffer content
    gmp_base_print("copy out all the items in the ring buffer.\r\n");
    data_gt *dat_out = malloc(1024 * sizeof(data_gt));

    ringbuf_get_array(&rb, dat_out, ringbuf_get_valid_size(&rb));

    gmp_base_print("Now, the copy out reuslt has %d to be the first element, and %d to be the last item.\r\n",
                   dat_out[0], dat_out[1023 - 1]);

    // using memcpy function to copy in buffer content
    memset(dat_out, 0x55, 1024);
    ringbuf_put_array(&rb, dat_out, 1000);

    gmp_base_print("The ring buffer has %d unit spare space, data_gt is %d bytes, %d unit has alloc.\r\n",
                   ringbuf_get_spare_size(&rb), sizeof(data_gt), ringbuf_get_valid_size(&rb));
    gmp_base_print("The first item is %d, the last item is %d.\r\n", ringbuf_peek_item(&rb),
                   ringbuf_peek_last_item(&rb));

    // push more items
    memset(dat_out, 0x66, 1024);
    ringbuf_put_array(&rb, dat_out, 10);

    gmp_base_print("The ring buffer has %d unit spare space, data_gt is %d bytes, %d unit has alloc.\r\n",
                   ringbuf_get_spare_size(&rb), sizeof(data_gt), ringbuf_get_valid_size(&rb));
    gmp_base_print("The first item is %d, the last item is %d.\r\n", ringbuf_peek_item(&rb),
                   ringbuf_peek_last_item(&rb));

    // push more items
    memset(dat_out, 0x77, 1024);
    fast_gt ret = ringbuf_put_array(&rb, dat_out, 100);

    gmp_base_print("Now, return value is %d.\r\n", ret);
    gmp_base_print("The ring buffer has %d unit spare space, data_gt is %d bytes, %d unit has alloc.\r\n",
                   ringbuf_get_spare_size(&rb), sizeof(data_gt), ringbuf_get_valid_size(&rb));
    gmp_base_print("The first item is %d, the last item is %d.\r\n", ringbuf_peek_item(&rb),
                   ringbuf_peek_last_item(&rb));

    // release the buffer
    free(dat_out);
    free(dat);
}
