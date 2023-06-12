[top]
components : gen@Generator queue@Queue server@Server perf@Performance

out : out_srv Lq Wq Ls Ws
in : get_data

Link : out@gen in@queue
Link : out@queue in@server
Link : beReady@queue beReady@server
Link : request@server request@queue
Link : out@server out_srv
Link : get_data get_data@perf
Link : Lq@perf Lq
Link : Wq@perf Wq
Link : Ls@perf Ls
Link : Ws@perf Ws
Link : out@gen enter_sys@perf
Link : out@queue exit_q@perf
Link : out@server exit_sys@perf


[gen]
distribution : constant
value : 5

[queue]
servers : 1

[server]
myId : 0
distribution : constant
value : 8
