#include "ParaEngine.h"
#include "ParaEngineSettings.h"
#include "util/os_calls.h"
#include "util/StringHelper.h"
#include "ObjectAutoReleasePool.h"
#include "AttributesManager.h"
#include "PluginManager.h"
#include "MeshPhysicsObject.h"
#include "MeshObject.h"
#include "MissileObject.h"
#include "BipedObject.h"
#include "BMaxModel/BMaxObject.h"
#include "SkyMesh.h"
#include "BlockPieceParticle.h"
#include "ContainerObject.h"
#include "RenderTarget.h"
#include "WeatherEffect.h"
#include "OverlayObject.h"
#include "LightObject.h"
#include "NPLRuntime.h"
#include "EventsCenter.h"
#include "BootStrapper.h"
#include "NPL/NPLHelper.h"
#include "AISimulator.h"
#include "AsyncLoader.h"
#include "FileManager.h"
#include "Archive.h"
#include "NPLPackageConfig.h"
#include "IO/ResourceEmbedded.h"
#include "GeosetObject.h"
#include "2dengine/GUIRoot.h"
#include "2dengine/GUIMouseVirtual.h"
#include "FrameRateController.h"
#include "FileLogger.h"
#include "Render/IRenderContext.h"
#include "InfoCenter/ICDBManager.h"
#include "InfoCenter/ICConfigManager.h"
#include "SceneObject.h"
#include "ParaWorldAsset.h"
#include "terrain/Terrain.h"
#include "ViewportManager.h"
#include "MoviePlatform.h"
#include "Framework/Common/Time/ParaTimer.h"
#include "EnvironmentSim.h"
#include "AutoCamera.h"
#include "BlockEngine/BlockWorldClient.h"
#include "BlockEngine/BlockWorldManager.h"
#include "ObjectManager.h"
#include "2dengine/GUIHighlight.h"
#include "WindowsApplication.h"
using namespace  ParaEngine;

void ParaEngine::CWindowsApplication::GameToClient(int& inout_x, int & inout_y, bool bInBackbuffer /*= true*/)
{
	throw std::logic_error("The method or operation is not implemented.");
}

void ParaEngine::CWindowsApplication::ClientToGame(int& inout_x, int & inout_y, bool bInBackbuffer /*= true*/)
{
	throw std::logic_error("The method or operation is not implemented.");
}

void ParaEngine::CWindowsApplication::SetRefreshTimer(float fTimeInterval, int nFrameRateControl /*= 0*/)
{
	throw std::logic_error("The method or operation is not implemented.");
}

bool ParaEngine::CWindowsApplication::AppHasFocus()
{
	throw std::logic_error("The method or operation is not implemented.");
}

void ParaEngine::CWindowsApplication::GetStats(string& output, DWORD dwFields)
{
	throw std::logic_error("The method or operation is not implemented.");
}

bool ParaEngine::CWindowsApplication::WriteRegStr(const string& root_key, const string& sSubKey, const string& name, const string& value)
{
	throw std::logic_error("The method or operation is not implemented.");
}

void ParaEngine::CWindowsApplication::SetAutoLowerFrameRateWhenNotFocused(bool bEnabled)
{
	throw std::logic_error("The method or operation is not implemented.");
}

const char* ParaEngine::CWindowsApplication::ReadRegStr(const string& root_key, const string& sSubKey, const string& name)
{
	throw std::logic_error("The method or operation is not implemented.");
}

bool ParaEngine::CWindowsApplication::WriteRegDWORD(const string& root_key, const string& sSubKey, const string& name, DWORD value)
{
	throw std::logic_error("The method or operation is not implemented.");
}

DWORD ParaEngine::CWindowsApplication::ReadRegDWORD(const string& root_key, const string& sSubKey, const string& name)
{
	throw std::logic_error("The method or operation is not implemented.");
}

bool ParaEngine::CWindowsApplication::GetAutoLowerFrameRateWhenNotFocused()
{
	throw std::logic_error("The method or operation is not implemented.");
}

void ParaEngine::CWindowsApplication::SetToggleSoundWhenNotFocused(bool bEnabled)
{
	throw std::logic_error("The method or operation is not implemented.");
}

bool ParaEngine::CWindowsApplication::GetToggleSoundWhenNotFocused()
{
	throw std::logic_error("The method or operation is not implemented.");
}
