#pragma once
#include "Shader.hpp"

class ShaderParticle : public Shader
{
	ShaderParticle(const char * vertex_file_path, const char * fragment_file_path) : Shader::Shader(vertex_file_path, fragment_file_path)
	{
	}
};