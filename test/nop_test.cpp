#include "nop.hpp"
#include "nop_test_utils.h"

#include <gtest/gtest.h>



template <class T>
std::vector<T> operator-(const std::vector<T> &a, const std::vector<T> &b) {
  std::vector<T> rt(a.size());
  for (size_t i = 0; i < a.size(); i++)
    rt[i] = a[i] - b[i];
  return rt;
}

template <class T>
std::ostream &operator<<(std::ostream &os, const std::vector<T> &data) {
  os << '(';
  for (auto x : data)
    os << x << ' ';
  os << ") ";
  return os;
}

TEST(NOP, funcMapTests)
{

    auto netOper = NetOper();
    auto a = 24.23;
    auto big_inf = pow(10,9);
    auto b = 7892.02;
    EXPECT_EQ(netOper.getUnaryOperationResult(1, a), ro_1(a));
    EXPECT_EQ(netOper.getUnaryOperationResult(2, a), ro_2(a));
    EXPECT_EQ(netOper.getUnaryOperationResult(2, big_inf), ro_2(big_inf));
    EXPECT_EQ(netOper.getUnaryOperationResult(3, a), ro_3(a));
    EXPECT_EQ(netOper.getUnaryOperationResult(4, a), ro_4(a));

    EXPECT_EQ(netOper.getBinaryOperationResult(1, a, b), xi_1(a, b));
    EXPECT_EQ(netOper.getBinaryOperationResult(2, a, b), xi_2(a, b));

}



TEST(NOP, setGetTest)
{
    auto netOper = NetOper();

    std::vector<int> nodesForVars = {0, 1, 2, 3};
    netOper.setNodesForVars(nodesForVars);
    EXPECT_TRUE(nodesForVars == netOper.getNodesForVars());

    std::vector<int> nodesForParams = {2, 3, 4, 5};
    netOper.setNodesForParams(nodesForParams);
    EXPECT_TRUE(nodesForParams == netOper.getNodesForParams());

    std::vector<int> nodesForOutput = {13, 13};
    netOper.setNodesForOutput(nodesForOutput);
    EXPECT_TRUE(nodesForOutput == netOper.getNodesForOutput());

    std::vector<float> parameters = {0.1, 0.1};
    netOper.setCs(parameters);
    EXPECT_TRUE(parameters == netOper.getCs());

    netOper.setPsi(NopPsiN);
    EXPECT_TRUE(NopPsiN == netOper.getPsi());

}


TEST(NOP, simpleTestWithFunction)
{
    auto desiredFunction = [](std::vector<float> x,
                               std::vector<float> q)
    {
        return (pow(x[0], 2) - pow(x[1], 2)) * cosf(q[0] * x[0] + q[1]) + x[0]*x[1]*exp(-q[2] * x[0]);
    };



    std::vector<float> parameters = {0.1, 0.1, 0.1};
    auto netOper = NetOper();
    // netOper.setOutputsNum(2);                // set Mout
    netOper.setNodesForVars({0, 1});         // Pnum
    netOper.setNodesForParams({2, 3, 4});    // Rnum
    netOper.setNodesForOutput({13, 13});     // Dnum
    netOper.setCs(parameters);              // set Cs

    netOper.setPsi(Psi);

    std::vector<float> x_in = {-9.4771230671817757E+001, 4.6561580083458731E-02};

    auto expectedResult = desiredFunction(x_in, parameters);


    std::vector<float> y_out(2);
    netOper.calcResult(x_in, y_out);


    std::cout << "desiredFunction RESULT: " << expectedResult << std::endl;

    std::cout << "RP RESULT: " << y_out << std::endl;
    auto diff = y_out[0] - expectedResult;
    std::cout << "DIFF: " << diff << std::endl;

    EXPECT_TRUE(abs(diff) < 0.001);
}

constexpr float test_inputs[]{
    0,
    0.123,
    1,
    6.666,
    364654846.2342,
    10E+8,
    -9.4771230671817757E+003,
    4.6561580083458731E-003
};

