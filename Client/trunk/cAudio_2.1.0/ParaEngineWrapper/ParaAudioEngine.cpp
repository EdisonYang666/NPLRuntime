//-----------------------------------------------------------------------------
// Class:	ParaEngine Audio Engine Wrapper for cAudio engine(OpenAL, MP3, Vorbis OGG, WAV)
// Authors:	LiXizhi
// Company: ParaEngine
// Date:	2010.6.26
//-----------------------------------------------------------------------------
#include "PluginAPI.h"
#include "ParaAudioEngine.h"
#include <AL/al.h>

#include "cPluginManager.h"
#include "plugins/mp3Decoder/cMP3Plugin.h"
#include "plugins/EAXLegacyPreset/cEAXLegacyPresetPlugin.h"


using namespace ParaEngine;
using namespace cAudio;

/** 0 for left hand(directX), 1 for right hand(openGL, default).*/
static int g_nCoordinateSystem = 1;

PARAVECTOR3 ParaEngine::FixCoordinate(const PARAVECTOR3& v)
{
	return (g_nCoordinateSystem == 1) ? v : PARAVECTOR3(v.x, v.y, -v.z);
}

CParaAudioEngine::CParaAudioEngine()
	:m_audio_manager(NULL), m_plugin_mp3(NULL), m_plugin_presets(NULL)
{
#ifdef CAUDIO_COMPILE_WITH_PLUGIN_SUPPORT
	// load plugins for MP3 and effects
	cPluginManager* pluginManager = cAudio::cPluginManager::Instance();
	m_plugin_mp3 = new cMP3DecoderPlugin();
	if(m_plugin_mp3)
	{
		pluginManager->installPlugin(m_plugin_mp3, "plugin_mp3");
	}
#endif
	m_plugin_presets = new cEAXLegacyPresetPlugin();
	if(m_plugin_presets)
	{
		pluginManager->installPlugin(m_plugin_presets, "plugin_presets");
	}

	//Create an initialized Audio Manager
	m_audio_manager = cAudio::createAudioManager(false);
}

CParaAudioEngine::~CParaAudioEngine()
{
	if(m_audio_manager!=NULL)
	{
		//Delete all IAudio sounds
		releaseAllSources();
		//Shutdown cAudio
		shutDown();
		// destroy 
		cAudio::destroyAudioManager(m_audio_manager);
	}

	if(m_plugin_mp3 != NULL)
		m_plugin_mp3->drop();
	if(m_plugin_presets != NULL)
		m_plugin_presets->drop();
}

void CParaAudioEngine::Release()
{
	delete this;
}

bool CParaAudioEngine::initialize(const char* deviceName /*= 0x0*/, int outputFrequency /*= -1*/, int eaxEffectSlots /*= 4*/)
{
	return m_audio_manager->initialize(deviceName, outputFrequency, eaxEffectSlots);
}

void ParaEngine::CParaAudioEngine::SetDistanceModel( ParaAudioDistanceModelEnum eDistModel )
{
	ALenum distModel = AL_NONE;
	switch(eDistModel)
	{
	case Audio_DistModel_EXPONENT_DISTANCE:
		distModel = AL_EXPONENT_DISTANCE;
		break;
	case Audio_DistModel_EXPONENT_DISTANCE_CLAMPED:
		distModel = AL_EXPONENT_DISTANCE_CLAMPED;
		break;
	case Audio_DistModel_INVERSE_DISTANCE:
		distModel = AL_INVERSE_DISTANCE;
		break;
	case Audio_DistModel_INVERSE_DISTANCE_CLAMPED:
		distModel = AL_INVERSE_DISTANCE_CLAMPED;
		break;
	case Audio_DistModel_LINEAR_DISTANCE:
		distModel = AL_LINEAR_DISTANCE;
		break;
	case Audio_DistModel_LINEAR_DISTANCE_CLAMPED:
		distModel = AL_LINEAR_DISTANCE_CLAMPED;
		break;
	default:
		distModel = AL_NONE;
		break;
	}
	alDistanceModel(distModel);
}

IParaAudioSource* ParaEngine::CParaAudioEngine::getSoundByName( const char* name )
{
	// m_audio_manager->play();
	return NULL;
}

void ParaEngine::CParaAudioEngine::release( IParaAudioSource* source )
{
	if(source)
	{
		AudioMap_Type::iterator it, itEnd = m_audio_source_map.end();
		for ( it=m_audio_source_map.begin(); it != itEnd; it++ )
		{
			if( ((IParaAudioSource*)(it->second)) == source )
			{
				m_audio_manager->release(it->second->m_pSource);
				SAFE_DELETE(it->second);
				m_audio_source_map.erase(it);
				break;
			}
		}
	}
}

