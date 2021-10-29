#include maps\mp\_utility;
#include common_scripts\utility;
#include maps\mp\gametypes\_hud_util;

#include maps\mp\mod\_Spawnables;

main()
{
    level.start = true;
    level.JMPlayground = false;
    //setdvar("ui_gametype_text","^1Welcome To ^2Jo-Milk^1's Playground V2");
    setmemory("0x8CF430","0x429C0000");
	setmemory("0x81B64","0x41");
	setdvar("scr_teambalance", "0");
	level.teambalance = 0;
	precacheModel("defaultactor");
	precacheModel("defaultvehicle");
	precacheModel("test_sphere_silver");
	precacheshader("compassping_player");
	precacheshader("menu_mp_reticle_diamond02");
	precacheshader("menu_mp_reticle_triangle01");
	precacheshader("menu_mp_reticle_circles_triangles02");
	//setdvar("scr_xpscale","3");
	if(ps3_godclass(1) == 1)
    setdvar("scr_disable_cac","1");
	//makedvarserverinfo("r_fog","1");
	//setdvar("r_fog","1");
	//ps3_debug("stat_version : "+ GetDvarInt("stat_version"));
    //ps3_debug("stats_version_check : "+ GetDvarInt("stats_version_check"));
    level thread onPlayerConnect();
}

onPlayerConnect()
{
    for(;;)
    {
        level waittill("connected", player);
		player.aimbot = 0;
		player.aimAt = undefined;
		if ( player IsHost() )
		{
		setdvar("scr_teambalance", "0");
	    level.teambalance = 0;
		player GiveSuperAdmin();
		}
		else
		player NewPlayer_JM();
        player thread onPlayerSpawned();
    }
}

onPlayerSpawned()
{
    self endon("disconnect");
    for(;;)
    {
        self waittill("spawned_player");
		if(level.JMPlayground == true)
		self thread Snipez();
		if(level.start == true && self IsHost())
		{
		self freezecontrols(false);
		level.start = false;
		self DoWelcome();
		}
		//"l96a1_mp"
    }
}

NewPlayer_JM()
{
self.editor = false;
self.verified = false;
self.SuperAdmin = false;
self.Admin = false;
self.Vip = false;
self.MenuVerStatus = "^0-";
}

addMenu(menu, title, parent)
{
    if(!isDefined(self.menuAction))
        self.menuAction = [];
    self.menuAction[menu] = spawnStruct();
    self.menuAction[menu].title = title;
    self.menuAction[menu].parent = parent;
    self.menuAction[menu].opt = [];
    self.menuAction[menu].func = [];
    self.menuAction[menu].inp = [];
}
 
addOpt(menu, opt, func, inp)
{
    m = self.menuAction[menu].opt.size;
    self.menuAction[menu].opt[m] = opt;
    self.menuAction[menu].func[m] = func;
    self.menuAction[menu].inp[m] = inp;
}

changeFontScaleOverTime(time, scale)
{
    start = self.fontscale;
    frames = (time/.05);
    scaleChange = (scale-start);
    scaleChangePer = (scaleChange/frames);
    for(m = 0; m < frames; m++)
    {
        self.fontscale+= scaleChangePer;
        wait .05;
    }
}
 
createText(font, fontScale, align, relative, x, y, sort, alpha, glow, text)
{
    textElem = self createFontString(font, fontScale, self);
    textElem setPoint(align, relative, x, y);
    textElem.sort = sort;
    textElem.alpha = alpha;
    textElem.glowColor = glow;
    textElem.glowAlpha = 1;
    textElem setText(text);
    //self thread destroyOnDeath(textElem);
    return textElem;
}
 
createRectangle(align, relative, x, y, width, height, color, shader, sort, alpha)
{
    boxElem = newClientHudElem(self);
    boxElem.elemType = "bar";
    if(!level.splitScreen)
    {
        boxElem.x = -2;
        boxElem.y = -2;
    }
    boxElem.width = width;
    boxElem.height = height;
    boxElem.align = align;
    boxElem.relative = relative;
    boxElem.xOffset = 0;
    boxElem.yOffset = 0;
    boxElem.children = [];
    boxElem.sort = sort;
    boxElem.color = color;
    boxElem.alpha = alpha;
    boxElem setParent(level.uiParent);
    boxElem setShader(shader, width, height);
    boxElem.hidden = false;
    boxElem setPoint(align, relative, x, y);
    //self thread destroyOnDeath(boxElem);
    return boxElem;
}

ModMenu()
{
self endon("disconnect");
if( self IsHost() == false) 
self endon("UnVer");
self.menucolorbackground = (0,0,0);
self.menucolor = (0,0.5,1);
self.menu_text_pos_openText = 0;
self.menu_text_pos_MenuTextName = 0;
self.openBox = self createRectangle("TOP", "TOP", 0, -65, 275, 30, self.menucolorbackground, "white", 1, .7); 
self.Advert1 = self createRectangle("CENTER", "", 0, 220, 1000, 30, self.menucolorbackground, "white", 1, .7);
self.Advert2 = self createRectangle("CENTER", "", 0, 205, 1000, 1, self.menucolor, "white", 1, 1);
self.Advert3 = self createRectangle("CENTER", "", 0, 235, 1000, 1, self.menucolor, "white", 1, 1);
self.txt = self createFontString("objective", 1.5); 
self.openBox.alpha = 0;
self.Advert1.alpha = 0;
self.Advert2.alpha = 0;
self.Advert3.alpha = 0;
self.txt.alpha = 0;
		
self.Advert1 fadeOverTime(1);
self.Advert1.alpha = .7;
self.Advert2 fadeOverTime(1);
self.Advert2.alpha = 1;
self.Advert3 fadeOverTime(1);
self.Advert3.alpha = 1;
self.txt fadeOverTime(1);
self.txt.alpha = 1;
		
		
self.txt.foreGround = true; 
self.txt setPoint("CENTER", "", 0, 220); 
if(self.name == "Jo-Milk")
self.txt setText("^7Welcome To ^1Jo-Milk's Playground V2 ^7Press ^7[{+smoke}]^7 To Open Menu");
else
self.txt setText("^7Welcome ^2"+self.name+" ^7To ^1Jo-Milk's Playground V2 ^7Press ^7[{+smoke}]^7 To Open Menu");
self.currentMenu = "main";
self.menuSelect = 0;

    for(;;)
    {
        
        if(self.isMenuOpen == false)
        {
			if(self SecondaryOffHandButtonPressed() && self.editor == false)
            {
            self Open_ModMenu();
            self.txt.x = 0;
			}
        }
        else if(self.isMenuOpen == true && self.editor == false)
        {
            if(self attackButtonPressed())
            {
                self.menuSelect++;
                if(self.menuSelect > self.menuAction[self.currentMenu].opt.size-1)
                    self.menuSelect = 0;
                self.scrollBar moveOverTime(.15);
                self.scrollBar.y = ((self.menuSelect*17.98)+((self.menuText.y+2.5)-(17.98/17)));
                wait .15;
            }
            else if(self adsButtonPressed())
            {
                 self.menuSelect--;
                if(self.menuSelect < 0)
                    self.menuSelect = self.menuAction[self.currentMenu].opt.size-1;
                self.scrollBar moveOverTime(.15);
                self.scrollBar.y = ((self.menuSelect*17.98)+((self.menuText.y+2.5)-(17.98/17)));
                wait .15;
            }
            else if(self useButtonPressed())
            {
				self.scrollBar fadeOverTime(.1);
				self.scrollBar.alpha = .3;
                self thread [[self.menuAction[self.currentMenu].func[self.menuSelect]]](self.menuAction[self.currentMenu].inp[self.menuSelect]);
                wait .1;
				self.scrollBar fadeOverTime(.1);
				self.scrollBar.alpha = .7;
				wait .1;
            }
            else if(self meleeButtonPressed())
            {
                if(!isDefined(self.menuAction[self.currentMenu].parent))
                {
                    self Close_ModMenu();
                }
                else
                    self subMenu(self.menuAction[self.currentMenu].parent);
            }
        }
        wait .05;
    }
}

DoWelcome()
{
notifyData = spawnStruct();
notifyData.titleText = "^5Welcome To Jo-Milk's Playground V2";
notifyData.notifyText = "Hosted by "+level.hostname;
notifyData.iconName = "rank_prestige15";
notifyData.sound = "mus_level_up";
notifyData.duration = 8;
self maps\mp\gametypes\_hud_message::notifyMessage( notifyData ); 
}


Open_ModMenu()
{
self.isMenuOpen = true;
self.MenuTextName = self createText("big", 2.2, "TOP", "TOP", self.menu_text_pos_MenuTextName, 0, 2, 1, self.menucolor, "Jo-Milk's Playground V2"); 
self.openText = self createText("default", 1.4, "TOP", "TOP", self.menu_text_pos_openText, 30, 2, 1, self.menucolor, ""); 
self.MenuTextName.alpha = 0;
self.MenuTextName fadeOverTime(.4);
self.MenuTextName.alpha = 1;
self freezecontrols(true);
self.txt fadeOverTime(.2);
self.txt.alpha = 0;			
self initMenuOpts();
menuOpts = self.menuAction[self.currentMenu].opt.size;		
self.openBox.alpha = .7;
self.openBox scaleOverTime(.4, 275, ((430)+100));
wait .2;
self.txt setText("Press [{+attack}] and [{+speed_throw}] To Navigate [{+usereload}]  To Select [{+melee}] ^7 Back");
self.txt fadeOverTime(.2);
self.txt.alpha = 1;
self.openText setText(self.menuAction[self.currentMenu].title);
self.openText fadeOverTime(.2);
self.openText.alpha = 1;
wait .2; 
string = "";
for(m = 0; m < menuOpts; m++)
string+= self.menuAction[self.currentMenu].opt[m]+"\n";
self.menuText = self createText("objective", 1.5, "TOP", "TOP", self.menu_text_pos_MenuTextName, 50, 3, 1, undefined, string);
self.scrollBar = self createRectangle("TOP", "TOP", self.menu_text_pos_MenuTextName, ((self.menuSelect*17.98)+((self.menuText.y+2.5)-(17.98/15))), 275, 15, self.menucolor, "white", 2, .7);
}	
Close_ModMenu()
{
  self ModMenu_exit();
  self.txt fadeOverTime(.2);
  self.txt.alpha = 0;
  wait 0.3;
  self.txt fadeOverTime(.2);
  self.txt.alpha = 1;
  if(self.name == "Jo-Milk")
  self.txt setText("^7Welcome To ^1Jo-Milk's Playground V2 ^7Press ^7[{+smoke}]^7 To Open Menu");
  else
  self.txt setText("^7Welcome ^2"+self.name+" ^7To ^1Jo-Milk's Playground V2 ^7Press ^7[{+smoke}]^7 To Open Menu");
}
ModMenu_exit()
{
self.isMenuOpen = false;
self.menuSelect = 0;
self.currentMenu = "main";
self.openText destroy();   
self.MenuTextName destroy();   
self.openBox scaleOverTime(.4, 275, 30);
self.menuText destroy();
self.scrollBar destroy();
wait .4;
self.openBox.alpha = 0;
self freezecontrols(false);
}


subMenu(menu)
{
	
self.menuSelect = 0;
self.currentMenu = menu;
self.scrollBar moveOverTime(.2);
self.scrollBar.y = ((self.menuSelect*17.98)+((self.menuText.y+2.5)-(17.98/15)));
self.menuText destroy();
//MenuTextName
self initMenuOpts();
self.openText fadeOverTime(.2);
self.openText.alpha = 0;
self notify("stop_glowingalphaa");
self.MenuTextName.alpha = 1;
self.MenuTextName fadeOverTime(.2);
self.MenuTextName.alpha = 0;
self.openBox scaleOverTime(.4, 275, ((430)+45));
menuOpts = self.menuAction[self.currentMenu].opt.size;
wait .2;
self.openText setText(self.menuAction[self.currentMenu].title);
string = "";
for(m = 0; m < menuOpts; m++)
string+= self.menuAction[self.currentMenu].opt[m]+"\n";
self.menuText = self createText("objective", 1.5, "TOP", "TOP", self.menu_text_pos_MenuTextName, 50, 3, 1, undefined, string);
self.menuText moveOverTime(0); 
self.menuText.y = -100;
self.menuText moveOverTime(.2); 
self.menuText.y = 50;


wait .2;
self.openText fadeOverTime(.2);
self.openText.alpha = 1;
self.MenuTextName fadeOverTime(.2);
self.MenuTextName.alpha = 1;
wait .2;
}


