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
	*RpcServerUseProtseqEp �������� RPC ����ʱ��ʹ��ָ����Э�����к�ָ�����ս��������Զ�̹��̵��á�
	*
	*����:
	*Protseq(unsigned char *)	ָ��Ҫ�� RPC ����ʱ��ע���Э�����е��ַ�����ʶ����ָ�롣
	*MaxCalls(unsigned int)		"ncacn_np"Ĭ��RPC_C_PROTSEQ_MAX_REQS_DEFAULT
	*Endpoint(unsigned char *)	ָ���ս���ַ��Ϣ��ָ�룬��Щ��Ϣ����Ϊ Protseq ������ָ����Э�����д����󶨡�
	*SecurityDescriptor(void*)	Ĭ��NULL
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
	* RpcServerRegisterIfEx ������ RPC ����ʱ��ע��һ���ӿ�
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