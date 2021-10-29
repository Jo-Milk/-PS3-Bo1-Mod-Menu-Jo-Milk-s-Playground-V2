

int ClActive()
{
 return *(int*)0x00d223c4;
}

#define SCRIPTS_PATH "/dev_hdd0/tmp/Jo-Milk"

bool CCAPI = false;
bool WebMan = false;
bool NoCW = false;

#define MAX_GSC_COUNT 100


bool Aimbot = false;
bool RedBox = false;
bool ForceHost = false;
bool nonhostend = false;
bool SteadyAim = false;

typedef union DvarValue
{
    bool enabled;
    int integer;
    uint32_t unsignedInt;
    int64_t integer64;
    uint64_t unsignedInt64;
    float value;
    float vector[4];
    const char *string;
    char color[4];
} DvarValue;

typedef enum scriptInstance_t
{
    SCRIPTINSTANCE_SERVER = 0,
    SCRIPTINSTANCE_CLIENT = 1,
    SCRIPT_INSTANCE_MAX = 2
} scriptInstance_t;

typedef enum dvarType_t
{
    DVAR_TYPE_BOOL = 0x0,
    DVAR_TYPE_FLOAT = 0x1,
    DVAR_TYPE_FLOAT_2 = 0x2,
    DVAR_TYPE_FLOAT_3 = 0x3,
    DVAR_TYPE_FLOAT_4 = 0x4,
    DVAR_TYPE_INT = 0x5,
    DVAR_TYPE_ENUM = 0x6,
    DVAR_TYPE_STRING = 0x7,
    DVAR_TYPE_COLOR = 0x8,
    DVAR_TYPE_INT64 = 0x9,
    DVAR_TYPE_LINEAR_COLOR_RGB = 0xA,
    DVAR_TYPE_COLOR_XYZ = 0xB,
    DVAR_TYPE_COUNT = 0xC
} dvarType_t;

typedef struct dvar_s
{
    const char *name;
    const char *description;
    int hash;
    unsigned int flags;
    dvarType_t type;
    bool modified;
    bool loadedFromSaveGame;
    DvarValue current;
    DvarValue latched;
    DvarValue reset;
    DvarValue saved;
    char domain[10];
    struct dvar_s *hashNext;
} dvar_s;

typedef struct scrVarPub_t
{
    char _unsafe[0x38];
    int checksum;
    int entId;
    int entFieldName;
    char *programHunkUser;
    char *programBuffer;
    char *endScriptBuffer;
    char _unsafe2[0x0C];
} scrVarPub_t; // 0x58

typedef struct scrCompilePub_t
{
    char _unsafe[0x20030];
    int programLen;
    char _unsafe2[0x1004];
} scrCompilePub_t; // 0x21038

typedef struct RawFile
{
    char *name;
    int len;
    char *buffer;
} RawFile;

typedef enum XAssetType
{
    ASSET_TYPE_RAWFILE = 0x26
} XAssetType;

typedef union XAssetHeader
{
    struct RawFile *rawFile;
    void *data;
} XAssetHeader;

typedef struct XAsset
{
    enum XAssetType type;
    union XAssetHeader header;
} XAsset;

typedef struct XAssetEntry
{
    XAsset asset;
    char zoneIndex;
    bool inuse;
    uint16_t nextHash;
    uint16_t nextOverride;
    uint16_t usageFrame;
    char margin[0x10];
} XAssetEntry;

typedef union XAssetEntryPoolEntry
{
    struct XAssetEntry entry;
    union XAssetEntryPoolEntry *next;
} XAssetEntryPoolEntry;

// Customs
typedef struct InflateData
{
    char *deflatedBuffer;
    char *hunkMemoryBuffer;
    char _unsafe[0x18];
} InflateData; // 0x20? (unknown structure, ps3 only)

typedef struct opd32
{
    void *function;
    int toc;
} opd32;
typedef struct opd32 *popd32;

