/*
 * main.cpp
 *
 *  Created on: 11.12.2013
 *      Author: niko
 */

#include <stdio.h>
#include "FlurryC.h"
#include <string.h>


extern "C"
{

	void flurry_set_show_error_in_log_enabled_Ext(int anEnabled)
	{
		flurry_set_show_error_in_log_enabled(anEnabled);
	}

	void flurry_set_debug_log_enabled_Ext(int anEnabled)
	{
		flurry_set_debug_log_enabled(anEnabled);
	}

	void flurry_start_session_Ext(const char* flurryApiKey )
	{
		flurry_start_session(flurryApiKey, NULL, NULL, 0);
	}

	void flurry_log_event_Ext(const char *anEventName, int aTimed ){
		flurry_log_event(anEventName, aTimed);
	}

	void flurry_log_event_with_params_Ext(const char *anEventName, int aTimed, const char *aParamsAndKeys, int aParamCount){
	    //flurry_log_event_with_params(const char *anEventName, int aTimed, const char **aParamKeys, const char **aParamValues, int aParamCount);
	    char * str1 = new char [strlen(aParamsAndKeys)];
        strcpy(str1, aParamsAndKeys);

        char * pch = strtok (str1,"\n");
        char ** keysArray = new char*[aParamCount];
        char ** valuesArray = new char*[aParamCount];
        int arrayCount = 0;
        while (pch != NULL)                         // пока есть лексемы
        {
            const char * oneValue = index(pch, '=');
            oneValue++;

            valuesArray[arrayCount] = new char [strlen(oneValue)];
            strcpy(valuesArray[arrayCount], oneValue);

            int keyLen = (int)(oneValue - pch);
            keysArray [arrayCount] =  new char [keyLen];
            memset(keysArray [arrayCount] , 0, keyLen);
            strncpy(keysArray[arrayCount], pch, keyLen-1);

            pch = strtok (NULL, "\n");
            arrayCount++;
        }

        flurry_log_event_with_params(anEventName, aTimed, (const char**)keysArray, (const char**)valuesArray, aParamCount);

        for (int i = 0; i< aParamCount; i++)
        {
            delete keysArray[i];
            delete valuesArray[i];
        }
        delete keysArray;
        delete valuesArray;

        delete [] str1;

	}

	void flurry_end_timed_event_Ext(const char *anEventName){

		flurry_end_timed_event(anEventName, NULL, NULL, 0);
	}
}
