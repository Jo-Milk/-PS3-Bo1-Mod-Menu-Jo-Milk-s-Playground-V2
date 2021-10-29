
void angleVectors(vec3_t &angles, vec3_t *forward, vec3_t *right, vec3_t *up) {
    float angle;
    float sr, sp, sy, cr, cp, cy;

    angle = angles.y * (M_PI * 2.0f / 360.0f);
    sy = sin1(angle);
    cy = cos1(angle);
    angle = angles.x * (M_PI * 2.0f / 360.0f);
    sp = sin1(angle);
    cp = cos1(angle);
    angle = angles.z * (M_PI * 2.0f / 360.0f);
    sr = sin1(angle);
    cr = cos1(angle);

    if (forward) {
        forward->x = cp*cy;
        forward->y = cp*sy;
        forward->z = -sp;
    }

    if (right) {
        right->x = (-1 * sr*sp*cy + -1 * cr*-sy);
        right->y = (-1 * sr*sp*sy + -1 * cr*cy);
        right->z = -1 * sr*cp;
    }

    if (up) {
        up->x = (cr*sp*cy + -sr*-sy);
        up->y = (cr*sp*sy + -sr*cy);
        up->z = cr*cp;
    }
}
int maxplayer = 12;
bool GameIsTeamDeathMatch()
	{
		if(!strcmp("tdm",Dvar_GetString("g_gametype")))
			return true;
		else
			return false;
	}

	bool GameIsDeathMatch()
	{
		if(!strcmp("dm",Dvar_GetString("g_gametype")))
			return true;
		else
			return false;
	}
	bool GameIsOneInChamber()
	{
		if(!strcmp("oic",Dvar_GetString("g_gametype")))
			return true;
		else
			return false;
	}
	bool GameIsStickAndStone()
	{
		if(!strcmp("hlnd",Dvar_GetString("g_gametype")))
			return true;
		else
			return false;
	}
	bool GameIsGunGame()
	{
		if(!strcmp("gun",Dvar_GetString("g_gametype")))
			return true;
		else
			return false;
	}
	bool GameIsSharpShooter()
	{
		if(!strcmp("shrp",Dvar_GetString("g_gametype")))
			return true;
		else
			return false;
	}
	
	bool isFFAType()
	{
		if(GameIsDeathMatch())
			return true;
		if(GameIsOneInChamber())
			return true;
		if(GameIsStickAndStone())
			return true;
		if(GameIsGunGame())
			return true;
		if(GameIsSharpShooter())
			return true;
		else
			return false;
	}


        bool isAlive(int client)//3766B154
        {
           if(*(int*)(0x3766b1b8 + (client * 0xD8)) == 0)
			   return true;
		   else
			   return false;
        }


float angleseeeee[3];
float* vectoangles(float* Angles)
{
	float forward;
	float yaw, pitch;
	float PI = 3.1415926535897931;3.141592653589793f;
	if (Angles[0] == 0 && Angles[1] == 0)
	{
		yaw = 0;
		if (Angles[2] > 0) pitch = 90.00;
		else pitch = 270.00;
	}
	else
	{
		if (Angles[0] != -1) yaw = (float)(atan2((double)Angles[1], (double)Angles[0]) * 180.00 / PI);
		else if (Angles[1] > 0) yaw = 90.00;
		else yaw = 270;
		if (yaw < 0) yaw += 360.00;

		forward = (float)sqrt((double)(Angles[0] * Angles[0] + Angles[1] * Angles[1]));
		pitch = (float)(atan2((double)Angles[2], (double)forward) * 180.00 / PI);
		if (pitch < 0) pitch += 360.00;
	}
	angleseeeee[0] = -pitch;
	angleseeeee[1] = yaw;
	angleseeeee[2] = 0;

	return angleseeeee;
}
int ftoi(float f) {
return *(int*)&f;
}


bool IsVisible(vec3_t start, vec3_t end, int skipNumber)
{
	trace_t tr;
	CG_LocationalTrace(&tr, (float*)&start, (float*)&end,skipNumber, 0x803003,0, 0);
	return (tr.fraction != 1.0f);
}


