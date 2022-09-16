#pragma once
#include <fstream>
#include <chrono>
#include <thread>
#include <mutex>
#include <vector>
#include <atomic>

#define MESURE_TIME

namespace Profiling {
	using clock = std::chrono::high_resolution_clock;
	using time_point = std::chrono::time_point<clock>;

	struct ProfileResult {
		const char* name;
		time_point start, end;
		std::thread::id thread_id;
	};

	class TimeLogger {
	public: // Singletone
		TimeLogger(const TimeLogger&) = delete;
		TimeLogger& operator = (const TimeLogger&) = delete;
		static TimeLogger& Instance() {
			static TimeLogger instance;
			return instance;
		}
	public: // Интерфейс
		void start_session(const std::string& file_path = "log_time.json", size_t buffer_size = 100);
		bool is_in_session() const noexcept { return m_is_in_session; }
		void end_session();
	private: // Singletone
		TimeLogger() = default;
		~TimeLogger() { if (m_is_in_session) end_session(); }
	private: // Скрытые методы
		friend class TimeCapture;
		void save_profile(ProfileResult&& result);
		void record_session();
	private: // Поля класса
		std::mutex m_mutex; // обеспечивает потокобезопасную работу
		std::ofstream m_out; // ассоциируется с JSON для текущей сессии
		std::vector<ProfileResult> m_profile_buffer; //быстро сохраняет результаты во время сессии
		size_t m_init_buffer_size = 0; // запоминает размер буфера в начале сессии
		std::atomic<bool> m_is_in_session = false; //отслеживает состояние сессии (внутри или вне)
	};

	class TimeCapture {
	public:
		TimeCapture(const char* name)
			: m_name(name), m_is_stoped(false), m_start(clock::now()) {}
		~TimeCapture() { if (!m_is_stoped) stop(); }
		void stop() noexcept;
	private:
		const char* m_name;
		bool m_is_stoped;
		time_point m_start;
	};
} // end Profiling  

#ifdef MESURE_TIME
#define START_SESSION_ARGS(path, buffer) Profiling::TimeLogger::Instance().start_session(path, buffer);
#define START_SESSION_PATH(path) Profiling::TimeLogger::Instance().start_session(path);
#define PROFILE_SCOPE(name) Profiling::TimeCapture time_capture(name);
#define END_SESSION Profiling::TimeLogger::Instance().end_session();
#else
#define START_SESSION_ARGS(path, buffer)
#define START_SESSION_PATH(path)
#define PROFILE_SCOPE(name) 
#define END_SESSION 
#endif

#define START_SESSION START_SESSION_PATH()
#define PROFILE_FUNCTION PROFILE_SCOPE(__FUNCTION__)