#include maps\mp\_utility;
#include common_scripts\utility;
#include maps\mp\gametypes\_hud_util;

JM_Spawn_GetText(val)
{
str = "";
switch(val)
{
case 1: str = "Bunker Tutorial"; break;
case 2: str = "Spawnable2"; break;
case 3: str = "Spawnable3"; break;
case 4: str = "Spawnable4"; break;
case 5: str = "Spawnable5"; break;
case 6: str = "Spawnable6"; break;
case 7: str = "Spawnable7"; break;
case 8: str = "Spawnable8"; break;
case 9: str = "Spawnable9"; break;
default:break;
}
return str;
}
Spawnable1()
{
self thread BunkerThread123();
}
Spawnable2()
{

}
Spawnable3()
{

}
Spawnable4()
{

}
Spawnable5()
{

}
Spawnable6()
{

}
Spawnable7()
{

}
Spawnable8()
{

}
Spawnable9()
{

}

WP(D,Z,P)
{
	L=strTok(D,",");
	for(i = 0 ; i < L.size; i += 2)
	{
		B = spawn("script_model",self.origin+(int(L[i]),int(L[i+1]),Z));
		if(!P)
			B.angles=(90,0,0);
		B setModel("mp_supplydrop_ally");
	}
}
BunkerThread123() 
{
	if(self.SneakerbunkerIsSpawned123 == false)
	{    
		self.SneakerbunkerIsSpawned123 = true;
		self iprintln("Pyramids ^2SPAWNED");
		//Layer 0
WP("0,0,25,0,50,0,75,0,100,0,125,0,150,0,175,0,200,0,225,0,0,30,225,30,0,60,225,60,0,90,225,90,0,120,225,120,0,150,225,150,0,180,225,180,0,210,225,210,0,240,225,240,0,270,25,270,50,270,75,270,100,270,125,270,150,270,175,270,200,270,225,270",0,0);
//Layer 0
WP("25,30,50,30,75,30,100,30,125,30,150,30,175,30,200,30,25,60,200,60,25,90,200,90,25,120,200,120,25,150,200,150,25,180,200,180,25,210,200,210,25,240,50,240,75,240,100,240,125,240,150,240,175,240,200,240",40,0);
//Layer 0
WP("50,60,75,60,100,60,125,60,150,60,175,60,50,90,175,90,50,120,175,120,50,150,175,150,50,180,175,180,50,210,75,210,100,210,125,210,150,210,175,210",80,0);
//Layer 0
WP("75,90,100,90,125,90,150,90,75,120,150,120,75,150,150,150,75,180,100,180,125,180,150,180",120,0);
//Layer 0
WP("100,120,125,120,100,150,125,150",150,0);

	}
	else
	{
		self iprintln("Pyramids is ^1Already SPAWNED");
	}
}