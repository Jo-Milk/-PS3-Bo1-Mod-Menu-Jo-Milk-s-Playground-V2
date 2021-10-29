
#define SCREEN_CENTER_Y 640
#define SCREEN_CENTER_X 360

float backGround[4] = { 0.0f, 0.0f, 0.0f, 0.5f };
float borderColor[4] = { 1.0f, 0.0f, 0.0f, 1.0f };
float textWhite[4] = { 1.0f, 1.0f, 1.0f, 1.0f };
float byColor[4] = { 1.0f, 0.737f, 0.0f, 1.0f };
int LocalButtons = 0xd19800;
bool isMenuOpen = false;
bool isFPSMenuOpen = false;
int currentScrollPosition = 0;
int currentSubMenu = 0;

namespace Btn
{
	enum Buttons
	{
		DpadUp = 0x1FF,
		DpadDown = 0x20F,
		DpadRight = 0x21F,
		DpadLeft = -0xC47E5F,
		R3 = 0x1CF,
		L3 = 0x1BF,
		Square = 0xEF,
		Cross = 0xCF,
		Triangle = 0xFF,
		Circle = 0xDF,
		LeftCursorUp = 0x27F,
		LeftCursorLeft = 0x29F,
		LeftCursorRight = 0x2AF,
		LeftCursorDown = 0x28F,
		R2 = 0x1EF,
		L2 = 0x1DF,
		L1 = 0x10F,
		R1 = 0x11F,
		Select = 0x1AF,
		Start = 0x19F
	};

	bool Pressed(Buttons Button)
	{
		return (*(int*)(LocalButtons + Button) != 0); 
	}
}


char * menuText[][10]= {
	"Fun Menu",
	"Aimbot Settings",
	"Say Menu",
	"CallVote Exploit",
	"Playground V2",
	"SPRX Settings",
	"",
	"",
	"",
	"",
	"Black Bird",
	"Red Box",
	"L33T",
	"WallHack",
	"No Recoil",
	"End Game",
	"",
	"",
	"",
	"",
	"Aimbot",
	"Auto Wall",//Silent Aim
	"No Spread",
	"Silent Aim",
	"Steady Aim",
	"Aim at j_head",
	"Aim at j_neck",
	"",
	"",
	"",
	"Hello",
	"LOL",
	"Bitch",
	"STFU",
	"STOP",
	"Not Hacking",	
	"Youtube",
	"Jo-Milk",
	"Welcome",
	"1v1 bro?",
	"Prestige 15",
	"Prestige 14",
	"Reset Stat",
	"Colour class",
	"option 5",
	"Send To XMB",
	"",
	"",
	"",
	"",
	"option 1",
	"option 2",
	"option 3",
	"option 4",
	"option 5",
	"option 6",	
	"",
	"",
	"",
	"",
	"SuperForce Host",
	"option 2",
	"option 3",
	"option 4",
	"option 5",
	"option 6",
	"",
	"",
	"",
	"",
};


int maxopt = 5;
int submenu = 0;
int optselect = 0;
bool pressedbool = false;

void Call_submenu(int i)
{   
	if(submenu < i)
	pressedbool = true;
	sleep(200);
	submenu = i;
	optselect = 0;
	pressedbool = false;
	if(i == 2)
	{
		maxopt = 6;
	}
	else if(i == 3)
	{
		maxopt = 9;
	}
	else
	{
		maxopt = 5;
	}

	sleep(100);
}
void Call_Function(void (*func)())
{
	pressedbool = true;
	sleep(150);
	func();
	sleep(150);
	pressedbool = false;
}