float mypow(float num, int power) {
    float ret = 1;
    for (int i = 0; i < power; i++)
        ret = ret*num;
    return ret;
}
float Get3dDistance(vec3_t& myCoords, vec3_t& enemyCoords)
{
return sqrtf(mypow((enemyCoords.x - myCoords.x), 2) + mypow((enemyCoords.y - myCoords.y), 2) + mypow((enemyCoords.z - myCoords.z), 2));
}
void VectorCopy(const vec3_t& src, vec3_t& dst)
{
    dst.x = src.x;
    dst.y = src.y;
    dst.z = src.z;
}
void VectorNormalize(vec3_t& vec)
{
	float totalLength = sqrtf(vec.x * vec.x + vec.y * vec.y + vec.z * vec.z);
	vec.x /= totalLength;
	vec.y /= totalLength;
	vec.z /= totalLength;
}
void VectorMultiply(const vec3_t& a, float b, vec3_t& c)
{
	c.x = a.x * b;
	c.y = a.y * b;
	c.z = a.z * b;
}
void VectorScale(const vec3_t& in, float scale, vec3_t& result)
{
	VectorMultiply(in, scale, result);
}

bool CanKillPlayer(int EntityNum, vec3_t bonePosStart,vec3_t bonePosend)
{
	int localclient = *(int*)(*(int*)(0xC3DFB8));
    BulletFireParams bp;
    BulletTraceResults br;
    bp.MaxEntNum = 1022;
    bp.ignoreEntIndex = localclient;
    bp.damageMultiplier = 1.0f;
    bp.methodOfDeath = 1;
	bp.origStart = bonePosStart;
    bp.start = bonePosStart;
    bp.end = bonePosend;

	vec3_t subs = bonePosend - bonePosStart;
    vectoangles((float*)&subs);
	subs.x = angleseeeee[0];
	subs.y = angleseeeee[1];
	subs.z = angleseeeee[2];
    angleVectors(subs, &bp.dir, NULL, NULL);

    FireBulletPenetrate(0, &bp, cg->ps.weapon, &centity[localclient], (float*)&bonePosStart, 0, 1, &br);

    return (EntityNum == bp.ignoreEntIndex);
}


double G_GoodRandomFloat(int *idum)
{
    double v3;
    int j;
    int iv[32];

    *idum = -*idum;
    
    for (j = 39; j >= 0; --j)
    {
        *idum = 16807 * (*idum % 127773) - 2836 * (*idum / 127773);
        if (*idum < 0)
            *idum += 0x7FFFFFFF;
        if (j < 32)
            iv[j] = *idum;
    }

    *idum = 16807 * (*idum % 127773) - 2836 * (*idum / 127773);
    
    if (*idum < 0)
        *idum += 0x7FFFFFFF;
    
    if (0.99999988 - (double)iv[iv[0] / 0x4000000] * 4.656612875245797e-10 < 0.0)
        v3 = 0.99999988;
    else
        v3 = (double)iv[iv[0] / 0x4000000] * 4.656612875245797e-10;
    
    return (float)v3;
}

void RandomBulletDir(int randSeed, float *x, float *y)
{
    long double v3;
    float sinT;
    float theta;
    float r;
    float cosT;

    theta = G_GoodRandomFloat(&randSeed) * 360.0;
    r = G_GoodRandomFloat(&randSeed);
    v3 = (float)(theta * 0.017453292);
    cosT = cos1(v3);
    sinT = sin1(v3);
    *x = r * cosT;
    *y = r * sinT;
}

void GetWeaponSpread(float*Spread)
{
	int localclient = *(int*)(*(int*)(0xC3DFB8));
	int ServerTime = cg->ps.commandTime;
    float SpreadMultiplier = cg->ps.aimSpreadScale / 255.0f;

    float MaxSpread = 0.0f;
    float BaseSpread = 0.0f;

    int iLocalWeapon = BG_GetWeaponDef(centity[localclient].weapon);

    BG_GetSpreadForWeapon((int)&cg->ps, iLocalWeapon, &BaseSpread, &MaxSpread);

    *Spread = BaseSpread + ((MaxSpread - BaseSpread) * SpreadMultiplier);
}

