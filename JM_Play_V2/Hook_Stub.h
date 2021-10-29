

int Scr_LoadScript_Trampoline(scriptInstance_t inst, const char *scriptName)
{
	__nop();
	__nop();
	__nop();
	__nop();
	__nop();
	__nop();
	__nop();
}

int cellSpursLFQueuePushBody_Trampoline(CellSpursLFQueue *lfqueue, const void *buffer, unsigned int isBlocking)
{
	__nop();
	__nop();
	__nop();
	__nop();
	__nop();
	__nop();
	__nop();
}

void Scr_GetChecksum_Trampoline(scrChecksum_t *checksum, scriptInstance_t inst)
{
	__nop();
	__nop();
	__nop();
	__nop();
	__nop();
	__nop();
	__nop();
}


void Scr_LoadGameType_Trampoline()
{
	__nop();
	__nop();
	__nop();
	__nop();
	__nop();
	__nop();
	__nop();
}
void CScr_LoadLevel_Trampoline()
{
	__nop();
	__nop();
	__nop();
	__nop();
	__nop();
	__nop();
	__nop();
}


popd32 Scr_GetFunction_Trampoline(const char **pName, int *type)
{
	__nop();
	__nop();
	__nop();
	__nop();
	__nop();
	__nop();
	__nop();
}
popd32 CScr_GetFunction_Trampoline(const char **pName, int *type)
{
	__nop();
	__nop();
	__nop();
	__nop();
	__nop();
	__nop();
	__nop();
}
int CG_ProcessSnapshots_Stub(int localClientNum) 
{
	__nop();
	__nop();
	__nop();
	__nop();
	__nop();
	__nop();
	__nop();
}
void CG_DrawCrosshair_Stub(int r3)
{
	__nop();
	__nop();
	__nop();
	__nop();
	__nop();
	__nop();
	__nop();
}
void VM_Notify_Stub(scriptInstance_t inst, unsigned int notifyListOwnerId, unsigned int stringValue, VariableValue *top)
{
	__nop();
	__nop();
	__nop();
	__nop();
	__nop();
	__nop();
	__nop();
}

void Menu_PaintAll_Stub(int localClientNum, UiContext *dc)
{
	__nop();
	__nop();
	__nop();
	__nop();
	__nop();
	__nop();
	__nop();
}


void LiveStats_SetStatChanged_Stub(const int controllerIndex, const char *hexMsg)
{
	__nop();
	__nop();
	__nop();
	__nop();
	__nop();
	__nop();
	__nop();
}

void SV_AddServerCommand_Stub(int clientadd, int type, const char *cmd)
{
	__nop();
	__nop();
	__nop();
	__nop();
	__nop();
	__nop();
	__nop();
}
int CL_WritePacket_Stub(int r3)
{
	__nop();
	__nop();
	__nop();
	__nop();
	__nop();
	__nop();
	__nop();
}

void ClientCommand_Stub(int r3)
{
	__nop();
	__nop();
	__nop();
	__nop();
	__nop();
	__nop();
	__nop();
}
/*
class cTracer
{
    public:
        float hit3D[3];
        float start3D[3];
};

char CG_BulletHitEvent_stub(int localClientNum, int sourceEntityNum, int targetEntityNum, int weapon, const float *startPos, const float *position, const float *normal, const float *seeThruDecalNormal, int surfType, int event_JM, int eventParam, int damage, int hitContents, char boneIndex)
{
	
}


opd_s CG_DObjGetWorldTagPos_t = { 0x0FD7F0, TOC };
int(*CG_DObjGetWorldTagPos)(int pose, int obj, unsigned int tagName, float *pos) = (int(*)(int pose, int obj, unsigned int , float))&CG_DObjGetWorldTagPos_t;

opd_s Com_GetClientDObj_t = { 0x0FD7F0, TOC };
int(*Com_GetClientDObj)(int handle, int localClientNum) = (int(*)(int handle, int localClientNum))&Com_GetClientDObj_t;

bool tester = true;
//void CG_BulletHitEvent(int localClientNum, int sourceEntityNum, int targetEntityNum, int weaponIndex, const float *startPos, const float *position, const float *normal, const float *seeThruDecalNormal, int surfType, int event, char eventParam, int damage, int hitContents, char boneIndex);



opd_s CG_SpawnTracer_t = { 0x16CFE8, TOC };
void(*CG_SpawnTracer)(int localClientNum, const float *pstart, const float *pend, int type, float width, float length) = (void(*)(int localClientNum, const float *pstart, const float *pend, int type, float width, float length))&CG_SpawnTracer_t;

char CG_BulletHitEvent_hook(int localClientNum, int sourceEntityNum, int targetEntityNum, int weapon, const float *startPos, const float *position, const float *normal, const float *seeThruDecalNormal, int surfType, int event_JM, int eventParam, int damage, int hitContents, char boneIndex)
{
	char ret = CG_BulletHitEvent_stub(localClientNum, sourceEntityNum, targetEntityNum, weapon, startPos, position, normal, seeThruDecalNormal, surfType, event_JM, eventParam, damage, hitContents, boneIndex);
 
	if (tester)
	{
		if (sourceEntityNum == cg->clientNum && targetEntityNum < 18 && boneIndex >= 0) //Some filtering, can be adjusted for different results
		{
            cTracer tracer = cTracer();
            CG_DObjGetWorldTagPos((0xC3DFC0 + (sourceEntityNum * 0x31C)),SL_GetString("tag_flash",0,SCRIPTINSTANCE_CLIENT), Com_GetClientDObj(0xC3DFC0 + 0x1DC + (sourceEntityNum * 0x31C),0xC3DFC0 + (sourceEntityNum * 0x31C)), tracer.start3D); //Passed startPos appears to be incorrect or in a different parameter, ty @VVLNT for the tag name
            tracer.hit3D[0] = position[0];
			tracer.hit3D[1] = position[1];
			tracer.hit3D[2] = position[2];
            CG_SpawnTracer(localClientNum,tracer.start3D,tracer.hit3D,0,9,999);
		}
	}
 
	return ret;
}

//ClActive = *(int*)0xD223C4
*/