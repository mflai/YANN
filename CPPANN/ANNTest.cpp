// ANNTest.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <vector>
#include <cmath>
#include <utility>
#include "ANN.h"
#include <vector>
#include <tuple>
#include <random>

#include "gmock\gmock.h"
#include "gtest/gtest.h"

using namespace std;
using namespace CPPANN;

TEST(Basics, mattmazur)
{
	//See http://mattmazur.com/2015/03/17/a-step-by-step-backpropagation-example/. But the guy didnt update the biases

	//Setup ANN
	ANNBuilder<double> ann_builder;
	auto ann = ann_builder.set_layer(0, 2)
		.set_bias(0, { 0.35, 0.35 })
		.set_layer(1, 2)
		.set_bias(1, { 0.60, 0.60 })
		.set_weights(0, {
			{ 0.15, 0.25 },
			{ 0.20, 0.30 },
		})
		.set_layer(2, 2)
		.set_weights(1, {
			{ 0.40, 0.50 }, //weights from the 0th neuron of the present layer
			{ 0.45, 0.55 },
		})
		.build();

	//Execute ANN
	ann.forward_propagate({ 0.05, 0.10 });
	ann.back_propagate(Matrix<double>{ { 0.01, 0.99} });

	//Verify
	double tolerence = 0.00000001;
	auto &weights = ann.getWeights();
	EXPECT_NEAR(0.14978072, weights[0](0, 0), tolerence);
	EXPECT_NEAR(0.24975114, weights[0](0, 1), tolerence);
	EXPECT_NEAR(0.19956143, weights[0](1, 0), tolerence);
	EXPECT_NEAR(0.29950229, weights[0](1, 1), tolerence);
	EXPECT_NEAR(0.35891648, weights[1](0, 0), tolerence);
	EXPECT_NEAR(0.51130127, weights[1](0, 1), tolerence);
	EXPECT_NEAR(0.40866619, weights[1](1, 0), tolerence);
	EXPECT_NEAR(0.56137012, weights[1](1, 1), tolerence);
}

