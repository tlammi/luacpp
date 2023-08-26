#include <gtest/gtest.h>

#include <luacpp/state.hpp>
#include <luacpp/table.hpp>


namespace lc = luacpp;

class TblTest : public ::testing::Test {
  protected:
    lc::State st{};
    lc::Stack stk{st.stack()};
};

TEST_F(TblTest, New) {
    ASSERT_EQ(stk.size(), 0);
    auto tbl = stk.push_tbl();
    (void) tbl;
    ASSERT_EQ(stk.size(), 1);
}

TEST_F(TblTest, RawSetInt) {
    auto tbl = stk.push_tbl();
    tbl.rawset(10, "foo");
    tbl.rawset(1, 2);
    ASSERT_EQ(stk.size(), 1);

    auto val = tbl[10];
    ASSERT_EQ(stk.size(), 2);
    ASSERT_TRUE(val.is_str());
    ASSERT_EQ(val.to_str(), "foo");
}

