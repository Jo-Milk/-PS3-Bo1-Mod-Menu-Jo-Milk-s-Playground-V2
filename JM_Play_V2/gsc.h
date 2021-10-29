void set_empty_deflated_data(char *buffer)
{
    int op[7];
    op[0] = 0x789C05B0;
    op[1] = 0xB1110000;
    op[2] = 0x04C48CC3;
    op[3] = 0x6869543A;
    op[4] = 0xF7BBE758;
    op[5] = 0xAEE75302;
    op[6] = 0x109802FE;
    sys_dbg_write_process_memory((uintptr_t)buffer, &op, 7 * 4);
}

GSCLoaderRawfile *get_loader_rawfile_from_deflated_buffer(char *deflatedBuffer)
{
    for (int i = 0; i < MAX_GSC_COUNT; i++)
    {
        if ((uintptr_t)deflatedBuffer == (uintptr_t)(loader.rawFiles[i].data.buffer + 2))
            return &loader.rawFiles[i];
    }
    return NULL;
}

void get_or_create_mod_path(char *path)
{
    int fd;
    CellFsErrno err;
    char pathMods[CELL_FS_MAX_FS_PATH_LENGTH] = "/dev_hdd0/tmp/Jo-Milk/mp";
    // Check scripts folder existing and create it if necessary
    err = cellFsMkdir(SCRIPTS_PATH, CELL_FS_DEFAULT_CREATE_MODE_1);
    if (err != CELL_FS_SUCCEEDED && err != CELL_FS_EEXIST)
    {
        printf("Cannot create the path '%s' (0x%08X).\n", SCRIPTS_PATH, err);
        return;
    }

    err = cellFsOpendir("/dev_hdd0/tmp/Jo-Milk/mp", &fd);
    if (err != CELL_FS_SUCCEEDED)
    {
        cellFsClosedir(fd);
        printf("Cannot open 'scripts' directory (0x%08X).\n", err);
        return;
    }

    uint64_t read;
    CellFsDirent ent;
    read = sizeof(CellFsDirent);
    while (!cellFsReaddir(fd, &ent, &read))
    {
        if (!read)
            break;

        if (strstr(ent.d_name, ".mod"))
        {
            strcpy(loader.currentModName, ent.d_name);
            sprintf(path, "/dev_hdd0/tmp/Jo-Milk/mp/%s", ent.d_name);
            path[strlen(path) - 4] = 0;
        }
    }

    cellFsClosedir(fd);
}


