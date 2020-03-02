#include <iostream>
#include <Windows.h>
int main()
{
	HANDLE hCom = CreateFile("\\\\.\\COM4", GENERIC_READ | GENERIC_WRITE,
		0, NULL, OPEN_EXISTING, 0, NULL); //��HC-06������������
	if (hCom == INVALID_HANDLE_VALUE) {
		std::cout << "Port unavailable!" << std::endl;
		return 0;
	}
//�������ô���ͨ�Ų���
	DCB dcb;
	GetCommState(hCom, &dcb);
	dcb.BaudRate = 9600;
	dcb.ByteSize = DATABITS_8;
	dcb.Parity = NOPARITY;
	dcb.StopBits = ONESTOPBIT;
	BOOL br = SetCommState(hCom,&dcb);
	COMMTIMEOUTS cto ={MAXDWORD, MAXDWORD, MAXDWORD, MAXDWORD, MAXDWORD};
	br = SetCommTimeouts(hCom, &cto);
//��ʼ�ȴ��û�����
	for (; ; ) {
		int nInput = 0;
		printf("please input a number :\n");
		std::cin >> nInput;
		if (nInput > 10|| nInput < 0) {
			break; //��������ֵ����10��С��0��ֱ���˳�����
		}
		BYTE byval = 0; 
		BYTE byVal = (BYTE)nInput;
		DWORD dwTransmitted;
//�������ֵ���͸�HC-06
		WriteFile(hCom, &byVal, sizeof(byVal), &dwTransmitted, NULL);
	}
	CloseHandle(hCom);
	return 0;
}

