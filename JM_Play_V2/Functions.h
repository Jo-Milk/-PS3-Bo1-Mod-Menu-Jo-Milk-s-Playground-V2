struct opd_s
{
	int32_t sub;
	int32_t toc;
};

opd_s va_t = { 0x4DB3D8, TOC };
char *(*va)(const char *format, ...) = (char *(*)(const char *, ...))&va_t;

opd_s DB_FindXAssetHeader_t = { 0x2601A0, TOC };
XAssetHeader *(*DB_FindXAssetHeader)(XAssetHeader *header, XAssetType type, const char *name, bool errorIfMissing, int waitTime) = (XAssetHeader *(*)(XAssetHeader *, XAssetType, const char *, bool ,int))&DB_FindXAssetHeader_t;
opd_s DB_LinkXAssetEntry_t = { 0x25EE38, TOC };
XAssetEntryPoolEntry*(*DB_LinkXAssetEntry)(XAssetEntry *newEntry, int allowOverride) = (XAssetEntryPoolEntry*(*)(XAssetEntry *, int))&DB_LinkXAssetEntry_t;
opd_s Dvar_FindVar_t = { 0x4C55A0, TOC };
dvar_s*(*Dvar_FindVar)(const char *name) = (dvar_s*(*)(const char *))&Dvar_FindVar_t;
opd_s Scr_ExecThread_t = { 0x5DD580, TOC };
unsigned short(*Scr_ExecThread)(scriptInstance_t inst, int handle, int paramcount) = (unsigned short(*)(scriptInstance_t , int, int))&Scr_ExecThread_t;
opd_s Scr_FreeThread_t = { 0x5CB2C0, TOC };
void(*Scr_FreeThread)(unsigned short handle, scriptInstance_t inst) = (void(*)(unsigned short, scriptInstance_t))&Scr_FreeThread_t;

opd_s Scr_GetMethod_t = { 0x315BA8, TOC };
popd32(*Scr_GetMethod)(const char **pName, int *type) = (popd32(*)(const char **, int *))&Scr_GetMethod_t;

opd_s Scr_GetFunction_t = { 0x310FD8, TOC };
popd32(*Scr_GetFunction)(const char **pName, int *type) = (popd32(*)(const char **, int *))&Scr_GetFunction_t;

opd_s Scr_GetChecksum_t = { 0x5BA818, TOC };
void(*Scr_GetChecksum)(scrChecksum_t *vmChecksum, scriptInstance_t inst) = (void(*)(scrChecksum_t *, scriptInstance_t ))&Scr_GetChecksum_t;

opd_s G_Damage_t = { 0x2D8038, TOC };
int(*G_Damage)(int targ, int inflictor, int attacker, float *Dir, float *point, int damage, int dFlag, int mod, int weapon, hitLocation_t hitLocation, unsigned int modelIndex, unsigned int partName, int timeOffset) = (int(*)(int, int, int, float*, float*, int, int, int, int, hitLocation_t, unsigned int, unsigned int, int))&G_Damage_t;
opd_s webyte_J = { 0x375548, TOC };
int(*G_GetWeaponIndexForName)(const char* weapon) = (int(*)(const char*))&webyte_J;

opd_s JM_cellSpursLFQueuePushBody_t = { 0x8C7080, TOC };
int(*JM_cellSpursLFQueuePushBody)(CellSpursLFQueue *lfqueue, const void *buffer, unsigned int isBlocking) = (int(*)(CellSpursLFQueue *, const void *, unsigned int))&JM_cellSpursLFQueuePushBody_t;

opd_s Scr_GetFunctionHandle_t = { 0x5A92A0, TOC };
int(*Scr_GetFunctionHandle)(scriptInstance_t inst, const char *scriptName, const char *functionName) = (int(*)(scriptInstance_t, const char *, const char *))&Scr_GetFunctionHandle_t;

opd_s Scr_GetNumParam_t = { 0x5CB210, TOC };
int(*Scr_GetNumParam)(int scriptInstance) = (int(*)(int))&Scr_GetNumParam_t;

opd_s Scr_GetString_t = { 0x5D0D68, TOC };
char*(*Scr_GetString)(unsigned int index, scriptInstance_t scriptInstance) = (char*(*)(unsigned int, scriptInstance_t))&Scr_GetString_t;

opd_s Scr_GetInt_t = { 0x5D16C0, TOC };
int(*Scr_GetInt)(unsigned int index, scriptInstance_t scriptInstance) = (int(*)(unsigned int, scriptInstance_t))&Scr_GetInt_t;

opd_s Scr_LoadGameType_t = { 0x315728, TOC };
void(*Scr_LoadGameType)(void) = (void(*)(void))&Scr_LoadGameType_t;

opd_s Scr_LoadScript_t = { 0x5A9068, TOC };
void(*Scr_LoadScript)(scriptInstance_t inst, const char *scriptName) = (void(*)(scriptInstance_t, const char *))&Scr_LoadScript_t;