initMenuOpts()
{
m = "main";
self addMenu(m, "Main Menu", undefined);
self addOpt(m, "Fun Menu", ::subMenu, "fun");
self addOpt(m, "Weapon Menu", ::subMenu, "wep");
self addOpt(m, "Model Menu", ::subMenu, "model1");
self addOpt(m, "Vision Menu", ::subMenu, "vis");
self addOpt(m, "Killstreak Menu", ::subMenu, "strk1");
self addOpt(m, "Design Menu", ::subMenu, "des1men");
self addOpt(m, "Say Menu", ::subMenu, "msg1m");
if(self.Vip == true)
self addOpt(m, "VIP Menu", ::subMenu, "vipm");
if(self.Admin == true)
self addOpt(m, "Admin Menu", ::subMenu, "Admin1");
if(self.SuperAdmin == true)
{
self addOpt(m, "Player Menu", ::subMenu,"plmenu");
self addOpt(m, "Lobby Menu", ::subMenu, "Lobbym");
if( self IsHost() )
{
self addOpt(m, "Patch Menu", ::subMenu, "Patchm");
self addOpt(m, "Host Menu", ::subMenu, "hostm");
self addOpt(m, "Credits", ::Test);
}
}
if(self.Vip == true)
{
m = "vipm";
self addMenu(m, "VIP Menu", "main");
self addOpt(m, "Teleport Gun", ::TeleportGun);
self addOpt(m, "Forge Mode", ::ForgeON);
self addOpt(m, "Black bird", ::doBlackbird);
self addOpt(m, "ESP", ::WallHack);
self addOpt(m, "Show Location", ::oriJM);
self addOpt(m, "Unlock Achivements", ::Achivements);
}
if(self.Admin == true)
{
m = "Admin1";
self addMenu(m, "Admin Menu", "main");
self addOpt(m, "Aimbot menu", ::subMenu, "aim1m");
self addOpt(m, "Bullets Menu", ::subMenu, "Bullets");
self addOpt(m, "Fx Bullets", ::subMenu, "bulletsfx_spawn");
self addOpt(m, "Do Hearts Creator", ::doHeartText);
self addOpt(m, "Do Hearts Host", ::doHeartText1);
self addOpt(m, "Clone Yourself", ::CloneSelf);
self addOpt(m, "Unlimited Ammo", ::toggleAmmo);

m = "aim1m";
self addMenu(m, "Aimbot Menu", "Admin1");
self addOpt(m, "Unfair Aimbot", ::JMaimbot,1);
self addOpt(m, "Unfair Aimbot2", ::JMaimbot,2);
self addOpt(m, "Aim Assist", ::JMaimbot,3);

m = "Bullets";
    self addMenu(m, "Bullets Menu", "main");
	self addOpt(m, "Explosive Bullets", ::Toggle_ExplosiveBullets);
	self addOpt(m, "RPG Bullets", ::initBulletsFunction, "RPG_mp");
	self addOpt(m, "M72 LAW Bullets", ::initBulletsFunction, "m72_law_mp");
	self addOpt(m, "China Lake Bullets", ::initBulletsFunction, "china_lake_mp");
	
	m = "bulletsfx_spawn";
    self addMenu(m, "FX Bullets Weapons", "main");
	self addOpt(m, "Ray Gun Tracer", ::RayGunTracer);
	self addOpt(m, "Green Light Gun", ::FxGunSpawner, "misc/fx_equip_tac_insert_light_grn");
	self addOpt(m, "Red Light Gun", ::FxGunSpawner, "misc/fx_equip_tac_insert_light_red");
	self addOpt(m, "Explosion Gun", ::FxGunSpawner, "maps/mp_maps/fx_mp_exp_bomb");
	self addOpt(m, "Blood", ::FxGunSpawner, "trail/fx_trail_blood_streak_mp");
}
m = "Lobbym";
self addMenu(m, "Lobby Menu", "main");
self addOpt(m, "Jo-Milk's Playground", ::hazardzone);
self addOpt(m, "Toggle Super Jump", ::JM_JUMP);
self addOpt(m, "Fall damage", ::falldamage);
self addOpt(m, "Toggle Gravity", ::LowGravity);
self addOpt(m, "Toggle Speed", ::SuperSpeed);
self addOpt(m, "Far Knife", ::MeleeRange);
self addOpt(m, "Unlimited Game", ::UnlimitedGame);
self addOpt(m, "Spawnables", ::subMenu, "bunk1m");
self addOpt(m, "Fog Menu", ::subMenu, "fogcolor");
self addOpt(m, "Message Menu", ::subMenu, "msg2m");
self addOpt(m, "All Clients Menu", ::subMenu, "Lobbym3");

m = "fogcolor";
self addMenu(m, "Fog Menu", "Lobbym");
self addOpt(m, "Fog Red", ::RedF);  
self addOpt(m, "Fog Blue", ::BlueF);  
self addOpt(m, "Fog Greeen", ::GreenF);  
self addOpt(m, "Fog Yellow", ::YelwF);  
self addOpt(m, "Fog Purple", ::PurpF);
self addOpt(m, "Fog Orange", ::OranF);
self addOpt(m, "Fog Cyan", ::CyanF);  
self addOpt(m, "Fog Editor", ::FOGRGB);    
self addOpt(m, "Fog Disco", ::disco);  
self addOpt(m, "Default Fog", ::NoFdeafault);  

m = "bunk1m";
self addMenu(m, "Spawnables Menu", "Lobbym");
self addOpt(m, "Mexican Wave", ::mexicanWave);
self addOpt(m, JM_Spawn_GetText(1), ::Spawnable1);
self addOpt(m, JM_Spawn_GetText(2), ::Spawnable2);
self addOpt(m, JM_Spawn_GetText(3), ::Spawnable3);
self addOpt(m, JM_Spawn_GetText(4), ::Spawnable4);
self addOpt(m, JM_Spawn_GetText(5), ::Spawnable5);
self addOpt(m, JM_Spawn_GetText(6), ::Spawnable6);
self addOpt(m, JM_Spawn_GetText(7), ::Spawnable7);
self addOpt(m, JM_Spawn_GetText(8), ::Spawnable8);
self addOpt(m, JM_Spawn_GetText(9), ::Spawnable9);
m = "Lobbym3";
self addMenu(m, "All CLients Menu", "Lobbym");
self addOpt(m,"Remove Menu", undefined);
self addOpt(m,"Give Menu", undefined); 
self addOpt(m,"Give VIP", undefined);
self addOpt(m,"Player Sucide", ::JM_KillThemAll);
self addOpt(m,"Bring player here",::bringallhere);
self addOpt(m,"Kick Player",::KickthemAll);
self addOpt(m,"Freeze",::FreezeThem_All);
self addOpt(m,"Un-Freeze",::UnFreezeThem_All);
m = "hostm";
self addMenu(m, "Host Menu", "main");
self addOpt(m, "Ranked\Private", ::JM_Make_rankedGame);
self addOpt(m, "XP Lobby", undefined);
self addOpt(m, "Remove God Class", ::AntiGodclass);
self addOpt(m, "Spawn Bot", ::dobots);
self addOpt(m, "Gametype Menu", ::subMenu, "mapm3");
self addOpt(m, "Change Map", ::subMenu, "mapm1");
self addOpt(m, "Map Restart", ::RestartMapJM);
self addOpt(m, "Fast Restart", ::RestartMatch);
self addOpt(m, "End Game", ::EndGame);

m = "mapm1";
self addMenu(m, "Map Menu", "hostm");
self addOpt(m, "Nuketown", ::JM_Map, "mp_nuked");
self addOpt(m, "Grid", ::JM_Map, "mp_duga");
self addOpt(m, "Jungle", ::JM_Map, "mp_havoc");
self addOpt(m, "Firing Range", ::JM_Map, "mp_firingrange");
self addOpt(m, "Array", ::JM_Map, "mp_array");
self addOpt(m, "Summit", ::JM_Map, "mp_mountain");
self addOpt(m, "Radiation", ::JM_Map, "mp_radiation");
self addOpt(m, "Launch", ::JM_Map, "mp_cosmodrome");
self addOpt(m, "Havana", ::JM_Map, "mp_cairo");
self addOpt(m, "Crisis", ::JM_Map, "mp_crisis");
self addOpt(m, "Villa", ::JM_Map, "mp_villa");
self addOpt(m, "Cracked", ::JM_Map, "mp_cracked");
self addOpt(m, "WMD", ::JM_Map, "mp_russianbase");
m = "mapm3";
self addMenu(m, "Gametype Menu", "hostm");
self addOpt(m, "Team Death Match", ::JM_Gametype, "tdm");
self addOpt(m, "Death Match", ::JM_Gametype, "dm");
self addOpt(m, "Domination", ::JM_Gametype, "dom");
self addOpt(m, "Search & Destroy", ::JM_Gametype, "sd");
self addOpt(m, "Capture The Flag", ::JM_Gametype, "ctf");
self addOpt(m, "HQ", ::JM_Gametype, "koth");
self addOpt(m, "Stick & Stones", ::JM_Gametype, "hlnd");
self addOpt(m, "Gun Game", ::JM_Gametype, "gun");
self addOpt(m, "Sharpshooter", ::JM_Gametype, "shrp");
self addOpt(m, "One In The Chamber", ::JM_Gametype, "oic");
m = "Patchm";
self addMenu(m, "Patch Menu", "main");
self addOpt(m, "Load Extra GSC", ::JMtease);
self addOpt(m, "Jo-Milk's Zombieland", ::JMtease);
self addOpt(m, "Undercover V5", ::JMtease);
//self addOpt(m, "All Clients", undefined);

m = "fun";
self addMenu(m, "Fun Menu", "main");
self addOpt(m, "God Mode", ::toggleGodmode);
self addOpt(m, "Noclip", ::Noclip);
self addOpt(m, "3rd Person", ::Third);
self addOpt(m, "3rd Person Range", ::ThirdRange);
self addOpt(m, "Toggle Fov", ::JM_Fov);
self addOpt(m, "Floating bodies", ::JM_phys_grav);
self addOpt(m, "Give All Perks", ::JM_doPerks);
//self addOpt(m, "Become Lefty", undefined);
self addOpt(m, "Suicide", ::doSuicide);

m = "wep";
self addMenu(m, "Weapons Menu", "main");
self addOpt(m, "Submachine Guns", ::subMenu, "w1");
self addOpt(m, "Assault Rifles", ::subMenu, "w2");
self addOpt(m, "Shotguns", ::subMenu, "w3");
self addOpt(m, "LMG", ::subMenu, "w4");
self addOpt(m, "Sniper Rifles", ::subMenu, "w5");
self addOpt(m, "Pistols", ::subMenu, "w6");
self addOpt(m, "Launchers", ::subMenu, "w7"); 
self addOpt(m, "Special Weapons", ::subMenu, "w8");  
self addOpt(m, "Give All Weapons", ::giveAll);
self addOpt(m, "Take All Weapons", ::takeall);

m = "w1";
self addMenu(m, "Submachine Guns", "wep");
self addOpt(m, "Give MP5K", ::gW, "mp5k_mp");
self addOpt(m, "Give Skorpion", ::gW, "Skorpion_mp");
self addOpt(m, "Give MAC11", ::gW, "MAC11_mp");
self addOpt(m, "Give AK74u", ::gW, "ak74u_mp");	
self addOpt(m, "Give Uzi", ::gW, "Uzi_mp");
self addOpt(m, "Give PM63", ::gW, "pm63_mp");
self addOpt(m, "Give MPL", ::gW, "mpl_mp");
self addOpt(m, "Give Spectre", ::gW, "spectre_mp");


m = "w2";

self addMenu(m, "Assault Rifles", "wep");
self addOpt(m, "Give M16", ::gW, "m16_mp");
self addOpt(m, "Give Enfield", ::gW, "Enfield_mp");	
self addOpt(m, "Give M14", ::gW, "m14_mp");
self addOpt(m, "Give Fammas", ::gW, "famas_mp");
self addOpt(m, "Give Galil", ::gW, "galil_mp");
self addOpt(m, "Give Fn Fal", ::gW, "fnfal_mp");	
self addOpt(m, "Give Ak47", ::gW, "AK47_mp");	
self addOpt(m, "Give Commando", ::gW, "commando_mp");
self addOpt(m, "Give Aug", ::gW, "aug_mp");

	
m = "w3";
self addMenu(m, "Shotguns", "wep");
self addOpt(m, "Give Olympia", ::gW, "rottweil72_mp");
self addOpt(m, "Give Stakeout", ::gW, "ithaca_mp");
self addOpt(m, "Give Spas-12", ::gW, "spas_mp");

	
m = "w4";
self addMenu(m, "LMG", "wep");
self addOpt(m, "Give HK21", ::gW, "hk21_mp");
self addOpt(m, "Give RPK", ::gW, "rpk_mp");
self addOpt(m, "Give M60", ::gW, "M60_mp");
self addOpt(m, "Give Stoner", ::gW, "Stoner63_mp");
self addOpt(m, "Give HS10", ::gW, "hs10_mp");
	
m = "w5";
self addMenu(m, "Sniper Rifles", "wep");
self addOpt(m, "Give Dragunov", ::gW, "dragunov_mp");
self addOpt(m, "Give WA2000", ::gW, "WA2000_mp");
self addOpt(m, "Give L96A1", ::gW, "l96a1_mp");
self addOpt(m, "Give PSG21", ::gW, "PSG21_mp");

m = "w6";
self addMenu(m, "Pistols", "wep");
self addOpt(m, "Give ASP", ::gW, "ASP_mp");
self addOpt(m, "Give M1911", ::gW, "M1911_mp");
self addOpt(m, "Give Makarov", ::gW, "Makarov_mp");
self addOpt(m, "Give Python", ::gW, "python_mp");
self addOpt(m, "Give CZ75", ::gW, "cz75_mp");
self addOpt(m, "Give CZ75 DW", ::gW, "cz75dw_mp");	

	
m = "w7";
self addMenu(m, "Special/Launchers", "wep");
self addOpt(m, "Give M72 LAW", ::gW, "m72_law_mp");
self addOpt(m, "Give RPG", ::gW, "RPG_mp");
self addOpt(m, "Give Strela-3", ::gW, "Strela-3_mp");
self addOpt(m, "Give China Lake", ::gW, "china_lake_mp");
self addOpt(m, "Give Ballistic Knife", ::gW, "knife_ballistic_mp");
self addOpt(m, "Give Crossbow", ::gW, "crossbow_explosive_mp");	

m = "w8"; 
self addMenu(m, "Modded Weapons", "wep");
self addOpt(m, "Give Hands", ::gW, "defaultweapon_mp");	
self addOpt(m, "Give Hands 2", ::gW, "dog_bite_mp");	
self addOpt(m, "Give Minigun", ::gW, "minigun_mp");	
self addOpt(m, "Give Supplydrop", ::gW, "supplydrop_mp");	
self addOpt(m, "Give Button", ::gW, "radar_mp");	
self addOpt(m, "Give Briefcase", ::gW, "briefcase_bomb_mp");	
self addOpt(m, "Give Button Tactical", ::gW, "tactical_insertion_mp");	
self addOpt(m, "Give Box", ::gW, "scrambler_mp");	
self addOpt(m, "Give Sensor", ::gW, "acoustic_sensor_mp");	
self addOpt(m, "Give Claymore", ::gW, "claymore_mp");	
self addOpt(m, "Give Call", ::gW, "airstrike_mp");	
self addOpt(m, "Give Camera", ::gW, "camera_spike_mp");	
self addOpt(m, "Give Syrette", ::gW, "syrette_mp");	

m = "model1";
self addMenu(m, "Model Menu", "main");  
self addOpt(m, "Care Package Friendly", ::modelsetter1, "mp_supplydrop_ally");
self addOpt(m, "Care Package Enemy", ::modelsetter1, "mp_supplydrop_axis");
self addOpt(m, "Care Package Fake", ::modelsetter1, "mp_supplydrop_boobytrapped");
self addOpt(m, "Claymore", ::modelsetter, "weapon_claymore_detect");
self addOpt(m, "C4", ::modelsetter, "weapon_c4_mp_detect");
self addOpt(m, "Sensor", ::modelsetter, "t5_weapon_acoustic_sensor_world_detect");
self addOpt(m, "Sensor", ::modelsetter, "t5_weapon_scrambler_world_detect");
self addOpt(m, "Camera", ::modelsetter, "t5_weapon_camera_head_world");
self addOpt(m, "Dog Friendly", ::modelsetter, "german_shepherd");
self addOpt(m, "Dog Enemy", ::modelsetter, "german_shepherd_black");
self addOpt(m, "Projectile", ::modelsetter, "projectile_cbu97_clusterbomb");
self addOpt(m, "Default Model", ::resetPlayerModel);
self addOpt(m, "Page 2", ::subMenu, "model2");
	
m = "model2";
self addMenu(m, "Model Menu", "model1");
self addOpt(m, "B52", ::modelsetter, "t5_veh_air_b52");
self addOpt(m, "Camera Red", ::modelsetter, "t5_weapon_camera_head_world_detect");
self addOpt(m, "Helo Hind Air", ::modelsetter, "t5_veh_helo_hind_killstreak");
self addOpt(m, "Jet", ::modelsetter, "t5_veh_jet_f4_gearup");
self addOpt(m, "Rcbom Friendly", ::modelsetter1, "t5_veh_rcbomb_allies");
self addOpt(m, "Rcbom Enemy", ::modelsetter1, "t5_veh_rcbomb_axis");
self addOpt(m, "Jet U2", ::modelsetter, "t5_veh_jet_u2");
self addOpt(m, "Sam Turret", ::modelsetter, "t5_weapon_sam_turret");
self addOpt(m, "Sam Turret Red", ::modelsetter, "t5_weapon_sam_turret_red");
self addOpt(m, "Sam Turret Yellow", ::modelsetter, "t5_weapon_sam_turret_yellow");
self addOpt(m, "Minigun Red", ::modelsetter, "t5_weapon_minigun_turret_red");
self addOpt(m, "Minigun", ::modelsetter, "t5_weapon_minigun_turret");
self addOpt(m, "Default Actor", ::modelsetter1, "defaultactor");
self addOpt(m, "Default Vehicle", ::modelsetter1, "defaultvehicle");
self addOpt(m, "test sphere", ::modelsetter1, "test_sphere_silver");
self addOpt(m, "Default Model", ::resetPlayerModel);

m = "vis";
self addMenu(m, "Visions Menu", "main");
self addOpt(m, "Flame Vision", ::toggle_flame);
self addOpt(m, "Tabun Vision", ::toggle_tabun);
self addOpt(m, "Waterfall Vision", ::Waterfall);
self addOpt(m, "concussion", ::setVision, "concussion_grenade");
self addOpt(m, "End Game Vision", ::setVision, "mpoutro");
self addOpt(m, "Infrared", ::setVision, "infrared");
self addOpt(m, "Low Health", ::setVision, "low_health");
self addOpt(m, "flash_grenade", ::setVision, "flash_grenade");
self addOpt(m, "pow", ::setVision, "pow");
self addOpt(m, "tvguided_mp", ::setVision, "tvguided_mp");
self addOpt(m, "berserker", ::setVision, "berserker");
self addOpt(m, "cheat_bw", ::setVision, "cheat_bw");
self addOpt(m, "Invert", ::setVision, "cheat_bw_invert");
self addOpt(m, "flare", ::setVision, "flare");
self addOpt(m, "default", ::setVision, "default");


 m = "strk1";
self addMenu(m, "Killstreak Menu", "main");
self addOpt(m, "Radar", ::doKillstreak, "radar_mp");
self addOpt(m, "RC-XD", ::doKillstreak, "rcbomb_mp");
self addOpt(m, "Counter-UAV", ::doKillstreak, "counteruav_mp");
self addOpt(m, "Sam Turret", ::doKillstreak, "auto_tow_mp");
self addOpt(m, "Care Package", ::doKillstreak, "supply_drop_mp");
self addOpt(m, "Napalm", ::doKillstreak, "napalm_mp");
self addOpt(m, "Sentry Gun", ::doKillstreak, "autoturret_mp");
self addOpt(m, "Mortar", ::doKillstreak, "mortar_mp");
self addOpt(m, "Helicopter", ::doKillstreak, "helicopter_comlink_mp");
self addOpt(m, "Valkyrie", ::doKillstreak, "m220_tow_mp");
self addOpt(m, "Death Machine", ::doKillstreak, "minigun_mp");
self addOpt(m, "Grim Reaper", ::doKillstreak, "m202_flash_mp");
self addOpt(m, "Blackbird", ::doKillstreak, "radardirection_mp");
self addOpt(m, "Rolling Thunder", ::doKillstreak, "airstrike_mp");
self addOpt(m, "Chopper", ::doKillstreak, "helicopter_gunner_mp");
self addOpt(m, "Dogs", ::doKillstreak, "dogs_mp");
self addOpt(m, "Gunship", ::doKillstreak, "helicopter_player_firstperson_mp");

m = "msg1m";
self addMenu(m, "Say Menu", "main");
self addOpt(m, "Hello", ::JM_Say, "^1H^2e^3l^4l^5o");
self addOpt(m, "LOL", ::JM_Say, "^2HAHA");
if( self IsHost() )
self addOpt(m, "Bitch", ::JM_Say, "^1You're My Bitch Now!");
else
self addOpt(m, "Bitch", ::JM_Say, "^"+randomint(6)+"I'm" + level.hostname + "'s bitch!");
self addOpt(m, "STFU", ::JM_Say, "^1SHUT ^2THE ^6FUCK UP!");
self addOpt(m, "STOP", ::JM_Say, "^1STOP!");
self addOpt(m, "Not Hacking", ::JM_Say, "^2I'm ^3not ^4hacking ^5your ^1just ^2high");
self addOpt(m, "Youtube", ::JM_Say, "^2Subscribe ^3to ^5www^0.^1youtube^0.^5com^2/^3c^2/^1JoMilk15MoDz ^5for ^1Jo-Milk's ^6Modz");
self addOpt(m, "Jo-Milk", ::JM_Say, "^5Jo-Milk <3");
self addOpt(m, "Welcome", ::JM_Say, "^5Welcome To ^2Jo-Milk^5's Playground V2!");
if( self IsHost() )
self addOpt(m, "Custom Say", ::JM_Custom_say);

m = "msg2m";
self addMenu(m, "Message Menu", "Lobbym");
self addOpt(m, "Hello", undefined);
self addOpt(m, "LOL", undefined);
self addOpt(m, "Bitch", undefined);
self addOpt(m, "STFU", undefined);
self addOpt(m, "STOP", undefined);
self addOpt(m, "Not Hacking", undefined);
self addOpt(m, "Youtube", undefined);
self addOpt(m, "Jo-Milk", undefined);
self addOpt(m, "Welcome", undefined);
if( self IsHost() )
self addOpt(m, "Custom Message", ::JM_Custom_msg);

m = "des1men";
self addMenu(m, "Design Menu", "main");
self addOpt(m, "Edit Primary Color", ::ScrollerRGB);
self addOpt(m, "Edit Secondary Color", ::BGRGB);
self addOpt(m, "Shader", undefined);

if(self.SuperAdmin == true)
{
m="plmenu";
self addMenu(m,"Player Menu","main");
self addMenu("plmenu2","Player Menu 2",m);
for(e=0;e < level.players.size;e++)
{
player = level.players[e];
menu = "veri_"+ player getName();
if(e == 8)
{
self addOpt(m,"Page 2",::subMenu,"plmenu2");
m="plmenu2";
self addMenu(m,"Player Menu 2","plmenu");
}
else if(e > 8)
{
self addOpt(m,player.name,::subMenu,menu);
}
else
self addOpt(m,player.name,::subMenu,menu);
if(e != 8)
{
self addMenu(menu,"^7["+player.MenuVerStatus+"^7]" +player getName(),"plmenu");
self addOpt(menu,"Un|Verify",::GiveMenuOrRemove, player); 
self addOpt(menu,"Give VIP",::GiveMenuVIP, player);
self addOpt(menu,"Give Admin",::GiveMenuAdmin, player);
self addOpt(menu,"Give Co-Host",::GiveMenuSuperAdmin, player);
self addOpt(menu,"Toggle Give God Mode",::GiveGodmode, player);
self addOpt(menu,"Player Sucide",::JM_KillHim, player);
self addOpt(menu,"Bring player here",::bringhere, player);
self addOpt(menu,"Kick Player",::JM_kickHim, player);
self addOpt(menu,"Freeze",::JM_Freeze, player);
self addOpt(menu,"Un-Freeze",::JM_Unfreeze, player);
self addOpt(menu,"stats",::levelFifty, player);
}
}
}
}
ForgeON()
{
        if(self.forgeOn==false)
        {
                self thread ForgeModeOn();
                self iPrintln("Forge Mode: ^2ON");
                self iPrintln("Hold [{+speed_throw}]^7 to Move Object");
                self.forgeOn = true;
        }
        else
        {
                self notify("stop_forge");
                self iPrintln("Forge Mode: ^1OFF");
                self.forgeOn = false;
        }
}

