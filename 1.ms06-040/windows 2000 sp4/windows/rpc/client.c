#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"hello_h.h"

#pragma comment(lib, "mpr")
#pragma comment(lib, "Rpcrt4")

int main()
{

	RPC_STATUS status;

	unsigned char * pszUuid = (unsigned char *)"62560D0C-C276-45cd-B60C-2922BE90031B";
	unsigned char * pszPortSeq = (unsigned char *)"ncacn_np";
	unsigned char * pszNetworkAddr = (unsigned char *)"192.168.2.8";
	unsigned char * pszEndpoint = (unsigned char*)"\\pipe\\hello";
	unsigned char * pszOptions = NULL;
	unsigned char * pszStringBinding = NULL;


	

	status = RpcStringBindingCompose(pszUuid,pszPortSeq,pszNetworkAddr,pszEndpoint,pszOptions,&pszStringBinding);
	if(status)
	{
		printf("RpcStringBindingCompose case error!\n");
		exit(status);
	}



	status = RpcBindingFromStringBinding(pszStringBinding,&HelloWorldBinding);
	if(status)
	{
		printf("RpcBindingFromStringBinding case error!\n");
		exit(status);
	}


	RpcTryExcept
	{
		Hello("kun");
	}
     RpcExcept(1)
     {
         printf( "RPC Exception %d\n", RpcExceptionCode() );
     }
     RpcEndExcept

     RpcStringFree(&pszStringBinding);
     RpcBindingFree(&HelloWorldBinding);
	 return 0;
}

void __RPC_FAR* __RPC_USER midl_user_allocate(size_t len)
{
     return(malloc(len));
}

void __RPC_USER midl_user_free(void __RPC_FAR *ptr)
{
     free(ptr);
}