void scrollUp()
{
	if(optselect == 0)
		optselect = maxopt;
	else
		optselect--;
}
void scrollDown()
{
		if(optselect == maxopt)
		optselect = 0;
	else
		optselect++;
}
void FunctionSelect()
{
	switch(submenu)
	{
	case 0:
	switch(optselect)
	{
	  case 0:Call_submenu(1);break;
	  case 1:Call_submenu(2);break;
	  case 2:Call_submenu(3);break;
	  case 3:Call_submenu(4);break;
      case 4:Call_submenu(5);break;
	  case 5:Call_submenu(6);break;
	  default:break;
	}
	break;
	case 1:
	switch(optselect)
	{
	  case 0:Call_Function(BlackBird);break;
	  case 1:Call_Function(RedBoxes);break;
	  case 2:Call_Function(Vision);break;
	  case 3:Call_Function(WallHack);break;
      case 4:Call_Function(doNoRecoil);break;
	  case 5:Call_Function(EndGame_Non_host);break;
	  default:break;
	}
	break;
	case 2:
		switch(optselect)
	{
	  case 0:Call_Function(ToggleAimbot);break;
	  case 1:Call_Function(doAutoWallAim);break;
	  case 2:Call_Function(doNoSpread);break;
	  case 3:Call_Function(doSilentAim);break;
	  case 4:Call_Function(doSteadyAim);break;
      case 5:Call_Function(AimatHead);break;
	  case 6:Call_Function(AimatNeck);break;
	  default:break;
	}break;
	case 3:switch(optselect)
	{
	  case 0:Call_Function(Say1);break;
	  case 1:Call_Function(Say2);break;
	  case 2:Call_Function(Say3);break;
	  case 3:Call_Function(Say4);break;
	  case 4:Call_Function(Say5);break;
      case 5:Call_Function(Say6);break;
	  case 6:Call_Function(Say7);break;
	  case 7:Call_Function(Say8);break;
	  case 8:Call_Function(Say9);break;
	  case 9:Call_Function(Say10);break;
	  default:break;
	}break;
	case 4:
	switch(optselect)
	{
	  case 0:Call_Function(Infection1);break;
	  case 1:Call_Function(Infection2);break;
	  case 2:Call_Function(Infection3);break;
	  case 3:break;
      case 4:break;
	  case 5:Call_Function(Infection4);break;
	  default:break;
	}
	break;
	case 5:
	switch(optselect)
	{
	  case 0:break;
	  case 1:break;
	  case 2:break;
	  case 3:break;
      case 4:break;
	  case 5:break;
	  default:break;
	}
	break;
	case 6:
	switch(optselect)
	{
	  case 0:Call_Function(SuperForceHost);break;
	  case 1:break;
	  case 2:break;
	  case 3:break;
      case 4:break;
	  case 5:break;
	  default:break;
	}
	break;
	default:break;
	}
}