opd_s Scr_LoadScriptInternal_t = { 0x5A8D38, TOC };
void(*Scr_LoadScriptInternal)(scriptInstance_t inst, const char *scriptName) = (void(*)(scriptInstance_t, const char *))&Scr_LoadScriptInternal_t;


opd_s Dvar_GetBool_t = { 0x4C7BF0, TOC };
bool(*Dvar_GetBool)(const char *) = (bool(*)(const char *))&Dvar_GetBool_t;

opd_s Dvar_SetFromStringByName_t = { 0x4CF160, TOC };
void(*Dvar_SetFromStringByName)(const char *dvarName, const char *value) = (void(*)(const char *, const char *))&Dvar_SetFromStringByName_t;


opd_s Scr_GetSelf_t = { 0x5BA4F0, TOC };
int(*Scr_GetSelf)(scriptInstance_t inst,int value) = (int(*)(scriptInstance_t,int))&Scr_GetSelf_t;
opd_s SL_ConvertToString_t = { 0x5B6D10, TOC };
const char*(*SL_ConvertToString)(int stringValue, scriptInstance_t inst) = (const char*(*)(int, scriptInstance_t))&SL_ConvertToString_t;

opd_s Session_IsHost_t = { 0x698490, TOC };
bool(*Session_IsHost)(SessionData_s *session, const int clientNum) = (bool(*)(SessionData_s *, const int))&Session_IsHost_t;

opd_s CG_GetClientNum_t = { 0x116A60, TOC };
int(*CG_GetClientNum)(int localClientNum) = (int(*)(int))&CG_GetClientNum_t;

opd_s cb1 = { 0x399CC8, TOC };
void(*Cbuf)(int client, char* cmd) = (void(*)(int, char*))&cb1;

opd_s SV_GameSendServerCommand_t = { 0x3E95F0, TOC };
void(*SV_GameSendServerCommand)(int client, int type, char* cmd) = (void(*)(int, int, char*))&SV_GameSendServerCommand_t;


opd_s SV_AddServerCommand_t = { 0x3EED08, TOC };
void(*SV_AddServerCommand)(int client, int type, char* cmd) = (void(*)(int, int, char*))&SV_AddServerCommand_t;

opd_s makeDvarServerInfo_t = { 0x31B590, TOC };
void(*GSC_makeDvarServerInfo)() = (void(*)())&makeDvarServerInfo_t;

opd_s UI_OpenToastPopup_t = { 0x42C198, TOC };
void(*UI_OpenToastPopup)(int localClientNum, const char *toastPopupIconName, const char *toastPopupTitle, const char *toastPopupDesc, int toastPopupDuration) = (void(*)(int, const char *, const char *, const char *, int))&UI_OpenToastPopup_t;

opd_s Cmd_MenuResponse_f_t = { 0x2D5AE8, TOC };
void(*Cmd_MenuResponse_f)(gentity_s *pEnt) = (void(*)(gentity_s *))&Cmd_MenuResponse_f_t;
opd_s SV_Cmd_ArgvBuffer_t = { 0x3997C8, TOC };
void(*SV_Cmd_ArgvBuffer)(int arg, char *buffer, int bufferLength) = (void(*)(int, char *, int))&SV_Cmd_ArgvBuffer_t;

opd_s AimTarget_IsTargetVisible_t = {0x58640,TOC};
bool(*AimTarget_IsTargetVisible)(int localClientNum, int targetEnt, short visBone) = (bool(*)(int localClientNum, int targetEnt, short visBone))&AimTarget_IsTargetVisible_t;
opd_s AimTarget_GetTagPos_t = {0x54C88,TOC};
float*(*AimTarget_GetTagPos)( int loaclclient,int cent, short tagName, float*pos) = (float*(*)( int, int , short , float*))&AimTarget_GetTagPos_t;

opd_s CG_LocationalTrace_t = {0x1A1C98,TOC};
void(*CG_LocationalTrace)(trace_t* results, const float *start, const float *end, int passEntityNum, int contentMask, bool checkRopes, int col_context_t) = (void(*)(trace_t* results, const float *start, const float *end, int passEntityNum, int contentMask, bool checkRopes, int col_context_t))&CG_LocationalTrace_t;

