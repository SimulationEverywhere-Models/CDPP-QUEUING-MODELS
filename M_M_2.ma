[top]
components : gen@Generator queue@Queue server_0@Server server_1@Server perf@Performance

out : out_srv Lq Wq Ls Ws
in : get_data

Link : out@gen in@queue
Link : out@queue in@server_0
Link : out@queue in@server_1
Link : beReady@queue beReady@server_0
Link : beReady@queue beReady@server_1
Link : request@server_0 request@queue
Link : request@server_1 request@queue
Link : out@server_0 out_srv
Link : out@server_1 out_srv
Link : get_data get_data@perf
Link : Lq@perf Lq
Link : Wq@perf Wq
Link : Ls@perf Ls
Link : Ws@perf Ws
Link : out@gen enter_sys@perf
Link : out@queue exit_q@perf
Link : out@server_0 exit_sys@perf
Link : out@server_1 exit_sys@perf

[gen]
distribution : poisson
mean : 35

[queue]
servers : 2

[server_0]
myId : 0
distribution : poisson
mean : 25

[server_1]
myId : 1
distribution : poisson
mean : 25