bool create_assets_from_scripts1(char *path)
{
    int fd;
    CellFsErrno err = cellFsOpendir(path, &fd);
    if (err != CELL_FS_SUCCEEDED)
    {
        cellFsClosedir(fd);
        printf("Cannot open '%s' directory (0x%08X).\n", path, err);
    }

    uint64_t read;
    CellFsDirent ent;
    read = sizeof(CellFsDirent);
    int assetIndex = 0;
    bool mainLinked = false;

    while (!cellFsReaddir(fd, &ent, &read) && assetIndex < MAX_GSC_COUNT)
    {
        if (!read)
            break;
        if(strstr(ent.d_name, ".csc") != NULL)
		{
			printf("Creating a new asset entry for '%s'.\n", ent.d_name);

			loader.rawFiles[assetIndex].asset.name = (char*)&loader.rawFiles[assetIndex].data.name;
            loader.rawFiles[assetIndex].asset.buffer = (char*)&loader.rawFiles[assetIndex].data.inflatedSize;
            loader.rawFiles[assetIndex].asset.len = 0xDEAD;

            set_empty_deflated_data(loader.rawFiles[assetIndex].data.buffer);

            sprintf(loader.rawFiles[assetIndex].data.name, "clientscripts/mp/mod/%s", ent.d_name);

            char filePath[CELL_FS_MAX_FS_PATH_LENGTH];
            sprintf(filePath, "%s/%s", path, ent.d_name);
            int fileSize = get_file_size(filePath);

            loader.rawFiles[assetIndex].data.inflatedSize = fileSize + 1;
            loader.rawFiles[assetIndex].data.size = 0x1B;
            loader.rawFiles[assetIndex].entry.asset.type = ASSET_TYPE_RAWFILE;
            loader.rawFiles[assetIndex].entry.asset.header.rawFile = &loader.rawFiles[assetIndex].asset;

            XAssetEntryPoolEntry *entry = 0;
            XAssetHeader header;

            DB_FindXAssetHeader(&header, ASSET_TYPE_RAWFILE, loader.rawFiles[assetIndex].asset.name, true, -1);
            
            if (header.rawFile != &loader.rawFiles[assetIndex].asset)
            {
                entry = DB_LinkXAssetEntry(&loader.rawFiles[assetIndex].entry, 0);
                if (!entry)
                {
                    printf("Linking asset '%s' failed.\n", loader.rawFiles[assetIndex].asset.name);
                    continue;
                }
                if (strcmp(ent.d_name, "main.csc") == 0)
                    mainLinked = true;

                assetIndex++;
            }
		}
    }
    cellFsClosedir(fd);

    return mainLinked && (assetIndex > 0);
}
bool create_assets_from_scripts2(char *path)
{
    int fd;
    CellFsErrno err = cellFsOpendir(path, &fd);
    if (err != CELL_FS_SUCCEEDED)
    {
        cellFsClosedir(fd);
        printf("Cannot open '%s' directory (0x%08X).\n", path, err);
    }

    uint64_t read;
    CellFsDirent ent;
    read = sizeof(CellFsDirent);
    int assetIndex = 0;
    bool mainLinked = false;

    while (!cellFsReaddir(fd, &ent, &read) && assetIndex < MAX_GSC_COUNT)
    {
        if (!read)
            break;

        if (strstr(ent.d_name, ".gsc") != NULL)
        {
            printf("Creating a new asset entry for '%s'.\n", ent.d_name);

            loader.rawFiles[assetIndex].asset.name = (char*)&loader.rawFiles[assetIndex].data.name;
            loader.rawFiles[assetIndex].asset.buffer = (char*)&loader.rawFiles[assetIndex].data.inflatedSize;
            loader.rawFiles[assetIndex].asset.len = 0xDEAD;

            set_empty_deflated_data(loader.rawFiles[assetIndex].data.buffer);

            sprintf(loader.rawFiles[assetIndex].data.name, "maps/mp/mod/%s", ent.d_name);

            char filePath[CELL_FS_MAX_FS_PATH_LENGTH];
            sprintf(filePath, "%s/%s", path, ent.d_name);
            int fileSize = get_file_size(filePath);

            loader.rawFiles[assetIndex].data.inflatedSize = fileSize + 1;
            loader.rawFiles[assetIndex].data.size = 0x1B;
            loader.rawFiles[assetIndex].entry.asset.type = ASSET_TYPE_RAWFILE;
            loader.rawFiles[assetIndex].entry.asset.header.rawFile = &loader.rawFiles[assetIndex].asset;

            XAssetEntryPoolEntry *entry = 0;
            XAssetHeader header;

            DB_FindXAssetHeader(&header, ASSET_TYPE_RAWFILE, loader.rawFiles[assetIndex].asset.name, true, -1);
            
            if (header.rawFile != &loader.rawFiles[assetIndex].asset)
            {
                entry = DB_LinkXAssetEntry(&loader.rawFiles[assetIndex].entry, 0);
                if (!entry)
                {
                    printf("Linking asset '%s' failed.\n", loader.rawFiles[assetIndex].asset.name);
                    continue;
                }
                if (strcmp(ent.d_name, "main.gsc") == 0)
                    mainLinked = true;

                assetIndex++;
            }
        }
    }
    cellFsClosedir(fd);

    return mainLinked && (assetIndex > 0);
}

