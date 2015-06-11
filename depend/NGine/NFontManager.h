#ifndef NGINE_FONTMANAGER_HDR
#define NGINE_FONTMANAGER_HDR

/***************************************************************************************************************/
#include "NAssetManager.h"
#include "NFont.h"
/***************************************************************************************************************/

class NFontManager : public NAssetManager<string, NFont>{

public:
    ///Load a True Type Font from File
    bool loadAsset(const string &key, const void *loadData);

    ///Unload a True Type Font
    void unloadAsset(const string &key);

    ///Unload all Resources
    ~NFontManager(void);
};

#endif // NGINE_FONTMANAGER_HDR
