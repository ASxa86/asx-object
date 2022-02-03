#include <asx-gl/Window.h>
#include <gtest/gtest.h>
#include <chrono>
#include <iostream>
#include <numeric>

#include <asx-gl/ElementBufferObject.h>
#include <asx-gl/Image.h>
#include <asx-gl/Sprite.h>
#include <asx-gl/Texture.h>
#include <asx-gl/VertexArrayObject.h>

using namespace asx;

constexpr std::string_view ShaderVertex = R"(
	#version 450 core
	layout (location = 0) in vec3 pos;
	layout (location = 1) in vec4 color;
	layout (location = 2) in vec2 texCoord;

	out vec4 outColor;
	out vec2 outTexCoord;

	void main()
	{
		gl_Position = vec4(pos.x, pos.y, pos.z, 1.0);
		outColor = color;
		outTexCoord = texCoord;
	}
)";

constexpr std::string_view ShaderFragment = R"(
	#version 450 core
	out vec4 FragColor;

	in vec4 outColor;
	in vec2 outTexCoord;

	uniform sampler2D texture1;

	void main()
	{
		FragColor = texture(texture1, outTexCoord) * outColor;
	}
)";

namespace asx
{
	class Event
	{
	};
}

TEST(Window, VertexArrayObject)
{
	Window window;

	Image image;
	ASSERT_TRUE(image.loadFromFile("sprite.png"));

	Texture texture;
	ASSERT_TRUE(texture.loadFromImage(image));

	Shader shader;
	ASSERT_TRUE(shader.loadFromMemory(ShaderVertex, ShaderFragment));

	VertexArrayObject vao{Primitive::TriangleStrip};

	std::vector<Vertex> vertices(4);
	vertices[0].position = {-0.5f, -0.5f, 0.0f};
	vertices[0].color = {1.0f, 0.0, 0.0, 1.0f};
	vertices[0].texCoord = {0.0f, 0.0f};

	vertices[1].position = {0.5f, -0.5f, 0.0f};
	vertices[1].color = {0.0f, 1.0, 0.0, 1.0f};
	vertices[1].texCoord = {1.0f, 0.0f};

	vertices[2].position = {-0.5f, 0.5f, 0.0f};
	vertices[2].color = {0.0f, 0.0, 1.0, 1.0f};
	vertices[2].texCoord = {0.0f, 1.0f};

	vertices[3].position = {0.5f, 0.5f, 0.0f};
	vertices[3].color = {0.5f, 0.5, 0.0, 1.0f};
	vertices[3].texCoord = {1.0f, 1.0f};
	vao.setVertices(vertices);

	EXPECT_TRUE(window.open());

	RenderStates states;
	states.shader = &shader;

	auto count = 0;
	std::vector<std::chrono::duration<double>> frames;
	frames.reserve(10'000'000);

	while(window.open() == true && count < 100000)
	{
		auto start = std::chrono::steady_clock::now();
		count++;

		asx::Event e;
		while(window.pollEvent(e) == true)
		{
		}

		window.clear({0.2f, 0.3f, 0.3f, 1.0f});
		window.draw(vao, states);
		window.display();

		std::chrono::duration<double> elapsed = std::chrono::steady_clock::now() - start;
		frames.push_back(elapsed);
	}

	const auto sum = std::accumulate(std::begin(frames), std::end(frames), decltype(frames)::value_type::zero());
	const auto avg = sum / frames.size();
	std::cout << "Elapsed: " << avg.count() << " FPS: " << 1.0 / avg.count() << "\n";
}

TEST(Window, ElementBufferObject)
{
	Window window;

	Shader shader;
	ASSERT_TRUE(shader.loadFromMemory(ShaderVertex, ShaderFragment));

	Image image;
	ASSERT_TRUE(image.loadFromFile("sprite.png"));

	Texture texture;
	ASSERT_TRUE(texture.loadFromImage(image));

	ElementBufferObject ebo{Primitive::Triangles};

	std::vector<Vertex> vertices(4);
	vertices[0].position = {-0.5f, -0.5f, 0.0f};
	vertices[0].color = {0.7f, 0.3f, 0.25f, 0.5f};
	vertices[0].texCoord = {0.0f, 0.0f};

	vertices[1].position = {0.5f, -0.5f, 0.0f};
	vertices[1].color = {0.7f, 0.3f, 0.25f, 0.5f};
	vertices[1].texCoord = {1.0f, 0.0f};

	vertices[2].position = {0.5f, 0.5f, 0.0f};
	vertices[2].color = {0.7f, 0.3f, 0.25f, 0.5f};
	vertices[2].texCoord = {1.0f, 1.0f};

	vertices[3].position = {-0.5f, 0.5f, 0.0f};
	vertices[3].color = {0.7f, 0.3f, 0.25f, 0.5f};
	vertices[3].texCoord = {0.0f, 1.0f};
	ebo.setVertices(vertices);

	std::vector<unsigned int> indices{{0, 1, 3, 1, 2, 3}};
	ebo.setIndices(indices);

	EXPECT_TRUE(window.open());

	RenderStates states;
	states.shader = &shader;

	auto count = 0;
	std::vector<std::chrono::duration<double>> frames;
	frames.reserve(10'000'000);

	while(window.open() == true && count < 1000000)
	{
		auto start = std::chrono::steady_clock::now();
		count++;

		asx::Event e;
		while(window.pollEvent(e) == true)
		{
		}

		window.clear({0.2f, 0.3f, 0.3f, 1.0f});
		window.draw(ebo, states);
		window.display();

		std::chrono::duration<double> elapsed = std::chrono::steady_clock::now() - start;
		frames.push_back(elapsed);
	}

	const auto sum = std::accumulate(std::begin(frames), std::end(frames), decltype(frames)::value_type::zero());
	const auto avg = sum / frames.size();
	std::cout << "Elapsed: " << avg.count() << " FPS: " << 1.0 / avg.count() << "\n";
}

TEST(Window, Sprite)
{
	Window window;

	Image image;
	ASSERT_TRUE(image.loadFromFile("sprite.png"));

	Texture texture;
	ASSERT_TRUE(texture.loadFromImage(image));

	Sprite sprite{texture};
	sprite.setPosition({-0.5f, 0.0f});
	sprite.setScale({0.5, 0.5});

	Sprite sprite2{texture};
	sprite2.setPosition({0.5f, 0.0f});
	sprite2.setScale({0.5, 0.5});
	sprite2.setRotation(45.0f);

	EXPECT_TRUE(window.open());

	auto count = 0;
	std::vector<std::chrono::duration<double>> frames;
	frames.reserve(10'000'000);

	while(window.open() == true && count < 100000)
	{
		auto start = std::chrono::steady_clock::now();
		count++;

		asx::Event e;
		while(window.pollEvent(e) == true)
		{
		}

		window.clear({0.2f, 0.3f, 0.3f, 1.0f});
		window.draw(sprite);
		window.draw(sprite2);
		window.display();

		std::chrono::duration<double> elapsed = std::chrono::steady_clock::now() - start;
		frames.push_back(elapsed);
	}

	const auto sum = std::accumulate(std::begin(frames), std::end(frames), decltype(frames)::value_type::zero());
	const auto avg = sum / frames.size();
	std::cout << "Elapsed: " << avg.count() << " FPS: " << 1.0 / avg.count() << "\n";
}