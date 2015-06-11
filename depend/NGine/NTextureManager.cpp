#include "NTextureManager.h"


/***************************************************************************************************************/
bool NTextureManager::loadAsset(const string &key, const void *loadInfo) {

	if(loadInfo == nullptr)     {
		cerr << "No File Name passed" << endl;
		return false;
	}
	if(containsAsset(key))      {
		cerr << "Key " << key << " is already in use" << endl;
		return false;
	}

	//Cast loading Information
	string src = (const char *)loadInfo;

	//Load Surface into Main RAM
	sf::Texture *result = new sf::Texture();

	if( !result->loadFromFile(src) ){
		cerr << "Texture Surface from File '" << src << "' could not be loaded" << endl;
		return false;
	}

    //Create an OpenGL compatible Texture from the optimized Surface
	NTexture tex;
	tex.m_texture = result;
	tex.findGLId();

    //Add Texture to List
	m_assets.insert(std::make_pair(key, tex));

	cout << "Successfully loaded Texture '" << key << "' (" << tex.getWidth() << "x" << tex.getHeight() << "p) from File '" << src << "'" << endl;
	return true;
}
/***************************************************************************************************************/


/***************************************************************************************************************/
void NTextureManager::unloadAsset(const string &key) {

	if(!containsAsset(key)) {
		cerr << "Texture '" << key << "'" << " not included in List" << endl;
		return;
	}

	m_assets.at(key).unloadTexture();

    m_assets.erase(key);

	cout << "Successfully unloaded Texture '" << key << "'" << endl;
}
/***************************************************************************************************************/


/***************************************************************************************************************/
NTextureManager::~NTextureManager(void){

	for(auto iter = m_assets.rbegin(); iter != m_assets.rend(); ++iter){

        iter->second.unloadTexture();
        cout << "Successfully unloaded Texture '" << iter->first << "'" << endl;
	}

	m_assets.clear();
}
/***************************************************************************************************************/