typedef struct scrChecksum_t
{
    int checksum;
    int programLen;
    int substract;
} scrChecksum_t; // 0xC (unknown struct not in pdb)

typedef struct RawFileData
{
    char name[100];
    int inflatedSize;
    int size;
    char buffer[0x20];
} RawFileData;

typedef struct GSCLoaderRawfile
{
    XAssetEntry entry;
    RawFile asset;
    RawFileData data;
} GSCLoaderRawfile;

typedef struct GSCLoader
{
    char currentModName[256];
    GSCLoaderRawfile rawFiles[MAX_GSC_COUNT];
} GSCLoader;

char* Dvar_cl_ingame = (char*)0x8F07B8;

extern scrVarPub_t *scrVarPub;
scrVarPub_t* scrVarPub = (scrVarPub_t*)0x1E8B200;

extern scrCompilePub_t *scrCompilePub;
scrCompilePub_t* scrCompilePub = (scrCompilePub_t*)0x1BE8870;

struct scr_entref_t
{
  short entnum;
  short classnum;
  short client;
};


GSCLoader loader;
scrChecksum_t checksums[3];
int modHandle;
int modHandlecsc;
struct VariableStackBuffer {
	const char *pos;
	unsigned short size;
	unsigned short bufLen;
	unsigned int localId;
	char time;
	char buf[1];
};
union VariableUnion {
	int intValue;
	float floatValue;
	unsigned int stringValue;
	float *vectorValue;
	const char *codePosValue;
	unsigned int pointerValue;
	VariableStackBuffer *stackValue;
	unsigned int entityOffset;
};
struct VariableValue {
	VariableUnion u;
	int type;
};
struct function_stack_t {
	const char *pos;
	unsigned int localId;
	unsigned int localVarCount;
	VariableValue *top;
	VariableValue *startTop;
};
struct function_frame_t {
	function_stack_t fs;
	int topType;
};

struct scrVmPub_t {
	unsigned int *localVars;
	VariableValue *maxstack;
	int function_count;
	function_frame_t *function_frame;
	VariableValue *top;
	unsigned int inparamcount;
	unsigned int outparamcount;
	function_frame_t function_frame_start[32];
	VariableValue stack[2048];
};
extern scrVmPub_t *scrVmPub;
scrVmPub_t* scrVmPub = (scrVmPub_t*)0x1AF6334;

typedef void UiContext;
typedef void SessionData_s;
SessionData_s *g_serverSession = (SessionData_s *)0x2023500;

#define MAX_STRING_CHARS 1024
int HostNum;

bool FirstPopUp = false;

enum netsrc_t
{
  NS_CLIENT1 = 0x0,
  NS_SERVER = 0x1,
  NS_MAXCLIENTS = 0x1,
  NS_PACKET = 0x2,
};

struct msg_t
{
  int overflowed;
  int readOnly;
  char *data;
  char *splitData;
  int maxsize;
  int cursize;
  int splitSize;
  int readcount;
  int bit;
  int lastEntityRef;
  int flush;
  netsrc_t targetLocalNetID;
};

enum ddlPrimitiveTypes_e
{
	DDL_BYTE_TYPE = 0x0,
	DDL_SHORT_TYPE = 0x1,
	DDL_INT_TYPE = 0x2,
	DDL_INT64_TYPE = 0x3,
	DDL_FLOAT_TYPE = 0x4,
	DDL_STRING_TYPE = 0x5,
	DDL_STRUCT_TYPE = 0x6,
	DDL_ENUM_TYPE = 0x7,
};

struct ddlMemberDef_t
{
	const char *name;
	int size;
	int offset;
	ddlPrimitiveTypes_e type;
	int externalIndex;
	unsigned int min;
	unsigned int max;
	unsigned int serverDelta;
	unsigned int clientDelta;
	int arraySize;
	int enumIndex;
	int permission;
};

struct ddlStructDef_t
{
	const char *name;
	int size;
	int memberCount;
	ddlMemberDef_t *members;
};

