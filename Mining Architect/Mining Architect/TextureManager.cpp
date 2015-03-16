 #include "TextureManager.h"

TextureManager* TextureManager::me;

TextureManager* TextureManager::getManager()
{
	if(!me)
	{
		me=new TextureManager();
	}
	return me;
}


TextureManager::TextureManager(void)
{
}


TextureManager::~TextureManager(void)
{
}


void TextureManager::createArrays()
{
}