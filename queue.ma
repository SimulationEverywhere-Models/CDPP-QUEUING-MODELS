[top]
components : queue@Queue
out : out beReady
in : in request

Link : in in@queue
Link : request request@queue
Link : beReady@queue beReady
Link : out@queue out

[queue]
servers : 3
