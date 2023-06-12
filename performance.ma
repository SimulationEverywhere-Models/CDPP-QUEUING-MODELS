[top]
components : perf@Performance

out : Lq Wq Ls Ws
in : enter_sys exit_q exit_sys get_data

Link : enter_sys enter_sys@perf
Link : exit_q exit_q@perf
Link : exit_sys exit_sys@perf
Link : get_data get_data@perf

Link : Lq@perf Lq
Link : Wq@perf Wq
Link : Ls@perf Ls
Link : Ws@perf Ws
