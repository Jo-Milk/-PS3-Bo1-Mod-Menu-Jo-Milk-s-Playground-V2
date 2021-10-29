bool DEX = true;
bool hen = false;
int32_t sys_dbg_write_process_memory_hen(uint64_t ea, const void* data, size_t size)
{
    system_call_6(8, 0x7777, 0x32, (uint64_t)sys_process_getpid(), (uint64_t)ea, (uint64_t)data, (uint64_t)size);
}
int32_t sys_dbg_write_process_memory_Dex(uint64_t ea, const void* data, size_t size)
{
    system_call_4(905, (uint64_t)sys_process_getpid(), ea, size, (uint64_t)data);
    return_to_user_prog(int32_t);
}
int32_t sys_dbg_write_process_memory(uint64_t ea, const void* data, size_t size)
{
	if(hen == true)
	{
    sys_dbg_write_process_memory_hen(ea, data,  size);
	}
	else
	{
	sys_dbg_write_process_memory_Dex(ea, data,  size);
	}
}
int32_t sys_dbg_read_process_memory_hen(uint64_t ea, const void* data, size_t size)
{
     system_call_6(8, 0x7777, 0x31, (uint64_t)sys_process_getpid(), (uint64_t)ea, (uint64_t)data, (uint64_t)size);
}
int32_t sys_dbg_read_process_memory_Dex(uint64_t ea, const void* data, size_t size)
{
     system_call_4(904, (uint64_t)sys_process_getpid(), ea, size, (uint64_t)data);
     return_to_user_prog(int32_t);
}
int32_t sys_dbg_read_process_memory(uint64_t ea, void* data, size_t size)
{
	if(hen == true)
	{
        sys_dbg_read_process_memory_hen(ea, data,  size);
	}
	else
	{
	    sys_dbg_read_process_memory_Dex(ea, data,  size);
	}
}

template<typename T>
void WriteProcessMemory(uint32_t address, const T value, size_t size)
{
	sys_dbg_write_process_memory(address, &value, size);
}

void HookFunctionStart(uint32_t functionStartAddress, uint32_t newFunction, uint32_t functionStub)
{
    uint32_t normalFunctionStub[8], hookFunctionStub[4];
    sys_dbg_read_process_memory(functionStartAddress, normalFunctionStub, 0x10);
    normalFunctionStub[4] = 0x3D600000 + ((functionStartAddress + 0x10 >> 16) & 0xFFFF);
    normalFunctionStub[5] = 0x616B0000 + (functionStartAddress + 0x10 & 0xFFFF);
    normalFunctionStub[6] = 0x7D6903A6;
    normalFunctionStub[7] = 0x4E800420;
    sys_dbg_write_process_memory(functionStub, normalFunctionStub, 0x20);
    hookFunctionStub[0] = 0x3D600000 + ((newFunction >> 16) & 0xFFFF);
    hookFunctionStub[1] = 0x616B0000 + (newFunction & 0xFFFF);
    hookFunctionStub[2] = 0x7D6903A6;
    hookFunctionStub[3] = 0x4E800420;
    sys_dbg_write_process_memory(functionStartAddress, hookFunctionStub, 0x10);
}
int32_t HookFunction(uint32_t address, uint32_t function)
{
	uint32_t opcode[4];
	opcode[0] = 0x3D600000 + ((function >> 16) & 0xFFFF);
	opcode[1] = 0x616B0000 + (function & 0xFFFF);
	opcode[2] = 0x7D6903A6;
	opcode[3] = 0x4E800420;
	return sys_dbg_write_process_memory(address, &opcode, 0x10);
}

size_t get_file_size(char *filePath)
{
    int size = 0;
    CellFsStat fstat;
    CellFsErrno err = cellFsStat(filePath, &fstat);
    if (err != CELL_FS_SUCCEEDED)
    {
        return err;
    }
    return fstat.st_size;
}

int console_write(const char * s)
{
        uint32_t len;
        system_call_4(403, 0, (uint64_t) s, 32, (uint64_t) &len);
        return_to_user_prog(int);
}
void sleep(usecond_t time)
{
        sys_timer_usleep(time * 1000);
}

int sys_ppu_thread_exit()//I think this for the debugger
{
	system_call_1(41, 0);//using syscall 41 int sys_ppu_thread_exit(error code)
	return_to_user_prog(int);
}