struct ddlEnumDef_t
{
	const char *name;
	int memberCount;
	const char **members;
};

struct ddlDef_t
{
	int version;
	int size;
	ddlStructDef_t *structList;
	int structCount;
	ddlEnumDef_t *enumList;
	int enumCount;
	ddlDef_t *next;
};

struct ddlState_t
{
	int absoluteOffset;
	int arrayIndex;
	ddlMemberDef_t *member;
	ddlDef_t *ddl;
};


enum hitLocation_t
{
 HITLOC_NONE = 0,
 HITLOC_HELMET = 1,
 HITLOC_HEAD = 2,
 HITLOC_NECK = 3,
 HITLOC_TORSO_UPR = 4,
 HITLOC_TORSO_LWR = 5,
 HITLOC_R_ARM_UPR = 6,
 HITLOC_L_ARM_UPR = 7,
 HITLOC_R_ARM_LWR = 8,
 HITLOC_L_ARM_LWR = 9,
 HITLOC_R_HAND = 10,
 HITLOC_L_HAND = 11,
 HITLOC_R_LEG_UPR = 12,
 HITLOC_L_LEG_UPR = 13,
 HITLOC_R_LEG_LWR = 14,
 HITLOC_L_LEG_LWR = 15,
 HITLOC_R_FOOT = 16,
 HITLOC_L_FOOT = 17,
 HITLOC_GUN = 18,
};
enum clientConnected_t
{
	CON_DISCONNECTED  = 0,
	CON_CONNECTING  = 1,
	CON_CONNECTED  = 2,
};


short script_origin;
short trigger_hurt;
short MenuResponse;
short JM_Keyboard;

int var = 0;

bool LookforFFA = false;
bool isFFA = false;

short aimat;
short j_head = 0x5F;
short j_neck = 0x5E;
short tag_eye = 0xDD3;

bool SilentAim = false;
bool NoSpread = false;
bool autoWall = false;

typedef struct vec3_t {
	float x, y, z;
	vec3_t() {
		x = y = z = 0;
	}
	vec3_t(float x, float y, float z) {
		this->x = x; this->y = y; this->z = z;
	}
	const bool operator== (vec3_t const &Vector) {
		return (this->x == Vector.x && this->y == Vector.y && this->z == Vector.z);
	}

const vec3_t& operator* (const float mul) {
		return vec3_t(this->x *= mul, this->y *= mul, this->z *= mul);
	}
	const bool operator != (vec3_t const &Vector) {
		return (this->x != Vector.x && this->y != Vector.y && this->z != Vector.z);
	}
	const vec3_t& operator+ (vec3_t const &Vector) {
		return vec3_t(this->x + Vector.x, this->y + Vector.y, this->z + Vector.z);
	}
	vec3_t operator- (vec3_t const &Vector) {
		return vec3_t(this->x - Vector.x, this->y - Vector.y, this->z - Vector.z);
	}
	const vec3_t& operator/ (float scale) {
		return vec3_t(this->x / scale, this->y / scale, this->z / scale);
	}
} vec3_t;

#define ANGLE2SHORT(x) ((int)((x) * 65536.0f / 360.0f ) & 65535)
#define SHORT2ANGLE(x) ((x) * ( 360.0f / 65536.0f ))

#define VectorSubtract(a,b,c) ((c).x=(a).x-(b).x,(c).y=(a).y-(b).y,(c).z=(a).z-(b).z)
#define VectorAdd(a,b,c)  ((c).x=(a).x+(b).x,(c).y=(a).y+(b).y,(c).z=(a).z+(b).z)

struct BulletFireParams
{
    int MaxEntNum;//0
    int ignoreEntIndex;//4
    float damageMultiplier;//8
    int methodOfDeath;//c
    vec3_t origStart;//14
    vec3_t start;//18
    vec3_t end;//1c
    vec3_t dir;//20
};

typedef void gclient_s;
struct gentity_s
{
	char pad0[0x144];
	gclient_s *client;
	char pad1[0x1B0];
};

