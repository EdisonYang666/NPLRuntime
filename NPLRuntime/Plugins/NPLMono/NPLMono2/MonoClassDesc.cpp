//-----------------------------------------------------------------------------
// Copyright (C) 2004 - 2009 ParaEngine Corporation, All Rights Reserved.
// Author: LiXizhi
// Date:	2009.7
// Desc: 
//-----------------------------------------------------------------------------

#include "NPLMono.h"

// ParaEngine includes
#include "PluginAPI.h"
#include "MonoScriptingState.h"

using namespace ParaEngine;

// the host application's NPL_Mono2_CLASS_ID must match this one. 
#define NPL_Mono2_CLASS_ID Class_ID(0x3b903b30, 0x57e409be)


/** description class */
class CMonoClassDesc : public ClassDescriptor 
{
public:
	void* Create(bool loading = FALSE) 
	{ 
		return new CMonoScriptingState(); 
	}

	const char* ClassName() 
	{ 
		return "CMonoScriptingState"; 
	}

	SClass_ID SuperClassID() 
	{ 
		return OBJECT_MODIFIER_CLASS_ID; 
	}

	Class_ID ClassID() 
	{ 
		return NPL_Mono2_CLASS_ID;
	}

	const char* Category() 
	{ 
		return "NPLFile"; 
	}

	const char* InternalName() 
	{ 
		return "NPLMono2"; 
	}	

	HINSTANCE HInstance() 
	{ 
		extern HINSTANCE Instance;
		return Instance; 
	}
};

ClassDescriptor* NPLMono_GetClassDesc() 
{ 
	static CMonoClassDesc Desc;
	return &Desc; 
}
