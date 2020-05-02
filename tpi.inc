/*
TogglePlayerInvisibility.
*/

#if defined _TPI_included
	#endinput
#endif
#define _TPI_included

#if ! defined PAWNRAKNET_INC_
	#error You must have Pawn.Raknet include in order to use this one.
#endif

static bool:TPI_IsInvisible[MAX_PLAYERS char];

/*TogglePlayerInvisibility*/
stock TogglePlayerInvisibility(const playerid, bool:toggle)
{
	if(!IsPlayerConnected(playerid)) 
	{
		return 0;
	}
	
	TPI_IsInvisible{playerid} = toggle;
	
	if(toggle)
	{
		new
			BitStream:tpi_bs = BS_New();
		
		BS_WriteValue(
			tpi_bs,
			PR_UINT16, playerid
		);

		BS_RPC(tpi_bs, -1, 0xA3);
		BS_Delete(tpi_bs);
	}
	else
	{
		new
			BitStream:tpi_bs = BS_New(),
			Float:tpi_pos_x,
			Float:tpi_pos_y,
			Float:tpi_pos_z,
			Float:tpi_angle;
		
		GetPlayerPos(playerid, tpi_pos_x, tpi_pos_y, tpi_pos_z);
		GetPlayerFacingAngle(playerid, tpi_angle);

		BS_WriteValue(
			tpi_bs,
			PR_UINT16, playerid,
			PR_UINT8, GetPlayerTeam(playerid),
			PR_UINT32, GetPlayerSkin(playerid),
			PR_FLOAT, tpi_pos_x,
			PR_FLOAT, tpi_pos_y,
			PR_FLOAT, tpi_pos_z,
			PR_FLOAT, tpi_angle,
			PR_UINT32, GetPlayerColor(playerid),
			PR_UINT8, GetPlayerFightingStyle(playerid)
		);

		BS_RPC(tpi_bs, -1, 0x20);
		BS_Delete(tpi_bs);
	}
	return 1;
}

/*IsPlayerInvisible*/
stock bool:IsPlayerInvisible(const playerid)
{
	if(!IsPlayerConnected(playerid))
	{
		return 0;
	}
	else
	{
		return TPI_IsInvisible{playerid};
	}
}

/*OnPlayerConnect*/
public OnPlayerConnect(playerid)
{
	TPI_IsInvisible{playerid} = false;
	
	#if defined TPI_OnPlayerConnect
		return TPI_OnPlayerConnect(playerid);
	#else
		return 1;
	#endif
}

/*OnOutcomingRPC*/
public OnOutcomingRPC(playerid, rpcid, BitStream:bs)
{
	if(rpcid == 0x20)
	{
		new tpi_playerid;

		BS_ReadValue(bs, PR_UINT16, tpi_playerid);
		
		if(TPI_IsInvisible{tpi_playerid}) return 0;

	}
	#if defined TPI_OnOutcomingRPC
		return TPI_OnOutcomingRPC(playerid, rpcid, bs);
	#else
		return 1;
	#endif
}

/*Hooks*/
#if defined _ALS_OnOutcomingRPC
#undef OnOutcomingRPC
#else
#define _ALS_OnOutcomingRPC
#endif
#define OnOutcomingRPC TPI_OnOutcomingRPC

#if defined TPI_OnOutcomingRPC
forward TPI_OnOutcomingRPC(playerid, rpcid, BitStream:bs);
#endif

#if defined _ALS_OnPlayerConnect
#undef OnPlayerConnect
#else
#define _ALS_OnPlayerConnect
#endif
#define OnPlayerConnect TPI_OnPlayerConnect

#if defined TPI_OnPlayerConnect
forward TPI_OnPlayerConnect(playerid);
#endif