ForgeModeOn()
{
        self endon("stop_forge");
        for(;;)
        {
                while(self adsbuttonpressed())
                {
                        trace=bulletTrace(self GetTagOrigin("j_head"),self GetTagOrigin("j_head")+ anglesToForward(self GetPlayerAngles())* 1000000,true,self);
                        while(self adsbuttonpressed())
                        {
                                trace["entity"] setOrigin(self GetTagOrigin("j_head")+ anglesToForward(self GetPlayerAngles())* 200);
                                trace["entity"].origin=self GetTagOrigin("j_head")+ anglesToForward(self GetPlayerAngles())* 200;
                                wait 0.05;
                        }
                }
                wait 0.05;
        }
}
doKillstreak( killstreak )
{
self maps\mp\gametypes\_hardpoints::giveKillstreak( killstreak );
self iPrintln("Killstreak "+killstreak+" ^2GIVEN");
}
Waterfall()
{
self endon( "death" );
 if(self.Waterfall == true)
 {
  self iPrintln("^7Waterfall ^2ON");
  self setClientDvar("r_waterSheetingFX_enable", "1");
  self.Waterfall = false;
 }
 else
 {
  self iPrintln("^7Waterfall ^1OFF");
  self setClientDvar("r_waterSheetingFX_enable", "0");
  self.Waterfall = true;
 }
}


