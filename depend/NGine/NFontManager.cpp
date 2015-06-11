#include "NFontManager.h"

/***************************************************************************************************************/
bool NFontManager::loadAsset(const string &key, const void *loadData){

    //Check given File Name for Consistency
    const char *file = (const char*)loadData;
    if(file == nullptr || file[0] == '\0'){
        cerr << "No valid True Type Font File specified" << endl;
        return false;
    }

    //Load Font from File
    sf::Font *result = new sf::Font();
    if( !result->loadFromFile(file) ){
        cerr << "True Type Font from File " << file << " could not be loaded" << endl;
        return false;
    }

    NFont font;
    font.m_font = result;

    //Add loaded Font to List
    m_assets.insert(std::make_pair(key, font));

    cout << "Successfully loaded Font '" << key << "' from File '" << file << "'" << endl;
    return true;
}
/***************************************************************************************************************/


/***************************************************************************************************************/
void NFontManager::unloadAsset(const string &key){

    if(!containsAsset(key)) {
		cerr << "Font '" << key << "'" << " not included in List" << endl;
		return;
	}

	m_assets.erase(key);

	cout << "Successfully unloaded Font '" << key << "'" << endl;
}
/***************************************************************************************************************/


/***************************************************************************************************************/
NFontManager::~NFontManager(void){

    for(auto iter = m_assets.rbegin(); iter != m_assets.rend(); ++iter){
        iter->second.unloadTTF();
        cout << "Successfully unloaded Font '" << iter->first << "'" << endl;
    }

    m_assets.clear();
}
/***************************************************************************************************************/