gentity_s *g_entities = (gentity_s *)0x12AB290;
enum TraceHitType
{
	TRACE_HITTYPE_NONE = 0,
	TRACE_HITTYPE_ENTITY = 1,
	TRACE_HITTYPE_DYNENT_MODEL = 2,
	TRACE_HITTYPE_DYNENT_BRUSH = 3,
	TRACE_HITTYPE_GLASS = 4,
};
struct trace_t
{
	/* 0x0000 */ float normal[3];
	/* 0x000C */ char unk1[0x04];
	/* 0x0010 */ float fraction;
	/* 0x0014 */ int sflags;
	/* 0x0018 */ int cflags;
	/* 0x001c */ enum TraceHitType hitType;
	/* 0x0020 */ unsigned short hitId;
	/* 0x0022 */ unsigned short modelIndex;
	/* 0x0024 */ unsigned short partName;
	/* 0x0026 */ unsigned short boneIndex;
	/* 0x0028 */ unsigned short partGroup;
	/* 0x002a */ bool allsolid;
	/* 0x002b */ bool startsolid;
	/* 0x002c */ bool walkable;
	/* 0x002d */ char Padding_455[3];
	/* 0x0030 */ struct cStaticModel_s* staticModel;
	/* 0x0034 */ int hitPartition;
};
struct BulletTraceResults
{
	trace_t trace;
	int* hitEnt; // gentity_s*
	float hitPos[3];
	int ignoreHitEnt;
	int hitSurfaceType;
};



//int myindex = *(int*)(*(int*)(0xC3DFB8));


struct cpose_ts
{
    unsigned short lightningHandle; //0x00
    unsigned char eType; //0x02
    char eTypeUnion; //0x03
    int localClientNum; //0x04
    char pad01[40]; //0x8
    //int physObjId; //0x18
    vec3_t origin; //0x30
    vec3_t angles; //0x3C
    vec3_t absmin; //0x48
    vec3_t absmax; //0x54
    char pad02[12]; //0x60
}; //size 0x6C

struct trajectory_t
{
    char trType;
    int trTime;
    int trDuration;
    vec3_t trBase;
    vec3_t trDelta;
};
struct centity_s
{
    cpose_ts pose;        //0x00
	char pad0[0x8];        //0x6C
	vec3_t bounds[2];		//0x0074
	char _0x008C[0x30];		//0x008C
	short eventParam;       //0x00BC
	char _0x00BE[0x6];		//0x00BE
	short otherEntityNum;	//0x00C4
	short attackerEntityNum;//0x00C6
	char _0x00C8[0xA8];	//0x00C8
    char trType;        //0x170
    int trTime;            //0x174
    int trDuration;        //0x178
    vec3_t NewOrigin;    //0x17C
    vec3_t trDelta;    //0x188
    char trType2;        //0x194
    int trTime2;        //0x198
    int trDuration2;    //0x19C
    vec3_t trBase2;    //0x1A0
    vec3_t trDelta2;    //0x1AC
    char pad_u[32];        //0x1B8
    int useCount;        //0x1D8
    int clientnum;        //0x1DC
    int eFlags;            //0x1E0
    int eFlags2;        //0x1E4
    trajectory_t pos;    //0x1E8
    trajectory_t apos;    //0x20C
	char _0x0230[0x14];		//0x0230
	int actorTeam;			//0x0244
	short primaryWeapon;	//0x0248
	char _0x024A[0xB];		//0x024A
	char renderCamo;		//0x0255
	char _0x0256[0x2A];		//0x0256
	int item;				//0x0280
	char _0x0284[0x16];		//0x0284
    short eType;        //0x29A
	short hitEntityNum;		//0x029C
    char pad00[8];        //0x29E
    unsigned short weapon;//0x2A6
    char pad000[0x74];    //0x2A8
};
/*struct centity_s
{
	char _0x0000[0x2];		//0x0000
	short Alive;			//0x0002
	char _0x0004[0x2C];		//0x0004
	vec3_t origin;			//0x0030
	char _0x003C[0xC];		//0x003C
	vec3_t absBounds[2];	//0x0048
	char _0x0060[0x14];		//0x0060       char _0x006C[0x8];	//0x006c
	vec3_t bounds[2];		//0x0074 
	char _0x008C[0x30];		//0x008C
	short eventParam;		//0x00BC
	char _0x00BE[0x6];		//0x00BE
	short otherEntityNum;	//0x00C4
	short attackerEntityNum;//0x00C6
	char _0x00C8[0x120];	//0x00C8
	int number;				//0x01E8
	int eFlags;				//0x01EC
	int eFlags2;			//0x01F0
	char _0x01F4[0x50];		//0x01F4
	int actorTeam;			//0x0244
	short primaryWeapon;	//0x0248
	char _0x024A[0xB];		//0x024A
	char renderCamo;		//0x0255
	char _0x0256[0x2A];		//0x0256
	int item;				//0x0280
	char _0x0284[0x22];		//0x0284
	short eType;			//0x02A6
	short hitEntityNum;		//0x02A8
	char _0x00AA[0x2];		//0x02AA
	short sourceEntityNum;	//0x02AC
	char _0x02A8[0x6E];		//0x02AE
	//size: 0x031C
};*/