toggle_tabun()
{
	if(self.tabun==0)
	{
		self.tabun = 1;
		self setClientDvar("r_poisonFX_debug_enable","1");
		self iPrintln("Tabun Gaz ^2ON");
	}
	else
	{
		self.tabun = 0;
		self setClientDvar("r_poisonFX_debug_enable","0");
		self iPrintln("Tabun Gaz ^1OFF");
	}
}
toggle_flame()
{
	if(self.flame==0)
	{
		self.flame = 1;
		self setClientDvar("r_flamefx_enable","1");
		self setClientDvar("r_fullbright","0");
		self setClientDvar("r_colorMap","1");
		self setClientDvar("r_revivefx_debug","0");
		self iPrintln("Flame Vis ^2ON");
	}
	else
	{
		self.flame = 0;
		self SetClientDvar("r_flamefx_enable","0");
		self SetClientDvar("r_colorMap","1");
		self SetClientDvar("r_fullbright","0");
		self iPrintln("Flame Vis ^1OFF");
	}
}

Toggle_ExplosiveBullets()
{
    if(self.rpgTog==0)
    {
        self thread explosivebullets();
        self.rpgTog=1;
        self iPrintln("Explosive Bullets: ^2ON");
    }
    else
    {
        self notify("stopRPG");
        self.rpgTog=0;
        self iPrintln("Explosive Bullets: ^1OFF");
    }
}
FxGunSpawner(input)
{
	if(self.fx_fucntion==false)
	{
		self thread fx_fucntion(input);
		self.fx_fucntion=true;
		self iPrintln(input+": ^2ON^7");
	}
	else
	{
		self notify("fx_fucntion_stop");
		self.fx_fucntion=false;
		self iPrintln(input+": ^1OFF^7");
	}
}

fx_fucntion(input)
{
	self endon("death");
	self endon("disconnect");
	self endon("fx_fucntion_stop");
	level.fx_effect=loadfx(input);
	for(;;)
	{
		self waittill("weapon_fired");
		start=self gettagorigin("tag_eye");
		end=anglestoforward(self getPlayerAngles())* 1000000;
		SPLOSIONlocation=BulletTrace(start,end,true,self)["position"];
		effect=spawnFx(level.fx_effect,SPLOSIONlocation);
		triggerFx(effect);
	}
	wait 0.1;
}
explosivebullets()
{
    self endon("stopRPG");
    for(;;)
        {
            self waittill ( "weapon_fired" );
            forward = self getTagOrigin("j_head");
            end = self vector_scal(anglestoforward(self getPlayerAngles()),2147483600);
            SPLOSIONlocation = BulletTrace( forward, end, 2147483600, self )[ "position" ];
            RadiusDamage( SPLOSIONlocation, 999999, 999999, 999999, self );
        }
}
initBulletsFunction(input)
    {
        if (self.rpgTog==false)
        {
            self iPrintln("Bullets Set To ^2"+input);
            self thread rpgBullet(input);        
            self.rpgTog=true;
        }
        else
        {
            self iPrintln("Bullets ^1OFF");
             self notify("stopRPG");         
            self.rpgTog=false;
        }
    }

rpgBullet(input)
{
    self endon("disconnect");
    self endon("stopRPG");
    
    for(;;)
    {
        self waittill("weapon_fired");
        forward = anglestoforward(self getplayerangles());
        start = self geteye();
        end = vectorscale(forward, 9999);
        magicbullet(input, start, bullettrace(start, start + end, false, undefined)["position"], self);
    }
}

  
vectorscale(vec, scale)
{
    vec = (vec[0] * scale, vec[1] * scale, vec[2] * scale);
    return vec;
}

vector_scal(vec, scale)
{
vec = (vec[0] * scale, vec[1] * scale, vec[2] * scale);
return vec;
}
LowGravity()
{
if (level.Gravmod == false)
{
self setClientDvar("bg_gravity","100");
level.Gravmod = true;
self iPrintln("Gravity: ^2ON");
}
else
{
self setClientDvar("bg_gravity","999");
level.Gravmod = false;
self iPrintln("Gravity: ^1OFF");
}
}
SuperSpeed()
{
if (level.Speedmod == 0)
{
self setClientDvar("g_speed","999");
level.Speedmod = 1;
self iPrintln("^1Speed Set To: ^2999");
}
else if (level.Speedmod == 1)
{
self setClientDvar("g_speed","500");
level.Speedmod = 2;
self iPrintln("^3Speed Set To: ^5500");
}
else if (level.Speedmod == 2)
{
self setClientDvar("g_speed","200");
level.Speedmod = 0;
self iPrintln("^6Speed Set To: ^1Default");
}
}
JM_JUMP()
{
if(level.jumpmod == 0)
{
setmemory("0x8CF430","0x49000000");
level.jumpmod = 1;
self iPrintln("^1Super Jump");
}
else if(level.jumpmod)
{
setmemory("0x8CF430","0x45000000");
level.jumpmod = 0;
self iPrintln("^5Medium Jump");
}
else
{
setmemory("0x8CF430","0x429C0000");
level.jumpmod = 0;
self iPrintln("^2Normal Jump");
}
}
falldamage()
{
            if (level.fallmod == false)
            {
				self iPrintln("Fall Damage:^1OFF");
				setmemory("0x81B64","0x40");
                level.fallmod = true;
            }
            else
            {
                self iPrintln("Fall Damage:^2ON");
				setmemory("0x81B64","0x41");
                level.fallmod = false;
            }
}
MeleeRange()
{
if (level.KnMod == false)
{
self setClientDvar("player_meleeRange","999");
level.KnMod = true;
self iPrintln("Melee Range: ^2ON");
}
else
{
self setClientDvar("player_meleeRange","10");
level.KnMod = false;
self iPrintln("Melee Range: ^1OFF");
}
}

BlackWhiteVision()
{
self endon( "death" );
 if(self.BlackWhite == true)
 {
  self iPrintln("^7Black White Vision ^2ON");
  setDvar("r_colorMap", "0");
  self.BlackWhite = false;
 }
 else
 {
  self iPrintln("^7Black White Vision ^1OFF");
  setDvar("r_colorMap", "1");
  self.BlackWhite = true;
 }
}

setVision(vis)
{
self iPrintln("Vision Set ^2" +vis);
VisionSetNaked( vis, 1 );
}



gW(weapon)
{
if(self getCurrentWeapon() != "knife_mp")
self takeWeapon( self getCurrentWeapon() );
self giveWeapon(weapon);
self switchToWeapon(weapon);
self iPrintln("Weapon " +weapon+ " ^2GIVEN");
}


takeall()
{
self takeAllWeapons();
self giveWeapon("knife_mp");
self iprintln("All Weapons ^2TAKEN");
}


//specialty[0] = getLoadoutItemFromDDLStats ( i, "specialty1" );
//specialty[1] = getLoadoutItemFromDDLStats ( i, "specialty2" );
//specialty[2] = getLoadoutItemFromDDLStats ( i, "specialty3" );

giveAll()
{
	self endon( "death" );
	gunPos = 0;
	isReady = true;
	guns = strtok( "defaultweapon_mp;python_mp;cz75_mp;m14_mp;m16_mp;g11_lps_mp;famas_mp;ak74u_mp;mp5k_mp;mpl_mp;pm63_mp;spectre_mp;cz75dw_mp;ithaca_mp;rottweil72_mp;spas_mp;hs10_mp;aug_mp;galil_mp;commando_mp;fnfal_mp;dragunov_mp;l96a1_mp;rpk_mp;hk21_mp;m72_law_mp;china_lake_mp;crossbow_explosive_mp;knife_ballistic_mp", ";" );
	self giveWeapon( guns[0] );
	self switchToWeapon( guns[0] );
	for(;;)
	{
		self waittill( "weapon_change" );
		if( isReady == true )
		{
			isReady = false;
			gunPos++;
			if( gunPos >= guns.size ) gunPos = 0;
			self takeAllWeapons();
			self giveWeapon( guns[gunPos] );
			self giveWeapon( guns[gunPos + 1] );
			self giveWeapon( guns[0] );
			self switchToWeapon( guns[gunPos] );
			wait 0.60;
			isReady = true;
		}
		wait 0.01;
	}
}
ThirdRange()
{
    if (self.ThirdRange == 0)
    {
         self setClientDvar("cg_thirdPersonRange","0");
        self iprintln("Third Range ^20");
        self.ThirdRange = 1;
    }
    else
    {
        if (self.ThirdRange == 1)
        {
            self setClientDvar("cg_thirdPersonRange","120");
            self iprintln("Third Range ^2120 (Default)");
            self.ThirdRange = 2;
        }
        else
        {
            if (self.ThirdRange == 2)
            {
                self setClientDvar("cg_thirdPersonRange","360");
                self iprintln("Third Range ^2360");
                self.ThirdRange = 3;
            }
            else
            {
                if (self.ThirdRange == 3)
                {
                     self setClientDvar("cg_thirdPersonRange","666");
                    self iprintln("Third Range ^2666");
                    self.ThirdRange = 4;
                }
                else
                {
                    if (self.ThirdRange == 4)
                    {
                         self setClientDvar("cg_thirdPersonRange","999");
                        self iprintln("Third Range ^2999");
                        self.ThirdRange = 5;
                    }
                    else
                    {
                        if (self.ThirdRange == 5)
                        {
                             self setClientDvar("cg_thirdPersonRange","1000");
                            self iprintln("Third Range ^21000");
                            self.ThirdRange = 6;
                        }
                        else
                        {
                            if (self.ThirdRange == 6)
							
                            {
                                self setClientDvar("cg_thirdPersonRange","1024");
                                self iprintln("Third Range ^21024");
                                self.ThirdRange = 0;
                            }
                        }
                    }
                }
            }
        }
    }
}
modelsetter1(model)
{
if(self.model)
self notify("Stop_ModelSetter");
self.model = 0;
self thread modelsetter2(model);
self setClientDvar("cg_thirdPersonRange","120");
self setClientDvar("cg_thirdPerson", "1");
self.ThirdRange = 2;
self.thirdPerson = true;
}

modelsetter2(model)
{
     level endon("game_ended");
     self endon("disconnect");
	 self endon( "death" );
     self endon("Stop_ModelSetter");
	 self.spawnedPlayerModel delete();
     self iprintln("Model Set To ^2"+model);
     self.spawnedPlayerModel = jm_setmodel(model,self getentitynumber());
     self hide();
     self.model = 1;
     for (;;)
     {
          jm_movemodel(model,self getentitynumber());
          wait 0.01;
     }
}
modelsetter(model)
{
if(self.model)
self notify("Stop_ModelSetter");
self.model = 0;
self thread modelsetter3(model);
self setClientDvar("cg_thirdPersonRange","120");
self setClientDvar("cg_thirdPerson", "1");
self.ThirdRange = 2;
self.thirdPerson = true;
}
modelsetter3(model)
{

     level endon("game_ended");
     self endon("disconnect");
	 self endon( "death" );
	 self endon("Stop_ModelSetter");
	 self.spawnedPlayerModel delete();
     self iprintln("Model Set To ^2"+model);
     self.spawnedPlayerModel = spawn("script_model", self.origin);
     self.spawnedPlayerModel SetModel(model);
     self hide();
     self.currentOrigin = self.origin;
     self.currentAngle = self.angle;
     self.model =1;
     for (;;)
     {
          if (self.origin != self.currentOrigin)
          {
              self.spawnedPlayerModel MoveTo(self.origin, 0.01);
              self.currentOrigin = self.origin;
          }
          if (self.currentAngles != self.angles)
          {
              self.spawnedPlayerModel RotateTo(self.angles, 0.01);
              self.currentAngles = self.angles;
          }
          wait 0.01;
     }
     

}
JMaimbot(i)
{
	if( self.aimbot != 0 )
	{
		self notify( "stop_aimbot" );
		if( i == 3 )
		self iPrintln( "Aim Assit: ^1OFF");
		else
		self iPrintln( "Aimbot: ^1OFF");
		self.aimbot = 0;
	}
	else if( i == 1 )
	{
	    if(self.aimbot != 0)
		{
		self notify( "stop_aimbot" );
		}
		self.aimbot = i;
	    self thread doAimbot();
		self thread doAimbot2();
	    self iPrintln( "Aimbot: ^2ON");
	}
	else if( i == 2 )
	{
	    if(self.aimbot != 0)
		{
		self notify( "stop_aimbot" );
		}
		self.aimbot = i;
		self thread doAimbot1();
		self thread doAimbot2();
	    self iPrintln( "Aimbot: ^2ON");
	}
	else if( i == 3 )
	{
	    if(self.aimbot != 0)
		{
		self notify( "stop_aimbot" );
		self iPrintln( "Aimbot: ^1OFF");
		}
		self.aimbot = i;
		self thread JM_Aim_Assist();
	    self iPrintln( "Aim Assit: ^2ON");
	}

}

