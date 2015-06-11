#ifndef NGINE_TEXTUREMANAGER_HDR
#define NGINE_TEXTUREMANAGER_HDR

/***************************************************************************************************************/
#include "NAssetManager.h"
#include "NTexture.h"
/***************************************************************************************************************/


///Manager for Texture Resources
class NTextureManager : public NAssetManager<string, NTexture> {

public:
	///Load a Texture from File (loadInfo should be the File name)
	bool loadAsset(const string &key, const void *loadInfo);

	///Unload a Texture
	void unloadAsset(const string &key);

    ///Unload all Resources
	~NTextureManager(void);
};

#endif // NGINE_TEXTUREMANAGER_HDR
