#ifndef STDLOG_H
#define STDLOG_H

#include <iostream>
#include <string>

// this switch controls StdLog::Debug and AutoLog outputs
#define LOG_DEBUG

#ifdef LOG_DEBUG
  #define STDLOG_DEBUG
  #define AUTOLOG_DEBUG
#endif

namespace bzh_utils
{
    namespace log
    {
        class StdLog
        {
        private:
            template <typename T, typename... Ts> static void printer(T arg1, Ts... arg_left)
            {
                std::cout << arg1;
                if constexpr ( sizeof...(arg_left) > 0 )
                    printer(arg_left...);
                else
                    std::cout << std::endl;
            }

        public:
            template <typename T, typename... Ts> static void Info(T arg1, Ts... arg_left)
            {
                std::cout << "[" << __FUNCTION__ << "] ";
                printer(arg1, arg_left...);
            }
            template <typename T, typename... Ts> static void Warning(T arg1, Ts... arg_left)
            {
                std::cout << "[" << __FUNCTION__ << "] ";
                printer(arg1, arg_left...);
            }
            template <typename T, typename... Ts> static void Error(T arg1, Ts... arg_left)
            {
                std::cout << "[" << __FUNCTION__ << "] ";
                printer(arg1, arg_left...);
            }
            template <typename T, typename... Ts> static void Debug(T arg1, Ts... arg_left)
            {
#ifdef STDLOG_DEBUG
                std::cout << "[" << __FUNCTION__ << "] ";
                printer(arg1, arg_left...);
#endif
            }
        };

#define AUTOLOG_TAB_SPACE 4

#define AUTOLOG_DETAILED                                                                   \
  bzh_utils::log::AutoLog autolog_##__func__(                                              \
      std::string(__FILE__) + ":" + std::to_string(__LINE__) + ":" + std::string(__func__) \
  )
#define AUTOLOG_FUNC_ONLY bzh_utils::log::AutoLog autolog_##__func__(std::string(__func__))

        class AutoLog
        {
        public:
            std::string str_construction, str_deconstruction;
            std::string str_message;

            AutoLog(
                std::string message,
                std::string construction = "Enter: ", std::string deconstruction = "Exit: "
            )
            {
#ifdef AUTOLOG_DEBUG
                str_message = message;
                str_construction = construction;
                str_deconstruction = deconstruction;

                std::cout << "[AutoLog] " << str_construction << str_message << std::endl;
#endif
            }
            ~AutoLog()
            {
#ifdef AUTOLOG_DEBUG
                std::cout << "[AutoLog] " << str_deconstruction << str_message << std::endl;
#endif
            }
        };

    }; // namespace log

}; // namespace bzh_utils

#endif // STDLOG_H