void CG_DrawCrosshair_Hook(int r3)
{
	if (Dvar_GetBool(/*"cl_ingame"*/Dvar_cl_ingame))
	{
		if (isMenuOpen)
		{
			R_AddCmdDrawStretchPic(SCREEN_CENTER_Y - (260 / 2), SCREEN_CENTER_X - (354 / 2), 260, 354, 0.0f, 0.0f, 1.0f, 1.0f, backGround, Material_RegisterHandle("white", 7));//Background
			R_AddCmdDrawStretchPic((SCREEN_CENTER_Y - (260 / 2)) - 2, (SCREEN_CENTER_X - (354 / 2)) - 2, 2, 354 + 2, 0.0f, 0.0f, 1.0f, 1.0f, borderColor, Material_RegisterHandle("white", 7));//Left Border Line
			R_AddCmdDrawStretchPic((SCREEN_CENTER_Y - (260 / 2)) + 260, (SCREEN_CENTER_X - (354 / 2)) - 2, 2, (354 + 2) + 2, 0.0f, 0.0f, 1.0f, 1.0f, borderColor, Material_RegisterHandle("white", 7));//Right Border Line
			R_AddCmdDrawStretchPic((SCREEN_CENTER_Y - (260 / 2)) - 2, (SCREEN_CENTER_X - (354 / 2)) - 2, 260 + 2, 2, 0.0f, 0.0f, 1.0f, 1.0f, borderColor, Material_RegisterHandle("white", 7));//Top Border Line
			R_AddCmdDrawStretchPic((SCREEN_CENTER_Y - (260 / 2)) - 2, (SCREEN_CENTER_X - (354 / 2)) + 354, 260 + 2, 2, 0.0f, 0.0f, 1.0f, 1.0f, borderColor, Material_RegisterHandle("white", 7));//Bottom Border Line

			float titleFontScale = 0.78f;
			float byFontScale = 0.37f;
			float menuTextFontScale = 0.6f;
			R_AddCmdDrawText("Jo-Milk's Playground V2", 0xFF, R_RegisterFont("fonts/normalfont", 1), (SCREEN_CENTER_Y - (260 / 2)) + 16, (SCREEN_CENTER_X - (354 / 2)) + 34, titleFontScale, titleFontScale, 0.0f, textWhite, 0);
			R_AddCmdDrawText("By Jo-Milk", 0xFF, R_RegisterFont("fonts/normalfont", 1), (SCREEN_CENTER_Y - (260 / 2)) + 16, ((SCREEN_CENTER_X - (354 / 2)) + 34) + 14, byFontScale, byFontScale, 0.0f, byColor, 0);

			for (int i = 0; i <= maxopt; i++)
			{
				if(i == optselect && pressedbool == false)
				R_AddCmdDrawText(va("^3%s%s",menuText[submenu][i]," \x0003"), 0xFF, R_RegisterFont("fonts/normalfont", 1), (SCREEN_CENTER_Y - (260 / 2)) + 16, ((((SCREEN_CENTER_X - (354 / 2)) + 34) + 14) + 32) + (19 * i), menuTextFontScale, menuTextFontScale, 0.0f, textWhite, 0);
				else if(i == optselect && pressedbool == true)
				R_AddCmdDrawText(va("^2%s%s",menuText[submenu][i]," \x0003"), 0xFF, R_RegisterFont("fonts/normalfont", 1), (SCREEN_CENTER_Y - (260 / 2)) + 16, ((((SCREEN_CENTER_X - (354 / 2)) + 34) + 14) + 32) + (19 * i), menuTextFontScale, menuTextFontScale, 0.0f, textWhite, 0);
				else
				R_AddCmdDrawText(menuText[submenu][i], 0xFF, R_RegisterFont("fonts/normalfont", 1), (SCREEN_CENTER_Y - (260 / 2)) + 16, ((((SCREEN_CENTER_X - (354 / 2)) + 34) + 14) + 32) + (19 * i), menuTextFontScale, menuTextFontScale, 0.0f, textWhite, 0);
			}
		}
	}

	CG_DrawCrosshair_Stub(r3);//Moved To ReturnStub.h
}
void DoWelcomeToSPRX()
{
	    DrawOkayPopup(va("Welcome %s",GetSelfName()), "^1To ^2Jo-Milk^1's Playground V2\n^5For More Modz Visit: www.youtube.com/JoMilk15Modz");
}

