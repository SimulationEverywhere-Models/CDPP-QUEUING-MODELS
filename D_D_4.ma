[top]
components : gen@Generator queue@Queue server_0@Server server_1@Server server_2@Server server_3@Server perf@Performance

out : out_srv Lq Wq Ls Ws
in : get_data

Link : out@gen in@queue
Link : out@queue in@server_0
Link : out@queue in@server_1
Link : out@queue in@server_2
Link : out@queue in@server_3
Link : beReady@queue beReady@server_0
Link : beReady@queue beReady@server_1
Link : beReady@queue beReady@server_2
Link : beReady@queue beReady@server_3
Link : request@server_0 request@queue
Link : request@server_1 request@queue
Link : request@server_2 request@queue
Link : request@server_3 request@queue
Link : out@server_0 out_srv
Link : out@server_1 out_srv
Link : out@server_2 out_srv
Link : out@server_3 out_srv
Link : get_data get_data@perf
Link : Lq@perf Lq
Link : Wq@perf Wq
Link : Ls@perf Ls
Link : Ws@perf Ws
Link : out@gen enter_sys@perf
Link : out@queue exit_q@perf
Link : out@server_0 exit_sys@perf
Link : out@server_1 exit_sys@perf
Link : out@server_2 exit_sys@perf
Link : out@server_3 exit_sys@perf

[gen]
distribution : poisson
mean : 30

[queue]
servers : 4

[server_0]
myId : 0
distribution : constant
value : 8

[server_1]
myId : 1
distribution : constant
value : 8

[server_2]
myId : 2
distribution : constant
value : 8

[server_3]
myId : 3
distribution : constant
value : 8
