#pragma once

#include "../util/def.hh"

#include <cstdint>
#include <initializer_list>

struct FBO
{
	using AttachmentType = uint8_t;
	static constexpr AttachmentType COLOR = 1 << 0;
	static constexpr AttachmentType ALPHA = 2 << 1;
	static constexpr AttachmentType DEPTH = 3 << 2;
	static constexpr AttachmentType STENCIL = 4 << 3;
	
	//FBOs must be pointers and can't be copied or moved
	FBO() = delete;
	FBO(FBO const &other) = delete;
	FBO(FBO const &&other) = delete;
	FBO(uint32_t width, uint32_t height, AttachmentType options, std::string const &name);
	~FBO();
	
	void regen(uint32_t width, uint32_t height);
	void bindFBO();
	void bindColor(uint32_t target);
	void bindDepth(uint32_t target);
	
	void print();
	
	uint32_t handle = 0, colorHandle = 0, depthHandle = 0, width = 0, height = 0;
	bool hasColor = false, hasAlpha = false, hasDepth = false, hasStencil = false;
	std::string name = "";
};

struct FBOPool
{
	FBOPool() = delete;
	FBOPool(FBOPool const &other) = delete;
	FBOPool(FBOPool const &&other) = delete;
	FBOPool(size_t alloc, uint32_t width, uint32_t height);
	
	SP<FBO> getNextAvailableFBO(uint32_t width, uint32_t height);

private:
	std::vector<SP<FBO>> pool;
};

void initFBOPool(size_t alloc, uint32_t width, uint32_t height);

extern UP<FBOPool> fboPool;