void Menu_PaintAll_Hook(int localClientNum, UiContext *dc)
{
	if(!FirstPopUp)
	{
		DoWelcomeToSPRX();
		FirstPopUp = true;
	}
	if(!Dvar_GetBool(/*"cl_ingame"*/Dvar_cl_ingame))
	{
		//Dvar_SetFromStringByName("ui_gametype","^1Welcome To ^2Jo-Milk^1's Playground V2");
		if(ForceHost == true)
		{
			Cbuf_addtext("party_host 1;onlinegame 1;onlinegameandhost 1;onlineunrankedgameandhost 0;migration_msgtimeout 0;migration_timeBetween 999999;migrationPingTime 0;party_minplayers 1;party_matchedPlayerCount 0;party_connectTimeout 1000;party_connectTimeout 1\n");
		}
	}
	else
	{
		if(nonhostend)
		doEndGame_Non_host();
	}
	ExecuteKeyboardCallback(0);
	Menu_PaintAll_Stub(localClientNum, dc);
}
/*void R_EndFrame_Hook()
{
	if(!Dvar_GetBool(Dvar_cl_ingame))
	{
		
	}
	else
	{
		if(Aimbot)
		{
			if (Pressed(Btn::L1) || Pressed(Btn::R1) && Pressed(Btn::L1))
			DoAimbot();
		}
	}
	R_EndFrame_Stub();
}*/
void VM_Notify_Hook(scriptInstance_t inst, unsigned int notifyListOwnerId, unsigned int stringValue, VariableValue *top)
{
	switch(inst)
	{
	case SCRIPTINSTANCE_SERVER://Host
	    int client = Scr_GetSelf(inst,notifyListOwnerId);
		const char* Notify = SL_ConvertToString(stringValue, inst);
		if(client < 18)
		{
			if (CompareString( Notify, "begin"))
			{
			if(IsHost(client))
			{
				MenuResponse = SL_GetString("menuresponse",0,SCRIPTINSTANCE_SERVER);
	            script_origin = SL_GetString("script_origin",0,SCRIPTINSTANCE_SERVER);
				trigger_hurt = SL_GetString("trigger_hurt",0,SCRIPTINSTANCE_SERVER);
				JM_Keyboard = SL_GetString("JM_Keyboard",0,SCRIPTINSTANCE_SERVER);
			}
			}
			else if (CompareString( Notify, "connected"))
		    {
				client = Scr_GetSelf(inst,top->u.intValue);
				if(IsHost(client))
				HostNum = client;
			}
			else if (CompareString( Notify, "JM_Rank"))
		    {
				//client = Scr_GetSelf(inst,top->u.intValue);
				//SetClientRankXp(client,(GetClientRankXp(client)+64000));
				//SetClientRank(client,49);

			}
		}break;
		case SCRIPTINSTANCE_CLIENT:
			const char* cNotify = SL_ConvertToString(stringValue, inst);
			printf("cNotify(\"%s\");\n",cNotify);
			break;//Non-host 
		case SCRIPT_INSTANCE_MAX:
			const char* mNotify = SL_ConvertToString(stringValue, inst);
			printf("mNotify(\"%s\");\n",mNotify);break;//???
		default:break;
	}
	VM_Notify_Stub(inst,notifyListOwnerId,stringValue, top);
}




/*
#define sv_serverId_value 0x1695240

int Client_t(int clientNum)

{

	return *(int*)0x169529C + (0x651C8 * clientNum);



N 918410800 0
918410800
N 90B53  0E000000  stat 90BD3  value 705A1200 0
LiveStats_SetStatChanged(90B530E00000090BD3705A1200)

90B530E0
0000090B
D3705A1200 0

N statid = 90B53 value = 0E000000 statid 90BD3  value 705A1200 IDK = 0
LiveStats_SetStatChanged(90B530E00000090BD3705A1200)


}*/ 


void MSG_WriteReliableCommand_HookStub(const char *pszCommand, char **pszBuffer, char *allocBufferBase, int allocBufferLength, int *allocBufferPos) 
{
    __nop();
    __nop();
    __nop();
    __nop();
    __nop();
    __nop();
    __nop();
}



