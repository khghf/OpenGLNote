#pragma once
#include<Buffer.h>
#include<vector>
struct VertexAttribute
{
	enum ComponentType {
		UShort = GL_UNSIGNED_SHORT,
		Int = GL_INT,
		UInt = GL_UNSIGNED_INT,
		Byte = GL_BYTE,
		Float = GL_FLOAT,
	};
	GLuint Location = -1;//对应着色器中的 location
	GLenum Type; //数据类型（如 GL_FLOAT）
	uint8_t ComponentCount;//总的分量数(1`4,vec1~vec4)
	bool bNormalized = false;//是否归一化
	int32_t Stride;//步长（两个顶点的同属性之间的字节距离）。
	//例如{位置1：1，1，1，颜色：5，5，0，位置2：2，2，2，颜色：6，6，0}
	//位置1到位置2就是6
	uint32_t Offset;
	//@Location 对应着色器中的Layout(Location=xx)
	//@ComponentCount,顶点属性的分量个数如Layout(Location=xx)vec3,就是3
	//@Type,顶点属性分量的数据类型，如vec3(1.0,1.0,1.0)就是GL_FLOAT
	//@Stride,同一类型的顶点属性之间的步长，注意这里指的是字节数
	//		Layout(Location=0)vec3位置
	//		Layout(Location=1)vec2纹理坐标
	//		如果一个数组同时存储这两种数据如果是float那么就应该是5*sizeof(float)
	//@Offset，数据开始位置，
	//		Layout(Location = 0)vec3位置
	//		Layout(Location=1)vec2纹理坐标
	//		在指定纹理坐标布局时那么其Offset为3
	VertexAttribute(GLuint Location, uint8_t ComponentCount, GLenum Type, int32_t Stride,uint32_t Offset) :
		Location(Location),
		ComponentCount(ComponentCount),
		Type(Type),
		bNormalized(false),
		Stride(Stride),
		Offset(Offset) 
	{
	}
};
class VertexArray
{
private:
	uint32_t Id = 0;
	SPtr<VertexBuffer>VBO;
	SPtr<IndexBuffer>IBO;
public:
	VertexArray();
	~VertexArray() {}
	template<typename T>
	explicit VertexArray(const std::vector<T>& Vertex, bool bDynamic = false);//指定顶点数据
	template<typename VertexT,typename IndexT>
	explicit VertexArray(const std::vector<VertexT>& Vertex, const std::vector<IndexT>& Index, bool bDynamic = false);//指定顶点、索引数据
	inline void Bind()
	{
		glBindVertexArray(Id);
		if (VBO)VBO->Bind();
		if (IBO)IBO->Bind();
	}
	inline void UnBind()
	{
		glBindVertexArray(0);
	}
	void Render(GLenum DrawMode = GL_TRIANGLES);
	void RenderVertex(GLenum DrawMode = GL_TRIANGLES);
	void RenderIndex(GLenum DrawMode=GL_TRIANGLES);//默认绘制三角形
	void AddVertexAttributeConfig(const std::vector<VertexAttribute>& Attributes);
};
template<typename T>
inline VertexArray::VertexArray(const std::vector<T>& Vertex, bool bDynamic)
{
	glGenVertexArrays(1, &Id);
	VBO = std::make_shared<VertexBuffer>(GL_ARRAY_BUFFER);
	Bind();
	if (bDynamic)
	{
		VBO->BufferDynamicData(Vertex);
	}
	else
	{
		VBO->BufferStaticData(Vertex);
	}
	UnBind();
}

template<typename VertexT, typename IndexT>
inline VertexArray::VertexArray(const std::vector<VertexT>& Vertex, const std::vector<IndexT>& Index, bool bDynamic)
{
	glGenVertexArrays(1, &Id);
	//创建缓冲区
	VBO = std::make_shared<VertexBuffer>();
	IBO = std::make_shared<IndexBuffer>();
	//绑定并填充数据
	Bind();
	if (bDynamic)
	{
		VBO->BufferDynamicData(Vertex);
		IBO->BufferDynamicData(Index);
	}
	else
	{
		VBO->BufferStaticData(Vertex);
		IBO->BufferStaticData(Index);
	}
	UnBind();
}

