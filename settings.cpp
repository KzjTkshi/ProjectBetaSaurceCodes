#include "main.h"
#include "settings.h"
#include "vendor/inih/cpp/INIReader.h"

#include "vendor/SimpleIni/SimpleIni.h"

void ApplyFPSPatch(uint8_t);

CSettings::CSettings()
{
	Log("Loading settings..");

	char buff[0x7F];
	sprintf(buff, "%sSAMP/config.ini", g_pszStorage);

	INIReader reader(buff);

	if(reader.ParseError() < 0)
	{
		Log("Error: can't load %s", buff);
		std::terminate();
		return;
	}

	// Client
	size_t length = 0;
	length = reader.Get("client", "user", "SAMP_PLAYER_1337").copy(m_Settings.szNickName, MAX_PLAYER_NAME);
	m_Settings.szNickName[length] = '\0';
	length = reader.Get("client", "host", "127.0.0.1").copy(m_Settings.szHost, MAX_SETTINGS_STRING);
	m_Settings.szHost[length] = '\0';
	length = reader.Get("client", "password", "").copy(m_Settings.szPassword, MAX_SETTINGS_STRING);
	m_Settings.szPassword[length] = '\0';
	m_Settings.iPort = reader.GetInteger("client", "port", 7777);

	m_Settings.szTimeStamp = reader.GetBoolean("client", "timestamp", false);

	// Debug
	m_Settings.bDebug = reader.GetBoolean("debug", "debug", false);
	m_Settings.bOnline = reader.GetBoolean("debug", "online", false);

	// gui
	length = reader.Get("gui", "Font", "Arial.ttf").copy(m_Settings.szFont, 35);
	m_Settings.szFont[length] = '\0';
	m_Settings.fFontSize = reader.GetReal("gui", "FontSize", 37.0f);
	m_Settings.iFontOutline = reader.GetInteger("gui", "FontOutline", 1);
	// chat
	m_Settings.fChatPosX = reader.GetReal("gui", "ChatPosX", 325.0f);
	m_Settings.fChatPosY = reader.GetReal("gui", "ChatPosY", 25.0f);
	m_Settings.fChatSizeX = reader.GetReal("gui", "ChatSizeX", 1150.0f);
	m_Settings.fChatSizeY = reader.GetReal("gui", "ChatSizeY", 220.0f);
	m_Settings.iChatMaxMessages = reader.GetInteger("gui", "ChatMaxMessages", 6);
	// scoreboard
	m_Settings.fScoreBoardSizeX = reader.GetReal("gui", "ScoreBoardSizeX", 1024.0f);
	m_Settings.fScoreBoardSizeY = reader.GetReal("gui", "ScoreBoardSizeY", 768.0f);
	// spawnscreen
	m_Settings.fSpawnScreenPosX = reader.GetReal("gui", "SpawnScreenPosX", 660.0f);
	m_Settings.fSpawnScreenPosY = reader.GetReal("gui", "SpawnScreenPosY", 950.0f);
	m_Settings.fSpawnScreenSizeX = reader.GetReal("gui", "SpawnScreenSizeX", 600.0f);
	m_Settings.fSpawnScreenSizeY = reader.GetReal("gui", "SpawnScreenSizeY", 100.0f);
	// nametags
	m_Settings.fHealthBarWidth = reader.GetReal("gui", "HealthBarWidth", 100.0f);
	m_Settings.fHealthBarHeight = reader.GetReal("gui", "HealthBarHeight", 10.0f);
}

bool CSettings::ToggleTimeStamp()
{
	char buff[0x7F];
	sprintf(buff, "%sSAMP/settings.ini", g_pszStorage);

	CSimpleIniA ini;
	ini.SetUnicode();
	ini.LoadFile(buff);
	SI_Error rc;

	bool timestamp = Get().szTimeStamp;

	rc = ini.SetBoolValue("client", "timestamp", !timestamp);
	rc = ini.SaveFile(buff);

	return (rc >= 0);
}