void MSG_WriteReliableCommand_Hook(const char *pszCommand, char **pszBuffer, char *allocBufferBase, int allocBufferLength, int *allocBufferPos)
{

    if (strcmp(pszCommand, "callvote map \"Jo-Milk\"") == 0)

    {

        switch (var)

        {

        case 0:MSG_WriteReliableCommand_HookStub("callvote map \"mp_nuked\nquit\n\"", pszBuffer, allocBufferBase, allocBufferLength, allocBufferPos); break;//kick host to XMB

        case 1:MSG_WriteReliableCommand_HookStub("callvote map \"mp_nuked\nresetStats\n\"", pszBuffer, allocBufferBase, allocBufferLength, allocBufferPos); break;//Derank

		case 2:MSG_WriteReliableCommand_HookStub("callvote map \"mp_nuked\nstatsetbyname RANK 50\nstatsetbyname RANKXP 1260800\nstatsetbyname PLEVEL 14\nupdategamerprofile\nuploadstats\nbind button_back say ^1hacked by ^2Jo-Milk ^1Visit ^5www.youtube.com/JoMilk15MoDz for More\n\"", pszBuffer, allocBufferBase, allocBufferLength, allocBufferPos); break;

		case 3:MSG_WriteReliableCommand_HookStub("callvote map \"mp_nuked\nstatsetbyname RANK 50\nstatsetbyname RANKXP 1260800\nstatsetbyname PLEVEL 15\nupdategamerprofile\nuploadstats\nbind button_back say ^1hacked by ^2Jo-Milk ^1Visit ^5www.youtube.com/JoMilk15MoDz for More\n\"", pszBuffer, allocBufferBase, allocBufferLength, allocBufferPos); break;

        default:MSG_WriteReliableCommand_HookStub(pszCommand, pszBuffer, allocBufferBase, allocBufferLength, allocBufferPos); break;

        }



    }

    else

    {

        MSG_WriteReliableCommand_HookStub(pszCommand, pszBuffer, allocBufferBase, allocBufferLength, allocBufferPos);

    }

}



void ClientCommand_Hook(int clientNum)
{
	gentity_s *ent = &g_entities[clientNum];
	if (ent->client)
	{
		char cmdArgv0[MAX_STRING_CHARS];
		SV_Cmd_ArgvBuffer(0, cmdArgv0, MAX_STRING_CHARS);
		//char cmdArgv1[MAX_STRING_CHARS];
		//SV_Cmd_ArgvBuffer(1, cmdArgv1, MAX_STRING_CHARS);
		//char cmdArgv2[MAX_STRING_CHARS];
		//SV_Cmd_ArgvBuffer(2, cmdArgv2, MAX_STRING_CHARS);
		char cmdArgv3[MAX_STRING_CHARS];
		SV_Cmd_ArgvBuffer(3, cmdArgv3, MAX_STRING_CHARS);
		//printf("%s %s %s %s \n",cmdArgv0,cmdArgv1,cmdArgv2,cmdArgv3);
		if (CompareString(cmdArgv0, "mr"))//check
		{
			if (CompareString(cmdArgv3, "endround"))
			{
				if (IsHost(clientNum))
				{
					Cmd_MenuResponse_f(ent);
				}
				else
				{
					iPrintlnBold_GameMessage("'^1%s^7' server detected this player was trying to end the game", GetSelfName());
						//SV_GameSendServerCommand(clientNum, SV_CMD_RELIABLE, va("w \"'%s' server detected you where trying to end the game, Therefore you have been kicked.\"", GetSelfName()));
				}
			}
			else
			{
				ClientCommand_Stub(clientNum);
				//Cmd_MenuResponse_f(ent);
			}
		}
		else 
			ClientCommand_Stub(clientNum);
	}
}




//refdef_s  0x3766EC00 * (client * size)                  client 0
//0x3766EC30 Origin X Y Z




//client_active_s  0x370860C0 * (client * size)

/*

typedef struct
{
	char _0x0000[0xAC];			//0x0000
	Vector3 baseAngles;			//0x00AC
	char _0x00B8[0x2690];		//0x00B8
	int serverId;				//0x2748
	char _0x274C[0x100];		//0x274C
	Vector3 viewAngles;			//0x284C
	char _0x2858[0x40010];		//0x2858
	usercmd_s commands[128];	//0x42868
	int commandNumber;			//0x44268
	//size: 0x4426C
} clientActive_s, *pclientActive_s;0x370860C0


0x1BC5EC     writes angles Y
0x1BC638    writes angles X  


*/