opd_s BG_GetWeaponDef_t = {0xC0A98,TOC};
int(*BG_GetWeaponDef)(unsigned short weaponIndex) = (int(*)(unsigned short ))&BG_GetWeaponDef_t;
opd_s BulletTrace_t = {0x18D6F0,TOC};
bool(*BulletTrace)(int localClientNum, BulletFireParams *bp, int weapDef, centity_s *attacker, BulletTraceResults *br, int lastSurfaceType) = (bool(*)(int localClientNum, BulletFireParams *bp, int weapDef, centity_s *attacker, BulletTraceResults *br, int lastSurfaceType))&BulletTrace_t;
opd_s Trace_GetEntityHitId_t = {0x38BD00,TOC};
short(*Trace_GetEntityHitId)(trace_t *trace) = (short(*)(trace_t *trace))&Trace_GetEntityHitId_t;
opd_s BG_GetSurfacePenetrationDepth_t = {0xA8A28,TOC};
float(*BG_GetSurfacePenetrationDepth)(int weapDef, int surfaceType) = (float(*)(int weapDef, int surfaceType))&BG_GetSurfacePenetrationDepth_t;
opd_s BG_AdvanceTrace_t = {0xABBB0,TOC};
bool(*BG_AdvanceTrace)(BulletFireParams *bp, BulletTraceResults *br, float dist) = (bool(*)(BulletFireParams *bp, BulletTraceResults *br, float dist))&BG_AdvanceTrace_t;
opd_s FireBulletPenetrate_t = { 0x001966A0, TOC };
void(*FireBulletPenetrate)(int localClientNum, BulletFireParams *bp, unsigned int weaponIndex, centity_s* attacker, float tracerStart[3], int drawTracer, int isPlayer, BulletTraceResults *br) = (void(*)(int, BulletFireParams*, unsigned int, centity_s*, float[3], int, int, BulletTraceResults*))&FireBulletPenetrate_t;
opd_s BG_GetSpreadForWeapon_t = {0xAB8C8,TOC};
void(*BG_GetSpreadForWeapon)(int ps, int weapDef, float *minSpread, float *maxSpread) = (void(*)(int ps, int weapDef, float *minSpread, float *maxSpread))&BG_GetSpreadForWeapon_t;

opd_s CL_SetViewAngles_t = {0x1A6448,TOC};
void(*CL_SetViewAngles)(int localClientNum, const float *angles) = (void(*)(int localClientNum, const float *angles))&CL_SetViewAngles_t;

bool CompareString(const char *str1, const char *str2)
{
	return !strcmp(str1, str2);
}

opd_s UI_OpenMenu_t = { 0x42F398, TOC };
void(*UI_OpenMenu)(int localClientNum, const char *menuName) = (void(*)(int, const char *))&UI_OpenMenu_t;

opd_s Key_SetCatcher_t = { 0x1BE2E0, TOC };
void(*Key_SetCatcher)(int localClientNum, int catcher) = (void(*)(int, int))&Key_SetCatcher_t;

opd_s Key_IsCatcherActive_t = { 0x1BF680, TOC };
bool(*Key_IsCatcherActive)(int localClientNum, int mask) = (bool(*)(int, int))&Key_IsCatcherActive_t;

opd_s Scr_AddInt_t = { 0x5DF2A0, TOC };
void(*Scr_AddInt)(int value, scriptInstance_t inst) = (void(*)(int, scriptInstance_t))&Scr_AddInt_t;
opd_s Scr_AddFloat_t = { 0x5DF630, TOC };
void(*Scr_AddFloat)(float value, scriptInstance_t inst) = (void(*)(float, scriptInstance_t))&Scr_AddFloat_t;
opd_s Scr_AddString_t = { 0x5DE750, TOC };
void(*Scr_AddString)(const char* value, scriptInstance_t inst) = (void(*)(const char*, scriptInstance_t))&Scr_AddString_t;
opd_s Scr_AddVector_t = { 0x5DEB08, TOC };
void(*Scr_AddVector)(float* value, scriptInstance_t inst) = (void(*)(float*, scriptInstance_t))&Scr_AddVector_t;
opd_s Scr_AddConstString_t = { 0x5DEEB8, TOC };
void(*Scr_AddConstString)(unsigned short value, scriptInstance_t inst) = (void(*)(unsigned short, scriptInstance_t))&Scr_AddConstString_t;
opd_s Scr_AddEntity_t = { 0x355028, TOC };
void(*Scr_AddEntity)(int value, scriptInstance_t inst) = (void(*)(int, scriptInstance_t))&Scr_AddEntity_t;
opd_s SL_GetString_t = { 0x5B99C8, TOC };
int(*SL_GetString)(const char* str, unsigned int user, scriptInstance_t inst) = (int(*)(const char*, unsigned int, scriptInstance_t))&SL_GetString_t;

opd_s CG_GameMessage_t = { 0x113550, TOC };
void(*CG_GameMessage)(int localClientNum, const char *msg) = (void(*)(int, const char *))&CG_GameMessage_t;

opd_s CG_BoldGameMessage_t = { 0x113528, TOC };
void(*CG_BoldGameMessage)(int localClientNum, const char *msg, int duration) = (void(*)(int, const char *, int))&CG_BoldGameMessage_t;

opd_s Dvar_GetString_t = { 0x4C7370, TOC };
char*(*Dvar_GetString)(const char *dvarName) = (char*(*)(const char *))&Dvar_GetString_t;

typedef void(*UI_KeyboardCallback)(int localClientNum, const wchar_t *text, size_t size);

opd_s ExecuteKeyboardCallback_t = { 0x56A270, TOC };
void(*ExecuteKeyboardCallback)(int localClientNum) = (void(*)(int))&ExecuteKeyboardCallback_t;

