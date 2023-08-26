#include <luacpp/any.hpp>

namespace luacpp {

Any::~Any() {
    using enum TypeId;
    switch (m_id) {
        case Nil:
            std::destroy_at(&m_nil);
            return;
        case Bool:
            std::destroy_at(&m_bool);
            return;
        case TypeId::LightUserdata:
            std::terminate();
        case TypeId::Number:
            std::destroy_at(&m_dbl);
            return;
        case TypeId::String:
            std::destroy_at(&m_str);
            return;
        case TypeId::Table:
        case TypeId::Func:
        case TypeId::Userdata:
        case TypeId::Thread:
        case TypeId::Unknown:
            std::terminate();
            break;
    }
}
} // namespace luacpp
