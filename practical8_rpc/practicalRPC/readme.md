rpcgen IDL.x

gcc -o client IDL_client.c IDL_clnt.c IDL_xdr.c
gcc -o server IDL_server.c IDL_svc.c IDL_xdr.c -lm

sudo service rpcbind start
sudo service rpcbind status
rpcinfo -p

