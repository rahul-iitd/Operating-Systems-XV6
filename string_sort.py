l=["sys_fork ","sys_send","sys_send_multi","sys_recv","sys_exit ","sys_wai t","sys_pipe ","sys_read ","sys_kill ","sys_exec ","sys_fstat ","sys_chdir ","sys_dup ","sys_getpid ","sys_sbrk ","sys_sleep ","sys_uptime ","sys_open ","sys_write ","sys_mknod ","sys_unlink ","sys_link ","sys_mkdir ","sys_close ","sys_print_count ","sys_toggle ","sys_add ","sys_ps "]

l.sort()
for i in range(len(l)):
    print (i+1)
    print (l[i])
