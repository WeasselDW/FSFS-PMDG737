#pragma once
#include <windows.h>
#include <tchar.h>
#include <stdio.h>
#include <strsafe.h>

#include "PMDG_NG3_SDK.h"
#include <iostream>
#include "SimConnect.h"
#include <functional>

class Sim
{
public:
	int     quit = 0;
	bool    AircraftRunning = false;
	PMDG_NG3_Data* data;
	HANDLE  hSimConnect = NULL;


	void pressFMCBtn(int btn);

	Sim(void (*loop)(Sim* sim));

	void static CALLBACK MyDispatchProc(SIMCONNECT_RECV* pData, DWORD cbData, void* pContext);
	//void static CALLBACK MyDispatchProcRD(SIMCONNECT_RECV* pData, DWORD cbData, void* pContext);



private:
	PMDG_NG3_Control Control;
	HRESULT hr;

	static enum DATA_REQUEST_ID {
		DATA_REQUEST,
		CONTROL_REQUEST,
		AIR_PATH_REQUEST
	};
	static enum EVENT_ID {
		EVENT_SIM_START,	// used to track the loaded aircraft

		EVENT_CDU_EXEC
	};

	
};