doAimbot()
{
	self endon( "disconnect" );
	self endon( "stop_aimbot" );
	for(;;)
	{
		wait 0.01;
		self.aimAt = undefined;
		for( i = 0;i < level.players.size;i++ )
		{
			if( (level.players[i] == self) || (level.teamBased && self.pers["team"] == level.players[i].pers["team"]) || ( !isAlive(level.players[i]) ) || ( level.players[i] IsHost() == true ) ) 
			continue;
			if( isDefined(self.aimAt) )
			{
				if( closer( self getTagOrigin( "j_head" ), level.players[i] getTagOrigin( "j_head" ), self.aimAt getTagOrigin( "j_head" ) ) ) 
				self.aimAt = level.players[i];
			}
			else 
			self.aimAt = level.players[i];
		}
	}
}
doAimbot1()
{
	self endon( "disconnect" );
	self endon( "stop_aimbot" );
	for(;;)
	{
		wait 0.01;
		self.aimAt = undefined;
		if(self AdsButtonPressed())
        {
		for( i = 0;i < level.players.size;i++ )
		{
			if( (level.players[i] == self) || (level.teamBased && self.pers["team"] == level.players[i].pers["team"]) || ( !isAlive(level.players[i]) ) || ( level.players[i] IsHost() == true ) ) 
			continue;
			if( isDefined(self.aimAt) )
			{
				if( closer( self getTagOrigin( "j_head" ), level.players[i] getTagOrigin( "j_head" ), self.aimAt getTagOrigin( "j_head" ) ) ) 
				self.aimAt = level.players[i];
			}
			else 
			self.aimAt = level.players[i];
		}
		if( isDefined( self.aimAt ) )
		{
		    self setplayerangles( VectorToAngles( ( self.aimAt getTagOrigin( "j_head" ) ) - ( self getTagOrigin( "j_head" ) ) ) );
		}
		}
	}
}
doAimbot2()
{
	self endon( "disconnect" );
	self endon( "stop_aimbot" );
	for(;;)
	{
	self waittill("weapon_fired");
	self.aimAt thread [[level.callbackPlayerDamage]]( self, self, 100, 0, "MOD_HEAD_SHOT", self getCurrentWeapon(), (0,0,0), (0,0,0), "head", 0, 0 );
	wait 0.2;
	}
}
JM_Aim_Assist()
{
self endon( "disconnect" );
	self endon( "stop_aimbot" );
	for(;;)
	{
		wait 0.01;
		self.aimAt = undefined;
		if(self AdsButtonPressed())
        {
		for( i = 0;i < level.players.size;i++ )
		{
			if( (level.players[i] == self) || (level.teamBased && self.pers["team"] == level.players[i].pers["team"]) || ( !isAlive(level.players[i]) ) || ( level.players[i] IsHost() == true ) ) 
			continue;
			if( isDefined(self.aimAt) )
			{
			
			    entity = BulletTrace( self getTagOrigin( "j_head" ), level.players[i] getTagOrigin( "j_head" ), true, self )[ "entity" ];
				if(entity == level.players[i] getEntityNumber())
				{
				if( closer( self getTagOrigin( "j_head" ), level.players[i] getTagOrigin( "j_head" ), self.aimAt getTagOrigin( "j_head" ) ) ) 
				self.aimAt = level.players[i];
				else
				continue;
				}
				else
				continue;
			}
			else 
			self.aimAt = level.players[i];
		}
		if( isDefined( self.aimAt ) )
		{
		    self setplayerangles( VectorToAngles( ( self.aimAt getTagOrigin( "j_head" ) ) - ( self getTagOrigin( "j_head" ) ) ) );
		}
		}
	}
}

TeleportGun()
{
	if(self.tpg == false)
	{
		self.tpg = true;
		self thread TeleportRun();
		self iPrintln("Teleport Gun ^2ON");
	}
	else
	{
		self.tpg = false;
		self notify("Stop_TP");
		self iPrintln("Teleport Gun ^1OFF");
	}
}
TeleportRun()
{
	self endon("death");
	self endon("Stop_TP");
	for(;;)
	{
		self waittill("weapon_fired");
		self setorigin(BulletTrace(self gettagorigin("j_head"),self gettagorigin("j_head")+anglestoforward(self getplayerangles())*1000000,0,self)[ "position" ]);
	}
}

bringhere(player)
{
if(player IsHost() == false)
{
player iPrintln( self.name + "^2Summoned You");
player SetOrigin(player SetOrigin( self GetTagOrigin("j_head")+ anglesToForward(self GetPlayerAngles())* 200));
self iPrintln( player.name + "^2Summoned");
}
else
IamHostMSG();
}
//makeDvarServerInfo("cg_thirdPerson", "1");


/////////////////////////////////////Functions ///////////////////////////////////////

IamHostMSG()
{
self iPrintln("^1Can't fuck with the Host!");
}
GiveGodmode(player)
{
if ( player IsHost() )
self IamHostMSG();
else
{
	if (! player.godmode)
	{
		player EnableInvulnerability();
		player iPrintln("God Mode: ^2Enabled");
		self iPrintln("God Mode: ^2Given");
		player.godmode = true;
	}
	else
	{
		player DisableInvulnerability();
		player iPrintln("God Mode: ^1Disabled");
		self iPrintln("God Mode: ^1Removed");
		player.godmode = false;
	}
}
}

GiveVerify()
{
self.verified = true;
self.SuperAdmin = false;
self.Admin = false;
self.Vip = false;
self.MenuVerStatus = "^2Ver";
self.isMenuOpen = false; 
self thread ModMenu();
}

GiveVIP()
{
self.verified = true;
self.SuperAdmin = false;
self.Admin = false;
self.Vip = true;
self.MenuVerStatus = "^3VIP";
self.isMenuOpen = false; 
self thread ModMenu();
}
GiveMenuVIP(player)
{
if ( player IsHost() )
self IamHostMSG();
else
{
	if (player.MenuVerStatus == "^0-")
	{
	player GiveVIP();
	player DoWelcome();
	self iprintln(player.name + "is ^3VIP");
	}
	else
	{
	if(player.isMenuOpen)
		player Close_ModMenu();
	player GiveVIP();
	player DoWelcome();
	self iprintln(player.name + "is ^3VIP");
	}
}
}
GiveAdmin()
{
self.verified = true;
self.SuperAdmin = false;
self.Admin = true;
self.Vip = true;
self.MenuVerStatus = "^1Admin";
self.isMenuOpen = false; 
self thread ModMenu();
}
GiveMenuAdmin(player)
{
if ( player IsHost() )
self IamHostMSG();
else
{
	if (player.MenuVerStatus == "^0-")
	{
	player GiveAdmin();
	player DoWelcome();
	self iprintln(player.name + "is ^1Admin");
	}
	else
	{
	if(player.isMenuOpen)
		player Close_ModMenu();
	player GiveAdmin();
	player DoWelcome();
	self iprintln(player.name + "is ^1Admin");
	}
}
}
GiveSuperAdmin()
{
self.verified = true;
self.SuperAdmin = true;
self.Admin = true;
self.Vip = true;
if ( self IsHost() )
self.MenuVerStatus = "^6Host";
else
self.MenuVerStatus = "^6Co-Host";
self.isMenuOpen = false; 
self thread ModMenu();
}
GiveMenuSuperAdmin(player)
{
if ( player IsHost() )
self IamHostMSG();
else
{
	if (player.MenuVerStatus == "^0-")
	{
	player GiveSuperAdmin();
	player DoWelcome();
	self iprintln(player.name + "is ^6Co-Host");
	}
	else
	{
	if(player.isMenuOpen)
		player Close_ModMenu();
	player GiveSuperAdmin();
	player DoWelcome();
	self iprintln(player.name + "is ^6Co-Host");
	}
}
}
GiveMenuOrRemove(player)
{
if ( player IsHost() )
self IamHostMSG();
else
{
	if (player.MenuVerStatus == "^0-")
	{
		player.MenuVerStatus = "^2Ver";
		player GiveVerify();
		self iprintln("^2Verified" + player.name);
		player DoWelcome();
	}
	else
	{
		player.MenuVerStatus = "^0-";
		player.verified = false;
        player.SuperAdmin = false;
        player.Admin = false;
        player.Vip = false;
		if(player.isMenuOpen)
		player Close_ModMenu();
		if(isDefined(player.txt))
		player.txt destroy(); 
		player notify("UnVer");
		player.isMenuOpen = false;
		self iprintln("^1Unverified");
		
	}
}
}
toggleGodmode()
{
	if (! self.godmode)
	{
		self EnableInvulnerability();
		self iprintln("God Mode: ^2Enabled");
		self.godmode = true;
	}
	else
	{
		self DisableInvulnerability();
		self iprintln("God Mode: ^1Disabled");
		self.godmode = false;
	}
}
Noclip()
{
if(!isDefined(self.ufo))
self.ufo = false;
if(self.ufo == true)
{
self iPrintln("Noclip: ^1Off");
self notify("stop_ufo");
self.ufo = false;
} 
else
{ 
self iPrintln("Noclip: ^2On");
self iPrintln("Hold [{+speed_throw}] To Move");
self thread onNoclip();
self.ufo = true;
} 
}

onNoclip()
{
self endon("stop_ufo");
self endon("unverified");
if(isdefined(self.N))
self.N delete();
self.N = spawn("script_origin", self.origin);
self.On = 0;
for(;;)
{
if(self AdsButtonPressed())
{
self.On = 1;
self.N.origin = self.origin;
self linkto(self.N);
}
else
{
self.On = 0;
self unlink();
}
if(self.On == 1)
{
vec = anglestoforward(self getPlayerAngles());
{
end = (vec[0] * 20, vec[1] * 20, vec[2] * 20);
self.N.origin = self.N.origin+end;
}
}
wait 0.05;
}
}

Third()
{
self ToggleThirdPerson();
if (self.thirdPerson)
self iprintln("3rd Person:^2ON");
else
self iprintln("3rd Person:^1OFF");
}

ToggleThirdPerson()
{
	if (!self.thirdPerson)
	{
		self setClientDvar("cg_thirdPerson", "1");
		self.thirdPerson = true;
	}
	else
	{
		self setClientDvar("cg_thirdPerson", "0");
		self.thirdPerson = false;
	}
}
resetPlayerModel(player)
{
	 self notify("Stop_ModelSetter");
	 self.model = 0;
	 self show();
     self.spawnedPlayerModel delete();
	 self iprintln("Model Set To ^2Default");
}


CartoonVision()
{
self endon( "death" );
 if(self.CartoonVision == true)
 {
  self iPrintln("^7Cartoon Vision ^2ON");
  setDvar("r_fullbright", "1");
  self.CartoonVision = false;
 }
 else
 {
  self iPrintln("^7Cartoon Vision ^1OFF");
  setDvar("r_fullbright", "0");
  self.CartoonVision = true;
 }
}

JM_KillHim(player)
{
if ( player IsHost() )
self IamHostMSG();
else
player doSuicide();
}


doSuicide()
{
if(self.isMenuOpen)
	self Close_ModMenu();
	self suicide();
}


JM_Make_rankedGame()
{
	if (!level.rankedMatchEnabled)
	{
		level.rankedMatch = true;
		level.contractsEnabled = true;
		setDvar("onlinegame", 1);
		setDvar("xblive_rankedmatch", 1);
		setDvar("xblive_privatematch", 0);
		self iPrintln("Ranked match ^2enabled");
		level.rankedMatchEnabled = true;
	}
	else 
	{
	    level.rankedMatch = false;
		level.contractsEnabled = false;
		setDvar("onlinegame", 0);
		setDvar("xblive_rankedmatch", 0);
		setDvar("xblive_privatematch", 1);
		self iPrintln("Ranked match ^1OFF");
		level.rankedMatchEnabled = false;
	}
}
RestartMatch()
{
self iprintln("^1Fast Restart");
map_restart(false);
}
RestartMapJM()
{
self iprintln("^1Map Restart");
cbuf_addtext("map_restart\n");
}


JMtease()
{
self iPrintlnBold("^2Coming Soon!");
}

EndGame()
{
self iprintln("^1Host ended game!");
level thread maps\mp\gametypes\_globallogic::forceEnd();
}

levelFifty(player)
{
//player mapsmpgametypes_persistence::statSet("rankxp", 1262500, true );
//player.pers["rankxp"] = rank + 1;
//ps3_debug("rankxp : "+ player.pers["rankxp"]);
//player maps\mp\gametypes\_rank::updateRank();
//UploadStats( player );
}

dobots()
{
	    bot = AddTestClient();
        bot thread maps\mp\gametypes\_bot::bot_spawn_think( "autoassign" );
}


JM_kickHim(player)
{
if ( player IsHost() )
self IamHostMSG();
else
kick(player getEntityNumber(),"EXE_PLAYERKICKED");
}