opd_s UI_DrawKeyboard_t = { 0x56A118, TOC };
void(*UI_DrawKeyboard)(int localClientNum, const wchar_t *title, const wchar_t *presetMessage, size_t size, UI_KeyboardCallback function) = (void(*)(int, const wchar_t *, const wchar_t *, size_t, UI_KeyboardCallback))&UI_DrawKeyboard_t;


void Scr_SetNumParam(scriptInstance_t inst, int numParams) 
{
    int ep = 0x1AF6334 + (inst * 0x4320) + 0x10;
    *(int*)(ep + 0xC) = numParams;
}
void Scr_ClearOutParams() 
{
    *(int*)(&scrVmPub->outparamcount) = 0;
}

opd_s ParseAddr(int Address) 
{
	opd_s GLS = { Address, TOC };
	return GLS;
}

///////////////////////////////////// non-host ///////////////////////////////////// 

opd_s R_AddCmdDrawStretchPic_t = { 0x751940, TOC };
opd_s Material_RegisterHandle_t = { 0x7458D8, TOC };
opd_s R_AddCmdDrawText_t = { 0x754410, TOC };
opd_s R_RegisterFont_t = { 0x734350, TOC };

void(*R_AddCmdDrawStretchPic)(float, float, float, float, float, float, float, float, float *, int) = (void(*)(float, float, float, float, float, float, float, float, float *, int))&R_AddCmdDrawStretchPic_t;
int(*Material_RegisterHandle)(char *, int) = (int(*)(char *, int))&Material_RegisterHandle_t;
void(*R_AddCmdDrawText)(char *, int, int, float, float, float, float, float, float *, int) = (void(*)(char *text, int maxChars, int font, float x, float y, float xScale, float yScale, float rotation, float *color, int style))&R_AddCmdDrawText_t;
int(*R_RegisterFont)(char *, int) = (int(*)(char *name, int imageTrack))&R_RegisterFont_t;




bool IsServerHost()
{
	return Session_IsHost(g_serverSession, CG_GetClientNum(0));
}

bool IsHost(int clientNum)
{
	return Session_IsHost(g_serverSession, clientNum);
}

void Cbuf_addtext(char* text)
{
    Cbuf(0, text);
}

void makeDvarServerInfo(char * var, char* val)
{
	Scr_AddString(val, SCRIPTINSTANCE_SERVER);
	Scr_AddString(var, SCRIPTINSTANCE_SERVER);
	Scr_SetNumParam(SCRIPTINSTANCE_SERVER, 2);
	GSC_makeDvarServerInfo();
	Scr_ClearOutParams();
}
bool IsPlayer(int client)
{
	if(client <= 18 && client >= 0)
	{
	    int player = *(int*)(0x12AB290 + (client * 0x2F8) + 0x144);//IsPlayer
		if(player != 0)//IsPlayer
			return true;
		else
			return false;
	}
	else
		return false;
}

void PlayerCmd_freezecontrols(int client, bool var)
{
	scr_entref_t enteref;
	enteref.client = client;
	enteref.entnum = client;
	Scr_AddInt(var, SCRIPTINSTANCE_SERVER);
	((void(*)(scr_entref_t))&ParseAddr(0x2C67A8))(enteref);
	Scr_ClearOutParams();
}
void SetDvar(const char *dvarName, const char *value)
{
	Dvar_SetFromStringByName(dvarName, value);
}
void DrawOkayPopup(const char *title, const char *message)
{
	SetDvar((char*)0x90FA58, title);//com_errorTitle
	SetDvar((char*)0x90FA40, message);//com_errorMessage
	if (!Key_IsCatcherActive(0, 0x10))
		Key_SetCatcher(0, 0x10);
	UI_OpenMenu(0, "error_popmenu");//error_popmenu
}


opd_s CM2 = { 0x36FFA0, TOC };
short (*G_ModelIndex)(const char* model) = (short(*)(const char*))&CM2;

short Gscr_PrecacheModel(const char* model)
{
	*(int*)0x121383C = 1;
	short ret = G_ModelIndex(model);
	*(int*)0x121383C = 0;
	return ret;
}

void iPrintln_GameMessage(const char *messageFormat, ...)
{
	va_list argptr;
	char text[MAX_STRING_CHARS];
	va_start(argptr, messageFormat);
	vsprintf(text, messageFormat, argptr);
	va_end(argptr);
	CG_GameMessage(0, text);
}

void iPrintlnBold_GameMessage(const char *messageFormat, ...)
{
	va_list argptr;
	char text[MAX_STRING_CHARS];
	va_start(argptr, messageFormat);
	vsprintf(text, messageFormat, argptr);
	va_end(argptr);
	CG_BoldGameMessage(0, text,5000);
}


