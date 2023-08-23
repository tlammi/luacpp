#pragma once

#include <bitset>
#include <luacpp/detail/tags.hpp>
#include <luacpp/stack.hpp>
#include <luacpp/types.hpp>
#include <optional>
#include <string_view>

namespace luacpp {
using StateFlags = std::bitset<1>;
namespace flags {
constexpr StateFlags open_libs = 0b1;
} // namespace flags

/**
 * \brief Root object for Lua context
 *
 * This object contains e.g. Lua stack and all functions etc.
 * */
class State {
  public:
    explicit State(StateFlags opts = 0);

    State(const State&) = delete;
    State& operator=(const State&) = delete;

    State(State&&) noexcept;
    State& operator=(State&&) noexcept;

    ~State();

    void dofile(const char* path);
    void dofile(const std::string& str) {
        dofile(str.c_str());
    }

    void dostr(const char* str);
    void dostr(const std::string& str) {
        dostr(str.c_str());
    }

    /**
     * \brief Evaluate an expression and get the result
     * */
    template <class T>
    T evalstr(const char* expr) {
        std::string script = std::string{"return "} + expr;
        loadstring(script.c_str());
        pcall(0, 1);
        return pop_stack_int().value();
    }

    /**
     * \brief Set value of a global symbol
     *
     * This assigns the given value to the variable and creates the variable does not exist.
     *
     * \param name Symbol name
     * \param t value to assign
     * */
    template <class T>
    void set_global(const char* name, const T& t) {
        if constexpr (std::is_integral_v<T>) {
            set_global_int(name, t);
        } else if constexpr (std::is_floating_point_v<T>) {
            set_global_float(name, t);
        } else if constexpr (std::is_convertible_v<T, std::string_view>) {
            set_global_str(name, t);
        } else {
            [] { static_assert(false); };
        }
    }

    /**
     * \brief Read value from a global symbol
     * */
    template <class T>
    T get_global(const char* name) {
        get_global_to_stack(name);
        if constexpr (std::is_integral_v<T>) {
            return pop_stack_int().value();
        } else if constexpr (std::is_floating_point_v<T>) {
            return pop_stack_float().value();
        } else if constexpr (std::is_same_v<T, std::string>) {
            return pop_stack_str();
        } else {
            [] { static_assert(false); };
        }
    }

    /**
     * \brief Number of entries in Lua stack.
     *
     * This is mostly used for testing
     * */
    [[nodiscard]] size_t stack_size() const noexcept;

#if defined(LUACPP_LUA_HANDLE)
    /**
     * \brief Access raw lua state
     * */
    lua_State* lua_state() const noexcept;
#endif


    Stack stack() noexcept {
        return Stack{*m_st};
    }


  private:
    /// \brief luaL_loadstring
    void loadstring(const char* str);
    /// \brief luaL_pcall
    void pcall(int nargs, int nres);
    void set_global_int(const char* name, Int i);
    void set_global_float(const char* name, Double d);
    void set_global_str(const char* name, std::string_view s);

    void get_global_to_stack(const char* name);

    std::optional<Int> pop_stack_int();
    std::optional<Double> pop_stack_float();
    std::string pop_stack_str();

    detail::state_t* m_st{nullptr};
};

} // namespace luacpp
