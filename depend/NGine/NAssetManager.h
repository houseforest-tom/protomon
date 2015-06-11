#ifndef NGINE_ASSETMANAGER_HDR
#define NGINE_ASSETMANAGER_HDR

/***************************************************************************************************************/
#include "NBase.h"
#include <map>
/***************************************************************************************************************/


///Virtual Manager Base Class for any Kind of Resource that requires
///Loading and Unloading from Filesystem
template<typename KeyType, typename ValueType>
class NAssetManager{

protected:
    ///List of loaded Assets
    typename std::map<const KeyType, ValueType> m_assets = { };

    ///Error Asset Key
    KeyType m_errorKey = { };

public:
    ///Returns whether an Asset of the given Key was loaded already
    inline bool containsAsset(const KeyType &key) const{

        return (m_assets.count(key) > 0);
    }

    ///Load an Asset and add It to the List
    virtual bool loadAsset(const KeyType &key, const void *loadInfo) = 0;

    ///Return a Reference to a loaded Asset
    inline const ValueType &getAsset(const KeyType &key) const{

        if(containsAsset(key)) return m_assets.at(key);
        else{
            cerr << "Asset '" << key << "' could not be found\nReturning Error Asset '" << m_errorKey << "' instead" << endl;
            return m_assets.at(m_errorKey);
        }
    }

    ///Unload an Asset and remove It from the List
    virtual void unloadAsset(const KeyType &key) = 0;

    ///Set an Error Asset
    inline void setErrorKey(const KeyType &errorAssetKey){

        m_errorKey = errorAssetKey;
    }

    virtual ~NAssetManager(void){ };
};

#endif // NGINE_ASSETMANAGER_HDR