void DrawKeyboard(char *title, const char *presetMessage, size_t size, uint32_t panelMode, UI_KeyboardCallback function)
{
	*(bool*)0x1B29434 = true;
	WriteProcessMemory<uint16_t>(0x56A122, HIWORD(panelMode), sizeof(uint16_t));
	wchar_t titleBuffer[MAX_STRING_CHARS], presetMessageBuffer[MAX_STRING_CHARS];
	StringToWideCharacter(titleBuffer, title, MAX_STRING_CHARS);
	StringToWideCharacter(presetMessageBuffer, presetMessage, MAX_STRING_CHARS);
	UI_DrawKeyboard(0, titleBuffer, presetMessageBuffer, size, function);
	WriteProcessMemory<uint16_t>(0x56A122, HIWORD(CELL_OSKDIALOG_PANELMODE_ALPHABET), sizeof(uint16_t));
}

int FromInt32ToRank(int Rank)
{
	if(Rank != 0)
		Rank--;
	return Rank;
}
int FromRankToRankXp(int Rank)
{
		if(Rank != 0 && Rank != 50)
		Rank--;
 switch(Rank)
 {
 case 0:return 0;
 case 1:return 300;
 case 2:return 1200;
 case 3:return 2700;
 case 4:return 4800;
 case 5:return 7500;
 case 6:return 10900;
 case 7:return 15000;
 case 8:return 19800;
 case 9:return 25300;
 case 10:return 31500;
 case 11:return 38600;
 case 12:return 46600;
 case 13:return 55500;
 case 14:return 65300;
 case 15:return 76000;
 case 16:return 87800;
 case 17:return 100700;
 case 18:return 114700;
 case 19:return 129800;
 case 20:return 146000;
 case 21:return 163400;
 case 22:return 182000;
 case 23:return 201800;
 case 24:return 222800;
 case 25:return 245000;
 case 26:return 268500;
 case 27:return 293300;
 case 28:return 319400;
 case 29:return 346800;
 case 30:return 375500;
 case 31:return 405600;
 case 32:return 437100;
 case 33:return 470000;
 case 34:return 504300;
 case 35:return 540000;
 case 36:return 577200;
 case 37:return 615900;
 case 38:return 656100;
 case 39:return 697800;
 case 40:return 741000;
 case 41:return 785800;
 case 42:return 832200;
 case 43:return 880200;
 case 44:return 929800;
 case 45:return 981000;
 case 46:return 1033900;
 case 47:return 1088500;
 case 48:return 1144800;
 case 49:return 1202800;
 case 50:return 1260800;
 default:return 1202800;
 }
}

enum svscmd_type
{
	SV_CMD_CAN_IGNORE = 0x0,
	SV_CMD_RELIABLE = 0x1,
};
opd_s LiveStats_GetRootDDLState_t = { 0x69D868, TOC };
ddlState_t *(*LiveStats_GetRootDDLState)() = (ddlState_t *(*)())&LiveStats_GetRootDDLState_t;

opd_s LiveStats_GetCacDDLState_t = { 0x69D858, TOC };
ddlState_t *(*LiveStats_GetCacDDLState)() = (ddlState_t *(*)())&LiveStats_GetCacDDLState_t;

opd_s DDL_MoveTo_t = { 0x5E4E88, TOC };
int(*DDL_MoveTo)(ddlState_t *searchState, ddlState_t *resultState, int argNum, ...) = (int(*)(ddlState_t *, ddlState_t *, int, ...))&DDL_MoveTo_t;

opd_s SV_GetClientDIntStat_t = { 0x3E2700, TOC };
unsigned int(*SV_GetClientDIntStat)(int clientNum, ddlState_t *searchState) = (unsigned int(*)(int, ddlState_t *))&SV_GetClientDIntStat_t;

opd_s SV_GetClientDStringStat_t = { 0x3E2600, TOC };
const char*(*SV_GetClientDStringStat)(int clientNum, ddlState_t *searchState) = (const char*(*)(int, ddlState_t *))&SV_GetClientDStringStat_t;

opd_s SV_SetClientDIntStat_t = { 0x3E7C40, TOC };
void(*SV_SetClientDIntStat)(int clientNum, ddlState_t *searchState, unsigned int value) = (void(*)(int, ddlState_t *, unsigned int))&SV_SetClientDIntStat_t;

opd_s SV_AddModifiedStats_t = { 0x3F5B00, TOC };
void(*SV_AddModifiedStats)(int clientNum) = (void(*)(int))&SV_AddModifiedStats_t;