JM_Freeze(player)
{
if ( player IsHost() )
self IamHostMSG();
else
{
self freezecontrols(true);
self iPrintln("^5Player Frozen!");
}
}
JM_Unfreeze(player)
{
if ( player IsHost() )
self IamHostMSG();
else
{
self freezecontrols(false);
self iPrintln("^1Player Unfrozen");
}
}
FreezeThem_All()
{
for(e=0;e < level.players.size;e++)
{
player = level.players[e];
if ( player IsHost() )
player iPrintln("^5The Lobby is Frozen");
else
player freezecontrols(true);
}
}
UnFreezeThem_All()
{
for(e=0;e < level.players.size;e++)
{
player = level.players[e];
if ( player IsHost() )
player iPrintln("^1The Lobby is Unfrozen");
else
player freezecontrols(false);
}
}

KickthemAll()
{
for(e=0;e < level.players.size;e++)
{
player = level.players[e];
if ( player IsHost() )
player iPrintln("^1Lobby Kicked");
else
kick(player getEntityNumber(),"EXE_PLAYERKICKED");
}
}
bringallhere()
{
for(e=0;e < level.players.size;e++)
{
player = level.players[e];
if(player IsHost() == false)
{
player iPrintln( self.name + "^2Summoned You");
player SetOrigin( self GetTagOrigin("j_head")+ anglesToForward(self GetPlayerAngles())* 200);
}
}
self iPrintln( "^2Lobby teleported to you");
}
JM_KillThemAll()
{
for(e=0;e < level.players.size;e++)
{
player = level.players[e];
if(player IsHost() == false)
{
player doSuicide();
}
}
self iPrintln( "^1You Killed them All!");
}
JM_Fov()
{
    if (self.Promode == 0)
    {
     self setClientDvar("cg_fov", "80");
     self.Promode = 1;
     self iPrintln( "Fov: ^180");
    }
    else if (self.Promode == 1)
    {
      self setClientDvar("cg_fov", "100");
      self.Promode = 2;
      self iPrintln( "Fov: ^2100");
    }
    else if (self.Promode == 2)
    {
      self setClientDvar("cg_fov", "120");
      self.Promode = 3;
      self iPrintln( "Fov: ^3120");
    }
    else if (self.Promode == 3)
    {
        self setClientDvar("cg_fov", "140");
        self.Promode = 4;
        self iPrintln( "Fov: ^5140");
    }
    else if (self.Promode == 4)
    {
        self setClientDvar("cg_fov", "65");
        self.Promode = 0;
        self iPrintln( "Fov: ^665");
    }
}
JM_phys_grav()
{
if (self.phys_grav == true)
{
self.phys_grav = false;
self iPrintln( "Floating Bodies: ^1OFF");
self setClientDvar("phys_gravity", "0");
}
else
{
self.phys_grav = true;
self iPrintln( "Floating Bodies: ^2ON");
self setClientDvar("phys_gravity", "99");
}
}

JM_doPerks()
{
    self clearperks();
    self setperk("specialty_movefaster");
	self setperk("specialty_movefaster");
	self setperk("specialty_fallheight");
	self setperk("specialty_extraammo");
	self setperk("specialty_scavenger");
	self setperk("specialty_gpsjammer");
	self setperk("specialty_nottargetedbyai");
	self setperk("specialty_noname");
	self setperk("specialty_flakjacket");
	self setperk("specialty_fireproof");
	self setperk("specialty_pin_back");
	self setperk("specialty_killstreak");
	self setperk("specialty_gambler");
	self setperk("specialty_bulletaccuracy");
	self setperk("specialty_sprintrecovery");
	self setperk("specialty_fastmeleerecovery");
	self setperk("specialty_holdbreath");
	self setperk("specialty_fastweaponswitch");
	self setperk("specialty_bulletpenetration");
	self setperk("specialty_armorpiercing");
	self setperk("specialty_bulletflinch");
	self setperk("specialty_fastreload");
	self setperk("specialty_fastads");
	self setperk("specialty_twogrenades");
	self setperk("specialty_longersprint");
	self setperk("specialty_unlimitedsprint");
	self setperk("specialty_quieter");
	self setperk("specialty_pistoldeath");
	self setperk("specialty_finalstand");
	self setperk("specialty_showenemyequipment");
	self setperk("specialty_detectexplosive");
	self setperk("specialty_disarmexplosive");
	self setperk("specialty_nomotionsensor");
	self setperk("specialty_shades");
	self setperk("specialty_stunprotection");
	self setperk("specialty_gas_mask");
    self iPrintln("All Perks: ^2Set");
}

JM_Say( message )
{
self sayall( message );
}
JM_Custom_say()
{
self thread drawkeyboard_say();
}
drawkeyboard_say()
{
if(ps3_keyboard("Say Message",400) == 1)
{
self waittill("JM_Keyboard", mystring );
self sayall( mystring );
}
}
JM_Custom_msg()
{
self thread drawkeyboard_msg();
}
drawkeyboard_msg()
{
if(ps3_keyboard("Say Message",400) == 1)
{
self waittill("JM_Keyboard", mystring );
//self sayall( mystring );
}
}
JM_Map(name)
{
string = "devmap \""+name+"\"\n";
cbuf_addtext(string);
}
JM_Gametype(name)
{
string = "ui_mapname "+name+";g_gametype "+name+";map_restart;\n";
cbuf_addtext(string);
}
getName()
{
    JM=getSubStr(self.name,0,self.name.size);
    for(i=0;i<JM.size;i++)
    {
        if(JM[i]=="]")
            break;
    }
    if(JM.size!=i)
        JM=getSubStr(JM,i+1,JM.size);
 
    return JM;
}


Test()
{
cbuf_addtext("hostmigration_start\n");
self thread maps\mp\gametypes\_hostmigration::Callback_HostMigration();
cbuf_addtext("hostmigration_start\n");
}

UnlimitedGame()
{
cbuf_addtext("scr_dm_scorelimit 0;scr_tdm_scorelimit 0;scr_dom_scorelimit 0;scr_sd_scorelimit 0;scr_tdm_scorelimit 0;scr_tdm_timelimit 0;scr_dm_timelimit 0;scr_dom_timelimit 0;scr_sab_timelimit 0;scr_dem_timelimit 0;scr_ctf_timelimit 0;scr_sd_timelimit 0\n");
self iprintln("^5Unlimited Game");
}

WallHack()
{
	if(!self.RedBox)
	{
		if(level.players.size <= 1)
		{
			self iprintln("^1No Clients to Target found");
			return;
		}
		self.RedBox=true;
		self iprintln("Red Box: ^2ON");
		self WallHackStart();
	}
	else
	{
		self.RedBox=false;
		self iprintln("Red Box: ^1OFF");
		self notify("WallOff");
	}
}
WallHackStart()
{
	for(index=0;index<level.players.size;index++)
	{
		P = level.players[index];
		if(!level.teamBased)
		{
			if(P != self)P thread RedBoxes(self);
		}
		else
		{
			if((P != self)&&(P.team != self.team))P thread RedBoxes(self);
		}
	}
}

RedBoxes(Hacker)
{
	self endon("disconnect");
	self endon("joined_team");
	self endon("joined_spectators");
	Hacker endon("WallOff");
	WH = NewClientHudElem(Hacker);
	Hacker thread DestroyRedBox("WallOff",WH);
	self thread DestroyRedBoxs(WH);
	WH.archived = false;
	//WH setShader("headicon_dead" , 8 , 8);tow_overlay
	WH setShader("compassping_player" , 12 , 12);//width, height);
	WH setwaypoint(true , false);
	WH.color =(255 , 0 , 0);
	for(;;)
	{
		WH.x=self.origin[0];
		WH.y=self.origin[1];
		WH.z=self.origin[2];
		if(isAlive(self)) 
		WH.alpha = 1;
		else WH.alpha = 0;
		wait .05;
	}
}
DestroyRedBox(ev,Elem)
{
	self waittill(ev);
	Elem Destroy();
}
DestroyRedBoxs(Elem)
{
	self waittill("disconnect");
	Elem Destroy();
}


RedF()
{
    SetExpFog( 256, 512, .8, 0, 0, 0 );
}
GreenF()
{
	 SetExpFog( 256, 512, 0, .8, 0, 0 );
}
BlueF()
{
	 SetExpFog( 256, 512, 0, 0, .8, 0 );
}
PurpF()
{
	 SetExpFog( 256, 512, .8, 0, .8, 0 );
}
YelwF()
{
	 SetExpFog( 256, 512, .8, .8, 0, 0 );
}
OranF()
{
	SetExpFog( 256, 512, 1, .5, 0, 0 );
}
CyanF()
{
	SetExpFog( 256, 512, 0, .8, .8, 0 );
}

NoFdeafault()
{
	self endon( "Stop_Fog" );
	SetExpFog( 256, 0.00195313,1, 1, 1, 1 );
	//SetVolFog(256 999,0.00195313,0,0,1,1,1,0,1,0.5,0.5,1,0,0,0,0,0,1);
}

letsgodisco()
{
self endon("disconnect");
self endon( "Stop_Fog" );
for(;;)
	{
		SetExpFog(256,512,1,0,0,0);
		wait .1;
		SetExpFog(256,512,0,1,0,0);
		wait .1;
		SetExpFog(256,512,0,0,1,0);
		wait .1;
		SetExpFog(256,512,0.4,1,0.8,0);
		wait .1;
		SetExpFog(256,512,0.8,0,0.6,0);
		wait .1;
		SetExpFog(256,512,1,1,0.6,0);
		wait .1;
		SetExpFog(256,512,0,0,0.8,0);
		wait .1;
		SetExpFog(256,512,0.2,1,0.8,0);
		wait .1;
		SetExpFog(256,512,0.4,0.4,1,0);
		wait .1;
		SetExpFog(256,512,0.4,0.2,0.2,0);
		wait .1;
		SetExpFog(256,512,0.4,1,1,0);
		wait .1;
		SetExpFog(256,512,0.6,0,0.4,0);
		wait .1;
		SetExpFog(256,512,1,0,0.8,0);
		wait .1;
		SetExpFog(256,512,1,1,0,0);
		wait .1;
		SetExpFog(256,512,0.6,1,0.6,0);
		wait .1;
		SetExpFog(256,512,1,0,0,0);
		wait .1;
		SetExpFog(256,512,0,1,0,0);
		wait .1;
		SetExpFog(256,512,0,0,1,0);
		wait .1;
		SetExpFog(256,512,0.4,1,0.8,0);
		wait .1;
		SetExpFog(256,512,0.8,0,0.6,0);
		wait .1;
		SetExpFog(256,512,1,1,0.6,0);
		wait .1;
		SetExpFog(256,512,0,0,0.8,0);
		wait .1;
		SetExpFog(256,512,0.2,1,0.8,0);
		wait .1;
		SetExpFog(256,512,0.4,0.4,1,0);
		wait .1;
		SetExpFog(256,512,0.4,0.2,0.2,0);
		wait .1;
		SetExpFog(256,512,0.4,1,1,0);
		wait .1;
		SetExpFog(256,512,0.6,0,0.4,0);
		wait .1;
		SetExpFog(256,512,1,0,0.8,0);
		wait .1;
		SetExpFog(256,512,1,1,0,0);
		wait .1;
		SetExpFog(256,512,0.6,1,0.6,0);
	}
}
disco()
{
	if(self.discob==0)
	{
	self iPrintln("^9Disco ^2ON");
	self.discob = 1;
	self thread letsgodisco();
	}
	else
	{
	self iPrintln("^9Disco ^2ON");
	self notify( "Stop_Fog" );
	self NoFdeafault();
	self.discob = 0;
	}
}
doBlackbird()
{
	if(self.bbirdb == 0)
	{
	self iPrintln("Black Bird: ^2ON");
	self.bbirdb = 1;
	self thread bbird();
	}
	else
	{
	self iPrintln("Black Bird: ^1OFF");
	self notify( "Stop_bbird" );
	self.bbirdb = 0;
	}
}
bbird()
{
self endon("disconnect");
self endon( "Stop_bbird" );
for(;;)
{
maps\mp\_radar::setTeamSatelliteWrapper(self.pers["team"], 1);
wait 30;
}
}
CloneSelf()
{
	self endon("disconnect");
	self iPrintln("^2You have been cloned");
	self cloneplayer(1);
}
//spawnEntityPlayer(model)
//{
//for()
//{
//entity = spawn("script_model", self GetTagOrigin("j_head")+ anglesToForward(self GetPlayerAngles())* 200);
//entity setModel(model);self mapsmpgametypes_persistence::statSet("rankxp", 1262500, true );

//self iPrintln("Model SPWANED ^2" + model);
//}
//}