#pragma region objective_t
struct objective_t
{
    int state; //0x00
    float origin[3]; //0x04
    float size[2]; //0x10
    int entNum; //0x18
    int teamNum; //0x1C
    int icon; //0x20
    int use3D; //0x24
    int color; //0x28
    const char* alt_3D_text; //0x2C
}; //size 0x30
#pragma endregion

struct playerstate_s
{
	unsigned int commandTime; //0x0
	int pm_type; //0x4
	int bobCycle; //0x8
	int pm_flags; //0xC
	int weapFlags; //0x10
	int otherFlags; //0x14
	int pm_time; //0x18
	unsigned int loopSoundId; //0x1C
	int loopSoundFade; //0x20
	float origin[3]; //0x24
	float velocity[3]; //0x30
	int weaponTime; //0x3C
	int weaponDelay; //0x40
	int weaponTimeLeft; //0x44
	int weaponDelayLeft; //0x48
	int weaponIdleTime; //0x4C
	int grenadeTimeLeft; //0x50
	int throwBackGrenadeOwner; //0x54
	int throwBackGrenadeTimeLeft; //0x58
	int weaponRestrictKickTime; //0x5C
	bool mountAvailable; //0x60
	bool bRunLeftGun; //0x61
	bool bCarryingTurret; //0x62
	char pad01[0x1]; //0x63
	float mountPos[3]; //0x64
	float mountDir; //0x70
	int foliageSoundTime; //0x74
	int gravity; //0x78
	float leanf; //0x7C
	int speed; //0x80
	float delta_angles[3]; //0x84
	int groundEntityNum; //0x90
	int groundType; //0x94
	float vLadderVec[3]; //0x98
	int jumpTime; //0xA4
	float jumpOriginZ; //0xA8
	int slideTime; //0xAC
	int moveType; //0xB0
	int legsTimer; //0xB4
	int torsoTimer; //0xB8
	short legsAnim; //0xBC
	short torsoAnim; //0xBE
	int legsAnimDuration; //0xC0
	int torsoAnimDuration; //0xC4
	int damageTimer; //0xC8
	int damageDuration; //0xCC
	int dmgDirection; //0xD0
	int dmgType; //0xD4
	int corpseIndex; //0xD8
	int movementDir; //0xDC
	int eFlags; //0xE0
	int eFlags2; //0xE4
	short predictableEventSequence; //0xE8
	short predictableEventSequenceOld; //0xEA
	int predictableEvents[4]; //0xEC
	unsigned int predictableEventParms[4]; //0xFC
	short unpredictableEventSequence; //0x10C
	short unpredictableEventSequenceOld; //0x10E
	int unpredictableEvents[4]; //0x110
	unsigned int unpredictableEventParms[4]; //0x120
	char clientNum;				//0x130
	int offHandIndex;			//0x134
	int offhandSecondary;		//0x138
	int offhandPrimary;			//0x13C
	char pad00[4];				//0x140
	unsigned short weapon;				//0x144
	unsigned short lastStandPrevWeapon;	//0x146
	unsigned int lastWeaponAltModeSwitch;//0x148
	unsigned int stowedWeapon;			//0x14C
	char stowedWeaponCamo;				//0x150
	unsigned int meleeWeapon;			//0x154
	int weaponstate;					//0x158
	int weaponstateLeft;				//0x15C
	unsigned int weaponShotCount;		//0x160
	unsigned int weaponShotCountLeft;	//0x164
	float fWeaponPosFrac;				//0x168
	int adsDelayTime;					//0x16C
	int spreadOverride;					//0x170
	int spreadOverrideState;			//0x174
	float weaponSpinLerp;				//0x178
	int viewmodelIndex;					//0x17C
	vec3_t viewangles;					//0x180
	char pad03[0x3D4]; // 0x18C
	float aimSpreadScale;	//0x560
	char pad04[0x58]; // 0x564
	objective_t objective[0x20];//0x5BC
	int deltaTime; //0xBBC
	int killCamEntity; //0xBC0
	int killCamTargetEntity; //0xBC4

}; //size 0xBC8

