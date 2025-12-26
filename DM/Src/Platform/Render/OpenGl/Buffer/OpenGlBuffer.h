#pragma once
#include<DMPCH.h>
#include<glad/glad.h>
#include<Core/Render/Buffer.h>
namespace DM
{
	//class Buffer
	//{
	//public:
	//	explicit Buffer(const uint32_t Type)
	//	{
	//		this->Type = Type;
	//		glGenBuffers(1, &Id);
	//	}
	//	~Buffer()
	//	{
	//		glDeleteBuffers(1, &Id);
	//	}
	//	inline void Bind() { glBindBuffer(Type, Id); }
	//	//inline void UnBind() { glBindBuffer(Type, 0); }
	//	template<typename T>
	//	void BufferStaticData(const std::vector<T>& Data);
	//	template<typename T>
	//	void BufferDynamicData(const std::vector<T>& Data);
	//	template<typename T>
	//	void BufferStreamData(const std::vector<T>& Data);
	//	inline bool IsValid() { return Id != 0; }
	//	inline int GetBufferDateSize()const { return Size; }
	//private:
	//	template<typename T>
	//	void BufferData(const std::vector<T>& Data, const GLenum& Usage);
	//private:
	//	GLenum Type;
	//	GLuint Id;
	//	int Size = 0;
	//	Buffer(const Buffer&) = delete;
	//	Buffer(Buffer&) = delete;
	//	Buffer(Buffer&&) noexcept = delete;
	//	Buffer& operator=(Buffer&) = delete;
	//	Buffer& operator=(Buffer&&) noexcept = delete;
	//};
	//template<typename T>
	//inline void Buffer::BufferStaticData(const std::vector<T>& Data)
	//{
	//	BufferData(Data, GL_STATIC_DRAW);
	//}
	//template<typename T>
	//inline void Buffer::BufferDynamicData(const std::vector<T>& Data)
	//{
	//	BufferData(Data, GL_DYNAMIC_DRAW);
	//}
	//template<typename T>
	//inline void Buffer::BufferStreamData(const std::vector<T>& Data)
	//{
	//	BufferData(Data, GL_STREAM_DRAW);
	//}
	//template<typename T>
	//inline void Buffer::BufferData(const std::vector<T>& Data, const GLenum& Usage)
	//{
	//	assert(IsValid() && "Cannot write data to invalid buffer");
	//	const auto& size = Data.size();
	//	this->Size = size;
	//	glBufferData(this->Type, sizeof(T) * size, &Data[0], Usage);
	//}
	//class VertexBuffer :public Buffer
	//{
	//public:
	//	VertexBuffer() :Buffer(GL_ARRAY_BUFFER) {}
	//	static std::shared_ptr<VertexBuffer>MakeSPtr()
	//	{
	//		return std::make_shared<VertexBuffer>();
	//	}
	//};
	//class IndexBuffer :public Buffer
	//{
	//public:
	//	IndexBuffer() :Buffer(GL_ELEMENT_ARRAY_BUFFER) {}
	//	static std::shared_ptr<IndexBuffer>MakeSPtr()
	//	{
	//		return std::make_shared<IndexBuffer>();
	//	}
	//};

	class OpenGlVertexBuffer :public VertexBuffer
	{
	public:
		OpenGlVertexBuffer(float* vertices, uint32_t elementCount);
		virtual ~OpenGlVertexBuffer() = default;
		virtual void Bind()override;
		virtual void UnBind()override;
		virtual void SetLayout(const BufferLayout& layout) override { m_Layout = layout; }
		virtual BufferLayout GetLayout()const override { return m_Layout; }
	private:
		uint32_t m_Id;
		BufferLayout m_Layout;
	};
	class OpenGlIndexBuffer :public IndexBuffer
	{
	public:
		OpenGlIndexBuffer(uint32_t* indices, uint32_t elementCount);
		virtual ~OpenGlIndexBuffer() = default;
		virtual void Bind()override;
		virtual void UnBind()override;
		virtual uint32_t GetCount()const override;
	private:
		uint32_t m_Id;
		uint32_t m_Count;

	};
}