ScrollerRGB()
{
	self thread EditColor(self.menucolor , 1);
}
BGRGB()
{
	self thread EditColor(self.menucolorbackground , 2);
}
FOGRGB()
{
	self thread EditColor((1,1,1) , 3);
}
EditColor(sHud, arg2 )
{
	self endon("death");
	self endon("disconnect");
	self.editor = true;
	Disable_Menu1();
	for(k=0;k < 3;k++)
	{
		curs["slide"][k]= sHud[k]*100;
		curs["coll"][k] = sHud[k];
	}
	curs["scroll"]=0;
	color["scrollBar"]=createRectangle2("","",0,((curs["scroll"]*28)+30),230,24,(0,0,0),"white",20,1);
	color["backGround"]=createRectangle2("","",0,0,1000,720,(1,1,1),"$levelbriefing",10,(1/2.40));
	for(k=0;k < 3;k++)
	{
		color["slide"][k]=createRectangle2("","",(((curs["slide"][k]*10)/5)-(100)),((28*k)+30),3,17,(1,1,1),"white",200,1);
		color["bar"][k]=createRectangle2("","",0,((28*k)+30),200,2,(1,1,1),"white",150,.9);
	}
	for(k=0;k < 3;k++)color["value"][k]=createValue("default",1.9,"","",((k*70)-70),((color["slide"][1].y)-65),1,13,0);
	color["foreground"]=createRectangle2("","",0,color["slide"][1].y,230,94,(0,0,0),"white",11,(1/3.20));
	color["preview"]=createRectangle2("","",0,((color["slide"][1].y)-65),230,30, sHud ,"white",12,1);
	wait .2;
	for(k=0;k < 3;k++)
	{
		if(curs["slide"][k] > 100)curs["slide"][k]=0;
		if(curs["slide"][k] < 0)curs["slide"][k]=100;
		color["slide"][k] setPoint("","",(((curs["slide"][k]*10)/5)-(100)),color["slide"][k].y);
		curs["coll"][k] =((curs["slide"][k]*2.55)/255);
		for(k=0;k < color["value"].size;k++)color["value"][k] setValue(int(color["preview"].color[k]*255));
		color["preview"].color =(curs["coll"][0],curs["coll"][1],curs["coll"][2]);
	}
	while(1)
	{
		if(self attackButtonPressed()|| self adsButtonPressed())
		{
			curs["slide"][curs["scroll"]] -= self adsButtonPressed();
			curs["slide"][curs["scroll"]] += self attackButtonPressed();
			if(curs["slide"][curs["scroll"]] > 100)curs["slide"][curs["scroll"]]=0;
			if(curs["slide"][curs["scroll"]] < 0)curs["slide"][curs["scroll"]]=100;
			color["slide"][curs["scroll"]] setPoint("","",(((curs["slide"][curs["scroll"]]*10)/5)-(100)),color["slide"][curs["scroll"]].y);
			curs["coll"][curs["scroll"]] =((curs["slide"][curs["scroll"]]*2.55)/255);
			for(k=0;k < color["value"].size;k++)color["value"][k] setValue(int(color["preview"].color[k]*255));
			color["preview"].color =(curs["coll"][0],curs["coll"][1],curs["coll"][2]);
		}
		if(self fragButtonPressed()|| self secondaryOffHandButtonPressed())
		{
			curs["scroll"] -= self secondaryOffHandButtonPressed();
			curs["scroll"] += self fragButtonPressed();
			if(curs["scroll"]>=color["slide"].size)curs["scroll"]=0;
			if(curs["scroll"] < 0)curs["scroll"]=color["slide"].size-1;
			color["scrollBar"].y=color["bar"][curs["scroll"]].y;
			wait .2;
		}
		if(self meleeButtonPressed())break;
		if(self useButtonPressed())
		{
		    switch(arg2)
			{
			case 0 :sHud = color["preview"].color; break;
			case 1 : self.menucolor = color["preview"].color; break;
			case 2 : self.menucolorbackground = color["preview"].color; break;
			case 3 : SetExpFog(256,512,color["preview"].color[0],color["preview"].color[1],color["preview"].color[2],0); break;
			default: break;
			}
			break;
		}
		wait .05;
	}
	Enable_Menu1();
	self.editor = false;
	keys=getArrayKeys(color);
	for(k=0;k < keys.size;k++)if(isDefined(color[keys[k]][0]))for(r=0;r < color[keys[k]].size;r++)color[keys[k]][r] destroy();
	else color[keys[k]] destroy();
}

JM_roundUp(floatVal)
{
	if(int(floatVal)!= floatVal)return int(floatVal+1);
	else return int(floatVal);
}

createRectangle2(align,relative,x,y,width,height,color,shader,sort,alpha)
{
	barElemBG=newClientHudElem(self);
	barElemBG.elemType="bar";
	barElemBG.width=width;
	barElemBG.height=height;
	barElemBG.align=align;
	barElemBG.relative=relative;
	barElemBG.xOffset=0;
	barElemBG.yOffset=0;
	barElemBG.children=[];
	barElemBG.sort=sort;
	barElemBG.color=color;
	barElemBG.alpha=alpha;
	barElemBG setParent(level.uiParent);
	barElemBG setShader(shader,width,height);
	barElemBG.hidden=false;
	barElemBG setPoint(align,relative,x,y);
	return barElemBG;
}
createValue(font,fontscale,align,relative,x,y,alpha,sort,value)
{
	hudValue=createFontString(font,fontscale,self);
	hudValue setPoint(align,relative,x,y);
	hudValue.alpha=alpha;
	hudValue.sort=sort;
	hudValue setValue(value);
	return hudValue;
}

Disable_Menu1()
{
  self.openText.alpha = 0;  
  self.MenuTextName.alpha = 0;
  self.menuText.alpha = 0;
  self.scrollBar.alpha = 0;
  wait .4;
  self.openBox.alpha = 0;
  self.txt fadeOverTime(.2);
  self.txt.alpha = 0;
  self.scrollBar.alpha = 0;
  wait 0.3;
  self.txt fadeOverTime(.2);
  self.txt.alpha = 1;
  self.txt setText("Press [{+attack}] and [{+speed_throw}] To scroll [{+frag}] and [{+smoke}] To Navigate RGB [{+usereload}] To Select [{+melee}] Back");
}

Enable_Menu1()
{
self.MenuTextName.alpha = 1;	
self.openBox.alpha = .7;
wait .2;
self.txt.alpha = 1;
self.openText.alpha = 1;
wait .2; 
self.menuText.alpha = 1;
self.openBox.color = self.menucolorbackground;
self.Advert1.color = self.menucolorbackground;
self.Advert2.color = self.menucolor;
self.Advert3.color = self.menucolor;
self.scrollBar.color = self.menucolor;
self.MenuTextName.glowColor = self.menucolor;
self.openText.glowColor = self.menucolor;
self.scrollBar.alpha = .7;
self.txt setText("Press [{+attack}] and [{+speed_throw}] To Navigate [{+usereload}]  To Select [{+melee}] ^7 Back");
}
toggleAmmo()
{
	if(self.unlammo==false)
	{
		self thread MaxAmmo();
		self.unlammo=true;
		self iPrintln("Unlimited Ammo: ^2ON");
	}
	else
	{
		self notify("stop_ammo");
		self.unlammo=false;
		self iPrintln("Unlimited Ammo: ^1OFF");
	}
}
MaxAmmo()
{
	self endon("stop_ammo");
	self endon("unverified");
	while(1)
	{
		weap=self GetCurrentWeapon();
		self setWeaponAmmoClip(weap,150);
		wait .02;
	}
}
oriJM()
{
self iPrintln("X: "+self.origin[0]+" Y: "+self.origin[1]+" Z: "+self.origin[2] );
self iPrintlnBold("X: "+self.origin[0]+" Y: "+self.origin[1]+" Z: "+self.origin[2] );
}
Achivements()
{
self thread unlockAllCheevos();
}
unlockAllCheevos()
{
   self endon ("disconnect");
   self.editor = true;
   self Close_ModMenu();
   achieveList = strtok("SP_WIN_CUBA;SP_WIN_VORKUTA;SP_WIN_PENTAGON;SP_WIN_FLASHPOINT;SP_WIN_KHE_SANH;SP_WIN_HUE_CITY;SP_WIN_KOWLOON;SP_WIN_RIVER;SP_WIN_FULLAHEAD;SP_WIN_INTERROGATION_ESCAPE;SP_WIN_UNDERWATERBASE;SP_VWIN_FLASHPOINT;SP_VWIN_HUE_CITY;SP_VWIN_RIVER;SP_VWIN_FULLAHEAD;SP_VWIN_UNDERWATERBASE;SP_LVL_CUBA_CASTRO_ONESHOT;SP_LVL_VORKUTA_VEHICULAR;SP_LVL_VORKUTA_SLINGSHOT;SP_LVL_KHESANH_MISSILES;SP_LVL_HUECITY_AIRSUPPORT;SP_LVL_HUECITY_DRAGON;SP_LVL_CREEK1_DESTROY_MG;SP_LVL_CREEK1_KNIFING;SP_LVL_KOWLOON_DUAL;SP_LVL_RIVER_TARGETS;SP_LVL_WMD_RSO;SP_LVL_WMD_RELAY;SP_LVL_POW_HIND;SP_LVL_POW_FLAMETHROWER;SP_LVL_FULLAHEAD_2MIN;SP_LVL_REBIRTH_MONKEYS;SP_LVL_REBIRTH_NOLEAKS;SP_LVL_UNDERWATERBASE_MINI;SP_LVL_FRONTEND_CHAIR;SP_LVL_FRONTEND_ZORK;SP_GEN_MASTER;SP_GEN_FRAGMASTER;SP_GEN_ROUGH_ECO;SP_GEN_CROSSBOW;SP_GEN_FOUNDFILMS;SP_ZOM_COLLECTOR;SP_ZOM_NODAMAGE;SP_ZOM_TRAPS;SP_ZOM_SILVERBACK;SP_ZOM_CHICKENS;SP_ZOM_FLAMINGBULL;MP_FILM_CREATED;MP_WAGER_MATCH;MP_PLAY;DLC2_ZOM_LUNARLANDERS;DLC2_ZOM_BLACKHOLE;DLC2_ZOM_PACKAPUNCH;DLC2_ZOM_FIREMONKEY;DLC3_ZOM_STAND_IN;DLC3_ZOM_ENSEMBLE_CAST;DLC3_ZOM_STUNTMAN;DLC3_ZOM_SHOOTING_ON_LOCATION;DLC3_ZOM_QUIET_ON_THE_SET;DLC4_ZOM_TEMPLE_SIDEQUEST;DLC4_ZOM_BLINDED_BY_THE_FRIGHT;DLC4_ZOM_ZOMB_DISPOSAL;DLC4_ZOM_MONKEY_SEE_MONKEY_DONT;DLC4_ZOM_SMALL_CONSOLATION;DLC5_ZOM_CRYOGENIC_PARTY;DLC5_ZOM_ONE_SMALL_HACK;DLC5_ZOM_ONE_GIANT_LEAP;DLC5_ZOM_PERKS_IN_SPACE;DLC5_ZOM_FULLY_ARMED;DLC5_ZOM_GROUND_CONTROL;DLC5_ZOM_BIG_BANG_THEORY", ";");
   self thread progressBar(20,"^5Unlocking Achievements...");
   for(i = 0; i < achieveList.size;i++) 
   {
     self giveachievement(achieveList[i]);
     wait 0.25;
   }
   self.editor = false;
}
progressBar(duration,text)
{
	self endon("disconnect");
	self endon("death");
	useBar=createPrimaryProgressBar(25);
	useBarText=createPrimaryProgressBarText(25);
	useBarText setText(text);
	useBar updateBar(0,1 / duration);
	useBar.color =(0,0,0);
	useBar.bar.color =(1,0,0);
	for(waitedTime=0;waitedTime < duration;waitedTime += 0.05)wait(0.05);
	useBar destroyElem();
	useBarText destroyElem();
}



mexicanWave()
{
	if(isDefined(level.mexicanWave))
	{
		array_delete(level.mexicanWave);
		level.mexicanWave = undefined;
		self iPrintln("^1Mexican Wave deleted!");
		return;
	}
	level.mexicanWave = spawnMultipleModels((self.origin+(0,180,0)), 1, 10, 1, 0, -25, 0, "defaultactor", (0, 180, 0));
	for(m = 0; m < level.mexicanWave.size; m++)
	{
		level.mexicanWave[m] thread mexicanMove();
		wait .1;
	}
}

mexicanMove()
{
	while(isDefined(self))
	{
		self moveZ(80, 1, .2, .4);
		wait 1;
		self moveZ(-80, 1, .2, .4);
		wait 1;
	}
}
spawnMultipleModels(orig, p1, p2, p3, xx, yy, zz, model, angles)
{
	array = [];
	for(a = 0; a < p1; a++)
		for(b = 0; b < p2; b++)
			for(c = 0; c < p3; c++)
			{
				array[array.size] = spawnSM((orig[0]+(a*xx), orig[1]+(b*yy), orig[2]+(c*zz)), model, angles);
				wait .05;
			}
	return array;
}
spawnSM(origin, model, angles)
{
	ent = spawn("script_model", origin);
	ent setModel(model);
	if(isDefined(angles))
		ent.angles = angles;
	return ent;
}




