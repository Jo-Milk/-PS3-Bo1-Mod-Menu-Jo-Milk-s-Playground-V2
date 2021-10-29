#define TOC	0xB576E8

#include "printf.h"
#include <np.h>

#include <sys/prx.h>
#include <sys/socket.h>
#include <sysutil/sysutil_userinfo.h>
#include <stdarg.h>
#include <limits.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <stdint.h>
#include <math.h>

#include <sys/process.h>
#include <sys/ppu_thread.h>
#include <sys/syscall.h>

#include <sysutil/sysutil_msgdialog.h>
#include <sysutil/sysutil_oskdialog.h>
#include <sysutil/sysutil_userinfo.h>

#include <cell/fs/cell_fs_file_api.h>
#include <cell/spurs/lfqueue.h>
#include <cell/error.h>
#include <sys/memory.h>
#include <sys/timer.h>

#include "Variables.h"
#include "Hook_Stub.h"
#include "PS3.h"
#include "Functions.h"
#include "hooks.h"
#include "Aimbot.h"
#include "GSC_Script.h"
#include "gsc.h"



SYS_MODULE_INFO( JM_Play_V2, 0, 1, 1);
SYS_MODULE_START( _JM_Play_V2_prx_entry );

SYS_LIB_DECLARE_WITH_STUB( LIBNAME, SYS_LIB_AUTO_EXPORT, STUBNAME );
SYS_LIB_EXPORT( _JM_Play_V2_export_function, LIBNAME );

// An exported function is needed to generate the project's PRX stub export library
extern "C" int _JM_Play_V2_export_function(void)
{
    return CELL_OK;
}
void MyHooks()
{
    HookFunctionStart(0x465368, *(uint32_t*)Menu_PaintAll_Hook, *(uint32_t*)Menu_PaintAll_Stub);
	HookFunctionStart(0x1B74F4, *(uint32_t*)CL_WritePacket_Hook, *(uint32_t*)CL_WritePacket_Stub);
	//HookFunction(0x2D6140, *(uint32_t*)ClientCommand_Hook);
	HookFunctionStart(0x2D6140, *(uint32_t*)ClientCommand_Hook, *(uint32_t*)ClientCommand_Stub);
	HookFunctionStart(0x16B7C8, *(uint32_t*)CG_ProcessSnapshots_hook, *(uint32_t*)CG_ProcessSnapshots_Stub);
}

void launcher(uint64_t)
{
	sys_prx_get_module_list_t pInfo;
    pInfo.max = 25;
    sys_prx_id_t ids[pInfo.max];
    pInfo.idlist = ids;
    pInfo.size = sizeof(pInfo);

    while (pInfo.count < 18)
    {
        sys_prx_get_module_list(0, &pInfo);
        sleep(10);
    }
    if (init_game() == 0 )
    {
	MyHooks();
	for(;;)
	{
		 if (Dvar_GetBool(/*"cl_ingame"*/Dvar_cl_ingame))
		{
			if(!LookforFFA)
			{
				isFFA = isFFAType();
				LookforFFA = true;
			}
			if(isFPSMenuOpen)
				 isFPSMenuOpen = false;
			if (!isMenuOpen)
			{
				if(Aimbot)
	            {
	                if (Pressed(Btn::L1) || Pressed(Btn::R1) && Pressed(Btn::L1))
	                {
						if(AImbotSetAngle == 1)
						{
							if(centity[target].pos.trBase != centity[target].NewOrigin)
	                        {
	                         ApplyPrediction(them, target, (float)0.20f);
	                        }
	                        vec3_t vecangles = (them - self);
                            vectoangles((float*)&vecangles);
	                        Angles.x = (angleseeeee[0] - clientActive->deltaAngles.x);
	                        Angles.y = (angleseeeee[1] - clientActive->deltaAngles.y);
	                        Angles.z = 0;
					        CL_SetViewAngles(0,(float*)&Angles);
						    AImbotSetAngle = 2;
							sleep(250);
						}
				    }	
				}
				if (Pressed(Btn::DpadUp) && Pressed(Btn::L1))
				{
					isMenuOpen = true;
					sleep(300);
				}
			}
			else
			{
				if (Pressed(Btn::R1))
				{
					scrollDown();
					sleep(300);
				}
				else if (Pressed(Btn::L1))
				{
					scrollUp();
					sleep(300);
				}
				else if (Pressed(Btn::Square))
				{
					FunctionSelect();
				}
				else if(Pressed(Btn::Circle))
				{
					if(!submenu)
					{
					isMenuOpen = false;
					sleep(300);
					}
					else
						Call_submenu(0);
				}
			}
		}
		else
		{
			 LookforFFA = false;
			 Aimbot = false;
			 if(isMenuOpen)
				 isMenuOpen = false;
			 if (!isFPSMenuOpen)
			 {
				if (Pressed(Btn::L2))
				{
					isFPSMenuOpen = true;
					sleep(300);
				}
			 }
			 else
			 {
				if (Pressed(Btn::Circle))
				{
					isFPSMenuOpen = false;
					sleep(300);
				}
			 }

		}
		sleep(10);
	}
	}
	else
    sys_ppu_thread_exit(0);
}

