#include "TimeLogger.h"

#include <stdexcept>
#include <algorithm>

void Profiling::TimeLogger::start_session(const std::string& file_path, size_t buffer_size) {
	if (m_is_in_session)
		throw std::runtime_error("Can't start session because the session is already started!");
	std::lock_guard<std::mutex> lock(m_mutex);
	m_out.open(file_path);
	if (!m_out) throw std::runtime_error("Can't open file: " + file_path);
	m_profile_buffer.reserve(buffer_size);
	m_init_buffer_size = m_profile_buffer.capacity();
	m_is_in_session = true;
}

void Profiling::TimeLogger::end_session() {
	if (!m_is_in_session)
		throw std::runtime_error("Can't end session because the session was not started!");
	std::lock_guard<std::mutex> lock(m_mutex);
	record_session();
	m_profile_buffer.clear();
	m_out.close();
	m_is_in_session = false;
	if (m_init_buffer_size != m_profile_buffer.capacity())
		throw std::runtime_error("The buffer was overloaded so the time was spend for reallocation!");
}

void Profiling::TimeLogger::save_profile(ProfileResult&& result) {
	// Может быть вызван только из TimeCapture только если is_in_session() == true
	std::lock_guard<std::mutex> lock(m_mutex);
	m_profile_buffer.push_back(std::move(result));
}

static inline void erase(std::string& str, const char* ch_arr) {
	if (auto pos = str.find(ch_arr); pos != std::string::npos)
		str.erase(pos, pos + std::strlen(ch_arr));
}

void Profiling::TimeLogger::record_session() {
	m_out << "{\"otherData\": {";
	if (m_init_buffer_size != m_profile_buffer.capacity())
		m_out << "\"issues\":\"the buffer was overloaded so the time was spend for reallocation\"";
	m_out << "},\"traceEvents\":[" << std::flush;
	for (auto it = m_profile_buffer.begin(); it != m_profile_buffer.end(); ++it) {
		if (it != m_profile_buffer.begin()) m_out << ",";
		std::string name = it->name;
		std::replace(name.begin(), name.end(), '"', '\'');
		erase(name, "Profiling::");
		uint64_t start = std::chrono::time_point_cast<std::chrono::microseconds>(it->start).time_since_epoch().count();
		uint64_t end = std::chrono::time_point_cast<std::chrono::microseconds>(it->end).time_since_epoch().count();
		uint32_t thread_id = std::hash<std::thread::id>{}(it->thread_id);
		m_out << "{"
			<< "\"cat\":\"function\","
			<< "\"dur\":" << (end - start) << ','
			<< "\"name\":\"" << name << "\","
			<< "\"ph\":\"X\","
			<< "\"pid\":0,"
			<< "\"tid\":" << thread_id << ","
			<< "\"ts\":" << start
			<< "}" << std::flush;
	}
	m_out << "]}" << std::flush;
}

void Profiling::TimeCapture::stop() noexcept {
	if (!TimeLogger::Instance().is_in_session()) return; // т.к. вне сессии
	TimeLogger::Instance().save_profile({ m_name, std::move(m_start), clock::now(), std::this_thread::get_id() });
	m_is_stoped = true;
}