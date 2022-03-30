/****************************************************************************************************
*
* file name:	server.c
* author:		king
* data:			2022.3.17
* description:	Test rpc on windows.To learn about remote code execution vulnerabilities on Windows
*
* E-mail:		lzk1342325850@163.com
*
*****************************************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include"hello_h.h"

#pragma comment(lib, "mpr")
#pragma comment(lib, "Rpcrt4")

void Hello( const unsigned char *psz)
{
	printf("%s\n",psz);
}

void ShutDown( void)
{
	RpcMgmtStopServerListening(NULL);
	RpcServerUnregisterIf(NULL, NULL, FALSE);
}

int main()
{
	RPC_STATUS status;
	unsigned char * pszProtocolSequence = (unsigned char *)"ncacn_np";
	unsigned char* pszEndpoint = (unsigned char*)"\\pipe\\hello";
	unsigned char* pszSecurity = NULL;

	/**********************************************************************************************
	*
	*RpcServerUseProtseqEp 函数告诉 RPC 运行时库使用指定的协议序列和指定的终结点来接收远程过程调用。
	*
	*参数:
	*Protseq(unsigned char *)	指向要向 RPC 运行时库注册的协议序列的字符串标识符的指针。
	*MaxCalls(unsigned int)		"ncacn_np"默认RPC_C_PROTSEQ_MAX_REQS_DEFAULT
	*Endpoint(unsigned char *)	指向终结点地址信息的指针，这些信息用于为 Protseq 参数中指定的协议序列创建绑定。
	*SecurityDescriptor(void*)	默认NULL
	*
	***********************************************************************************************/
	status = RpcServerUseProtseqEp(pszProtocolSequence,RPC_C_LISTEN_MAX_CALLS_DEFAULT,pszEndpoint,pszSecurity);
	if(status)
	{
		printf("RpcServerUseProtseqEp case error!\n");
		exit(status);
	}
	/****************************************************************************************************************************************
	*
	* RpcServerRegisterIfEx 函数向 RPC 运行时库注册一个接口
	*
	*
	*
	*
	****************************************************************************************************************************************/
	status = RpcServerRegisterIfEx(HelloWorld_v1_0_s_ifspec,NULL,NULL,RPC_IF_ALLOW_CALLBACKS_WITH_NO_AUTH,RPC_C_LISTEN_MAX_CALLS_DEFAULT,NULL);
	if(status)
	{
		printf("RpcServerRegisterIfEx case error!\n");
		exit(status);
	}

	RpcServerListen(1,20,FALSE);

	return 0;

}
/**************************************************************************************************************





***************************************************************************************************************/
void __RPC_FAR* __RPC_USER midl_user_allocate(size_t len)
{
     return(malloc(len));
}

void __RPC_USER midl_user_free(void __RPC_FAR *ptr)
{
     free(ptr);
}