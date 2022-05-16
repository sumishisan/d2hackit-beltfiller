/**
 * BeltFiller.cpp
 * ------------
 *
 * Auto fill belt slots of potions.
 *
 * oracle (b3gn_oracle@hotmail.com)
 */
#include "D2HackIt\\Includes\\D2Hackit.h"
#include "D2HackIt\\Includes\\ClientCore.cpp"

BOOL g_Enabled = TRUE;

BOOL PRIVATE OnGameCommandHelp(char** argv, int argc);
BOOL PRIVATE OnGameCommandEnable(char** argv, int argc);
BOOL PRIVATE OnGameCommandDisable(char** argv, int argc);
BOOL PRIVATE OnGameCommandToggle(char** argv, int argc);

CLIENTINFO
(		
	0,1,
	"oracle",
	"www.b3gn.com/",
	"Belt Filler",
	"b3gn_oracle@hotmail.com"
)

MODULECOMMANDSTRUCT ModuleCommands[] =
{
	{
		"help",
		OnGameCommandHelp,
		"helpÿc0 List commands available in this module.\n"
		"<command> helpÿc0 Shows detailed help for <command> in this module."
	},
	{
		"enable", OnGameCommandEnable,
		"hostile ÿc0Enable put potion to belt automatically."
	},
	{
		"disable", OnGameCommandDisable,
		"hp ÿc0Disable potion to belt automatically."
	},
	{
		"toggle", OnGameCommandToggle,
		"mana ÿc0Toggle."
	},
	{NULL} // No more commands
};

VOID EXPORT OnUnitMessage(UINT nMessage, LPCGAMEUNIT lpUnit, WPARAM wParam, LPARAM lParam)
{
	if (nMessage != UM_ITEMEVENT || wParam != ITEM_EVENT_FROM_BELTSLOT)
		return;

	int PutInBelt = 0;
	if (g_Enabled)
		for(int x = 0; x < 10; x++)
			for(int y = 0; y < 4; y++)
			{
				if (me->PutInventoryPotionToBelt(me->GetStorageItem(STORAGE_INVENTORY,x,y)))
					PutInBelt++;
				
			}

	if (PutInBelt == 0)
		server->GameInfof("BeltFiller: Inventory is empty. No potion left.");
}


BOOL PRIVATE OnGameCommandEnable(char** argv, int argc)
{
	server->GameInfof("Auto put: Enabled");
	g_Enabled = TRUE;
	return TRUE;
}

BOOL PRIVATE OnGameCommandDisable(char** argv, int argc)
{
	server->GameInfof("Auto put: Disabled");
	g_Enabled = FALSE;
	return TRUE;
}

BOOL PRIVATE OnGameCommandToggle(char** argv, int argc)
{
	g_Enabled = !g_Enabled;

	if (g_Enabled)
		server->GameInfof("Auto put: Enabled");
	else
		server->GameInfof("Auto put: Disabled");
	return TRUE;
}
