#include "model.hpp"
#include <cmath>
#include <gtest/gtest.h>

// TEST(Model, reset) {
//   Model model({-10, 0, 0});
//   Model::State state{1, 0, 0};
//   model.reset(state);
//   EXPECT_EQ(model.getState().x, 1.);
// }

// TEST(Model, getNext) {
//   Model model({1, 0, 0});
//   Model::Control control{1, 1};
//   EXPECT_EQ(model.getNext(control, 1).x, 2);
//   Model::Control control2{-1, -1};
//   EXPECT_EQ(model.getNext(control2, 1).x, 0);
// }

// TEST(Model, applyControl) {
//   Model model({1, 0, 0});
//   Model::Control control{1, 1};
//   model.applyControl(control, 1);
//   EXPECT_EQ(model.getState().x, 2.);
//   model.applyControl(control, 1);
//   EXPECT_EQ(model.getState().x, 3.);
// }