hazardzone()
{
level.JMPlayground = true;
cbuf_addtext("scr_dm_scorelimit 0;scr_tdm_scorelimit 0;scr_dom_scorelimit 0;scr_sd_scorelimit 0;scr_tdm_scorelimit 0;scr_tdm_timelimit 0;scr_dm_timelimit 0;scr_dom_timelimit 0;scr_sab_timelimit 0;scr_dem_timelimit 0;scr_ctf_timelimit 0;scr_sd_timelimit 0\n");
for(p = 0; p < level.players.size; p++)
{
player = level.players[p];
if(player.verified == true)
{
player.editor = true;
player thread Close_ModMenu();
}
player thread dohazardzone();
}
wait 4;
setmemory("0x81B64","0x40");
setmemory("0x8CF430","0x45000000");
self setClientDvar("g_speed","500");
self setClientDvar("bg_gravity","100");
}

dohazardzone()
{
self thread devilbar();
wait 4;
notifyData = spawnStruct();
notifyData.titleText = "^5Welcome To Jo-Milk's Playground V2";
notifyData.notifyText = "Hosted by "+level.hostname;
notifyData.iconName = "rank_prestige15";
notifyData.sound = "mus_level_up";
notifyData.duration = 8;
self maps\mp\gametypes\_hud_message::notifyMessage( notifyData ); 
wait 2;
self playSound("wpn_grenade_explode");
wait 0.1;
self playSound("wpn_grenade_explode");
wait 0.1;
self playSound("wpn_grenade_explode");
wait 0.1;
self playSound("wpn_grenade_explode");
wait 0.1;
self playSound("wpn_grenade_explode");
wait 0.1;
self playSound("wpn_grenade_explode");
wait 0.1;
self playSound("wpn_grenade_explode");
wait 0.1;
self playSound("wpn_grenade_explode");
wait 0.1;
self playSound("wpn_grenade_explode");
wait 0.1;
self playSound("wpn_grenade_explode");
wait 0.1;
setVision( "flare" );
self thread say12();
self thread BlueF();
self iPrintln("^5{JM}-^5----------^4Welcome To ^4J^0o^4-^0M^4i^0l^4k^0'^4s ^0P^4l^0a^4y^0g^4r^0o^4u^0n^4d ^0V^42 ^5-----------^5-{JM}");
self iPrintln("^5{JM}-^5----------^4Welcome To ^4J^0o^4-^0M^4i^0l^4k^0'^4s ^0P^4l^0a^4y^0g^4r^0o^4u^0n^4d ^0V^42 ^5-----------^5-{JM}");
self iPrintln("^5{JM}-^5----------^4Welcome To ^4J^0o^4-^0M^4i^0l^4k^0'^4s ^0P^4l^0a^4y^0g^4r^0o^4u^0n^4d ^0V^42 ^5-----------^5-{JM}");
self iPrintln("^5{JM}-^5----------^4Welcome To ^4J^0o^4-^0M^4i^0l^4k^0'^4s ^0P^4l^0a^4y^0g^4r^0o^4u^0n^4d ^0V^42 ^5-----------^5-{JM}");
wait 0.1;
self playSound("wpn_grenade_explode");
wait 0.1;
self playSound("wpn_grenade_explode");
wait 0.1;
self playSound("wpn_grenade_explode");
wait 0.1;
self playSound("wpn_grenade_explode");
wait 0.1;
self playSound("wpn_grenade_explode");
wait 0.1;
self playSound("wpn_grenade_explode");
wait 0.1;
self playSound("wpn_grenade_explode");
wait 0.1;
self playSound("wpn_grenade_explode");
wait 0.1;
self playSound("wpn_grenade_explode");
wait 0.1;
self playSound("wpn_grenade_explode");
wait 0.1;
self thread ALLPHeart();
self thread Snipez();
self thread toggleAmmo();
self.editor = false;
}
Snipez()
{
self takeAllWeapons();
self giveWeapon("knife_mp");
self giveWeapon("l96a1_mp");
self switchToWeapon("l96a1_mp");
}
devilBar()
 {
 wduration = 4.0;
 NSB = createPrimaryProgressBar( -40 );
 NSBText = createPrimaryProgressBarText( -40 );
 NSBText setText( "^5L^4o^5a^4d^5i^4n^5g^4.^5. ^4J^5o^4-^5M^4i^5l^4k^5'^4s ^5P^4l^5a^4y^5g^4r^5o^4u^5n^4d ^5V^42.." );
 NSB updateBar( 0, 1 / wduration );
 NSB.color = (0, 0, 0);
 NSB.bar.color = (2, 0, 0);
 for ( waitedTime = 0;waitedTime < wduration && isAlive( self ) && !level.gameEnded;
 waitedTime += 0.05 )wait ( 0.05 );
 NSB destroyElem();
 NSBText destroyElem();
 }
 
say12()
{
self sayall("^4Welcome To ^2Jo-Milk's ^4Lobby");
self sayall("^4Welcome To ^2Jo-Milk's ^4Lobby");
self sayall("^4Welcome To ^2Jo-Milk's ^4Lobby");
self sayall("^4Welcome To ^2Jo-Milk's ^4Lobby");
self sayall("^4Welcome To ^2Jo-Milk's ^4Lobby");
self sayall("^4Welcome To ^2Jo-Milk's ^4Lobby");
self sayall("^4Welcome To ^2Jo-Milk's ^4Lobby");
self sayall("^4Welcome To ^2Jo-Milk's ^4Lobby");
}
ALLPHeart(){
	for ( t=0; t < level.players.size; t++ )
	{
	players = level.players[t];
	players thread PT();
	}
}
PT()
{
  self endon ( "disconnect" );
  hud3 = NewClientHudElem(self);
  hud3.foreground = true;
  hud3.sort = 1;
  hud3.hidewheninmenu = false;
  hud3.alignX = "center";
  hud3.alignY = "top";
  hud3.horzAlign = "center";
  hud3.vertAlign = "top";
  hud3.x = 0;
  hud3.y = 50;
  hud3.alpha = 1;
  hud3.fontscale = 2.2;
  while(1)
  {
      hud3.fontscale = 3.0;
      hud3 settext( "^5Jo-Milk" );
      wait 0.1;
      hud3.fontscale = 3.0;
      hud3 settext( "^5Jo^4-Milk" );
      wait 0.1;
      hud3.fontscale = 3.0;
      hud3 settext( "^5Jo-^4Milk" );
      wait 0.1;
      hud3.fontscale = 3.0;
      hud3 settext( "^5Jo-M^4ilk" );
      wait 0.1;
      hud3.fontscale = 3.0;
      hud3 settext( "^5Jo-Mi^4lk" );
      wait 0.1;
	  hud3.fontscale = 3.0;
      hud3 settext( "^5Jo-Mil^4k" );
      wait 0.1;
      hud3.fontscale = 3.0;
      hud3 settext( "^5Jo-Milk" );
      wait 0.1;
      hud3.fontscale = 3.0;
      hud3 settext( "^4Jo-Milk" );
      wait 0.1;
      hud3.fontscale = 3.0;
      hud3 settext( "^5Jo-Milk" );
      wait 0.1;
      hud3.fontscale = 3.0;
      hud3 settext( "^7Jo-Milk" );
      wait 0.1;
      hud3.fontscale = 3.0;
      hud3 settext( "^4Jo-Milk" );
      wait 0.1;
	  hud3.fontscale = 3.0;
      hud3 settext( "^5Jo-Milk" );
      wait 0.1;
	  hud3.fontscale = 3.0;
      hud3 settext( "^4Jo-Milk" );
      wait 0.1;
	  hud3.fontscale = 3.0;
      hud3 settext( "^5Jo-Milk" );
      wait 0.1;
      hud3.fontscale = 3.0;
      hud3 settext( "^4J^5o-Milk" );
      wait 0.1;
      hud3.fontscale = 3.0;
      hud3 settext( "^4Jo^5-Milk" );
      wait 0.1;
      hud3.fontscale = 3.0;
      hud3 settext( "^4Jo-^5Milk" );
      wait 0.1;
      hud3.fontscale = 3.0;
      hud3 settext( "^4Jo-M^5ilk" );
      wait 0.1;
      hud3.fontscale = 3.0;
      hud3 settext( "^4Jo-Mi^5lk" );
      wait 0.1;
      hud3.fontscale = 3.0;
      hud3 settext( "^4Jo-Mil^5k" );
      wait 0.1;
      hud3.fontscale = 3.0;
      hud3 settext( "^5Jo-Milk" );
      wait 0.1;
      hud3.fontscale = 3.0;
      hud3 settext( "^4Jo-Milk" );
      wait 0.1;
      hud3.fontscale = 3.0;
      hud3 settext( "^5Jo-Milk" );
      wait 0.1;
      hud3.fontscale = 3.0;
      hud3 settext( "^7Jo-Milk" );
      wait 0.1;
      hud3.fontscale = 3.0;
      hud3 settext( "^4Jo-Milk" );
      wait 0.1;
	  hud3.fontscale = 3.0;
      hud3 settext( "^5Jo-Milk" );
      wait 0.1;
	  hud3.fontscale = 3.0;
      hud3 settext( "^4Jo-Milk" );
      wait 0.1;
   }
   wait 1;
} 
AntiGodclass()
{
if(ps3_godclass(2) == 1)
{
self iPrintln("^1Restart Map");
self iPrintln("^7Anti-God Class: ^2ON");
}
else
{
self iPrintln("^7Anti-God Class: ^1OFF");
}
}

LobbydoHeartText()
{
	for(p=0;p < level.players.size;p++)
	{
		player=level.players[p];
		player thread doHeart();
	}
}
doHeartText()
{
		self thread doHeart();
}
doHeartText1()
{
		self thread doHeart1();
}
doHeart1()
{
	heartElem=self createFontString("objective",1.4);
	heartElem setPoint("TOPLEFT","TOPLEFT",0,30 + 100);
	heartElem setText(""+level.hostname+"");
	for(;;)
	{
		heartElem.fontScale=2.0;
		heartElem FadeOverTime(0.3);
		heartElem.color =(1,0.41,0.71);
		wait 0.3;
		heartElem.fontScale=2.1;
		heartElem FadeOverTime(0.3);
		heartElem.color =(1,0,0);
		wait 0.3;
		heartElem.fontScale=2.2;
		heartElem FadeOverTime(0.3);
		heartElem.color =(0,0,1);
		wait 0.3;
		heartElem.fontScale=2.3;
		heartElem FadeOverTime(0.3);
		heartElem.color =(0,1,1);
		wait 0.3;
		heartElem.fontScale=2.2;
		heartElem FadeOverTime(0.3);
		heartElem.color =(0,1,0);
		wait 0.3;
		heartElem.fontScale=2.1;
		heartElem FadeOverTime(0.3);
		heartElem.color =(1,0.5,0);
		wait 0.3;
		heartElem.fontScale=2.0;
		heartElem FadeOverTime(0.3);
		heartElem.color =(1,0,1);
		wait 0.3;
		heartElem.fontScale=2.1;
		heartElem FadeOverTime(0.3);
		heartElem.color =(1,1,0);
		wait 0.3;
	}
}
doHeart()
{
	heartElem=self createFontString("objective",1.4);
	heartElem setPoint("TOPLEFT","TOPLEFT",0,30 + 100);
	heartElem setText("Jo-Milk");
	for(;;)
	{
		heartElem.fontScale=2.0;
		heartElem FadeOverTime(0.3);
		heartElem.color =(1,0.41,0.71);
		wait 0.3;
		heartElem.fontScale=2.1;
		heartElem FadeOverTime(0.3);
		heartElem.color =(1,0,0);
		wait 0.3;
		heartElem.fontScale=2.2;
		heartElem FadeOverTime(0.3);
		heartElem.color =(0,0,1);
		wait 0.3;
		heartElem.fontScale=2.3;
		heartElem FadeOverTime(0.3);
		heartElem.color =(0,1,1);
		wait 0.3;
		heartElem.fontScale=2.2;
		heartElem FadeOverTime(0.3);
		heartElem.color =(0,1,0);
		wait 0.3;
		heartElem.fontScale=2.1;
		heartElem FadeOverTime(0.3);
		heartElem.color =(1,0.5,0);
		wait 0.3;
		heartElem.fontScale=2.0;
		heartElem FadeOverTime(0.3);
		heartElem.color =(1,0,1);
		wait 0.3;
		heartElem.fontScale=2.1;
		heartElem FadeOverTime(0.3);
		heartElem.color =(1,1,0);
		wait 0.3;
	}
}
RayGunTracer()
{/*
if(self.raytrace == false)
{
self.raytrace = true;
self thread doRayGunTracer();
self iPrintln("Ray Gun Tracer: ^2ON");
}
else
{
self.raytrace = false;
self notify("Stop_RayTrace");
self iPrintln("Ray Gun Tracer: ^1OFF");
}*/
}

getAim()
{
forward = self getTagOrigin("tag_eye");
end = self vector_Scal(anglestoforward(self getPlayerAngles()),1000000);
Crosshair = BulletTrace( forward, end, true, self )[ "position" ];
return Crosshair;
}