void correctSpread(usercmd_s *old) 
{
    if (cg->ps.fWeaponPosFrac != 1.0f) {
        int ServerTime = cg->ps.commandTime;

        float Spread;
        GetWeaponSpread(&Spread);

        vec3_t flSpread;

        RandomBulletDir(ServerTime, &flSpread.x, &flSpread.y);

        old->angles[0] += ANGLE2SHORT(flSpread.y * Spread);
        old->angles[1] += ANGLE2SHORT(flSpread.x * Spread);
    }
}




int target = -1;

int clientNum, team;
vec3_t them;
vec3_t self;


int GetSuitableTarget()
{
	int bestTarget = -1;
	float min = 0x7fffffff;
	vec3_t them_tmp;
	AimTarget_GetTagPos(0,(0x377e3a08 + (clientNum * 0x31C)),tag_eye,(float*)&self);
	for (int i = 0; i < 18; i++)
	{
		clientInfo_t* client = &cg->clientInfo[i];
		if (client->clientNum == clientNum || !client->infoValid || !strcmp(client->name, "democlient") || client->team == 3 || !isAlive(client->clientNum))
			continue;
		else if(!isFFA)
		{
			if(client->team == team)
				continue;
		}
		AimTarget_GetTagPos(0,(0x377e3a08 + (i * 0x31C)),aimat,(float*)&them_tmp);
		bool notVisible = IsVisible(self, them, clientNum);
		if (notVisible)
		{
			if (autoWall)
			{
				if (!CanKillPlayer(i,self,them_tmp))
				{
					continue;
				}
			}
		    else
			{
				continue;
			}
		}
		float distance = sqrtf((them_tmp.x - self.x) * (them_tmp.x - self.x) + (them_tmp.y - self.y) * (them_tmp.y - self.y) + (them_tmp.z - self.z) * (them_tmp.z - self.z));

		if (distance < min)
		{
			min = distance;
			bestTarget = i;
		}
	}

	return bestTarget;
}
void UpdateValues()
{
	clientNum = cg->clientNum;
	team = cg->clientInfo[clientNum].team;
}

void ApplyPrediction(vec3_t& position, int i, float flMultiplier) {
    vec3_t vVelocity;
    VectorSubtract(centity[i].pos.trBase, centity[i].NewOrigin, vVelocity);
    vVelocity.x *= flMultiplier;
    vVelocity.y *= flMultiplier;
    vVelocity.z *= flMultiplier;
    VectorAdd(position, vVelocity, position);
}
vec3_t Angles;
int AImbotSetAngle = 0;
int lastTarget = -1;
void DoAimbot()
{
	if(AImbotSetAngle == 0)
	{
	//vec3_t angles;
	UpdateValues();
	target = GetSuitableTarget();
	if (target == -1)
	{
		return;
	}
	else
	{
	AimTarget_GetTagPos(0,(0x377e3a08 + (clientNum * 0x31C)),tag_eye,(float*)&self);
	AimTarget_GetTagPos(0,(0x377e3a08 + (target * 0x31C)),aimat,(float*)&them);
	AImbotSetAngle = 1;
	}
	}
}

//

int CG_ProcessSnapshots_hook(int localClientNum) 
{
	if (Dvar_GetBool(Dvar_cl_ingame))
	{
    if(Aimbot)
	{
	if (Pressed(Btn::L1) || Pressed(Btn::R1) && Pressed(Btn::L1))
	{
		DoAimbot();
	}
	else if(Pressed(Btn::DpadDown))
	{

		//const char* string = SL_ConvertToString(0x5F,SCRIPTINSTANCE_SERVER);
		//iPrintln_GameMessage("^1TAG client %i",j_head);
	}
	}
	}
    return CG_ProcessSnapshots_Stub(localClientNum);
}