int Scr_LoadScript_Hook(scriptInstance_t inst, const char *scriptName)
{
    int res = Scr_LoadScript_Trampoline(inst, scriptName);//is the stub
	char buffer[255];
    dvar_s *mapname = Dvar_FindVar("mapname");

    if (!mapname)
    {
        //printf("Dvar mapname not found.");
        return res;
    }
    // The game will load some script on boot (ZM), avoid it.
    if (strcmp(mapname->current.string, "frontend") == 0)
    {
        return res;
    }
	if(inst == SCRIPTINSTANCE_CLIENT)
	{
		sprintf(buffer, "clientscripts/mp/%s" , mapname->current.string);
		if(strcmp(scriptName, buffer) == 0)
		{
		checksums[inst].checksum = scrVarPub[inst].checksum;
        checksums[inst].programLen = scrCompilePub[inst].programLen;
        checksums[inst].substract = (int)scrVarPub[inst].endScriptBuffer - (int)scrVarPub[inst].programBuffer;
		// Clean all previous values.
        memset(loader.rawFiles, 0, sizeof(loader.rawFiles));

        // Get active mod.
        char modPath[CELL_FS_MAX_FS_PATH_LENGTH];
        get_or_create_mod_path(modPath);
		if (*modPath)
        {
            // Create asset entry for each file in our mod directory.
            if (create_assets_from_scripts1(modPath))
            {
                // Load the main file, any gsc used as include inside will be loaded too.
                char *mainMod = "clientscripts/mp/mod/main";
                Scr_LoadScript_Trampoline(inst, mainMod);

                // Get our main function handle to start it later in another hook.
                modHandlecsc = Scr_GetFunctionHandle(SCRIPTINSTANCE_CLIENT, mainMod, "main");
                printf("Main function handle of '%s' is 0x%08X.\n", mainMod, modHandlecsc);
            }
            else
			{
				__nop();
                printf("Couldn't load mod files from '%s'.\n", modPath);
			}
        }
		}
	}
	else
	{
    sprintf(buffer, "maps/mp/%s" , mapname->current.string);

    // Checking the current gsc loaded was the one for the current map.
    if (strcmp(scriptName, buffer) == 0)
    {

        // We can safely now save the checksum data, we will return this one later in a different hook once we loaded our scripts.
        checksums[inst].checksum = scrVarPub[inst].checksum;
        checksums[inst].programLen = scrCompilePub[inst].programLen;
        checksums[inst].substract = (int)scrVarPub[inst].endScriptBuffer - (int)scrVarPub[inst].programBuffer;

        // Clean all previous values.
        memset(loader.rawFiles, 0, sizeof(loader.rawFiles));

        // Get active mod.
        char modPath[CELL_FS_MAX_FS_PATH_LENGTH];
        get_or_create_mod_path(modPath);

        if (*modPath)
        {
            // Create asset entry for each file in our mod directory.
            if (create_assets_from_scripts2(modPath))
            {
                // Load the main file, any gsc used as include inside will be loaded too.
                char *mainMod = "maps/mp/mod/main";
                Scr_LoadScript_Trampoline(inst, mainMod);

                // Get our main function handle to start it later in another hook.
                modHandle = Scr_GetFunctionHandle(SCRIPTINSTANCE_SERVER, mainMod, "main");
                printf("Main function handle of '%s' is 0x%08X.\n", mainMod, modHandle);
            }
            else
			{
				__nop();
                //printf("Couldn't load mod files from '%s'.\n", modPath);
			}
        }
        else
		{
			__nop();
            //printf("Nothing to load.");
		}
    }
	}
    return res;
}


int cellSpursLFQueuePushBody_Hook(CellSpursLFQueue *lfqueue, const void *buffer, unsigned int isBlocking)
{
    // Hooked by replacing popd import because using CTR an instruction of the source function will overwrite toc in stack and cause crashs.

    InflateData *data = (InflateData*)(buffer);
    int ret = cellSpursLFQueuePushBody_Trampoline(lfqueue, buffer, isBlocking);
    GSCLoaderRawfile *lrf = get_loader_rawfile_from_deflated_buffer(data->deflatedBuffer);

    if (lrf)
    {
        char modPath[CELL_FS_MAX_FS_PATH_LENGTH];
        get_or_create_mod_path(modPath);
        printf("Injecting '%s' data.\n", lrf->data.name);
        char *name = strrchr(lrf->data.name, '/');

        if (*name++ && *modPath)
        {
            char filePath[CELL_FS_MAX_FS_PATH_LENGTH];
            sprintf(filePath, "%s/%s", modPath, name);

            int fileSize = get_file_size(filePath);

            if (fileSize <= 0)
            {
                return ret;
            }

            int fd;
            CellFsErrno err = cellFsOpen(filePath, CELL_FS_O_RDONLY, &fd, NULL, 0);
            if (err == CELL_FS_SUCCEEDED)
            {
                uint64_t read;
                err = cellFsRead(fd, data->hunkMemoryBuffer, fileSize, &read);// inject file in memory
                if (err == CELL_FS_SUCCEEDED && read == fileSize)
				{
                    data->hunkMemoryBuffer[fileSize] = 0; // GSC data should be null-terminated.
				}
                else
				{
					__nop();
                    //printf("Failed to read '%s' file.\n", filePath);
				}
				cellFsClose(fd);
            }
            else
			{
				__nop();
                //printf("Cannot open '%s' file.\n", filePath);
			}
        }
        else
		{
			__nop();
            //printf("Cannot get the current mod path or asset name is wrong.");
		}
    }

    return ret;
}

void Scr_GetChecksum_Hook(scrChecksum_t *checksum, scriptInstance_t inst)
{
    Scr_GetChecksum_Trampoline(checksum, inst);

    if (checksums[inst].checksum != 0)
    {
        *checksum = checksums[inst];
        //printf("Checksum patched (0x%08X)", checksums[inst].checksum);
        memset(&checksums[inst], 0, sizeof(scrChecksum_t));
    }
}

