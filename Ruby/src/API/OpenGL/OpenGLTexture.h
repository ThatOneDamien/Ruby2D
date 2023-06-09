#pragma once

#include "Ruby/Render/Texture.h"

namespace Ruby {

	class OpenGLTexture : public Texture
	{
	public:
		OpenGLTexture(const std::string& filepath);
		OpenGLTexture(int width, int height);
		virtual ~OpenGLTexture();

		virtual void bind(uint8_t slot) const override;
		virtual void unbind() const override;
		virtual void setData(const void* data, uint32_t size) override;

	private:
		uint32_t m_RendererID;
		mutable int8_t m_BoundSlot; // If set to -1, texture is currently not bound
		uint32_t m_FormatIntern, m_FormatRender;
		int m_Width, m_Height, m_BPP;
	};

}