bool yesno_dialog_result = false;
bool yesno_dialog_input = false;
bool ok_dialog_input = false;
bool ok_dialog_result = false;

void YesNoDialogCallBack(int button_type, void *userdata)
{
	switch (button_type)
	{
	case CELL_MSGDIALOG_BUTTON_YES:
		yesno_dialog_result = true;
		break;
	case CELL_MSGDIALOG_BUTTON_NO:
		yesno_dialog_result = false;
		break;
	}
	yesno_dialog_input = false;
}

bool DrawYesNoMessageDialog(const char *str)
{
	cellMsgDialogOpen2(CELL_MSGDIALOG_TYPE_SE_TYPE_NORMAL | CELL_MSGDIALOG_TYPE_BUTTON_TYPE_YESNO | CELL_MSGDIALOG_TYPE_DISABLE_CANCEL_ON | CELL_MSGDIALOG_TYPE_DEFAULT_CURSOR_NO, str, YesNoDialogCallBack, NULL, NULL);
	yesno_dialog_input = true;
	while (yesno_dialog_input)
	{
		sleep(16);
		cellSysutilCheckCallback();
	}
	return yesno_dialog_result;
}

void OkDialogCallBack(int button_type, void *userdata)
{
	switch (button_type)
	{
	case CELL_MSGDIALOG_BUTTON_OK:ok_dialog_result = true;break;
	default : break;
	}
	ok_dialog_input = false;
}
void DrawOkMessageDialog(const char *str)
{
	cellMsgDialogOpen2(CELL_MSGDIALOG_TYPE_SE_TYPE_NORMAL | CELL_MSGDIALOG_TYPE_BUTTON_TYPE_OK | CELL_MSGDIALOG_TYPE_DISABLE_CANCEL_ON | CELL_MSGDIALOG_TYPE_DEFAULT_CURSOR_OK, str, OkDialogCallBack, NULL, NULL);
	ok_dialog_input = true;
	while (ok_dialog_input)
	{
		sleep(16);
		cellSysutilCheckCallback();
	}
}
const char * GetSelfUserName()
{
    CellUserInfoUserStat stat;
    cellUserInfoGetStat(CELL_SYSUTIL_USERID_CURRENT, &stat);
    return stat.name;
}
 
const char * GetSelfOnlineName()
{
    SceNpOnlineName onlineName;
    sceNpManagerGetOnlineName(&onlineName);
    return onlineName.data;
}
 
const char * GetSelfName()
{
    int connectionStatus;
    sceNpManagerGetStatus(&connectionStatus);//checks if online
    if (connectionStatus == SCE_NP_MANAGER_STATUS_ONLINE)
        return GetSelfOnlineName();
    else
        return GetSelfUserName();
}



static int connect_to_CAPPI(void)
{
 struct sockaddr_in sin;
 int s;

 sin.sin_family = AF_INET;
 sin.sin_addr.s_addr = 0x7F000001; //127.0.0.1 (localhost)
 sin.sin_port = htons(6333);
 s = socket(AF_INET, SOCK_STREAM, 0);
 if (s < 0)
 {
  return -1;
 }

 if (connect(s, (struct sockaddr *)&sin, sizeof(sin)) < 0)
 {
  return -1;
 }

 return s;
}


static int connect_to_webman(void)
{
 struct sockaddr_in sin;
 int s;

 sin.sin_family = AF_INET;
 sin.sin_addr.s_addr = 0x7F000001; //127.0.0.1 (localhost)
 sin.sin_port = htons(80);         //http port (80)
 s = socket(AF_INET, SOCK_STREAM, 0);
 if (s < 0)
 {
  return -1;
 }

 if (connect(s, (struct sockaddr *)&sin, sizeof(sin)) < 0)
 {
  return -1;
 }

 return s;
}

static void sclose(int *socket_e)
{
 if (*socket_e != -1)
 {
  shutdown(*socket_e, SHUT_RDWR);
  socketclose(*socket_e);
  *socket_e = -1;
 }
}


