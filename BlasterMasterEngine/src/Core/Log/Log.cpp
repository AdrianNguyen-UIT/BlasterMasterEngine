#include "d3dpch.h"
#include "Log.h"

std::shared_ptr<spdlog::logger> Log::s_Logger;

Log::Log()
{

}

Log::~Log()
{

}

void Log::Init()
{
	spdlog::set_pattern("%^[%T] %n->%l: %v%$");

	s_Logger = spdlog::stdout_color_mt("APPLICATION");
	s_Logger->set_level(spdlog::level::trace);
}

std::shared_ptr<spdlog::logger> Log::GetLogger()
{
	return Log::s_Logger;
}