/*
void RemoveSpread(usercmd_s* usercmd, int servertime)
{
	float spread, minSpread, maxSpread, SpreadX, SpreadY;
	int weaponDefPtr = BG_GetWeaponDef(GetCurrentWeapon());

	BG_GetSpreadForWeapon(playerState, weaponDefPtr, &minSpread, &maxSpread);
	RandomBulletDir(servertime, &SpreadX, &SpreadY);

	if (*(float*)(PLAYER_STATE + 0x168) == 1.0f) // fWeaponPosFrac
		spread = *(float*)(weaponDefPtr + 0x6C8) + ((maxSpread - *(float*)(weaponDefPtr + 0x6C8)) * playerState->spreadMultiplier / 255.f); // minSpread
	else
		spread = (maxSpread - minSpread) * (playerState->spreadMultiplier / 255.f) + minSpread;

	SpreadX *= spread;
	SpreadY *= spread;

	usercmd->angles[0] += ANGLE2SHORT(SpreadY);
	usercmd->angles[1] += ANGLE2SHORT(SpreadX);
}
*/


/*
#define VectorSubtract(a,b,c) ((c).x=(a).x-(b).x,(c).y=(a).y-(b).y,(c).z=(a).z-(b).z)
#define VectorAdd(a,b,c)  ((c).x=(a).x+(b).x,(c).y=(a).y+(b).y,(c).z=(a).z+(b).z)
void ApplyPrediction(Vector3& position, int i, float flMultiplier) {
    Vector3 vVelocity;
    VectorSubtract(centity[i].OldOrigin, centity[i].NewOrigin, vVelocity);
    vVelocity.x *= flMultiplier;
    vVelocity.y *= flMultiplier;
    vVelocity.z *= flMultiplier;
    VectorAdd(position, vVelocity, position);
}*/


#pragma region Movement Fix
char ClampChar_r(const int i) {
    if (i < -128) {
        return -128;
    }
    if (i > 127) {
        return 127;
    }
    return i;
}
float DEG2RAD(float DEG) {
	return ((DEG * M_PI) / 180);
}

void SilentFix(usercmd_s* cmd, float Angle, float OldAngle, float fOldForward, float fOldSidemove)
{
    float temp;
    if (OldAngle < 0.0f)
        OldAngle = OldAngle + 360.0f;

    if (Angle < 0.0f)
        Angle = Angle + 360.0f;

    if (Angle < OldAngle)
        temp = abs(Angle - OldAngle);
    else
        temp = 360.0f - abs(OldAngle - Angle);

    float deltaView = 360.0f - temp;
    cmd->forwardmove = ClampChar_r((int)(cos1(DEG2RAD(deltaView)) * fOldForward + (cos1(DEG2RAD(deltaView + 90.0f)) * fOldSidemove)));
    cmd->rightmove = ClampChar_r((int)(sin1(DEG2RAD(deltaView)) * fOldForward + (sin1(DEG2RAD(deltaView + 90.0f)) * fOldSidemove)));
}

void AdjustUserCmdMoves(usercmd_s* user_cmd, const float angle, const float old_angle, const float old_forwardMove, const float old_rightMove) {
    float delta_view = DEG2RAD(angle - old_angle);
    user_cmd->forwardmove = ClampChar_r(static_cast<int>(cos1(delta_view) * old_forwardMove - sin1(delta_view) * old_rightMove));
    user_cmd->rightmove = ClampChar_r(static_cast<int>(sin1(delta_view) * old_forwardMove + cos1(delta_view) * old_rightMove));
}
#pragma endregion