TEST(NOPminPsi, unarPsi) {
  using SliceT = std::vector<float>;

  NetOper netOper;
  netOper.setNodesForVars({0});
  netOper.setNodesForOutput({1});

  for (int i = 1; i <= 28; i++) {

    netOper.setPsi({
      {0, i},
      {0, 1}
    });

    std::vector<SliceT> slice_pack;

    for (float x : test_inputs) {
      slice_pack.push_back({x, netOper.getUnaryOperationResult(i, x)});
      slice_pack.push_back({-x, netOper.getUnaryOperationResult(i, -x)});
    }

    std::vector<SliceT> y_out_pack;
    std::vector<SliceT> y_out_gold_pack;

    for (auto s : slice_pack) {
      auto x_in = SliceT{s[0]};
      auto y_out_gold = SliceT{s[1]};
      auto y_out = SliceT{0};
      netOper.calcResult(x_in, y_out);
      // std::cout << y_out_gold - y_out;
      y_out_pack.push_back(y_out);
      y_out_gold_pack.push_back(y_out_gold);
    }

    EXPECT_EQ(y_out_pack, y_out_gold_pack);
  }
}

TEST(NOPminPsi, paramPsi) {
  using SliceT = std::vector<float>;

  NetOper netOper;
  netOper.setNodesForParams({0});
  netOper.setNodesForOutput({1});

  for (int i = 1; i <= 28; i++) {

    netOper.setPsi({
      {0, i},
      {0, 1}
    });

    std::vector<SliceT> slice_pack;

    for (float x : test_inputs) {
      slice_pack.push_back({x, netOper.getUnaryOperationResult(i, x)});
      slice_pack.push_back({-x, netOper.getUnaryOperationResult(i, -x)});
    }

    std::vector<SliceT> y_out_pack;
    std::vector<SliceT> y_out_gold_pack;

    for (auto s : slice_pack) {
      auto x_in = SliceT{s[0]};
      auto y_out_gold = SliceT{s[1]};
      auto y_out = SliceT{0};
      netOper.setCs(x_in);
      netOper.calcResult({0}, y_out);
      // std::cout << y_out_gold - y_out;
      y_out_pack.push_back(y_out);
      y_out_gold_pack.push_back(y_out_gold);
    }

    EXPECT_EQ(y_out_pack, y_out_gold_pack);
  }
}

TEST(NOPminPsi, multPsi) {
  using SliceT = std::vector<float>;

  NetOper netOper;
  netOper.setNodesForVars({0, 1});
  netOper.setNodesForOutput({2, 3});

  for (int i = 1; i <= 28; i++) {

    netOper.setPsi({
      {0, 0, i, 0},
      {0, 0, 0, i},
      {0, 0, 1, 0},
      {0, 0, 0, 1}
       });

    std::vector<SliceT> slice_pack;

    for (float x : test_inputs) {
      slice_pack.push_back({x, netOper.getUnaryOperationResult(i, x)});
      slice_pack.push_back({-x, netOper.getUnaryOperationResult(i, -x)});
    }

    std::vector<SliceT> y_out_pack;
    std::vector<SliceT> y_out_gold_pack;

    for (auto s : slice_pack) {
      auto x_in = SliceT{s[0], s[0]};
      auto y_out_gold = SliceT{s[1], s[1]};
      auto y_out = SliceT{0, 0};
      netOper.calcResult(x_in, y_out);
      // std::cout << y_out_gold - y_out;
      y_out_pack.push_back(y_out);
      y_out_gold_pack.push_back(y_out_gold);
    }

    EXPECT_EQ(y_out_pack, y_out_gold_pack);
  }
}

