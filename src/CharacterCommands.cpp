#include "Config.h"
#include "Player.h"
#include "ScriptMgr.h"
#include "Chat.h"

class mod_charactercommandsScripts : public CommandScript
{
public:
    mod_charactercommandsScripts() : CommandScript("mod_charactercommandsScripts") { }

    Acore::ChatCommands::ChatCommandTable GetCommands() const override
    {
        static Acore::ChatCommands::ChatCommandTable CharacterScriptsCommandTable =
        {
            // Character modifications:
            { "u customize",  HandleCustomizeCommand, SEC_PLAYER, Acore::ChatCommands::Console::Yes },
            { "u changerace",  HandleChangeRaceCommand, SEC_PLAYER, Acore::ChatCommands::Console::Yes },
            { "u changefaction",  HandleChangeFactionCommand, SEC_PLAYER, Acore::ChatCommands::Console::Yes }
        };

        return CharacterScriptsCommandTable;
    }

    static bool HandleCustomizeCommand(ChatHandler* handler, const char* args)
    {
        Player* player = handler->GetSession()->GetPlayer();

        if (!CanUseCommand(player, handler))
            return false;

        player->SetAtLoginFlag(AT_LOGIN_CUSTOMIZE);
        handler->PSendSysMessage("Success! You can logout and customize your character.");
        return true;
    }

    static bool HandleChangeRaceCommand(ChatHandler* handler, const char* args)
    {
        Player* player = handler->GetSession()->GetPlayer();

        if (!CanUseCommand(player, handler))
            return false;

        player->SetAtLoginFlag(AT_LOGIN_CHANGE_RACE);
        handler->PSendSysMessage("Success! You can now logout and change your race.");
        return true;
    }

    static bool HandleChangeFactionCommand(ChatHandler* handler, const char* args)
    {
        Player* player = handler->GetSession()->GetPlayer();

        if (!CanUseCommand(player, handler))
            return false;

        player->SetAtLoginFlag(AT_LOGIN_CHANGE_FACTION);
        handler->PSendSysMessage("Success! You can now now logout and change your faction.");
        return true;
    }

    static bool CanUseCommand(Player* player, ChatHandler* handler)
    {
        // I believe some of these checks are also done on the core side, but preventing is better.

        if (!sConfigMgr->GetOption<bool>("CharacterScripts.Enable", false))
        {
            handler->PSendSysMessage("Custom character scripts are not enabled.");
            handler->SetSentErrorMessage(true);
            return false;
        }

        if (player->GetLevel() < 10)
        {
            handler->PSendSysMessage("This command cannot be executed whilest you are below level 10.");
            handler->SetSentErrorMessage(true);
            return false;
        }

        if (player->IsInFlight())
        {
            handler->PSendSysMessage("This command cannot be executed whilest you are flying.");
            handler->SetSentErrorMessage(true);
            return false;
        }

        if (player->IsInCombat())
        {
            handler->PSendSysMessage("This command cannot be executed whilest you are in combat.");
            handler->SetSentErrorMessage(true);
            return false;
        }

        if (player->InBattleground() || player->InBattlegroundQueue())
        {
            handler->PSendSysMessage("This command cannot be executed while you are queued for or participating in a battleground or arena.");
            handler->SetSentErrorMessage(true);
            return false;
        }

        if (player->IsUsingLfg())
        {
            handler->PSendSysMessage("This command cannot be executed whilest you are using LFG.");
            handler->SetSentErrorMessage(true);
            return false;
        }

        if (player->GetGroup())
        {
            handler->PSendSysMessage("This command cannot be executed whilest you are in a group.");
            handler->SetSentErrorMessage(true);
            return false;
        }

        if (player->isDead() || player->HasFlag(PLAYER_FLAGS, PLAYER_FLAGS_GHOST))
        {
            handler->PSendSysMessage("This command cannot be executed whilest you are dead.");
            handler->SetSentErrorMessage(true);
            return false;
        }

        return true;
    }
};

void Addmod_charactercommandsScripts()
{
    new mod_charactercommandsScripts();
}