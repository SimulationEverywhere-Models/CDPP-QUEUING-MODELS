[top]
components : server@Server
out : out request
in : in beReady

Link : in in@server
Link : beReady beReady@server
Link : request@server request
Link : out@server out

[server]
myId : 3
distribution : poisson
mean : 8