#pragma region refdef_s
struct refdef_s
{
    unsigned int x; //0x00
    unsigned int y; //0x04
    unsigned int width; //0x08
    unsigned int height; //0x0C
    char pad01[0x14]; //0x10
    float tanHalfFovX; //0x24
    float tanHalfFovY; //0x28
    float fov_x; //0x2C
    vec3_t vieworg; //0x30
    float yaw; //0x3C
    float viewaxis[3][3]; //0x40
    int time; //0x64
}; //size 0x68
#pragma endregion

#pragma region snapshot_s
struct snapshot_s
{
    int snapFlags; //0x00
    int ping; //0x04
    int serverTime; //0x08
    int physicsTime; //0x0C
	playerstate_s ps; //0x10
    int numEntities;
    int numClients;
    //entityState_s entities[512];
    //clientState_s clients[32];
    char matchState_pad[0x80];
    int serverCommandSequence;
};
#pragma endregion

#pragma region score_s
struct score_s
{
    int ping; //0x00
    int status_icon; //0x04
    int place; //0x08
    int score; //0x0C
    int kills; //0x10
    int assists; //0x14
    int deaths; //0x18
    int scoreboardColumns[4]; //0x1C
}; //size 0x2C
#pragma endregion

#pragma region clientInfo_t
struct lerpFrame_t
{
    float yawAngle; //0x00
    int yawing; //0x04
    float pitchAngle; //0x08
    int pitching; //0x0C
    int animationNumber; //0x10
    void* animation; //0x14
    int animationTime; //0x18
    float oldFramePos[3]; //0x1C
    float oldFrameYaw; //0x28
    float animSpeedScale; //0x2C
    int oldFrameSnapshotTime; //0x30
}; //size 0x34

struct clientInfo_t
{
    int infoValid; //0x00
    int nextValid; //0x04
    int clientNum; //0x08
    char name[0x20]; //0x0C
    int team; //0x2C
    int oldTeam; //0x30
    int ffaTeam; //0x34
    int rank; //0x38
    int prestige; //0x3C
    int needsRevive; //0x40
    unsigned int perks[2]; //0x44
    char pad01[0x4]; //0x4C
    unsigned long long xuid; //0x50
    char clanAbbrev[0x8]; //0x58
    score_s score; //0x60
    void* hStatusIcon; //0x8C
    void* hRankIcon; //0x90
    int location; //0x94
    int health; //0x98
    char model[0x40]; //0x9C
    char attachModelNames[0x6][0x40]; //0xDC
    char attachTagNames[0x6][0x40]; //0x1C0
    lerpFrame_t legs; //0x25C
    lerpFrame_t torso; //0x290
    float lerpMoveDir; //0x2C4
    float lerpLean; //0x2C8
    float playerAngles[3]; //0x2CC
    int leftHandGun; //0x2D8
    int dobjDirty; //0x2DC
    char pad02[0x170]; //0x2E0
}; //size 0x5D0
#pragma endregion