IParaAudioSource* ParaEngine::CParaAudioEngine::create( const char* name, const char* filename, bool stream /*= false*/ )
{
	IParaAudioSource* pSource = getSoundByName(name);
	if(pSource!=0)
		return pSource;
	IAudioSource* pSrc = m_audio_manager->create(name, filename, stream);
	if(pSrc)
	{
		CParaAudioSource* pSrc_ = new CParaAudioSource(pSrc);
		m_audio_source_map[name] =pSrc_;
		return pSrc_;
	}
	return NULL;
}

IParaAudioSource* ParaEngine::CParaAudioEngine::createFromMemory( const char* name, const char* data, size_t length, const char* extension )
{
	IParaAudioSource* pSource = getSoundByName(name);
	if(pSource!=0)
		return pSource;
	IAudioSource* pSrc = m_audio_manager->createFromMemory(name, data, length, extension);
	if(pSrc)
	{
		CParaAudioSource* pSrc_ = new CParaAudioSource(pSrc);
		m_audio_source_map[name] =pSrc_;
		return pSrc_;
	}
	return NULL;
}

IParaAudioSource* ParaEngine::CParaAudioEngine::createFromRaw( const char* name, const char* data, size_t length, unsigned int frequency, ParaAudioFormats format )
{
	IParaAudioSource* pSource = getSoundByName(name);
	if(pSource!=0)
		return pSource;
	IAudioSource* pSrc = m_audio_manager->createFromRaw(name, data, length, frequency, (AudioFormats)format);
	if(pSrc)
	{
		CParaAudioSource* pSrc_ = new CParaAudioSource(pSrc);
		m_audio_source_map[name] =pSrc_;
		return pSrc_;
	}
	return NULL;
}

void ParaEngine::CParaAudioEngine::releaseAllSources()
{
	AudioMap_Type::iterator it, itEnd = m_audio_source_map.end();
	for ( it=m_audio_source_map.begin(); it != itEnd; it++ )
	{
		CParaAudioSource* pSrc = it->second;
		SAFE_DELETE(pSrc);
	}
	m_audio_source_map.clear();

	m_audio_manager->releaseAllSources();
}

void ParaEngine::CParaAudioEngine::SetCoordinateSystem( int nLeftHand )
{
	g_nCoordinateSystem = nLeftHand;
}

const char* ParaEngine::CParaAudioEngine::getAvailableDeviceName(unsigned int index)
{
	return m_audio_manager->getAvailableDeviceName(index);
}

unsigned int ParaEngine::CParaAudioEngine::getAvailableDeviceCount()
{
	return m_audio_manager->getAvailableDeviceCount();
}

const char* ParaEngine::CParaAudioEngine::getDefaultDeviceName()
{
	return m_audio_manager->getDefaultDeviceName();
}

///////////////////////////////////////////////////////////////////////
// Audio Source
///////////////////////////////////////////////////////////////////////

void ParaEngine::CParaAudioSource::registerEventHandler( IAudioSourceEventHandler* handler )
{
	if(m_pEventHandler == NULL && m_pSource!=NULL)
	{
		m_pEventHandler = handler;
		m_pSource->registerEventHandler(this);
	}
}

void ParaEngine::CParaAudioSource::unRegisterAllEventHandlers()
{
	m_pEventHandler = NULL;
	m_pSource->unRegisterAllEventHandlers();
}

void ParaEngine::CParaAudioSource::onPlay()
{
	if(m_pEventHandler!=0)
	{
		m_pEventHandler->onPlay();
	}
}

void ParaEngine::CParaAudioSource::onStop()
{
	if(m_pEventHandler!=0)
	{
		m_pEventHandler->onPlay();
	}
}

void ParaEngine::CParaAudioSource::onUpdate()
{
	if(m_pEventHandler!=0)
	{
		m_pEventHandler->onUpdate();
	}
}

void ParaEngine::CParaAudioSource::onRelease()
{
	if(m_pEventHandler!=0)
	{
		m_pEventHandler->onRelease();
	}
}

void ParaEngine::CParaAudioSource::onPause()
{
	if(m_pEventHandler!=0)
	{
		m_pEventHandler->onPause();
	}
}

void ParaEngine::CParaAudioSource::release()
{
	m_pSource->release();
}

void ParaEngine::CParaAudioSource::setMaxDistance(const float& maxDistance)
{
	m_pSource->setMaxDistance(maxDistance);
}