TEST(Basics, CounterCheckInPython)
{
	//Setup ANN
	ANNBuilder<double> ann_builder;
	auto ann = ann_builder.set_layer(0, 5)
		.set_layer(1, 4)
		.set_layer(2, 3)
		.set_layer(3, 2)
		.set_weights(0, {
			{ 0.01, 0.02, 0.03, 0.04 },
			{ 0.05, 0.06, 0.07, 0.08 },
			{ 0.09, 0.10, 0.11, 0.12 },
			{ 0.13, 0.14, 0.15, 0.16 },
			{ 0.17, 0.18, 0.19, 0.20 },
		})
		.set_weights(1, {
			{ 0.25, 0.26, 0.27 },
			{ 0.28, 0.29, 0.30 },
			{ 0.31, 0.32, 0.33 },
			{ 0.34, 0.35, 0.36 },
		})
		.set_weights(2, {
			{ 0.40, 0.41 },
			{ 0.42, 0.43 },
			{ 0.44, 0.45 },
		})
		.set_bias(0, { 0.21, 0.22, 0.23, 0.24 })
		.set_bias(1, { 0.37, 0.38, 0.39 })
		.set_bias(2, { 0.46, 0.47 })
		.build();

	ann.forward_propagate({ 0.18, 0.29, 0.40, 0.51, 0.62 });
	ann.back_propagate(Matrix<double>{ { 0.01, 0.99 }});

	//Verify
	double tolerence = 0.00000001;
	auto &weights = ann.getWeights();
	EXPECT_NEAR(0.00987499, weights[0](0, 0), tolerence);
	EXPECT_NEAR(0.0198615, weights[0](0, 1), tolerence);
	EXPECT_NEAR(0.02984825, weights[0](0, 2), tolerence);
	EXPECT_NEAR(0.03983527, weights[0](0, 3), tolerence);
	EXPECT_NEAR(0.0497986, weights[0](1, 0), tolerence);
	EXPECT_NEAR(0.05977686, weights[0](1, 1), tolerence);
	EXPECT_NEAR(0.06975552, weights[0](1, 2), tolerence);
	EXPECT_NEAR(0.07973461, weights[0](1, 3), tolerence);
	EXPECT_NEAR(0.0897222, weights[0](2, 0), tolerence);
	EXPECT_NEAR(0.09969222, weights[0](2, 1), tolerence);
	EXPECT_NEAR(0.10966279, weights[0](2, 2), tolerence);
	EXPECT_NEAR(0.11963394, weights[0](2, 3), tolerence);
	EXPECT_NEAR(0.12964581, weights[0](3, 0), tolerence);
	EXPECT_NEAR(0.13960758, weights[0](3, 1), tolerence);
	EXPECT_NEAR(0.14957005, weights[0](3, 2), tolerence);
	EXPECT_NEAR(0.15953327, weights[0](3, 3), tolerence);
	EXPECT_NEAR(0.16956941, weights[0](4, 0), tolerence);
	EXPECT_NEAR(0.17952294, weights[0](4, 1), tolerence);
	EXPECT_NEAR(0.18947732, weights[0](4, 2), tolerence);
	EXPECT_NEAR(0.1994326, weights[0](4, 3), tolerence);
	EXPECT_NEAR(0.24780606, weights[1](0, 0), tolerence);
	EXPECT_NEAR(0.25773575, weights[1](0, 1), tolerence);
	EXPECT_NEAR(0.26766959, weights[1](0, 2), tolerence);
	EXPECT_NEAR(0.27778027, weights[1](1, 0), tolerence);
	EXPECT_NEAR(0.28770913, weights[1](1, 1), tolerence);
	EXPECT_NEAR(0.29764219, weights[1](1, 2), tolerence);
	EXPECT_NEAR(0.30775465, weights[1](2, 0), tolerence);
	EXPECT_NEAR(0.31768269, weights[1](2, 1), tolerence);
	EXPECT_NEAR(0.32761498, weights[1](2, 2), tolerence);
	EXPECT_NEAR(0.33772922, weights[1](3, 0), tolerence);
	EXPECT_NEAR(0.34765645, weights[1](3, 1), tolerence);
	EXPECT_NEAR(0.35758797, weights[1](3, 2), tolerence);
	EXPECT_NEAR(0.35310712, weights[2](0, 0), tolerence);
	EXPECT_NEAR(0.4204483, weights[2](0, 1), tolerence);
	EXPECT_NEAR(0.3727042, weights[2](1, 0), tolerence);
	EXPECT_NEAR(0.44053808, weights[2](1, 1), tolerence);
	EXPECT_NEAR(0.39230839, weights[2](2, 0), tolerence);
	EXPECT_NEAR(0.46062627, weights[2](2, 1), tolerence);

	auto &biases = ann.getBiases();
	EXPECT_NEAR(0.2093055, biases[0](0, 0), tolerence);
	EXPECT_NEAR(0.21923054, biases[0](0, 1), tolerence);
	EXPECT_NEAR(0.22915696, biases[0](0, 2), tolerence);
	EXPECT_NEAR(0.23908484, biases[0](0, 3), tolerence);
	EXPECT_NEAR(0.36638459, biases[1](0, 0), tolerence);
	EXPECT_NEAR(0.37626872, biases[1](0, 1), tolerence);
	EXPECT_NEAR(0.38615969, biases[1](0, 2), tolerence);
	EXPECT_NEAR(0.39749299, biases[2](0, 0), tolerence);
	EXPECT_NEAR(0.48392732, biases[2](0, 1), tolerence);
}

