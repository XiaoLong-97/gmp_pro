#include <gmp_core.h>

#include <core/dev/rtshell/expr_parser.c>
#include <cpre/dev/rtshell/rtsh_cmd.h>

int gmp_cmd_internal(int argc, char*argv[])
{
    return 0;
}

rtsh_cmd_record_t internal_cmd[] = {{"gmp", gmp_cmd_internal, "show gmp realtime shell information"}, {0, 0, 0}};
