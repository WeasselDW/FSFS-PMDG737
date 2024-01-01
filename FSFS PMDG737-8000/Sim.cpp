#include "Sim.h"

void Sim::pressBtn(int btn)
{
	if (Control.Event == 0)
	{
		Control.Event = btn;
		Control.Parameter = 1;

		SimConnect_SetClientData(hSimConnect, PMDG_NG3_CONTROL_ID, PMDG_NG3_CONTROL_DEFINITION,
			0, 0, sizeof(PMDG_NG3_Control), &Control);
	}
}

void CALLBACK Sim::MyDispatchProc(SIMCONNECT_RECV* pData, DWORD cbData, void* pContext)
{
	Sim* simInstance = static_cast<Sim*>(pContext); 
	switch (pData->dwID)
	{
	case SIMCONNECT_RECV_ID_CLIENT_DATA:
		// Receive and process the NG3 data block
	{
		SIMCONNECT_RECV_CLIENT_DATA* pObjData =
			(SIMCONNECT_RECV_CLIENT_DATA*)pData;
		switch (pObjData->dwRequestID)
		{
		case DATA_REQUEST:
		{
			PMDG_NG3_Data* test = (PMDG_NG3_Data*)&pObjData->dwData;
			simInstance->data = test;
			break;
		}
		}
	}
	}
}

Sim::Sim(void (*loop)(Sim* sim))
{

	if (SUCCEEDED(SimConnect_Open(&hSimConnect, "PMDG", NULL, 0, 0, 0)))
	{
		printf("\nConnected to Flight Simulator!\n");

		// 1) Set up data connection

		// Associate an ID with the PMDG data area name
		hr = SimConnect_MapClientDataNameToID(hSimConnect, PMDG_NG3_DATA_NAME, PMDG_NG3_DATA_ID);

		// Define the data area structure - this is a required step
		hr = SimConnect_AddToClientDataDefinition(hSimConnect, PMDG_NG3_DATA_DEFINITION, 0, sizeof(PMDG_NG3_Data), 0, 0);

		hr = SimConnect_RequestClientData(hSimConnect, PMDG_NG3_DATA_ID, DATA_REQUEST, PMDG_NG3_DATA_DEFINITION,
			SIMCONNECT_CLIENT_DATA_PERIOD_ON_SET, SIMCONNECT_CLIENT_DATA_REQUEST_FLAG_CHANGED, 0, 0, 0);

		// 2) Set up control connection

		// First method: control data area
		Control.Event = 0;
		Control.Parameter = 0;
		// 2) Set up control connection

		// First method: control data area
		Control.Event = 0;
		Control.Parameter = 0;

		// Associate an ID with the PMDG control area name
		hr = SimConnect_MapClientDataNameToID(hSimConnect, PMDG_NG3_CONTROL_NAME, PMDG_NG3_CONTROL_ID);

		// Define the control area structure - this is a required step
		hr = SimConnect_AddToClientDataDefinition(hSimConnect, PMDG_NG3_CONTROL_DEFINITION, 0, sizeof(PMDG_NG3_Control), 0, 0);

		// Sign up for notification of control change.  
		hr = SimConnect_RequestClientData(hSimConnect, PMDG_NG3_CONTROL_ID, CONTROL_REQUEST, PMDG_NG3_CONTROL_DEFINITION,
			SIMCONNECT_CLIENT_DATA_PERIOD_ON_SET, SIMCONNECT_CLIENT_DATA_REQUEST_FLAG_CHANGED, 0, 0, 0);




		// 3) Request current aircraft .air file path
		hr = SimConnect_RequestSystemState(hSimConnect, AIR_PATH_REQUEST, "AircraftLoaded");
		// also request notifications on sim start and aircraft change
		hr = SimConnect_SubscribeToSystemEvent(hSimConnect, EVENT_SIM_START, "SimStart");

		//hr = SimConnect_MapClientEventToSimEvent(hSimConnect, EVENT_CDU_EXEC, "#70188"); //EVT_CDU_L_EXEC

		// 5) Main loop




		while (quit == 0)
		{
			// receive and process the NG3 data


			SimConnect_CallDispatch(hSimConnect, MyDispatchProc, this);
			if (data) {
				loop(this);
			}
			Sleep(1);
		}

		hr = SimConnect_Close(hSimConnect);
	}
	else {
		printf("\nUnable to connect!\n");
	}


}