TEST(Basics, Accending_and_decending)
{
	//Setup ANN
	ANNBuilder<double> ann_builder;
	auto ann = ann_builder.set_layer(0, 5)
		.set_layer(1, 4)
		.set_layer(2, 3)
		.set_layer(3, 2)
		.set_weights(0, {
			{ 0.01, 0.02, 0.03, 0.04 },
			{ 0.05, 0.06, 0.07, 0.08 },
			{ 0.09, 0.10, 0.11, 0.12 },
			{ 0.13, 0.14, 0.15, 0.16 },
			{ 0.17, 0.18, 0.19, 0.20 },
		})
		.set_weights(1, {
			{ 0.25, 0.26, 0.27 },
			{ 0.28, 0.29, 0.30 },
			{ 0.31, 0.32, 0.33 },
			{ 0.34, 0.35, 0.36 },
		})
		.set_weights(2, {
			{ 0.40, 0.41 },
			{ 0.42, 0.43 },
			{ 0.44, 0.45 },
		})
		.set_bias(0, { 0.21, 0.22, 0.23, 0.24 })
		.set_bias(1, { 0.37, 0.38, 0.39 })
		.set_bias(2, { 0.46, 0.47 })
		.build();

	std::vector<double> low_to_high_input = { 0.18, 0.29, 0.40, 0.51, 0.62 };
	std::vector<double> low_to_high_expected_result = { 0.01, 0.99 };
	std::vector<double> high_to_low_input = { 0.62, 0.51, 0.40, 0.29, 0.18 };
	std::vector<double> high_to_low_expected_result = { 0.99, 0.01 };

	for (int i = 0; i < 1000000; i++) {
		ann.forward_propagate(low_to_high_input);
		ann.back_propagate(low_to_high_expected_result);
		ann.forward_propagate(high_to_low_input);
		ann.back_propagate(high_to_low_expected_result);
	}

	std::vector<double> low_to_high_output = ann.forward_propagate(low_to_high_input);
	std::vector<double> high_to_low_output = ann.forward_propagate(high_to_low_input);

	double tolerence = 0.05;
	EXPECT_NEAR(0.01, low_to_high_output[0], tolerence);
	EXPECT_NEAR(0.99, low_to_high_output[1], tolerence);
	EXPECT_NEAR(0.99, high_to_low_output[0], tolerence);
	EXPECT_NEAR(0.01, high_to_low_output[1], tolerence);
}

TEST(Basics, XOR_SIGMOID)
{
	ANNBuilder<double> ann_builder;
	auto ann = ann_builder.set_layer(0, 2)
		.set_layer(1, 2)
		.set_weights(0, {
			{ 0.5, -0.7 },
			{ -0.8, 0.6 }
		})
		.set_bias(0, { 0.01, -0.9 })
		.set_weights(1, {
			{ 2. }, //weights from the 0th neuron of the present layer
			{ 3. },
		})
		.set_layer(2, 1)
		.set_bias(1, { -0.8 })
		.build();

	std::vector<double> true_true_input{ 1., 1. };
	Matrix<double> true_true_expected_result{ {0.} };

	std::vector<double> false_false_input{ 0., 0. };
	Matrix<double> false_false_expected_result{ { 0. } };
	
	std::vector<double> false_true_input{ 0., 1. };
	Matrix<double> false_true_expected_result{ { 1. } };

	std::vector<double> true_false_input{ 1., 0. };
	Matrix<double> true_false_expected_result{ { 1. } };

	std::vector<double> true_true_result, false_true_result, true_false_result, false_false_result;
	for (int i = 0; i < 1000000; i++) {
		true_true_result = ann.forward_propagate(true_true_input);
		ann.back_propagate(true_true_expected_result);
		false_false_result = ann.forward_propagate(false_false_input);
		ann.back_propagate(false_false_expected_result);
		false_true_result = ann.forward_propagate(false_true_input);
		ann.back_propagate(false_true_expected_result);
		true_false_result = ann.forward_propagate(true_false_input);
		ann.back_propagate(true_false_expected_result);
	}
	double tolerence = 0.05;
	EXPECT_NEAR(0., true_true_result[0], tolerence);
	EXPECT_NEAR(0., false_false_result[0], tolerence);
	EXPECT_NEAR(1., false_true_result[0], tolerence);
	EXPECT_NEAR(1., true_false_result[0], tolerence);
}

int main(int argc, char *argv[])
{
	::testing::InitGoogleMock(&argc, argv);
	return RUN_ALL_TESTS();
}