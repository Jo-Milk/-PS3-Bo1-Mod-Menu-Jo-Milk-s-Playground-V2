#include clientscripts\mp\_utility;
#include clientscripts\mp\_utility_code;

main()
{
	waitforclient(0);
	player = GetLocalPlayer(0);
    player thread JM_onPlayerSpawned();
	player thread JM_MainMod();
}

JM_onPlayerSpawned()
{
for(;;)
{
self waittill("respawn");
wait 1;
if(self isalive() == true)
{
jm_iprintln( "to Open Non-Host Menu" );
}
}
}

JM_MainMod()
{
for(;;)
{
if(self isalive() == true)
{
if(jm_pressing() == 1)
{
jm_cschook();
wait 0.03;
}
else
wait 0.03;
}
else
wait 0.6;
}
}