/*
double G_GoodRandomFloat(int *idum)
{
  double v3; // [sp+4h] [bp-98h]@11
  int j; // [sp+14h] [bp-88h]@1
  int iv[32]; // [sp+1Ch] [bp-80h]@6

  *idum = -*idum;
  for ( j = 39; j >= 0; --j )
  {
    *idum = 16807 * (*idum % 127773) - 2836 * (*idum / 127773);
    if ( *idum < 0 )
      *idum += 0x7FFFFFFF;
    if ( j < 32 )
      iv[j] = *idum;
  }
  *idum = 16807 * (*idum % 127773) - 2836 * (*idum / 127773);
  if ( *idum < 0 )
    *idum += 0x7FFFFFFF;
  if ( 0.99999988 - (double)iv[iv[0] / 0x4000000] * 4.656612875245797e-10 < 0.0 )
    v3 = 0.99999988;
  else
    v3 = (double)iv[iv[0] / 0x4000000] * 4.656612875245797e-10;
  return (float)v3;
}
void RandomBulletDir(int randSeed, float *x, float *y)
{
  long double v3; 
  float sinT; 
  float theta; 
  float r; 
  float cosT; 
  theta = G_GoodRandomFloat(&randSeed) * 360.0;
  r = G_GoodRandomFloat(&randSeed);
  v3 = (float)(theta * 0.017453292);
  cosT = cos1(v3);
  sinT = sin1(v3);
  *x = r * cosT;
  *y = r * sinT;
}*//*
void RemoveSpread(usercmd_s* usercmd)
{
	int servertime = *(int*)&usercmd->serverTime;
	float spread, minSpread, maxSpread, SpreadX, SpreadY;
	int weaponDefPtr = BG_GetWeaponDef(cg->ps.weapon);
	BG_GetSpreadForWeapon((int)&cg->ps, weaponDefPtr, &minSpread, &maxSpread);
	RandomBulletDir(servertime , &SpreadX, &SpreadY);

	//if (*(float*)(&cg->ps.fWeaponPosFrac) == 1.0f) // fWeaponPosFrac*/
		//spread = *(float*)(weaponDefPtr + 0x6C8/*fAdsSpread*/) + ((maxSpread - *(float*)(weaponDefPtr + 0x6C8/*fAdsSpread*/)) * cg->ps.aimSpreadScale / 255.f); // minSpread
	//else
		/*spread = (maxSpread - minSpread) * (cg->ps.aimSpreadScale / 255.f) + minSpread;

	SpreadX *= spread;
	SpreadY *= spread;

	usercmd->angles[0] += ANGLE2SHORT(SpreadX);
	usercmd->angles[1] += ANGLE2SHORT(SpreadY);
}*/

float normalize180(float num) {
	while (num < -180)
		num+=360;
	while (num > 180)
		num-=360;
	return num;
}
float normalize90(float num) {
	while (num < -90)
		num+=180;
	while (num > 90)
		num-=180;
	if (num > 89)
		num = 88;
	if (num < -89)
		num = -88;
	return num;
}

int CL_WritePacket_Hook(int localClientNum)
{
	usercmd_s* NewCmd = &clientActive->cmds[(clientActive->cmdNumber + 1) & 0x7F];
	usercmd_s* CurrentCmd = &clientActive->cmds[clientActive->cmdNumber & 0x7F];
	usercmd_s* OldCmd = &clientActive->cmds[(clientActive->cmdNumber - 1) & 0x7F];
	
	*OldCmd = *CurrentCmd;
	--OldCmd->serverTime;

	float OldAngleY = ANGLE2SHORT(OldCmd->angles[1]);

	if(SilentAim || NoSpread || SilentAim)
	{
	if(AImbotSetAngle == 2)
	{
	if(SilentAim)
	{
	OldCmd->angles[0] = SHORT2ANGLE((Angles.x - clientActive->deltaAngles.x));
	OldCmd->angles[1] = SHORT2ANGLE((Angles.y - clientActive->deltaAngles.y));
	AdjustUserCmdMoves(OldCmd,SHORT2ANGLE(OldCmd->angles[1]),OldAngleY,(float)OldCmd->forwardmove,(float)OldCmd->rightmove);
	SilentFix(OldCmd,OldCmd->angles[1],OldAngleY,(float)OldCmd->forwardmove,(float)OldCmd->rightmove);
	}
	if(NoSpread)
	{
	correctSpread(OldCmd);
	}
	AImbotSetAngle = false;
	}
	}
	else
	{
	if(AImbotSetAngle == 2)
	AImbotSetAngle = 0;
	}
	//AdjustUserCmdMoves(OldCmd,SHORT2ANGLE(OldCmd->angles[1]),OldAngleY,(float)OldCmd->forwardmove,(float)OldCmd->rightmove); //MovementFix
	//float spin_angle;
	//if((spin_angle > 360) ? spin_angle - 360 : spin_angle + 65.f);
	//CurrentCmd->angles[1] = ANGLE2SHORT(spin_angle);//set spin antiaim
    return CL_WritePacket_Stub(localClientNum);
}