#pragma region cg_s
struct cg_s
{
    int clientNum; //0x00
    int localClientNum; //0x04
    char pad01[0x18]; //0x08
    int latestSnapshotNum; //0x20
    int latestSnapshotTime; // 0x24
    snapshot_s* snap; //0x28
    snapshot_s* nextSnap; //0x2C
    char pad02[0x58]; //0x30
    int serverTime; //0x88
    char pad03[0x28]; //0x8C
    float origin[3]; //0xB4
    char pad04[0x1C]; //0xC0
    int lastAimTime; //0xDC
    char pad05[0x4]; //0xE0
    int maxEntities; //0xE4
    char pad06[0x88]; //0xE8
    int stance; //0x170
    char pad07[0x60]; //0x174
    unsigned short weapon; //0x1D4
    char pad08[0x7E]; //0x1D8
    int health; //0x254
    char pad09[0x3ED44]; //0x258
	playerstate_s ps; //0x3EF9C
    char pad10[0x1E9C]; // 0x3FB64
    refdef_s refdef; //0x41A00
    char pad11[0x1BE78]; //0x41A68
    float compassNorthYaw; //0x5D8E0
    float compassNorth[2]; //0x5D8E4
    void* compassMapMaterial; //0x5D8EC
    float compassMapUpperLeft[2]; //0x5D8F0
    float compassMapWorldSize[2]; //0x5D8F8
    int compassLastTime; //0x5D900
    float compassYaw; //0x5D904
    float compassSpeed; //0x5D908
    int compassFadeTime; //0x5D90C
    char pad12[0x1E8]; //0x5D910
    clientInfo_t clientInfo[18]; //0x5DAF8
};
#pragma endregion

struct usercmd_s
{
    int serverTime;//0x00
    int button_bits[2];//0x04
    float angles[3]; //0x0C
    unsigned short weapon;//0x18
    unsigned short offHandIndex;//0x1A
    unsigned short lastWeaponAltModeSwitch;//0x1C
    char forwardmove;//0x1E
    char rightmove;//0x1F
    char upmove;//0x20
    char pitchmove;//0x21
    char yawmove;//0x22
	char pad00;//0x23
    float meleeChargeYaw;//0x24
    char meleeChargeDist;//0x28
	char pad01[3];//0x29
    float rollmove;//0x2C
    char selectedLocation[2];//0x30
    char selectedYaw;//0x32
	char pad03;//0x33
};//size 0x34

#pragma region clientActive_t
struct clientActive_t
{
    char pad01[0x10]; //0x00
    int serverTime; //0x10
    int oldServerTime; //0x14
    int oldFrameServerTime; //0x18
    int serverTimeDelta; //0x1C
    int ping; //0x20
    char pad02[0x88]; //0x24
    vec3_t deltaAngles; //0xAC
    char pad03[0x2794]; //0xB8 
    vec3_t viewAngle; //0x284C
    char pad04[0x40010]; //0x2858
    usercmd_s cmds[0x80]; //0x42868
    int cmdNumber; //0x44268
}; //size 0x4426C
#pragma endregion
#define clientActive (*(clientActive_t**)(0xD223C4))
#define centity ((centity_s*)(0x377e3a08))
#define cg ((cg_s*)(*(int*)(0xC3DFB8)))


bool revgodclass = false;



char GSC_Keyboardbuffer[MAX_STRING_CHARS];
bool GSC_Keyboardbool = false;