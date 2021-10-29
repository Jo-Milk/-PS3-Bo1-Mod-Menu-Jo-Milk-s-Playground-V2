void scrfct_setmemory()
{
    // Verify that we have 2 parameters for this function.
    if (Scr_GetNumParam(0) == 2)
    {
        // Getting parameters, we don't check the type using a function again here but we could have did it.
        char *hexAddress = Scr_GetString(0, SCRIPTINSTANCE_SERVER);
        char *hexData = Scr_GetString(1, SCRIPTINSTANCE_SERVER);

        if (hexAddress && hexData)
        {
            // Allocate input size +2 in case to handle zero padding and null terminated char.
            char hexAddressFixed[strlen(hexAddress) + 2];
            char hexDataFixed[strlen(hexData) + 2];
               
            hex_str_to_padded_hex_str(hexAddressFixed, hexAddress);
            hex_str_to_padded_hex_str(hexDataFixed, hexData);

            size_t addressSize = strlen(hexAddressFixed)/2;
            size_t dataSize = strlen(hexDataFixed)/2;

            int offset = hex_str_to_int32(hexAddressFixed, addressSize);

            char buffer[dataSize];
            memset(buffer, 0, dataSize);
            hex_str_to_buffer(buffer, hexDataFixed, dataSize);

            sys_dbg_write_process_memory(offset, buffer, dataSize);

            printf("Function 'setMemory' called from gsc with the following parameters: %s, %s.\n", hexAddress, hexData);
        }
        else
            printf("Cannot resolve setmemory parameters call from gsc.");
    }
}
opd_s NTFY = { 0x354F08, TOC };
void(*scr_Notify)(int ent, short stringValue, unsigned int paramcount) = (void(*)(int, short, unsigned int))&NTFY;

void GSC_KeyboardCallback(int localClientNum, const wchar_t *text, size_t size)
{
	if (size)
	{
		if (WideCharacterToString(GSC_Keyboardbuffer, text, size))
		{
			Scr_ClearOutParams();
			Scr_AddString(GSC_Keyboardbuffer, SCRIPTINSTANCE_SERVER);
			scr_Notify( 0x012AB290 + (HostNum * 0x2F8),SL_GetString("JM_Keyboard",0,SCRIPTINSTANCE_SERVER),1);
			memset(GSC_Keyboardbuffer, 0, MAX_STRING_CHARS);
			GSC_Keyboardbool = false;
		}
	}
}

void scrfct_ps3_keyboard()
{
    if (Scr_GetNumParam(0) == 2)
    {
		char* title = Scr_GetString(0, SCRIPTINSTANCE_SERVER);
        int size = Scr_GetInt(1, SCRIPTINSTANCE_SERVER);
		if(size)
		{
		if(GSC_Keyboardbool == false)
		{
			GSC_Keyboardbool = true;
            DrawKeyboard(title,"", size, CELL_OSKDIALOG_PANELMODE_ALPHABET, GSC_KeyboardCallback);
			Scr_AddInt(1, SCRIPTINSTANCE_SERVER);
		}
		else
		Scr_AddInt(0, SCRIPTINSTANCE_SERVER);
		}
		else
		Scr_AddInt(0, SCRIPTINSTANCE_SERVER);
    }
}


void scrfct_ps3_godclass()
{
    // Verify that we have 2 parameters for this function.
    if (Scr_GetNumParam(0) == 1)
    {
        // Getting parameters, we don't check the type using a function again here but we could have did it.
        int vari = Scr_GetInt(0, SCRIPTINSTANCE_SERVER);

        if(vari == 1)
		{
			if(revgodclass == false)
			{
				vari = 0;
			}
			else
			{
				vari = 1;
			}
		}
		else if(vari == 2)
		{
			if(revgodclass == false)
			{
				revgodclass = true;
				vari = 1;
			}
			else
			{
				revgodclass = false;
				vari = 0;
			}
		}
		Scr_AddInt(vari, SCRIPTINSTANCE_SERVER);
    }
}

void cscrfct_setmemory()
{
    // Verify that we have 2 parameters for this function.
    if (Scr_GetNumParam(1) == 2)
    {
        // Getting parameters, we don't check the type using a function again here but we could have did it.
        char *hexAddress = Scr_GetString(0, SCRIPTINSTANCE_CLIENT);
        char *hexData = Scr_GetString(1, SCRIPTINSTANCE_CLIENT);

        if (hexAddress && hexData)
        {
            // Allocate input size +2 in case to handle zero padding and null terminated char.
            char hexAddressFixed[strlen(hexAddress) + 2];
            char hexDataFixed[strlen(hexData) + 2];
               
            hex_str_to_padded_hex_str(hexAddressFixed, hexAddress);
            hex_str_to_padded_hex_str(hexDataFixed, hexData);

            size_t addressSize = strlen(hexAddressFixed)/2;
            size_t dataSize = strlen(hexDataFixed)/2;

            int offset = hex_str_to_int32(hexAddressFixed, addressSize);

            char buffer[dataSize];
            memset(buffer, 0, dataSize);
            hex_str_to_buffer(buffer, hexDataFixed, dataSize);

            sys_dbg_write_process_memory(offset, buffer, dataSize);

            printf("Function 'setMemory' called from gsc with the following parameters: %s, %s.\n", hexAddress, hexData);
        }
        else
            printf("Cannot resolve setmemory parameters call from csc.\n");
    }
}

