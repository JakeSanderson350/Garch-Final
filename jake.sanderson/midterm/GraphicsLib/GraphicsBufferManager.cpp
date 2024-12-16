#include "GraphicsBufferManager.h"
#include "GraphicsBuffer.h"

GraphicsBufferManager::~GraphicsBufferManager()
{
	cleanup();
}

bool GraphicsBufferManager::init()
{
	return true;
}

void GraphicsBufferManager::cleanup()
{
	//Deletes every buffer in map
	for (auto iter : mMap)
	{
		GraphicsBuffer* pBufferToBeDeleted = iter.second;
		delete pBufferToBeDeleted;
	}

	mMap.clear();
}

GraphicsBuffer* GraphicsBufferManager::createAndManageBuffer(const BufferKey& key, const std::string filename)
{
	GraphicsBuffer* pNewGraphicsBuffer = nullptr;

	std::unordered_map<BufferKey, GraphicsBuffer*>::iterator iter = mMap.find(key);

	//Checks if buffer in map already
	if (iter == mMap.end())
	{
		//Makes new buffer using filename
		pNewGraphicsBuffer = new GraphicsBuffer(filename);

		mMap[key] = pNewGraphicsBuffer;
	}

	return pNewGraphicsBuffer;
}

GraphicsBuffer* GraphicsBufferManager::createAndManageBuffer(const BufferKey& key, unsigned int width, unsigned int height, Color color)
{
	GraphicsBuffer* pNewGraphicsBuffer = nullptr;

	std::unordered_map<BufferKey, GraphicsBuffer*>::iterator iter = mMap.find(key);

	//Checks if buffer in map already
	if (iter == mMap.end())
	{
		//Makes new buffer using dimensions and a color
		pNewGraphicsBuffer = new GraphicsBuffer(width, height, color);

		mMap[key] = pNewGraphicsBuffer;
	}

	return pNewGraphicsBuffer;
}

void GraphicsBufferManager::deleteBuffer(const BufferKey& key)
{
	std::unordered_map<BufferKey, GraphicsBuffer*>::iterator iter = mMap.find(key);

	//Deletes the buffer with the matching key
	if (iter != mMap.end())
	{
		delete iter->second;
		mMap.erase(iter);
	}
}

void GraphicsBufferManager::deleteBuffer(GraphicsBuffer* pBufferToBeDeleted)
{
	//Goes through map and deletes buffer that matches pointer
	for (auto iter : mMap)
	{
		if (pBufferToBeDeleted == iter.second)
		{
			delete pBufferToBeDeleted;
			mMap.erase(iter.first);
			return;
		}
	}
}

GraphicsBuffer* GraphicsBufferManager::getBuffer(const BufferKey& key) const
{
	auto iter = mMap.find(key);

	//If map found return buffer
	if (iter != mMap.end())
	{
		return iter->second;
	}
	//If not found return nullptr
	else
	{
		return nullptr;
	}
}