static void send_wm_request(const char *cmd)
{
 // send command
 int conn_s = -1;
 conn_s = connect_to_webman();

 struct timeval tv;
 tv.tv_usec = 0;
 tv.tv_sec = 3;
 setsockopt(conn_s, SOL_SOCKET, SO_SNDTIMEO, &tv, sizeof(tv));
 setsockopt(conn_s, SOL_SOCKET, SO_RCVTIMEO, &tv, sizeof(tv));

 if (conn_s >= 0)
 {
  char wm_cmd[1048];
  int cmd_len = sprintf(wm_cmd, "GET %s HTTP/1.0\r\n", cmd);
  send(conn_s, wm_cmd, cmd_len, 0);
  sclose(&conn_s);
 }
}

static void send_CCAPI_request(const char *cmd)
{
 // send command
 int conn_s = -1;
 conn_s = connect_to_CAPPI();

 struct timeval tv;
 tv.tv_usec = 0;
 tv.tv_sec = 3;
 setsockopt(conn_s, SOL_SOCKET, SO_SNDTIMEO, &tv, sizeof(tv));
 setsockopt(conn_s, SOL_SOCKET, SO_RCVTIMEO, &tv, sizeof(tv));

 if (conn_s >= 0)
 {
  char wm_cmd[1048];
  int cmd_len = sprintf(wm_cmd, "GET %s HTTP/1.0\r\n", cmd);
  send(conn_s, wm_cmd, cmd_len, 0);
  sclose(&conn_s);
 }
}

void fixSpaces(char** szReturn) {
 char *str = *szReturn;
 char _returnStr[512];// = (char*)Malloc(128);

 _returnStr[0] = '\0';

 int dwStrIndex = 0;

 for (int i = 0; i < strlen(str) + 1; i++) {
  if (str[i] != 0x20) {
   _returnStr[dwStrIndex] = str[i];
   dwStrIndex++;
  }
  else
  {
   _returnStr[dwStrIndex] = '%';
   _returnStr[dwStrIndex + 1] = '2';
   _returnStr[dwStrIndex + 2] = '0';
   dwStrIndex += 3;
  }


  _returnStr[dwStrIndex] = '\0';
 }

 *szReturn = _returnStr;
}


void AreYouCCAPIorWebMan()
{
	int CCAPI_s = -1;
	CCAPI_s = connect_to_CAPPI();
	if(CCAPI_s != -1)
	{
		CCAPI = true;
		WebMan = false;
		NoCW = false;
	}
	else
	{
		int web_s = -1;
		web_s= connect_to_webman();
		if(web_s >= 0)
	    {
		CCAPI = false;
		WebMan = true;
		NoCW = false;
	    }
		else
		{
			CCAPI = false;
            WebMan = false;
			NoCW = true;
		}
	}

}


void DoNotify(char *szFormat,int id = 0) {
 char _notify_buffer[512];
 if(CCAPI == true)
 {
 snprintf(_notify_buffer, 512, "/ccapi/notify?id=%i&msg=%s",id,szFormat);
 send_CCAPI_request(_notify_buffer);
 }
 else if(WebMan == true)
 {
 fixSpaces(&szFormat);
 snprintf(_notify_buffer, 512, "/notify.ps3mapi?msg=%s", szFormat);
 send_wm_request(_notify_buffer);
 }
}
/*
void ShutDownPS3() {
 char _notify_buffer[512];
 if(CCAPI == true)
 {
 snprintf(_notify_buffer, 512, "/ccapi/shutdown?mode=1");
 send_CCAPI_request(_notify_buffer);
 }
 else if(WebMan == true)
 {
 snprintf(_notify_buffer, 512, "/shutdown.ps3");
 send_wm_request(_notify_buffer);
 }
}
void RestartPS3() {
 char _notify_buffer[512];
 if(CCAPI == true)
 {
 snprintf(_notify_buffer, 512, "/ccapi/shutdown?mode=2");
 send_CCAPI_request(_notify_buffer);
 }
 else if(WebMan == true)
 {
 snprintf(_notify_buffer, 512, "/restart.ps3");
 send_wm_request(_notify_buffer);
 }
}
void Buzzer(int snd = 1)
{
 char _notify_buffer[512];
 if(CCAPI == true)
 {
 snprintf(_notify_buffer, 512, "/ccapi/ringbuzzer?type=%i",snd);
 send_CCAPI_request(_notify_buffer);
 }
 else if(WebMan == true)
 {
 snprintf(_notify_buffer, 512, "/buzzer.ps3mapi?mode=%i",snd);
 send_wm_request(_notify_buffer);
 }
}
*/