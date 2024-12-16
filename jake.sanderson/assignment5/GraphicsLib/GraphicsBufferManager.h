#pragma once

#include <string>
#include <unordered_map>
#include <Trackable.h>
#include "Color.h"

class GraphicsBuffer;

typedef std::string BufferKey;

class GraphicsBufferManager : public Trackable
{
public:
	GraphicsBufferManager() {};
	~GraphicsBufferManager();

	bool init();

	void cleanup();

	GraphicsBuffer* createAndManageBuffer(const BufferKey& key, const std::string filename);
	GraphicsBuffer* createAndManageBuffer(const BufferKey& key, unsigned int width, unsigned int height, Color color = Color());

	void deleteBuffer(const BufferKey& key);
	void deleteBuffer(GraphicsBuffer* pBufferToBeDeleted);

	GraphicsBuffer* getBuffer(const BufferKey& key) const;

private:
	std::unordered_map<BufferKey, GraphicsBuffer*> mMap;
};