TEST(NOPminPsi, binarPsi) {
  using SliceT = std::vector<float>;

  NetOper netOper;
  netOper.setNodesForVars({0, 1});
  netOper.setNodesForOutput({2});

  for (int i = 1; i <= 8; i++) {
    netOper.setPsi({
      {0, 1, 0},
      {0, i, 1},
      {0, 0, 1}
    });

    std::vector<SliceT> slice_pack;

    for (float x : test_inputs) {
      slice_pack.push_back({x, netOper.getBinaryOperationResult(i, x,x)});
      slice_pack.push_back({-x, netOper.getBinaryOperationResult(i, -x,-x)});
    }


    std::vector<SliceT> y_out_pack;
    std::vector<SliceT> y_out_gold_pack;

    for (auto s : slice_pack) {
      auto x_in = SliceT{s[0], s[0]};
      auto y_out_gold = SliceT{s[1]};
      auto y_out = SliceT{0};
      netOper.calcResult(x_in, y_out);
      // std::cout << y_out_gold - y_out;
      y_out_pack.push_back(y_out);
      y_out_gold_pack.push_back(y_out_gold);
    }

    EXPECT_EQ(y_out_pack, y_out_gold_pack);
  }
}

TEST(NOP, trainedOperatorTest)
{

    auto netOper = NetOper();
    netOper.setNodesForVars({0, 1, 2});   // Pnum
    netOper.setNodesForParams({3, 4, 5}); // Rnum
    netOper.setNodesForOutput({22, 23});  // Dnum
    netOper.setCs(qc);                    // set Cs

    netOper.setPsi(NopPsiN);
    using SliceT = std::vector<float>;

    std::vector<SliceT> slice_pack = {
      { 2.5000000000000000E+000,  2.5000000000000000E+000,  1.3100000000000001E+000,  7.6197997817352853E+003,  -9.4771230671817757E+003 },
      { 2.5000000000000000E+000,  2.5000000000000000E+000,  -1.3100000000000001E+000, 1.4423954467471624E+001,  -3.9757176807666457E+000 },
      { 2.5000000000000000E+000,  -2.5000000000000000E+000, -1.3100000000000001E+000, -5.5207311836960698E+003, 5.8007645332198299E+003 },
      { 4.6561580083458731E-003,  4.0351029521603278E-002,  8.3948216438293491E-002,  1.3335461264421879E+001,  8.4973200088496483E+000 },
      { -9.1758697199960415E-001, -4.4754665005156380E-001, -5.1089064121246375E-001, -3.4732514696068890E+001, -6.2624360542277708E+000 },
      { 5.6599015741103036E-002,  4.1273824183417351E-002,  -2.5226671345531987E-001, -2.0985952049623924E-001, 2.6154650032382927E+000 },
    };
    std::vector<SliceT> y_out_pack;
    std::vector<SliceT> y_out_gold_pack;

    for (auto s : slice_pack) {
      auto x_in = SliceT{s[0], s[1], s[2]};
      auto y_out_gold = SliceT{s[3], s[4]};
      auto y_out = SliceT{0, 0};
      netOper.calcResult(x_in, y_out);
      y_out_pack.push_back(y_out);
      y_out_gold_pack.push_back(y_out_gold);
      
      // printf("Inputs: %.3f %.3f %.3f\n", s[0], s[1], s[2]);
      // printf("y_out     : %.3f %.3f\n", y_out[0], y_out[1]);
      // printf("y_out_gold: %.3f %.3f\n", s[3], s[4]);


    }

    for (int ii = 0; ii < y_out_pack.size(); ++ii) {
      EXPECT_TRUE(fabs(y_out_pack[ii][0] - y_out_gold_pack[ii][0]) < 0.001); 
      EXPECT_TRUE(fabs(y_out_pack[ii][1] - y_out_gold_pack[ii][1]) < 0.01); 
    }
}

TEST(NOP, readMatrixAndParamsTests)
{

  auto netOper = NetOper();
  NOPMatrixReader& reader = netOper.getReader();

  std::string cwd = getexepath();
  cwd = std::string(cwd.begin(), cwd.end()-9);
  std::string matrixPath = cwd + "/test_data/24_NOP_461";
  std::string paramsPath = cwd + "/test_data/q_461.txt";

  reader.readMatrix(matrixPath);
  reader.readParams(paramsPath);

  EXPECT_EQ(reader.getMatrix(), NopPsiN);
  EXPECT_EQ(reader.getParams(), qc);

}