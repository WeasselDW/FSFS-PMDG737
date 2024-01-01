
#include <windows.h>
#include <tchar.h>
#include <stdio.h>
#include <strsafe.h>

#include "PMDG_NG3_SDK.h"
#include <iostream>
#include "SimConnect.h"
#include "Sim.h"
#include "Serial.h"
#include <functional>
#include <thread>
#include <chrono>
Sim* sim;
Serial* Arduino;

void loop(Sim* sim) {
	std::string receivedData = Arduino->ReadString();
	if (!receivedData.empty()) {
		std::cout << "Received from Arduino: " << receivedData;
	}


	if (sim->data) {
		if (sim->data->CDU_annunEXEC[0]) {
			
		}
	}
}


int main()
{
	Arduino = new Serial(L"COM3");
	sim = new Sim(&loop);

}