int GetClientStat(int clientNum,char* name)
{
	ddlState_t searchState;
	if (DDL_MoveTo(LiveStats_GetRootDDLState(), &searchState, 2, "PlayerStatsList", name))
		return SV_GetClientDIntStat(clientNum, &searchState);
	else
		return 0;
}
void SetClientStat(int clientNum,char* name,int value)
{
	ddlState_t searchState;
	if (DDL_MoveTo(LiveStats_GetRootDDLState(), &searchState, 2, "PlayerStatsList", name))
		SV_SetClientDIntStat(clientNum, &searchState,value);
}
int GetClientPrestige(int clientNum)
{
	ddlState_t searchState;
	if (DDL_MoveTo(LiveStats_GetRootDDLState(), &searchState, 2, "PlayerStatsList", "PLEVEL"))
		return SV_GetClientDIntStat(clientNum, &searchState);
	else
		return 0;
}
void SetClientPrestige(int clientNum,int value)
{
	ddlState_t searchState;
	if (DDL_MoveTo(LiveStats_GetRootDDLState(), &searchState, 2, "PlayerStatsList", "PLEVEL"))
		SV_SetClientDIntStat(clientNum, &searchState,value);
}
int GetClientRankXp(int clientNum)
{
	ddlState_t searchState;
	if (DDL_MoveTo(LiveStats_GetRootDDLState(), &searchState, 2, "PlayerStatsList", "RANKXP"))
		return SV_GetClientDIntStat(clientNum, &searchState);
}
void SetClientRankXp(int clientNum,int value)
{
	ddlState_t searchState;
	if (DDL_MoveTo(LiveStats_GetRootDDLState(), &searchState, 2, "PlayerStatsList", "RANKXP"))
		SV_SetClientDIntStat(clientNum, &searchState,value);
}
int GetClientRank(int clientNum)
{
	ddlState_t searchState;
	if (DDL_MoveTo(LiveStats_GetRootDDLState(), &searchState, 2, "PlayerStatsList", "RANK"))
		return SV_GetClientDIntStat(clientNum, &searchState);
}
void SetClientRank(int clientNum,int value)
{
	ddlState_t searchState;
	if (DDL_MoveTo(LiveStats_GetRootDDLState(), &searchState, 2, "PlayerStatsList", "RANK"))
		SV_SetClientDIntStat(clientNum, &searchState,value);
}
void SetLevel50(int clientNum)
{
	ddlState_t searchState;
	DDL_MoveTo(LiveStats_GetRootDDLState(), &searchState, 2, "PlayerStatsList", "RANKXP");
	SV_SetClientDIntStat(clientNum, &searchState, 1260800);
	ddlState_t searchState2;
	//SV_AddModifiedStats(clientNum);
	//SV_GameSendServerCommand(clientNum,SV_CMD_RELIABLE, va("N RANKXP %d",1262500));
	//SV_GameSendServerCommand(clientNum,SV_CMD_RELIABLE, va("N RANK %d",49));
	SV_GameSendServerCommand(clientNum,SV_CMD_RELIABLE, "Q");
}

int GetClientPerk(int clientNum,int classnum,int perknum = 1)
{
	ddlState_t searchState;
	if(classnum<6)
	{
	if (DDL_MoveTo(LiveStats_GetRootDDLState(), &searchState, 3, "cacLoadouts", va("customclass%i",classnum), va("specialty%i",perknum)))
	return SV_GetClientDIntStat(clientNum, &searchState);
	}
	else
	{
	if (DDL_MoveTo(LiveStats_GetRootDDLState(), &searchState, 3, "cacLoadouts", va("prestigeclass%i",(classnum - 5)), va("specialty%i",perknum)))
		return SV_GetClientDIntStat(clientNum, &searchState);
	}
}
void SetClientPerk(int clientNum,int classnum,int perknum = 1)
{
	ddlState_t searchState;
	if(classnum<6)
	{
	DDL_MoveTo(LiveStats_GetRootDDLState(), &searchState, 3, "cacLoadouts", va("customclass%i",classnum), va("specialty%i",perknum));
	}
	else
	{
	DDL_MoveTo(LiveStats_GetRootDDLState(), &searchState, 3, "cacLoadouts", va("prestigeclass%i",(classnum - 5)), va("specialty%i",perknum));
	}
	SV_SetClientDIntStat(clientNum, &searchState,0);
}


opd_s SP1 = { 0x373488, TOC };
int(*G_Spawn)(void) = (int(*)(void))&SP1;
opd_s unlinkent = { 0x003FA588, TOC };
void(*SV_UnlinkEntity)(int Entity) = (void(*)(int))&unlinkent;
opd_s SVlinkent = { 0x3FB038, TOC };
void(*SV_linkEntity)(int Entity) = (void(*)(int))&SVlinkent;
opd_s linkent = { 0x003376C8, TOC };
void(*SP_Script_Model)(int Entity) = (void(*)(int))&linkent;
opd_s scori = { 0x337608, TOC };
void(*SP_Script_Origin)(int Entity) = (void(*)(int))&scori;
opd_s CM1 = { 0x316A00, TOC };
void(*G_SetModel)(int client,const char* model) = (void(*)(int,const char*))&CM1;

	int Spawn_Script_Model2(float posix,float posiy,float posiz,float anglepitch = 0,float angleyaw = 0,float angleroll = 0,char* model = "mp_supplydrop_ally")
	{//this sucks fix this shit 
	int ENT = G_Spawn();
	G_SetModel(ENT,model);
	SP_Script_Origin(ENT);
	SV_UnlinkEntity(ENT);
	*(float*)(ENT + 0x124) = posix;
    *(float*)(0x124 + ENT + 4)= posiy;
    *(float*)(0x124 + ENT + 8)= posiz;
	*(float*)(ENT + 0x130) = anglepitch;
    *(float*)(0x130 + ENT + 4) = angleyaw;
    *(float*)(0x130 + ENT + 8) = angleroll;
	*(int*)(ENT + 0xDF) = 0x00010004;
	*(short*)(ENT + 0x164) = script_origin;
	SV_UnlinkEntity(ENT);
	SP_Script_Origin(ENT);
	return ENT;
	}
	void Move_Model_Script_Origin(int ENT,float posix,float posiy,float posiz,float anglepitch = 0,float angleyaw = 0,float angleroll = 0)
	{
	*(float*)(ENT + 0x124) = posix;
    *(float*)(0x124 + ENT + 4)= posiy;
    *(float*)(0x124 + ENT + 8)= posiz;
	*(float*)(ENT + 0x130) = anglepitch;
    *(float*)(0x130 + ENT + 4) = angleyaw;
    *(float*)(0x130 + ENT + 8) = angleroll;
	*(int*)(ENT + 0xDF) = 0x00010004;
	SV_UnlinkEntity(ENT);
	SP_Script_Origin(ENT);
	*(int*)(ENT + 0x108) = 0;
	*(int*)(ENT + 4) = 0x11;
	*(int*)(ENT + 0xDF) = 0x00010004;
	}