void scrfct_ps3_debug()
{
    if (Scr_GetNumParam(0) == 1)
    {
        char *message = Scr_GetString(0, SCRIPTINSTANCE_SERVER);

        if (message)
        {
            printf("GSC debug : %s\n", message);
        }
        else
            printf("Cannot resolve ps3_debug parameters call from gsc\n");
	}
}

void scrfct_Cbuf()
{
    if (Scr_GetNumParam(0) == 1)
    {
        char *string = Scr_GetString(0, SCRIPTINSTANCE_SERVER);
        if (string)
        {
            Cbuf_addtext(string);
        }
	}
}

void cscrfct_ps3_debug()
{
    if (Scr_GetNumParam(1) == 1)
    {
        char *message = Scr_GetString(0, SCRIPTINSTANCE_CLIENT);

        if (message)
        {
            printf("CSC debug : %s\n", message);
        }
        else
            printf("Cannot resolve ps3_debug parameters call from csc\n");
	}
	else
	{
		printf("Cannot resolve ps3_debug parameters call from csc\n");
	}
}

//0x5B7840 SL_FindLowercaseString(message,0)

opd_s SL_FindLowercaseString_t = { 0x5B7840, TOC };
int(*SL_FindLowercaseString)(const char* string, int inst) = (int(*)(const char* , int ))&SL_FindLowercaseString_t;
opd_s Scr_GetConstLowercaseString_t = { 0x5D0438, TOC };
int(*Scr_GetConstLowercaseString)(char* string, int inst) = (int(*)(char* , int ))&Scr_GetConstLowercaseString_t;


void cscrfct_jm_iprintln()
{
	if (Scr_GetNumParam(1) == 1)
    {
        char *message = Scr_GetString(0, SCRIPTINSTANCE_CLIENT);

        if (message)
        {
			if(!strcmp("to Open Non-Host Menu",message))
			{
            CG_GameMessage(0, va("\x0005 + \x0014 ^2%s",message));
			}
			else
			{
				CG_GameMessage(0, message);
			}
        }
	}
}

int Custom_Model[18];
void scrfct_jm_setmodel()
{
    if (Scr_GetNumParam(0) == 2)
    {
        char* model = Scr_GetString(0, SCRIPTINSTANCE_SERVER);
		int client = Scr_GetInt(1, SCRIPTINSTANCE_SERVER);
		if(IsPlayer(client))
	    {
		int entity = Spawn_Script_Model2(*(float*)(0x13950EC + (client * 0x2A38)),*(float*)(0x13950EC + (client * 0x2A38) + 4),*(float*)(0x13950EC + (client * 0x2A38) + 8),*(float*)(0x1395248 + (0x2A38 * client)),*(float*)(0x1395248 + (0x2A38 * client)+ 4),*(float*)(0x1395248 + (0x2A38 * client)+ 8),model);
		Custom_Model[client] = entity;
		Scr_AddEntity(entity, SCRIPTINSTANCE_SERVER);
		}
	}
}
void scrfct_jm_movemodel()
{
    if (Scr_GetNumParam(0) == 2)
    {
        char* model = Scr_GetString(0, SCRIPTINSTANCE_SERVER);
		int client = Scr_GetInt(1, SCRIPTINSTANCE_SERVER);
		if(IsPlayer(client))
	    {
		if(strcmp(model, "t5_veh_rcbomb_allies") == 0 || strcmp(model, "t5_veh_rcbomb_axis") == 0)
		Move_Model_Script_Origin(Custom_Model[client],*(float*)(0x13950EC + (client * 0x2A38)),*(float*)(0x13950EC + (client * 0x2A38) + 4),*(float*)(0x13950EC + (client * 0x2A38) + 8),*(float*)(0x1395248 + (0x2A38 * client)),*(float*)(0x1395248 + (0x2A38 * client)+ 4),*(float*)(0x1395248 + (0x2A38 * client)+ 8));
		else
		Move_Model_Script_Origin(Custom_Model[client],*(float*)(0x13950EC + (client * 0x2A38)),*(float*)(0x13950EC + (client * 0x2A38) + 4),((*(float*)(0x13950EC + (client * 0x2A38) + 8)) + 20),*(float*)(0x1395248 + (0x2A38 * client)),*(float*)(0x1395248 + (0x2A38 * client)+ 4),*(float*)(0x1395248 + (0x2A38 * client)+ 8));
		}
	}
}

void IspressingJM()
{
	if(Aimbot)
	{
	 if (Pressed(Btn::L1) || Pressed(Btn::R1) && Pressed(Btn::L1))
	     Scr_AddInt(1, SCRIPTINSTANCE_CLIENT);
	 else
		 Scr_AddInt(0, SCRIPTINSTANCE_CLIENT);
	}
	else
		Scr_AddInt(0, SCRIPTINSTANCE_CLIENT);
}


void MyCSCHook()
{
	if(Aimbot)
	{
	 if (Pressed(Btn::L1) || Pressed(Btn::R1) && Pressed(Btn::L1))
	 {
	 DoAimbot();
	 }
	}
}