void RemoveThreadIDCheckOnCL_ConsolePrint()//allows iPrintln_GameMessage and iPrintlnBold_GameMessage by noping Com_GetParseThreadInfo in 0x001AF228 CL_ConsolePrint
{
    uint32_t PPC[] = { 0x60000000 };
	for (int i = 0; i < 0x4; i++)
		sys_dbg_write_process_memory(0x1AF264 + (i * 4), &PPC[0], 4);
}
void RSATEST()
{
    uint32_t PPC[] = { 0x60000000 };
	sys_dbg_write_process_memory(0x230258, &PPC[0], 4);
    sys_dbg_write_process_memory(0x23025C, &PPC[0], 4);
    sys_dbg_write_process_memory(0x230260, &PPC[0], 4);
	sys_dbg_write_process_memory(0x230264, &PPC[0], 4);
	sys_dbg_write_process_memory(0x230268, &PPC[0], 4);
}
void RemoveCheatProtection()//can use some cheat protected dvars 
{
	uint32_t PPC[] = { 0x60000000, 0x3B200000 };
	sys_dbg_write_process_memory(0x4C8EC4, &PPC[0], 4);
	sys_dbg_write_process_memory(0x4C8ED0, &PPC[0], 4);
	sys_dbg_write_process_memory(0x4C8ED4, &PPC[1], 4);
	
	//TEST
	sys_dbg_write_process_memory(0x3E013C, &PPC[0], 4);
}


sys_ppu_thread_t id;
extern "C" int _JM_Play_V2_prx_entry(void)
{
	aimat = j_neck;
	//HookFunctionStart(0x7548A8  /*0x1B74F0*/, *(uint32_t*)R_EndFrame_Hook, *(uint32_t*)R_EndFrame_Stub);//last adding thing 1B74F0 CL_WritePacket
	HookFunctionStart(0xF8160, *(uint32_t*)CG_DrawCrosshair_Hook, *(uint32_t*)CG_DrawCrosshair_Stub);
	HookFunctionStart(0x3CCAF8, *(uint32_t*)MSG_WriteReliableCommand_Hook, *(uint32_t*)MSG_WriteReliableCommand_HookStub);
	RSATEST();
	RemoveThreadIDCheckOnCL_ConsolePrint();//by Jo-Milk 2020-01-10 added to NonHost.h
	RemoveCheatProtection();//by Jo-Milk 2020-01-10 added to NonHost.h
    sys_ppu_thread_create(&id, launcher, 0, 100, 0x64, 0, "Jo-Milk");
    return SYS_PRX_RESIDENT;
}
/*
439C

Start       0x029002C0


Attribute   Value
Address     0x28F0000

begining 0x28FB4FC
*/


//iMCSx
