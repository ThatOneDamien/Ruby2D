#pragma once

#include "Ruby/Render/VertexArray.h"

namespace Ruby {

	class OpenGLVA : public VertexArray
	{
	public:
		OpenGLVA();
		virtual ~OpenGLVA();

		virtual void bind() const override;
		virtual void unbind() const override;

		virtual void pushVertexBuffer(const SharedPtr<VertexBuffer>& buffer) override;
		virtual void setIndexBuffer(const SharedPtr<IndexBuffer>& buffer) override;

		virtual inline const std::vector<SharedPtr<VertexBuffer> >& getVertexBufferList() const override { return m_VertexBuffers; }
		virtual inline const SharedPtr<IndexBuffer>& getIndexBuffer() const override { return m_IndexBuffer; }

	private:
		uint32_t m_RendererID;
		std::vector<SharedPtr<VertexBuffer>> m_VertexBuffers;
		SharedPtr<IndexBuffer> m_IndexBuffer;
	};

}