void RedBoxes()
{
	if(RedBox == false)
	{
		WriteProcessMemory<uint32_t>(0x001206C8, 0x60000000, 4);
		WriteProcessMemory<uint32_t>(0x001205C0, 0x60000000, 4);
		RedBox = true;
		iPrintln_GameMessage("Red Boxes: ^2ON");
	}
	else
	{
	    WriteProcessMemory<uint32_t>(0x001205C0,  0x41860278, 4);
		RedBox = false;
		iPrintln_GameMessage("Red Boxes: ^1OFF");
	}
}

void Vision()
{
	if(*(char*)0x4566A8 == 0x40)
	{
		WriteProcessMemory<char>(0x4566A8, 0x41, 1);
		WriteProcessMemory<char>(0x465244, 0x41, 1);
		iPrintln_GameMessage("L33T Vision: ^2ON");
	}
	else
	{
	    WriteProcessMemory<char>(0x4566A8, 0x40, 1);
		WriteProcessMemory<char>(0x465244, 0x40, 1);
		iPrintln_GameMessage("L33T Vision: ^1OFF");
	}
}
void SuperForceHost()
{
	if(!ForceHost)
	{
		ForceHost = true;
		iPrintln_GameMessage("Super Force Host: ^2ON");
	}
	else
	{
		ForceHost = false;
		iPrintln_GameMessage("Super Force Host: ^1OFF");
		Cbuf_addtext("party_host 0;onlinegame 1;onlinegameandhost 0;onlineunrankedgameandhost 0;migration_msgtimeout 500;migration_timeBetween 30000;migrationPingTime 10;party_minplayers 2;party_matchedPlayerCount 4;party_connectTimeout 8000;\n");
	}
}

void BlackBird()
{
	if(*(int*)0xEBDF4 == 0x409A00C4)
	{
		WriteProcessMemory<uint32_t>(0xEBDF4, 0x419A00C4, 4);
		iPrintln_GameMessage("Black Bird: ^1OFF");
	}
	else
	{
	    WriteProcessMemory<uint32_t>(0xEBDF4, 0x409A00C4, 4);
		iPrintln_GameMessage("Black Bird: ^2ON");
	}
}

void ToggleAimbot()
{
	if(Aimbot)
	{
		Aimbot = false;
		iPrintln_GameMessage("Aimbot: ^1OFF");
	}
	else
	{
	    Aimbot = true;
		iPrintln_GameMessage("Aimbot: ^2ON");
	}
}
bool NoRecoil = false;
void doNoRecoil()
{
	if(!NoRecoil)
	{
		NoRecoil = true;
		unsigned char byte[4] = {0x60,0x00,0x00,0x00};
		sys_dbg_write_process_memory(0x19B244,byte,4);
		iPrintln_GameMessage("No Recoil: ^2ON");
	}
	else
	{
		NoRecoil = false;
		unsigned char byte[4] = {0x4B, 0xF1, 0x84, 0xCD};
		sys_dbg_write_process_memory(0x19B244,byte,4);
		iPrintln_GameMessage("No Recoil: ^1OFF");
	}
}

void WallHack()
{
	if(*(int*)0x131144 == 0xFCC0F890)
	{
		WriteProcessMemory<uint32_t>(0x131144, 0x38C0F003, sizeof(uint32_t));
		iPrintln_GameMessage("WallHack: ^2ON");
	}
	else
	{
	    WriteProcessMemory<uint32_t>(0x131144, 0xFCC0F890, sizeof(uint32_t));
		iPrintln_GameMessage("WallHack: ^1OFF");
	}
}

		
bool IsConnected(int client)
{
    if(CON_CONNECTED == *(int*)(0x13977D8 +(client * 0x2A38)))
		return true;
	else
	    return false;
}



	