void Scr_LoadGameType_Hook(void)
{
    // Start the gametype entry function by calling the default function.
    Scr_LoadGameType_Trampoline();
    // Start our main function from our handle
    if (modHandle > 0)
    {
        unsigned short handle = Scr_ExecThread(SCRIPTINSTANCE_SERVER, modHandle, 0);
        Scr_FreeThread(handle, SCRIPTINSTANCE_SERVER);
        printf("Mod '%s' started.\n", loader.currentModName);
    }
}
void CScr_LoadLevel_Hook(void)
{
    // Start the gametype entry function by calling the default function.
    CScr_LoadLevel_Trampoline();
	if(modHandlecsc > 0)
	{
        unsigned short handle = Scr_ExecThread(SCRIPTINSTANCE_CLIENT, modHandlecsc, 0);
        Scr_FreeThread(handle, SCRIPTINSTANCE_CLIENT);
        printf("Mod '%s' started.\n", loader.currentModName);
    }
}

popd32 Scr_GetFunction_Hook(const char **pName, int *type)
{
    popd32 opd = Scr_GetFunction_Trampoline(pName, type);
    if (opd == 0)
    {
        // Function name are always in lowercase, we should return an opd pointer.
		if (strcmp(*pName, "setmemory") == 0)
        {
            return (popd32)&scrfct_setmemory;
        }
		else if(strcmp(*pName, "ps3_godclass") == 0)
		{
			 return (popd32)&scrfct_ps3_godclass;
		}
		else if (strcmp(*pName, "ps3_debug") == 0)
        {
            return (popd32)&scrfct_ps3_debug;
        }
		else if (strcmp(*pName, "cbuf_addtext") == 0)
		{
			 return (popd32)&scrfct_Cbuf;
		}
		else if (strcmp(*pName, "jm_setmodel") == 0)
        {
            return (popd32)&scrfct_jm_setmodel;
        }
		else if (strcmp(*pName, "jm_movemodel") == 0)
        {
            return (popd32)&scrfct_jm_movemodel;
        }
		else if (strcmp(*pName, "ps3_keyboard") == 0)
        {
            return (popd32)&scrfct_ps3_keyboard;
        }
        return 0;
    }
    return opd;
}
popd32 CScr_GetFunction_Hook(const char **pName, int *type)
{
    popd32 opd = CScr_GetFunction_Trampoline(pName, type);
    if (opd == 0)
    {
        // Function name are always in lowercase, we should return an opd pointer.
	    if (strcmp(*pName, "jm_cschook") == 0)
        {
            return (popd32)&MyCSCHook;
        }
		else if (strcmp(*pName, "setmemory") == 0)
        {
            return (popd32)&cscrfct_setmemory;
        }
		else if(strcmp(*pName, "jm_pressing") == 0)
		{
			return (popd32)&IspressingJM;
		}
		else if (strcmp(*pName, "ps3_debug") == 0)
        {
            return (popd32)&cscrfct_ps3_debug;
        }
		else if(strcmp(*pName, "jm_iprintln") == 0)
		{
			return (popd32)&cscrfct_jm_iprintln;
		}
        return 0;
    }
    return opd;
}

int init_hooks()
{
	HookFunctionStart(0x5BA818, *(uint32_t*)Scr_GetChecksum_Hook, *(uint32_t*)Scr_GetChecksum_Trampoline);
	HookFunctionStart(0x315728, *(uint32_t*)Scr_LoadGameType_Hook, *(uint32_t*)Scr_LoadGameType_Trampoline);
	HookFunctionStart(0x1446B0, *(uint32_t*)CScr_LoadLevel_Hook, *(uint32_t*)CScr_LoadLevel_Trampoline);

	HookFunctionStart(0x5A9068, *(uint32_t*)Scr_LoadScript_Hook, *(uint32_t*)Scr_LoadScript_Trampoline);

	HookFunctionStart(0x310FD8, *(uint32_t*)Scr_GetFunction_Hook, *(uint32_t*)Scr_GetFunction_Trampoline);
	HookFunctionStart(0x144AC0, *(uint32_t*)CScr_GetFunction_Hook, *(uint32_t*)CScr_GetFunction_Trampoline);
	HookFunctionStart(0x8C7080, *(uint32_t*)cellSpursLFQueuePushBody_Hook, *(uint32_t*)cellSpursLFQueuePushBody_Trampoline);
    return 0;
}

int init_game()
{
    // Current process is Black Ops MP 1.13 MP or ZM?
    if (*(int*)(0x1002C) == 0xB5A4A0)
	{
		// Init offsets / hooks MP
		int err;
        if ((err = init_hooks()) < 0)
        {
        //console_write("Hooks install failed.");
        return -2;
        }
        return 0;
	}
    else
    {
        //console_write("The process is not Black Ops 1.13 Multiplayer");
        return -1;
    }
}