void DamagePlayer(int attackerNum, int victimNum,int weapon = 0x61C) {
	if(victimNum != -1)
	{
	float null[3] = { 0, 0, 0 };
	G_Damage(0x012AB290 + (0x2F8 *victimNum), 0x012AB290 + (0x2F8 *attackerNum), 0x012AB290 + (0x2F8 *attackerNum), null, null, 0x7FFFFFFF, 0, 0x2, weapon, HITLOC_HEAD, 0, 0, 0);
	}
}

char RetErrorW[] = "none";
const char* PlayerCmd_GetCurrentWeapon(int client)
{
	if(IsPlayer(client))
	{
    scr_entref_t enteref;
    enteref.client = client;
    enteref.entnum = client;
    enteref.classnum = 0;
    ((void(*)(scr_entref_t))&ParseAddr(0x2CB958))(enteref);
	Scr_ClearOutParams();
	return SL_ConvertToString(scrVmPub->top->u.stringValue,SCRIPTINSTANCE_SERVER);
	}
	return RetErrorW;
}



int Client_t(int clientNum)

{

	return *(int*)0x169529C + (0x651C8 * clientNum);

}


void Infection1()
{
	var = 3;
    Cbuf_addtext("callvote map \"Jo-Milk\"");
}

void Infection2()
{
	var = 2;
	Cbuf_addtext("callvote map \"Jo-Milk\"");
}

void Infection3()
{
	var = 1;
	Cbuf_addtext("callvote map \"Jo-Milk\"");
}

void Infection4()
{
	var = 0;
	Cbuf_addtext("callvote map \"Jo-Milk\"");
}

void doEndGame_Non_host()
{
	Cbuf_addtext( va("cmd mr %i -1 endround",(*(int*)0xD25EF0)));
	nonhostend = false;
}
void EndGame_Non_host()
{
	nonhostend = true;
	iPrintln_GameMessage("^1Game Ended by You");
}

void doSteadyAim()
{
	if(*(int*)0xAB8EC != 0x60000000)
	{
		SteadyAim = true;
		WriteProcessMemory<uint32_t>(0xAB8EC,0x60000000,4);
		WriteProcessMemory<bool>(0xBBC2E4,0x02,1);
		sleep(20);
		iPrintln_GameMessage("Steady Aim: ^2ON");
	}
	else
	{
	    SteadyAim = false;
		WriteProcessMemory<uint32_t>(0xAB8EC,0x2F800002,4);
		WriteProcessMemory<bool>(0xBBC2E4,0x01,1);
		iPrintln_GameMessage("Steady Aim: ^1OFF");
	}
}
void AimatHead()
{
aimat = j_head;
iPrintln_GameMessage("Aiming at: ^2j_head");
}
void AimatNeck()
{
aimat = j_neck;
iPrintln_GameMessage("Aiming at: ^2j_neck");
}
void doSilentAim()
{
	if(!SilentAim)
	{
		SilentAim = true;
		iPrintln_GameMessage("Silent Aim: ^2ON");
	}
	else
	{
	    SilentAim = false;
		iPrintln_GameMessage("Silent Aim: ^1OFF");
	}
}
void doAutoWallAim()
{
	if(!autoWall)
	{
		autoWall = true;
		iPrintln_GameMessage("Auto Wall: ^2ON");
	}
	else
	{
	    autoWall = false;
		iPrintln_GameMessage("Auto Wall: ^1OFF");
	}
}
void doNoSpread()
{
	if(!NoSpread)
	{
		NoSpread = true;
		iPrintln_GameMessage("No Spread: ^2ON");
	}
	else
	{
	    NoSpread = false;
		iPrintln_GameMessage("No Spread: ^1OFF");
	}
}
void Say1()
{
	Cbuf_addtext("say \"^1H^2e^3l^4l^5o\"\n");
}
void Say2()
{
	Cbuf_addtext("say \"^2HAHA\"\n");
}
void Say3()
{
	Cbuf_addtext("say \"^1You're My Bitch Now!\"\n");
}
void Say4()
{
	Cbuf_addtext("say \"^1SHUT ^2THE ^6FUCK UP!\"\n");
}
void Say5()
{
	Cbuf_addtext("say \"^1STOP!\"\n");
}
void Say6()
{
	Cbuf_addtext("say \"^2I'm ^3not ^4hacking ^5your ^1just ^2high\"\n");
}
void Say7()
{
	Cbuf_addtext("say \"^2Subscribe ^3to ^5www^0.^1youtube^0.^5com^2/^3c^2/^1JoMilk15MoDz ^5for ^1Jo-Milk's ^6Modz\"\n");
}
void Say8()
{
	Cbuf_addtext("say \"^5Jo-Milk <3\"\n");
}
void Say9()
{
	Cbuf_addtext("say \"^5Welcome To ^2Jo-Milk^5's Playground!\"\n");
}
void Say10()
{
	Cbuf_addtext("say \"^51v1 me!\"\n");
}
